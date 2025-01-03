#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//fonction echange pour un vecteur
void echangeVect(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

//fonction d'affichage des elements du vecteur
void afficherVect(int T[], int taille){
    printf("Les elements du tableau sont :\n");
    for (int j = 0; j < taille; j++) {
        printf("%d ", T[j]);
    }
    printf("\n");
}


//tri par selection
void triParSelectionVect (int T[], int Taille) {
    int i, j, min;
    int nbComp = 0;
    int nbPerm = 0;

    for (i = 0; i < Taille; i++) {
        min = i;
        for (j = i + 1; j < Taille; j++) {
            nbComp++;
            //trouver le plus petit element
            if (T[j] < T[min]) {
                min = j;
            }
        }
        //placer cet element dans la position correcte
        echangeVect(&T[min], &T[i]);
        nbPerm++;
        afficherVect(T, Taille);
    }
    //la complexite de la fonction triParSelection
    printf("le nombre de comparaison:%d\n ", nbComp);
    printf("le nombre de permutation:%d\n ", nbPerm);
}

//tri par bulle
void triParBulleVect (int T[], int Taille) {
    int i, j;
    int nbComp = 0;
    int nbPerm = 0;
    for (i = 0; i < Taille; i++) {
        for (j = 0; j < Taille-i-1; j++) {
            nbComp++;
            //comparision de 2 elements adjacents
            if (T[j] > T[j+1]) {
                echangeVect(&T[j], &T[j+1]);
                afficherVect(T, Taille);
                nbPerm++;
            }
        }

    }
    //la complexite de la fonction triParBulle
    printf("le nombre de comparaison:%d\n ", nbComp);
    printf("le nombre de permutation:%d\n ", nbPerm);
}

//tri par insertion
void triParInsertionVect (int T[], int Taille) {
    int i, j, temp;
    int nbComp = 0;
    int nbPerm = 0;
    //on commance par le 2eme element du tableau
    for (i = 1; i < Taille; i++) {
        temp = T[i];
        j = i - 1;
        nbComp++;
        //positioner l'element dans la position correcte
        while (j >= 0 && T[j] > temp) {
            //le decalage des element avant l'element T[i]
            T[j + 1] = T[j];
            nbPerm++;
            j = j - 1;
        }
        //positioner l'element temp dans sa position exact dans le tableau
        T[j + 1] = temp;
        nbPerm++;
        afficherVect(T, Taille);
    }
    printf("le nombre de comparaison:%d\n ", nbComp);
    printf("le nombre de permutation:%d\n ", nbPerm);
}


//tri rapide
//la complexite de la fonction triRapide
int nbCompTR = 0;
int nbPermTR = 0;

int partitionTR(int T[], int bas, int haut){
    //placer le dernier element comme pivot
    int pivot = T[haut];
    int i = (bas - 1);
    for (int j = bas; j < haut; j++){
        nbCompTR++;
        //placer les elements inferieur a l'element de pivot a gauche
        if(T[j] <= pivot){
            i++;
            echangeVect(&T[i], &T[j]);
            nbPermTR++;
        }
    }
    //placer le pivot dans sa position correcte
    echangeVect(&T[i+1], &T[haut]);
    nbPermTR++;
    return(i+1);
}

void triRapideVect (int T[], int bas, int haut){
    nbCompTR++;
    if(bas < haut){
        //premiere partition et definir le pivot
        int pivot = partitionTR(T, bas, haut);
        //tri rapide des elements inferieurs a l'element de pivot
        triRapideVect(T, bas, pivot - 1);
        //tri rapide des elements superieurs a l'element de pivot
        triRapideVect(T, pivot + 1, haut);
        afficherVect(T, haut + 1);
    }
}

//tri  par fusion
//la complexite de la fonction tri par fusion
int nbCompF = 0;
int nbPermF = 0;

void fusion(int T[], int gauche, int milieu, int droite) {
    int i, j, k;
    int n1 = milieu - gauche + 1;
    int n2 = droite - milieu;
    int G[n1], D[n2];
    for (i = 0; i < n1; i++){
        nbPermF++;
        G[i] = T[gauche + i];
    }
    for (j = 0; j < n2; j++){
        nbPermF++;
        D[j] = T[milieu + 1 + j];
    }
    i = 0;
    j = 0;
    k = gauche;
    nbCompF++;
    while (i < n1 && j < n2) {
        nbCompF++;
        if (G[i] <= D[j]) {
            nbPermF++;
            T[k] = G[i];
            i++;
        } else {
            nbPermF++;
            T[k] = D[j];
            j++;
        }
        k++;
    }
    nbCompF++;
    while (i < n1) {
        nbPermF++;
        T[k] = G[i];
        i++;
        k++;
    }
    nbCompF++;
    while (j < n2) {
        nbPermF++;
        T[k] = D[j];
        j++;
        k++;
    }
}

void triFusionTemp(int T[], int gauche, int droite) {
    nbCompF++;
    if (gauche < droite) {
        int milieu = gauche + (droite - gauche) / 2;
        triFusionTemp(T, gauche, milieu);
        triFusionTemp(T, milieu + 1, droite);
        afficherVect(T, droite+1);
        fusion(T, gauche, milieu, droite);
        afficherVect(T, droite+1);
    }
}

void triParFusionVect (int T[], int Taille) {
    triFusionTemp(T, 0, Taille - 1);
}



//tri peigne
//la complexite de la fonction triPeigne
int nbCompP = 0;
int nbPermP = 0;

int prochainEcart (int ecart) {
    ecart = (ecart * 10) / 13;
    nbCompP++;
    if (ecart < 1) {
        return 1;
    }
    return ecart;
}

void triPeigneVect (int T[], int taille) {
    int ecart = taille;
    int swapped = 1;
    nbCompP++;
    while (ecart != 1 || swapped) {
        ecart = prochainEcart(ecart);
        swapped = 0;
        afficherVect(T, taille);
        for (int i = 0; i < taille - ecart; i++) {
            nbCompP++;
            if (T[i] > T[i + ecart]) {
                nbPermP++;
                echangeVect(&T[i], &T[i + ecart]);
                swapped = 1;
            }
        }
    }
}


void triVect() {
    int choix;
    printf("1. Tri par selection  2. Tri par bulle  3. Tri par insertion  4. Tri rapide  5. Tri fusion  6. Tri peigne\n");
    printf("choisissez une methode de tri:");
    scanf("%d", &choix);

    printf("Entrez la taille du vecteur: ");
    int n;
    scanf("%d", &n);
    if (n <= 0) {
        printf("La taille du vecteur doit �tre positive.\n");
        return 1;
    }


    int T[n];
    printf("Entrez les elements du vecteur:\n");
    for (int i = 0; i < n; i++) {
        printf("Element %d: ", i + 1);
        scanf("%d", &T[i]);
    }

    switch (choix) {
        case 1:
            printf("le tri par selection de tableau\n");
            triParSelectionVect(T, n);
            break;
        case 2:
            printf("le tri par bulle de tableau\n");
            triParBulleVect(T, n);
            break;
        case 3:
            printf("le tri par insertion de tableau\n");
            triParInsertionVect(T, n);
            break;
        case 4:
            printf("le tri rapide de tableau\n");
            triRapideVect(T, 0, n - 1);
            printf("le nombre de comparaison:%d\n ", nbCompTR);
            printf("le nombre de permutation:%d\n ", nbPermTR);
            break;
        case 5:
            printf("le tri par fusion de tableau\n");
            triParFusionVect(T, n);
            printf("le nombre de comparaison:%d\n ", nbCompF);
            printf("le nombre de permutation:%d\n ", nbPermF);
            break;
        case 6:
            printf("le peige rapide de tableau\n");
            triPeigneVect(T, n);
            printf("le nombre de comparaison:%d\n ", nbCompP);
            printf("le nombre de permutation:%d\n ", nbPermP);
            break;
        default:
            printf("ERREUR\n");
    }

}


//la fonction d'affichage de la matrice
void afficherMat(char mat[][20], int n){
    printf("Les elements du matrice sont :\n");
    for(int i = 0; i < n; i++){
        printf("%s \n", mat[i]);
    }

}

//la fonction d'echange de la matrice
void echangeMat(char T1[20], char T2[20]){
    char temp[20];
    strcpy(temp, T1);
    strcpy(T1, T2);
    strcpy(T2, temp);


}

//tri par bulle de la matrice d'orde alphebitique
void triBulleMat(char mat[][20], int n){
    int nbComp = 0;
    int nbPerm = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            nbComp++;
            //comparrer les strings adjacents
            if (strcmp(mat[j], mat[j + 1]) > 0) {
                //l'echange des deaux lignes adjacentes
                nbPerm++;
                echangeMat(&mat[j], &mat[j+1]);
                afficherMat(mat, n);
            }
        }
    }
    //la complexite de la fonction triBulleMat
    printf("le nombre de comparaison:%d\n ", nbComp);
    printf("le nombre de permutation:%d\n ", nbPerm);

}

