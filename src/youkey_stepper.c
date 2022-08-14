/*
 * File:   youkey_stepper.c
 * Author: Yuki Miyakoshi
 */
 
/*
 * ステッピングモーターを回転させる関数
 * youkey_turnStepperMotor(int excitation, bool isForward, int motorPinNumber)

 * 引数:excitation 励磁方式 
 *  0, 無回転
 *  1, 1-1相励磁
 *  2, 2-2相励磁
 *  3, 1-2相励磁
 * 
 * 引数:isForward 正転か逆転かどうか 
 *  true, 正転
 *  false, 逆転 
 * 
 * 引数:motorPinNumber ステッピングモータの番号
 * (あなたがモータに番号をつけてください。1個だけモータを使っていたら0です。)
 * 
 * 返り値:
 * なし
 * 
 */

#include "stepper.h"

static int count[3] = {0,0,0};
static bool isHalf[3] = {true,true,true};
static int motorPIN_output[3] = {0,0,0};

static void onePhaseOn(bool isForward, int motorPinNumber);
static void twoPhaseOn(bool isForward, int motorPinNumber);

static void countUp(bool isForward, int motorPinNumber);
static void setMotorPinOutput(int motorPinNumber);

int youkey_getStepperBit(int motorPinNumber){
  return motorPIN_output[motorPinNumber];
}

void youkey_turnStepperMotor(int excitation, bool isForward, int motorPinNumber){
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


static void onePhaseOn(bool isForward, int motorPinNumber){
  output[motorPinNumber] = 0x01 << count[motorPinNumber] ;
  setMotorPinOutput(motorPinNumber);

  countUp(isForward, motorPinNumber);

}

static void twoPhaseOn(bool isForward, int motorPinNumber){
  
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

static void countUp(bool isForward, int motorPinNumber){

  if(isForward){
    count[motorPinNumber] = (count[motorPinNumber] != 3) ? count[motorPinNumber] + 1 : 0 ;
  }else{
    count[motorPinNumber] = (count[motorPinNumber] != 0) ? count[motorPinNumber] - 1 : 3 ;
  }

}