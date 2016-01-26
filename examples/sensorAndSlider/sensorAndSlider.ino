/*
Read from and Write to a Hybrid Object

Copy the files from the interface folder 
to your Hybrid Object.

created 2015
by Valentin Heun
*/

#include <HybridObject.h>
HybridObject obj;

int counter =0;

void setup() {
obj.developer(); // allow developer tools
obj.add("yourObjectName", "led"); // add a new I/O Point to the Object
obj.add("yourObjectName", "sensor");
}

void loop() {
	
  // Read from sensor
  float reading = obj.map(analogRead(A0), 0, 940); 
  
  // Write to Object
  obj.write("yourObjectName", "sensor", reading);
  
  // Read from Object
  analogWrite(13, obj.read("yourObjectName", "led") * 255);
 
  delay(30);
}
