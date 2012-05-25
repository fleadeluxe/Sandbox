/*
 *  InputManager.h
 *  Sandbox
 *
 *  Created by Jack Smith on 6/08/11.
 *  Copyright 2011 . All rights reserved.
 *
 */

#ifndef INPUT_MANAGER_H_INCLUDED
#define INPUT_MANAGER_H_INCLUDED

#include "InputConstants.h"

class IInputDevice;

class CInputManager
{
public:
	CInputManager();
	
	bool Initialise(EInputDeviceType p_eDeviceType);
	void Uninitialise();
	
	void Update(float fElapsed);
	
	const SControllerState& GetState() const;
    
    bool IsButtonDown(EButton p_eButton, const SControllerState& p_rState) const;
	
private:
	
	void ZeroState();
	
	IInputDevice* m_pInputDevice;
	
	SControllerState m_LastControllerState;
};

#endif //INPUT_MANAGER_H_INCLUDED