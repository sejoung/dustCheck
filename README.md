# dustCheck
20171029

미세먼지 눈에보이지 않을정도의 작은 먼지
황사 중국과 몽골 사막에서 바람을 타고 넘어온것 자연적으로 일어난것
스모그 연기 + 안개(인위적으로 일어난것)

먼지
총먼지
미세먼지
pm10(미세먼지), pm2.5(초미세먼지)

에어포칼립스(영국경제지에서 나온 이야기)

예방법 손씻기, 미세먼지 자주 확인


이날 애가 너무 울어서 못함 이제 부터 혼자 할려고 함


먼저 그날 받았던 킷은 NodeMCU와 미세먼지 센서 저항 rgb led 하나 등등 이다.

아두이노 (Arduino) IDE 에 NodeMCU 보드 설정

https://www.arduino.cc/en/Main/Software 에서 OS 에 맞는 아두이노 IDE 를 다운받아 설치합니다.

File에서 Preferences 에서 Additional Board Manager URLs 에 http://arduino.esp8266.com/stable/package_esp8266com_index.json 를 입력합니다.

Tools > Board > Board Manager... 에서 eps8266 보드를 설치합니다.

Tools > Board 에서 NodeMCU 1.0 보드를 선택합니다.

Port 에서 NodeMCU 보드에 연결된 시리얼 포트를 선택합니다.

속도는 115200 이 기본 설정인데, 빠른 속도를 선택하면 업로드가 금방 끝나지만 오류가 발생할 확률도 높아집니다. 케이블이나 포트 상태에 따라 230400 나 460800 를 사용할 수도 있습니다.

위에 작업을 해야 이제 작업할수있는 환경이 됨

만약에 Baud rate가 Serial.begin(9600)으로 설정해놓고 시리얼 모니터 하단에서 115200 설정되어 있으면 글자가 깨짐 현상이 있음




# 참조 
-----
* [NodeMCU](https://en.wikipedia.org/wiki/NodeMCU)
* [arduino 홈페이지](https://www.arduino.cc/)
* [Quick-Start-to-Nodemcu-ESP8266-on-Arduino-IDE](http://www.instructables.com/id/Quick-Start-to-Nodemcu-ESP8266-on-Arduino-IDE/)
* [아두이노 미세먼지 측정기](http://www.hardcopyworld.com/ngine/aduino/index.php/archives/1849)
* [Sharp_GP2Y1010AU](https://www.dfrobot.com/wiki/index.php/Sharp_GP2Y1010AU)
