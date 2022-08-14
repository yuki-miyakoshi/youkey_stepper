![](https://img.shields.io/github/license/yuki-miyakoshi/youkey_stepper)

# youkey_stepper

This is a library for stepper motors for Arduino and microcontrollers.<br>
Arduinoやマイコン用のステッピングモータ用ライブラリです。

This makes it easy to change the excitation scheme of multiple running stepping motors and adjust the direction and angle of rotation of each.<br>
動作中に複数のステッピングモーターの励磁方式を変更し、それぞれの回転方向や角度を簡単に調整することができます。

# Function Description

## int youkey_getStepperBit(`int motorPinNumber`);
Function to get information whether the stepper motor should rotate or not<br>
ステッピングモータが回転するべきかどうかの情報を取得する関数

### Arguments: `int motorPinNumber` (number the motors, e.g., 0 for motor 1, 1 for motor 2, 2 for motor 3)
Note: Up to 3 motors can run at the same time.<br>
引数:int motorPinNumber モータの番号(モータに番号をつけてください。1番モータは0,2番モータは1,3番モータは2のように)
注意:同時に動かせるモータは３個までです

### RETURN VALUE:
The four bool values totaling whether the motor should rotate or not. Example: If motor #0 is {true,false,false,fals}, then 8 (0b1000 in binary) Refer to examples/stepper/stepper.ino for details.<br>
返り値:
モータが回転するべきかどうかのbool値が4つ合計された状態で出てきます。例:0番のモータが{true,false,false,fals}であれば、8(2進数で0b1000) 詳しくはexamples/stepper/stepper.inoを参照してください。

## void youkey_turnStepperMotor(`int excitation, _Bool isForward, int motorPinNumber`);
Function to rotate a stepper motor<br>
ステッピングモーターを回転させる関数

### Argument: `int excitation` Excitation method 
引数:int excitation 励磁方式<br>
 0, no-rotation 無回転<br>
 1, 1-1 phase excitation 1-1相励磁<br>
 2, 2-2 phase excitation 2-2相励磁<br>
 3, 1-2 phase excitation 1-2相励磁<br>

### Argument: `bool isForward` Whether forward or reverse
引数:bool isForward 正転か逆転かどうか<br>
 true, 正転<br>
 false, 逆転<br>

### Argument: `int motorPinNumber` Number of the stepping motor
(You number the motors, e.g., 0 for motor #1, 1 for motor #2, 2 for motor #3, etc.)<br>
引数:motorPinNumber ステッピングモータの番号
(あなたがモータに番号をつけてください。1番モータは0,2番モータは1,3番モータは2のように)

### Return value:
None<br>
返り値:
なし