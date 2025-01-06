#!/usr/bin/env python3
"""
Python Student Management System with SQLite

Usage:
    python main.py
"""

import sqlite3

DB_NAME = "students.db"

def create_tables(conn):
    """
    Create the students and grades tables if they don't already exist.
    """
    with conn:
        conn.execute("""
            CREATE TABLE IF NOT EXISTS students (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                name TEXT NOT NULL
            );
        """)
        conn.execute("""
            CREATE TABLE IF NOT EXISTS grades (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                student_id INTEGER NOT NULL,
                grade_value REAL NOT NULL,
                FOREIGN KEY(student_id) REFERENCES students(id)
            );
        """)

def create_student(conn, name):
    """
    Insert a new student into the 'students' table.
    Returns True if successful, False otherwise.
    """
    try:
        with conn:
            conn.execute("INSERT INTO students(name) VALUES(?);", (name,))
        return True
    except sqlite3.Error as e:
        print(f"Error creating student: {e}")
        return False

def read_student(conn, student_id):
    """
    Retrieve a student record by ID.
    Returns a tuple (id, name) if found, or None if not found.
    """
    cursor = conn.cursor()
    cursor.execute("SELECT id, name FROM students WHERE id = ?;", (student_id,))
    row = cursor.fetchone()
    if row:
        return row  # (id, name)
    return None

def add_grade(conn, student_id, grade):
    """
    Add a grade record for the specified student_id.
    Returns True if successful, False otherwise.
    """
    try:
        with conn:
            conn.execute("""
                INSERT INTO grades(student_id, grade_value)
                VALUES(?, ?);
            """, (student_id, grade))
        return True
    except sqlite3.Error as e:
        print(f"Error adding grade: {e}")
        return False

def update_student_name(conn, student_id, new_name):
    """
    Update the name of a student by ID.
    Returns True if at least one row was updated, False otherwise.
    """
    try:
        with conn:
            result = conn.execute("""
                UPDATE students
                SET name = ?
                WHERE id = ?;
            """, (new_name, student_id))
        # Check how many rows were updated
        if result.rowcount > 0:
            return True
        return False
    except sqlite3.Error as e:
        print(f"Error updating student: {e}")
        return False

def delete_student(conn, student_id):
    """
    Delete a student (and their grades) from the database.
    Returns True if the student was deleted, False otherwise.
    """
    try:
        with conn:
            # First, delete from 'grades' table
            conn.execute("DELETE FROM grades WHERE student_id = ?;", (student_id,))
            # Then, delete from 'students' table
            result = conn.execute("DELETE FROM students WHERE id = ?;", (student_id,))
        if result.rowcount > 0:
            return True
        return False
    except sqlite3.Error as e:
        print(f"Error deleting student: {e}")
        return False

def calculate_average(conn, student_id):
    """
    Calculate the average of all grades for the given student_id.
    Returns the average as a float or None if no grades exist or error occurs.
    """
    try:
        cursor = conn.cursor()
        cursor.execute("""
            SELECT AVG(grade_value)
            FROM grades
            WHERE student_id = ?;
        """, (student_id,))
        row = cursor.fetchone()
        if row and row[0] is not None:
            return float(row[0])
        return None
    except sqlite3.Error as e:
        print(f"Error calculating average: {e}")
        return None

def main():
    # Connect (or create) the database
    conn = sqlite3.connect(DB_NAME)
    
    # Create tables if they don't exist
    create_tables(conn)

    while True:
        print("\n========== MENU ==========")
        print("1. Create Student")
        print("2. Read Student (by ID)")
        print("3. Add Grade to Student")
        print("4. Update Student Name")
        print("5. Delete Student")
        print("6. Calculate Average")
        print("7. Exit")
        print("==========================")

        choice = input("Choose an option: ").strip()

        if choice == "1":
            name = input("Enter student name: ")
            if create_student(conn, name):
                print("Student created successfully.")
            else:
                print("Failed to create student.")

        elif choice == "2":
            student_id = input("Enter Student ID to read: ")
            if not student_id.isdigit():
                print("Invalid ID.")
                continue
            student_id = int(student_id)
            student = read_student(conn, student_id)
            if student:
                print(f"ID: {student[0]}, Name: {student[1]}")
            else:
                print("Student not found.")

        elif choice == "3":
            student_id = input("Enter Student ID to add grade: ")
            if not student_id.isdigit():
                print("Invalid ID.")
                continue
            student_id = int(student_id)
            grade_input = input("Enter Grade (float): ")
            try:
                grade = float(grade_input)
            except ValueError:
                print("Invalid grade.")
                continue
            if add_grade(conn, student_id, grade):
                print("Grade added successfully.")
            else:
                print("Failed to add grade.")

        elif choice == "4":
            student_id = input("Enter Student ID to update: ")
            if not student_id.isdigit():
                print("Invalid ID.")
                continue
            student_id = int(student_id)
            new_name = input("Enter new student name: ")
            if update_student_name(conn, student_id, new_name):
                print("Student updated successfully.")
            else:
                print("Failed to update student or student not found.")

        elif choice == "5":
            student_id = input("Enter Student ID to delete: ")
            if not student_id.isdigit():
                print("Invalid ID.")
                continue
            student_id = int(student_id)
            if delete_student(conn, student_id):
                print("Student deleted.")
            else:
                print("Failed to delete student or student not found.")

        elif choice == "6":
            student_id = input("Enter Student ID for average calculation: ")
            if not student_id.isdigit():
                print("Invalid ID.")
                continue
            student_id = int(student_id)
            avg = calculate_average(conn, student_id)
            if avg is not None:
                print(f"Average grade: {avg:.2f}")
            else:
                print("No grades found or error occurred.")

        elif choice == "7":
            print("Exiting. Goodbye!")
            break

        else:
            print("Invalid choice. Please try again.")

    conn.close()


if __name__ == "__main__":
    main()
