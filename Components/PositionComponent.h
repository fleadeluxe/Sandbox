//
//  PositionComponent.h
//  Sandbox
//
//  Created by Jack Smith on 26/11/11.
//  Copyright (c) 2011. All rights reserved.
//

//Manage position, velocity and acceleration of the component owner

#ifndef Sandbox_PositionComponent_h
#define Sandbox_PositionComponent_h

#include "Component.h"

class CPositionComponent : public CComponent
{
public:
    CPositionComponent()
    : CComponent(EComponentType_Position)
    , m_vPos(g_zeroVec)
    , m_vVel(g_zeroVec)
    , m_vAccel(g_zeroVec)
    , m_fMaxSpeed(0.0f)
    {}
    ~CPositionComponent(){}
    
    void DoWork(float p_fDelta);
    void DoWork(float p_fDelta, const SControllerState &p_rState);
    
    const glm::vec2& GetPosition() const
    {
        return m_vPos;
    }
    
    const glm::vec2& GetVelocity() const
    {
        return m_vVel;
    }
    
    const glm::vec2& GetAcceleration() const
    {
        return m_vAccel;
    }
    
    float GetMaxSpeed() const
    {
        return m_fMaxSpeed;
    }
    
    const glm::vec2& SetPosition(const glm::vec2& p_vNewPos)
    {
        return (m_vPos = p_vNewPos);
    }
    
    const glm::vec2& SetVelocity(const glm::vec2& p_vNewVel)
    {
        return (m_vVel = p_vNewVel);
    }
    
    const glm::vec2& SetAcceleration(const glm::vec2& p_vNewAccel)
    {
        return (m_vAccel = p_vNewAccel);
    }
    
    float SetMaxSpeed(float p_fMaxSpeed)
    {
        return (m_fMaxSpeed = p_fMaxSpeed);
    }
    
private:
    
    void ClampToScreen();

    glm::vec2   m_vPos;
    glm::vec2   m_vVel;
    glm::vec2   m_vAccel;
    float       m_fMaxSpeed;
};

#endif
