# LibMotorola - TurnOutDecoder
###### Enhanced for servo-driven Turnouts.
-

This library decodes the signals send by a control-unit using the Märklin-Motorola protocol.
It is written for use on an Arduino and tested with an 'Arduino Mega2560 R3' Board.

--

### Physical Prerequisites:
Have a look at the simulation I have done [here](./doc/circuit.pdf). That's actually the circuit I'm using with my system.
The green voltage gauge is the Arduino and the line where the other gauge is connected to represents the the data line with the digital signal from your control-unit.



You need to connect at least 3 wires to the arduino.

1. The **decoder-pin**: this pin needs to be an interupt pin. For the mega2560 you can have a look at [this page](http://www.arduino.org/learning/tutorials/hackings/atmega-2560-arduino-pin-mapping).  
For example I chose pin 43 which can be read directly from the registers at the address **PD0** (SCL/INT0) and is connected to digital **pin 21** (SCL) on the header.

2. You can connect the supply-voltage from your circuit directly with the 5V header of your mega. However, be careful using it, as any fluctuation and/or voltage peaks might kill it.

3. The ground needs to be connected to the ground of your circuit as well.

--
### Detector and Decoder

You create them both globally so they're accessible both in the `setup()` as well as in the `loop()` part.

	#include <Decoder145027.h>
	#include <Detect145027.h>

	//Globally create a detector.
	Detect145027 detector(Detect145027::TURNOUT_NOMINAL_PULSE_WIDTH_MICROS);
	Decoder145027 decoder;


After this setup is done, you need to ask the detector if there are any datagrams to decode. Therefore `loop()` looks like:

	if (detector.available()) {
		unsigned char* datagram = detector.getCurrentDatagram();
    	decoder.decodeDatagram(datagram);
    }

As the decoder finishes decoding, it automatically notifies all attached handlers.


--
### Servo-TurnOut Convenience Class

The handler is created by calling the following constructor:

	ServoTurnOutDataHandler(unsigned char address, unsigned char outputPin, unsigned char maxR, unsigned char maxS);
	
You need to pass the following values:

1. The **address** is the one this turnout should be controlled by. It's the one you enter in your control-unit (e.g. Uhlenbrock's IntelliBox).

2. The **outputPin** is the pin (supporting PWM) the servos data line is connected to.

3. **maxR** and **maxS** stand for the angle in degrees (range: 0 - 180) when the turnout is in position *round* or *straight* respectively.

Finally you need to attach the handler to the decoder. This is done in the `setup()` part of the arduino like so:

	// create a new servo and start listening
    ServoTurnOutDataHandler *dataHandler = new ServoTurnOutDataHandler(SWITCH_ADDRESS, SERVO_PIN, 90, 0);
    decoder.addHandler(dataHandler);

You can have a look at this [example](./servoExample/servoExample.ino).


--
### Credits

Credits for the decoding library go to [666c796e6e](https://github.com/666c796e6e/LibMotorola).