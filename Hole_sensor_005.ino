#include "GyverFilters.h"
unsigned long lastflash;
int RPM;
int RPM_1;



void setup() {
    Serial.begin(115200);  //открыть порт
    attachInterrupt(0,sens,RISING); //подключить прерывание на 2 пин при повышении сигнала
    pinMode(3, OUTPUT);   //3 пин как выход  
    digitalWrite(3, HIGH);
    analogReference(EXTERNAL);
}
void sens() {
  RPM=60/((float)(micros()-lastflash)/1000000);  //расчет
  lastflash=micros();  //запомнить время последнего оборота
  if (RPM >= 0 && RPM <=2800){
    if (RPM < RPM_1 + 100 || RPM > RPM_1 - 100){
    RPM_1 = RPM;
    }
    }
}
void loop() {
  if ((micros()-lastflash)>500000){ //если сигнала нет больше секунды
    RPM_1=0;  //считаем что RPM 0
  }
  Serial.println(RPM_1);   //вывод в порт
  delay(100);  //задержка для стабильности
}
