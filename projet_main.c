#include <stdio.h>
#include <stdlib.h>
#include "projet1.c"

int main() {
  
    int choix_menu;
    int connexion_reussie = 0;
    CONNEXION c;

    do {
        c = saisir_connexion(); // Demander les informations de connexion

        if (verifier_connexion(c.email, c.mdp, "admin", "test.txt")) {
            printf("Connexion réussie en tant qu'administrateur.\n");
            connexion_reussie = 1;

            while (connexion_reussie) {
                printf("\nMenu :\n");
                printf("1. Marquer présence\n");
                printf("2. Liste des présences\n");
                printf("3. Générer fichiers\n");
                printf("4. Déconnexion\n");
                printf("Entrez votre choix : ");
                scanf("%d", &choix_menu);

                switch (choix_menu) {   
                    case 1: 
                        // Marquer présence
                        printf("Saisir le code de l'étudiant : ");
                        char code_etudiant[Max_taille];
                        scanf("%s", code_etudiant);
                        marquer_presence(code_etudiant, "user.txt");   
                        break;
                    case 2:
                        afficher_liste_presences();
                        break;
                    case 3:
                        // Sous-options de génération de fichiers
                        printf("1. Générer tous les fichiers\n");
                        printf("2. Générer par dates\n");
                        printf("Entrez votre choix : ");
                        int sous_choix;
                        scanf("%d", &sous_choix);
                        switch (sous_choix) {
                            case 1:
                            case 2:
                                generer_fichier_toutes_dates();// Appel de la fonction pour générer par dates
                                break;
                            default:
                                printf("Choix invalide. Veuillez entrer un nombre entre 1 et 2.\n");
                                break;
                        }      
                        break;
                    case 4:
                        // Déconnexion
                        connexion_reussie = 0;
                        break;
                    default:
                        printf("Choix invalide. Veuillez entrer un nombre entre 1 et 4.\n");
                        break;
                }
            }
        } 
        else if (verifier_connexion(c.email, c.mdp, "utilisateur", "test.txt")) {
            printf("Connexion réussie en tant qu'utilisateur.\n");
            connexion_reussie = 1;

            while (connexion_reussie) {
                printf("\nMenu :\n");
                printf("1. Marquer présence\n");
                printf("2. Mes messages\n");
                printf("3. Déconnexion\n");
                printf("Entrez votre choix : ");
                scanf("%d", &choix_menu);
                switch (choix_menu) {
                    case 1:
                        // Marquer présence
                        printf("Saisir le code de l'étudiant : ");
                        char code_etudiant[Max_taille];
                        scanf("%s", code_etudiant);
                        marquer_presence(code_etudiant, "user.txt");   
                        break;
                    case 2:
                        // message
                        break;
                    case 3:
                        // Déconnexion
                        connexion_reussie = 0;
                        break;
                    default:
                        printf("Choix invalide. Veuillez entrer un nombre entre 1 et 3.\n");
                        break;
                }
            } 
        }
        else {
            printf("Échec de la connexion. Veuillez saisir un login et un mot de passe valide.\n");
        }
    } while (!connexion_reussie);
             
    return 0;
}
