//
//  RenderComponent.cpp
//  Sandbox
//
//  Created by Jack Smith on 26/11/11.
//  Copyright (c) 2011. All rights reserved.
//

#include "RenderComponent.h"

#include "../Graphics/GraphicsTypes.h"
#include "../Graphics/RenderManager.h"

CRenderComponent::CRenderComponent()
: CComponent(EComponentType_Renderer)
{
    m_pBatch = g_pSandbox->GetRenderManager()->GetRenderBatch();
}

CRenderComponent::~CRenderComponent()
{
    g_pSandbox->GetRenderManager()->ReleaseRenderBatch(m_pBatch);
}

