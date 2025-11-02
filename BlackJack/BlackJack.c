#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct {
    char name[50];
    int totalPoints;
    int aceCount; // numero di assi contati come 11
} Player;

typedef struct {
    int totalPoints;
    int aceCount;
} Dealer;

// Creazione del mazzo
void initDeck(int deck[]){
    int index = 0;
    for(int suit = 0; suit < 4; suit++){
        for(int value = 1; value <= 13; value++){ // carte 1-13
            deck[index++] = value;
        }
    }
}

// Mischiare il mazzo
void shuffleDeck(int deck[]){
    for(int i = 51; i > 0; i--){
        int j = rand() % (i+1);
        int temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

// Pescare una carta dal mazzo
int drawCard(int deck[], int *topCard){
    int card = deck[*topCard];
    (*topCard)++;
    return card;
}

// Valore della carta
int cardValue(int card){
    if(card >= 2 && card <= 10) return card;
    if(card >= 11 && card <= 13) return 10;
    return 11; // Asso
}

// Stampa carta
void printCard(int card){
    switch(card){
        case 1: printf("A"); break;
        case 11: printf("J"); break;
        case 12: printf("Q"); break;
        case 13: printf("K"); break;
        default: printf("%d", card);
    }
}

// Aggiunge carta al giocatore
void addCardToPlayer(Player *p, int card){
    int value = cardValue(card);
    p->totalPoints += value;
    if(card == 1) p->aceCount++;

    while(p->totalPoints > 21 && p->aceCount > 0){
        p->totalPoints -= 10;
        p->aceCount--;
    }

    printf("Hai pescato: ");
    printCard(card);
    printf("\nTotale punti: %d\n", p->totalPoints);
}

// Aggiunge carta al dealer
void addCardToDealer(Dealer *d, int card){
    int value = cardValue(card);
    d->totalPoints += value;
    if(card == 1) d->aceCount++;

    while(d->totalPoints > 21 && d->aceCount > 0){
        d->totalPoints -= 10;
        d->aceCount--;
    }
}

// Controllo blackjack
bool checkBlackJack(Player p, Dealer d){
    if(p.totalPoints == 21 && d.totalPoints == 21){
        printf("Parita', entrambi hanno il BlackJack!\n");
        return true;
    } else if(p.totalPoints == 21){
        printf("BlackJack! Hai vinto!\n");
        return true;
    } else if(d.totalPoints == 21){
        printf("Il Dealer ha BlackJack! Hai perso!\n");
        return true;
    }
    return false;
}

int main(){
    srand(time(NULL));
    while (1){
    
        Player p;
        Dealer d;
        p.totalPoints = 0; p.aceCount = 0;
        d.totalPoints = 0; d.aceCount = 0;
    
        int deck[52];
        int topCard = 0;
    
        initDeck(deck);
        shuffleDeck(deck);
    
        printf("-----------------------------------\n");
        printf("         REGOLE DEL BLACKJACK        \n");
        printf("-----------------------------------\n");
        printf("Obiettivo: piu' vicino a 21 senza superarlo.\n");
        printf("Hit = pescare, Stand = fermarsi.\n");
        printf("-----------------------------------\n\n");
    
        printf("Inserisci il tuo nome: ");
        scanf("%s", p.name);
    
        printf("\nInizio gioco!\n\n");
    
        // Carte iniziali
        int card1 = drawCard(deck, &topCard);
        int card2 = drawCard(deck, &topCard);
        addCardToPlayer(&p, card1);
        addCardToPlayer(&p, card2);
    
        int dealerCard1 = drawCard(deck, &topCard);
        int dealerCard2 = drawCard(deck, &topCard);
        addCardToDealer(&d, dealerCard1);
        addCardToDealer(&d, dealerCard2);
    
        if(checkBlackJack(p, d)){
            return 0; // termina subito il gioco se c'è blackjack
        }
    
    
        printf("\nIl dealer mostra solo la prima carta: ");
        printCard(dealerCard1);
        printf("\n\n");
    
        // Turno del giocatore
        char choice;
        while((p.totalPoints < 21)){
            printf("Vuoi pescare un'altra carta? (H = Hit / S = Stand): ");
            scanf(" %c", &choice);
    
            if (isblank(choice)) {
                continue;
            }
    
            if (!isalnum(choice)){
                printf("Inserisci un carattere valido.\n");
                continue;
            }
    
            char c = tolower(choice);
    
            if(c == 'h'){
                int newCard = drawCard(deck, &topCard);
                addCardToPlayer(&p, newCard);
                if(p.totalPoints > 21){
                    printf("Hai superato 21! Bust!\n");
                    break;
                }
            } else if(c == 's'){
                printf("Ti fermi a %d punti.\n", p.totalPoints);
                break;
            } else{
                printf("Inserisci H o S!\n");
            }
    
        }
    
        // Turno dealer
        printf("\nTurno del dealer...\n");
        printf("Dealer rivela la seconda carta: ");
        printCard(dealerCard2);
        printf("\n");
    
        while(d.totalPoints < 17){
            int newCard = drawCard(deck, &topCard);
            addCardToDealer(&d, newCard);
            printf("Dealer pesca: ");
            printCard(newCard);
            printf(" (Totale: %d)\n", d.totalPoints);
        }
    
        // Risultati finali
        printf("\n--- Risultato finale ---\n");
        printf("%s: %d punti\n", p.name, p.totalPoints);
        printf("Dealer: %d punti\n", d.totalPoints);
    
        if (p.totalPoints > 21) {
            printf("Hai perso!\n");
        } else if (d.totalPoints > 21) {
            printf("Hai vinto!\n");
        } else if (p.totalPoints > d.totalPoints) {
            printf("Hai vinto!\n");
        } else if (p.totalPoints < d.totalPoints) {
            printf("Hai perso!\n");
        } else {
            printf("Parità! Vince il dealer.\n");
        }
    
    
        printf("\nGrazie per aver giocato!\n");
        printf("----------------------\n\n");
        printf("Vuoi giocare ancora? (Y/N): ");
    
        char playAgain;
    
        scanf(" %c", &playAgain);
        if(tolower(playAgain) != 'y') break;
    
    }
    printf("Premi INVIO per uscire...");
    getchar(); getchar();
    
    return 0;
}
