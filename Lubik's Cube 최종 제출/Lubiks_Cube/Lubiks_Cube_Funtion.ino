// 핀 초기화 함수
void setStatePin(byte start = 0, byte finish = 9, byte state = 1) 
{
   for(byte i = start; i <= finish; i++) // start핀부터 finish 핀까지 state 상태로 만들어줌.(0-LOW 1-HIGH)
  {
    digitalWrite(rpin[i],state);
    digitalWrite(gpin[i],state);
    digitalWrite(bpin[i],state);
  }
}

void setupPin() // 핀 초기화
{
  pinMode(btn_power,INPUT); // 버튼 핀 초기화
  pinMode(btn_funtion,INPUT);
  
  for(byte i = 0; i < 8; i++) // 조이스틱 초기화
    pinMode(joy[i],INPUT);

  for(byte i=0; i<9; i++) // rgb핀 출력모드로 설정
  {
    rpin[i]=pin_rgb; // 22, 25, 28, 31, 34, 37,40, 43, 46
    gpin[i]=pin_rgb+1; // 23, 26, 29, 32, 35, 38, 41, 44, 47
    bpin[i]=pin_rgb+2; // 24, 27, 30, 33, 36, 39, 42, 45, 48
    pinMode(rpin[i],OUTPUT);
    pinMode(gpin[i],OUTPUT);
    pinMode(bpin[i],OUTPUT);
    pin_rgb=pin_rgb+3;
  }
  
  for(byte i=0; i<6; i++) // 전원핀 출력모드 설정
  {
    zpin[i]=pin_gnd; // 2(R), 3(U), 4(F), 5(L), 6(D), 7(B)
    pinMode(zpin[i],OUTPUT);
    pin_gnd++;
  }
  setStatePin();
}

// -------------------------- 블럭 함수
void setStatus(byte r, byte g, byte b,Block &block)
{
  block.r = r;
  block.g = g;
  block.b = b;
}

void copyBlock(Block &block, Block &copyBlock) // 블럭을 복사하는 함수
{
  block.r = copyBlock.r; // 블럭의 rgb 값을 복사한다.
  block.g = copyBlock.g;
  block.b = copyBlock.b;
}

byte getRStatus(Block block) { return block.r; } // 블럭의 r, g, b 값을 반환받는 함수.
byte getGStatus(Block block) { return block.g; }
byte getBStatus(Block block) { return block.b; }

void setupBlock() // 블럭값 초기화
{
  for(byte i=0; i<4; i++) // 큐브초기화
  {
      setStatus(0,1,1,CL[i]); // 빨
      setStatus(0,0,1,CU[i]); // 노
      setStatus(0,1,0,CR[i]); // 분
      setStatus(0,0,0,CD[i]); // 흰
      setStatus(1,0,1,CF[i]); // 초
      setStatus(1,1,0,CB[i]); // 파

      setStatus(0,1,1,EL[i]);
      setStatus(0,0,1,EU[i]);
      setStatus(0,1,0,ER[i]);
      setStatus(0,0,0,ED[i]);
      setStatus(1,0,1,EF[i]);
      setStatus(1,1,0,EB[i]); // 엣지
  }

  setStatus(0,1,1,LC);
  setStatus(0,0,1,UC);
  setStatus(0,1,0,RC);
  setStatus(0,0,0,DC);
  setStatus(1,0,1,FC);
  setStatus(1,1,0,BC); // 센터
}

