// SERVO MOTOR CONSTANTS
#include <Servo.h>
Servo myservo;  // create Servo object to control a servo
int pos = 0;    // variable to store the servo position

// WATER LEVEL CONSTANTS 
const int WATER_SENSOR = 2;
const int RELAY_ENABLE = 3;
const int RELAY_PIN = 13;  // the Arduino pin, which connects to the IN pin of relay

// PH LEVEL CONSTANTS
#define SensorPin 0          // the pH meter Analog output is connected with the Arduino’s Analog
unsigned long int avgValue;  //Store the average value of the sensor feedback
float b;
int buf[10],temp;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin as an output.

  // SERVO MOTOR SETUP
  pinMode(3,INPUT);
  myservo.attach(9);

  // WATER LEVEL SETUP
  pinMode(RELAY_ENABLE, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);

  // PH LEVEL SETUP
  Serial.begin(9600);  
  Serial.println("\nReady");    //Test the serial monitor
}

// the loop function runs over and over again forever
void loop() {
  // WATER LEVEL SYSTEM
  int status = digitalRead(2);
  if (status == HIGH) {
  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(RELAY_ENABLE, HIGH);
  delay(4000);                      // wait for a second
  } else {
  digitalWrite(RELAY_ENABLE, LOW);
  digitalWrite(RELAY_PIN, HIGH);
  }
  // SERVO MOTOR SYSTEM
  if(digitalRead(3)==LOW){
    myservo.write(180);
  }
  else
 myservo.write(0);

 // PH LEVEL SYSTEM
 for(int i=0;i<10;i++)       //Get 10 sample value from the sensor for smooth the value
  { 
    buf[i]=analogRead(SensorPin);
    delay(10);
  }
  for(int i=0;i<9;i++)        //sort the analog from small to large
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
  avgValue=0;
  for(int i=2;i<8;i++)                      //take the average value of 6 center sample
    avgValue+=buf[i];
  float phValue=(float)avgValue*5.0/1024/6; //convert the analog into millivolt
  phValue=3.5*phValue - 1.5;                      //convert the millivolt into pH value
  Serial.print("    pH:");  
  Serial.print(phValue,2);
  Serial.println(" ");
  digitalWrite(13, HIGH);       
  delay(800); 
}