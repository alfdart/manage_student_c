# Project: Student Management System (CRUD + Grade Calculation in C)
## Summary
Developed a command-line student management system in C that demonstrates object-oriented programming principles (simulated via struct and associated functions). The program supports creating, reading, updating, and deleting (CRUD) student records, storing them in a text file. Additionally, it allows for entering and averaging students’ grades.

## Key Features

- Simulated OOP in C: Used struct as a “class,” encapsulating student attributes (ID, name, and notes array), with functions acting as methods.
- CRUD Operations: Created functions to add, retrieve, update, and delete students directly from a .txt file.
- Grade Management: Enabled adding multiple grades per student and calculating their average score.
- File Persistence: Implemented text-file–based storage, making it easy to share and persist data without a database.
- User-Friendly Menu: Included a simple, interactive CLI menu that guides users to perform operations.
  
##Technologies & Concepts

- C Language: Leveraged fundamental C features, including file I/O (fopen, fclose, etc.), string manipulation, and structures.
- Procedural & Modular Design: Organized the code into multiple files (.h / .c) to separate declarations from implementations.
- POO-Like Approach: Emulated basic object-oriented principles, such as “constructors,” “methods,” and data encapsulation.
- Error Handling: Ensured safe string operations (e.g., strncpy, boundary checks) and file access error checking.
- Computational Logic: Calculated averages by iterating through stored grades.
## Why It’s Relevant

- Demonstrates your ability to build robust C applications with file operations and data handling.
- Highlights understanding of code organization (headers vs. source files, modular design).
- Showcases the simulation of OOP concepts (e.g., “methods” for structs) in a lower-level language.
- Emphasizes familiarity with basic algorithms (like computing averages) and CRUD workflows.

## Possible Extensions

- Enhance file structure (e.g., CSV or binary storage).
- Add error handling, data validation (e.g., restricting invalid grades).
- Expand the system to include advanced features like searching by name or sorting.
- Incorporate a user interface library (curses) for a more polished CLI experience.
