/*
 *  InputDevice.h
 *  Sandbox
 *
 *  Created by Jack Smith on 6/08/11.
 *  Copyright 2011 JackCorp. All rights reserved.
 *
 */

#ifndef INPUT_DEVICE_H_INCLUDED
#define INPUT_DEVICE_H_INCLUDED

#include "InputConstants.h"

class IInputDevice
{
public:
	virtual void GetInputState(SControllerState& p_rState) = 0;
};

#endif //INPUT_DEVICE_H_INCLUDED