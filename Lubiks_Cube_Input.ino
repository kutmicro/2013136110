void btnInput(byte btn_p, byte btn_f)
{
   if(btn_p == 1) // 파워버튼
  {
    if(power == false) // 파워 오프인 경우
    {
      Serial.print('0');
      setupBlock(); // 온되면 블럭 최초상태로 초기화
      copyBlockAll();
      powerOnCube();
      power = true; // 파워 온으로 바꿔줌
    }
    
    else // 파워 온인 경우
    {
      Serial.print('8');
      powerOffCube();
      power = false; // 파워 오프로 바꿔줌
      start = false; // 시작 취소
      solving = false; // 솔빙 취소
    }
  }
  
  else if(power == true && btn_f == 1) // 파워 온 상태에서 동작버튼 누른경우
  {
    if(start == false) // 큐브 맞추기 시작 전
    {
      Serial.print(2);
      scrambleCube();
      start = true; // 섞기 후 솔빙 시작
    }

    else if(start == true && solving == false)
    {
      Serial.print(4);
      solving = true;
    }
    else if(solving == true) // 큐브맞추기 시작 후
    {
      if(checkCube() == true) // 큐브상태를 검사하여 다맞춘 경우
      { 
        Serial.print(6);
        start = false;
        solving = false;
      }
      else // 다 맞추지 못한경우.
        Serial.print(7);
    }
  }
  previousTime = currentTime; // 입력받은 후의 시간을 previousTime 으로 저장.
}

void joyInput(int R,int U, int L, int D, int F, int M, int X, int Y) // 조이스틱별로 입력을 받아 케이스 저장함수.
{
  byte select = -1; // 0 ~ 13 R/U/F/L/D/B/M 14~17 X/Y
  
  if(R == 0) select = 0; // R
  else if(R == 1023) select = 1; // Rp
  
  else if(U == 0) select = 2; // U
  else if(U == 1023) select = 3; // Up
  
  else if(F == 0) select = 4; // F
  else if(F == 1023) select = 5; // Fp
  
  else if(L == 0) select = 6; // Lp
  else if(L == 1023) select = 7; // L
  
  else if(D == 0) select = 8; // D
  else if(D == 1023) select = 9; // Dp
  
  else if(M == 0) select = 12; // M
  else if(M == 1023) select = 13; // Mp
  
  else if(X == 1023) select = 14; // X
  else if(X == 0) select = 15; // Xp
  
  else if(Y == 1023) select = 16; // Y
  else if(Y == 0) select = 17; // Yp

  rotationCube(select); // 저장된 케이스를 함수에 전달하여 큐브 회전
  previousTime = currentTime; // 입력받은 후의 시간을 previousTime 으로 저장.
}

