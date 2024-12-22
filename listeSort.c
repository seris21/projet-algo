#include <stdio.h>
#include <stdlib.h>

typedef struct list{
    char mot[20];
    struct list* svt;
}list;

void afficher(list* L){
    list* temp = L;
    printf("Les elements du liste sont :\n");
    while(temp != NULL){
        printf("%s\n", temp->mot);
        temp = temp->svt;
    }

}

struct liste* creerListe(char info[]){
    list* newListe = (list*)malloc(sizeof(list));
    strcpy(newListe->mot, info);
    newListe->svt = NULL;
    return newListe;
};

//tri par bulle
void triBullelist(list* L){
    char swap[100];
    list* p;
    list* p2;
    //le cas de la liste vide
    if (L == NULL){
        printf("la list est vide");
        return;
    }else{

        int nbComp = 0;
        int nbPerm = 0;
        int verification = 1;
        while (verification){
            p = L;
            verification = 0;
            nbComp++;
            while (p->svt != NULL){
                p2 = p->svt;
                nbComp++;
                //comparision de 2 elements adjacents
                if (strcmp(p->mot, p2->mot) > 0){
                    verification = 1;
                    //echanger les 2 elements
                    strcpy(swap, p->mot);
                    strcpy(p->mot, p2->mot);
                    nbPerm++;
                    strcpy(p2->mot, swap);
                    afficher(L);
                }
                p = p->svt;
            }
        }
        //la complexite de la fonction triBullelist
        printf("le nombre de comparaison:%d\n ", nbComp);
        printf("le nombre de permutation:%d\n ", nbPerm);
    }
}


// tri par insertion
void triInsertionlist(list* L){
    list* p = L;
    list* p2;
    char swap[100];

    int nbComp = 0;
    int nbPerm = 0;
    while (p != NULL){
        //on commance par le 2eme element du tableau
        p2 = p;
        while (p2->svt != NULL){
            nbComp++;
            if (strcmp(p->mot, p2->svt->mot) > 0){
                //le decalage des element avant l'element p2
                strcpy(swap, p->mot);
                strcpy(p->mot, p2->svt->mot);
                strcpy(p2->svt->mot, swap);
                nbPerm++;
            }
            p2 = p2->svt;
        }
        p = p->svt;
        afficher(L);
    }
    //la complexite de la fonction triInsertionlist
    printf("le nombre de comparaison:%d\n", nbComp);
    printf("le nombre de permutation:%d\n", nbPerm);
}


int main(){
    struct list* L = creerListe("hello");
    struct list* L1 = creerListe("alger");
    struct list* L2 = creerListe("paris");
    L->svt = L1;
    L1->svt = L2;
    printf("le tri par bulle de la liste dans lordre alphabetique des mots\n");
    triBullelist(L);

    printf("le tri par insertion de la liste dans lordre alphabetique des mots\n");
    triInsertionlist(L);

return 0;
}
