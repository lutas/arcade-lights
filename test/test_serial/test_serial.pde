import processing.serial.*;

Serial myPort;

void setup() {
  String portName = "COM5";
  
  myPort = new Serial(this, portName, 9600);
  
  
}

void draw() {
  
  // send test data
  if (mousePressed == true) {
    println("sending data");
    myPort.write(byte(0xFF));
    myPort.write(byte(0x01));
    
    myPort.write(byte(0x18));    
  }

  // look for print messages from arduino for debugging
  if ( myPort.available() > 0) {  
    String val = myPort.readStringUntil('\n'); 
    println(val);
  }
}
