//
//  PositionComponent.cpp
//  Sandbox
//
//  Created by Jack Smith on 23/05/12.
//  Copyright (c) 2012 --. All rights reserved.
//

#include "PositionComponent.h"

void CPositionComponent::DoWork(float p_fDelta)
{
    //Do nothing
}

void CPositionComponent::DoWork(float p_fDelta, const SControllerState &p_rState)
{
    m_vPos += m_vVel * p_fDelta;
    m_vVel = g_zeroVec;
    
    //@todo: Make it easier to determine button state changes
    int nXMod = ((p_rState.m_nButtons & CONTROLLER_DPAD_LEFT) != 0) ? -1 : 0;
    nXMod += ((p_rState.m_nButtons & CONTROLLER_DPAD_RIGHT) != 0 ) ? 1 : 0;
    
    int nYMod = ((p_rState.m_nButtons & CONTROLLER_DPAD_DOWN) != 0) ? 1 : 0;
    nYMod += ((p_rState.m_nButtons & CONTROLLER_DPAD_UP) != 0 ) ? -1 : 0;
    
    m_vVel.x += m_fMaxSpeed * nXMod;
    m_vVel.y += m_fMaxSpeed * nYMod;
    
    glm::clamp(m_vVel.x, m_fMaxSpeed * -1, m_fMaxSpeed);
    glm::clamp(m_vVel.y, m_fMaxSpeed * -1, m_fMaxSpeed);
}