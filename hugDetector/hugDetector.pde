import processing.serial.*;

Serial myPort;      // The serial port
int whichKey = -1;  // Variable to hold keystoke values
int inByte = -1;    // Incoming serial data
String inString;
IntList touchValues = new IntList();
int touchThreshold = 5;
float hugThreshold = .5; //percentage of sensors touched range 0-1
String dummyString = "S,0,0,22,44.";

void setup() {
  size(400, 400);
  PFont myFont = createFont(PFont.list()[2], 14);
  textFont(myFont);

  // List all the available serial ports:
  //printArray(Serial.list());

  // I know that the first port in the serial list on my mac
  // is always my  FTDI adaptor, so I open Serial.list()[0].
  // In Windows, this usually opens COM1.
  // Open whatever port is the one you're using.
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600);
  myPort.clear();
}

void draw() {
  background(0);
  if (inString!=null) {
    cleanMessage();
    if (hugDetected()) {
      //println("HUG");
      textSize(100);
      text("HUG", 100, 250);
    }
  }
}

void serialEvent(Serial myPort) {
  inString = null;
  touchValues.clear();
  inString = myPort.readStringUntil(46);
}

void mousePressed() {
  myPort.write(dummyString);
  whichKey = key;
}

void cleanMessage() {
  inString = split(inString, "S,")[1];
  //println(inString);
  String [] tempStrings = split(inString, ",");
  for (int i=0; i<tempStrings.length; i++) {
    touchValues.append(int(tempStrings[i]));
  }
  inString = null;
  //println(touchValues);
}

boolean hugDetected() {
  float numOfTouches=0;
  for (int i=0; i<touchValues.size(); i++) {
    if (touchValues.get(i)>touchThreshold) {
      numOfTouches++;
    }
  }
  if (numOfTouches/float(touchValues.size())>=hugThreshold) {
    return true;
  } else return false;
}