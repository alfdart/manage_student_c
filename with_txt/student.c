#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS  // Pour éviter les warnings sur Windows
#endif

#include "student.h"

/* ---- Fonctions « méthodes » Student ---- */

void initStudent(Student *s, int id, const char *name) {
    if (s == NULL) return;
    s->id = id;
    strncpy(s->name, name, MAX_NAME_LEN - 1);
    s->name[MAX_NAME_LEN - 1] = '\0';  // Sécurité
    s->notesCount = 0;
}

void addNote(Student *s, float note) {
    if (s == NULL) return;
    if (s->notesCount < MAX_NOTES) {
        s->notes[s->notesCount++] = note;
    } else {
        printf("Impossible d'ajouter plus de notes (limite atteinte : %d).\n", MAX_NOTES);
    }
}

float calculateAverage(const Student *s) {
    if (s == NULL || s->notesCount == 0) return 0.0f;
    float sum = 0.0f;
    for (int i = 0; i < s->notesCount; i++) {
        sum += s->notes[i];
    }
    return sum / s->notesCount;
}

void displayStudent(const Student *s) {
    if (s == NULL) return;
    printf("ID: %d | Nom: %s\n", s->id, s->name);
    printf("Notes: ");
    for (int i = 0; i < s->notesCount; i++) {
        printf("%.2f ", s->notes[i]);
    }
    printf("\n");
    printf("Moyenne: %.2f\n", calculateAverage(s));
    printf("--------------------\n");
}


/* ---- Fonctions CRUD ---- 
   Format d'enregistrement dans le fichier : 
   ID Nom notesCount notes...
   Par exemple :
   1 Jean 2 12.50 15.75
   2 Alice 3 10.00 14.00 9.75
*/

int createStudent(const char *filename, const Student *s) {
    if (s == NULL) return 0;
    FILE *fp = fopen(filename, "a"); // "a" pour ajouter à la fin
    if (!fp) {
        perror("Erreur d'ouverture de fichier (createStudent)");
        return 0;
    }
    // On écrit : id name notesCount notes...
    fprintf(fp, "%d %s %d", s->id, s->name, s->notesCount);
    for (int i = 0; i < s->notesCount; i++) {
        fprintf(fp, " %.2f", s->notes[i]);
    }
    fprintf(fp, "\n");
    fclose(fp);
    return 1;
}

int readStudent(const char *filename, int id, Student *foundStudent) {
    if (foundStudent == NULL) return 0;
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        // Fichier peut ne pas exister encore
        return 0;
    }
    
    int tempId, notesCount;
    char tempName[MAX_NAME_LEN];
    float tempNote;
    int found = 0;

    while (!feof(fp)) {
        if (fscanf(fp, "%d %s %d", &tempId, tempName, &notesCount) == 3) {
            Student s;
            initStudent(&s, tempId, tempName);
            // On lit les notes si notesCount > 0
            for (int i = 0; i < notesCount; i++) {
                if (fscanf(fp, "%f", &tempNote) == 1) {
                    addNote(&s, tempNote);
                }
            }
            // On compare avec l'id recherché
            if (s.id == id) {
                *foundStudent = s; // Copie de la structure
                found = 1;
                break;
            }
        }
    }
    fclose(fp);
    return found;
}

int updateStudent(const char *filename, const Student *updatedStudent) {
    if (updatedStudent == NULL) return 0;

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        // Fichier inexistant => rien à mettre à jour
        return 0;
    }

    // On va créer un fichier temporaire pour réécrire toutes les données
    // en y insérant la version mise à jour de l'étudiant.
    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        fclose(fp);
        perror("Erreur d'ouverture du fichier temporaire (updateStudent)");
        return 0;
    }

    int tempId, notesCount;
    char tempName[MAX_NAME_LEN];
    float tempNote;
    int found = 0;

    // Lecture/écriture
    while (!feof(fp)) {
        if (fscanf(fp, "%d %s %d", &tempId, tempName, &notesCount) == 3) {
            Student s;
            initStudent(&s, tempId, tempName);
            for (int i = 0; i < notesCount; i++) {
                if (fscanf(fp, "%f", &tempNote) == 1) {
                    addNote(&s, tempNote);
                }
            }
            // Si c'est l'étudiant qu'on veut mettre à jour
            if (s.id == updatedStudent->id) {
                s = *updatedStudent; // Remplace par la nouvelle version
                found = 1;
            }
            // Écriture dans le fichier temporaire
            fprintf(temp, "%d %s %d", s.id, s.name, s.notesCount);
            for (int i = 0; i < s.notesCount; i++) {
                fprintf(temp, " %.2f", s.notes[i]);
            }
            fprintf(temp, "\n");
        }
    }

    fclose(fp);
    fclose(temp);

    // On remplace l'ancien fichier par le nouveau
    remove(filename);
    rename("temp.txt", filename);

    return found;
}

int deleteStudent(const char *filename, int id) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        // Fichier inexistant => rien à supprimer
        return 0;
    }
    
    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        fclose(fp);
        perror("Erreur d'ouverture du fichier temporaire (deleteStudent)");
        return 0;
    }

    int tempId, notesCount;
    char tempName[MAX_NAME_LEN];
    float tempNote;
    int found = 0;

    while (!feof(fp)) {
        if (fscanf(fp, "%d %s %d", &tempId, tempName, &notesCount) == 3) {
            Student s;
            initStudent(&s, tempId, tempName);
            for (int i = 0; i < notesCount; i++) {
                if (fscanf(fp, "%f", &tempNote) == 1) {
                    addNote(&s, tempNote);
                }
            }
            if (s.id == id) {
                // On ne recopie pas cet étudiant => suppression
                found = 1;
            } else {
                // On recopie tel quel
                fprintf(temp, "%d %s %d", s.id, s.name, s.notesCount);
                for (int i = 0; i < s.notesCount; i++) {
                    fprintf(temp, " %.2f", s.notes[i]);
                }
                fprintf(temp, "\n");
            }
        }
    }

    fclose(fp);
    fclose(temp);

    remove(filename);
    rename("temp.txt", filename);

    return found;
}
