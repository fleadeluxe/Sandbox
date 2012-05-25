/*
 *  InputConstants.h
 *  Sandbox
 *
 *  Created by Jack Smith on 6/08/11.
 *  Copyright 2011 . All rights reserved.
 *
 */

#ifndef INPUT_CONSTANTS_H_INCLUDED
#define INPUT_CONSTANTS_H_INCLUDED

#define CONTROLLER_DPAD_UP			0x0001
#define CONTROLLER_DPAD_DOWN		0x0002
#define CONTROLLER_DPAD_LEFT		0x0004
#define CONTROLLER_DPAD_RIGHT		0x0008

#define CONTROLLER_START			0x0010
#define CONTROLLER_SELECT			0x0020

#define CONTROLLER_LEFT_TRIGGER		0x0040
#define CONTROLLER_RIGHT_TRIGGER	0x0080

#define CONTROLLER_LEFT_SHOULDER	0x0100
#define CONTROLLER_RIGHT_SHOULDER	0x0200

#define CONTROLLER_JOY_CLICK_LEFT	0x0400
#define CONTROLLER_JOY_CLICK_RIGHT	0x0800

#define CONTROLLER_BUTTON_BOTTOM	0x1000 //A, Cross
#define CONTROLLER_BUTTON_RIGHT		0x2000 //B, Circle
#define CONTROLLER_BUTTON_LEFT		0x4000 //X, Square
#define CONTROLLER_BUTTON_TOP		0x8000 //Y, Triangle

#define CONTROLLER_NAME_PS3 "PLAYSTATION(R)3 Controller"

#define SIGNED_INT_16_MAX 32768.0f
#define AXIS_DEADZONE 3276 //10% of max

struct SControllerState
{
	Uint16	m_nButtons;
	
	float	m_fLeftStickX;
	float	m_fLeftStickY;
	float	m_fRightStickX;
	float	m_fRightStickY;
};

enum EInputDeviceType
{
	EInputDeviceType_Unknown = 0,
	EInputDeviceType_Gamepad,
    EInputDeviceType_Keyboard,
	EInputDeviceType_InputFile,
	
	EInputDeviceType_Max
};

enum EGamepadType
{
	EGamepadType_Unknown = 0,
	EGamepadType_PS3
};

//Values SDL attributes to individual PS3 axes
enum EPS3RawAxesIndex
{
	EPS3RawAxesIndex_LeftX = 0,
	EPS3RawAxesIndex_LeftY = 1,
	EPS3RawAxesIndex_RightX = 2,
	EPS3RawAxesIndex_RightY = 3
};

//Values SDL attributes to individual PS3 controller buttons
enum EPS3RawButtonIndex
{
	EPS3RawButtonIndex_Select			= 0,
	
	EPS3RawButtonIndex_JoyClickLeft		= 1,
	EPS3RawButtonIndex_JoyClickRight	= 2,
	
	EPS3RawButtonIndex_Start			= 3,
	
	EPS3RawButtonIndex_DpadUp			= 4,
	EPS3RawButtonIndex_DpadRight		= 5,
	EPS3RawButtonIndex_DpadDown			= 6,
	EPS3RawButtonIndex_DpadLeft			= 7,
	
	EPS3RawButtonIndex_TriggerLeft		= 8,
	EPS3RawButtonIndex_TriggerRight		= 9,
	
	EPS3RawButtonIndex_ShoulderLeft		= 10,
	EPS3RawButtonIndex_ShoulderRight	= 11,
	
	EPS3RawButtonIndex_Triangle			= 12,
	EPS3RawButtonIndex_Circle			= 13,
	EPS3RawButtonIndex_Cross			= 14,
	EPS3RawButtonIndex_Square			= 15,
	
	EPS3RawButtonIndex_PSButton			= 16,
	
	EPS3RawButtonIndex_Invalid
};

#endif //INPUT_CONSTANTS_H_INCLUDED