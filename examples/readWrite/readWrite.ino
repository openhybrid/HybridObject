/*
Read from and Write to a Hybrid Object

Copy the html page from the interface folder 
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
obj.add("yourObjectName", "generator");
}

void loop() {
	
  // Read from Object  
  analogWrite(13, obj.read("yourObjectName", "led") * 255);
    counter+=30;
    if(counter>1023){
     counter = 0; 
    }
       // Write to Object
       obj.write("yourObjectName", "generator",obj.map(counter, 0, 1023));
       
  delay(30);
}
