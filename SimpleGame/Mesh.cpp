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

	// 첫 번째 삼각형
	m_nindices.push_back(0);
	m_nindices.push_back(1);
	m_nindices.push_back(2);

	// 두 번째 삼각형
	m_nindices.push_back(3);
	m_nindices.push_back(4);
	m_nindices.push_back(5);

	// 세 번째 삼각형
	m_nindices.push_back(6);
	m_nindices.push_back(7);
	m_nindices.push_back(8);

	// 네 번째 삼각형
	m_nindices.push_back(9);
	m_nindices.push_back(10);
	m_nindices.push_back(11);

	// 다섯 번째 삼각형
	m_nindices.push_back(12);
	m_nindices.push_back(13);
	m_nindices.push_back(14);

	// 여섯 번째 삼각형
	m_nindices.push_back(15);
	m_nindices.push_back(16);
	m_nindices.push_back(17);

	// 일곱 번째 삼각형
	m_nindices.push_back(18);
	m_nindices.push_back(19);
	m_nindices.push_back(20);

	// 여덟 번째 삼각형
	m_nindices.push_back(21);
	m_nindices.push_back(22);
	m_nindices.push_back(23);

	// 아홉 번째 삼각형
	m_nindices.push_back(24);
	m_nindices.push_back(25);
	m_nindices.push_back(26);

	// 열 번째 삼각형
	m_nindices.push_back(27);
	m_nindices.push_back(28);
	m_nindices.push_back(29);

	// 열한 번째 삼각형
	m_nindices.push_back(30);
	m_nindices.push_back(31);
	m_nindices.push_back(32);

	// 열두 번째 삼각형
	m_nindices.push_back(33);
	m_nindices.push_back(34);
	m_nindices.push_back(35);
	glGenBuffers(1, &m_VBORect);//
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);//vbo 버퍼를 만들어줄거야
	glBufferData(GL_ARRAY_BUFFER, m_vVertices.size()*sizeof(CVertex),
		m_vVertices.data(), GL_STATIC_DRAW);

}
void CMesh::BuildObjMesh(const char* filename)
{
	std::ifstream file{ filename };

	m_nVertices = 0;
	m_nTextures = 0;
	m_nNormals = 0;
	m_nFaces = 0;
	m_nStride = sizeof(CVertex);
	m_nOffset = 0;//지금 사용 x
	m_nSlot = 0;//지금 사용 x
	string count;
	//--- 1. 전체 버텍스 개수 및 삼각형 개수 세기
	while (!file.eof()) {
		file >> count;
		if (count[0] == 'v' && count.size() == 1)
			m_nVertices++;
		else if (count[0] == 'v' && count[1] == 't' && count.size() == 2)
			m_nTextures++;
		else if (count[0] == 'v' && count[1] == 'n' && count.size() == 2)
			m_nNormals++;
		else if (count[0] == 'f' && count.size() == 1)
			m_nFaces++;
	}


	// 파일 포인터를 다시 파일의 처음으로 이동
	file.clear(); // 에러 플래그를 초기화
	file.seekg(0, std::ios::beg);

	int v = 0, t = 0, n = 0, f = 0;
	string bind;
	float fx, fy, fz;


	m_vVertices.resize(m_nVertices);
	m_vTextures.resize(m_nTextures);
	m_vNormals.resize(m_nNormals);
	m_nindices.resize(m_nFaces * 3);

	while (1) {
		file >> bind;
		if (file.eof())break;
		if (bind[0] == 'v' && bind.size() == 1) {
			file >> fx >> fy >> fz;
			m_vVertices[v++] = glm::vec3(fx , fy , fz );
		}
		else if (bind[0] == 'v' && bind[1] == 't' && bind.size() == 2) {
			file >> fx >> fy;
			m_vTextures[t++] = glm::vec2(fx, fy);
		}
		else if (bind[0] == 'v' && bind[1] == 'n' && bind.size() == 2) {
			file >> fx >> fy >> fz;
			m_vNormals[n++] = glm::vec3(fx, fy, fz);
		}
		else if (bind[0] == 'f' && bind.size() == 1) {
			unsigned int v[3], t[3], n[3];
			char ch;
			for (int c = 0; c < 3; ++c)
				file >> v[c] >> ch >> t[c] >> ch >> n[c];
			for (int c = 0; c < 3; ++c)
				m_nindices[f++] = v[c] - 1;
		}
	}


	glGenBuffers(1, &m_VBORect);//
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);//vbo 버퍼를 만들어줄거야
	glBufferData(GL_ARRAY_BUFFER, m_vVertices.size() * sizeof(CVertex),
		m_vVertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &m_EBORect);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBORect);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * m_nFaces * 3, m_nindices.data(), GL_STATIC_DRAW);

}