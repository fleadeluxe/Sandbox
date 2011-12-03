//
//  Paddle.h
//  Sandbox
//
//  Created by Jack Smith on 3/12/11.
//  Copyright (c) 2011. All rights reserved.
//

#ifndef Sandbox_Paddle_h
#define Sandbox_Paddle_h

#include "GameEntity.h"

class CPaddle : public CGameEntity
{
public:
    CPaddle(int nWidth, int nHeight);
    
    void Update(float p_fDelta, const SControllerState& p_rState);
    void PreRender();
    
private:
    int m_nWidth;
    int m_nHeight;
};

#endif
