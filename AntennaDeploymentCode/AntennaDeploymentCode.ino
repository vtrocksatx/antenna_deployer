/*
 * RockSat-X 2016 Antenna Deployer Code
 * Version: 02/21/2016
 * Author(s): Sebastian Welsh and John Mulvaney
 */

#define DIR_PIN 2
#define STEP_PIN 3
#define DEPLOY_SPEED .8 // (0.0, 1.0] note: slower is stronger
#define ROTATE_SPEED .1 // (0.0, 1.0] note: slower is stronger
#define RETRACT_SPEED .8 // (0.0, 1.0] note: slower is stronger
#define DEPLOY_STEPS 26000 // 8 microsteps per step
#define ROTATE_STEPS 8000 // 8 microsteps per step
#define RETRACT_STEPS 25000 // 8 microsteps per step
#define PREDEPLOY_SLEEP_TIME 1000
#define TRANSMIT_WINDOW_LENGTH 1000

bool executeDeployment = true;

void setup() { 
  pinMode(DIR_PIN, OUTPUT); 
  pinMode(STEP_PIN, OUTPUT); 
} 

void loop(){
  
  if (executeDeployment) {
    executeDeployment = false;
    // Wait until skirt sep.
    delay(PREDEPLOY_SLEEP_TIME);
  
    // Deploy antenna
    for (int i = 0; i < 5; i++) {
      rotate(-DEPLOY_STEPS, DEPLOY_SPEED);
    }
    rotate(-ROTATE_STEPS, ROTATE_SPEED);
  
    // Wait until transmission is complete
    delay(TRANSMIT_WINDOW_LENGTH); 

    // Retract antenna
    rotate(ROTATE_STEPS, ROTATE_SPEED);
    for (int i = 0; i < 5; i++) {
      rotate(RETRACT_STEPS, RETRACT_SPEED);
    }
  }
  
}

/*
 * This function rotates the stepper motor a specified number
 * of microsteps at the given speed.
 * @param steps The number of microsteps to move
 * @param speed The spped to move at
 */
void rotate(int steps, float speed){ 
  int dir = (steps > 0) ? HIGH : LOW;
  steps = abs(steps);

  digitalWrite(DIR_PIN, dir); 

  float usDelay = (1/speed) * 70;

  for(int i=0; i < steps; i++){ 
    digitalWrite(STEP_PIN, HIGH); 
    delayMicroseconds(usDelay); 

    digitalWrite(STEP_PIN, LOW); 
    delayMicroseconds(usDelay); 
  } 
}
