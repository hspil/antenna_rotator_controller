//Rotator control signals
int az_left = 2;
int az_right = 3;
int el_up = 4;
int el_down = 5;

//Rotator feedback signals
int az_pos = A2;
int el_pos = A3;

void setup() {
    Serial.begin(115200);
    
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
    Serial.print("az:");
    Serial.print(360.0*analogRead(az_pos)/1023.0 - 180.0);
     
    Serial.print(",el:");
    Serial.println(180.0*analogRead(el_pos)/1023.0);
}
