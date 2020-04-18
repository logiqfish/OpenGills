#define potPin A3      //Potentiometer attaches on A3 of arduino
/*Declaring variables*/
int rawData = 0;
int data = 0;
void setup() {
  Serial.begin(9600); // initialize serial communication at 9600 bits per second:
}

void loop() {
  rawData = analogRead(potPin);  // read the input on analog pin 3:
  data = rawData / 10.23;        // convert the raw data(ranging from 0 to 1023) into data(ranging from 0 to 100):
  Serial.println(data);          // print out the value you read:
  delay(1);                      // delay in between reads for stability
}
