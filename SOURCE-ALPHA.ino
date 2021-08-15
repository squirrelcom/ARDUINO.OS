#include <time.h>
#include <NewPing.h>  //NEWPING-ECHO
#define TRIGGER_PIN A1
#define ECHO_PIN A2
#define MAX_DISTANCE 400
#define BUTTON_ADC_PIN           A0  // A0 is the button ADC input

#define LCD_BACKLIGHT_PIN         10  // D10 controls LCD backlight

#define RIGHT_10BIT_ADC           0  // right
#define UP_10BIT_ADC            120  // up
#define DOWN_10BIT_ADC          280  // down
#define LEFT_10BIT_ADC          480  // left
#define SELECT_10BIT_ADC        720  // right
#define BUTTONHYSTERESIS         30  // hysteresis for valid button sensing window

NewPing sonar(TRIGGER_PIN,ECHO_PIN,MAX_DISTANCE); //NEWPING HC-SR04

#include <LCD4Bit_mod.h>
#include <LiquidCrystal.h>
LCD4Bit_mod lcd = LCD4Bit_mod(2); //SCREEN-R2

#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 RTC;  //TIMER

#include <OneWire.h>
#include <DS18B20.h>
#define ONEWIRE_PIN 2
byte address[8] = {��������������������������������������0x28, 0xFF, 0x39, 0x4F, 0xC0, 0x16, 0x4, 0x31};
OneWire onewire(ONEWIRE_PIN);
DS18B20 sensors(&onewire);  //TERMOMETR


//Z
int b=16; int TIME=600; int add; int af; 
extern int s=1; extern int w=0; 
int k=2; int liczba; int dlug;
int g=16, h=16, j=13; int v=13; int vv; int vj=1;
int countt; char outputCountt[16]; 
int count; char outputCount[16]; 
int counttt; char outputCounttt[16]; 

int lcd_key     = 0;  //KEYS
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5


int read_LCD_buttons()
{
 adc_key_in = analogRead(0);      // read the value from the sensor
 // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
 // we add approx 50 to those values and check to see if we are close
 if (adc_key_in > 1000) return btnNONE; // 1st option will be the most likely result
 if (adc_key_in < 50)   return btnRIGHT; 
 if (adc_key_in < 195)  return btnUP;
 if (adc_key_in < 380)  return btnDOWN;
 if (adc_key_in < 555)  return btnLEFT;
 if (adc_key_in < 790)  return btnSELECT;  
 return btnNONE;  // when all others fail, return this...
}

/* /////////// */

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); //INIC.DIODY
  lcd.init(); //INIC.LCD    
  lcd.clear();
  lcd.printIn(" WELCOME TO"); lcd.cursorTo(2,0);
  lcd.printIn("  ChipOS v0.1 "); delay(TIME);
  lcd.cursorTo(1,0); lcd.printIn("DESIGNED BY");
  lcd.cursorTo(2,0); lcd.printIn("Squirrel Computers");
 delay(TIME); 
 
  for(int a=0;a<16;a++){ 
 b--; lcd.cursorTo(1,0);
lcd.cursorTo(1,a); lcd.printIn("/");
lcd.cursorTo(2,b); lcd.printIn("\\");
  }  
lcd.clear();
delay(200);

Wire.begin();
 RTC.begin(); //TIMER
 RTC.adjust(DateTime(__DATE__, __TIME__)); 

 sensors.begin();  //TERMO.
  sensors.request(address);
}

/* /////////// */

