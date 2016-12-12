// -------------------------- 변수선언
byte rpin[9];
byte gpin[9];
byte bpin[9];
byte zpin[6];

byte pin_rgb = 22;
byte pin_gnd = 2; // 핀 초기화

byte joy[8] = { A0, A1, A2, A3, A4, A5, A6, A7 }; // RU(01) FM(23) LD(45) XY(67)

byte btn_power = 8; // on/off 버튼
byte btn_funtion = 9; // on -> start -> finish 순으로동작

bool power;
bool start;
bool solving;

byte data;

struct Block
{
  byte r,g,b;
};

Block CU[4];
Block CB[4];
Block CL[4];
Block CR[4];
Block CF[4];
Block CD[4];

Block EU[4];
Block EB[4];
Block EL[4];
Block ER[4];
Block EF[4];
Block ED[4];

Block UC;
Block BC;
Block LC;
Block RC;
Block FC;
Block DC;

Block allBlock[6][9]; // R(0) U(1) F(2) L(3) D(4) B(5)

unsigned long previousTime = 0, currentTime;

// -------------------------- 회전함수
// -------------------------- 전체회전 함수
// -------------------------- 셋업
// -------------------------- 루프















  
  

