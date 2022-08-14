/* 
 * File:   youkey_stepper.h
 * Author: Yuki Miyakoshi
 */

#ifndef STEPPER_H
#define	STEPPER_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

int youkey_getStepperBit(int motorPinNumber);
void youkey_turnStepperMotor(int excitation, _Bool isForward, int motorPinNumber);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

