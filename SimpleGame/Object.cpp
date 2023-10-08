#pragma once
#include "stdafx.h"
#include "Object.h"
#include "Mesh.h"

class GameMananger;

CObject::CObject()
{
	m_pMesh = new CMesh;
	m_xmf4x4World = glm::mat4(1.0f);
	f_Speed = 0.1f;
}

CObject::~CObject()
{
	delete m_pMesh;
}



void CObject::BuildObject(GLuint& mShader)
{
	m_pMesh->BuildCubeMesh(0.5,0.5,0.5);//큐브 메쉬 만들기
	m_pShader = mShader;
	
}

void CObject::Render( )
{
	glUseProgram(m_pShader);


	int posLoc = glGetAttribLocation(m_pShader, "a_Position");
	glEnableVertexAttribArray(posLoc);
	glBindBuffer(GL_ARRAY_BUFFER, m_pMesh->m_VBORect);
	glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE,
		sizeof(float) * 3, 0);

	
	glUniformMatrix4fv(glGetUniformLocation(m_pShader, "u_WorldMatrix"),1, GL_FALSE, glm::value_ptr(m_xmf4x4World));

	glDrawArrays(GL_TRIANGLES, 0, 36);//레스터라이제이션
}

void CObject::SetinitScale(glm::vec3 &Scale)
{
	glm::mat4 tmpxmf4x4world = m_xmf4x4World;
	glm::mat4 initmatrix = glm::mat4(1.0f);
	m_xmf4x4World = glm::scale(initmatrix, Scale);//자전
	m_xmf4x4World[3] = tmpxmf4x4world[3];
	m_xmf4x4World = glm::rotate(m_xmf4x4World, glm::radians(v3_tmpRotate.x), glm::vec3(1.0, 0, 0));//자전
	m_xmf4x4World = glm::rotate(m_xmf4x4World, glm::radians(v3_tmpRotate.y), glm::vec3(0, 1.0, 0));//자전
	m_xmf4x4World = glm::rotate(m_xmf4x4World, glm::radians(v3_tmpRotate.z), glm::vec3(0, 0, 1.0));//자전
}

void CObject::SetScale(glm::vec3 &Scale)
{
	m_xmf4x4World = glm::scale(m_xmf4x4World, Scale);//자전
}

void CObject::Rotate(float fPitch, float fYaw, float fRoll)
{
	v3_tmpRotate += vec3(fPitch, fYaw, fRoll);
}

void CObject::MoveDirection(glm::vec3 &direction)
{
	m_xmf4x4World = glm::translate(m_xmf4x4World, direction* f_Speed);
}

void CObject::SetPosition(glm::vec3 &Position)
{
	m_xmf4x4World = glm::translate(m_xmf4x4World, Position );
}


