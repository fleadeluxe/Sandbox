//
//  RenderComponent.h
//  Sandbox
//
//  Created by Jack Smith on 26/11/11.
//  Copyright (c) 2011. All rights reserved.
//

#ifndef Sandbox_RenderComponent_h
#define Sandbox_RenderComponent_h

#include "Component.h"

struct SRenderBatch;

class CRenderComponent : public CComponent
{
public:
    CRenderComponent();
    ~CRenderComponent();
    
    void DoWork(float p_fDelta) {};
    
    SRenderBatch* GetRenderBatch()
    {
        return m_pBatch;
    }
    
private:
    SRenderBatch* m_pBatch;
};

#endif
