//
//  TestEntity.h
//  Sandbox
//
//  Created by Jack Smith on 3/12/11.
//  Copyright (c) 2011. All rights reserved.
//

#ifndef Sandbox_TestEntity_h
#define Sandbox_TestEntity_h

#include "GameEntity.h"

class CTestEntity : public CGameEntity
{
public:
    CTestEntity(int nWidth, int nHeight, const glm::vec2& vStartPos);
    
    void Update(float p_fDelta, const SControllerState& p_rState);
    void PreRender();
    
private:
    int m_nWidth;
    int m_nHeight;
};

#endif
