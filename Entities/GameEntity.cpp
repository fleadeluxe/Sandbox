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

CGameEntity::CGameEntity(const SEntityState& p_rInitialState)
: m_State(p_rInitialState)
{
    m_pRenderer = dynamic_cast<CRenderComponent*>(g_pSandbox->GetComponentFactory()->GetComponent(EComponentType_Renderer));
}

CGameEntity::~CGameEntity()
{
    g_pSandbox->GetComponentFactory()->ReleaseComponent(m_pRenderer);
}