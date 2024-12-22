#include <stdio.h>
#include <string.h>

void afficherMat(char mat[][20], int n){
    printf("Les elements du matrice sont :\n");
    for(int i = 0; i < n; i++){
        printf("%s \n", mat[i]);
    }

}

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

int main(){

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

    printf("le tri par bulle de la matrice dans lordre alphabetique des mots\n");
    triBulleMat(mat, N);

    printf("le tri rapide de la matrice dans lordre alphabetique des mots\n");
    triRapideMat(mat, 0, N-1);
    printf("le nombre de comparaison:%d\n ", nbcompMat);
    printf("le nombre de permutation:%d\n ", nbPermMat);

    return 0;
}
