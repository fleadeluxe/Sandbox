/*
 *  Camera.cpp
 *  Sandbox
 *
 *  Created by Jack Smith on 10/08/11.
 *  Copyright 2011 JackCorp. All rights reserved.
 *
 */

#include "Camera.h"

CCamera::CCamera(const glm::vec3& p_rvPosition)
:	m_vRight(1.0f, 0.0f, 0.0f)
,	m_vUp(0.0f, 1.0f, 0.0f)
,	m_vForward(0.0f, 0.0f, -1.0f)
,	m_vPosition(p_rvPosition)
,	m_mTransform(0)
,	m_nSpeed(10)
{
	m_mTransform[0] = glm::vec4(m_vRight.x, m_vRight.y, m_vRight.z, 0.0f);
	m_mTransform[1] = glm::vec4(m_vUp.x, m_vUp.y, m_vUp.z, 0.0f);
	m_mTransform[2] = glm::vec4(m_vForward.x, m_vForward.y, m_vForward.z, 0.0f);
	m_mTransform[3] = glm::vec4(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.0f);
}

void CCamera::Update(float p_fElapsed, const SControllerState& p_rState)
{	
	//Pitch
	LocalRotate(glm::vec3(1.0f, 0.0f, 0.0f), -1*((p_rState.m_fRightStickY * 90.0f)*p_fElapsed));
	
	//Yaw
	LocalRotate(glm::vec3(0.0f, 1.0f, 0.0f), -1*((p_rState.m_fRightStickX * 90.0f)*p_fElapsed));
	
	//Forward
	LocalTranslate(glm::vec3(0.0f, 0.0f, 1.0f), ((p_rState.m_fLeftStickY * m_nSpeed)*p_fElapsed));
	
	//Strafe
	LocalTranslate(glm::vec3(1.0f, 0.0f, 0.0f), ((p_rState.m_fLeftStickX * m_nSpeed)*p_fElapsed));
}

void CCamera::SetView()
{
	glMatrixMode(GL_MODELVIEW);
	
	glLoadIdentity();
	
	glm::mat4 viewMatrix(0);
	
	viewMatrix[0] = glm::vec4(m_mTransform[0].x, m_mTransform[1].x, m_mTransform[2].x, 0);
	viewMatrix[1] = glm::vec4(m_mTransform[0].y, m_mTransform[1].y, m_mTransform[2].y, 0);
	viewMatrix[2] = glm::vec4(m_mTransform[0].z, m_mTransform[1].z, m_mTransform[3].z, 0);
	
	float fX = -1*((m_mTransform[0].x * m_mTransform[3].x) +
				   (m_mTransform[0].y * m_mTransform[3].y) +
				   (m_mTransform[0].z * m_mTransform[3].z));
	
	float fY = -1*((m_mTransform[1].x * m_mTransform[3].x) +
				   (m_mTransform[1].y * m_mTransform[3].y) +
				   (m_mTransform[1].z * m_mTransform[3].z));
	
	float fZ = -1*((m_mTransform[2].x * m_mTransform[3].x) +
				   (m_mTransform[2].y * m_mTransform[3].y) +
				   (m_mTransform[2].z * m_mTransform[3].z));
	
	viewMatrix[3] = glm::vec4(fX, fY, fZ, 1.0f);
	
	glLoadMatrixf(glm::value_ptr(viewMatrix));
}

void CCamera::LocalTranslate(const glm::vec3& p_rvTranslate, float p_fDistance)
{
	float dx =	p_rvTranslate.x * m_mTransform[0].x + 
				p_rvTranslate.y * m_mTransform[1].x + 
				p_rvTranslate.z * m_mTransform[2].x;
	
	float dy =	p_rvTranslate.x * m_mTransform[0].y + 
				p_rvTranslate.y * m_mTransform[1].y + 
				p_rvTranslate.z * m_mTransform[2].y;
	
	float dz =	p_rvTranslate.x * m_mTransform[0].z + 
				p_rvTranslate.y * m_mTransform[1].z + 
				p_rvTranslate.z * m_mTransform[2].z;
	
	m_vPosition.x += dx * p_fDistance;
	m_vPosition.y += dy * p_fDistance;
	m_vPosition.z += dz * p_fDistance;
	
	m_mTransform[3].x = m_vPosition.x;
	m_mTransform[3].y = m_vPosition.y;
	m_mTransform[3].z = m_vPosition.z;
}

void CCamera::WorldTranslate(const glm::vec3& p_rvTranslate, float p_fDistance)
{
	m_vPosition.x += p_rvTranslate.x * p_fDistance;
	m_vPosition.y += p_rvTranslate.y * p_fDistance;
	m_vPosition.z += p_rvTranslate.z * p_fDistance;
	
	m_mTransform[3].x = m_vPosition.x;
	m_mTransform[3].y = m_vPosition.y;
	m_mTransform[3].z = m_vPosition.z;
}

void CCamera::LocalRotate(const glm::vec3& p_rvRotAxis, float p_fAngleDeg)
{
	glMatrixMode(GL_MODELVIEW);
		
	glPushMatrix();
		glLoadMatrixf(glm::value_ptr(m_mTransform));
		glRotatef(p_fAngleDeg, p_rvRotAxis.x, p_rvRotAxis.y, p_rvRotAxis.z);
		glGetFloatv(GL_MODELVIEW_MATRIX, glm::value_ptr(m_mTransform));
	glPopMatrix();	
}

void CCamera::WorldRotate(const glm::vec3& p_rvRotAxis, float p_fAngleDeg)
{
	float dx = p_rvRotAxis.x * m_mTransform[0].x + 
				p_rvRotAxis.y * m_mTransform[0].y + 
				p_rvRotAxis.z * m_mTransform[0].z;
	
	float dy = p_rvRotAxis.x * m_mTransform[1].x + 
				p_rvRotAxis.y * m_mTransform[1].y + 
				p_rvRotAxis.z * m_mTransform[1].z;
	
	float dz= p_rvRotAxis.x * m_mTransform[2].x + 
				p_rvRotAxis.y * m_mTransform[2].y + 
				p_rvRotAxis.z * m_mTransform[2].z;
	
	LocalRotate(glm::vec3(dx, dy, dz), p_fAngleDeg);
}

void CCamera::SetPosition(const glm::vec3& p_rvPosition)
{
	m_vPosition = p_rvPosition;
	m_mTransform[3].x = m_vPosition.x;
	m_mTransform[3].y = m_vPosition.y;
	m_mTransform[3].z = m_vPosition.z;
}

const glm::vec3& CCamera::GetPosition() const
{
	return m_vPosition;
}

const glm::vec3& CCamera::GetRight() const
{
	return m_vRight;
}

const glm::vec3& CCamera::GetUp() const
{
	return m_vUp;
}

const glm::vec3& CCamera::GetForward() const
{
	return m_vForward;
}