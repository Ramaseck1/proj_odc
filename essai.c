#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // bibliothèque pour travailler avec le temps
#include <termios.h> // marquer mot de passe
#include <unistd.h> // bibliothèque pour STDIN_FILENO

#define Max_taille 100

typedef struct {
    char email[Max_taille];
    char mdp[Max_taille];
    char role[Max_taille];
} CONNEXION;

typedef struct {
    char nom[Max_taille];
} Classe;

typedef struct {
    char nom[Max_taille];
    char prenom[Max_taille];
    
    int code;
    int age;
    int present; // Champ de présence
} ETUDIANT;

// Fonction pour saisir le mot de passe en masquant l'entrée
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

// Fonction pour vérifier la connexion
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

// Fonction pour saisir la connexion
CONNEXION saisir_connexion(void) {
    CONNEXION c;
    printf("Entrer un email : ");
    scanf("%s", c.email);
    puts("Mot de passe :");
    fflush(stdout);
    mdp(c.mdp);
    printf("\n");
    return c;
}

// Fonction pour marquer la présence de l'étudiant
void marquer_presence() {
    
    
    // Récupérer la liste des apprenants depuis le fichier
    ETUDIANT etudiants[Max_taille];
    int nb_etudiants;
    // Implémentez la fonction recuperer_liste_etudiants pour récupérer la liste des étudiants depuis le fichier
         int code;
    printf("Saisir le code de l'apprenant : ");
    scanf("%d", &etudiants.code);
    // Vérifier si le code correspond à celui d'un étudiant existant
    int index_etudiant = -1; // Initialisé à -1 pour indiquer aucune correspondance
    for (int i = 0; i < nb_etudiants; i++) {
        if (code == etudiants[i].code) {
            index_etudiant = i; // Enregistrer l'indice de l'étudiant correspondant au code
            break; 
        }
    } 

    // Vérifier si un étudiant correspondant au code a été trouvé
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
    FILE *journal = fopen("user.txt", "r");
    if (journal != NULL) {
        fprintf(journal, "%s %s %d- Présent à %s\n", etudiants[index_etudiant].prenom, etudiants[index_etudiant].nom, temps_format,etudiants->code);
        fclose(journal);
    } else {
        printf("Erreur lors de l'ouverture du journal de présence.\n");
    }
}

// Fonction pour afficher la liste des présences
void afficher_liste_presences() {
    printf("=== Liste des présences ===\n");
    
    // Lire le fichier journal_presence.txt et afficher son contenu
    FILE *journal = fopen("user.txt", "r");
    if (journal != NULL) {
        char ligne[Max_taille];
        while (fgets(ligne, sizeof(ligne), journal) != NULL) {
            printf("%s", ligne);
        }
        fclose(journal);
    } else {
        printf("Aucune présence enregistrée.\n");
   }
}

int main() {
    int choix_menu;
    int connexion_reussie = 0;
    
    do {
        CONNEXION c = saisir_connexion();
        
        if (verifier_connexion(c.email, c.mdp, "admin", "test.txt")) {
            printf("Connexion réussie en tant qu'administrateur.\n");
            connexion_reussie = 1;

            while (1) {
                printf("\nMenu :\n");
                printf("1. Marquer présence\n");
                printf("2. Liste des présences \n");
                printf("3. Déconnexion\n");
                printf("Entrez votre choix : ");
                scanf("%d", &choix_menu);

                switch (choix_menu) {   
                    case 1:
                        // Appeler la fonction pour marquer la présence
                        marquer_presence();
                        break;
                    case 2:
                        // Appeler la fonction pour afficher la liste des présences
                        afficher_liste_presences();
                        break;
                    case 3:
                        printf("Déconnexion.\n");
                        return 0;
                    default:
                        printf("Choix invalide. Veuillez entrer un nombre entre 1 et 3.\n");
                        break;
                }
            }
        } else if (verifier_connexion(c.email, c.mdp, "utilisateur", "test.txt")) {
            printf("Connexion réussie en tant qu'utilisateur.\n");
            connexion_reussie = 1;
            // Ajoutez votre code pour un utilisateur normal ici
        } else {
            printf("Échec de la connexion. Veuillez saisir un login et un mot de passe valide.\n");
        }
    } while (!connexion_reussie);
    
    return 0;
}
