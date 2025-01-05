#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50
#define MAX_NOTES    20

typedef struct {
    int    id;
    char   name[MAX_NAME_LEN];
    float  notes[MAX_NOTES];
    int    notesCount;
} Student;

/* ---- Fonctions « méthodes » associées à Student ---- */

/**
 * @brief Initialise un étudiant (constructeur).
 * @param s Pointeur vers la structure Student à initialiser.
 * @param id Identifiant unique de l'étudiant.
 * @param name Nom de l'étudiant (char *).
 */
void initStudent(Student *s, int id, const char *name);

/**
 * @brief Ajoute une note à l'étudiant (s'il y a de la place).
 * @param s Pointeur vers la structure Student.
 * @param note La note (float).
 */
void addNote(Student *s, float note);

/**
 * @brief Calcule la moyenne des notes d’un étudiant.
 * @param s Pointeur vers la structure Student.
 * @return La moyenne (float). Retourne 0 si aucune note.
 */
float calculateAverage(const Student *s);

/**
 * @brief Affiche les informations d’un étudiant.
 * @param s Pointeur vers la structure Student.
 */
void displayStudent(const Student *s);

/* ---- Fonctions CRUD pour gérer les étudiants dans le fichier ---- */

/**
 * @brief Ajoute un nouvel étudiant dans le fichier.
 * @param filename Nom du fichier (char *).
 * @param s Pointeur vers l'étudiant à ajouter.
 * @return 1 si succès, 0 sinon.
 */
int createStudent(const char *filename, const Student *s);

/**
 * @brief Recherche et lit un étudiant à partir de son id dans le fichier.
 * @param filename Nom du fichier (char *).
 * @param id Identifiant de l’étudiant à rechercher.
 * @param foundStudent Pointeur vers la structure où stocker l'étudiant trouvé.
 * @return 1 si trouvé, 0 sinon.
 */
int readStudent(const char *filename, int id, Student *foundStudent);

/**
 * @brief Met à jour (modifie) un étudiant existant dans le fichier.
 * @param filename Nom du fichier (char *).
 * @param s Pointeur vers l'étudiant à mettre à jour.
 * @return 1 si succès, 0 sinon.
 */
int updateStudent(const char *filename, const Student *s);

/**
 * @brief Supprime un étudiant (par id) dans le fichier.
 * @param filename Nom du fichier (char *).
 * @param id Identifiant de l’étudiant à supprimer.
 * @return 1 si succès, 0 sinon.
 */
int deleteStudent(const char *filename, int id);

#endif
