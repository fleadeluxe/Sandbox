//
//  ComponentFactory.h
//  Sandbox
//
//  Created by Jack Smith on 26/11/11.
//  Copyright (c) 2011. All rights reserved.
//

#ifndef Sandbox_ComponentFactory_h
#define Sandbox_ComponentFactory_h

#include "Component.h"

#include <vector>
#include <map>

class CComponentFactory
{
public:
    CComponentFactory();
    ~CComponentFactory();
    
    bool Initialise();
	void Uninitialise();
    
    CComponent*  GetComponent(EComponentType p_eType);
    void        ReleaseComponent(CComponent* p_pComponent);

    typedef std::vector<CComponent*> TComponentCollection;

    const TComponentCollection&  GetComponentCollection(EComponentType p_eType);
    
private:
    
    CComponent* ConstructComponent(EComponentType p_eType);
    
    typedef std::map<EComponentType, TComponentCollection> TComponentMap;
    
    TComponentMap   m_Components;
    
    bool m_bInitialised;
};

#define REGISTER_COMPONENT(class, type)  \
    dynamic_cast<class*>(g_pSandbox->GetComponentFactory()->GetComponent(type))
#define UNREGISTER_COMPONENT(ptr)  \
    g_pSandbox->GetComponentFactory()->ReleaseComponent(m_pRenderer)

#endif
