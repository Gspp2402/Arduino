// Definizione del pin del LED
const int redPin = 2; // Pin digitale 2
const int yellowin = 3; 
const int greenPin = 4;
const int startPin = 2;
int currentPin;
int startDelay;

void setup() {
  // Imposta il pin come uscita
  pinMode(redPin, OUTPUT);
  pinMode(yellowin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  currentPin = 0;
  startDelay = 5000;
  // Inizializzazione serial monitor
  Serial.begin(9600);
  Serial.println("Arduino pronto a partire");
}

int getPin(int pin){
  switch(pin){
    case 2: return 4;
    break;
    case 3: return 2;
    break;
    case 4: return 3;
    break;
    default: return startPin;
  }
}

int getDelayHIGH(int pin){
  switch(pin){
    case 2: return 5000;
    break;
    case 3: return 2000;
    break;
    case 4: return 5000;
    break;
    default: return startDelay;
  }
}

void loop() {
  currentPin = getPin(currentPin);
  digitalWrite(currentPin, HIGH); // Accendi il LED
  Serial.println("Ho acceso il Led");
  delay(getDelayHIGH(currentPin));               // Aspetta 1 secondo
  digitalWrite(currentPin, LOW);  // Spegni il LED
  Serial.println("Ho spento il Led");
  delay(10);              // Aspetta 1 secondo
}

