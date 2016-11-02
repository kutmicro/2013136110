#include <LiquidCrystal.h> // LCD 라이브러리 헤더파일 추가.

LiquidCrystal lcd(3,4,10,11,12,13); // LCD에 사용할 디지털 핀. 핀은 LCD 의 데이터버스에 연결되어있다.

byte data; // 시리얼 통신을 통해 받아온 데이터를 저장할 변수.
String msg; // LCD에 출력할 문자열 객체 

void setup() {
  Serial.begin(9600); // 시리얼통신 설정. 매개변수로 초당 전송 비트수(baud)를 설정.
  lcd.begin(16,2); // lcd를 초기화함. 매개변수로 가로, 세로를 받는다. (16x2 LCD 생성)
  lcd.clear(); // lcd의 화면을 지우고 커서를 처음 자리로 옮긴다. (0,0)
  lcd.print("< LCD Practice >"); // 최초의 위치에 문자열을 출력한다. (현재는 연습)
  pinMode(A5,OUTPUT); // 가변저항이 없으므로 LCD의 3번핀을 아날로그에 연결하여 전압값을 조절한다.
  analogWrite(A5,120); // 아날로그 A5핀에 아날로그값 120만큼의 전압을 출력한다.
}

void printLCD(String msg = "") // 문자열 객체를 전달받아 LCD에 설정해주는 함수.
{
   lcd.clear(); // LCD화면을 지운다.
   lcd.print("< LCD Practice >"); // 최초의 위치에 문자열을 출력한다. (현재는 연습)
   lcd.setCursor(0,1); // LCD의 커서를 0,1 로 옮긴다. 매개변수로 (가로위치,세로위치)를 받는다.
   lcd.print(msg); // 문자열 출력. 최초엔 "" 로 아무것도 출력하지 않고, 데이터를 받은 이후에 결정된 문자열을 계속 출력.
}

void loop() {

 if( Serial.available() ) { // 아두이노 버퍼에서 64바이트까지 읽어오며, 읽어올 byte 없으면 -1을 반환한다. 즉 받아올 데이터가 있을때 동작하도록 한다.
    data = Serial.read(); // 아두이노 버퍼에서 64바이트까지 데이터를 읽온 뒤 삭제하고 반환한다. 데이터가 없으면 -1을 반환한다.
    
    if(data == '0') { msg = "Do not scramble."; printLCD(msg); } // 값에 따라 문자열을 설정하고 lcd에 출력한다.
    else if(data == '1') { msg = "Solving start."; printLCD(msg); }
    else if(data == '2') { msg = "Complete."; printLCD(msg); }
    else if(data == '3') { msg = "Not Complete."; printLCD(msg); }
    else if(data == '4') { msg = "Cube scramble."; printLCD(msg); }
    else if(data == '5') { msg = "Alredy scramble."; printLCD(msg); }
    else if(data == '6') { msg = "Alredy Start."; printLCD(msg); }
 }
 delay(500);
}
