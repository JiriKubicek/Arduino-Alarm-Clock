#include <LiquidCrystal.h>
#include <Keypad.h>

#define D4 A4
#define D5 A5
#define D6 8
#define D7 9
#define E 10
#define RS 11

// - - - - - KEYBOARD BLOCK - - - - - //
	
const byte numRows = 4;			//number of rows on the keypad
const byte numCols = 4;			//number of collumns on the keypad

char keys[numRows][numCols] =   //array which copies positions of keys
{								//and defines function of different keys
  {'1', '2', '3', 'A' },
  {'4', '5', '6', 'B' },
  {'7', '8', '9', 'C' },
  {'*', '0', '#', 'D' }
};

byte rowPins[numRows] = {A0, A1, 7, 6};	
byte colPins[numCols] = {5, 4, 3, 2};

Keypad keyPad = Keypad( makeKeymap(keys), rowPins, colPins, numRows, numCols); 


// - - - - - KEYBOARD BLOCK - - - - - //

// - - - - LCD DISPLAY BLOCK - - - - //
LiquidCrystal LCD(RS, E, D4, D5, D6, D7);   
  
// - - - - LCD DISPLAY BLOCK - - - - //

void setup()
{
  LCD.begin(16,2);
  pinMode(13, OUTPUT);
  Serial.begin();
}

void loop()
{
  /*
  digitalWrite(13, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(13, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
  */
  
}