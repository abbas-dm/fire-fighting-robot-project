/*========================================================================================*/
                                /*Fire Figthing Robot - Code*/
/*========================================================================================*/

/*INCLUDING SERVO.H LIBRARY TO OPERATE ON SERVO MOTOR*/
#include<Servo.h>

/* For the sensor value */
#define middle_sensor 0
#define left_sensor 2
#define right_sensor 3

/* For the motor control */
#define left_motor1 5
#define left_motor2 6
#define right_motor1 7
#define right_motor2 8

#define pump 10
#define servo_motor 11

boolean flame = false;
int motion_pos = 0;
Servo servo;

void setup() {
  // put your setup code here, to run once:
  /*Configuring pinMode for sensor pins*/
  pinMode(middle_sensor, INPUT);
  pinMode(left_sensor, INPUT);
  pinMode(right_sensor, INPUT);
  
  /*Configuring pinMode for motor pins*/
  pinMode(left_motor1, OUTPUT);
  pinMode(left_motor2, OUTPUT);
  pinMode(right_motor1,OUTPUT);
  pinMode(right_motor2,OUTPUT);
  
  pinMode(pump, OUTPUT);
  pinMode(servo_motor, OUTPUT);

  /* Attaching pin to Servo motor*/ 
  servo.attach(servo_motor);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  /*Checking for flame is present or not*/
  if(digitalRead(middle_sensor) == 1 & digitalRead(left_sensor) == 1 & digitalRead(right_sensor) == 1){
    Serial.println("No fire/flame is detected");
    digitalWrite(left_motor1, HIGH);
    digitalWrite(left_motor2, HIGH);
    digitalWrite(right_motor1, HIGH);
    digitalWrite(right_motor2, HIGH);
    delay(500);  
  }  
    
  /*If flame is detected at middle sensor*/
  else if(digitalRead(middle_sensor) == 0){
    Serial.println("Fire Fire Fire!!!!");
    digitalWrite(left_motor1, HIGH);
    digitalWrite(left_motor2, LOW);
    digitalWrite(right_motor1, HIGH);
    digitalWrite(right_motor2, LOW);
    flame = true; 
  }  
  
  /*If flame is detected at left sensor*/
  else if(digitalRead(left_sensor) == 0){
    Serial.println("Fire Fire Fire!!!!");
    digitalWrite(left_motor1, LOW);
    digitalWrite(left_motor2, HIGH);
    digitalWrite(right_motor1, HIGH);
    digitalWrite(right_motor2, HIGH);
    flame = true; 
  }  
   
  /*If flame is detected at right sensor*/
  else if(digitalRead(right_sensor) == 0){
    Serial.println("Fire Fire Fire!!!!");
    digitalWrite(left_motor1, HIGH);
    digitalWrite(left_motor2, HIGH);
    digitalWrite(right_motor1, LOW);
    digitalWrite(right_motor2, HIGH);
    flame = true; 
  }
  
  while(flame == true){     // Loop to activate pumping action of the robot
    delay(500);
    digitalWrite(left_motor1, HIGH);
    digitalWrite(left_motor2, HIGH);
    digitalWrite(right_motor1, HIGH);
    digitalWrite(right_motor2, HIGH);
    digitalWrite(pump, HIGH);
    delay(10);

    /*Logic for the rotation of servo motor to put water on flame*/
    for(motion_pos = 50; motion_pos<130; motion_pos+=1){
      servo.write(motion_pos);
      delay(10);  
    }
    for(motion_pos = 130; motion_pos>=50; motion_pos-=1){
      servo.write(motion_pos);
      delay(10);  
    }
    
    digitalWrite(pump, LOW);
    servo.write(90);
    flame = false; 
  }   
}
