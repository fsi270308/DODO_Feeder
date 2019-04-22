/*
 * Maf,2019-4-22
 * DODO Feeder
 */

int x;
int enable = 6;
int sstep = 5;
int dir = 4;
int button = 7;
boolean lastState = LOW;  //记录上次的开关状态，初始化为LOW
boolean toggle = LOW;  //触发信号，初始化为LOW
int bclick = 0;  //开关信号的改变次数，初始化为0

void setup() {
  // put your setup code here, to run once:
  pinMode(enable,OUTPUT);  //Enable
  pinMode(sstep,OUTPUT);  //Step
  pinMode(dir,OUTPUT);  //Dir
  pinMode(button,INPUT_PULLUP);  //按钮接内部上拉电阻
  digitalWrite(enable,LOW);  //Set Enable low,6pin可不接  
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
    digitalWrite(dir,HIGH);  //方向给定
    for(x = 0; x < 200; x++)
    {
      digitalWrite(sstep,HIGH);
      delayMicroseconds(800);
      digitalWrite(sstep,LOW);
      delayMicroseconds(800);
    }
    delay(1000);
  }
}
