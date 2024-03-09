#include <stdio.h>
#include <stdlib.h>
#include "projet1.c"

int main() {
  
  int choix_menu;
  int connexion_reussie = 0;
  
  do
  {
    
 

  CONNEXION c = saisir_connexion();
                    if (verifier_connexion(c.email, c.mdp, "admin", "test.txt")) {
                        printf("Connexion réussie en tant qu'administrateur.\n");
                    connexion_reussie = 1;
                        while (1) {
                        printf("\nMenu :\n");
                        printf("1. Marquer presence\n");
                        printf("2. liste des presences \n");
                        printf("3. Deconnection\n");
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
                        printf("veullez saisir un email et un mot de passe \n");
                        CONNEXION c = saisir_connexion();
                        if (verifier_connexion(c.email, c.mdp, "admin", "test.txt")) {
                        printf("Connexion réussie en tant qu'administrateur.\n");
                        }
                        return 0;
                        break;
                        default:
                        printf("Choix invalide. Veuillez entrer un nombre entre 1 et 2.\n");
                        break;
                     }
                   
                    }
                    } 
                else if (verifier_connexion(c.email, c.mdp, "utilisateur", "test.txt")) {
                            printf("Connexion réussie en tant qu'utilisateur.\n");
                        connexion_reussie = 1; 
                        connexion_reussie = 1;
                        while (1) {
                        printf("\nMenu :\n");
                        printf("1. Marquer presence\n");
                        printf("3. Deconnection\n");
                        printf("Entrez votre choix : ");
                        scanf("%d", &choix_menu);
                        switch (choix_menu)
                        {
                        case 1:
                         // Marquer présence
                    printf("Saisir le code de l'étudiant : ");
                    char code_etudiant[Max_taille];
                    scanf("%s", code_etudiant);
                    marquer_presence(code_etudiant, "user.txt");   
                    break;

                            break;
                        case 2:

                        break;
                        
                        default:
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