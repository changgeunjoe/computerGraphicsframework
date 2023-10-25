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
	
protected:
	glm::mat4x4 m_xmf4x4World;//월드 행렬
	glm::mat4x4 m_xmf4x4viewWorld=mat4(1.0f);//월드 행렬
	float f_Speed;
	vec3 v3_tmpScale=vec3(1.0f);
	vec3 v3_tmpRotate = vec3(0.0f);
public:
	virtual void BuildObject(GLuint& mShader, const char* fn);
	virtual void Render();
	vec3 GetPosition();
	void SetinitRotate(glm::vec3& Rotate);
	void SetinitScale(glm::vec3 &Scale);
	void SetScale(glm::vec3 &Scale);
	void SetPosition(glm::vec3& Position);
	void Rotate(float fPitch, float fYaw, float fRoll);
	void MoveDirection(glm::vec3& direction);
	CMesh* m_pMesh{ NULL };
	GLuint m_pShader{};
	


};

