#include <LiquidCrystal.h> // LCD 라이브러리 헤더파일 추가.

LiquidCrystal lcd(3,4,10,11,12,13); // LCD에 사용할 디지털 핀. 핀은 LCD 의 데이터버스에 연결되어있다.

byte data; // 시리얼 통신을 통해 받아온 데이터를 저장할 변수.
int save; // lcd 출력 케이스를 저장할 변수

void printLCD(String msg = "", int k=0, int de = 200) // 문자열을 전달받아 LCD에 설정해주는 함수.
{
   lcd.clear(); // LCD화면을 지운다.
   lcd.print("< Lubik's Cube >"); // 최초의 위치에 문자열을 출력한다. (현재는 연습)
   lcd.setCursor(k,1); // LCD의 커서를 k,1 로 옮긴다. 매개변수로 (가로위치,세로위치)를 받는다.
   lcd.print(msg); // 문자 출력. 최초엔 "" 로 아무것도 출력하지 않고, 데이터를 받은 이후에 결정된 문자열을 계속 출력.
   delay(de); // 전달받은 값 만큼 딜레이.
}

void printLCD(char msg, int k=0, int de = 200) // 문자 한개를 전달받아 LCD에 설정해주는 함수.
{
   lcd.clear(); // LCD화면을 지운다.
   lcd.print("< Lubik's Cube >"); // 최초의 위치에 문자열을 출력한다. (현재는 연습)
   lcd.setCursor(k,1); // LCD의 커서를 k,1 로 옮긴다. 매개변수로 (가로위치,세로위치)를 받는다.
   lcd.print(msg); // 문자 출력.
   delay(de); // 전달받은 값 만큼 딜레이.
}
// 각각의 케이스에 대해 LCD의 문자열을 출력하는 함수들.
void printSU()
{
  char msg[] = "SUCESS";
  for(int i = 0; i <6; i++)
  {
    printLCD(msg[i], i+5,80);
    printLCD();
  }
    printLCD("SUCESS",5);
    printLCD();
    printLCD("SUCESS",5,400);
}

void printPS()
{
  printLCD("Plz Scramble",2,400);
  printLCD("",0,400);
}

void printSol()
{
 for(int i = 0; i < 10; i++)
  printLCD("Solving",i);
  
 for(int i = 8; i >0; i--)
  printLCD("Solving",i);
}

void printNC()
{
  printLCD("Not Sucess",3,400);
  printLCD("",0,400);
}

void printCS()
{
  printLCD("Cube Scrambled",1,400);
  printLCD("",0,400);
}

void printAS()
{
  printLCD("Alredy scrambled",0,400);
  printLCD("",0,400);
}

void printAT()
{
  printLCD("Alredy Started",1,400);
  printLCD("",0,400);
}

void setup() {
  Serial.begin(9600); // 시리얼통신 설정. 매개변수로 초당 전송 비트수(baud)를 설정.
  lcd.begin(16,2); // lcd를 초기화함. 매개변수로 가로, 세로를 받는다. (16x2 LCD 생성)
  lcd.clear();
  lcd.print("< Lubik's Cube > ");
  pinMode(A5,OUTPUT); // 가변저항이 없으므로 LCD의 3번핀을 아날로그에 연결하여 전압값을 조절한다.
  analogWrite(A5,120); // 아날로그 A5핀에 아날로그값 120만큼의 전압을 출력한다.
  save = 7;
}

void loop() {
 if( Serial.available() ) { // 아두이노 버퍼에서 64바이트까지 읽어오며, 읽어올 byte 없으면 -1을 반환한다. 즉 받아올 데이터가 있을때 동작하도록 한다.
    data = Serial.read(); // 아두이노 버퍼에서 64바이트까지 데이터를 읽온 뒤 삭제하고 반환한다. 데이터가 없으면 -1을 반환한다.
    
    if(data == '0') { save = 0; } // 값에 따라 출력할 케이스를 저장.
    else if(data == '1') { save = 1; }
    else if(data == '2') { save = 2; }
    else if(data == '3') { save = 3; }
    else if(data == '4') { save = 4; }
    else if(data == '5') { save = 5; }
    else if(data == '6') { save = 6; }
 }
 switch(save) // 저장된 케이스에 따라 함수를 호출하여 메세지 출력. 다음 케이스가 되기 전까지 반복된다.
 {
  case 0 : printPS(); break;
  case 1 : printSol(); break;
  case 2 : printSU(); break;
  case 3 : printNC(); break;
  case 4 : printCS(); break;
  case 5 : printAS(); break;
  case 6 : printAT(); break;
 }
}
