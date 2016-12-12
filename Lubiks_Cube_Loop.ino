#define INPUT_INTERVAL 200 // 입력 간격은 0.2초로 한다.

void loop() {
  currentTime = millis(); // 아두이노에 전원이 들어간 이후 시간을 측정한다.
  
  byte btn_p = digitalRead(btn_power); // POWER 버튼과 START 버튼의 입력값을 읽는다.
  byte btn_f = digitalRead(btn_funtion);

  int R = analogRead(joy[0]); // 조이스틱값을 읽는다.
  int U = analogRead(joy[1]);
  int L = analogRead(joy[2]);
  int D = analogRead(joy[3]);
  int F = analogRead(joy[4]);
  int M = analogRead(joy[5]);
  int X = analogRead(joy[6]);
  int Y = analogRead(joy[7]);

  if((unsigned long)currentTime - previousTime > INPUT_INTERVAL) { // 0.2초 이상 시간이 지났을 때만 입력을 받음.
    btnInput(btn_p, btn_f); // 버튼 입력값을 함수에 전달한다.
    if(solving == true) { joyInput(R, U, L, D, F, M, X, Y); } // 큐브맞추기가 시작되었으면 조이스틱 입력값을 전달한다.
  }
  
  if(power == true) // 파워 온 인 경우에만 큐브를 갱신한다.
    setCube(); // 큐브를 갱신한다.
}
