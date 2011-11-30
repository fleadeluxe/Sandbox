/*
 *  Sandbox.h
 *  Sandbox
 *
 *  Created by Jack Smith on 11/07/11.
 *  Copyright 2011 . All rights reserved.
 *
 */
#ifndef SANDBOX_H_INCLUDED
#define SANDBOX_H_INCLUDED

class CRenderManager;
class CInputManager;
class CCamera;
class CComponentFactory;
class CWorld;

#include "InputConstants.h"

class CSandbox
{
public:
	CSandbox();
	~CSandbox();
	
	bool Initialise();
	void Run();
	void Deinitialise();
    
    CComponentFactory* GetComponentFactory() const
    {
        return m_pComponentFactory;
    }
    
    CRenderManager* GetRenderManager() const
    {
        return m_pRenderManager;
    }
	
private:
	
	bool ShouldQuit(const SControllerState& p_rState) const;
		
	CRenderManager* m_pRenderManager;
	CInputManager*	m_pInputManager;
    CComponentFactory* m_pComponentFactory;
	CWorld* m_pWorld;
	CCamera* m_pCamera;
	
	bool m_bInitialised;
};

extern CSandbox* g_pSandbox;

#endif //SANDBOX_H_INCLUDED