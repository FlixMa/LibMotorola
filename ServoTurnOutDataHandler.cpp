/*
 * ServoTurnOutDataHandler.cpp
 *
 *  Created on: 07.06.2017
 *      Author: felix
 */

#include "Arduino.h"
#include <assert.h>
#include "ServoTurnOutDataHandler.h"

ServoTurnOutDataHandler::ServoTurnOutDataHandler(unsigned char address, unsigned char outputPin, unsigned char maxR, unsigned char maxS)
: TurnOutDataHandler(address), outputPin(outputPin), maxR(maxR), maxS(maxS) {
    
    this->servo = new Servo;
    this->servo->attach(outputPin);
    
    this->state = TURNOUT_STATE_ROUND;
    this->turnRound();
    
};

void ServoTurnOutDataHandler::setMaxR(unsigned char maxR) {
    this->maxR = maxR;
};

void ServoTurnOutDataHandler::setMaxS(unsigned char maxS) {
    this->maxS = maxS;
};


void ServoTurnOutDataHandler::turnRound() {
    this->servo->write(maxR);
};
 
void ServoTurnOutDataHandler::turnStraight() {
    this->servo->write(maxS);
};



