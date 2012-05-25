//
//  Component.h
//  Sandbox
//
//  Created by Jack Smith on 26/11/11.
//  Copyright (c) 2011. All rights reserved.
//

#ifndef Sandbox_Component_h
#define Sandbox_Component_h

#include "includes.h"
#include "../Sandbox.h"

enum EComponentType
{
    EComponentType_Renderer = 0,
    EComponentType_Position = 1,
    
    EComponentType_MAX
};

class CComponent
{
public:
    CComponent(EComponentType p_eType)
    : m_eType(p_eType)
    , m_bInUse(false)
    {}
    
    virtual ~CComponent(){}
    
    virtual void DoWork(float p_fDelta) = 0;
    
    void SetInUse(bool p_bInUse)
    {
        m_bInUse = p_bInUse;
    }
    
    bool GetInUse() const 
    { 
        return m_bInUse; 
    }
    
    EComponentType GetType() const { return m_eType; }
    
private:
    bool            m_bInUse;
    EComponentType  m_eType;
};

#endif