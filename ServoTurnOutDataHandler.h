/*
 * ServoTurnOutDataHandler.h
 *
 *  Created on: 07.06.2017
 *      Author: felix
 */

#ifndef SERVOTURNOUTDATAHANDLER_H_
#define SERVOTURNOUTDATAHANDLER_H_

#include "TurnOutDataHandler.h"
#include <Servo.h>

class ServoTurnOutDataHandler: public TurnOutDataHandler {
private:
    
    unsigned char outputPin;
    unsigned char maxR;
    unsigned char maxS;
    Servo *servo;
    
public:
    ServoTurnOutDataHandler(unsigned char address, unsigned char outputPin, unsigned char maxR, unsigned char maxS);
    
    void setMaxR(unsigned char maxR);
    void setMaxS(unsigned char maxS);

    void turnRound();
    void turnStraight();
};


#endif /* SERVOTURNOUTDATAHANDLER_H_ */
