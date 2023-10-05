#pragma once
#include"stdafx.h"
class CMesh;
class CShader;
class GameManager;
class CObject
{
public :
	CObject();
	virtual ~CObject();

private:
	int m_nReferences = 0;
public:
	void AddRef() { m_nReferences++; }
	void Release() { if (--m_nReferences <= 0)delete this; }
	bool ReadFile(char* filename, std::string* target);
	void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
	GLuint CompileShaders(char* filenameVS, char* filenameFS);
protected:
	glm::mat4x4 m_xmf4x4World;//월드 행렬
	float f_Speed;
public:
	virtual void BuildObject();
	virtual void Render();
	
	void MoveDirection(glm::vec3 direction);

	CMesh* m_pMesh = NULL;
	GLuint m_SolidRectShader = 0;


};

