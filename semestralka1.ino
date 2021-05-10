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
 SET_TIME_NEW, SET_DAY, MENU, SET_TIME, SET_ALARM, SET_TIMER, ALARM, TIMER  
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

int alarmH = 0;
int alarmM = 0;
int alarmS = 0;
int alarmD = 0;

int timerH = 0;
int timerM = 0;
int timerS = 0;

bool alarmSet = 0;

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

char keyPressed;

// - - - - - KEYBOARD BLOCK - - - - - // 

// - - - - LCD DISPLAY BLOCK - - - - //
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);  

void displayMenu( )
{
  lcd.setCursor(0, 0);
  lcd.print("TIME: ");
  printTime();
  
  lcd.setCursor(0, 1);
  lcd.print(" DAY: ");
  printDay();
}

void printTime()
{
  if(h < 10)
    lcd.print("0");
  lcd.print(h);
  
  lcd.print(":");
  
  if(m < 10)
    lcd.print("0");
  lcd.print(m);
  
  lcd.print(":");
  
  if(s < 10)
    lcd.print("0");
  lcd.print(s);
}


void printDay()
{
  switch(d)
  {
  	case 1:
    	lcd.print("MONDAY    ");
    	break;
    case 2:
    	lcd.print("TUESDAY   ");
    	break;
    case 3:
    	lcd.print("WEDNESDAY ");
    	break;
    case 4:
    	lcd.print("THURSDAY  ");
    	break;
    case 5:
    	lcd.print("FRIDAY    ");
    	break;
    case 6:
    	lcd.print("SATURDAY  ");
    	break;
    case 7:
    	lcd.print("SUNDAY    ");
    	break;
  }
}

// - - - - LCD DISPLAY BLOCK - - - - //

// BEGINNING OF MARIO THEME taken from the link below: //
// https://gist.github.com/gskielian/6135641 		   //
void playMelody()
{
  	tone(12,660,100);
	delay(150);
	tone(12,660,100);
	delay(300);
	tone(12,660,100);
	delay(300);
	tone(12,510,100);
	delay(100);
	tone(12,660,100);
	delay(300);
	tone(12,770,100);
	delay(550);
	tone(12,380,100);
	delay(575); 
}



/*
*	checkTime function increments the values of time and day
*	it is repeatedly called with a delay after displaying a menu
*	it checks if values are correct and don't go over 
*/
void checkTime()
{
  s += 1;
  if(s == 60)
  {
    s = 0;
    m += 1;
  }
  if(m == 60)
  {
    m = 0;
    h += 1;
  }
  if(h == 24)
  {
    h = 0;
    d += 1;
  }
  if(d > 7)
  {
    d = 1; 
  }
}

/* Check Alarm functions checks whether an alarm will be activated or not */
bool checkAlarm()
{
  if( alarmH == h )
  {
    if( alarmM == m )
    {
      if( alarmS == s )
      {
       if( alarmD == d )
       {
    	 return true;
       }
      }
    }
  }
  return false;
}

/* Alarm method plays tune and changes the display until confirmation	*/
void alarm()
{
  lcd.clear();
  lcd.setCursor( 2, 0 );
  lcd.print("WAKE UP!");
  lcd.setCursor( 0, 1 );
  lcd.print("PRESS ANY BUTTON");
  
  while( true )
  {
   keyPressed = keyPad.getKey();
   if( keyPressed != NO_KEY )
   {
    if( alarmSet == true )
    {
    	alarmSet = false;
    }
    break; 
   }
   playMelody();  
  }
  
}

/* Timer method counts down to 0 and prints current countdown to LCD*/
void timer()
{
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("COUNTDOWN");
  while( true )
  {
    lcd.setCursor(4, 1);
  	if(timerH < 10)
      lcd.print("0");
  	lcd.print(timerH);
  
  	lcd.print(":");
  
  	if(timerM < 10)
  	  lcd.print("0");
  	lcd.print(timerM);
  
  	lcd.print(":");
  
  	if(timerS < 10)
  	  lcd.print("0");
  	lcd.print(timerS);
   
    checkTime();
    
  	if(timerS == 0)
  	{
      if( timerM != 0 )
      {
      	timerS = 59;
  	  	timerM -= 1;
      }
  	}
  	if(timerM == 0)
  	{
      if( timerH != 0 )
      {
  	  	timerM = 59;
  	  	timerH -= 1;
      }
  	}
  	if(timerH == 0)
    {
  	}
    timerS -= 1;
    delay(1000);
    if(timerH == 0 && timerM == 0 && timerS == 0 )
      break;
  }
}

// - - - - - - - - - SET METHOD BLOCK - - - - - - - - - //

