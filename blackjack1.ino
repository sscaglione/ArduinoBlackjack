char myDeck[] = {'A','2','3','4','5','6','7','8','9','T','J','Q','K','A','2','3','4','5','6','7','8','9','T','J','Q','K','A','2','3','4','5','6','7','8','9','T','J','Q','K','A','2','3','4','5','6','7','8','9','T','J','Q','K'};
char myNewDeck[] = {'A','2','3','4','5','6','7','8','9','T','J','Q','K','A','2','3','4','5','6','7','8','9','T','J','Q','K','A','2','3','4','5','6','7','8','9','T','J','Q','K','A','2','3','4','5','6','7','8','9','T','J','Q','K'};
char dealerCards[8] = {NULL};
char dealerSuits[8] = {NULL};
char playerCards[8] = {NULL};
char playerSuits[8] = {NULL};
// set pin numbers:
const int hitButtonPin = 8;     // the number of the “hit” pushbutton pin
const int stayButtonPin = 9;     // the number of the “hit” pushbutton pin
int initialBalance=100;
int balance=initialBalance; //player balance
int bet=10; //bet value


void displayAllCards()
{
  for(int i=0; i<8; i++){
    Serial.print(dealerCards[i]);
    Serial.print(dealerSuits[i]);
  }
  Serial.println();
  for(int i=0; i<8; i++){
    Serial.print(playerCards[i]);
    Serial.print(playerSuits[i]);
  }
  Serial.println();
  Serial.println();
}

int deal(boolean whichPlayer, int cardNumber){
  int myRand;
  char mySuit; 
  int cardValue;
  
  do{
    myRand = random(52);
  } while(myDeck[myRand]=='\0');

  char myCard = myDeck[myRand];
  myDeck[myRand]='\0';

  if(myRand<13){
    mySuit='C';
  }
  else if(myRand<26){
    mySuit='D';
  }
   else if(myRand<39){
    mySuit='H';
  }
   else {
    mySuit='S';
  }

  switch(myCard){
    case 'A':
      cardValue=11;
      break;
    case '2':
      cardValue=2;
      break;
    case '3':
      cardValue=3;
      break;
    case '4':
      cardValue=4;
      break;
    case '5':
      cardValue=5;
      break;
    case '6':
      cardValue=6;
      break;
    case '7':
      cardValue=7;
      break;
    case '8':
      cardValue=8;
      break;
    case '9':
      cardValue=9;
      break;
    case 'T':
      cardValue=10;
      break;
    case 'J':
      cardValue=10;
      break;
    case 'Q':
      cardValue=10;
      break;
    case 'K':
      cardValue=10;
      break;
  }

  if(whichPlayer==false) //0 refers to the player
  {
    playerCards[cardNumber]=myCard;
    playerSuits[cardNumber]=mySuit;
  }
  else
  {
    dealerCards[cardNumber]=myCard;
    dealerSuits[cardNumber]=mySuit;
  }
return(cardValue);
}

void initialize(){
  for(int i=0; i<52; i++)
  {
    myDeck[i]=myNewDeck[i];
  }
  
  for(int i=0; i<8; i++){
    dealerCards[i] = NULL;
    dealerSuits[i] = NULL;
    playerCards[i] = NULL;
    playerSuits[i] = NULL;
  }
}


