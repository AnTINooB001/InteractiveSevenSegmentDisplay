#include "Header.hpp"

Eyes eyes(0,2);

void setup() {
  Serial.begin(9600);

  // если порт 0 неподключен, то генератор псевдослучайных чисел
  // будет инициализироваться функцией randomSeed() со случайного
  // значения при каждом запуске программы из-за "шума" на порту
  randomSeed(analogRead(0));

  // put your setup code here, to run once:
  for(byte i = 0; i < seg_count; i++) {
    pinMode(segment[i],OUTPUT);
  }
  for(byte i = 0; i < disp_count; i++) {
    pinMode(disp[i],OUTPUT);
    digitalWrite(disp[i],DISP_OFF);
  }
  Map::init();
}

void loop() {


     const char* str = "hello world!";
     draw_str(str,0.6);

  for(int i = 0; i < Eyes::emotion_count;)
  {
    eyes.emotions(i,0.5);
    i++;
  }
  eyes.draw_face();

}