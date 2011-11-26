/*
 *  GamepadInputDevice.h
 *  Sandbox
 *
 *  Created by Jack Smith on 6/08/11.
 *  Copyright 2011 JackCorp. All rights reserved.
 *
 */

#ifndef GAMEPAD_INPUT_DEVICE_H_INCLUDED
#define GAMEPAD_INPUT_DEVICE_H_INCLUDED

#include "includes.h"
#include "InputDevice.h"

class CGamepadInputDevice : public IInputDevice
{
public:
	
	CGamepadInputDevice(int p_nDeviceIndex);
	virtual ~CGamepadInputDevice();
	
	void GetInputState(SControllerState& p_rState);
	
private:
	
	void EnumeratePS3Axes(SControllerState& p_rState);
	void EnumeratePS3Buttons(SControllerState& p_rState);
	
	SDL_Joystick* m_pGamepad;
	
	EGamepadType m_eType;
	
	int m_nNumAxes;
	int m_nNumButtons;
};

#endif //GAMEPAD_INPUT_DEVICE_H_INCLUDED