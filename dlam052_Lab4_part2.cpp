enum States{INIT, S0, S1} SM1_state = INIT;
unsigned long lastRan;
const unsigned long period = 1000;
int X_button = 8;
int Y_button = 9;

// Array of Output Pin variables, set to the pins being used
const int b_size = 4;
const int b[b_size] = {2, 3, 4, 5};
// Output Buffer
int b_buf = 0x00;
// Input Variables

// Serial Monitor Buffer
int s_buf = 0x00; 

/* 's' is an array of integers of size 8. Note that arrays start at 0
 We will use this to be able to see the individual bit values of the s_buf

 */
const int s_size = 8;
int s[s_size];

bool temp = false;
int counter = 0;

// We can also define our own helper functions. It is a good idea to use helper functions whenever they make sense.
// Normally we also define the return type (void for none)

// Read from the serial monitor into s_buf and the s[] array for individual bits
void readData()
{
    if(Serial.available())
        s_buf = Serial.parseInt();

    for(int i = (s_size - 1); i>=0; i--)  { 
        s[i] = (s_buf >> i) & 0x01; // What's going on here?
        // ">>" bit shifting 
        // "&" bit masking
    }

}
// Reset the Output Buffer. 
void resetBuffer() {
    if(analogRead(A1) <= 100) {
      delay(2000);
    }
    delay(1000);
    for(int i = 0; i < b_size; i++) {
        // Note this is an arduino function call to the pins
        digitalWrite(b[i], LOW);
    }
}
// Writes to the buffer. Note this function ORs the current value with the new value
// Note that size is an optional argument with default size the same as the buffer
void writeBuffer(unsigned char b_temp, int size = b_size)
{
    for (int i = (size - 1); i >= 0; i--) {
        if ((b_temp >> i) & 0x01) {
        digitalWrite(b[i], HIGH);
        }
    }
    

}


void setup(){
  //some set up (Default Arduino Function)
    pinMode(X_button, INPUT);
    pinMode(A1, INPUT);

    // LEDs
    for(int i = 0; i < b_size; i++)
    {
        pinMode(b[i], OUTPUT);
    }
    Serial.begin(9600);
   lastRan = 0;
}
// This function takes in the state as an argument & returns the current state
int SM1_Tick(int state){
    //Read thing
    switch(state){ // State transitions
      case INIT:
         //State Transition
            state = S0;
        break;
      case S0:
            state = S0;
        break;
    }

    switch(state){ // State Action
      case INIT:
         //State Action
        break;
      case S0:
         while(!temp){
           for(int i = counter; i < b_size; i++) {
            if(i == 3) {
              counter = 0;
            }
            digitalWrite(b[i], HIGH);
            resetBuffer();
            
           }
         }
        
      break;

    return state;
}
}

void loop(){ 
    ///Default arduino function
    // We have to cast the return value of the tick function to type States
  if ((millis() - lastRan) > period) {
    SM1_state = (States)SM1_Tick(SM1_state);
    lastRan = millis();
  } 
}