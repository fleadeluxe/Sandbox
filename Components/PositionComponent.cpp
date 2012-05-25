//
//  PositionComponent.cpp
//  Sandbox
//
//  Created by Jack Smith on 23/05/12.
//  Copyright (c) 2012 --. All rights reserved.
//

#include "PositionComponent.h"
#include "RenderManager.h"
#include "Sandbox.h"
#include "InputManager.h"
#include "Logger.h"

void CPositionComponent::DoWork(float p_fDelta)
{
    //Do nothing
}

void CPositionComponent::DoWork(float p_fDelta, const SControllerState &p_rState)
{
    m_vPos += m_vVel * p_fDelta;
    
    ClampToScreen();
    
    m_vVel = g_zeroVec;
    
    int nXMod = g_pSandbox->GetInputManager()->IsButtonDown(EButton_DPAD_Left, p_rState) ? -1 : 0;
    nXMod += g_pSandbox->GetInputManager()->IsButtonDown(EButton_DPAD_Right, p_rState) ? 1 : 0;
    
    int nYMod = g_pSandbox->GetInputManager()->IsButtonDown(EButton_DPAD_Down, p_rState) ? 1 : 0;
    nYMod += g_pSandbox->GetInputManager()->IsButtonDown(EButton_DPAD_Up, p_rState) ? -1 : 0;
    
    m_vVel.x += m_fMaxSpeed * nXMod;
    m_vVel.y += m_fMaxSpeed * nYMod;
    
    glm::clamp(m_vVel.x, m_fMaxSpeed * -1, m_fMaxSpeed);
    glm::clamp(m_vVel.y, m_fMaxSpeed * -1, m_fMaxSpeed);
}

void CPositionComponent::ClampToScreen()
{
    glm::vec2 vScreenSize = g_pSandbox->GetRenderManager()->GetScreenSize();
    
    if (m_vPos.x < 0)
    {
        m_vPos.x = vScreenSize.x;
    }
    else if (m_vPos.x > vScreenSize.x)
    {
        m_vPos.x = 0;
    }
    
    if (m_vPos.y < 0)
    {
        m_vPos.y = vScreenSize.y;
    }
    else if (m_vPos.y > vScreenSize.y)
    {
        m_vPos.y = 0;
    }
}