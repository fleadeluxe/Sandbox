//
//  World.h
//  Sandbox
//
//  Created by Jack Smith on 26/11/11.
//  Copyright (c) 2011. All rights reserved.
//

#ifndef Sandbox_World_h
#define Sandbox_World_h

#include <vector>
#include "../Input/InputConstants.h"

class CGameEntity;

class CWorld
{
public:
    CWorld();
    ~CWorld();
    
    bool Initialise();
    void Uninitialise();
    
    void Update(float p_fDelta, const SControllerState& p_rState);
    void PreRender();
    
private:
    typedef std::vector<CGameEntity*> TEntities;
    
    TEntities m_vEntities;
    
    bool m_bInitialised;
};

#endif
