#include <Servo.h>
#include <LiquidCrystal_I2C.h>

/*Defining Constants*/
#define SERVOPIN 2
#define POTPIN1 A1
#define POTPIN2 A3

/*Declaring Global Variables */
int rawData1 = 0, rawData2 = 0;
int VO2 = 0;
int rate = 0;
int angleStroke = 150;
int currentThreshold = 0;
int angleChangeDuration = 10;
int servoPosition = 0;
int timePeriod = 0;
int lcdRefresh = 0;
int refreshThreshold = 70;

Servo myservo;  // create servo object to control a servo
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display


void setup() {
  Serial.begin(9600);
  myservo.attach(SERVOPIN);             //Attach pin number to the servo object
  lcd.begin();                           //Initialize the LCD
  lcd.backlight();                      //Turn the backlight of LCD
  lcd.setCursor(2, 0);                  //''''\\
  lcd.print("INITIALIZING");            //     \\ Print Values
  lcd.setCursor(3, 0);                  //     // to LCD Screen
  lcd.print("OPENGILLS VENTILATOR");              //,,,,//
  delay(2000);                          // Delay of 2 sec
  lcd.clear();                          // Clears the data on LCD screen
}

void loop() {
  oxygenVolume();                                 //Function to read and convert data from Potentiometer 1
  respirationRate();                              //Function to read and convert data from Potentiometer 2
  displayStatus(rate, VO2);                       //Function to write data to LCD screen
  moveServo(angleStroke, angleChangeDuration);    //Function to write angles to move servo with specific delay between two movements.

}

int oxygenVolume() {                 //Function to read and convert data from Potentiometer 1
  rawData1 = analogRead(POTPIN1);
  VO2 = rawData1 / 10.23;
//  Serial.print("VO2  "); Serial.print(VO2); Serial.print("\t");
}

int respirationRate() {              //Function to read and convert data from Potentiometer 2
  rawData2 = analogRead(POTPIN2);
  rate = rawData2 / 10.23;
//  Serial.print("rate  "); Serial.print(rate); Serial.print("\t");
}

void displayStatus(int x, int y) {   //Function to print the values on LCD
 if( lcdRefresh >= refreshThreshold){
  lcd.setCursor(0, 0);
  lcd.print("Res. Rate: ");
  lcd.print(x);                      //Print Respiration Rate in percentage on LCD
  lcd.print("  ");
  lcd.setCursor(0, 1);
  lcd.print("Air Volume: ");
  lcd.print(y);                      //Print Air Volume in percentage on LCD
  lcd.print(" ");
  if (y < 100) {
    lcd.print(" ");
    if (y < 10) {
      lcd.print(" ");
    }
  }
  lcdRefresh = 0;
 }
 lcdRefresh++;
}
long int t = 0, tp = 0, td = 0;
void moveServo(int l, int m) {     //Function to move servo

  for (servoPosition = 0; servoPosition <= currentThreshold; servoPosition += 1) { //Forward Stroke loop of servo
    myservo.write(servoPosition);
    delay(angleChangeDuration);
    updateData();                                                             //Updates data on Screen while servo is moving
    Serial.println(servoPosition);
  }
  for (servoPosition = currentThreshold; servoPosition >= 0; servoPosition -= 1) { //Backward Stroke loop of servo
    myservo.write(servoPosition);
    delay(angleChangeDuration);
    updateData();                                                             //Updates data on Screen while servo is moving
    Serial.println(servoPosition);
  }
}

void updateData() {
  oxygenVolume();
  respirationRate();
  displayStatus(rate, VO2);
  calculation();
}

void calculation() {
  timePeriod = (60000 / (8 + ((34 * rate) / 100)));
  currentThreshold = (20+((angleStroke * VO2) / 100));
  angleChangeDuration = (timePeriod / (2 * currentThreshold));
//  Serial.print("timePeriod"); Serial.print(timePeriod); Serial.print("\t");
//  Serial.print(currentThreshold); Serial.print("\t");
//  Serial.print(angleChangeDuration); Serial.print("\t");
}
