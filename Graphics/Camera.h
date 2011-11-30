/*
 *  Camera.h
 *  Sandbox
 *
 *  Created by Jack Smith on 10/08/11.
 *  Copyright 2011 . All rights reserved.
 *
 */

#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "includes.h"
#include "InputConstants.h"

class CCamera
{
public:
	CCamera(const glm::vec3& p_rvPosition);
	
	void SetView();
	
	const glm::vec3& GetPosition() const;
	const glm::vec3& GetRight() const;
	const glm::vec3& GetUp() const;
	const glm::vec3& GetForward() const;
	
	void Update(float p_fElapsed, const SControllerState& p_rState);
	
	void SetPosition(const glm::vec3& p_rvPosition);
	
	void LocalTranslate(const glm::vec3& p_rvTranslate, float p_fDistance);
	void WorldTranslate(const glm::vec3& p_rvTranslate, float p_fDistance);
	
	void LocalRotate(const glm::vec3& p_rvRotAxis, float p_fAngleDeg);
	void WorldRotate(const glm::vec3& p_rvRotAxis, float p_fAngleDeg);
	
private:
	
	int m_nSpeed;
	
	glm::vec3 m_vRight; 
	glm::vec3 m_vUp;
	glm::vec3 m_vForward;
	
	glm::vec3 m_vPosition;
	
	glm::mat4 m_mTransform;
};

#endif //CAMERA_H_INCLUDED