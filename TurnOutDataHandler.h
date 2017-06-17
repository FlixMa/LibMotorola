/*
 * TurnOutDataHandler.h
 *
 *  Created on: 07.06.2017
 *      Author: felix
 */

#ifndef TURNOUTDATAHANDLER_H_
#define TURNOUTDATAHANDLER_H_

#include <DataHandlerInterface.h>

typedef enum {
    TURNOUT_STATE_UNKNOWN,
    TURNOUT_STATE_ROUND,
    TURNOUT_STATE_STRAIGHT
} TurnOutState;

class TurnOutDataHandler: public DataHandlerInterface {
protected:
    unsigned char blockAddress;
    unsigned char subAddress;

    TurnOutState preState;
    TurnOutState state;
    
public:
    TurnOutDataHandler(unsigned char address);
    
    void handleEvent(unsigned char address, unsigned char data);
    void handleTimeouts();
    
    virtual void turnRound();
    virtual void turnStraight();
};


#endif /* TURNOUTDATAHANDLER_H_ */
