#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int nbComp = 0;
int nbPerm = 0;

typedef struct list {
    char mot[100];
    struct list* svt;
} list;


void inserer(list** L, char* new_mot) { 
    list* newNoeud = (list*)malloc(sizeof(list)); 
    strcpy(newNoeud->mot, new_mot); 
    newNoeud->svt = (*L); 
    (*L) = newNoeud;
}

void afficherListe(list* L) {
    while (L != NULL) {
        printf("%s ", L->mot);
        L = L->svt;
    }
    printf("\n");
}

void triParBulle(list* L)
{
    char swap[100];
    list* p;
    list* p2;
    if (L == NULL)
    {
        printf("la list est vide");
        return;
    }

    int verification = 1;
    while (verification)
    {
        p = L;
        nbComp++;
        verification = 0;
        while (p->svt != NULL)
        {
            p2 = p->svt;
            nbComp++;
            if (strcmp(p->mot, p2->mot) > 0)
            {
                verification = 1;
                strcpy(swap, p->mot);
                strcpy(p->mot, p2->mot);
                strcpy(p2->mot, swap);
                nbPerm++;
            }
            p = p->svt;
        }
    }
}

void triParInsertion(list* L)
{
    list* p = L;
    list* p2;
    char swap[100];
    while (p != NULL)
    {
        p2 = p;
        while (p2->svt != NULL)
        {
            nbComp++;
            if (strcmp(p->mot, p2->svt->mot) > 0)
            {
                strcpy(swap, p->mot);
                strcpy(p->mot, p2->svt->mot);
                strcpy(p2->svt->mot, swap);
                nbPerm++;
            }
            p2 = p2->svt;
        }
        p = p->svt;
    }
}

int main() {
    int d;
    struct list* liste = NULL;
    inserer(&liste, "pomme");
    inserer(&liste, "orange");
    inserer(&liste, "banane");
    inserer(&liste, "kiwi");
    inserer(&liste, "mangue");

    printf("Liste avant le tri :\n");
    afficherListe(liste);

    printf("LES MODE DE TRI :\n");
    printf("1. tri par bulle\n");
    printf("2. tri par Insertion\n");
    printf("Choisie un mode :");
    scanf("%d", &d);
    
switch (d) {
  case 1:
    triParBulle(liste);
    break;
  case 2:
    triParInsertion(liste);
    break;
  default:
    printf("error");
}
    

    printf("Liste apres le tri :\n");
    printf("\n");
    printf("le nombre de comparaison: %d\n ", nbComp);
    printf("le nombre de permutation: %d\n ", nbPerm);


    return 0;
}