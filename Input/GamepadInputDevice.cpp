/*
 *  GamepadInputDevice.cpp
 *  Sandbox
 *
 *  Created by Jack Smith on 6/08/11.
 *  Copyright 2011 . All rights reserved.
 *
 */
	
#include "GamepadInputDevice.h"

CGamepadInputDevice::CGamepadInputDevice(int m_nIndex)
: m_pGamepad(NULL)
, m_eType(EGamepadType_Unknown)
, m_nNumAxes(0)
, m_nNumButtons(0)
{
	m_pGamepad = SDL_JoystickOpen(m_nIndex);
	
	if (m_pGamepad != NULL)
	{
		m_nNumAxes = SDL_JoystickNumAxes(m_pGamepad);
		m_nNumButtons = SDL_JoystickNumButtons(m_pGamepad);
		
		if (strcmp(SDL_JoystickName(m_nIndex), CONTROLLER_NAME_PS3) == 0)
		{
			m_eType = EGamepadType_PS3;
		}
	}
}

CGamepadInputDevice::~CGamepadInputDevice()
{
	if (m_pGamepad != NULL)
	{
		SDL_JoystickClose(m_pGamepad);
		m_pGamepad = NULL;
	}
}

void CGamepadInputDevice::EnumeratePS3Axes(SControllerState& p_rState)
{
	for (int i = 0; i < m_nNumAxes; ++i)
	{
		int nAxisVal = SDL_JoystickGetAxis(m_pGamepad, i);
		int nMod = nAxisVal < 0 ? -1 : 1;
		nAxisVal *= nMod;
		
		float fStickVal = 0.0f;
		
		if (nAxisVal > AXIS_DEADZONE)
		{
			fStickVal = (float)((float)nAxisVal/SIGNED_INT_16_MAX) * nMod;
		}
	
		switch((EPS3RawAxesIndex)(i))
		{
			case EPS3RawAxesIndex_LeftX:
				p_rState.m_fLeftStickX = fStickVal;
				break;
			case EPS3RawAxesIndex_LeftY:
				p_rState.m_fLeftStickY = fStickVal;
				break;
			case EPS3RawAxesIndex_RightX:
				p_rState.m_fRightStickX = fStickVal;
				break;
			case EPS3RawAxesIndex_RightY:
				p_rState.m_fRightStickY = fStickVal;
				break;
			default:
				continue;
		}
	}
}