//tri rapide de la matrice d'ordre alphebitique
//la complexite de la fonction triRapideMat
int nbcompMat = 0;
int nbPermMat = 0;

int partitionTRMat(char mat[][20], int bas, int haut){
    //placer le dernier element comme pivot
    char pivot[20];
    strcpy(pivot, mat[haut]);
    int i = bas - 1;
    for (int j = bas; j < haut; j++) {
        nbcompMat++;
        //placer les elements inferieur a l'element de pivot a gauche
        if (strcmp(mat[j], pivot) < 0) {
            i++;
            echangeMat(mat[i], mat[j]);
            nbPermMat++;
        }
    }
    //placer le pivot dans sa position correcte
    echangeMat(mat[i + 1], mat[haut]);
    nbPermMat++;
    return i + 1;

}

void triRapideMat(char mat[][20], int bas, int haut) {
    nbcompMat++;
    if (bas < haut) {
        //premiere partition et definir le pivot
        int pivot = partitionTRMat(mat, bas, haut);
        //tri rapide des elements inferieurs a l'element de pivot
        triRapideMat(mat, bas, pivot - 1);
        //tri rapide des elements superieurs a l'element de pivot
        triRapideMat(mat, pivot + 1, haut);
        afficherMat(mat, haut + 1);
    }
}


