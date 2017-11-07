//센서값 입력 핀: A0(아날로그)
float measurePin = 0;

//미세먼지 농도 설정
float dustDensity = 0;

// 적외선 발사 핀 : 2번(Nodemcu D4번, 디지털)
int ledPower = 2;

/*
   샘플링 간격 변수 & 값 변환 변수 설정 부분
   1)샘플링을 위한 시간 간격 설정
   2)입력받은 아날로그 값을 전압, 밀리그램 단위의 먼지농도, 마이크로밀리그램 단위의 먼지농도로 변환하는 변수 설정
*/
int samplingTime = 280;
int delayTime = 40;
float offTime = 9680;

// 초기 설정(시리얼 통신, 핀 설정)
void setup() {
  Serial.begin(9600);
  pinMode(ledPower, OUTPUT);
}
// 무한 반복
void loop() {
  //전압, 먼지센서 값 설정
  float voltage = 0;
  float dust = 0;

  //LED를 on/off하여 값을 센싱하는 부분
  digitalWrite(ledPower, LOW);
  delayMicroseconds(samplingTime);

  //먼지 센서를 값을 0.0V~3.3V 을 0~1024 값으로 변경해 줌(아날로그 값)
  measurePin = analogRead(A0);
  delayMicroseconds(delayTime);
  digitalWrite(ledPower, HIGH);
  delayMicroseconds(offTime);
  //3초마다 읽어들임
  delay(3000);

  //입력된 볼트를 계산해 줌(전압)
  voltage = measurePin * (3.3 / 1024);
  
  // 볼트를 기준으로 미세먼지 값으로 변환해 줌, 데이터 시트을 참고 오차가 존재합니다.(밀리그램 단위)
  dust = (0.17 * voltage) * 1000;

  // 미세먼지 수치 출력(마이크로그램단위로 미세먼지 농도 환산)
  Serial.print("Dust density(ug/m3) = ");
  Serial.print(dust);

  //아날로그로 읽어 들인 0-1024 수치
  Serial.print(", dustVal = ");
  Serial.print(measurePin);

  // 볼트로 계산해서 출력
  Serial.print(", voltage = ");
  Serial.println(voltage);
}
