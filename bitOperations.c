#include<stdio.h>
#include<stdlib.h>
#include<time.h>

/* handy typedefs */
typedef unsigned char card;  
typedef unsigned char pairs;  

/* arrays for the names of things */
static char *suits[] = {"Hearts","Diamonds","Clubs","Spades"};
static char *values[]= {"Ace","Two","Three","Four","Five","Six",\
					    "Seven","Eight","Nine","Ten","Jack",\
					    "Queen","King"};
static char *colour[]= {"Black","Red"};

/* function prototypes */
void printcard(card c); /* Displays the value of a card*/

void printdeck(card deck[52]); /* prints an entire deck of cards*/

void filldeck(card deck[52]); /* Populates a deck of cards */

void shuffle(card deck[52]); /* Randomizes the order of cards */

int compareface(const void* c1,const void *c2);
/* compares the face value of 2 cards, suitable to pass to qsort
 as the fourth argument */

pairs findpairs(card *hand); /* finds any pairs in a hand */

int main()
{
    card deck[52],*deckp;
    card hands[5][5],handssorted[5][5];
    pairs numpairs[5],highest;
    int hand,cd,winner;
    
    srand(time(NULL));       /* seed the random number generator */
    
    /*populate and shuffle the deck */
    
    filldeck(deck);
    printdeck(deck);
    shuffle(deck);
    printdeck(deck);
    
    int deckIndex = 0;
    
    for(cd=0;cd<5;cd++)
    {
        for(hand=0;hand<5;hand++)
        {
            /* dealing the hands */
            
            hands[hand][cd] = deck[deckIndex];
            
            /* Copying the hand to handssorted array */
            
            handssorted[hand][cd] = deck[deckIndex];
            
            deckIndex++; 
        }
    }
      
    /* Print the hands before sorting to 
    check if sorting dose not make changes to the hand's cards values

    for ( int h = 0; h< 5; h++){
        
        printf("Hand %i:==== \n", h+1);
        card c1 = hands[h][0];
        card c2 = hands[h][1];
        card c3 = hands[h][2];
        card c4 = hands[h][3];
        card c5 = hands[h][4];
        
        printcard(c1);
        printcard(c2);
        printcard(c3);
        printcard(c4);
        printcard(c5);       
    } */
    
    char handsHighestPair[] = {-1, -1, -1, -1, -1};

    printf("\n");
    
    for(hand=0;hand<5;hand++)
    {   
        /* sorting the hands */
        
        card swapCard = 0x0;
        
        for ( int k = 0; k < 5; k++){
               
            for ( int j = 0; j < 4-k; j++){
                
                char firstCardValue = (((handssorted[hand][j])&0x1e)>>1);
                
                char secondCardValue = (((handssorted[hand][j+1])&0x1e)>>1);
                
                if ( firstCardValue > secondCardValue ){
                    
                    swapCard = handssorted[hand][j];
                    
                    handssorted[hand][j] = handssorted[hand][j+1];
                    
                    handssorted[hand][j+1] = swapCard;
                }
            }
        }
        
        numpairs[hand]=findpairs(handssorted[hand]);
        
        /* printing the hands */
        
        printf("Hand %i: \n", hand+1);
        card c1 = handssorted[hand][0];
        card c2 = handssorted[hand][1];
        card c3 = handssorted[hand][2];
        card c4 = handssorted[hand][3];
        card c5 = handssorted[hand][4];
        
        printcard(c1);
        printcard(c2);
        printcard(c3);
        printcard(c4);
        printcard(c5);

        /* Geting number of pairs in a hand from numpair */
        pairs numberOfPairs = (numpairs[hand]&0x0f);
        
        /* Getting the highest pair value of a hand */
        pairs highestPairValue = ((numpairs)[hand]>>4);

        printf("number of pairs is %i \n", numberOfPairs );


        if (numberOfPairs > 0){

            printf("Highest pair is: %s \n", values[highestPairValue]);
        }

        printf("\n");
        
        if (numberOfPairs > 0){
            handsHighestPair[hand] = highestPairValue;
        }
    }

    /* determining the winner and printing it */

    char winnerHand = -1;
    char winnerPair = -1;

    for(  int t = 0; t < 5; t++ ){

        if (handsHighestPair[t] > -1){
            if (handsHighestPair[t] > winnerPair){
                winnerPair = handsHighestPair[t];
                winnerHand = t+1;
            }
            else if (handsHighestPair[t] == winnerPair){
                winnerPair = -1;
                winnerHand = -1;
            }
        }
    }

    

    if (winnerHand != -1){

        printf("Winner is hand %i with a pair of %s\n", winnerHand, values[winnerPair]);
    }
    else{
        printf("Drawn game\n");
    }
    
    return 0;
}

