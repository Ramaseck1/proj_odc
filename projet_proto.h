#ifndef FONTION_H_INCLUDED
#define FONTION_H_INCLUDED
#define Max_taille 100

typedef struct 
{
   
    char email[Max_taille];
    char mdp[Max_taille];
    char role[Max_taille];

    
}CONNEXION;
typedef struct {
    char nom[Max_taille];
} Classe;

typedef struct {
    char nom[Max_taille];
    char prenom[Max_taille];
    char mdp[Max_taille];
    int age;
    int present; // Champ de présence
} ETUDIANT;



//connexion admin
CONNEXION saisir_connexion(void) ;
int verifier_connexion(char *email, char *mot_de_passe, char *role,   char *nomfichier) ;








#endif