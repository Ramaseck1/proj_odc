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
        return 0;
    }

    int nb_etudiants = 0;
    while (fscanf(fichier, "%s %s %d", e[nb_etudiants].nom, e[nb_etudiants].prenom, &e[nb_etudiants].age) == 3) {
        nb_etudiants++;
    }

    fclose(fichier);
    return nb_etudiants;
} */

// marquer presence (admin)


void marquer_presence_admin(void) {
    printf("=== Marquer la présence d'un apprenant ===\n");

    char mot_de_passe[Max_taille];
    printf("Veuillez entrer le mot de passe de l'étudiant : ");
    fflush(stdout);
    mdp(mot_de_passe);

    // Récupérer la liste des apprenants depuis le fichier
    ETUDIANT etudiants[Max_taille];

    // Vérifier si le mot de passe correspond à celui d'un étudiant existant
    int index_etudiant = -1; //  initialisé à -1 pour indiquer aucune correspondance
   /*  for (int i = 0; i < nb_etudiants; i++) {
        if (strcmp(mot_de_passe, etudiants[i].mdp) == 0) {
            index_etudiant = i; // Enregistrer l'indice de l'étudiant correspondant au mot de passe
            break; 
        }
    } */

    // Vérifier si un étudiant correspondant au mot de passe a été trouvé
    if (index_etudiant == -1) {
        printf("Aucun étudiant trouvé avec ce mot de passe.\n");
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
    FILE *journal = fopen("marquer_presence.txt", "a");
    if (journal != NULL) {
        fprintf(journal, "%s %s - Présent à %s\n", etudiants[index_etudiant].prenom, etudiants[index_etudiant].nom, temps_format);
        fclose(journal);
    } else {
        printf("Erreur lors de l'ouverture du journal de présence.\n");
    }
}