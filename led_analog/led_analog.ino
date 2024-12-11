const float pin1 = 3;
const float pin2 = 5;
const float pin3 = 6;
const float pin4 = 9;
const float pin5 = 10;
int head;
const int changeHead = 100;

class LED {
  private:
  int pin;
  int voltage;
  public:
  static const int initialVoltage = 160;
  LED(int p){
    pin = p;
    voltage = initialVoltage;
    pinMode(pin, OUTPUT);

  }
  int getVoltage(){
    return voltage;
  }

  int getPin(){
    return pin;
  }

  void reduceVoltage(){
    if (voltage > 0){
      voltage -= 2;
    }
    else{
      voltage = 0;
    }
  }

  void writeLed(){
    analogWrite(pin, voltage);
  }

  void resetVoltage(){
    voltage = initialVoltage;
  }

  void turnOffLed(){
    voltage = 0;
    writeLed();
  }
};

LED leds[5] = {LED(pin1), LED(pin2), LED(pin3), LED(pin4), LED(pin5)};

int manageLed(LED leds[], int head){
  for (int i = head; i >= 0; i --){
    leds[i].reduceVoltage();
    leds[i].writeLed();
  }

  if (leds[head].getVoltage() == changeHead){
    if (head == 4){
      resetLed(leds);
      leds[0].writeLed();
      return 0;
    }
    else{
      leds[head +1].writeLed();
      return (head + 1);
    }
  }
  else{
    return head;
  }
}

void resetLed(LED leds[]){
  for(int i = 0; i < 5; i++){
    leds[i].turnOffLed();
    leds[i].resetVoltage();
  }
}

void setup() {
  // put your setup code here, to run once:
  head = 0;
  Serial.begin(9600);
  Serial.println("Arduino pronto a partire");
}

void loop() {
  // put your main code here, to run repeatedly:
  head = manageLed(leds, head);
  delay(5);

}