void copyBlockAll() // 전체큐브 배열에 각각 블럭을 복사
{
  for(byte i = 0; i<4; i++)
  {
    copyBlock(allBlock[0][i*2], CR[i]); // 빨
    copyBlock(allBlock[1][i*2], CU[i]); // 노
    copyBlock(allBlock[2][i*2], CF[i]); // 초
    copyBlock(allBlock[3][i*2], CL[i]); // 핑
    copyBlock(allBlock[4][i*2], CD[i]); // 흰
    copyBlock(allBlock[5][i*2], CB[i]); // 파

    copyBlock(allBlock[0][i*2+1], ER[i]);
    copyBlock(allBlock[1][i*2+1], EU[i]);
    copyBlock(allBlock[2][i*2+1], EF[i]);
    copyBlock(allBlock[3][i*2+1], EL[i]);
    copyBlock(allBlock[4][i*2+1], ED[i]);
    copyBlock(allBlock[5][i*2+1], EB[i]);
  }
  copyBlock(allBlock[0][8], RC);
  copyBlock(allBlock[1][8], UC);
  copyBlock(allBlock[2][8], FC);
  copyBlock(allBlock[3][8], LC);
  copyBlock(allBlock[4][8], DC);
  copyBlock(allBlock[5][8], BC);
}

// 큐브 제어 함수
void onSide(byte side, int de = 1) // 한 면을 켜주는 함수. 전원공급 문제로 LED를 3개씩 껏다 키는것을 반복.
{
    digitalWrite(zpin[side],HIGH);
    for(int j = 0; j <= 6; j = j+3)
    {
      for(int i = j; i <= j+2; i++)
      {
        digitalWrite(rpin[i], getRStatus(allBlock[side][i]));
        digitalWrite(gpin[i], getGStatus(allBlock[side][i]));
        digitalWrite(bpin[i], getBStatus(allBlock[side][i]));
      }
      delay(de);
      for(int i = j; i <= j+2; i++)
      {
        digitalWrite(rpin[i], 1);
        digitalWrite(gpin[i], 1);
        digitalWrite(bpin[i], 1);
      }
    }
    digitalWrite(zpin[side],LOW);
}

void onBlock(byte side, byte pos, int de = 1) // side 면의 pos 위치 블럭(LED)를 켜주는 함수.
{
    digitalWrite(zpin[side], HIGH);

    digitalWrite(rpin[pos], getRStatus(allBlock[side][pos]));
    digitalWrite(gpin[pos], getGStatus(allBlock[side][pos]));
    digitalWrite(bpin[pos], getBStatus(allBlock[side][pos]));

    delay(de);

    digitalWrite(rpin[pos], 1);
    digitalWrite(gpin[pos], 1);
    digitalWrite(bpin[pos], 1);

    digitalWrite(zpin[side], LOW);
}

void powerOnCube() // 큐브 전원을 켤 때 호출되는 함수.
{
  for(int t = 75; t >= 25; t -= 25)
  {
    for(int i = 0; i < 6; i++)
    for(int j = 0; j < 9; j++)
      onBlock(i, j, t); // 블럭을 하나씩 점점 빠르게 순회함.
  }
  delay(1000); // 다 순회하고 나면 1초 뒤에 큐브가 켜지도록 한다.
}

void onCube() // 큐브 전체를 켜는 함수
{
  for(int i = 0; i < 6; i++) // 한 면씩 총 6면을 킨다.
    onSide(i);
}

void offCube() // 큐브를 끄는 함수.
{
  for(byte i = 0; i < 6; i++) // 전원핀과 모든 rgb핀에 LOW를 줘서 전류가 흐르지 않게하여 큐브를 끈다.
    digitalWrite(zpin[i],LOW);
    setStatePin();
}

void powerOffCube() // 큐브 전원을 끌 때 호출되는 함수
{
  for(int i = 0; i <= 100; i += 5) // 큐브를 깜빡거리게 하여 꺼지는 듯한 시각적 효과 표현
  {
    onCube(); // 큐브 전체를 키고 i만큼의 delay를 주어 점점 느리게 껏다 켜지게 한다.
    delay(i);
  }

  offCube(); // 핀들의 값을 조정하여 전류가 흐르지 않게 한다.
}

