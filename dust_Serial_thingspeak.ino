//esp8266 라이브러리 불러오기
#include <ESP8266WiFi.h>
/*
   thingspeak 서버 연결
   thingspeak 나의 채널 API Key 붙여넣기
   Wifi SSID 붙여넣기
   Wifi PW 붙여넣기
*/
const char* server = "api.thingspeak.com";
String apiKey = "4ZWQVFHPQ0PH0UCF";
const char* MY_SSID = "SK_WiFiGIGA9E5A";
const char* MY_PWD = "1603057461";

int sent = 0;

//센서값 입력 핀: A0(아날로그)
float measurePin = 0;

// 적외선 발사 핀 : 2번(Nodemcu D4번, 디지털)
int ledPower = 2;

/*
    RGB 핀 설정(PWM 핀)
    Red Pin : D8
    Green Pin : D6
    Blue Pin : D5
*/
const int RED = 15; // Red Pin : D8(15)
const int GREEN = 12;// Green Pin : D6(12)
const int BLUE = 14;//Blue Pin : D5(14)

/*
   샘플링 간격 변수 & 값 변환 변수 설정 부분
   1)샘플링을 위한 시간 간격 설정
   2)입력받은 아날로그 값을 전압, 밀리그램 단위의 먼지농도, 마이크로밀리그램 단위의 먼지농도로 변환하는 변수 설정
*/
int samplingTime = 280;
int delayTime = 40;
float offTime = 9680;

//상태 지정
int state = 0;

//// 초기 설정(시리얼 통신, 핀 설정)
void setup() {
  Serial.begin(115200);
  connectWifi();
  pinMode(ledPower, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

void loop() {
  //전압, 먼지센서 값 설정
  float voltage = 0;
  float dust = 0;

  //Wifi 연결
  WiFiClient client;

  //LED를 on/off하여 값을 센싱하는 부분
  digitalWrite(ledPower, LOW); // power on the LED
  delayMicroseconds(samplingTime);

  //먼지 센서를 값을 0.0V~3.3V 을 0~1024 값으로 변경해 줌(아날로그 값)
  measurePin = analogRead(A0);
  delayMicroseconds(delayTime);
  digitalWrite(ledPower, HIGH);
  delayMicroseconds(offTime);

  // 입력된 볼트를 계산해 줌(전압)
  voltage = measurePin * (3.3 / 1024);

  // 볼트를 기준으로 미세먼지 값으로 변환해 줌, 데이터 시트을 참고 오차가 존재합니다.(밀리그램 단위)
  dust = (0.17 * voltage) * 1000;

  // 미세먼지 수치 출력(마이크로그램단위로 미세먼지 농도 환산)
  Serial.print("Dust density(ug/m3) = ");
  Serial.print(dust);

  // 아날로그로 읽어 들인 0-1024 수치
  Serial.print(", dustVal = ");
  Serial.print(measurePin);

  // 볼트로 계산해서 출력
  Serial.print(", voltage = ");
  Serial.println(voltage);

  // thingspeak서버로 미세먼지 농도 보내기
  if (client.connect(server, 80)) { // use ip 184.106.153.149 or api.thingspeak.com
    Serial.println("WiFi Client connected");

    Serial.print(String(sent) + "Dust density(ug/m3) : ");
    Serial.println(dust);

    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(dust);
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
    delay(1000);
  }
  sent++;
  delay(15000);
  client.stop();

  //Dust density(ug/m3)에 따른  RGB LED 출력
  if (dust != 0) {
    if (dust > 150) {
      state = 1;
    }
    else if (dust > 80) {
      state = 2;
    }
    else if (dust <= 80) {
      state = 3;
    }
  }
  if (state == 1) {
    analogWrite(RED, 255);
    analogWrite(GREEN, 0);
    analogWrite(BLUE, 0);
  }
  else if (state == 2) {
    analogWrite(RED, 255);
    analogWrite(GREEN, 127);
    analogWrite(BLUE, 0);
  }
  else if (state == 3) {
    analogWrite(RED, 0);
    analogWrite(GREEN, 255);
    analogWrite(BLUE, 0);
  }
}

//와이파이 설정
void connectWifi()
{
  Serial.print("Connecting to " + *MY_SSID);
  WiFi.begin(MY_SSID, MY_PWD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected");
  Serial.println("");
}

