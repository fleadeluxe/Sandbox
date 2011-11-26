//
//  ComponentFactory.cpp
//  Sandbox
//
//  Created by Jack Smith on 26/11/11.
//  Copyright (c) 2011. All rights reserved.
//

#include "ComponentFactory.h"
#include "RenderComponent.h"

#include <algorithm>

#define MAX_COMPONENTS 10

CComponentFactory::CComponentFactory()
: m_bInitialised(false)
{
    for (int i = 0; i < EComponentType_MAX; ++i)
    {   
        std::pair<TComponentMap::iterator, bool> ret;
        ret = m_Components.insert(std::make_pair((EComponentType)(i), TComponentCollection()));
        (*(ret.first)).second.reserve(MAX_COMPONENTS);
    }
}

CComponentFactory::~CComponentFactory()
{
    if (m_bInitialised)
    {
        Uninitialise();
    }
}

bool CComponentFactory::Initialise()
{
    for (int i = 0; i < EComponentType_MAX; ++i)
    {   
        for (int j = 0; j < MAX_COMPONENTS; ++j)
        {
            EComponentType eType = (EComponentType)(i);
            CComponent* pComp = ConstructComponent(eType);
            
            if (pComp != NULL)
            {
                m_Components[eType].push_back(pComp);
            }
        }
    }
    
    m_bInitialised = true;
    
    return true;
}

CComponent* CComponentFactory::ConstructComponent(EComponentType p_eType)
{
    switch(p_eType)
    {
        case EComponentType_Renderer:
            return new CRenderComponent();
            break;
        default:
            break;
    }
    
    return NULL;
}

void CComponentFactory::Uninitialise()
{
    for (int i = 0; i < EComponentType_MAX; ++i)
    {
        EComponentType eType = (EComponentType)(i);        
        TComponentCollection& coll = m_Components[eType];
        
        for (TComponentCollection::iterator iter = coll.begin(); iter != coll.end(); ++iter)
        {
            CComponent* pComp = (*iter);
            if (pComp != NULL)
            {
                delete pComp;
            }
        }
        
        coll.clear();
    }
}

CComponent* CComponentFactory::GetComponent(EComponentType p_eType)
{
    TComponentCollection& coll = m_Components[p_eType];
    for(TComponentCollection::iterator iter = coll.begin(); iter != coll.end(); ++iter)
    {
        if (!(*iter)->GetInUse())
        {
            (*iter)->SetInUse(true);
            return (*iter);
        }
    }
    
    CComponent* pComp = ConstructComponent(p_eType);
    if (pComp != NULL)
    {
        pComp->SetInUse(true);
        coll.push_back(pComp);
        
        return pComp;
    }
    
    return NULL;
}

void CComponentFactory::ReleaseComponent(CComponent *p_pComponent)
{
    if (p_pComponent != NULL)
    {
        EComponentType eType = p_pComponent->GetType();
        TComponentCollection& coll = m_Components[eType];
        TComponentCollection::iterator found = std::find(coll.begin(), coll.end(), p_pComponent);
            
        if (found != coll.end())
        {
            (*found)->SetInUse(false);
        }
    }
}

const 
CComponentFactory::TComponentCollection& CComponentFactory::GetComponentCollection(EComponentType p_eType)
{
    return m_Components[p_eType];
}
