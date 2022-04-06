//This was my inspiration for the code:
//https://www.youtube.com/user/greatscottlab

const int inputPin = 1; // The pin that the amplified sound signal will be read into the microcontroller
const int buttonPin = 0; // The pin used to correct for different noise environments
const int outputPin = 1; // The pin used to turn on the light/motor/relay/5V/9V 

//Setup Variables
int sensorvalue=0;
int eventstatus = 0;
int sensorthresholdhigh = 750;
int sensorthresholdlow = 730;
int threshold;

// YOU MAY WANT TO CHANGE HERE
// If clap is too sensitive, increase margin. Else, decrease margin
int margin = 20;


//Setup Pins
void setup () {
  pinMode(outputPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(inputPin+1, INPUT);
}

void loop() { 

// Read the sound value 10 times. The average becomes the threshold value which is used to detect a clap
  if(!(digitalRead(buttonPin))){
    delay(2000);
    int analogsum = 0;
    for(int n=0;n<10;n++){
      delay(10);
      analogsum += analogRead(inputPin); 
      }
    threshold = analogsum/10; 
    sensorthresholdhigh = threshold+margin;
    sensorthresholdlow = threshold-margin;
    delay(1000);
  }

  // Read the amplified value of the microphone
  eventstatus = 0;  
  sensorvalue = analogRead(inputPin); 
  delay(1);

  // Step 0: Detect a high signal
  if(eventstatus==0){ 
    if(sensorvalue>sensorthresholdhigh){
      eventstatus=1;  
    }
  }
   // Step 1: Detect a low signal
    if(eventstatus==1){  
    for(int k =100; k>0;k--){
      delay(1);
      sensorvalue=analogRead(inputPin);
      if(sensorvalue<threshold){
        eventstatus=2; 
        
        break;
      }      
    }
  }
  // Step 2: Detect a high signal from second clap
  if(eventstatus==2){
    delay(500);
    for(int n=1000;n>0;n--){
      delay(1);
      sensorvalue=analogRead(inputPin);
      if(sensorvalue>sensorthresholdhigh){
        eventstatus=3;
      break;
      }
      
    }
  }

    // Step 3: Turn on the light
  if(eventstatus==3){
    digitalWrite(outputPin, !digitalRead(outputPin));
    delay(100);
    
  }
}
