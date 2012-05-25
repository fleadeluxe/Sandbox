/*
 *  InputManager.cpp
 *  Sandbox
 *
 *  Created by Jack Smith on 6/08/11.
 *  Copyright 2011 . All rights reserved.
 *
 */

#include "includes.h"
#include "InputManager.h"
#include "GamepadInputDevice.h"
#include "KeyboardInputDevice.h"

CInputManager::CInputManager()
:	m_pInputDevice(NULL)
{
	
}

bool CInputManager::Initialise(EInputDeviceType p_eDeviceType)
{	
	switch(p_eDeviceType)
	{
		case(EInputDeviceType_Gamepad):
		{			
			if (SDL_NumJoysticks() > 0)
			{
				m_pInputDevice = new CGamepadInputDevice(0);
			}
		}
        case (EInputDeviceType_Keyboard):
        {
            m_pInputDevice = new CKeyboardInputDevice();
        }
		break;
		default:
			break;
	}
	
	return true;
}

void CInputManager::Uninitialise()
{
	if (m_pInputDevice != NULL)
	{
		delete m_pInputDevice;
		m_pInputDevice = NULL;
	}
}

void CInputManager::ZeroState()
{
	m_LastControllerState.m_nButtons = 0;
	m_LastControllerState.m_fLeftStickX = 0.0f;
	m_LastControllerState.m_fLeftStickY = 0.0f;
	m_LastControllerState.m_fRightStickX = 0.0f;
	m_LastControllerState.m_fRightStickY = 0.0f;	
}

const SControllerState& CInputManager::GetState() const
{
	return m_LastControllerState;
}

bool CInputManager::IsButtonDown(EButton p_eButton, const SControllerState& p_rState) const
{
    return (p_rState.m_nButtons & p_eButton) != 0;
}

void CInputManager::Update(float fElapsed)
{
	if (m_pInputDevice == NULL)
		return;
	
	//Get latest state from input handler
	ZeroState();
	m_pInputDevice->GetInputState(m_LastControllerState);

	//Map to input types
	//Add to event queue
}