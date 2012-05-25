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
#include "../Components/PositionComponent.h"
#include "../Components/ComponentFactory.h"

CGameEntity::CGameEntity()
: m_pRenderer(NULL)
, m_pPosition(NULL)
{
    m_pPosition = REGISTER_COMPONENT(CPositionComponent, EComponentType_Position);
    m_pRenderer = REGISTER_COMPONENT(CRenderComponent, EComponentType_Renderer);
}

CGameEntity::~CGameEntity()
{
    UNREGISTER_COMPONENT(m_pPosition);
    UNREGISTER_COMPONENT(m_pRenderer);
    
    m_pPosition = NULL;
    m_pRenderer = NULL;
}