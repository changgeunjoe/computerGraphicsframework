/*
WARP게임 프레임워크입니다.
*/
#pragma once
#include "stdafx.h"
#include "GameMananager.h"
#include "GUIMGR.h"
GameMananager* g_GameMananager{NULL};
GUIMgr g_GUIMananger ;

bool firstMouse{ true};
float lastX{};
float lastY{};
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
	
	//g_GameMananager->DrawSolidRect(0, 0, 0, 4, 1, 0, 1, 1);
	g_GameMananager->Animate(1);
	g_GameMananager->Render();
	g_GUIMananger.Render();
	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	
	g_GameMananager->MouseInput(button, state, x, y);
	//int imgx = normalize(x);
	ImGui_ImplGLUT_MouseFunc(button, state, static_cast<int>(x), static_cast<int>(y));
}

void motionCall(int x, int y)
{
	ImGui_ImplGLUT_MotionFunc(static_cast<int>(x), static_cast<int>(y));
	float xpos = static_cast<float>(x);
	float ypos = static_cast<float>(y);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;
	g_GameMananager->MotionInput(xoffset, yoffset);
	//camera.ProcessMouseMovement(xoffset, yoffset);
}

void KeyInput(unsigned char key, int x, int y)
{
	g_GameMananager->KeyInput(key, x, y);
	switch (key) {
		case 'w':
			break;
		case 's':
			break;
		case 'd':
			break;
		case 'a':
			break;
		default:
			break;
	}
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

int main(int argc, char **argv)
{
	// Initialize GL things
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(SCR_WIDTH, SCR_HEIGHT);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();

	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	// Initialize GameMananager
	g_GameMananager = new GameMananager(SCR_WIDTH, SCR_HEIGHT);

	if (!g_GameMananager->IsInitialized())
	{
		std::cout << "GameMananager could not be initialized.. \n";
	}
	g_GameMananager->BuildObjects();
	
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glCullFace(GL_FRONT);




	glutSpecialFunc(SpecialKeyInput);
	//g_GUIMananger = new GUIMgr();
	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	g_GUIMananger.Init();
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutMotionFunc(motionCall);
	
	//glutMotionFunc(motionCall);


	glutMainLoop();
	

	delete g_GameMananager;

    return 0;
}

