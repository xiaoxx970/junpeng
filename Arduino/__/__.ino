int stp = 2;
int dir = 5;
int en = 8;
int x;
void setup() {
  // put your setup code here, to run once:
  pinMode(en,OUTPUT); // Enable: EN可以使用单片机端口控制，也可以直接连接GND使能

  pinMode(stp,OUTPUT); // steps:脉冲个数

  pinMode(dir,OUTPUT); // dir:为方向控制

  digitalWrite(en,LOW); // Set Enable low
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(dir,HIGH); // Set Dir high

  for(x = 0; x < 200; x++) // Loop 200 times

  {

      digitalWrite(stp,HIGH); // Output high

      delayMicroseconds(800); // Wait 1/2 a ms

      digitalWrite(stp,LOW); // Output low

      delayMicroseconds(800); // Wait 1/2 a ms

    }

  delay(1000); // pause one second

  

  digitalWrite(dir,LOW); // Set Dir low

  

  for(x = 0; x < 200; x++) // Loop 2000 times

  {

      digitalWrite(stp,HIGH); // Output high

      delayMicroseconds(800); // Wait 1/2 a ms

      digitalWrite(stp,LOW); // Output low

      delayMicroseconds(800); // Wait 1/2 a ms

    }

    delay(1000); // pause one second
}