/*
* 	setTime function sets a new time for the Alarm clock
* 	infinite loop checks if key pressed is correct and the proceeds
*	once all numbers are written, the time is set. 
*/
void setTime( bool alarm )
{
  lcd.clear();
  lcd.setCursor(4, 0);
  if( alarm == false )
  {
  	lcd.print("SET TIME     ");
  }
  else
  {
    lcd.print("SET ALARM    "); 
  }
  lcd.setCursor(4, 1);
  
  int pos = 1;	//pos number shows current position on time scale
  				//12:34:56 where pos 1 and 2 are hours etc.
  Serial.println(pos);
  int temp = 0;
  
  while(true)
  {
    temp = 0;
    keyPressed = keyPad.getKey();
    // SETTING OF HOURS
    if( pos == 1 && (keyPressed == '0' || keyPressed == '1' || keyPressed == '2' ))
    {
      temp = keyPressed - 48;
      if( !alarm )
      {
      	h = temp * 10;		//tens of hours thus * 10
      }
      else
      {
        alarmH = temp * 10; 
      }
      pos += 1;
      lcd.print(temp);
      continue;
    }
    
    if( pos == 2 && (keyPressed == '0' || keyPressed == '1' || keyPressed == '2'
       			 || keyPressed == '3' || keyPressed == '4' || keyPressed == '5'
       			 || keyPressed == '6' || keyPressed == '7' || keyPressed == '8' 
                 || keyPressed == '9'))
    {
      	if( h < 20 )
      	{
          	temp = keyPressed - 48;
          	if( ! alarm )
            {  
        	  h += temp;
            }
          	else
            {
              alarmH += temp; 
            }
        	pos += 1;
          	lcd.print(temp);
            lcd.print(":");
          	//Serial.println(h);
          	continue;
      	}
      	else if ( h == 20 )
      	{
        	if(keyPressed == '0' || keyPressed == '1' || keyPressed == '2' || keyPressed == '3')
        	{
          		temp = keyPressed - 48;
                if( !alarm )
                {
        		  h += temp;
                }
              	else
                {
                  alarmH += temp; 
                }
        		pos += 1;
              	lcd.print(temp);
                lcd.print(":");
              	//Serial.println(h);
              	continue;
        	}
      	}
    }
    
    // SETTING OF MINUTES
    if( pos == 3 && (keyPressed == '0' || keyPressed == '1' || keyPressed == '2'
       			 || keyPressed == '3' || keyPressed == '4' || keyPressed == '5' ))
    {
      temp = keyPressed - 48;
       if( !alarm )
      {
      	m = temp * 10;		//tens of minutes thus * 10
      }
      else
      {
        alarmM = temp * 10; 
      }
      pos += 1;
      lcd.print(temp);
      continue;
    }
    
    if( pos == 4 && (keyPressed == '0' || keyPressed == '1' || keyPressed == '2'
       			 || keyPressed == '3' || keyPressed == '4' || keyPressed == '5'
       			 || keyPressed == '6' || keyPressed == '7' || keyPressed == '8' 
                 || keyPressed == '9'))
    {
      temp = keyPressed - 48;
        if( !alarm )
        {
          m += temp;
        }
        else
        {
          alarmM += temp; 
        }		
      pos += 1;
      lcd.print(temp);
      lcd.print(":");
      Serial.println(m);
      continue;
    }
    
    // SETTING OF SECONDS
    if( pos == 5 && (keyPressed == '0' || keyPressed == '1' || keyPressed == '2'
       			 || keyPressed == '3' || keyPressed == '4' || keyPressed == '5' ))
    {
      temp = keyPressed - 48;
      if( !alarm )
      {
      	s = temp * 10;		//tens of seconds thus * 10
      }
      else
      {
        alarmS = temp * 10; 
      }
      pos += 1;
      lcd.print(temp);
      continue;
    }
    
    if( pos == 6 && (keyPressed == '0' || keyPressed == '1' || keyPressed == '2'
       			 || keyPressed == '3' || keyPressed == '4' || keyPressed == '5'
       			 || keyPressed == '6' || keyPressed == '7' || keyPressed == '8' 
                 || keyPressed == '9'))
    {
      temp = keyPressed - 48;
        if( !alarm )
        {
          s += temp;
        }
        else
        {
          alarmS += temp; 
        }		
      pos += 1;
      lcd.print(temp);
      Serial.println(s);
      break;
    }
  }
}

void setDay( bool alarm )
{
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("SET DAY 1-7");
  lcd.setCursor(7, 1);
  
  while( true )
  {
    keyPressed = keyPad.getKey();
    if(	   keyPressed == '1' || keyPressed == '2' || keyPressed == '3' || keyPressed == '4' 
       	|| keyPressed == '5' || keyPressed == '6' || keyPressed == '7' )
    {
      	if( !alarm )
      	{  
      		d = keyPressed - 48;
      	}
      	else
      	{
        	alarmD = keyPressed - 48; 
      	}
   		lcd.print(keyPressed);
        break;
    }
  }
  
}

