#include "stdafx.h"
#pragma once


class CVertex
{
public:
	glm::vec3  m_xmf3Coordinate;

public:
	CVertex() { m_xmf3Coordinate = glm::vec3(0.0f, 0.0f, 0.0f); }
	CVertex(glm::vec3 xmf3Coordinate) { m_xmf3Coordinate = xmf3Coordinate; }
	~CVertex() { }
};

class CMesh
{
public:
	CMesh();
	virtual ~CMesh();
public:

	UINT m_nSlot = 0;
	UINT m_nVertices = 0;
	UINT m_nStride = 0;
	UINT m_nOffset = 0;
	GLuint m_VBORect = 0;
	GLuint m_EBORect = 0;
	UINT m_nTextures = 0;
	UINT m_nNormals = 0;
	UINT m_nFaces = 0;

	vector<CVertex> m_vVertices;
	std::vector<unsigned int> m_nindices;
	vector<glm::vec2> m_vTextures;
	vector<glm::vec3> m_vNormals;
public:
	virtual void BuildCubeMesh(float fWidth, float fHeight, float fDepth);
	virtual void BuildObjMesh(const char* filename);

};

//정점을 표현하기 위한 클래스를 선언한다.