void setCube() // 블럭 복사한 뒤 큐브를 켜줌.
{
  copyBlockAll(); // 모든블럭을 복사한다.
  onCube(); // 큐브를 킨다.
}
// -------------------------- 블럭 비교 및 완성상태 검사함수
bool compareBlock(Block b1, Block b2)
{
  if(b1.r == b2.r && b1.g == b2.g && b1.b == b2.b) return true;
  else return false;
}

bool checkCube() // 큐브 상태 확인.
{
  for(byte i=0; i<4; i++)
  {
    if( !compareBlock(CR[i],RC) || !compareBlock(ER[i],RC) 
    ||  !compareBlock(CU[i],UC) || !compareBlock(EU[i],UC) 
    ||  !compareBlock(CF[i],FC) || !compareBlock(EF[i],FC) 
    ||  !compareBlock(CL[i],LC) || !compareBlock(EL[i],LC) 
    ||  !compareBlock(CD[i],DC) || !compareBlock(ED[i],DC) 
    ||  !compareBlock(CB[i],BC) || !compareBlock(EB[i],BC)  ) // 각 면의 코너 또는 엣지 색깔이 다르면 맞춰지지 않은 경우임.
     return false;
  }
  return true;
}

// 여기부터 회전함수
void rotation_R() // 1 = 0, 2 = 1, 3 = 2, 0 = 3
{
  Block tblock = ER[3];
  for(byte i = 3; i >= 1; i--)
    ER[i] = ER[i-1];
  ER[0] = tblock;

  tblock = CR[3];
  for(byte i = 3; i >= 1; i--)
    CR[i] = CR[i-1];
  CR[0] = tblock;

  tblock = EF[2];
  EF[2] = ED[2];
  ED[2] = EB[2];
  EB[2] = EU[2];
  EU[2] = tblock;

  for(byte i = 2; i <= 3; i++)
  {
    tblock = CF[i];
    CF[i] = CD[i];
    CD[i] = CB[i];
    CB[i] = CU[i];
    CU[i] = tblock;
  }    
}
  
void rotation_Rp() // 0 = 1, 1 = 2, 2 = 3, 3 = 0
{
  Block tblock = ER[0];
  for(byte i = 0; i <= 2; i++)
    ER[i] = ER[i+1];
  ER[3] = tblock;

  tblock = CR[0];
  for(byte i = 0; i <= 2; i++)
    CR[i] = CR[i+1];
  CR[3] = tblock;

  tblock = EF[2];
  EF[2] = EU[2];
  EU[2] = EB[2];
  EB[2] = ED[2];
  ED[2] = tblock;
  
  for(byte i = 2; i <= 3; i++)
  {
    tblock = CF[i];
    CF[i] = CU[i];
    CU[i] = CB[i];
    CB[i] = CD[i];
    CD[i] = tblock;
  }    
}  

void rotation_U() // 1 = 0 , 2 = 1, 3 = 2, 0 = 3
{
  Block tblock = EU[3];
  for(byte i = 3; i >= 1; i--)
    EU[i] = EU[i-1];
  EU[0] = tblock;
  
  tblock = CU[3];
  for(byte i = 3; i >= 1; i--)
    CU[i] = CU[i-1];
  CU[0] = tblock;

  tblock = EF[1];
  EF[1] = ER[0];
  ER[0] = EB[3];
  EB[3] = EL[2];
  EL[2] = tblock;

  tblock = CF[1];
  CF[1] = CR[0];
  CR[0] = CB[3];
  CB[3] = CL[2];
  CL[2] = tblock;

  tblock = CF[2];
  CF[2] = CR[1];
  CR[1] = CB[0];
  CB[0] = CL[3];
  CL[3] = tblock;
}

