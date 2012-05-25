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
class CPositionComponent;

class CGameEntity
{
public:
    CGameEntity();
    virtual ~CGameEntity();
    
    virtual void Update(float p_fDelta, const SControllerState& p_rState) = 0;
    virtual void PreRender() = 0;
    
    CPositionComponent* GetPositionComponent() const
    {
        assert(m_pPosition != NULL);
        return m_pPosition;
    }
    
protected:
    
    CRenderComponent* m_pRenderer;
    CPositionComponent* m_pPosition;
    
    TVertices   m_Vertices;
    TIndices    m_Indices;
};

#endif