void loop() {
  digitalWrite(LED_BUILTIN, HIGH); 
    lcd_key = read_LCD_buttons();
// OS

if(w==3){ //TIMER
lcd.cursorTo(1,0); lcd.printIn("Time:");        
 lcd.cursorTo(1,6); itoa(count, outputCount, 10); //int -> char (USNG10)
  lcd.printIn(outputCount); count++; lcd.printIn("     "); //STOPER
   DateTime now = RTC.now(); lcd.cursorTo(2,0); //CZAS GLOBALNY
   int m=now.minute(); int g=now.hour(); int d=now.day(); int mo=now.month(); int y=now.year();
  char mi[16]; itoa(m, mi, 10); char go[16]; itoa(g, go, 10); 
  char di[16]; itoa(d, di, 10); char moo[16]; itoa(mo, moo, 10);
  char yy[16]; itoa(y, yy, 10);
  
    lcd.printIn( go ); lcd.printIn(":"); lcd.printIn( mi ); 
    lcd.printIn("-"); lcd.printIn( di ); lcd.printIn( moo ); 
    lcd.cursorTo(1,12); lcd.printIn( yy );    
    
    if (sensors.available())
  {
    int temperature = sensors.readTemperature(address);
    char te[16]; itoa(temperature, te, 10);
    
    lcd.cursorTo(2,11); lcd.printIn( te ); lcd.printIn( "'C" );

    sensors.request(address);
  }
    
  delay(1000); switch (lcd_key) {case btnLEFT:{lcd.clear();w=0;count=0; break;}}  }

if(w==5){ //SLOT1
if(w==6){ //SLOT2
if(w==4){ //CALC
 
#define LCD_BACKLIGHT_OFF()     digitalWrite( LCD_BACKLIGHT_PIN, LOW )
#define LCD_BACKLIGHT_ON()      digitalWrite( LCD_BACKLIGHT_PIN, HIGH )
#define LCD_BACKLIGHT(state)    { if( state ){digitalWrite( LCD_BACKLIGHT_PIN, HIGH );}else{digitalWrite( LCD_BACKLIGHT_PIN, LOW );} }
/*--------------------------------------------------------------------------------------
 Variables
 --------------------------------------------------------------------------------------*/
byte buttonJustPressed  = false;         //this will be true after a ReadButtons() call if triggered
byte buttonJustReleased = false;         //this will be true after a ReadButtons() call if triggered
byte buttonWas          = BUTTON_NONE;   //used by ReadButtons() for detection of button events


int SelectingMenu = true;               //This will be true until the select button is pressed in Menu()
int scroll = 0;                         //Used in Menu(). Stores numerical value of key pressed
int button = 0;                         //Sets scroll when a button is pressed. Acts on it when release
int menu = 4;                           //Stores the value of the menu. Used in Menu()
int FunctionChoice;                     //Stores the value of the selected function
float Answer;                           //where the answer is stored.

float A;                                //holds the values being computed
float B;
/*--------------------------------------------------------------------------------------
 Init the LCD library with the LCD pins to be used
 --------------------------------------------------------------------------------------*/
LiquidCrystal lcd( 8, 9, 4, 5, 6, 7 );   //Pins for the freetronics 16x2 LCD shield. LCD: ( RS, E, LCD-D4, LCD-D5, LCD-D6, LCD-D7 )

//------------------------------------------------------------------------------------


void setup()
{
  //button adc input
  pinMode( BUTTON_ADC_PIN, INPUT );         //ensure A0 is an input
  digitalWrite( BUTTON_ADC_PIN, LOW );      //ensure pullup is off on A0
  //lcd backlight control
  digitalWrite( LCD_BACKLIGHT_PIN, HIGH );  //backlight control pin D3 is high (on)
  pinMode( LCD_BACKLIGHT_PIN, OUTPUT );     //D3 is an output
  //set up the LCD number of columns and rows: 
  lcd.begin( 16, 2 );
  //Print some initial text to the LCD.
  lcd.setCursor( 0, 0 );   //top left
  lcd.print( "  ChipCalculator    "  ); 

  lcd.setCursor( 0, 1 );   //bottom left
  lcd.print( "               " );
  delay(1000);
  Serial.begin(9600);
  Serial.print ("We are setup");      //Testing purposes

}


void loop ()
{
  SelectingMenu = true;
  //function choice loop
  //----------------------------------------------------------
  while (SelectingMenu ==true)      
  {
    lcd.setCursor (0,0);
    lcd.print ("Function:              ");

    lcd.setCursor (0,1);

    FunctionChoice = Menu();        //Get value for FunctionChoice


    //Now we do something with the menu value we just got
    //case 0 and 5 provide looping

    switch (FunctionChoice)
    {
    case 0: 
      {
        FunctionChoice = 4;
        menu = 4;
      }
    case 1: 
      {
        lcd.print ("Add        (A+B)              ");
        break;
      }
    case 2:
      { 
        lcd.print ("Subtract   (A-B)         ");
        break;
      }
    case 3: 
      {
        lcd.print ("Multiply   (A*B)        ");
        break;
      }
    case 4:
      {
        lcd.print ("Divide     (A/B)            ");
        break;
      }
    case 5: 
      {
        FunctionChoice = 1;
        menu = 1;
      }      
    }  //End switch
  }  // End while


  // So if we get here, this means that the select button must have been pushed.
  //FunctionChoice now holds the value of the function selected by the user.
  lcd.setCursor (0,0);
  lcd.print ("   Selection       ");
  lcd.setCursor (0,1);
  lcd.print ("   Confirmed            ");
  delay (1000);  

  //                         Get A and B
  //-----------------------------------------------------------------------------

  //Similar setup, this time get A and B. No looping

  SelectingMenu = true;
  while (SelectingMenu == true)                      //Get value for A
  {
    A = Menu();
    lcd.setCursor (0,0);
    lcd.print ("   Menu            ");
    lcd.setCursor (0,1);
    lcd.print ("A = ");
    lcd.print (A);  
    lcd.print ("                       ");  

  }
  lcd.setCursor (0,0);
  lcd.print ("   A: Selection        ");
  lcd.setCursor (0,1);
  lcd.print ("   Confirmed            ");
  delay (1000);  



  SelectingMenu = true;
  while (SelectingMenu == true)                      //Get value for B
  {
    B = Menu();
    lcd.setCursor (0,0);
    lcd.print ("   Menu                ");
    lcd.setCursor (0,1);
    lcd.print ("B = ");
    lcd.print (B);  
    lcd.print ("                       ");  

  }
  lcd.setCursor (0,0);
  lcd.print ("   B: Selection           ");
  lcd.setCursor (0,1);
  lcd.print ("   Confirmed            ");
  delay (1000);  


  //                       Compute and Output
  //------------------------------------------------------------------------
  lcd.setCursor (0,0);


  switch (FunctionChoice)
  {
  case 0: 
    {
      FunctionChoice = 4;
    }
  case 1: 
    {
      lcd.print ("Add        (A+B)              ");
      Add();
      break;
    }
  case 2:
    {
      lcd.print ("Subtract   (A-B)         ");
      Subtract();
      break;
    }
  case 3: 
    {
      lcd.print ("Multiply   (A*B)        ");
      Multiply();
      break;
    }
  case 4:
    {
      lcd.print ("Divide     (A/B)            ");
      Divide();
      break;
    }
  case 5: 
    {
      FunctionChoice = 1;
    }      
  }  //End switch

  lcd.setCursor (0,1);
  lcd.print ("Answer = ");
  lcd.print (Answer);  
  lcd.print ("                       ");  
  delay(2500);
  lcd.setCursor (0,0);
  lcd.print ("                  ");
  lcd.setCursor (0,1);
  lcd.print ("                       ");  
  lcd.setCursor (0,1);
} //End void loop
//                   END LOOP
//-------------------------------------------------------------------- 






//---------------------------------------------------------------------------------
//                         Computational Functions
//---------------------------------------------------------------------------------

int Add()
{
  Answer = A+B;
  return Answer;
}
int Subtract()
{
  Answer = A-B;
  return Answer;
}
int Multiply()
{
  Answer = A*B;
  return Answer;
}
int Divide()
{
  Answer = A/B;
  return Answer;
}


//--------------------------------------------------------------------------------------
//Allows the user to scroll up and down through a menu.
//User must provide looping and Display
//--------------------------------------------------------------------------------------

int Menu ()
{
  SelectingMenu = true;
  button = ReadButtons();
  if ( buttonJustPressed == true )  //If the button is pressed, store the value
  {
    scroll = button;
    Serial.print (button);   //Testing purposes
    buttonJustPressed = false;
  }

  if (buttonJustReleased == true)  //If the button is released, act on value
  {
    buttonJustReleased = false;

    switch (scroll)
    {
    case BUTTON_UP:
      { 
        menu = menu +1;
        break;
      }
    case BUTTON_DOWN:
      {
        menu = menu - 1;
        break;
      }
    case BUTTON_SELECT:
      {
        SelectingMenu = false;
      }
    default:
      {
        break;
      }
    }  //End switch
  }    //End if
  Serial.println(menu);
  return menu;
}  //End Function






//-------------------------------------------------------------------------------------------------  


byte ReadButtons()
{
  unsigned int buttonVoltage;
  byte button = BUTTON_NONE;   // return no button pressed if the below checks don't write to btn

  //read the button ADC pin voltage
  buttonVoltage = analogRead( BUTTON_ADC_PIN );
  //sense if the voltage falls within valid voltage windows
  if( buttonVoltage < ( RIGHT_10BIT_ADC + BUTTONHYSTERESIS ) )
  {
    button = BUTTON_RIGHT;
  }
  else if(   buttonVoltage >= ( UP_10BIT_ADC - BUTTONHYSTERESIS )
    && buttonVoltage <= ( UP_10BIT_ADC + BUTTONHYSTERESIS ) )
  {
    button = BUTTON_UP;
  }
  else if(   buttonVoltage >= ( DOWN_10BIT_ADC - BUTTONHYSTERESIS )
    && buttonVoltage <= ( DOWN_10BIT_ADC + BUTTONHYSTERESIS ) )
  {
    button = BUTTON_DOWN;
  }
  else if(   buttonVoltage >= ( LEFT_10BIT_ADC - BUTTONHYSTERESIS )
    && buttonVoltage <= ( LEFT_10BIT_ADC + BUTTONHYSTERESIS ) )
  {
    button = BUTTON_LEFT;
  }
  else if(   buttonVoltage >= ( SELECT_10BIT_ADC - BUTTONHYSTERESIS )
    && buttonVoltage <= ( SELECT_10BIT_ADC + BUTTONHYSTERESIS ) )
  {
    button = BUTTON_SELECT;
  }
  //handle button flags for just pressed and just released events
  if( ( buttonWas == BUTTON_NONE ) && ( button != BUTTON_NONE ) )
  {
    //the button was just pressed, set buttonJustPressed, this can optionally be used to trigger a once-off action for a button press event
    //it's the duty of the receiver to clear these flags if it wants to detect a new button change event
    buttonJustPressed  = true;
    buttonJustReleased = false;
  }
  if( ( buttonWas != BUTTON_NONE ) && ( button == BUTTON_NONE ) )
  {
    buttonJustPressed  = false;
    buttonJustReleased = true;
  }

  //save the latest button value, for change event detection next time round
  buttonWas = button;

  return( button );
}

if(w==2){ //TEXT
  if(k==2){char a[16]="Welcome to /////"; char bb[16]="nie w tak spekta"; lcd.cursorTo(1,0); lcd.printIn(a); lcd.cursorTo(2,0); lcd.printIn(bb);} 
  if(k==3){char a[16]="ChipOS Let's go "; char bb[16]="kularny sposob j"; lcd.cursorTo(1,0); lcd.printIn(a); lcd.cursorTo(2,0); lcd.printIn(bb);} if(k<2){k=2;} 
  if(k==4){char a[16]="through the apps"; char bb[16]="ak zapowiadaly t"; lcd.cursorTo(1,0); lcd.printIn(a); lcd.cursorTo(2,0); lcd.printIn(bb);}    
  if(k==5){char a[16]="ak zapowiadaly t"; char bb[16]="o filmy i gry..."; lcd.cursorTo(1,0); lcd.printIn(a); lcd.cursorTo(2,0); lcd.printIn(bb);} 
switch (lcd_key) {
  case btnLEFT:{lcd.clear();w=0; break;} 
  case btnDOWN:{ k++; if(w==2){break;}} 
  case btnUP:{ k--; if(w==2){break;}}
  case btnNONE:{if(w==2){break;}}}}

if(w==1){ //GAME
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

#define btnRight     0
#define btnUp        1
#define btnDown      2
#define btnLeft      3
#define btnSelect    4
#define btnNone      5

byte dino[8] =
{
  B00100,
  B00111,
  B00111,
  B11110,
  B11111,
  B01110,
  B01110,
  B01010
};
byte dino1[8] =
{
  B00100,
  B00111,
  B00111,
  B11110,
  B11111,
  B01110,
  B01110,
  B01000
};

byte dino2[8] =
{
  B00100,
  B00111,
  B00111,
  B11110,
  B11111,
  B01110,
  B01110,
  B00010
};
byte dinosit[8] =
{
  B00000,
  B00000,
  B00100,
  B00111,
  B00111,
  B11110,
  B11111,
  B01010
};
byte dinosit1[8] =
{
  B00000,
  B00000,
  B00100,
  B00111,
  B00111,
  B11110,
  B11111,
  B00010
};
byte dinosit2[8] =
{
  B00000,
  B00000,
  B00100,
  B00111,
  B00111,
  B11110,
  B11111,
  B01010
};
byte obs1[8] =
{
 B00000,
 B00000,
 B10000,
 B11101,
 B11010,
 B01010,
 B01110,
 B01100
};

byte obs2[8] =
{
 B00100,
 B00100,
 B01110,
 B11111,
 B11111,
 B01110,
 B00100,
 B00100
};

byte obs3[8] =
{
 B11111,
 B01110,
 B00100,
 B00000,
 B00000,
 B00000,
 B00000,
 B00000
};

byte obs4[8] =
{
 B00100,
 B10101,
 B10101,
 B11111,
 B10101,
 B10101,
 B11111,
 B00100
};
byte freep[8] =
{
 B00000,
 B00000,
 B00000,
 B00000,
 B00000,
 B00000,
 B00000,
 B00000
};

int mat[2][24] = {
  {7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7},
  {7,0,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7}
  };

int dinoAnim[] = {1,0,2,3};

void setup() {
  Serial.begin(9600);
  
  //pinMode(but1,INPUT);
  //pinMode(but2,INPUT);
  lcd.createChar(0, dino1);
  lcd.createChar(1, dino2);
  lcd.createChar(2, dinosit1);
  lcd.createChar(3, dinosit2);
  lcd.createChar(4, obs1);
  lcd.createChar(5, obs3);
  lcd.createChar(6, obs4);
  lcd.createChar(7, freep);
  lcd.begin(16, 2);

  gameover();

}
int b1 = 0;
int b2 = 0;
int walk = 0;
int fps = 0;
int maxhigh = 600;
long jumpstarted = 0;
int isJumping = 1;
int pausebetween = 1;
bool gamestarted = false;
int highscore = 0;
int score = 0;
void redraw(){ 
  for(int j = 15; j >= 0; j--){
    for(int i = 0; i < 2; i++){
      lcd.setCursor(j,i);
      lcd.write(mat[i][j]);
    }
  }
  if(!gamestarted){
    String s = "Score: "+String(score);
    String hs = "HighS: "+String(highscore);
    lcd.setCursor(3,0);
    lcd.print(s);
    lcd.setCursor(3,1);
    lcd.print(hs);
  }
}

void cleanmat(){
  for(int i = 0; i < 2; i++){
    for(int j = 0; j < 16; j++){
      mat[i][j] = 7;
    }
  }
}

void gameover(){
  cleanmat();
  gamestarted = false;
  pausebetween = 1;
  delay(1000);
}
void loop() {
  if((getKey() == btnUp) && !b2)jumpstarted = millis();
  
  b1 = (getKey() == btnDown);
  b2 = (getKey() == btnUp);
   
  if(!gamestarted){
    if(b1 || b2){
      gamestarted = true;
      score = 0;
    }
  }
  if(gamestarted){
    if(fps%3==0)walk+=1;
    walk%=2;
    if(fps%4==0){
      pausebetween -= 1;
      for(int i = 0; i<2;i++){
        for(int j = 0; j<23; j++){
          mat[i][j] = mat[i][j+1];
        }
      }
      mat[0][23] = 7;
      mat[1][23] = 7;
    }
  
    if(!pausebetween)generate_obstacles();
    
    isJumping = !((millis()-jumpstarted<maxhigh) && b2);

    if(!isJumping && mat[0][1]==6){
      gameover();
    }
    if(!isJumping && !b1 && mat[0][1]==5){
      gameover();
    }
    if(isJumping && mat[1][1]==4){
      gameover(); 
    }
    if(isJumping && mat[1][1]==5 && !b1){
      gameover();
    }
    if(!b1) score+=1;
    if(score>highscore)highscore=score; 
    fps+=1;
  }
  redraw();
  lcd.setCursor(1,isJumping);
  lcd.write(dinoAnim[b1*2+(walk)]);
  
  delay(20);
}

void generate_obstacles(){
  int obscount = random(1,4);
  int types[4][2] = {{7,4},{6,5},{5,4},{6,7}} ;
  int type = random(0,4);
  for(int i = 0; i< obscount; i++){
    mat[0][16+i] = types[type][0];
    mat[1][16+i] = types[type][1];
  }
  int spacecount = random(2,5);
  pausebetween = obscount + spacecount;
}

int getKey() {
  int b = analogRead(A0);
  if (b > 1000) return btnNone;
  if (b < 50) return btnRight;
  if (b < 180) return btnUp;
  if (b < 330) return btnDown;
  if (b < 520) return btnLeft;
  if (b < 700) return btnSelect;
  return btnNone;
}
  

if(w==0){ //MENU
lcd.cursorTo(1,0); lcd.printIn("v0.1"); lcd.cursorTo(1,12); lcd.printIn("HOME");
if(s==1) {lcd.cursorTo(2,0); lcd.printIn(">GAME HELP TIMER");}
if(s==2) {lcd.cursorTo(2,0); lcd.printIn(" GAME>HELP TIMER");} 
if(s==3) {lcd.cursorTo(2,0); lcd.printIn(" GAME HELP>TIMER");}
if(s==4) {lcd.cursorTo(2,0); lcd.printIn(">CALC SLO1 SLOT2");}
if(s==5) {lcd.cursorTo(2,0); lcd.printIn(" CALC>SLO1 SLOT2");}
if(s==6) {lcd.cursorTo(2,0); lcd.printIn(" CALC SLO1>SLOT2");}

if(sonar.ping_cm()>=1){ 
counttt = sonar.ping_cm(); 
itoa(counttt, outputCounttt, 10);
lcd.cursorTo(1,4); lcd.printIn("|"); lcd.cursorTo(1,6); lcd.printIn("  "); 
lcd.cursorTo(1,11); lcd.printIn("|");

switch (lcd_key)               // depending on which button was pushed, we perform an action
 {
   case btnRIGHT:
     {
     if(s==1) {s=2; break;}
     if(s==2) {s=3; break;}
     if(s==3) {s=4; break;}
     if(s==4) {s=5; break;}
     if(s==5) {s=6; break;}
     if(s==6) {s=6; break;}
     }
   case btnLEFT:
     {
     if(s==6 && w==0) {s=5; break;}
     if(s==5 && w==0) {s=4; break;}
     if(s==4 && w==0) {s=3; break;}
     if(s==3 && w==0) {s=2; break;}
     if(s==2 && w==0) {s=1; break;}
     if(s==1 && w==0) {s=1; break;}
     }
   //case btnUP:
   //case btnDOWN:
   //case btnNONE:  
   
   case btnSELECT:
     {
//---
if(s==6) {w=6; lcd.clear(); break;}
if(s==5) {w=5; lcd.clear(); break;}
if(s==4) {w=4; lcd.clear(); break;}
if(s==3) {w=3; lcd.clear(); break;}
if(s==2) {w=2; lcd.clear(); break;}
if(s==1) {w=1; lcd.clear(); break;}
//---    
     }
  
 }

}}
