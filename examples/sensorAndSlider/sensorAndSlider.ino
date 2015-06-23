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
obj.add("slider", "led"); // add a new I/O Point to the Object
obj.add("slider", "sensor");
}

void loop() {
	
  // Read from sensor
  float reading = obj.map(analogRead(A0), 0, 940); 
  
  // Write to Object
  obj.write("slider", "sensor", reading);
  
  // Read from Object
  analogWrite(13, obj.read("slider", "led") * 255);
 
  delay(30);
}
