#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // bibliothèque pour travailler avec le temps
#include <termios.h> // marquer mot de passe
#include <unistd.h> // bibliothèque pour STDIN_FILENO

#include "projet_proto.h"

#define Max_taille 100 
// return 0 Échec de la connexion 
// return 1 // Connexion réussie

// masquer mot de pass


void mdp(char *mot_de_passe) {
    struct termios argin, argout;
    char c;
    char *x = mot_de_passe;

    tcgetattr(0, &argin);
    argout = argin;
    argout.c_lflag &= ~(ICANON | ECHO);
    argout.c_iflag &= ~(ICRNL);
    argout.c_oflag &= ~(OPOST);
    argout.c_cc[VMIN] = 1;
    argout.c_cc[VTIME] = 0;
    tcsetattr(0, TCSADRAIN, &argout);

    do {
        if (read(0, &c, 1) != 1)
            continue;
        if (c == 0x0d)
            break;
        if ((c == 0x08) || (c == 0x7f)) { // backspace
            putchar(8);
            putchar(' ');
            putchar(8);
            x--;
        } else {
            *x++ = c;
            putchar('*');
        }
        fflush(stdout);
    } while (x - mot_de_passe < Max_taille - 1);
    *x = '\0';
    tcsetattr(0, TCSADRAIN, &argin);
}

int verifier_connexion(char *email, char *mot_de_passe, char *role, char *nomfichier) {
    FILE *fichier = fopen(nomfichier, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s.\n", nomfichier);
        return 0; // Échec de la connexion
    }

    CONNEXION c;
    while (fscanf(fichier, "%s %s %s", c.email, c.mdp, c.role) == 3) {
        if (strcmp(email, c.email) == 0 && strcmp(mot_de_passe, c.mdp) == 0 && strcmp(role, c.role) == 0) {
            fclose(fichier);
            return 1; // Connexion réussie
        }
    }

    fclose(fichier);
    return 0; // Échec de la connexion
}
CONNEXION saisir_connexion(void) {
    CONNEXION c;
    printf("Entrer un email : ");
    scanf("%s", c.email);
    puts("Mot de passe:");
    fflush(stdout);
    mdp(c.mdp);
    printf("\n");
    return c;
}// marquer presence

/* // liste de la classe 
int recuperer_classes(Classe *classes) {
    FILE *fichier = fopen("test.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 0;
    }

    int nb_classes = 0;
    char ligne[Max_taille];

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        char *token = strtok(ligne, " ");
        while (token != NULL) {
            strcpy(classes[nb_classes].nom, token);
            nb_classes++;
            token = strtok(NULL, " ");
        }
    }

    fclose(fichier);
    return nb_classes;
}

// liste etudiant

int recuperer_liste_etudiants(ETUDIANT *e,char *nomfichier) {
    FILE *fichier = fopen("test.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s.\n", "test.txt");
    "éa"    return 0;
    }

    int nb_etudiants = 0;
    while (fscanf(fichier, "%s %s %d", e[nb_etudiants].nom, e[nb_etudiants].prenom, &e[nb_etudiants].age) == 3) {
        nb_etudiants++;
    }

    fclose(fichier);
    return nb_etudiants;
} */

// marquer presence (admin)
 
/* void marquer_presence_admin(int code) {
    printf("=== Marquer la présence d'un apprenant ===\n");
    

    // Récupérer la liste des apprenants depuis le fichier
    ETUDIANT etudiants[Max_taille];
    int nb_etudiants = recuperer_liste_etudiants(etudiants, "test.txt");

    // Vérifier si le code correspond à celui d'un étudiant existant
    int index_etudiant = -1; // Initialisé à -1 pour indiquer aucune correspondance
    for (int i = 0; i < nb_etudiants; i++) {
        if (code == etudiants[i].code) {
            index_etudiant = i; // Enregistrer l'indice de l'étudiant correspondant au code
            break; 
        }
    } 

     //Vérifier si un étudiant correspondant au code a été trouvé
    if (index_etudiant == -1) {
        printf("Aucun étudiant trouvé avec ce code.\n");
        return;
    }

    // Afficher le nom et le prénom de l'étudiant correspondant
    printf("Vous avez sélectionné : %s %s\n", etudiants[index_etudiant].prenom, etudiants[index_etudiant].nom);

    // Obtenir le temps actuel
    time_t temps_actuel = time(NULL);
    struct tm *temps_struct = localtime(&temps_actuel);
    char temps_format[100];
    strftime(temps_format, sizeof(temps_format), "%d/%m/%Y %H:%M:%S", temps_struct);

    // Afficher le temps où l'étudiant a été marqué présent
    printf("L'étudiant a été marqué présent à : %s\n", temps_format);

    // Marquer la présence de l'étudiant avec le temps actuel
    FILE *journal = fopen("test.txt", "a");
    if (journal != NULL) {
        fprintf(journal, "%s %s - Présent à %s\n", etudiants[index_etudiant].prenom, etudiants[index_etudiant].nom, temps_format);
        fclose(journal);
    } else {
        printf("Erreur lors de l'ouverture du journal de présence.\n");
    }
} 
 */

void marquer_presence(char *code_etudiant, char *nomfichier) {
    FILE *fichier = fopen(nomfichier, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s.\n", nomfichier);
        return;
    }

    char nom[Max_taille];
    char code[Max_taille];
    char name[Max_taille];
    int apprenant_present = 0; 

    // Vérifie si l'étudiant est déjà présent dans la liste
    while (fscanf(fichier, "%s %s %s", name, nom, code) == 3) {
        if (strcmp(code, code_etudiant) == 0) {
            fclose(fichier);
            time_t rawtime;
            struct tm *timeinfo;
            time(&rawtime);
            timeinfo = localtime(&rawtime);
            printf("%s %s est présent à %s", name, nom, asctime(timeinfo));

            // Vérifie si l'étudiant est déjà présent dans la liste de présences
            FILE *fichier_presence = fopen("liste_presences.txt", "r");
            if (fichier_presence == NULL) {
                printf("Erreur lors de l'ouverture du fichier liste_presences.txt.\n");
                return;
            }

            char existing_code[Max_taille];
            while (fscanf(fichier_presence, "%s", existing_code) != EOF) {
                if (strcmp(existing_code, code_etudiant) == 0) {
                    printf("%s %s est déjà présent dans la liste de présences.\n", name, nom);
                    apprenant_present = 1;
                    break;
                }
            }

            fclose(fichier_presence);

            // Si l'étudiant n'est pas déjà présent, l'ajoute à la liste des présences
            if (!apprenant_present) {
                FILE *fichier_presence_ajout = fopen("liste_presences.txt", "a");
                if (fichier_presence_ajout == NULL) {
                    printf("Erreur lors de l'ouverture du fichier liste_presences.txt pour ajout.\n");
                    return;
                }
                fprintf(fichier_presence_ajout, "%s %s est présent à %s", name, nom, asctime(timeinfo));
                fclose(fichier_presence_ajout);
            }

            return;
        }
    }

    fclose(fichier);
    printf("Code de l'étudiant invalide.\n");
}


void afficher_liste_presences() {
    FILE *fichier = fopen("liste_presences.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier des présences.\n");
        return;
    }

    printf("Liste des présences :\n");
    char ligne[Max_taille];
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        printf("%s", ligne);
    }

    fclose(fichier);
}