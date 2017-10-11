//********************************
//  Filename: arduinoblackjackproject.ino
//Students: Braeden Benedict,Braeden.C.Benedict.8@nd.edu
//          Brooks Meadowcroft,Brooks.S.Meadowcroft.1@nd.edu
//          Samantha Scaglione,sscaglio@nd.edu
//Final Project: Arduino Blackjack
//
//Description: This is the file for the
// Arduino Blackjack final project.
//*********************************
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int dealerCardNumber=0; //number of cards dealer has
int playerCardNumber=0; //number of cards player has
char myDeck[] = {'A','2','3','4','5','6','7','8','9','T','J','Q','K','A','2','3','4','5','6','7','8','9','T','J','Q','K','A','2','3','4','5','6','7','8','9','T','J','Q','K','A','2','3','4','5','6','7','8','9','T','J','Q','K'};
char myNewDeck[] = {'A','2','3','4','5','6','7','8','9','T','J','Q','K','A','2','3','4','5','6','7','8','9','T','J','Q','K','A','2','3','4','5','6','7','8','9','T','J','Q','K','A','2','3','4','5','6','7','8','9','T','J','Q','K'};
char dealerCards[8] = {NULL}; //the array to keep track of the dealer's cards 
char dealerSuits[8] = {NULL}; //the array to keep track of the suits of the dealer's cards
char playerCards[8] = {NULL}; //the array to keep track of the player's cards
char playerSuits[8] = {NULL}; //the array to keep track of the suits of the player's cards
// set pin numbers:
const int hitButtonPin = 8;     // the number of the “hit” pushbutton pin
const int stayButtonPin = 9;     // the number of the “hit” pushbutton pin
int initialBalance=100; // the starting balance
int balance=initialBalance; //player balance
int bet; //bet value
int potpin = 0;  // analog pin used to connect the potentiometer
int potVal;    // variable to read the value from the analog pin
// set up the customized LCD characters
byte hearts[8] = {
  B00000,
  B01010,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000,
};
byte diamonds[8] = {
  B00000,
  B00100,
  B01110,
  B11111,
  B01110,
  B00100,
  B00000,
};

byte spades[8] = {
  B00100,
  B01010,
  B10001,
  B10101,
  B01010,
  B00100,
  B01110,
};
byte clubs[8] = {
  B01110,
  B01010,
  B10001,
  B11011,
  B00100,
  B01110,
  B00000,
  B00000,
}; 



void displayAllCards()
{
  lcd.clear();
  for(int i=0; i<dealerCardNumber; i++){
    lcd.print(dealerCards[i]);
    writeSuits(dealerSuits[i]);

  }
  lcd.setCursor(0,1); // sets where to type on the LCD
  for(int i=0; i<playerCardNumber; i++){
    lcd.print(playerCards[i]);
    writeSuits(playerSuits[i]);
 
  }
}
//****************************
// *Name: displayAllCards()
// *Purpose: this function will display all cards
// *Input: this function does not take an input
// *Return: this function will prompt a display
//          on the LCD screen
//**************************** 

void displayCards()
{
  lcd.clear();
  lcd.print("XX");
  for(int i=1; i<dealerCardNumber; i++){
    lcd.print(dealerCards[i]);
     
    writeSuits(dealerSuits[i]);
  
  }
  lcd.setCursor(0,1);
  for(int i=0; i<playerCardNumber; i++){
    lcd.print(playerCards[i]);
     
    writeSuits(playerSuits[i]);
  
  }
}

