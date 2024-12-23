#include <stdio.h>
#include <string.h>

int nbComp = 0;
int nbPerm = 0;

// fonction pour permute entre deux elment d'un vecteur
void permuter(int *a, int *b) {
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
    nbPerm++;
}  

// fonction tri par selection d'un vecteur
void triParSelection (int T[], int Taille) {
    int i, j, min;

    for (i = 0; i < Taille; i++) {
        min = i;
        for (j = i + 1; j < Taille; j++) {
            nbComp++;
            if (T[j] < T[min]) { min = j;}                        
        }
    permuter(&T[min], &T[i]);   
    }   
}

// fonction tri par Bulle d'un vecteur
void triParBulle (int T[], int Taille) {
    int i, j;

    for (i = 0; i < Taille; i++) {
        
        for (j = 0; j < Taille-i-1; j++) {
            nbComp++;
            if (T[j] > T[j+1]) {
                permuter(T[j], T[j+1]);   
            }    
        }
    }           
}

// fonction tri par insertion d'un vecteur
void triParInsertion (int T[], int Taille) {
    int i, j, temp;

    for (i = 1; i < Taille; i++) { 
        temp = T[i];
        j = i - 1;
        while (j >= 0 && T[j] > temp) { 
            nbComp++;
            T[j + 1] = T[j]; 
            j = j - 1;
            nbPerm++;
        }
        T[j + 1] = temp;
    }
}

// fonction qui fusionne deux sous-vecteur 
void fusion(int T[], int gauche, int milieu, int droite) {
    int i, j, k;
    int n1 = milieu - gauche + 1;
    int n2 = droite - milieu;

   
    int G[n1], D[n2];

    
    for (i = 0; i < n1; i++)
        G[i] = T[gauche + i];
    for (j = 0; j < n2; j++)
        D[j] = T[milieu + 1 + j];

    
    i = 0; 
    j = 0; 
    k = gauche; 
    while (i < n1 && j < n2) {
        nbComp++;
        if (G[i] <= D[j]) {
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
}

// fonction recursive tri par fusion
void triFusionTemp(int T[], int gauche, int droite) {
    if (gauche < droite) {
        int milieu = gauche + (droite - gauche) / 2;

        triFusionTemp(T, gauche, milieu);
        triFusionTemp(T, milieu + 1, droite);

        fusion(T, gauche, milieu, droite);
    }
}

// fonction tri par fusion d'un vecteur
void triParFusion(int T[], int Taille) {
    triFusionTemp(T, 0, Taille - 1);
}

// fonction qui permet d'avoir le prochaine écart le plus optimisé entre deux element du vecteur
int prochainEcart(int ecart) {
    ecart = (ecart * 10) / 13;
    if (ecart < 1) {
        return 1;
    }
    return ecart;
}

// fonction tri par peigne d'un vecteur
void triPeigne(int T[], int Taille) {
    int ecart = Taille; 
    int swapped = 1;
    
    while (ecart != 1 || swapped) {
        ecart = prochainEcart(ecart); 
        swapped = 0;

        
        for (int i = 0; i < Taille - ecart; i++) {
            nbComp++;
            if (T[i] > T[i + ecart]) {
                permuter(&T[i], &T[i + ecart]);                
                swapped = 1;
            }
        }
    }
}


int main() {
    int n, d;
    printf("Entre La Taille Du Tableau :");
    scanf("%d",&n);
    int Tab[n];
    for (int i=0; i<n; i++) {
        printf("Entre T[%d] :", i);
        scanf("%d",&Tab[i]);
    }
    
    printf("\n"); printf("\n");


    printf("Tableau avant le tri :\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", Tab[i]);
    }
    printf("\n"); printf("\n");

    printf("LES MODE DE TRI \n:");
    printf("1. tri par selection \n");
    printf("2. tri par Bulle \n");
    printf("3. tri par insertion \n");
    printf("4. tri par rapide \n");
    printf("5. tri par fusion \n");
    printf("6. tri par peigne \n");
    printf("\n");
    printf("Choisie un mode :");
    scanf("%d",&d);

    switch (d) {
  case 1:
    triParSelection(Tab, n);
    break;
  case 2:
    triParBulle(Tab, n);
    break;
  case 3:
    triParInsertion(Tab, n);
    break;
  case 4:
    triParBulle(Tab, n);
    break;  
  case 5:
    triParFusion(Tab, n);
    break;
  case 6:
    triPeigne(Tab, n);
    break;
  
  
  default:
    printf("error");
}


    printf("Tableau apres le tri :\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", Tab[i]);
    }
    printf("\n");
    printf("\n");


    printf("Nombre de comparaisons : %d\n", nbComp);
    printf("Nombre de permutations : %d\n", nbPerm);

    return 0;
}
