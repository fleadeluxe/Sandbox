//
//  TestEntity.cpp
//  Sandbox
//
//  Created by Jack Smith on 3/12/11.
//  Copyright (c) 2011 --. All rights reserved.
//

#include "TestEntity.h"
#include "../Components/RenderComponent.h"
#include "../Components/PositionComponent.h"

#include "Logger.h"

static const float g_paddleSpeed = 500.0f;
static const float g_paddleSpeedMin = g_paddleSpeed * -1.0f;

CTestEntity::CTestEntity(int nWidth, int nHeight,
                 const glm::vec2& vStartPos)
: CGameEntity()
, m_nWidth(nWidth)
, m_nHeight(nHeight)
{
    m_Indices.push_back(0);
    m_Indices.push_back(1);
    m_Indices.push_back(3);
    
    m_Indices.push_back(1);
    m_Indices.push_back(2);
    m_Indices.push_back(3);
    
    GetPositionComponent()->SetPosition(vStartPos);
    GetPositionComponent()->SetMaxSpeed(g_paddleSpeed);
}

void CTestEntity::Update(float p_fDelta, const SControllerState &p_rState)
{
    GetPositionComponent()->DoWork(p_fDelta, p_rState);
}

void CTestEntity::PreRender()
{
    if (m_pRenderer == NULL)
        return;
    
    m_Vertices.clear();
    
    const glm::vec2& vPos = GetPositionComponent()->GetPosition();
    
    m_Vertices.push_back(vPos.x - m_nWidth);
    m_Vertices.push_back(vPos.y - m_nHeight);
    m_Vertices.push_back(0.0f);
    
    m_Vertices.push_back(vPos.x + m_nWidth);
    m_Vertices.push_back(vPos.y - m_nHeight);
    m_Vertices.push_back(0.0f);
    
    m_Vertices.push_back(vPos.x + m_nWidth);
    m_Vertices.push_back(vPos.y + m_nHeight);
    m_Vertices.push_back(0.0f);
    
    m_Vertices.push_back(vPos.x - m_nWidth);
    m_Vertices.push_back(vPos.y + m_nHeight);
    m_Vertices.push_back(0.0f);
    
    BindRenderData(m_Vertices, m_Indices, m_pRenderer->GetRenderBatch());
}