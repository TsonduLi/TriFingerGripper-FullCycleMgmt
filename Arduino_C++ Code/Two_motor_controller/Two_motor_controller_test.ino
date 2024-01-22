const int stepPin1 = 3;
const int dirPin1 = 4;
const int slpPin1 = 7;
const int fsrVoltagePin1 = 13;

const int stepPin2 = 9;
const int dirPin2 = 10;
const int slpPin2 = 13;
int analogInputPin = A0;
int rawValueRead= 0;
float vArduino = 0.0;
float vActual = 0.0;

int fsrPin = 0;     // the FSR and 10K pulldown are connected to a0
int fsrReading;     // the analog reading from the FSR resistor divider
int fsrVoltage;     // the analog reading converted to voltage
int FSR=0;           // not using force sensor resistor if FSR is set to zero
int keepRotating; 
int frequency=100;    // frequecny which applied force is measured
int count=0;
int sleep=0;
unsigned long fsrResistance;  // The voltage converted to resistance
unsigned long fsrConductance;
double fsrForce;       // Finally, the resistance converted to force
double NewtonThreshold=2; // threshold in Newton to stop the DC motor

int close=1;
int open=1;

long MotorlInterval=800;
long Motor2Interval=1;
unsigned long previousMotor1Time=micros();
unsigned long previousMotor2Time=micros();

 
void setup(void) {
  pinMode(stepPin1,OUTPUT);
  pinMode(dirPin1,OUTPUT);
  pinMode(slpPin1,OUTPUT);
  pinMode(fsrVoltagePin1, OUTPUT);
  pinMode(stepPin2,OUTPUT);
  pinMode(dirPin2,OUTPUT);
  pinMode(slpPin2,OUTPUT);
  pinMode(analogInputPin, INPUT);
  Serial.begin(115200);  // We'll send debugging information via the Serial monitor
}

void loop(void) {
  rawValueRead = analogRead(analogInputPin);
  vArduino = (rawValueRead * 5.0) / 1024.0;
  Serial.print("Vdc = ");
  Serial.println(vArduino,2);
  //write initial state
  //digitalWrite(dirPin1,HIGH);
  if (sleep==0){
    digitalWrite(slpPin1,HIGH);
    }else {digitalWrite(slpPin1,LOW);}
  
  //digitalWrite(dirPin2,HIGH);
  if (sleep==0){
    digitalWrite(slpPin2,HIGH);
    }else {digitalWrite(slpPin2,LOW);}
   
  // input desired rotation numeber mannually 
    //rotate the motor based on input revolution number 
    //(close)
    //for(int x = 0; x < 1; x++) {
    if (close==1){    
      digitalWrite(dirPin1,HIGH);
      digitalWrite(dirPin2,HIGH);
        //digitalWrite(stepPin1, LOW);
        //digitalWrite(stepPin2, LOW);      
      //previousMotor1Time=micros();
      for(int x = 0; x < 204*5;x++) {
        //unsigned long currentMotor1Time=micros();
        //unsigned long currentMotor2Time=micros();
        digitalWrite(stepPin1, HIGH); 
        delayMicroseconds(600); 
        digitalWrite(stepPin1,LOW); 
        delayMicroseconds(600);

        digitalWrite(stepPin2, HIGH); 
        delayMicroseconds(600); 
        digitalWrite(stepPin2,LOW); 
        delayMicroseconds(600);
      }
    }
  delay(5000);
    if (open==1){    
      digitalWrite(dirPin1,LOW);
      digitalWrite(dirPin2,LOW);
      //digitalWrite(stepPin1, LOW);
      //digitalWrite(stepPin2, LOW);      
      for(int x = 0; x < 204*0;x++) {

        digitalWrite(stepPin1, HIGH); 
        delayMicroseconds(600); 
        digitalWrite(stepPin1,LOW); 
        delayMicroseconds(600);

        digitalWrite(stepPin2, HIGH); 
        delayMicroseconds(600); 
        digitalWrite(stepPin2,LOW); 
        delayMicroseconds(600);
      }
    }
    exit(0);
}
