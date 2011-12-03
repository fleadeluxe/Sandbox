//
//  Paddle.cpp
//  Sandbox
//
//  Created by Jack Smith on 3/12/11.
//  Copyright (c) 2011 --. All rights reserved.
//

#include "Paddle.h"
#include "../Components/RenderComponent.h"

static const glm::vec2 g_zeroVec = glm::vec2(0.0f, 0.0f);

CPaddle::CPaddle(int nWidth, int nHeight)
: CGameEntity(SEntityState(g_zeroVec, g_zeroVec))
, m_nWidth(nWidth)
, m_nHeight(nHeight)
{}

void CPaddle::Update(float p_fDelta, const SControllerState &p_rState)
{
    m_State.vPos += m_State.vVel * p_fDelta;
    
    m_State.vVel = g_zeroVec;
    
    int nXMod = ((p_rState.m_nButtons & CONTROLLER_DPAD_LEFT) != 0) ? -1 : 0;
    nXMod += ((p_rState.m_nButtons & CONTROLLER_DPAD_RIGHT) != 0 ) ? 1 : 0;
    
    int nYMod = ((p_rState.m_nButtons & CONTROLLER_DPAD_DOWN) != 0) ? -1 : 0;
    nYMod += ((p_rState.m_nButtons & CONTROLLER_DPAD_UP) != 0 ) ? 1 : 0;
    
    m_State.vVel.x += 5.0f * nXMod;
    m_State.vVel.y += 5.0f * nYMod;
    
    glm::clamp(m_State.vVel.x, 5.0f * -1, 5.0f);
    glm::clamp(m_State.vVel.y, 5.0f * -1, 5.0f);
}

void CPaddle::PreRender()
{
    if (m_pRenderer == NULL)
        return;
    
    m_Vertices.clear();
    
    m_Vertices.push_back(m_State.vPos.x - m_nHeight);
    m_Vertices.push_back(m_State.vPos.y - m_nHeight);
    m_Vertices.push_back(0.0f);
    
    m_Vertices.push_back(m_State.vPos.x + m_nWidth);
    m_Vertices.push_back(m_State.vPos.y - m_nHeight);
    m_Vertices.push_back(0.0f);
    
    m_Vertices.push_back(m_State.vPos.x + m_nWidth);
    m_Vertices.push_back(m_State.vPos.y + m_nHeight);
    m_Vertices.push_back(0.0f);
    
    m_Vertices.push_back(m_State.vPos.x - m_nWidth);
    m_Vertices.push_back(m_State.vPos.y + m_nHeight);
    m_Vertices.push_back(0.0f);
    
    BindRenderData(m_Vertices, m_Indices, m_pRenderer->GetRenderBatch());
}