void CGamepadInputDevice::EnumeratePS3Buttons(SControllerState& p_rState)
{
	for (int i = 0; i < m_nNumButtons; ++i)
	{
		bool bDown = SDL_JoystickGetButton(m_pGamepad, i) == 1;
		
		if (bDown)
			std::cout << "Button [" << i << "] down" << std::endl;
		
		switch((EPS3RawButtonIndex)(i))
		{
			case EPS3RawButtonIndex_Select:
				bDown ? p_rState.m_nButtons |= CONTROLLER_SELECT : 
						p_rState.m_nButtons &= ~(CONTROLLER_SELECT);
				break;
			case EPS3RawButtonIndex_JoyClickLeft:
				bDown ? p_rState.m_nButtons |=  CONTROLLER_JOY_CLICK_LEFT : 
						p_rState.m_nButtons &= ~(CONTROLLER_JOY_CLICK_LEFT);
				break;
			case EPS3RawButtonIndex_JoyClickRight:
				bDown ? p_rState.m_nButtons |=  CONTROLLER_JOY_CLICK_RIGHT : 
						p_rState.m_nButtons &= ~(CONTROLLER_JOY_CLICK_RIGHT);
				break;
			case EPS3RawButtonIndex_Start:
				bDown ? p_rState.m_nButtons |=  CONTROLLER_START : 
						p_rState.m_nButtons &= ~(CONTROLLER_START);
				break;
			case EPS3RawButtonIndex_DpadUp:
				bDown ? p_rState.m_nButtons |=  CONTROLLER_DPAD_UP : 
						p_rState.m_nButtons &= ~(CONTROLLER_DPAD_UP);
				break;
			case EPS3RawButtonIndex_DpadRight:
				bDown ? p_rState.m_nButtons |=  CONTROLLER_DPAD_RIGHT : 
						p_rState.m_nButtons &= ~(CONTROLLER_DPAD_RIGHT);
				break;
			case EPS3RawButtonIndex_DpadDown:
				bDown ? p_rState.m_nButtons |=  CONTROLLER_DPAD_DOWN : 
						p_rState.m_nButtons &= ~(CONTROLLER_DPAD_DOWN);
				break;
			case EPS3RawButtonIndex_DpadLeft:
				bDown ? p_rState.m_nButtons |=  CONTROLLER_DPAD_LEFT : 
						p_rState.m_nButtons &= ~(CONTROLLER_DPAD_LEFT);
				break;
			case EPS3RawButtonIndex_TriggerLeft:
				bDown ? p_rState.m_nButtons |=  CONTROLLER_LEFT_TRIGGER : 
						p_rState.m_nButtons &= ~(CONTROLLER_LEFT_TRIGGER);
				break;
			case EPS3RawButtonIndex_TriggerRight:
				bDown ? p_rState.m_nButtons |=  CONTROLLER_RIGHT_TRIGGER : 
						p_rState.m_nButtons &= ~(CONTROLLER_RIGHT_TRIGGER);
				break;
			case EPS3RawButtonIndex_ShoulderLeft:
				bDown ? p_rState.m_nButtons |=  CONTROLLER_LEFT_SHOULDER : 
						p_rState.m_nButtons &= ~(CONTROLLER_LEFT_SHOULDER);
				break;
			case EPS3RawButtonIndex_ShoulderRight:
				bDown ? p_rState.m_nButtons |=  CONTROLLER_RIGHT_SHOULDER : 
						p_rState.m_nButtons &= ~(CONTROLLER_RIGHT_SHOULDER);
				break;				
			case EPS3RawButtonIndex_Triangle:
				bDown ? p_rState.m_nButtons |=  CONTROLLER_BUTTON_TOP : 
						p_rState.m_nButtons &= ~(CONTROLLER_BUTTON_TOP);
				break;
			case EPS3RawButtonIndex_Circle:
				bDown ? p_rState.m_nButtons |=  CONTROLLER_BUTTON_RIGHT : 
						p_rState.m_nButtons &= ~(CONTROLLER_BUTTON_RIGHT);
				break;
			case EPS3RawButtonIndex_Cross:
				bDown ? p_rState.m_nButtons |=  CONTROLLER_BUTTON_BOTTOM : 
						p_rState.m_nButtons &= ~(CONTROLLER_BUTTON_BOTTOM);
				break;
			case EPS3RawButtonIndex_Square:
				bDown ? p_rState.m_nButtons |=  CONTROLLER_BUTTON_LEFT : 
						p_rState.m_nButtons &= ~(CONTROLLER_BUTTON_LEFT);
				break;
			case EPS3RawButtonIndex_PSButton:
				//There's no room left! :(
				break;				
			default:
				break;
		}
	}
}

void CGamepadInputDevice::GetInputState(SControllerState& p_rState)
{
	if (m_pGamepad == NULL)
	{
		p_rState.m_nButtons = 0;
		
		p_rState.m_fLeftStickX = 0.0f;
		p_rState.m_fLeftStickY = 0.0f;
		
		p_rState.m_fRightStickX = 0.0f;
		p_rState.m_fRightStickY = 0.0f;
		
		return;
	}
	
	SDL_JoystickUpdate();
	
	switch(m_eType)
	{
		case EGamepadType_PS3:
		{
			EnumeratePS3Axes(p_rState);
			EnumeratePS3Buttons(p_rState);
		}
		break;
        case EGamepadType_Unknown:
        default:
            return;
	}
}