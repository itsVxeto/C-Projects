#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int secretNumber = rand() % 100 + 1;
    int difference = 0;
    int guess = 0;
    int attempts = 0;

    printf("------------------------------\n");
    printf(" Benvenuto a Indovina il Numero!\n");
    printf("------------------------------\n");

    printf("Sei stato sfidato a indovinare un numero casuale da 1 a 100. \n");
    printf("Il tuo scopo e' indovinare il numero nel minor numero di tentativi possibili.\n");
    printf("Se fai 5 errori per te e' GAME OVER!\n");
    printf("Eccoti una piccola legenda:\n\n");

    printf("Se il numero segreto e' sotto/sopra di 25, rispondero' con 'Freddo'\n");
    printf("Se il numero segreto e' sotto/sopra di 10, rispondero' con 'Caldo'\n");
    printf("Se il numero segreto e' sotto/sopra di 5, rispondero' con 'Brucia'\n");
    printf("Se sei ancora piu' vicino, ti diro' 'Molto vicino!'\n\n");

    printf("Iniziamo! E buona fortuna!\n\n");

    while (attempts < 5 && guess != secretNumber) {
        printf("Inserisci il tuo %d tentativo: ", attempts + 1);
        scanf("%d", &guess);

        if (guess < 1 || guess > 100) {
            printf("Per favore, inserisci un numero valido!\n");
            continue;
        }

        if (guess < secretNumber) {
            difference = secretNumber - guess;
            if (difference >= 25)
                printf("Freddo! Il numero segreto e' piu' alto.\n");
            else if (difference >= 10)
                printf("Caldo! Il numero segreto e' piu' alto.\n");
            else if (difference >= 5)
                printf("Brucia! Il numero segreto e' piu' alto.\n");
            else
                printf("Molto vicino! Dai che ci sei! E' piu' alto\n");
        } else if (guess > secretNumber) {
            difference = guess - secretNumber;
            if (difference >= 25)
                printf("Freddo! Il numero segreto e' piu' basso.\n");
            else if (difference >= 10)
                printf("Caldo! Il numero segreto e' piu' basso.\n");
            else if (difference >= 5)
                printf("Brucia! Il numero segreto e' piu' basso.\n");
            else
                printf("Molto vicino! Dai che ci sei! E' piu' basso\n");
        } else {
            printf("Congratulazioni! Hai indovinato il numero segreto %d in %d tentativi!\n",
                   secretNumber, attempts + 1);
            break;
        }

        attempts++;
        printf("\n");
    }

    if (attempts == 5 && guess != secretNumber) {
        printf("GAME OVER! Hai esaurito i tuoi tentativi. Il numero segreto era %d.\n", secretNumber);
    }

    printf("Grazie per aver giocato!\n");
    printf("\nPremi INVIO per uscire...");
    getchar(); getchar();

    return 0;
}
