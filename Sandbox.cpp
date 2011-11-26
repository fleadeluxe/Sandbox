#include "includes.h"

#include "Sandbox.h"
#include "Graphics/RenderManager.h"
#include "Input/InputManager.h"

#include "Graphics/Camera.h"

#include "Utility/Utilities.h"
#include "Utility/ProfilerHelper.h"

#include "Entities/GameEntity.h"

#include "Components/ComponentFactory.h"

#include "World/World.h"

#include <stdlib.h>
#include <time.h>

CSandbox* g_pSandbox = NULL;

static int s_nWindowHeight = 640;
static int s_nWindowWidth = 1024;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    
	g_pSandbox = new CSandbox();
	
	if(g_pSandbox->Initialise() != false)
	{
		g_pSandbox->Run();
	}
	
	g_pSandbox->Deinitialise();
	
	delete g_pSandbox;

    return 0;
}

CSandbox::CSandbox()
:	m_pRenderManager(NULL)
,	m_pInputManager(NULL)
,	m_bInitialised(false) 
,	m_pCamera(NULL)
,   m_pWorld(NULL)
,   m_pComponentFactory(NULL)
{
	
}

CSandbox::~CSandbox()
{
	if (m_bInitialised)
	{
		Deinitialise();
	}
}

bool CSandbox::Initialise()
{	
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		return false;
	
	m_pRenderManager = new CRenderManager();
	
	if (!m_pRenderManager->Initialise(s_nWindowWidth, s_nWindowHeight))
		return false;
	
	m_pInputManager = new CInputManager();
	
	if (!m_pInputManager->Initialise(EInputDeviceType_Gamepad))
		return false;
	
	m_pCamera = new CCamera(glm::vec3(0.0f, 0.0f, -5.0f));
    
    m_pComponentFactory = new CComponentFactory();
    
    m_pWorld = new CWorld(10, 10);
    
    m_pWorld->Initialise();
    
    m_pComponentFactory->Initialise();
	
	m_pRenderManager->SetCamera(m_pCamera);

	m_bInitialised = true;
	
	return m_bInitialised;
}

void CSandbox::Run()
{
	if (!m_bInitialised)
	{
		return;
	}

	float fCurrentTime = 0.0f;
	bool bRun = true;
	
	while(bRun)
	{	
		PROFILER_NEW_FRAME;
		
		const float fNewTime = GetTime();
		float fDelta = fNewTime - fCurrentTime;
		fCurrentTime = fNewTime;
		
		PROFILE("Main Loop");
		
		{
			PROFILE("Update");
			
			m_pInputManager->Update(fDelta);
			
			const SControllerState& rState = m_pInputManager->GetState();
            
            m_pWorld->Update(fDelta, rState);
			
			m_pCamera->Update(fDelta, rState);
			
			bRun = !ShouldQuit(rState);
		}
        
        {
            PROFILE("PreRender");
            
            m_pWorld->PreRender();
        }
		
		{
			PROFILE("Render");
			m_pRenderManager->Render(m_pComponentFactory->GetComponentCollection(EComponentType_Renderer));
		}
	}
}

void CSandbox::Deinitialise()
{
	if (!m_bInitialised)
	{
		return;
	}
	
	if (m_pCamera != NULL)
	{
		m_pRenderManager->SetCamera(NULL);
		delete m_pCamera;
		m_pCamera = NULL;
	}
    
    if (m_pWorld != NULL)
    {
        m_pWorld->Uninitialise();
        delete m_pWorld;
        m_pWorld = NULL;
    }
    
    if (m_pComponentFactory != NULL)
    {
        m_pComponentFactory->Uninitialise();
        delete m_pComponentFactory;
        m_pComponentFactory = NULL;
    }
	
	if (m_pInputManager != NULL)
	{
		m_pInputManager->Uninitialise();
		delete m_pInputManager;
		m_pInputManager = NULL;
	}
	
	if (m_pRenderManager != NULL)
	{
		m_pRenderManager->Uninitialise();
		delete m_pRenderManager;
		m_pRenderManager = NULL;
	}
	
	m_bInitialised = false;
}

bool CSandbox::ShouldQuit(const SControllerState& p_rState) const
{
	if (SDL_QuitRequested())
		return true;
    
    if ((p_rState.m_nButtons & CONTROLLER_START) != 0)
    {
        int i = 0;
        i = 3;
    }
	
	return ((p_rState.m_nButtons & CONTROLLER_START) != 0) && ((p_rState.m_nButtons & CONTROLLER_SELECT) != 0);
}
