//
//  World.cpp
//  Sandbox
//
//  Created by Jack Smith on 26/11/11.
//  Copyright (c) 2011. All rights reserved.
//

#include "World.h"

#include "../Entities/Paddle.h"

#include "includes.h"

#include <stdlib.h>

#define NUM_ENTITIES 20

CWorld::CWorld(int p_nWidth, int p_nHeight)
: m_nWidth(p_nWidth)
, m_nHeight(p_nHeight)
, m_bInitialised(false)
{
    
}

CWorld::~CWorld()
{
    if (m_bInitialised)
        Uninitialise();
}

bool CWorld::Initialise()
{
    m_vEntities.push_back(new CPaddle(10.0f, 5.0f));
    return true;
}

void CWorld::Uninitialise()
{
    for (TEntities::iterator iter = m_vEntities.begin(); iter != m_vEntities.end(); ++iter)
    {
        if ((*iter) != NULL)
        {
            delete (*iter);
        }
    }
    
    m_vEntities.clear();
}

void CWorld::Update(float p_fDelta, const SControllerState& p_rState)
{
    for (TEntities::iterator iter = m_vEntities.begin(); iter != m_vEntities.end(); ++iter)
    {
        if ((*iter) != NULL)
        {
            (*iter)->Update(p_fDelta, p_rState);
        }
    }
}

void CWorld::PreRender()
{
    for (TEntities::iterator iter = m_vEntities.begin(); iter != m_vEntities.end(); ++iter)
    {
        if ((*iter) != NULL)
        {
            (*iter)->PreRender();
        }
    }    
}