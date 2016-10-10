int pin_R[4] = {22,26,30,34}; // LED 4개의 R핀 설정
int pin_G[4] = {23,27,31,35}; // LED 4개의 G핀 설정
int pin_B[4] = {24,28,32,36}; // LED 4개의 B핀 설정
int pin_btn = 11; // 버튼 핀 설정

int pin_power[3] = {7,6,5}; // 면 세개의 전원 핀 설정

struct Block // 한 블럭의 RGB 값을 담을 구조체 정의
{
  int r; // 각각의 변수는 RGB 의 R, G, B 코드를 저장한다.
  int g;
  int b;
};

Block R[4]; // 2x2x2 큐브의 면들을 구조체 배열을 사용하여 정의한다.
Block U[4];
Block F[4];
Block L[4];
Block D[4];
Block B[4];

int i; // 반복문에 사용될 변수 i

void setStatus(int rr,int gg,int bb, Block &b) // r,g,b 값과 블럭을 전달받아 해당 블럭의 rgb 값을 바꾸는 함수
{
  b.r = rr;
  b.g = gg;
  b.b = bb;
}

int getRStatus(Block b) { return b.r; } // 전달받은 블럭의 r,g,b 값을 반환하는 함수
int getGStatus(Block b) { return b.g; }
int getBStatus(Block b) { return b.b; }

void rotation_R() // R면을 시계방향으로 회전하는 함수
{
  Block tblock = R[3]; // 임시로 블럭을 저장한다.
  
  for(int i=3; i>0; i--)
    R[i]=R[i-1]; // 블럭들의 값을 서로 바꾼다.

    R[0] = tblock; // 임시로 저장한 블럭으로 바꾼다.

   for(int i=2; i<=3; i++) // 나머지 면의 블럭들을 바꾼다.
   {
    tblock = D[i];
    D[i]=B[i];
    B[i]=U[i];
    U[i]=F[i];
    F[i]=tblock;
   }
}

void rotation_U() // U면을 시계방향으로 회전하는 함수
{
  Block tblock = U[3]; // 임시로 블럭을 저장한다.
  
  for(int i=3; i>0; i--)
    U[i]=U[i-1]; // 블럭들의 값을 서로 바꾼다.

    U[0] = tblock; // 임시로 저장한 블럭으로 바꾼다.

  tblock = R[1]; // 나머지 면의 블럭들을 바꾼다.
  R[1]=B[3];
  B[3]=L[1];
  L[1]=F[1];
  F[1]=tblock;

  tblock = R[2];
  R[2]=B[0];
  B[0]=L[2];
  L[2]=F[2];
  F[2]=tblock;
}

void setup() {

  for(int i=0; i<4; i++) // 최초의 블럭들의 RGB 값을 저장한다. 국제 표준 색배치를 사용하고, 사람들이 흔히 쓰는 흰색면을 아래, 초록면을 앞에 두도록 초기화한다.
  {
      setStatus(255,0,0,L[i]); // L면 : 빨강
      setStatus(255,255,0,U[i]); // U면 : 노랑
      setStatus(255,0,255,R[i]); // R면 : 분홍
      setStatus(255,255,255,D[i]); // D면 : 하양
      setStatus(0,255,0,F[i]); // F면 : 초록
      setStatus(0,0,255,B[i]); // B면 : 파랑
  }
  
  for(int i = 0; i<4; i++) // RGB 핀은 출력이므로 OUTPUT으로 설정한다.
  {
    pinMode(pin_R[i],OUTPUT);
    pinMode(pin_G[i],OUTPUT);
    pinMode(pin_B[i],OUTPUT);
  }
  for(int i = 0; i<3; i++) // 전원핀 또한 출력이므로 OUTPUT으로 설정한다.
    pinMode(pin_power[i],OUTPUT);

  pinMode(pin_btn, INPUT); // 버튼은 입력이므로 INPUT으로 설정한다.
}

void loop() {

  if(digitalRead(pin_btn) == LOW) // 버튼이 눌렸을 경우 동작한다.
  {
    rotation_U(); // 큐브를 U 회전시킨다.
    delay(50); // 딜레이를 줌으로써 버튼이 중복으로 눌리는 것을 막는다.
  }
  for(int i = 0; i < 6; i++) // 총 6면이므로 0부터 5까지 반복한다.
  {
    Block block[4]; // 현재의 면을 설정한다. i의 경우에 따라 각각의 면으로 값을 설정한다.
    if(i == 0) 
      for(int q = 0; q < 4; q++) block[q] = U[q];

     else  if(i == 1)
      for(int q = 0; q < 4; q++) block[q] = F[q];

     else  if(i == 2)
      for(int q = 0; q < 4; q++) block[q] = R[q];

      else  if(i == 3)
      for(int q = 0; q < 4; q++) block[q] = L[q];

      else  if(i == 4)
      for(int q = 0; q < 4; q++) block[q] = D[q];

      else  if(i == 5)
      for(int q = 0; q < 4; q++) block[q] = B[q];
    
    for(int j = 0; j < 4; j++) // 위에서 설정된 block 상태에 따라 LED를 출력한다.
    {
      if(getRStatus(block[j]) == 255) digitalWrite(pin_R[j],LOW); // 블럭에서 읽은 R값이 255이면 R핀에 전류가 흐르도록 해야하므로 LOW를 준다.
      else if(getRStatus(block[j]) == 0) digitalWrite(pin_R[j],HIGH); // 그렇지 않으면 전류가 흐르지 않도록 HIGH를 준다.
      
      if(getGStatus(block[j]) == 255) digitalWrite(pin_G[j],LOW); // 블럭에서 읽은 G값이 255이면 G핀에 전류가 흐르도록 해야하므로 LOW를 준다.
      else if(getGStatus(block[j]) == 0) digitalWrite(pin_G[j],HIGH); // 그렇지 않으면 전류가 흐르지 않도록 HIGH를 준다.
      
      if(getBStatus(block[j]) == 255) digitalWrite(pin_B[j],LOW); // 블럭에서 읽은 B값이 255이면 B핀에 전류가 흐르도록 해야하므로 LOW를 준다.
      else if(getBStatus(block[j]) == 0) digitalWrite(pin_B[j],HIGH); // 그렇지 않으면 전류가 흐르지 않도록 HIGH를 준다.
    }
    digitalWrite(pin_power[i],HIGH); // 전언핀에 HIGH를 줌으로써 전위차가 발생하여 전류가 흐른다.
    delay(1); // 매우 작은 딜레이를 준다.
     digitalWrite(pin_power[i],LOW); // 전원핀에 LOW를 줌으로써 현재 면의 전원핀에 전류를 차단한다. 
  } // 위의 과정들이 인간이 감지할 수 없는 빠른 속도이므로 모든 면이 켜져있는 것 처럼 보이게 된다.
}















