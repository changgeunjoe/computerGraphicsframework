#pragma once
#include "stdafx.h"
#include "GameMananager.h"
#include "Object.h"
#include "GUIMGR.h"
#include"Camera.h"

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
	m_pMainCamera = new CCamera;

	/*if (m_SolidRectShader > 0 && m_VBORect > 0)
	{
		m_Initialized = true;
	}*/
}

void GameMananager::BuildObjects()
{
	m_pCubeObject = new CObject;
	m_pCubeObject->BuildObject();
}

void GameMananager::MouseInput(int button, int state, int x, int y)
{
	m_pMainCamera->ProcessMouseInput(static_cast<float>(x), static_cast<float>(y));
}

bool GameMananager::IsInitialized()
{
	return m_Initialized;
}




void GameMananager::KeyInput(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w':
		m_pCubeObject->MoveDirection(DIRECTION::Moveforward);
		break;
	case 's':
		m_pCubeObject->MoveDirection(DIRECTION::MoveBack);
		break;
	case 'd':
		m_pCubeObject->MoveDirection(DIRECTION::MoveRight);
		break;
	case 'a':
		m_pCubeObject->MoveDirection(DIRECTION::MoveLeft);
		break;
	case 'q':
		m_pCubeObject->MoveDirection(DIRECTION::MoveUp);
		break;
	case 'e':
		m_pCubeObject->MoveDirection(DIRECTION::MoveDown);
		break;
	case 'r':
		m_pCubeObject->Rotate(0,5,0);
		break;
	default:
		break;
	}
}

void GameMananager::Animate(float fTimeelapsed)
{
	m_pMainCamera->UpdateCamera();
	glm::vec3 CubeScale = glm::vec3(g_GUIMananger.GetScale());
	m_pCubeObject->SetinitScale(CubeScale);
}


void GameMananager::Render()
{

	//Program select
	m_pMainCamera->Render();
	m_pCubeObject->Render();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

