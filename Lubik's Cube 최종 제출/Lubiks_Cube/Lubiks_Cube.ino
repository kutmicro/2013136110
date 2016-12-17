// -------------------------- 변수선언
byte rpin[9], gpin[9], bpin[9] // 9개 블럭의 rgb핀
byte zpin[6]; // 6면의 LED 전원핀
byte pin_rgb = 22; // rgb 핀은 디지털 22번핀부터 시작
byte pin_gnd = 2; // 전원핀은 디지털 2번 핀부터 시작
byte joy[8] = { A0, A1, A2, A3, A4, A5, A6, A7 }; // RU(01) FM(23) LD(45) XY(67)
byte btn_power = 8; // on/off 버튼
byte btn_funtion = 9; // on -> start -> finish 순으로동작
bool power;
bool start;
bool solving; // 전원 공급, 큐브맞추기 시작, 큐브 맞추는 중의 여부를 표시할 변수
byte data; // 시리얼통신으로 받아온 데이터를 저장할 변수
struct Block // LED의 r,g,b 값을 저장할 구조체 변수
{
  byte r,g,b;
};
Block CU[4];
Block CB[4];
Block CL[4];
Block CR[4];
Block CF[4];
Block CD[4]; // 코너블럭
Block EU[4];
Block EB[4];
Block EL[4];
Block ER[4];
Block EF[4];
Block ED[4]; // 엣지블럭
Block UC;
Block BC;
Block LC;
Block RC;
Block FC;
Block DC; // 센터블럭
Block allBlock[6][9]; // R(0) U(1) F(2) L(3) D(4) B(5)
unsigned long previousTime = 0, currentTime; // 입력시간 측정에 사용될 변수
















  
  

