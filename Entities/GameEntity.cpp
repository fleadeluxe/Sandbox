//
//  GameEntity.cpp
//  Sandbox
//
//  Created by Jack Smith on 26/11/11.
//  Copyright (c) 2011. All rights reserved.
//

#include "GameEntity.h"

#include "../Graphics/GraphicsTypes.h"

#include "../Components/RenderComponent.h"
#include "../Components/ComponentFactory.h"

static const glm::vec2 g_zeroVec = glm::vec2(0.0f, 0.0f);

CGameEntity::CGameEntity(const SEntityState& p_rInitialState,
                         float p_fMaxSpeed)
: m_State(p_rInitialState)
, m_fMaxSpeed(p_fMaxSpeed)
, m_fWidth(0.5f)
, m_fHeight(0.5f)
{
    m_pRenderer = dynamic_cast<CRenderComponent*>(g_pSandbox->GetComponentFactory()->GetComponent(EComponentType_Renderer));
    
    m_Indices.push_back(0);
    m_Indices.push_back(1);
    m_Indices.push_back(3);
    
    m_Indices.push_back(1);
    m_Indices.push_back(2);
    m_Indices.push_back(3);
}

CGameEntity::~CGameEntity()
{
    g_pSandbox->GetComponentFactory()->ReleaseComponent(m_pRenderer);
}

void CGameEntity::Update(float p_fDelta, const SControllerState &p_rState)
{
    m_State.vPos += m_State.vVel * p_fDelta;
    
    m_State.vVel = g_zeroVec;
    
    int nXMod = ((p_rState.m_nButtons & CONTROLLER_DPAD_LEFT) != 0) ? -1 : 0;
    nXMod += ((p_rState.m_nButtons & CONTROLLER_DPAD_RIGHT) != 0 ) ? 1 : 0;
    
    int nYMod = ((p_rState.m_nButtons & CONTROLLER_DPAD_DOWN) != 0) ? -1 : 0;
    nYMod += ((p_rState.m_nButtons & CONTROLLER_DPAD_UP) != 0 ) ? 1 : 0;
    
    m_State.vVel.x += m_fMaxSpeed * nXMod;
    m_State.vVel.y += m_fMaxSpeed * nYMod;
    
    glm::clamp(m_State.vVel.x, m_fMaxSpeed * -1, m_fMaxSpeed);
    glm::clamp(m_State.vVel.y, m_fMaxSpeed * -1, m_fMaxSpeed);
}

void CGameEntity::PreRender()
{
    if (m_pRenderer == NULL)
        return;
    
    m_Vertices.clear();
    
    m_Vertices.push_back(m_State.vPos.x - m_fWidth);
    m_Vertices.push_back(m_State.vPos.y - m_fHeight);
    m_Vertices.push_back(0.0f);
    
    m_Vertices.push_back(m_State.vPos.x + m_fWidth);
    m_Vertices.push_back(m_State.vPos.y - m_fHeight);
    m_Vertices.push_back(0.0f);
    
    m_Vertices.push_back(m_State.vPos.x + m_fWidth);
    m_Vertices.push_back(m_State.vPos.y + m_fHeight);
    m_Vertices.push_back(0.0f);
    
    m_Vertices.push_back(m_State.vPos.x - m_fWidth);
    m_Vertices.push_back(m_State.vPos.y + m_fHeight);
    m_Vertices.push_back(0.0f);
    
    BindRenderData(m_Vertices, m_Indices, m_pRenderer->GetRenderBatch());
}