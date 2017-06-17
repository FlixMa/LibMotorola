#include <Decoder145027.h>
#include <Detect145027.h>

#include <ServoTurnOutDataHandler.h>

//Globally create a detector.
Detect145027 detector(Detect145027::TURNOUT_NOMINAL_PULSE_WIDTH_MICROS);
Decoder145027 decoder;


// the input pin to read the signal from (which should get decoded)
#define INPUT_PIN (21)
const int INTERRUPT_PIN = digitalPinToInterrupt(INPUT_PIN);

// the actual address which is pressed on the IntelliBox
// (i.e. Control Unit from the german manufaturer Uhlenbrock)
#define SWITCH_ADDRESS (5)

// the pwm-pin the servo is attached to
#define SERVO_PIN (8)


void handler() {

  // Do read the pin that corresponds to the interrupt as fast as possible.
  // This is machine-dependent:
  // http://www.arduino.org/learning/tutorials/hackings/atmega-2560-arduino-pin-mapping
  // 43 | PD0 ( SCL/INT0 ) | Digital pin 21 (SCL)
  int fastReadResult = PIND & (1 << PD0);

  // Call the appropriate method on the detector.
  if (fastReadResult != 0) {
    // state is up, must have been leading edge...
    detector.pickUpLeadingEdge();
    
  } else {
    // must have been trailing edge then...
    detector.pickUpTrailingEdge();
    
  }
}


//#############################################################################


// The setup function is called once at startup of the sketch
void setup() {

    // set up the input pin for decoding
    pinMode(INPUT_PIN, INPUT);
    attachInterrupt(INTERRUPT_PIN, &handler, CHANGE);


    // create a new servo and start listening
    ServoTurnOutDataHandler *dataHandler = new ServoTurnOutDataHandler(SWITCH_ADDRESS, SERVO_PIN, 90, 0);
    decoder.addHandler(dataHandler);

}

// The loop function is called in an endless loop
void loop() {
  if (detector.available()) {
    unsigned char* datagram = detector.getCurrentDatagram();
    decoder.decodeDatagram(datagram); // after decoding, it automatically notifies the handlers
  }
}
