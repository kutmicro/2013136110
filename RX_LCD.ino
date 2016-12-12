#include <LiquidCrystal.h> // LCD 라이브러리 헤더파일 추가.

LiquidCrystal lcd(5, 6, 7, 8, 9, 10); // LCD에 사용할 디지털 핀. 핀은 LCD 의 데이터버스에 연결되어있다.

byte data; // 시리얼 통신을 통해 받아온 데이터를 저장할 변수.
int save; // lcd 출력 케이스를 저장할 변수

bool isAvailable() // 시리얼통신으로 받아올 데이터가 있는지 반환.
{
  return Serial.available() > 0; // 0보다 큰 값이 반환되면 데이터가 있으므로 true, -1인 경우 데이터가 없는 경우이다.
}

void printLCD(String msg = "", int k=0, int de = 200) // 문자열을 전달받아 LCD에 설정해주는 함수.
{
   lcd.clear(); // LCD화면을 지운다.
   lcd.print("< Lubik's Cube >"); // 최초의 위치에 문자열을 출력한다. (현재는 연습)
   lcd.setCursor(k,1); // LCD의 커서를 k,1 로 옮긴다. 매개변수로 (가로위치,세로위치)를 받는다.
   lcd.print(msg); // 문자 출력. 최초엔 "" 로 아무것도 출력하지 않고, 데이터를 받은 이후에 결정된 문자열을 계속 출력.
   if(isAvailable() == true) return; // 출력 도중 다른 문구 데이터를 받으면 함수 중단.
   delay(de); // 원하는 de만큼 delay
}

void printLCD(char msg, int k=0, int de = 200) // 문자 한개를 전달받아 LCD에 설정해주는 함수.
{
   lcd.clear(); // LCD화면을 지운다.
   lcd.print("< Lubik's Cube >"); // 최초의 위치(0,0)에 문자열을 출력한다. (현재는 연습)
   lcd.setCursor(k,1); // LCD의 커서를 k,1 로 옮긴다. 매개변수로 (가로위치,세로위치)를 받는다.
   lcd.print(msg); // 문자 출력.
   if(isAvailable() == true) return; // 출력 도중 다른 문구 데이터를 받으면 함수 중단.
   delay(de); // 원하는 de만큼 delay
}

// 각각의 케이스에 대해 LCD의 문자열을 출력하는 함수들.

void printPressPower() // Press Power 출력 save = 9
{
  printLCD("Press POWER!", 2, 400);
  printLCD("", 0, 400);
}
void printCubeOn() // Wait -> Cube On 출력 save = 0
{
  String str = "Wait............";
  printLCD();
  for(int i = 0; i < 16; i++)
  {
    lcd.setCursor(i,1);
    lcd.print(str[i]);
    if(isAvailable() == true) return; // 출력 도중 다른 문구 데이터를 받으면 함수 중단.
    delay(500);
  }
  printLCD("Cube", 4, 1000);
  printLCD("Cube On!", 4, 1000);
}

void printCubeOff() // Cube off 출력 save = 8
{
  printLCD("Cube Off....",2,500);

  for(int i = 2; i <= 13; i++)
  {
    lcd.setCursor(i,1);
    lcd.print(' ');
    if(isAvailable() == true) return;
    delay(100);
  }
}

void printPressStart() // Press Start 출력 save = 1
{
  printLCD("Press START!",2,400);
  printLCD("",0,400);
}

void printReady()
{
  printLCD("Are You READY?", 1, 1000);
  printLCD("Press START!",2,1000);
}
void printStart()  //Ready가 끝나면 Solving Start 출력 save = 4
{
  printLCD("Solving", 1, 500);
  printLCD("Solving Start!", 1, 1000);
  printLCD();
}

void printSU() // SUCESS 출력 save = 6
{
  char msg[] = "SUCESS";
  for(int i = 0; i < 2; i++) {
    for(int j = 0; j <6; j++)
    {
      printLCD(msg[j], j+5,200);
      printLCD();
    }
     printLCD("SUCESS",5);
     printLCD();
     printLCD("SUCESS",5,400);
     printLCD();
  }
}

void printSol() // Solving 출력 sava = 5
{
 for(int i = 0; i < 10; i++)
  printLCD("Solving",i);
  
 for(int i = 8; i >0; i--)
  printLCD("Solving",i);
}

void printNC()
{
  for(int i = 0; i < 3; i++) 
  {
    printLCD("Not Sucess",3,400);
    printLCD("",0,400);
  }
}

void printCS() // Scrambling 출력 save = 2 
{
  String str = "Scrambling";
  printLCD();
    for(int i = 3; i<= 12; i++)
    {
      lcd.setCursor(i,1);
      lcd.print(str[i-3]);
      if(isAvailable() == true) return; // 출력 도중 다른 문구 데이터를 받으면 함수 중단.
      delay(100);
    }

     for(int i = 3; i<= 12; i++)
    {
      lcd.setCursor(i,1);
      lcd.print(' ');
      if(isAvailable() == true) return; // 출력 도중 다른 문구 데이터를 받으면 함수 중단.
      delay(100);
    }
}

// 시리얼통신으로 받은 데이터 저장 함수
void setData(char data)
{
    if(data == '0') { save = 0; } // Cube On
    else if(data == '1') { save = 1; } // Press Start
    else if(data == '2') { save = 2; } // Scrambling
    else if(data == '3') { save = 3; } // Ready
    else if(data == '4') { save = 4; } // Solving Start
    else if(data == '5') { save = 5; } // Solving
    else if(data == '6') { save = 6; } // Success
    else if(data == '7') { save = 7; } // Not Success
    else if(data == '8') { save = 8; } // Cube Off
    else { save = 9; }
}

void setLCD(byte save) 
{
 switch(save) // 저장된 케이스에 따라 함수를 호출하여 메세지 출력. 다음 케이스가 되기 전까지 반복된다.
 {
  case 0 : printCubeOn(); setData('1'); break;
  case 1 : printPressStart(); break;
  case 2 : printCS(); setData('3'); break;
  case 3 : printReady(); break;
  case 4 : printStart(); setData('5'); break;
  case 5 : printSol(); break;
  case 6 : printSU(); setData('1'); break;
  case 7 : printNC(); setData('5'); break;
  case 8 : printCubeOff(); setData('9'); break;
  case 9 : printPressPower(); break;
 }  
}

void getData() {
   if( Serial.available() ) { // 아두이노 버퍼에서 64바이트까지 읽어오며, 읽어올 byte 없으면 -1을 반환한다. 즉 받아올 데이터가 있을때 동작하도록 한다.
    data = Serial.read(); // 아두이노 버퍼에서 64바이트까지 데이터를 읽온 뒤 삭제하고 반환한다. 데이터가 없으면 -1을 반환한다.
    setData(data);
 }
}

// 셋업
void setup() {
   // 시리얼통신 설정. 매개변수로 초당 전송 비트수(baud)를 설정.
  Serial.begin(9600);
  lcd.begin(16,2); // lcd를 초기화함. 매개변수로 가로, 세로를 받는다. (16x2 LCD 생성)
  pinMode(A5,OUTPUT); // 가변저항이 없으므로 LCD의 3번핀을 아날로그에 연결하여 전압값을 조절한다.
  analogWrite(A5,120); // 아날로그 A5핀에 아날로그값 120만큼의 전압을 출력한다.
  save = 9; // 최초상태는 대기상태로 초기화.
}

// 루프
void loop() {
  getData(); // 시리얼통신으로 데이터를 받아서 처리한다.
  setLCD(save);  // 처리된 데이터를 사용하여 LCD에 문구를 출력한다.
}


