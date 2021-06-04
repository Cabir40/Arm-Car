#include <Servo.h>

Servo motor_1; // servo motorları tanımlıyoruz
Servo motor_2;
Servo motor_3;
Servo motor_4;

#define enA 4  //Enable1 L298 Pin enA 
#define in1 A3 //Motor1  L298 Pin in1 
#define in2 A2 //Motor1  L298 Pin in2 
#define in3 A1 //Motor2  L298 Pin in3 
#define in4 A0 //Motor2  L298 Pin in4 
#define enB 5  //Enable2 L298 Pin enB 

int servo1 = 90;
int servo2 = 90;
int servo3 = 90;
int servo4 = 40;

int bt_data;
int Speed = 150;

void setup(){
  
  Serial.begin(9600); // serial communication at 9600 bits per second:
   
  motor_1.attach(8);  // aç kapa
  motor_2.attach(9);  // sağ sol
  motor_3.attach(6);  // yukarı aşağı
  motor_4.attach(7);  // ileri geri
  
  motor_1.write(servo1); 
  motor_2.write(servo2); 
  motor_3.write(servo3); 
  motor_4.write(servo4); 
  
  pinMode(enA, OUTPUT); // L298 için çıkış Pin enA 
  pinMode(in1, OUTPUT); // L298 için çıkış Pin in1 
  pinMode(in2, OUTPUT); // L298 için çıkış Pin in2 
  pinMode(in3, OUTPUT); // L298 için çıkış Pin in3   
  pinMode(in4, OUTPUT); // L298 için çıkış Pin in4 
  pinMode(enB, OUTPUT); // L298 için çıkış Pin enB
  
  delay(1000);
}

void loop(){


  if(Serial.available() > 0){     
    bt_data = Serial.read(); 
    Serial.println(bt_data);
    if(bt_data > 20){Speed = bt_data;}      
  }
  
  analogWrite(enA, Speed); // 0 to 255 Enable Pin A for Motor1 Speed 
  analogWrite(enB, Speed); // 0 to 255 Enable Pin B for Motor2 Speed 


       if(bt_data == 4){forword(); }  // if the bt_data is '1' the DC motor will go forward
  else if(bt_data == 3){backword();}  // if the bt_data is '2' the motor will Reverse
  else if(bt_data == 2){turnLeft();}  // if the bt_data is '3' the motor will turn left
  else if(bt_data == 1){turnRight();} // if the bt_data is '4' the motor will turn right
  else if(bt_data == 5){Stop(); }     // if the bt_data '5' the motor will Stop

  else if(bt_data == 6){turnLeft();  delay(400);  bt_data = 5;}
  else if(bt_data == 7){turnRight(); delay(400);  bt_data = 5;}   

  else if (bt_data == 8){
    if(servo1<150){servo1 = servo1+1;}
    motor_1.write(servo1); 
    delay(10); 
  }
  else if (bt_data == 9){
    if(servo1>30){servo1 = servo1-1;} 
    motor_1.write(servo1); 
    delay(10); 
  }
  
  else if (bt_data == 10){
    if(servo2>60){servo2 = servo2-1;}
    motor_2.write(servo2);
    delay(10);
  }
  else if (bt_data == 11){
    if(servo2<130){servo2 = servo2+1;}
    motor_2.write(servo2);  
    delay(10);
  }
  
  else if(bt_data == 13){              //aşağı
    if(servo3>40){servo3 = servo3-1;}
    motor_3.write(servo3);
    delay(10);
  }
  else if (bt_data == 12){             // yukarı
    if(servo3<130){servo3 = servo3+1;}
    motor_3.write(servo3);
    delay(10);
  }
  
  else if (bt_data == 14){            // ileri
    if(servo4<150){servo4 = servo4+1;}
    motor_4.write(servo4);
    delay(10);
  }
  else if(bt_data == 15){            // geri
    if(servo4>20){servo4 = servo4-1;}
    motor_4.write(servo4);
    delay(10);
  }


  delay(10);
}


void forword(){  //forword
  digitalWrite(in1, HIGH);  
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);  
  digitalWrite(in4, HIGH); 
}

void backword(){ //backword
  digitalWrite(in1, LOW);  
  digitalWrite(in2, HIGH); 
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);  
}

void turnRight(){ //turnRight
  digitalWrite(in1, LOW);  
  digitalWrite(in2, HIGH);   
  digitalWrite(in3, LOW);  
  digitalWrite(in4, HIGH); 
}

void turnLeft(){ //turnLeft
  digitalWrite(in1, HIGH); 
  digitalWrite(in2, LOW);  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);   
}

void Stop(){ //stop
  digitalWrite(in1, LOW); 
  digitalWrite(in2, LOW); 
  digitalWrite(in3, LOW); 
  digitalWrite(in4, LOW); 
}
