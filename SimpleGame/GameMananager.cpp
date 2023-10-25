#pragma once
#include "stdafx.h"
#include "GameMananager.h"
#include "Object.h"
#include "GUIMGR.h"
#include"Camera.h"
#include"Physx.h"

extern GUIMgr g_GUIMananger;

namespace DIRECTION {
	vec3 Moveforward = glm::vec3(0.0f, 0.0f, -1.0f);
	vec3 MoveBack = glm::vec3(0.0f, 0.0f, 1.0f);
	vec3 MoveRight = glm::vec3(1.0f, 0.0f, 0.0f);
	vec3 MoveLeft = glm::vec3(-1.0f, 0.0f, 0.0f);
	vec3 MoveUp = glm::vec3(0.0f, 1.0f, 0.0f);
	vec3 MoveDown = glm::vec3(0.0f, -1.0f, 0.0f);
}

GameMananager::GameMananager(int windowSizeX, int windowSizeY)
{
	Initialize(windowSizeX, windowSizeY);
}


GameMananager::~GameMananager()
{

}

void GameMananager::Initialize(int windowSizeX, int windowSizeY)
{
	//Set window size
	m_WindowSizeX = windowSizeX;
	m_WindowSizeY = windowSizeY;

	m_pPhysisc = new CPhysx;
	m_pPhysisc->init();
	m_pMainCamera = new CCamera;
	m_pMainCamera->SetPosition(vec3(0.0f, 6.0f, 9.0f));
	m_SolidRectShader = CompileShaders("./Shaders/SolidRect.vs", "./Shaders/SolidRect.fs");
}

void GameMananager::BuildObjects()
{

	m_pPhysisc->BuildActor();


	m_pCubeObject = new CObject;
	m_pCubeObject->BuildObject(m_SolidRectShader,"sqqq2.obj");
	m_ppObjects.emplace_back(m_pCubeObject);//큐브 오브젝트 넣기 
	physx::PxTriangleMesh* TriangleMesh = m_pPhysisc->CreateTriangleMesh(m_pCubeObject);
	m_pPhysisc->addDynamicTriangleMeshInstance(physx::PxTransform(physx::PxVec3(0.4f, 10.0f, 0.0f)), TriangleMesh);

	//physx::PxTriangleMesh* TriangleMesh = m_pPhysisc->CreateTriangleMesh(m_pCubeObject);
	//m_pPhysisc->addDynamicTriangleMeshInstance(physx::PxTransform(physx::PxVec3(0.4f, 10.0f, 0.0f)), TriangleMesh);

	m_pPlaneObject = new CObject;
	m_pPlaneObject->BuildObject(m_SolidRectShader, "sqqq2.obj");
	m_pPlaneObject->SetPosition(vec3(0.0f, -0.7f, 0.0f));
	m_pPlaneObject->SetScale(vec3(4.0f, 0.5f, 4.0f));
	m_ppObjects.emplace_back(m_pPlaneObject);//바닥 오브젝트 넣기
	
	
}

void GameMananager::MouseInput(int button, int state, int x, int y)
{
	//m_pMainCamera->ProcessMouseInput(static_cast<float>(x), static_cast<float>(y));
}
void GameMananager::MotionInput(float x, float y)
{
	m_pMainCamera->ProcessMouseMovement(x, y);
}

bool GameMananager::IsInitialized()
{
	return m_Initialized;
}




void GameMananager::KeyInput(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w':
		m_pMainCamera->ProcessKeyboard(Camera_Movement::FORWARD,0.01);
		break;
	case 's':
		m_pMainCamera->ProcessKeyboard(Camera_Movement::BACKWARD, 0.01);
		break;
	case 'd':
		m_pMainCamera->ProcessKeyboard(Camera_Movement::RIGHT, 0.01);
		break;
	case 'a':
		m_pMainCamera->ProcessKeyboard(Camera_Movement::LEFT, 0.01);
		break;
	case 'q':
		break;
	case 'e':
		break;
	case 'r':
		break;
	default:
		break;
	}
}

void GameMananager::Animate(float fTimeelapsed)
{
	glm::vec3 CubeScale = glm::vec3(g_GUIMananger.GetScale());
	m_pCubeObject->SetinitScale(CubeScale);

	m_pPhysisc->UpdatePhysics(m_ppObjects);

	//m_pMainCamera->SetPosition(vec3(m_pCubeObject->GetPosition().x, m_pCubeObject->GetPosition().y, m_pCubeObject->GetPosition().z + 10));
}


void GameMananager::Render()
{
	m_pMainCamera->Render(m_SolidRectShader);//카메라 렌더

	for (int i = 0; i < m_ppObjects.size(); ++i) {
		m_ppObjects[i]->Render();//큐브 오브젝트 렌더
	}

	qobj = gluNewQuadric(); // 객체 생성하기
	gluQuadricDrawStyle(qobj, GLU_LINE); // 도형 스타일
	gluQuadricNormals(qobj, GLU_SMOOTH); //? 생략 가능
	gluQuadricOrientation(qobj, GLU_OUTSIDE); //? 생략 가능
	gluSphere(qobj, 1.5, 50, 50);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glCullFace(GL_FRONT);


}

