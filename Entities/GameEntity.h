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
    SEntityState(glm::vec2 pos, glm::vec2 vel)
    : vPos(pos)
    , vVel(vel)
    {}
    
    glm::vec2 vPos;
    glm::vec2 vVel;
};

class CGameEntity
{
public:
    CGameEntity(const SEntityState& p_rInitialState);
    virtual ~CGameEntity();
    
    virtual void Update(float p_fDelta, const SControllerState& p_rState) = 0;
    virtual void PreRender() = 0;
    
protected:
    
    SEntityState    m_State;
    
    CRenderComponent* m_pRenderer;
    
    TVertices   m_Vertices;
    TIndices    m_Indices;
};

#endif
