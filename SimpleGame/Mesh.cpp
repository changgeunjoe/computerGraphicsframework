#pragma once
#include"stdafx.h"
#include"Mesh.h"
#pragma once

CMesh::CMesh()
{
}

CMesh::~CMesh()
{
}

void CMesh::BuildCubeMesh(float fWidth, float fHeight, float fDepth)
{
	m_nVertices = 36;
	m_nStride = sizeof(CVertex);
	m_nOffset = 0;//지금 사용 x
	m_nSlot = 0;//지금 사용 x
	float fx = fWidth * 0.5f, fy = fHeight * 0.5f, fz = fDepth * 0.5f;
	
	int i = 0;

	vector<CVertex> m_vVertices;
	m_vVertices.resize(36);
	m_vVertices[i++] = CVertex(glm::vec3(-fx, +fy, -fz));
	m_vVertices[i++] = CVertex(glm::vec3(+fx, +fy, -fz));
	m_vVertices[i++] = CVertex(glm::vec3(+fx, -fy, -fz));
					 
	m_vVertices[i++] = CVertex(glm::vec3(-fx, +fy, -fz));
	m_vVertices[i++] = CVertex(glm::vec3(+fx, -fy, -fz));
	m_vVertices[i++] = CVertex(glm::vec3(-fx, -fy, -fz));
					 
	m_vVertices[i++] = CVertex(glm::vec3(-fx, +fy, +fz));
	m_vVertices[i++] = CVertex(glm::vec3(+fx, +fy, +fz));
	m_vVertices[i++] = CVertex(glm::vec3(+fx, +fy, -fz));
					 
	m_vVertices[i++] = CVertex(glm::vec3(-fx, +fy, +fz));
	m_vVertices[i++] = CVertex(glm::vec3(+fx, +fy, -fz));
	m_vVertices[i++] = CVertex(glm::vec3(-fx, +fy, -fz));
					 
	m_vVertices[i++] = CVertex(glm::vec3(-fx, -fy, +fz));
	m_vVertices[i++] = CVertex(glm::vec3(+fx, -fy, +fz));
	m_vVertices[i++] = CVertex(glm::vec3(+fx, +fy, +fz));
					 
	m_vVertices[i++] = CVertex(glm::vec3(-fx, -fy, +fz));
	m_vVertices[i++] = CVertex(glm::vec3(+fx, +fy, +fz));
	m_vVertices[i++] = CVertex(glm::vec3(-fx, +fy, +fz));
					 
	m_vVertices[i++] = CVertex(glm::vec3(-fx, -fy, -fz));
	m_vVertices[i++] = CVertex(glm::vec3(+fx, -fy, -fz));
	m_vVertices[i++] = CVertex(glm::vec3(+fx, -fy, +fz));
					 
	m_vVertices[i++] = CVertex(glm::vec3(-fx, -fy, -fz));
	m_vVertices[i++] = CVertex(glm::vec3(+fx, -fy, +fz));
	m_vVertices[i++] = CVertex(glm::vec3(-fx, -fy, +fz));
					
	m_vVertices[i++] = CVertex(glm::vec3(-fx, +fy, +fz));
	m_vVertices[i++] = CVertex(glm::vec3(-fx, +fy, -fz));
	m_vVertices[i++] = CVertex(glm::vec3(-fx, -fy, -fz));
					 
	m_vVertices[i++] = CVertex(glm::vec3(-fx, +fy, +fz));
	m_vVertices[i++] = CVertex(glm::vec3(-fx, -fy, -fz));
	m_vVertices[i++] = CVertex(glm::vec3(-fx, -fy, +fz));
					 
	m_vVertices[i++] = CVertex(glm::vec3(+fx, +fy, -fz));
	m_vVertices[i++] = CVertex(glm::vec3(+fx, +fy, +fz));
	m_vVertices[i++] = CVertex(glm::vec3(+fx, -fy, +fz));
					 
	m_vVertices[i++] = CVertex(glm::vec3(+fx, +fy, -fz));
	m_vVertices[i++] = CVertex(glm::vec3(+fx, -fy, +fz));
	m_vVertices[i++] = CVertex(glm::vec3(+fx, -fy, -fz));


	glGenBuffers(1, &m_VBORect);//
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);//vbo 버퍼를 만들어줄거야
	glBufferData(GL_ARRAY_BUFFER, m_vVertices.size()*sizeof(CVertex),
		m_vVertices.data(), GL_STATIC_DRAW);

}
