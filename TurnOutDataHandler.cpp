/*
 * TurnOutDataHandler.cpp
 *
 *  Created on: 07.06.2017
 *      Author: felix
 */

#include "TurnOutDataHandler.h"
#include "Arduino.h"
#include <assert.h>

TurnOutDataHandler::TurnOutDataHandler(unsigned char address) {
    
    assert(address >= 1);
    
    // IB-Adresse
    //   -> IB-Block | IB-Weiche (Block besteht aus 4 Weichen)
    //   -> address | payload (without parity bit)
    
    //  3 -> (1 | 2) -> (1 | 4/5)
    //  8 -> (2 | 3) -> (2 | 6/7)
    //  9 -> (3 | 0) -> (3 | 0/1)
    // 10 -> (3 | 1) -> (3 | 2/3)
    
    this->blockAddress = (address - 1) / 4 + 1;
    this->subAddress = ((address - 1) % 4) * 2;
}


void TurnOutDataHandler::handleEvent(unsigned char address, unsigned char data) {
    
    // If it's a foreign address, ignore it.
    if (address != this->blockAddress) {
        return;
    }
    
    //least significant bit is always zero.
    //the preceding three bits hold the payload
    //(which tells us the coil to activate/deactivate)
    unsigned char subAddress = (data & 0x0F) >> 1;
    
    
    //The fifth bit gives the enable-state
    unsigned char enable = (data & 0x10) >> 4;
    
    if (enable) {
        
        if (subAddress == this->subAddress) {
            //we are supposed to go "ROUND"

            if (this->preState != TURNOUT_STATE_ROUND) {
                //to filter false-positives lets see what the next command gives us
                this->preState = TURNOUT_STATE_ROUND;

            } else if (this->state != TURNOUT_STATE_ROUND) {
                //this is the second time receiving instructions to go "ROUND"

                //lets do it
                this->state = TURNOUT_STATE_ROUND;
                this->turnRound();
            }

        } else if (subAddress == this->subAddress + 1) {
            //we are supposed to go "STRAIGHT"

            if (this->preState != TURNOUT_STATE_STRAIGHT) {
                //wait one command
                this->preState = TURNOUT_STATE_STRAIGHT;

            } else if (this->state != TURNOUT_STATE_STRAIGHT) {
                //this is the second time receiving instructions to go "STRAIGHT"

                //lets do it
                this->state = TURNOUT_STATE_STRAIGHT;
                this->turnStraight();
            }
        }
        
    }
    
}

void TurnOutDataHandler::handleTimeouts() {}
