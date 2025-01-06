#include "student.h"

#define FILENAME "etudiants.txt"

void menu() {
    printf("\n========== MENU ==========\n");
    printf("1. Creer un etudiant\n");
    printf("2. Lire un etudiant (afficher ses infos)\n");
    printf("3. Mettre a jour (ajouter une note, modifier nom...)\n");
    printf("4. Supprimer un etudiant\n");
    printf("5. Quitter\n");
    printf("==========================\n");
    printf("Votre choix : ");
}

int main() {
    int choix;
    int id;
    char nom[MAX_NAME_LEN];
    float note;
    Student s;
    Student found;

    do {
        menu();
        scanf("%d", &choix);
        getchar(); // Pour consommer le \n restant

        switch (choix) {
        case 1:
            printf("Entrez ID: ");
            scanf("%d", &id);
            getchar();

            printf("Entrez Nom: ");
            fgets(nom, MAX_NAME_LEN, stdin);
            // Supprimer le \n s'il existe
            nom[strcspn(nom, "\n")] = '\0';

            initStudent(&s, id, nom);

            // Optionnel : ajouter quelques notes
            int nbNotes;
            printf("Combien de notes voulez-vous saisir ? ");
            scanf("%d", &nbNotes);
            for (int i = 0; i < nbNotes; i++) {
                printf("Note %d: ", i + 1);
                scanf("%f", &note);
                addNote(&s, note);
            }

            if (createStudent(FILENAME, &s)) {
                printf("Etudiant cree avec succes.\n");
            } else {
                printf("Echec de creation.\n");
            }
            break;

        case 2:
            printf("Entrez ID de l'etudiant a lire: ");
            scanf("%d", &id);
            if (readStudent(FILENAME, id, &found)) {
                displayStudent(&found);
            } else {
                printf("Etudiant introuvable.\n");
            }
            break;

        case 3:
            printf("Entrez ID de l'etudiant a mettre a jour: ");
            scanf("%d", &id);
            // On lit d'abord les infos existantes
            if (readStudent(FILENAME, id, &found)) {
                printf("Etudiant trouve : \n");
                displayStudent(&found);

                // Exemple : Ajouter une nouvelle note
                printf("Voulez-vous ajouter une note ? (1 = Oui, 0 = Non) : ");
                int rep;
                scanf("%d", &rep);
                if (rep == 1) {
                    printf("Entrez la note : ");
                    scanf("%f", &note);
                    addNote(&found, note);
                }

                // Exemple : Mettre a jour le nom
                printf("Voulez-vous changer le nom ? (1 = Oui, 0 = Non) : ");
                scanf("%d", &rep);
                getchar();
                if (rep == 1) {
                    printf("Nouveau nom : ");
                    fgets(nom, MAX_NAME_LEN, stdin);
                    nom[strcspn(nom, "\n")] = '\0';
                    strncpy(found.name, nom, MAX_NAME_LEN - 1);
                }

                // On enregistre les modifications
                if (updateStudent(FILENAME, &found)) {
                    printf("Mise a jour reussie.\n");
                } else {
                    printf("Echec de la mise a jour.\n");
                }
            } else {
                printf("Etudiant introuvable.\n");
            }
            break;

        case 4:
            printf("Entrez ID de l'etudiant a supprimer: ");
            scanf("%d", &id);
            if (deleteStudent(FILENAME, id)) {
                printf("Etudiant supprime avec succes.\n");
            } else {
                printf("Echec de la suppression ou etudiant introuvable.\n");
            }
            break;

        case 5:
            printf("Au revoir !\n");
            break;

        default:
            printf("Choix invalide. Reessayez.\n");
            break;
        }
    } while (choix != 5);

    return 0;
}
