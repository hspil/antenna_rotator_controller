//Rotator control signals
int az_left = 2;
int az_right = 3;
int el_up = 4;
int el_down = 5;

void setup() {
    
    //setup control pins
    pinMode(az_left, OUTPUT);
    pinMode(az_right, OUTPUT);
    pinMode(el_up, OUTPUT);
    pinMode(el_down, OUTPUT);

    //force low
    digitalWrite(az_right, LOW);
    digitalWrite(az_left, LOW);
    digitalWrite(el_up, LOW);
    digitalWrite(el_down, LOW);
}

void loop() {
    
    digitalWrite(az_left, LOW);
    digitalWrite(az_right, HIGH);
    delay(1000);
    digitalWrite(az_right, LOW);
    digitalWrite(az_left, HIGH);
    delay(1000);
    digitalWrite(az_right, LOW);
    digitalWrite(az_left, LOW);
    delay(2000);
    
    digitalWrite(el_down, LOW);
    digitalWrite(el_up, HIGH);
    delay(1000);
    digitalWrite(el_up, LOW);
    digitalWrite(el_down, HIGH);
    delay(1000);
    digitalWrite(el_up, LOW);
    digitalWrite(el_down, LOW);
    delay(2000);
}
