#include "GyverFilters.h"
unsigned long lastflash;
int RPM;
int RPM_1;
int RPM_2;
GMedian<20, int> testFilter; 
GFilterRA average(0.5, 80);

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
    if (RPM < RPM_1 + 2000 && RPM > RPM_1 - 2000){
    RPM_1 = RPM;
    RPM_2 = testFilter.filtered(RPM_1);
    RPM_2 = average.filtered(RPM_2);
    }
    }
}
void loop() {
  if ((micros()-lastflash)>500000){ //если сигнала нет больше секунды
    RPM_1=0;  //считаем что RPM 0
  }
  Serial.println(RPM_2);   //вывод в порт
  delay(100);  //задержка для стабильности
}