void rotation_Up() // 3 = 0, 0 = 1, 1 = 2, 2 = 3
{
  Block tblock = EU[0];
  for(byte i = 0; i <= 2; i++)
    EU[i] = EU[i+1];
  EU[3] = tblock;
  
  tblock = CU[0];
  for(byte i = 0; i <= 2; i++)
    CU[i] = CU[i+1];
  CU[3] = tblock;

  tblock = EF[1];
  EF[1] = EL[2];
  EL[2] = EB[3];
  EB[3] = ER[0];
  ER[0] = tblock;

  tblock = CF[1];
  CF[1] = CL[2];
  CL[2] = CB[3];
  CB[3] = CR[0];
  CR[0] = tblock;

  tblock = CF[2];
  CF[2] = CL[3];
  CL[3] = CB[0];
  CB[0] = CR[1];
  CR[1] = tblock;
}

void rotation_F() // 1 = 0 , 2 = 1, 3 = 2, 0 = 3;
{
  Block tblock = EF[3];
  for(byte i = 3; i >= 1; i--)
    EF[i] = EF[i-1];
  EF[0] = tblock;

  tblock = CF[3];
  for(byte i = 3; i >= 1; i--)
    CF[i] = CF[i-1];
  CF[0] = tblock;

  tblock = EU[3];
  EU[3] = EL[3];
  EL[3] = ED[1];
  ED[1] = ER[3];
  ER[3] = tblock;
  
  tblock = CU[0];
  CU[0] = CL[0];
  CL[0] = CD[2];
  CD[2] = CR[0];
  CR[0] = tblock;

  tblock = CU[3];
  CU[3] = CL[3];
  CL[3] = CD[1];
  CD[1] = CR[3];
  CR[3] = tblock;  
} 

void rotation_Fp() // 3 = 0, 0 = 1, 1 = 2, 2 = 3
{
  Block tblock = EF[0];
  for(byte i = 0; i <= 2; i++)
    EF[i] = EF[i+1];
  EF[3] = tblock;
  
  tblock = CF[0];
  for(byte i = 0; i <= 2; i++)
    CF[i] = CF[i+1];
  CF[3] = tblock;

  tblock = EU[3];
  EU[3] = ER[3];
  ER[3] = ED[1];
  ED[1] = EL[3];
  EL[3] = tblock;
  
  tblock = CU[0];
  CU[0] = CR[0];
  CR[0] = CD[2];
  CD[2] = CL[0];
  CL[0] = tblock;

  tblock = CU[3];
  CU[3] = CR[3];
  CR[3] = CD[1];
  CD[1] = CL[3];
  CL[3] = tblock;  
}

void rotation_L() // 3 = 2 , 2 = 1, 1 = 0, 0 = 3
{
  Block tblock = EL[3];
  for(byte i = 3; i > 0; i--)
    EL[i] = EL[i-1];
  EL[0] = tblock;

  tblock = CL[3];
  for(byte i = 3; i > 0; i--)
    CL[i] = CL[i-1];
  CL[0] = tblock;

  tblock = EF[0];
  EF[0] = EU[0];
  EU[0] = EB[0];
  EB[0] = ED[0];
  ED[0] = tblock;
  
  tblock = CF[0];
  CF[0] = CU[0];
  CU[0] = CB[0];
  CB[0] = CD[0];
  CD[0] = tblock;

  tblock = CF[1];
  CF[1] = CU[1];
  CU[1] = CB[1];
  CB[1] = CD[1];
  CD[1] = tblock;
}

void rotation_Lp() // 2 = 3, 1 = 2, 0 = 1, 3 = 0
{
  Block tblock = EL[0];
  for(byte i = 0; i <= 2; i++)
    EL[i] = EL[i+1];
  EL[3] = tblock;

  tblock = CL[0];
  for(byte i = 0; i <= 2; i++)
    CL[i] = CL[i+1];
  CL[3] = tblock;

  tblock = EF[0];
  EF[0] = ED[0];
  ED[0] = EB[0];
  EB[0] = EU[0];
  EU[0] = tblock;
  
  tblock = CF[0];
  CF[0] = CD[0];
  CD[0] = CB[0];
  CB[0] = CU[0];
  CU[0] = tblock;

  tblock = CF[1];
  CF[1] = CD[1];
  CD[1] = CB[1];
  CB[1] = CU[1];
  CU[1] = tblock; 
}

