#define INPUT_INTERVAL 300 // 입력간 간격을 0.3ms 로 상수로 정의한다.

byte joy[8] = { A0, A1, A2, A3, A4, A5, A6, A7 }; // RU(01) FM(23) LD(45) XY(67) 에 사용될 아날로그핀 8개

unsigned long previousTime = 0,currentTime; // 시간을 측정할 변수를 선언한다. 이전시간은 0으로 초기화한다.
void joyInput(int R,int U, int L, int D, int F, int M, int X, int Y) // 조이스틱 입력을 전달받아 처리하는 함수이다.
{
  byte select = -1; // 0 ~ 13 R/U/F/L/D/B/M 14~17 X/Y // 최초는 -1로 초기화하여 아무 동작도 하지 않는다.
  
  if(R == 1023) Serial.println("R");
  else if(R == 0) Serial.println("Rp");
  
  else if(U == 0) Serial.println("U");
  else if(U == 1023) Serial.println("UP");
  
  else if(F == 1023) Serial.println("F");
  else if(F == 0) Serial.println("Fp");
  
  else if(L == 0) Serial.println("Lp");
  else if(L == 1023) Serial.println("L");
  
  else if(D == 1023) Serial.println("D");
  else if(D == 0) Serial.println("Dp");
  
  else if(M == 0) Serial.println("M");
  else if(M == 1023) Serial.println("Mp");
  
  else if(X == 1023) Serial.println("X");
  else if(X == 0) Serial.println("Xp");
  
  else if(Y == 0) Serial.println("Y");
  else if(Y == 1023) Serial.println("Yp"); // 각각의 케이스 출력.
  previousTime = currentTime; // 이전 시간을 현재까지의 시간으로 초기화. 타이머가 리셋되는 효과를 가짐.
}

void setup() {
    for(byte i = 0; i < 8; i++)
      pinMode(joy[i],INPUT); // 아날로그핀을 입력으로 설정

}

void loop() {
  currentTime = millis(); // 프로그램이 시작 된 이후부터 시간을 측정한다.

  int R = analogRead(joy[0]);
  int U = analogRead(joy[1]);
  int L = analogRead(joy[2]);
  int D = analogRead(joy[3]);
  int F = analogRead(joy[4]);
  int M = analogRead(joy[5]);
  int X = analogRead(joy[6]);
  int Y = analogRead(joy[7]); // 각각의 조이스틱에서 값을 읽어서 저장한다.
  
  if((unsigned long)currentTime - previousTime > INPUT_INTERVAL) // 현재의 시간과 이전의 시간의 차이가 300 보다 클 때, 즉 입력한지 0.3초가 흘러야 재입력으로 인식한다.
  {
     joyInput(R, U, L, D, F, M, X, Y);
  }
}
