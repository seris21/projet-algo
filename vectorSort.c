#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void echange(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

void affichage(int T[], int taille){
    printf("Les elements du tableau sont :\n");
    for (int j = 0; j < taille; j++) {
        printf("%d ", T[j]);
    }
    printf("\n");
}

//tri par selection
void triParSelection (int T[], int Taille) {
    int i, j, min;
    int nbComp = 0;
    int nbPerm = 0;
    for (i = 0; i < Taille; i++) {
        min = i;
        for (j = i + 1; j < Taille; j++) {
            nbComp++;
            if (T[j] < T[min]) {
                min = j;
            }
        }
        echange(&T[min], &T[i]);
        nbPerm++;
        affichage(T, Taille);
    }
    printf("le nombre de comparaison:%d\n ", nbComp);
    printf("le nombre de permutation:%d\n ", nbPerm);
}

//tri par bulle
void triParBulle (int T[], int Taille) {
    int i, j;
    int nbComp = 0;
    int nbPerm = 0;
    for (i = 0; i < Taille; i++) {
        for (j = 0; j < Taille-i-1; j++) {
            nbComp++;
            if (T[j] > T[j+1]) {
                echange(&T[j], &T[j+1]);
                nbPerm++;
            }
        }affichage(T, Taille);
    }
    printf("le nombre de comparaison:%d\n ", nbComp);
    printf("le nombre de permutation:%d\n ", nbPerm);
}

//tri par insertion
void triParInsertion (int T[], int Taille) {
    int i, j, temp;
    int nbComp = 0;
    int nbPerm = 0;
    for (i = 1; i < Taille; i++) {
        temp = T[i];
        j = i - 1;
        nbComp++;
        while (j >= 0 && T[j] > temp) {
            T[j + 1] = T[j];
            nbPerm++;
            j = j - 1;
        }
        T[j + 1] = temp;
        nbPerm++;
        affichage(T, Taille);
    }
    printf("le nombre de comparaison:%d\n ", nbComp);
    printf("le nombre de permutation:%d\n ", nbPerm);
}


//tri rapide
int nbCompTR = 0;
int nbPermTR = 0;

int partitionTR(int T[], int bas, int haut){
    int pivot = T[haut];
    int i = (bas - 1);
    for (int j = bas; j < haut; j++){
        nbCompTR++;
        if(T[j] <= pivot){
            i++;
            echange(&T[i], &T[j]);
            nbPermTR++;
        }
    }
    echange(&T[i+1], &T[haut]);
    nbPermTR++;
    return(i+1);
}

void triRapide(int T[], int bas, int haut){
    nbCompTR++;
    if(bas < haut){
        int pivot = partitionTR(T, bas, haut);
        triRapide(T, bas, pivot - 1);
        triRapide(T, pivot + 1, haut);
        affichage(T, haut + 1);
    }
}

//tri  par fusion
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
        affichage(T, droite+1);
        fusion(T, gauche, milieu, droite);
        affichage(T, droite+1);

    }
}

void triParFusion(int T[], int Taille) {

    triFusionTemp(T, 0, Taille - 1);
}



//tri peigne
int nbCompP = 0;
int nbPermP = 0;

int prochainEcart(int ecart) {
    ecart = (ecart * 10) / 13;
    nbCompP++;
    if (ecart < 1) {
        return 1;
    }
    return ecart;
}

void triPeigne(int T[], int taille) {
    int ecart = taille;
    int swapped = 1;
    nbCompP++;
    while (ecart != 1 || swapped) {
        ecart = prochainEcart(ecart);
        swapped = 0;
        affichage(T, taille);
        for (int i = 0; i < taille - ecart; i++) {
            nbCompP++;
            if (T[i] > T[i + ecart]) {
                nbPermP++;
                echange(&T[i], &T[i + ecart]);
                swapped = 1;
            }
        }
    }
}


int main(){
    printf("Entrez la taille du tableau : ");
    int n;
    scanf("%d", &n);
    if (n <= 0) {
        printf("La taille du tableau doit être positive.\n");
        return 1;
    }


    int T[n];
    printf("Entrez les elements du tableau :\n");
    for (int i = 0; i < n; i++) {
        printf("Element %d : ", i + 1);
        scanf("%d", &T[i]);
    }
    printf("le tri rapide de tableau\n");
    triRapide(T, 0, n - 1);
    printf("le nombre de comparaison:%d\n ", nbCompTR);
    printf("le nombre de permutation:%d\n ", nbPermTR);

    printf("le tri par selection de tableau\n");
    triParSelection(T, n);

    printf("le par bulle de tableau\n");
    triParBulle(T, n);

    printf("le tri par insertion de tableau\n");
    triParInsertion(T, n);

    printf("le tri par fusion de tableau\n");
    triParFusion(T, n);
    printf("le nombre de comparaison:%d\n ", nbCompF);
    printf("le nombre de permutation:%d\n ", nbPermF);

    printf("le peige rapide de tableau\n");
    triPeigne(T, n);
    printf("le nombre de comparaison:%d\n ", nbCompP);
    printf("le nombre de permutation:%d\n ", nbPermP);


    return 0;
}




