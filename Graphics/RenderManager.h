/*
 *  RenderManager.h
 *  Sandbox
 *
 *  Created by Jack Smith on 11/07/11.
 *  Copyright 2011 JackCorp. All rights reserved.
 *
 */

#ifndef RENDER_MANAGER_H_INCLUDED
#define RENDER_MANAGER_H_INCLUDED

#include <vector>
#include "includes.h"

class SDL_Surface;
class CCamera;
class CGameEntity;
class CComponent;

struct SRenderBatch;

class CRenderManager
{
public:
	CRenderManager();
	
	bool Initialise(int p_nWidth, int p_nHeight);
	void Uninitialise();
	
	void SetCamera(CCamera* p_pCamera);
    
    SRenderBatch*    GetRenderBatch();
    void             ReleaseRenderBatch(SRenderBatch* p_pBatch, bool p_bErase = true);
	
    typedef std::vector<CComponent*> TRenderComps;
	void Render(const TRenderComps& p_rComps);
	
private:
	
	void BuildProjectionMatrix(glm::mat4& p_rMatrix,
							   float p_fFOV,
							   float p_fAspect,
							   float p_fZNear,
							   float p_fZFar);
	
	SDL_Surface*	m_pDrawContext;
	CCamera*		m_pCamera;
	
    typedef std::vector<SRenderBatch*> TRenderBatches;
    TRenderBatches  m_vBatches;
    
	int m_nWindowWidth;
	int m_nWindowHeight;
};

#endif //RENDER_MANAGER_H_INCLUDED