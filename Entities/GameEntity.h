//
//  GameEntity.h
//  Sandbox
//
//  Created by Jack Smith on 26/11/11.
//  Copyright (c) 2011. All rights reserved.
//

#ifndef Sandbox_GameEntity_h
#define Sandbox_GameEntity_h

#include "includes.h"
#include "InputConstants.h"

#include "../Graphics/GraphicsTypes.h"

#include <vector>

class CRenderComponent;

struct SEntityState
{
    glm::vec2 vPos;
    glm::vec2 vVel;
};

class CGameEntity
{
public:
    CGameEntity(const SEntityState& p_rInitialState, float p_fMaxSpeed);
    ~CGameEntity();
    
    void Update(float p_fDelta, const SControllerState& p_rState);
    void PreRender();
    
private:
    
    SEntityState    m_State;
    float           m_fMaxSpeed;
    
    CRenderComponent* m_pRenderer;
    
    TVertices   m_Vertices;
    TIndices    m_Indices;
    
    float m_fWidth;
    float m_fHeight;
};

#endif
