/*
 * File:   steppermotor.ino
 * Author: Yuki Miyakoshi
 */
 
/*
 * ステッピングモーターを回転させる関数
 * turnStepperMotor(int excitation, bool isForward, int motorPinNumber)
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
 * 引数:motorPinNumber ステッピングモータのPIN番号;
 * 
 * 返り値:
 * なし
 * 
 * motorPIN_output[][] 返り値はありませんが、この配列にbool値が代入されます。
 * 例
 * 1-2相励磁,正回転,3番目のモータの場合
 * turnStepperMotor(3,true,2);
 * digitalWrite(2,motorPIN_output[2][0]);
 * digitalWrite(3,motorPIN_output[2][1]);
 * digitalWrite(4,motorPIN_output[2][2]);
 * digitalWrite(5,motorPIN_output[2][3]);

 */