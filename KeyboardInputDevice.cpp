//
//  KeyboardInputDevice.cpp
//  Sandbox
//
//  Created by Jack Smith on 26/11/11.
//  Copyright (c) 2011. All rights reserved.
//

#include "KeyboardInputDevice.h"
#include "includes.h"

void CKeyboardInputDevice::EnumerateKeys(SControllerState& p_rState)
{
    int nLeftXMod = 0;
    int nLeftYMod = 0;
    int nRightXMod = 0;
    int nRightYMod = 0;
    
    int nKeysSize = 0;
    Uint8* pKeys = SDL_GetKeyState(&nKeysSize);
    
    for (int i = 0; i < nKeysSize; ++i)
    {
        if (pKeys[i] == 1)
        {
            switch((SDLKey)(i))
            {
                case SDLK_w:
                    nLeftYMod += -1;
                    break;
                case SDLK_s:
                    nLeftYMod += 1;
                    break;
                case SDLK_d:
                    nLeftXMod += 1;
                    break;
                case SDLK_a:
                    nLeftXMod += -1;
                    break;
                case SDLK_UP:
                    nRightYMod += 1;
                    break;
                case SDLK_DOWN:
                    nRightYMod += -1;
                    break;
                case SDLK_RIGHT:
                    nRightXMod += 1;
                    break;
                case SDLK_LEFT:
                    nRightXMod += -1;
                    break;
                case SDLK_SPACE:
                    p_rState.m_nButtons |=  CONTROLLER_START;
                    break;
                case SDLK_ESCAPE:
                    p_rState.m_nButtons |= CONTROLLER_SELECT;
                    break;
                case SDLK_k:
                    p_rState.m_nButtons |=  CONTROLLER_DPAD_DOWN;
                    break;
                case SDLK_i:
                    p_rState.m_nButtons |= CONTROLLER_DPAD_UP;
                    break;
                case SDLK_j:
                    p_rState.m_nButtons |=  CONTROLLER_DPAD_LEFT;
                    break;
                case SDLK_l:
                    p_rState.m_nButtons |= CONTROLLER_DPAD_RIGHT;
                    break;     
                default:
                    break;
            }
        }
    }
    
    p_rState.m_fLeftStickX = (float)(nLeftXMod);
    p_rState.m_fLeftStickY = (float)(nLeftYMod);
    
    p_rState.m_fRightStickX = (float)(nRightXMod);
    p_rState.m_fRightStickY = (float)(nRightYMod);
}

void CKeyboardInputDevice::GetInputState(SControllerState& p_rState)
{	
	SDL_PumpEvents();
	
    EnumerateKeys(p_rState);
}