void rotation_D() // 1 = 0, 2 = 1, 3 = 2, 0 = 3
{
  Block tblock = ED[3];
  for(byte i = 3; i >= 1; i--)
    ED[i] = ED[i-1];
  ED[0] = tblock;
  
  tblock = CD[3];
  for(byte i = 3; i >= 1; i--)
    CD[i] = CD[i-1];
  CD[0] = tblock;

  tblock = EF[3];
  EF[3] = EL[0];
  EL[0] = EB[1];
  EB[1] = ER[2];
  ER[2] = tblock;

  tblock = CF[0];
  CF[0] = CL[1];
  CL[1] = CB[2];
  CB[2] = CR[3];
  CR[3] = tblock;

  tblock = CF[3];
  CF[3] = CL[0];
  CL[0] = CB[1];
  CB[1] = CR[2];
  CR[2] = tblock;
}

void rotation_Dp() // 0 = 1, 1 = 2, 2 = 3, 3 = 0
{
  Block tblock = ED[0];
  for(byte i = 0; i <= 2; i++)
    ED[i] = ED[i+1];
  ED[3] = tblock;
  
  tblock = CD[0];
  for(byte i = 0; i <= 2; i++)
    CD[i] = CD[i+1];
  CD[3] = tblock;

  tblock = EF[3];
  EF[3] = ER[2];
  ER[2] = EB[1];
  EB[1] = EL[0];
  EL[0] = tblock;

  tblock = CF[0];
  CF[0] = CR[3];
  CR[3] = CB[2];
  CB[2] = CL[1];
  CL[1] = tblock;

  tblock = CF[3];
  CF[3] = CR[2];
  CR[2] = CB[1];
  CB[1] = CL[0];
  CL[0] = tblock;
}

void rotation_B() // 0 = 3, 1 = 0, 2 = 1, 3 = 2
{
  Block tblock = EB[3];
  for(byte i = 3; i >= 1; i--)
    EB[i] = EB[i-1];
  EB[0] = tblock;

  tblock = CB[3];
  for(byte i = 3; i >= 1; i--)
    CB[i] = CB[i-1];
  CB[0] = tblock;

  tblock = EU[1];
  EU[1] = ER[1];
  ER[1] = ED[3];
  ED[3] = EL[1];
  EL[1] = tblock;
  
  tblock = CU[1];
  CU[1] = CR[1];
  CR[1] = CD[3];
  CD[3] = CL[1];
  CL[1] = tblock;

  tblock = CU[2];
  CU[2] = CR[2];
  CR[2] = CD[0];
  CD[0] = CL[2];
  CL[2] = tblock;  
} 

void rotation_Bp()
{
  Block tblock = EB[0];
  for(byte i = 0; i <= 2; i++)
    EB[i] = EB[i+1];
  EB[3] = tblock;
  
  tblock = CB[0];
  for(byte i = 0; i <= 2; i++)
    CB[i] = CB[i+1];
  CB[3] = tblock;

  tblock = EU[1];
  EU[1] = EL[1];
  EL[1] = ED[3];
  ED[3] = ER[1];
  ER[1] = tblock;
  
  tblock = CU[1];
  CU[1] = CL[1];
  CL[1] = CD[3];
  CD[3] = CR[1];
  CR[1] = tblock;

  tblock = CU[2];
  CU[2] = CL[2];
  CL[2] = CD[0];
  CD[0] = CR[2];
  CR[2] = tblock;  
} 

void rotation_M()
{
  Block tblock = FC;
  FC = UC;
  UC = BC;
  BC = DC;
  DC = tblock;

  tblock = EF[1];
  EF[1] = EU[1];
  EU[1] = EB[1];
  EB[1] = ED[1];
  ED[1] = tblock;

  tblock = EF[3];
  EF[3] = EU[3];
  EU[3] = EB[3];
  EB[3] = ED[3];
  ED[3] = tblock;
}

