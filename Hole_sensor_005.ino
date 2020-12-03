
unsigned long lastflash;
int RPM;



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
}

void loop() {
  if ((micros()-lastflash)>1000000){ //если сигнала нет больше секунды
    RPM=0;  //считаем что RPM 0
  }
  Serial.println(RPM/2);   //вывод в порт
  delay(50);  //задержка для стабильности
}
