#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define WINNING_SCORE 100

typedef struct {
    char name[50];
    int totalPoints;
} Player;

int diceRoll() {
    return rand() % 6 + 1;
}

int main() {
    Player Player1, Player2;
    char choice;

    srand(time(NULL));

    printf("Inserisci il nome del primo giocatore: ");
    scanf("%s", Player1.name);
    Player1.totalPoints = 0;

    printf("Inserisci il nome del secondo giocatore: ");
    scanf("%s", Player2.name);
    Player2.totalPoints = 0;

    do {
        printf("Vuoi tirare il dado? (s/n): ");
        scanf(" %c", &choice);

        if (choice == 's' || choice == 'S') {
            int roll1 = diceRoll();
            printf("%s ha tirato il dado ed e' uscito... %d\n", Player1.name, roll1);
            Player1.totalPoints += roll1;
            printf("Punti totali di %s: %d\n", Player1.name, Player1.totalPoints);

            int roll2 = diceRoll();
            printf("%s ha tirato il dado ed e' uscito... %d\n", Player2.name, roll2);
            Player2.totalPoints += roll2;
            printf("Punti totali di %s: %d\n", Player2.name, Player2.totalPoints);
        } else if (choice == 'n' || choice == 'N') {
            printf("Uffa :(\n");
        } else {
            printf("Devi scegliere tra s o n!\n");
        }

        printf("\n--------------------------\n\n");

    } while (Player1.totalPoints < WINNING_SCORE && Player2.totalPoints < WINNING_SCORE);

    if (Player1.totalPoints >= WINNING_SCORE) {
        printf("%s ha vinto con %d punti!\n", Player1.name, Player1.totalPoints);
    } else if (Player2.totalPoints >= WINNING_SCORE) {
        printf("%s ha vinto con %d punti!\n", Player2.name, Player2.totalPoints);
    }

    printf("Grazie per aver giocato!\n");
    printf("\nPremi INVIO per uscire...");
    getchar(); getchar();
    
    return 0;
}
