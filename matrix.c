#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// fonction pour permute entre deux chaine de caracteres
void permuterChar(char **str1, char **str2) {
    char *temp = *str1;
    *str1 = *str2;
    *str2 = temp;
}

// fonction tri par Bulle d'une matrice
void triParBulles(char *T[], int taille) {
    for (int i = 0; i < taille - 1; i++) {
        for (int j = 0; j < taille - i - 1; j++) {
            if (strcmp(T[j], T[j + 1]) > 0) {
                permuterChar(&T[j], &T[j + 1]);
            }
        }
    }
}

// fonction qui fusionne deux sous-matrice 
void fusion(char *T[], int gauche, int milieu, int droite) {
    int i, j, k;
    int n1 = milieu - gauche + 1;
    int n2 = droite - milieu;

    char **G = (char **)malloc(n1 * sizeof(char *));
    char **D = (char **)malloc(n2 * sizeof(char *));


    for (i = 0; i < n1; i++)
        G[i] = T[gauche + i];
    for (j = 0; j < n2; j++)
        D[j] = T[milieu + 1 + j];

    i = 0; 
    j = 0;
    k = gauche;
    while (i < n1 && j < n2) {
        if (strcmp(G[i], D[j]) <= 0) {
            T[k] = G[i];
            i++;
        } else {
            T[k] = D[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        T[k] = G[i];
        i++;
        k++;
    }

    while (j < n2) {
        T[k] = D[j];
        j++;
        k++;
    }

    free(G);
    free(D);
}

// fonction recursive tri par fusion
void triFusionTemp(char *T[], int gauche, int droite) {
    if (gauche < droite) {
        int milieu = gauche + (droite - gauche) / 2;

        triFusionTemp(T, gauche, milieu);
        triFusionTemp(T, milieu + 1, droite);

        fusion(T, gauche, milieu, droite);
    }
}

// fonction tri par fusion d'une matrice
void triParFusion(char *T[], int Taille) {
    triFusionTemp(T, 0, Taille - 1);
}

int main() {
    char *T[] = {"pomme", "orange", "banane", "kiwi", "mangue"};
    int taille = sizeof(T) / sizeof(T[0]);
    int d;

    printf("T avant le tri :\n");
    for (int i = 0; i < taille; i++) {
        printf("%s\n", T[i]);
    }
    printf("\n"); printf("\n");

    printf("LES MODE DE TRI \n:");
    printf("1. tri par bulle\n");
    printf("2. tri par fusion\n");
    printf("Choisie un mode :");
    scanf("%d", &d);
    
    switch (d) {
  case 1:
    triParBulles(T,taille);
    break;
  case 2:
    triParFusion(T,taille);
    break;
  default:
    printf("error");
}  

    printf("T après le tri :\n");
    for (int i = 0; i < taille; i++) {
        printf("%s\n", T[i]);
    }

    return 0;
}