pairs findpairs(card *hand)
{
    pairs numpairs=0;
    
    int highestPair = 0;

    int count = 0;
    
    /* finding the pairs */

    for ( int p = 0; p < 4; p++ ){

        char firstCardValueToCompare = (((hand[p])&0x1e)>>1);
                
        char secondCardValueToCompare = (((hand[p+1])&0x1e)>>1);

        if (firstCardValueToCompare == secondCardValueToCompare){
                
                highestPair = firstCardValueToCompare;
            
            count++;
            
            p++;
        }

    }

    numpairs = (highestPair<<4|count);

    return numpairs;    
}

void filldeck(card deck[52])
{
    /* populating the deck */
    
    int counter = 0;
    
    char colourOfCard = 0x1;
    char valueOfCard = 0x0;
    char suit = 0x0;
    
    for (int suitsCounter = 0; suitsCounter < 4; suitsCounter++){
        
        if (suitsCounter == 1){
            
            colourOfCard = 0x1;
            suit = 0x1;
        }
        
        if (suitsCounter == 2){
            colourOfCard = 0x0;
            suit = 0x2;
        }
        
        if (suitsCounter == 3){
            colourOfCard = 0x0;
            suit = 0x3;
        }
        
        valueOfCard = 0x0;
        
        for (int numberOfCards = 0; numberOfCards < 13; numberOfCards++){
            
            deck[counter] = (colourOfCard|(suit<<5)|(valueOfCard<<1));
            
            valueOfCard++;
            
            counter++;
            
        }
    }
    
    return;
}

void printdeck(card deck[52])
{
    int i;

    printf("\n");
    for(i=0;i<52;i++)
        printcard(deck[i]);
    return;
}

void printcard(card c)
{
    /* printing the value of the card */
    
    char cardValue = ((c)&0x1e)>>1;
    
    char cardColour = ((c&0x1));
    
    
    printf("%s of %s, is %s \n", values[cardValue], suits[(c>>5)], colour[cardColour] );
    
    return;
}

void shuffle(card deck[52])
{
    
    int i,rnd;
    card c;
    
    for(i=0;i<52;i++)
    {
        /* generating a random number between 0 & 51 */
        rnd=rand() * 52.0 / RAND_MAX; 
        
        /* finishing shuffling the deck */
        
        card tempCard = deck[i];
        deck[i] = deck[rnd];
        deck[rnd] = tempCard;
    }
    
    return;
}


int compareface(const void* c1, const void *c2)
{
    /* This function extracts the two cards face values
     and returns 1 if cd1 > cd2, 0 if cd1 == cd2, and
     -1 otherwise. The weird argument types are for
     compatibility with qsort(), the first two lines
     decode the arguments back into "card".
     */
    card cd1,cd2;
    
    cd1=*((card*) c1);
    cd2=*((card*) c2);
    
    cd1= (cd1&0x1e)>>1;
    cd2= (cd2&0x1e)>>1;
    
    if(cd1>cd2)
        return 1;
    if(cd1==cd2)
        return 0;
    
    return -1;
}
