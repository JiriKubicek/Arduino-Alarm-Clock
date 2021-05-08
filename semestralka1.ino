#include <LiquidCrystal.h>
#include <Keypad.h>

// - - - CONSTANTS and IMPORTANT VALUES BLOCK - - - //

#define D4 A4
#define D5 A5
#define D6 8
#define D7 9
#define E 10
#define RS 11

const int buzzer = 12;

enum states {
 SET_TIME, SET_DAY, MENU_NEW, MENU_DEL  
};
enum states STATE, NEXT_STATE;

enum week
{
  MON, TUE, WED, THU, FRI, SAT, SUN
};

int h = 0;
int m = 0;
int s = 0;
int d = 0;

// - - - CONSTANTS and IMPORTANT VALUES BLOCK - - - //

// - - - - - KEYBOARD BLOCK - - - - - //
	
const byte numRows = 4;			//number of rows on the keypad
const byte numCols = 4;			//number of collumns on the keypad

char keys[numRows][numCols] =   //array which copies positions of keys
{								//and defines function of different keys
  {'1', '2', '3', 'A' },		// 1 - 9 are numbers
  {'4', '5', '6', 'B' },		//
  {'7', '8', '9', 'C' },
  {'*', '0', '#', 'D' }
};

byte rowPins[numRows] = {A0, A1, 7, 6};	
byte colPins[numCols] = {5, 4, 3, 2};

Keypad keyPad = Keypad( makeKeymap(keys), rowPins, colPins, numRows, numCols); 

// - - - - - KEYBOARD BLOCK - - - - - // 

// - - - - LCD DISPLAY BLOCK - - - - //
LiquidCrystal LCD(RS, E, D4, D5, D6, D7);  

void displayMenu( )
{
  LCD.setCursor(0, 0);
  LCD.print("TIME ");
  printTime();
  
  LCD.setCursor(0, 1);
  LCD.print("DAY: ");
  printDay();
}

// - - - - LCD DISPLAY BLOCK - - - - //

printTime()
{
  
}


printDay()
{
  switch(d)
  {
  	case 0:
    	LCD.print("MONDAY   ");
    	break;
    case 1:
    	LCD.print("TUESDAY  ");
    	break;
    case 2:
    	LCD.print("WEDNESDAY");
    	break;
    case 3:
    	LCD.print("THURSDAY ");
    	break;
    case 4:
    	LCD.print("FRIDAY   ");
    	break;
    case 5:
    	LCD.print("SATURDAY ");
    	break;
    case 6:
    	LCD.print("SUNDAY   ");
    	break;
}


////////////////////////////////////////////////////////////////
void setup()
{
  LCD.begin(16,2);
  pinMode(12, OUTPUT);		//buzzer setup
  Serial.begin(9600);
}

void loop()
{
  
  
  /*
  char keyPressed = keyPad.getKey();
  if( keyPressed != NO_KEY )
  {
    Serial.println(keyPressed);
  }
  
  digitalWrite(13, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(13, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
  */
  
}