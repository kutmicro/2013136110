void setup() 
{
  Serial.begin(9600); // 시리얼 통신을 보우레이트 9600으로 시작한다.
  
  setupPin(); // 핀들을 셋업해주는 함수를 호출한다.
 
  start = false; // 큐브맞추기 시작 상태. 최초는 false
  power = false; // 큐브 전원공급 상태. 최초는 false
  solving = false; // 솔빙 진행 상태. 최초는 false
}