//****************************
// *Name: displayCards()
// *Purpose: this function will display all
//           the player's cards and one of the
//           dealer's cards
// *Input: this function does not take an input
// *Return: this function will prompt a display
//          on the LCD screen
//**************************** 

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
//****************************
// *Name: int deal(boolean whichPlayer, int cardNumber)
// *Purpose: this function deals cards based on a
//           randomly generated card number that
//           points somewhere in the deck of cards
//           array and gives it to the designated player
// *Input: whichPlayer, a boolean variable that determines
//         which player is dealt to; cardNumber, an int
//         that points somewhere in the deck array
// *Return: this function will return the
//          value of the relevant card
//**************************** 

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
//****************************
// *Name: initialize()
// *Purpose: this function will clear the player's
//           and the dealer's hands
// *Input: this function does not take an input
// *Return: this function will clear the arrays
//          describing the hands of the dealer
//          and the player
//**************************** 
void writeSuits(char suit){
  switch(suit){
   
    case 'H':
    lcd.write(byte(4));
    break;
     case 'D':
    lcd.write(byte(1));
    break;
    case 'S':
    lcd.write(byte(2));
    break;
    case 'C':
    lcd.write(byte(3));
    break;
  }
}
//****************************
// *Name: int writeSuits(char suit)
// *Purpose: this function will write the suits
//           to the LCD screen
// *Input: char suit, a character indicating
//         which custom character to display
// *Return: this function will prompt a display
//          on the LCD screen
//**************************** 
void setup() {
Serial.begin(9600);
randomSeed(analogRead(1));
pinMode(hitButtonPin, INPUT);
pinMode(stayButtonPin, INPUT);
lcd.begin(16, 2);  
  lcd.createChar(4, hearts);
  lcd.createChar(1, diamonds);
  lcd.createChar(2, spades);
  lcd.createChar(3, clubs);

}
void loop(){
 dealerCardNumber=0; //number of cards dealer has
 playerCardNumber=0;
int dealerTotal=0;      //value of cards in hand
int playerTotal=0;
char userInput;
char gameStartInput;  
boolean hit=true;
boolean pressed=false;
boolean gameStart=false;


 while(gameStart==false){
             gameStartInput = Serial.read();
             if ((char)gameStartInput == ' '){
              gameStart= true;
             }else{
                potVal = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
                bet = map(potVal, 0, 1023, balance, 1);     // scale it to use it with the betting (value between 0 and balance
               lcd.clear();
            
                lcd.print("Balance: ");
                lcd.print(balance);
                lcd.setCursor(0,1);
                lcd.print("Bet: ");
                lcd.print(bet);
                delay(300);
                   }
             }
 
playerTotal=playerTotal + deal(0,playerCardNumber); //player first card
playerCardNumber++;
dealerTotal=dealerTotal + deal(1,dealerCardNumber); //dealer first card
dealerCardNumber++;
playerTotal=playerTotal + deal(0,playerCardNumber); //player second card
playerCardNumber++;
dealerTotal=dealerTotal + deal(1,dealerCardNumber); //dealer second card
dealerCardNumber++;

displayCards();

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
    delay(1000);
    lcd.clear();
    lcd.print("Push.");
  }
  else{
    balance=(1.5*bet)+balance;
    delay(1000);
    lcd.clear();
    lcd.print("Blackjack!");
  }
}

//if the player doesn't have a blackjack
else{
  if(dealerTotal==21){
    balance=balance-bet;
    delay(1000);
    lcd.clear();
    lcd.print("Dealer blackjack!");
  }
  else{
      while(hit){
          if(playerTotal>21){
            balance=balance-bet;
            delay(1000);
            lcd.clear();
            lcd.print("Bust!");
            hit=false;
          }
          else{
            pressed=false;
            while(pressed==false){
              delay(100);
             userInput = Serial.read();
              if((char)userInput=='h'){
                pressed=true;
                hit=true;
              }
              else if((char)userInput=='s'){
                pressed=true;
                hit=false;
              }
              else{
                pressed=false;
              }
            }
            if(hit){
              playerTotal=playerTotal + deal(0,playerCardNumber); //deal player a card
              playerCardNumber++;
            }
          
          
          boolean hasSoftAce=false;
          int softAcePosition;
          for(int q=0; q<8; q++){
            if(playerCards[q]=='A'){
              hasSoftAce=true;
              softAcePosition=q;
            }
          }
          if(hasSoftAce==true && playerTotal>21){
            playerTotal=playerTotal-10;
            playerCards[softAcePosition]='a';
            displayCards();
          }
          else{
            displayCards();
          }
          }
      } 
     if (playerTotal<=21){
      displayAllCards();
     }
      delay(1000);
      while(dealerTotal<17 && playerTotal<=21){
          dealerTotal=dealerTotal + deal(1,dealerCardNumber); //deal dealer a card
              dealerCardNumber++;
           
         boolean hasSoftAce=false;
          int softAcePosition;
          for(int q=0; q<8; q++){
            if(dealerCards[q]=='A'){
              hasSoftAce=true;
              softAcePosition=q;
            }
          }
          if(hasSoftAce==true && dealerTotal>21){
            dealerTotal=dealerTotal-10;
            dealerCards[softAcePosition]='a';
            displayAllCards();
          }
          else{
            displayAllCards(); 
            delay(1000);  
          }
          
       }

      if(playerTotal==dealerTotal){
        balance=balance;
        delay(1000);
        lcd.clear();
        lcd.print("Push.");
      }
      else if(dealerTotal>21 && playerTotal<=21){
          balance=balance+bet;
          delay(1000);
          lcd.clear();
          lcd.print("Dealer bust.");
          lcd.setCursor(0,1);
          lcd.print("Player wins!");
        }
      else if(playerTotal>dealerTotal && playerTotal<=21){
        balance=balance+bet;
        delay(1000);
        lcd.clear();
        lcd.print("Player wins!");
      }
      else if(playerTotal<dealerTotal && dealerTotal<=21){
        balance=balance-bet;
        delay(1000);
        lcd.clear();
        lcd.print("Dealer wins.");
      }
        
      }
      
      
 }
delay(2000);
if(balance<=0){
  lcd.clear();
  lcd.print("Out of Money"); //player is out of money
  lcd.setCursor(0,1);
  lcd.print("New game.");
  balance=initialBalance; //set the balance equal to the initial balance for a new game
  delay(2000);
}

initialize();
}





