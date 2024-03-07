#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projet_proto.h"

#define MAX_TAILLE 100

// Structure pour stocker les informations de connexion
typedef struct {
    char email[MAX_TAILLE];
    char mdp[MAX_TAILLE];
    char role[MAX_TAILLE];
} CONNEXION;

// Fonction pour vérifier la connexion
int verifier_connexion(char *email, char *mot_de_passe, char *role) {
    FILE *fichier = fopen("test.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 0; // Échec de la connexion
    }

    CONNEXION c;
    while (fscanf(fichier, "%s %s %s", c.email, c.mdp, c.role) == 3) {
        if (strcmp(email, c.email) == 0 && strcmp(mot_de_passe, c.mdp) == 0) {
            if (strcmp(role, c.role) == 0 || strcmp(role, "admin") == 0) {
                fclose(fichier);
                return 1; // Connexion réussie
            }
        }
    }

    fclose(fichier);
    return 0; // Échec de la connexion
}

// Fonction pour saisir les informations de connexion
CONNEXION saisir_connexion(void) {
    CONNEXION c;
    printf("Entrer un email : ");
    fgets(c.email, sizeof(c.email), stdin);
    printf("Entrer un mot de passe : ");
    fgets(c.mdp, sizeof(c.mdp), stdin);
    c.email[strcspn(c.email, "\n")] = '\0'; // Supprimer le retour à la ligne
    c.mdp[strcspn(c.mdp, "\n")] = '\0'; // Supprimer le retour à la ligne
    return c;
}

void controlesaisiecon(CONNEXION c) {
    printf("%s %s %s\n", c.email, c.mdp, c.role);
}

int main() {
    CONNEXION c = saisir_connexion();
    if (verifier_connexion(c.email, c.mdp, "admin")) {
        printf("Connexion réussie en tant qu'administrateur.\n");
    } else if (verifier_connexion(c.email, c.mdp, "utilisateur")) {
        printf("Connexion réussie en tant qu'utilisateur.\n");
    } else {
        printf("Échec de la connexion. Veuillez vérifier vos informations d'identification.\n");
    }
    return 0;
}