void setAlarm()
{
  setTime(true);
  setDay(true);
  alarmSet = true;
}

void setTimer()
{
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("SET TIMER   ");
  lcd.setCursor(4, 1);
  
  int pos = 1;
  
  while(true)
  {
    keyPressed = keyPad.getKey();
    int temp = 0;
    //SETTING TIMER HOURS
    if(pos == 1 && keyPressed != NO_KEY &&( keyPressed != 'A' || keyPressed != 'B' || keyPressed != 'C'
                ||   keyPressed != 'D'  || keyPressed != '#' || keyPressed != '*'))
    {
      temp = keyPressed - 48;
      timerH = temp * 10;
      pos += 1;
      lcd.print(keyPressed);
      continue;
    }
    if(pos == 2 && keyPressed != NO_KEY && ( keyPressed != 'A' || keyPressed != 'B' || keyPressed != 'C'
                ||   keyPressed != 'D' || keyPressed != '#' || keyPressed != '*'))
    {
      temp = keyPressed - 48;
      timerH += temp;
      pos += 1;
      lcd.print(keyPressed);
      lcd.print(':');
      continue;
    }
    //SETTING TIMER MINUTES
    if(pos == 3 && keyPressed != NO_KEY &&( keyPressed == '1' || keyPressed == '2' || keyPressed == '3'
                ||   keyPressed != '4' || keyPressed != '5' || keyPressed != '0'))
    {
      temp = keyPressed - 48;
      timerM = temp * 10;
      pos += 1;
      lcd.print(keyPressed);
      continue;
    }
    if(pos == 4 && keyPressed != NO_KEY && ( keyPressed != 'A' || keyPressed != 'B' || keyPressed != 'C'
                ||   keyPressed != 'D' || keyPressed != '#' || keyPressed != '*'))
    {
      temp = keyPressed - 48;
      timerM += temp;
      pos += 1;
      lcd.print(keyPressed);
      lcd.print(':');
      continue;
    }
    //SETTING TIMER SECONDS
    if(pos == 5 && keyPressed != NO_KEY && ( keyPressed == '1' || keyPressed == '2' || keyPressed == '3'
                ||   keyPressed != '4' || keyPressed != '5' || keyPressed != '0'))
    {
      temp = keyPressed - 48;
      timerS = temp * 10;
      pos += 1;
      lcd.print(keyPressed);
      continue; 
    }
    if(pos == 6 && keyPressed != NO_KEY && ( keyPressed != 'A' || keyPressed != 'B' || keyPressed != 'C'
                ||   keyPressed != 'D' || keyPressed != '#' || keyPressed != '*'))
    {
      temp = keyPressed - 48;
      timerS += temp;
      pos += 1;
      lcd.print(keyPressed);
      break;
    } 
  }    
}

// - - - - - - - - - SET METHOD BLOCK - - - - - - - - - //


////////////////////////////////////////////////////////////////
//					SETUP AND LOOP BLOCK					  //
////////////////////////////////////////////////////////////////
void setup()
{
  lcd.begin(16,2);
  pinMode(12, OUTPUT);		//buzzer setup
  Serial.begin(9600);
}

void loop()
{
  //displayMenu();
  switch(STATE)
  {
    case SET_TIME_NEW:
    	setTime(false);
    	NEXT_STATE = SET_DAY;
    	break;
    
    case SET_DAY:
    	setDay(false);
    	NEXT_STATE = MENU;
    	break;
    
    case MENU:
    	displayMenu();
    	keyPressed = keyPad.getKey();
    
    	if( keyPressed == 'A' )
        {
          NEXT_STATE = SET_TIME;
        }
    	if( keyPressed == 'B' )
        {
          NEXT_STATE = SET_ALARM;
        }
    	if( keyPressed == 'C' )
        {
          NEXT_STATE = SET_TIMER;
        }
    	break;
    
    case SET_TIME:
    	setTime(false);
    	NEXT_STATE = SET_DAY;
    	break;
    
    case SET_ALARM:
    	setAlarm();
    	NEXT_STATE = MENU;
    	break;
    
    case SET_TIMER:
    	setTimer();
    	NEXT_STATE = TIMER;
    	break;
    
    case ALARM:
    	alarm();
    	NEXT_STATE = MENU;
    	break;
    
    case TIMER:
    	timer();
    	alarm();
    	NEXT_STATE = MENU;
    	break;
  }
  delay(990);
  if( alarmSet == true )
  {
  	if ( checkAlarm() )
    {
     NEXT_STATE = ALARM; 
    }
  }
  checkTime();
  STATE = NEXT_STATE;
    
}
