/*
 * File:   youkey_stepper.c
 * Author: Yuki Miyakoshi
 */
 
/*
 * Function to rotate a stepper motor
 * Up to three motors can be run at the same time
 * ステッピングモーターを回転させる関数
 * 同時に動かせるモータは３個までです
 * youkey_turnStepperMotor(int excitation, _Bool isForward, int motorPinNumber)
 *
 * Argument:excitation Excitation method 
 * 引数:excitation 励磁方式 
 *  0, no-rotation 無回転
 *  1, 1-1 phase excitation 1-1相励磁
 *  2, 2-2 phase excitation 2-2相励磁
 *  3, 1-2 phase excitation 1-2相励磁
 * 
 * Argument:isForward Whether forward or reverse
 * 引数:isForward 正転か逆転かどうか 
 *  true, 正転
 *  false, 逆転 
 * 
 * Argument: motorPinNumber Number of the stepping motor
 * (You number the motors, e.g., 0 for motor #1, 1 for motor #2, 2 for motor #3, etc.)
 * 引数:motorPinNumber ステッピングモータの番号
 * (あなたがモータに番号をつけてください。1番モータは0,2番モータは1,3番モータは2のように)
 * 
 * 返り値:
 * なし
 * 
 */

#include <youkey_stepper.h>

static int count[3] = {0,0,0};
static _Bool isHalf[3] = {1,1,1};
static int motorPIN_output[3] = {0,0,0};

static void onePhaseOn(_Bool isForward, int motorPinNumber);
static void twoPhaseOn(_Bool isForward, int motorPinNumber);

static void countUp(_Bool isForward, int motorPinNumber);
static void setMotorPinOutput(int motorPinNumber);

int youkey_getStepperBit(int motorPinNumber){
  return motorPIN_output[motorPinNumber];
}

void youkey_turnStepperMotor(int excitation, _Bool isForward, int motorPinNumber){
	switch (excitation){
  case 0:
    break;
    
	case 1:
		{
			onePhaseOn(isForward, motorPinNumber);
		}
		break;

	case 2:
		{
			twoPhaseOn(isForward, motorPinNumber);
		}
		break;

	case 3:
		{
      if (isHalf[motorPinNumber]){
        onePhaseOn(isForward, motorPinNumber);
        if(isForward){
          count[motorPinNumber] = (count[motorPinNumber] != 0) ? count[motorPinNumber] - 1 : 3 ;
        }      
      }else{
        twoPhaseOn(isForward, motorPinNumber);
        if(!isForward){
          count[motorPinNumber] = (count[motorPinNumber] != 3) ? count[motorPinNumber] + 1 : 0 ;
        }
      }
      isHalf[motorPinNumber] = !isHalf[motorPinNumber] ;
      
		}
		break;
	}

}

static int output[3];


static void onePhaseOn(_Bool isForward, int motorPinNumber){
  output[motorPinNumber] = 0x01 << count[motorPinNumber] ;
  setMotorPinOutput(motorPinNumber);

  countUp(isForward, motorPinNumber);

}

static void twoPhaseOn(_Bool isForward, int motorPinNumber){
  
  output[motorPinNumber] = (count[motorPinNumber] != 3) ? 0x03 << count[motorPinNumber] : 0x09 ;
  setMotorPinOutput(motorPinNumber);

  countUp(isForward, motorPinNumber);

}

static void setMotorPinOutput(int motorPinNumber){
  motorPIN_output[motorPinNumber] = 0x00;
  if( output[motorPinNumber] & 0x01 ){ motorPIN_output[motorPinNumber] =  motorPIN_output[motorPinNumber] | 0x01 ;}
  if( output[motorPinNumber] & 0x02 ){ motorPIN_output[motorPinNumber] =  motorPIN_output[motorPinNumber] | 0x02 ;}
  if( output[motorPinNumber] & 0x04 ){ motorPIN_output[motorPinNumber] =  motorPIN_output[motorPinNumber] | 0x04 ;}
  if( output[motorPinNumber] & 0x08 ){ motorPIN_output[motorPinNumber] =  motorPIN_output[motorPinNumber] | 0x08 ;}

};

static void countUp(_Bool isForward, int motorPinNumber){

  if(isForward){
    count[motorPinNumber] = (count[motorPinNumber] != 3) ? count[motorPinNumber] + 1 : 0 ;
  }else{
    count[motorPinNumber] = (count[motorPinNumber] != 0) ? count[motorPinNumber] - 1 : 3 ;
  }

}