void rotation_Mp()
{
  Block tblock = FC;
  FC = DC;
  DC = BC;
  BC = UC;
  UC = tblock;

  tblock = EF[1];
  EF[1] = ED[1];
  ED[1] = EB[1];
  EB[1] = EU[1];
  EU[1] = tblock;
  
  tblock = EF[3];
  EF[3] = ED[3];
  ED[3] = EB[3];
  EB[3] = EU[3];
  EU[3] = tblock; 
}

void rotation_E()
{
  Block tblock = RC;
  RC = FC;
  FC = LC;
  LC = BC;
  BC = tblock;

  tblock = EF[0];
  EF[0] = EL[1];
  EL[1] = EB[2];
  EB[2] = ER[3];
  ER[3] = tblock;

  tblock = EF[2];
  EF[2] = EL[3];
  EL[3] = EB[0];
  EB[0] = ER[1];
  ER[1] = tblock;  
}

void rotation_Ep()
{
  Block tblock = RC;
  RC = BC;
  BC = LC;
  LC = FC;
  FC = tblock;

  tblock = EF[0];
  EF[0] = ER[3];
  ER[3] = EB[2];
  EB[2] = EL[1];
  EL[1] = tblock;
  
  tblock = EF[2];
  EF[2] = ER[1];
  ER[1] = EB[0];
  EB[0] = EL[3];
  EL[3] = tblock;
}

void rotation_X()
{
  rotation_R();
  rotation_Mp();
  rotation_Lp();
}
void rotation_Xp()
{
  rotation_Rp();
  rotation_M();
  rotation_L();
}

void rotation_Y()
{
  rotation_U();
  rotation_Ep();
  rotation_Dp();
}

void rotation_Yp()
{
  rotation_Up();
  rotation_E();
  rotation_D();
}

void rotationCube(byte select)
{
  switch(select) // 0 ~ 13 R/U/F/L/D/B/M 14~17 X/Y
  {
    case 0: rotation_R(); break;
    case 1: rotation_Rp(); break;
    case 2: rotation_U(); break;
    case 3: rotation_Up(); break;
    case 4: rotation_F(); break;
    case 5: rotation_Fp(); break;
    case 6: rotation_L(); break;
    case 7: rotation_Lp(); break;
    case 8: rotation_D(); break;
    case 9: rotation_Dp(); break;
    case 10: rotation_B(); break;
    case 11: rotation_Bp(); break;
    case 12: rotation_M(); break;
    case 13: rotation_Mp(); break;
    case 14: rotation_X(); break;
    case 15: rotation_Xp(); break;
    case 16: rotation_Y(); break;
    case 17: rotation_Yp(); break;
  }
  copyBlockAll(); // 회전 후 모든 블럭을 복사한다.
}

// -------------------------- 스크램블 함수
void scrambleCube()
{
  byte scramble[100]; // 100개의 스크램블을 저장할 배열
  byte temp = 12; // 이전과 같은 회전이 나오는 것을 방지할 값

  for(byte i = 0; i < 100; i++) // 0~11 값의 난수를 100번 발생시킨다.
  {
    scramble[i] = random(12); // 0~11 // 스크램블에 값을 저장한다.

    while(i != 0 && scramble[i] == scramble[i-1]) // 두번째 기호부터 이전 기호와 같은 기호가 저장되었는지 확인
      scramble[i] = random(12); // 같은 기호가 확인되면 다를때 까지 난수발생
  }
  for(byte i = 0; i < 100; i++) // 저장된 스크램블을 사용하여 큐브를 섞는다.
  {
    setCube(); // 블럭을 복사한 뒤 큐브를 켜준다.
    rotationCube(scramble[i]); // 큐브를 i번째 배열값으로 회전시킨다.
  }
}



