//
//  KeyboardInputDevice.h
//  Sandbox
//
//  Created by Jack Smith on 26/11/11.
//  Copyright (c) 2011 Transmission Games. All rights reserved.
//

#ifndef Sandbox_KeyboardInputDevice_h
#define Sandbox_KeyboardInputDevice_h

#include "InputDevice.h"

class CKeyboardInputDevice : public IInputDevice
{
public:
	
	CKeyboardInputDevice(){}
	virtual ~CKeyboardInputDevice(){}
	
	void GetInputState(SControllerState& p_rState);
	
private:
	
	void EnumerateKeys(SControllerState& p_rState);
};

#endif