void triMat(){
    int choix;
    printf("1. Tri par bulle  2. Tri rapide\n");
    printf("choisissez une methode de tri:");
    scanf("%d", &choix);

    int N;
    char mat[100][20];
    printf("Enterer le nombre des mots que vous allez inserer:");
    scanf("%d", &N);
    getchar();
    for (int i = 0; i < N; i++) {
        printf("Enterer le mot %d:", i + 1);
        fgets(mat[i], 20, stdin);
        mat[i][strcspn(mat[i], "\n")] = '\0';
    }


    switch (choix) {
        case 1:
            printf("le tri par bulle de la matrice dans lordre alphabetique des mots\n");
            triBulleMat(mat, N);
            break;
        case 2:
            printf("le tri rapide de la matrice dans lordre alphabetique des mots\n");
            triRapideMat(mat, 0, N-1);
            printf("le nombre de comparaison:%d\n ", nbcompMat);
            printf("le nombre de permutation:%d\n ", nbPermMat);
            break;
        default:
            printf("ERREUR\n");
    }

}


typedef struct list{
    char mot[20];
    struct list* svt;
}list;

struct liste* creerListe(char info[]){
    struct list* nouvListe = (list*)malloc(sizeof(list));
    strcpy(nouvListe->mot, info);
    nouvListe->svt = NULL;
    return nouvListe;
};


void triliste(){
    int choix,n;
    printf("1. Tri par bulle  2. Tri rapide\n");
    printf("choisissez une methode de tri:");
    scanf("%d", &choix);
    printf("Enterer le nombre des mots que vous allez inserer:");
    scanf("%d", &n);

    struct list *L = NULL;
    char info[20];
    struct list *p;

    //creer la liste
    for(int i = 0; i < n; i++){
         printf("Entrez le mot %d: ", i+1);
         scanf("%s", info);
         struct list* nouv = creerListe(info);
         //le premier element de la liste
         if(L == NULL){
            L = nouv;
         } else {
            p = L;
            while(p->svt != NULL){
                p = p->svt;
            }
            p->svt = nouv;
         }
    }


    switch (choix) {
        case 1:
            printf("le tri par bulle de la liste dans lordre alphabetique des mots\n");
            triBullelist(L);
            break;
        case 2:
            printf("le tri par insertion de la liste dans lordre alphabetique des mots\n");
            triInsertionlist(L);
            break;
        default:
            printf("ERREUR\n");
    }


}




void afficherListe(list* L){
    list* p = L;
    printf("Les elements du liste sont :\n");
    while(p != NULL){
        printf("%s\n", p->mot);
        p = p->svt;
    }

}

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
                    afficherListe(L);
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
        afficherListe(L);
    }
    //la complexite de la fonction triInsertionlist
    printf("le nombre de comparaison:%d\n", nbComp);
    printf("le nombre de permutation:%d\n", nbPerm);
}


int main() {
    int choix;
    printf("1. Tri d'un vecteur   2. Tri d'une matrice  3. Tri d'une liste chainee\n");
    printf("Choisissez un tri: ");
    scanf("%d", &choix);

    switch (choix) {
        case 1:
            triVect();
            break;
        case 2:
            triMat();
            break;
        case 3:
            triliste();
            break;
        default:
            printf("ERREUR\n");
    }

    return 0;

}
