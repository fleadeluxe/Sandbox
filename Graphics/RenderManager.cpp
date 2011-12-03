/*
 *  RenderManager.cpp
 *  Sandbox
 *
 *  Created by Jack Smith on 11/07/11.
 *  Copyright 2011 . All rights reserved.
 *
 */

#include "RenderManager.h"
#include "GraphicsTypes.h"
#include "Camera.h"
#include "../Components/RenderComponent.h"

#include "Logger.h"

const float g_fFOV = 60.0f; //Degrees
const float g_fAspect = 1.3333f;
const float g_fZNear = 1.0f;
const float g_fZFar = 1000.0f;

const float g_fPIOver360 = M_PI/360.0f;

CRenderManager::CRenderManager()
:	m_pDrawContext(NULL)
,	m_pCamera(NULL)
,	m_nWindowWidth(0)
,	m_nWindowHeight(0)
{

}

bool CRenderManager::Initialise(int p_nWidth, int p_nHeight)
{	
    VLOG("New window. Width: %d Height: %d", p_nWidth, p_nHeight);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	
	m_pDrawContext = SDL_SetVideoMode(p_nWidth, p_nHeight, 0, SDL_OPENGL | 
															  SDL_GL_DOUBLEBUFFER | 
															  SDL_HWSURFACE);
	
	m_nWindowWidth = p_nWidth;
	m_nWindowHeight = p_nHeight;
	
	glClearColor(0, 0, 0, 0);
	
	glClearDepth(1.0f);
	
	glViewport(0, 0, m_nWindowWidth, m_nWindowHeight);
	
	glMatrixMode (GL_PROJECTION);
	
	glLoadIdentity ();
	
	glm::mat4 projMatrix(0);
	BuildProjectionMatrix(projMatrix, g_fFOV, g_fAspect, g_fZNear, g_fZFar);
	
	glLoadMatrixf(glm::value_ptr(projMatrix));
	
	glMatrixMode (GL_MODELVIEW);
	
	glEnable(GL_TEXTURE_2D);
    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    	
	glLoadIdentity();
	
	return true;
}

void CRenderManager::SetCamera(CCamera* p_pCamera)
{
	m_pCamera = p_pCamera;
}

void CRenderManager::BuildProjectionMatrix(glm::mat4& p_rMatrix,
										   float p_fFOV,
										   float p_fAspect,
										   float p_fZNear,
										   float p_fZFar)
{
	const float fHeight = 1.0f/tan(p_fFOV*g_fPIOver360);
	float fNegDepth = p_fZNear - p_fZFar;
	
	p_rMatrix[0] = glm::vec4(fHeight / p_fAspect, 0, 0, 0);
	p_rMatrix[1] = glm::vec4(0, fHeight, 0, 0);
	p_rMatrix[2] = glm::vec4(0, 0, (p_fZFar + p_fZNear)/fNegDepth, -1);
	p_rMatrix[3] = glm::vec4(0, 0, 2.0f*(p_fZNear*p_fZFar)/fNegDepth, 0);
}

void CRenderManager::Uninitialise()
{
    for (TRenderBatches::iterator iter = m_vBatches.begin(); iter != m_vBatches.end(); ++iter)
    {
        ReleaseRenderBatch(*iter, false);
    }
    
    m_vBatches.clear();
    
    SDL_Quit();
}

SRenderBatch* CRenderManager::GetRenderBatch()
{
    GLuint aBuffIds[2];
    
    glGenBuffers(2, &aBuffIds[0]);
    
    SRenderBatch* pBatch = new SRenderBatch;
    
    pBatch->m_gluVertexBufferId = aBuffIds[0];
    pBatch->m_gluIndexBufferId = aBuffIds[1];
    pBatch->m_uElements = 0;
    
    m_vBatches.push_back(pBatch);
    
    return pBatch;
}

void CRenderManager::ReleaseRenderBatch(SRenderBatch* p_pBatch, bool p_bErase /*= true*/)
{
    if (p_pBatch == NULL)
        return;
    
    const GLuint aBuffIds[2] = 
    {
        p_pBatch->m_gluVertexBufferId,
        p_pBatch->m_gluIndexBufferId
    };
    
    glDeleteBuffers(2, &aBuffIds[0]);
    
    if (p_bErase)
    {
        TRenderBatches::iterator found = std::find(m_vBatches.begin(), m_vBatches.end(), p_pBatch);
        if (found != m_vBatches.end())
        {
            m_vBatches.erase(found);
        }
    }
}

void CRenderManager::Render(const TRenderComps& p_rComps)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	if (m_pCamera != NULL)
		m_pCamera->SetView();
        
    for (TRenderComps::const_iterator citer = p_rComps.begin(); citer != p_rComps.end(); ++citer)
    {
        CRenderComponent* pComp = dynamic_cast<CRenderComponent*>(*citer);
        
        if (pComp != NULL && pComp->GetInUse())
        {
            SRenderBatch* pBatch = pComp->GetRenderBatch();
            glBindBuffer(GL_ARRAY_BUFFER, pBatch->m_gluVertexBufferId);
            
            glVertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
            
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pBatch->m_gluIndexBufferId);
            
            glEnableClientState(GL_VERTEX_ARRAY);
            
            glDrawElements(GL_TRIANGLES, pBatch->m_uElements, GL_UNSIGNED_INT, BUFFER_OFFSET(0));
                    
            glDisableClientState(GL_VERTEX_ARRAY);
        }
    }
	
	SDL_GL_SwapBuffers();
}