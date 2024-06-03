#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NAME_LENGTH 100
#define MAX_PLAYERS 10

void genererOrdre(int ordre[], int nombre) {
    for (int i = 0; i < nombre; i++) {
        ordre[i] = i;
    }
    for (int i = nombre - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = ordre[i];
        ordre[i] = ordre[j];
        ordre[j] = temp;
    }
}

void reinitialiserPartie(int scores[], int ordre[], int nombre, int scoreDepart) {
    for (int i = 0; i < nombre; i++) {
        scores[i] = scoreDepart;
    }
    genererOrdre(ordre, nombre);
}

int main() {
    srand(time(NULL)); // Initialisation du générateur de nombres aléatoires

    printf("###        ##\n");
    printf(" ##\n");
    printf(" ##       ###      ####    #####    ##  ##    ####    #####    ##  ##    ####\n");
    printf(" #####     ##     ##  ##   ##  ##   ##  ##   ##  ##   ##  ##   ##  ##   ##  ##\n");
    printf(" ##  ##    ##     ######   ##  ##   ##  ##   ######   ##  ##   ##  ##   ######\n");
    printf(" ##  ##    ##     ##       ##  ##    ####    ##       ##  ##   ##  ##   ##\n");
    printf(" ######    ####     #####   ##  ##     ##      #####   ##  ##    ######   #####\n\n");
    printf("Lancer une partie (o/n)? ");
    char choix;
    scanf(" %c", &choix);
    if (choix == 'o') {
        int nombre;
        printf("Combien de joueurs? ");
        scanf("%d", &nombre);

        if (nombre > MAX_PLAYERS) {
            printf("Le nombre de joueurs est limité à %d.\n", MAX_PLAYERS);
            nombre = MAX_PLAYERS;
        }

        while (getchar()!= '\n');

        char noms[MAX_PLAYERS][MAX_NAME_LENGTH];

        for (int i = 0; i < nombre; i++) {
            printf("Nom du joueur %d : ", i + 1);
            fgets(noms[i], MAX_NAME_LENGTH, stdin);
            noms[i][strcspn(noms[i], "\n")] = '\0';
        }

        int objectif;
        printf("\nChoisissez l'objectif de la partie (301 ou 501) : ");
        while (1) {
            scanf("%d", &objectif);
            if (objectif == 301 || objectif == 501) {
                break;
            } else {
                printf("Erreur : l'objectif doit être soit 301 soit 501. Réessayez : ");
            }
            while (getchar()!= '\n');
        }

        int scores[MAX_PLAYERS];
        int ordre[MAX_PLAYERS];

        genererOrdre(ordre, nombre);

        for (int i = 0; i < nombre; i++) {
            scores[i] = objectif;
        }

        while (1) {
            system("cls");
            for (int i = 0; i < nombre; i++) {
                int joueur = ordre[i];
                printf("\nTour de %s (score : %d)\n", noms[joueur], scores[joueur]);
                for (int j = 0; j < 3; j++) {
                    int score;
                    printf("Score de la flechette %d : ", j + 1);
                    scanf("%d", &score);
                    scores[joueur] -= score;
                    if (scores[joueur] < 0) {
                        printf("OVER!\n");
                        scores[joueur] += score;
                        break;
                    } else if (scores[joueur] == 0) {
                        printf("%s a gagné!\n", noms[joueur]);
                        char rejouer;
                        printf("Voulez-vous rejouer (o/n)? ");
                        scanf(" %c", &rejouer);
                        if (rejouer == 'n') {
                            return 0;
                        } else {
                            reinitialiserPartie(scores, ordre, nombre, objectif);
                        }
                    }
                }
            }
        }
    }
    return 0;
}