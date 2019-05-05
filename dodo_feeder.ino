/*
 * Maf,2019-4-22
 * DODO Feeder
 * 
 * A4988说明
 * MS1,MS2,MS3跳线说明：（例子里是低电平，悬空或接地线，使用全步进模式）
 * 分别是全步进，1/2步进，1/4步进，1/8步进，1/16步进模式。
 * 步进电机走一步是1.8度，一圈就是200步。
 * 例如使用1/16步进，则需要走3200步才等于一圈。
 * 
 * 2019-04-24
 * 加载了StepperDriver库（https://github.com/laurb9/StepperDriver）
 * A4988步进细分
 *  MS1 - D10
 *  MS2 - D11
 *  MS3 - D12
 *  
 * 利用WIFI模块（https://s.click.taobao.com/NyAldBw）控制中间继电器吸合，
 * 来触发动作。
 */

#include <Arduino.h>
#include "A4988.h"
#define MOTOR_STEPS 200  //使用一圈200步的电机
#define DIR 4
#define STEP 5
#define MS1 10
#define MS2 11
#define MS3 12
A4988 stepper(MOTOR_STEPS, DIR, STEP, MS1, MS2, MS3);
int x;
int button = 7;
boolean lastState = LOW;  //记录上次的开关状态，初始化为LOW
boolean toggle = LOW;  //触发信号，初始化为LOW
int bclick = 0;  //开关信号的改变次数，初始化为0

void setup() {
  
  stepper.begin(20, 16);  //设置电机转速为20rpm,细分为16
  stepper.enable();
  pinMode(button,INPUT_PULLUP);  //按钮接内部上拉电阻
  lastState = digitalRead(button);  //读取开关的初始状态值
}

void loop() {
  // put your main code here, to run repeatedly:
  boolean b1 = digitalRead(button);  //读取目前的开关状态
  
  if(b1 != lastState)  //如果开关值变化
  {
    delay(100);  //去震动
    boolean b2 = digitalRead(button);  //再读取一次开关值

    if(b2 == b1)  //确认两次读取开关值一致
    {
      lastState = b1;  //存储开关状态
      bclick++;  //次数累计
    }
  }
  
  if(bclick == 2)  //如果开关状态改变2次
  {
    bclick = 0;  //归零
    toggle = !toggle;  //触发信号取相反值
    stepper.rotate(60/11.25*40);
    delay(1000);
  }
}
