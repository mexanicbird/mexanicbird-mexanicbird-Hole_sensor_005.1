
unsigned long lastflash;
int RPM;
int OUT;
int TV1;


void setup() {
    Serial.begin(115200);  //открыть порт
    attachInterrupt(0,sens,RISING); //подключить прерывание на 2 пин при повышении сигнала
    pinMode(3, OUTPUT);   //3 пин как выход  
    digitalWrite(3, HIGH);
    analogReference(EXTERNAL);
}
void sens() {
    // функция для расчета при вращении
    RPM=60/((float)(micros()-lastflash)/1000000);  //расчет
    lastflash=micros();  //запомнить время последнего оборота
    OUT = map (RPM, 0, 2800, 0, 255); //выходная карта

}

void loop() {
    if ((micros()-lastflash)>1000000){ //если сигнала нет больше секунды
        RPM=0;  //считаем что RPM 0
        OUT = map (RPM, 0, 2800, 0, 255); }
        //TV1 = 1234; 
        //else { sens();}
  
Serial.println(OUT);   //вывод в порт
delay(30);  //задержка для стабильности
}
