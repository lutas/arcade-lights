import processing.serial.*;

Serial myPort;

int ButtonWidth = 64;
int ButtonHeight = 64;
PFont f;

void setup() { 
  size(548, 200);
  
  String portName = "COM5";  
  myPort = new Serial(this, portName, 9600);  
  
  f = createFont("c:/windows/fonts/lucon.ttf", 24);
  textFont(f);
  textAlign(CENTER, CENTER);
}

void switchLight(byte index, byte state) {
  
  // send test data
  println("sending data");
  myPort.write(byte(0xFF));
  myPort.write(byte(0x01));
  
  byte data = (byte)(index << 3 | state);
  
  myPort.write(data);   
  
}

void toggleButton(byte index, String name, int x, int y) {
  
  int w = ButtonWidth;
  int h = ButtonHeight;
  
  stroke(255);
  fill(color(255, 255, 255));
  rect(x, y, w, h);
  
  if (mouseX >= x && mouseX <= x + w &&
      mouseY >= y && mouseY <= y + h) {
        
      stroke(127);
      rect(x, y, w, h); 
      fill(color(255, 255, 255));     
      
      if (mousePressed) {
        switchLight(index, (byte)1);
      }
  }
  
  stroke(127);
  color inside = color(204, 102, 0);
  fill(inside);
  text(name, x + (w / 2), y + (h / 2));
}

void drawGUI() {
  
  // draw individual buttons
  for (byte i = 0; i < 8; ++i) {    
    toggleButton(i, str(i + 1), 4 + i * (ButtonWidth + 4), 10);    
  }
}

void draw() {
  
  drawGUI();

  // look for print messages from arduino for debugging
  if ( myPort.available() > 0) {  
    String val = myPort.readStringUntil('\n'); 
    println(val);
  }
}
