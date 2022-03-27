/* Yaesu G-5500 Antenna Rotator Controller
 *      * EasycommII protocol compatible (barebones)
 * 
 * Copyright © 2022 hspil
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

//Rotator control signals
int az_left = 2;
int az_right = 3;
int el_up = 4;
int el_down = 5;

//Rotator feedback signals
int az_pos = A2;
int el_pos = A3;

struct coordinates{
	double az;
	double el;
};

coordinates current;
coordinates desired;


const double tolerance = 5; //degrees

void setup() {
	Serial.begin(115200);
	
	//setup control pins
	pinMode(az_left, OUTPUT);
	pinMode(az_right, OUTPUT);
	pinMode(el_up, OUTPUT);
	pinMode(el_down, OUTPUT);	
	
	current.az = 0.0;
	current.el = 0.0;
	
	desired.az = 0.0;
	desired.el = 0.0;
}

void loop() {
	
	//EasycommII protocol parsing
	
	//check for command
	if(Serial.available()) {
		String command = Serial.readStringUntil('\n');
		Serial.println(command);
		//Parse and respond to each command
		
		//query position
		if(command == "AZ EL") {
			Serial.println("+" + String(current.az) + " " + String(current.el));
		}
		//set position
		else if(command.substring(0, 2) == "AZ" && command.substring(8, 10) == "AZ") {
			desired.az = command.substring(2, 7).toDouble();
			desired.el = command.substring(10, 15).toDouble();
			Serial.println(desired.az, desired.el);
		}
	}
    
    
	//Check current position
	//linearly map analogRead ADC value between 0 and 1023 to rotator angles
	current.az = 360.0 * analogRead(az_pos)/1023.0 - 180.0;
	current.el = 180.0 * analogRead(el_pos)/1023.0;
	
	
	//Azimuth control
	//azimuth angle too big: turn right
	if(current.az - desired.az > tolerance) {
		digitalWrite(az_right, LOW);
        digitalWrite(az_left, HIGH);
	}
	//too small: left
	else if(current.az - desired.az < -tolerance) {
		digitalWrite(az_left, LOW);
        digitalWrite(az_right, HIGH);
	}
	else {
		digitalWrite(az_right, LOW);
		digitalWrite(az_left, LOW);
	}
	
	
	//Elevation control
	if(current.el - desired.el > tolerance) {
		digitalWrite(el_down, HIGH);
		digitalWrite(el_up, LOW);
	}
	//too small: left
	else if(current.el - desired.el < -tolerance) {
		digitalWrite(el_down, LOW);
		digitalWrite(el_up, HIGH);
	}
	else {
		digitalWrite(el_up, LOW);
		digitalWrite(el_down, LOW);
	}
}
