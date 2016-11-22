void setup() {
  Serial.begin(9600); // 시리얼통신을 보레이트 9600 으로 설정
  pinMode(13,INPUT); // 디지털핀 12,13을 입력으로 설정
  pinMode(12,INPUT);
}

void loop() {
  int red = digitalRead(12); // 빨간버튼과 파란버튼에 연결된 디지털 핀 번호에서 값을 받아온다.
  int blue = digitalRead(13);

  if(red == 1) Serial.println("RED BUTTON"); // 버튼이 눌린경우 (1) 각각의 버튼에 해당하는 문구 출력.
  if(blue == 1) Serial.println("BLUE BUTTON");
}
