//Ben Clark

//Remote Control Robot

#include <IRremote.h>  // Tell the IDE that we’re using the IRremote library
int receiverpin = 12; // Signal pin the IR receiver is connected to

// Create objects needed by the IRremote Library
IRrecv irrecv(receiverpin); // Create an irrecv object instance
decode_results results;   // Create a place to hold the IR code read

int motorA1 = 4; //IN1: Sets variable for motor A1 to pin 4
int motorA2 = 5; //IN2: Sets variable for motor A2 to pin 5
int motorB1 = 6; //IN3: Sets variable for motor B1 to pin 6
int motorB2 = 7; //IN4: Sets variable for motor B2 to pin 7
int speed_value;

void setup() {
  pinMode(motorA1, OUTPUT); //Initializes motor pins as outputs
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  pinMode(receiverpin, INPUT_PULLUP); //Initializes receiver pin as an input
  irrecv.enableIRIn(); //Start the IR receiver
}

void loop() {
  if (irrecv.decode(&results))  // Have we received an IR signal?
  {
    switch(results.value) //Determine which key is pressed and act accordingly
    {
      case 0xFFA25D: speed_value = set_speed(10); break; //1 key is pressed, set speed to 10%
      case 0xFF629D: speed_value = set_speed(20); break; //2 key is pressed, set speed to 20%
      case 0xFFE21D: speed_value = set_speed(30); break; //3 key is pressed, set speed to 30%
      case 0xFF22DD: speed_value = set_speed(40); break; //4 key is pressed, set speed to 40%
      case 0xFF02FD: speed_value = set_speed(50); break; //5 key is pressed, set speed to 50%
      case 0xFFC23D: speed_value = set_speed(60); break; //6 key is pressed, set speed to 60%
      case 0xFFE01F: speed_value = set_speed(70); break; //7 key is pressed, set speed to 70%
      case 0xFFA857: speed_value = set_speed(80); break; //8 key is pressed, set speed to 80%
      case 0xFF906F: speed_value = set_speed(90); break; //9 key is pressed, set speed to 90%
      case 0xFF9867: speed_value = set_speed(100); break; //0 key is pressed, set speed to 100%
      case 0xFF18E7: go_forward(); break; //up key is pressed, move forward
      case 0xFF4AB5: go_backward(); break; //down key is pressed, move backward
      case 0xFF5AA5: turn_right(); break; //right key is pressed, pivot right
      case 0xFF10EF: turn_left(); break; //left key is pressed, pivot left
      case 0xFF38C7: stop_robot();  break; //OK key is pressed, stop the robot
    }
    irrecv.resume();     // Get ready to receive the next value
  }
}

int set_speed(int speed_percent) { //converts speed percent to a scale from 0 to 255
  int speed_val;
  speed_val = map(speed_percent, 0, 100, 0, 255);
  return speed_val;
}


void go_forward() { //moves robot forward at desired speed
  digitalWrite(motorA1, LOW); 
  analogWrite(motorA2, speed_value);
  digitalWrite(motorB1, LOW);
  analogWrite(motorB2, speed_value);
  }
void go_backward() { //moves robot backward at desired speed
  analogWrite(motorA1, speed_value);
  digitalWrite(motorA2, LOW);
  analogWrite(motorB1, speed_value);
  digitalWrite(motorB2, LOW);
}
void turn_right() { //turns robot to the right at desired speed
  analogWrite(motorA1, speed_value);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  analogWrite(motorB2, speed_value);
}
void turn_left() { //turns robot to the left at desired speed
  digitalWrite(motorA1, LOW);
  analogWrite(motorA2, speed_value);
  analogWrite(motorB1, speed_value);
  digitalWrite(motorB2, LOW);
}
void stop_robot() { //stops the robot
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
}
  
  
