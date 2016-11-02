int btn_start = 8; // 시작, 종료 버튼을 디지털 8번에 연결하기 위해 8로 초기화.
int btn_scramble = 9; // 섞기 버튼을 디지털 9번에 연결하기 위해 9로 초기화.

void setup() {
  
  pinMode(btn_start,INPUT); // 디지털 8번 핀을 INPUT으로 설정함.
  pinMode(btn_scramble,INPUT); // 디지털 9번 핀을 INPUT으로 설정함.
  Serial.begin(9600); // 시리얼통신 설정. 매개변수로 초당 전송 비트수(baud)를 설정.

}

void loop() {

  int btn_sc = digitalRead(btn_scramble); // 디지털 핀 9번에서 값을 읽어와 상태를 btn_sc에 저장.
  int btn_st = digitalRead(btn_start); // 디지털 핀 8번에서 값을 읽어와 상태를 btn_st에 저장.

  if(btn_st == 1) // 시작버튼 누른경우.
  {
    if(start == false) // 시작하지 않은 경우
    {
      if(finish == true) { Serial.write('0'); } // LCD에서 "Do not scramble." 출력. 시작하지 않음. 시리얼로 '0'을 전달.
      else { start = true; Serial.write('1'); } // LCD에서 "Solving start." 출력. 시작함. 시리얼로 '1'을 전달.
    }
    
    else // 시작한 경우
    {
      finish = checkCube();
      if(finish == true) { start = false; Serial.write('2'); } // LCD에서 "Complete." 출력. 완성 시리얼로 '2'를 전달.
      else { finish = true; Serial.write('3'); } // LCD에서 "Not Complete." 출력. 미완성. 시리얼로 '3'을 전달.
    }
  }
  
  if(btn_sc == 1) // 섞기버튼 누른경우.
  {
    if(start == false) // 시작하지 않은 경우
    {
      if(finish == true) { finish = false; Serial.write('4'); } // LCD에서 "Cube scramble." 출력. 다 맞춰져있으면 큐브섞음. 시리얼로 '4'전달.
      else { Serial.write('5'); } // LCD에서 "Alredy scramble." 출력. 섞기버튼은 이미 큐브를 섞은 경우 동작하지 않음.시리얼로 '5'전달.
    }
    else // 시작한 경우
      { Serial.write('6'); } // LCD에서 "Alredy Start." 출력. 맞추기 시작했으면 섞기버튼은 동작하지 않음. 시리얼로 '6' 전달.
  }
  delay(1000);
}