void setup() {
Serial.begin(9600);
randomSeed(analogRead(1));
pinMode(hitButtonPin, INPUT);
pinMode(stayButtonPin, INPUT);

int hitButtonState = LOW;         // variable for reading the pushbutton status
int stayButtonState = LOW;         // variable for reading the pushbutton status
int dealerCardNumber=0; //number of cards dealer has
int playerCardNumber=0;
int dealerTotal=0;      //value of cards in hand
int playerTotal=0;  
boolean hit=true;
boolean pressed=false;
Serial.print("Balance: ");
Serial.println(balance);
Serial.print("Bet: ");
Serial.println(bet);
delay(1000);

playerTotal=playerTotal + deal(0,playerCardNumber); //player first card
playerCardNumber++;
dealerTotal=dealerTotal + deal(1,dealerCardNumber); //dealer first card
dealerCardNumber++;
playerTotal=playerTotal + deal(0,playerCardNumber); //player second card
playerCardNumber++;
dealerTotal=dealerTotal + deal(1,dealerCardNumber); //dealer second card
dealerCardNumber++;

displayAllCards();

//if in the unlikely scenario either dealer or player gets two aces, adjust accordingly
if(playerTotal>21){
  playerTotal=playerTotal-10;
  playerCards[1]='a';
}
if(dealerTotal>21){
  dealerTotal=dealerTotal-10;
  dealerCards[1]='a';
}

if(playerTotal==21){
  if(dealerTotal==21){
    balance=balance;
    Serial.println("Push.");
  }
  else{
    balance=(1.5*bet)+balance;
    Serial.println("Blackjack!");
  }
}

//if the player doesn't have a blackjack
else{
  if(dealerTotal==21){
    balance=balance-bet;
    Serial.println("Dealer blackjack!");
  }
  else{
      while(hit){
          if(playerTotal>21){
            balance=balance-bet;
            Serial.println("Bust!");
            hit=false;
          }
          else{
            pressed=false;
            while(pressed==false){
              hitButtonState=LOW;
              stayButtonState=LOW;
              hitButtonState=digitalRead(hitButtonPin);
              stayButtonState=digitalRead(stayButtonPin);
              if(hitButtonState==HIGH){
                Serial.println("Read hit");
                pressed=true;
                hit=true;
              }
              else if(stayButtonState==HIGH){
                pressed=true;
                hit=false;
                Serial.println("Read stay");
              }
              else{
                pressed=false;
              }
            }
            if(hit){
              playerTotal=playerTotal + deal(0,playerCardNumber); //deal player a card
              playerCardNumber++;
              displayAllCards();
              Serial.println("Dealt player a card");
            }
          }
          /*
          boolean hasSoftAce=false;
          int softAcePosition;
          for(int q=0; q<8; q++){
            if(playerCards[q]='A'){
              hasSoftAce=true;
              softAcePosition=q;
            }
          }
          if(hasSoftAce=true && playerTotal>21){
            playerTotal=playerTotal-10;
            playerCards[softAcePosition]='a';
            displayAllCards();
          }
          */
          delay(4000);
      } 
      
      while(dealerTotal<17 && playerTotal<=21){
          dealerTotal=dealerTotal + deal(1,dealerCardNumber); //deal dealer a card
              dealerCardNumber++;
           /*   
         boolean hasSoftAce=false;
          int softAcePosition;
          for(int q=0; q<8; q++){
            if(dealerCards[q]='A'){
              hasSoftAce=true;
              softAcePosition=q;
            }
          }
          if(hasSoftAce=true && dealerTotal>21){
            dealerTotal=dealerTotal-10;
            dealerCards[softAcePosition]='a';
            displayAllCards();
          }
          else{
            displayAllCards();   
          }
          */
          displayAllCards();
          Serial.print("Dealt dealer a card");
       }

      if(playerTotal==dealerTotal){
        balance=balance;
        Serial.println("Push.");
      }
      else if(dealerTotal>21 && playerTotal<=21){
          balance=balance+bet;
          Serial.println("Dealer bust. Player win!");
        }
      else if(playerTotal>dealerTotal && playerTotal<=21){
        balance=balance+bet;
        Serial.println("Player wins!");
      }
      else if(playerTotal<dealerTotal && dealerTotal<=21){
        balance=balance-bet;
        Serial.println("Dealer wins.");
      }
        
      }
      
      
 }

if(balance<=0){
  Serial.println("You broke, son."); //player is out of money
  Serial.println("New game.");
  balance=initialBalance; //set the balance equal to the initial balance for a new game
}

initialize();
}

void loop(){
}



