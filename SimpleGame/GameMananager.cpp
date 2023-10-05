#pragma once
#include "stdafx.h"
#include "GameMananager.h"
#include "Object.h"

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


	/*if (m_SolidRectShader > 0 && m_VBORect > 0)
	{
		m_Initialized = true;
	}*/
}

void GameMananager::BuildObjects()
{
	CubeObject = new CObject;
	CubeObject->BuildObject();
}

bool GameMananager::IsInitialized()
{
	return m_Initialized;
}


void GameMananager::AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
	//���̴� ������Ʈ ����
	GLuint ShaderObj = glCreateShader(ShaderType);

	if (ShaderObj == 0) {
		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
	}

	const GLchar* p[1];
	p[0] = pShaderText;
	GLint Lengths[1];
	Lengths[0] = strlen(pShaderText);
	//���̴� �ڵ带 ���̴� ������Ʈ�� �Ҵ�
	glShaderSource(ShaderObj, 1, p, Lengths);

	//�Ҵ�� ���̴� �ڵ带 ������
	glCompileShader(ShaderObj);

	GLint success;
	// ShaderObj �� ���������� ������ �Ǿ����� Ȯ��
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];

		//OpenGL �� shader log �����͸� ������
		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
		printf("%s \n", pShaderText);
	}

	// ShaderProgram �� attach!!
	glAttachShader(ShaderProgram, ShaderObj);
}

bool GameMananager::ReadFile(char* filename, std::string *target)
{
	std::ifstream file(filename);
	if (file.fail())
	{
		std::cout << filename << " file loading failed.. \n";
		file.close();
		return false;
	}
	std::string line;
	while (getline(file, line)) {
		target->append(line.c_str());
		target->append("\n");
	}
	return true;
}

GLuint GameMananager::CompileShaders(char* filenameVS, char* filenameFS)
{
	GLuint ShaderProgram = glCreateProgram(); //�� ���̴� ���α׷� ����

	if (ShaderProgram == 0) { //���̴� ���α׷��� ����������� Ȯ��
		fprintf(stderr, "Error creating shader program\n");
	}

	std::string vs, fs;

	//shader.vs �� vs ������ �ε���
	if (!ReadFile(filenameVS, &vs)) {
		printf("Error compiling vertex shader\n");
		return -1;
	};

	//shader.fs �� fs ������ �ε���
	if (!ReadFile(filenameFS, &fs)) {
		printf("Error compiling fragment shader\n");
		return -1;
	};

	// ShaderProgram �� vs.c_str() ���ؽ� ���̴��� �������� ����� attach��
	AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);

	// ShaderProgram �� fs.c_str() �����׸�Ʈ ���̴��� �������� ����� attach��
	AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };

	//Attach �Ϸ�� shaderProgram �� ��ŷ��
	glLinkProgram(ShaderProgram);

	//��ũ�� �����ߴ��� Ȯ��
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);

	if (Success == 0) {
		// shader program �α׸� �޾ƿ�
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		std::cout << filenameVS << ", " << filenameFS << " Error linking shader program\n" << ErrorLog;
		return -1;
	}

	glValidateProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		std::cout << filenameVS << ", " << filenameFS << " Error validating shader program\n" << ErrorLog;
		return -1;
	}

	glUseProgram(ShaderProgram);
	std::cout << filenameVS << ", " << filenameFS << " Shader compiling is done.";

	return ShaderProgram;
}

void GameMananager::KeyInput(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w':
		CubeObject->MoveDirection(DIRECTION::Moveforward);
		break;
	case 's':
		CubeObject->MoveDirection(DIRECTION::MoveBack);
		break;
	case 'd':
		CubeObject->MoveDirection(DIRECTION::MoveRight);
		break;
	case 'a':
		CubeObject->MoveDirection(DIRECTION::MoveLeft);
		break;
	case 'q':
		CubeObject->MoveDirection(DIRECTION::MoveUp);
		break;
	case 'e':
		CubeObject->MoveDirection(DIRECTION::MoveDown);
		break;
	default:
		break;
	}
}


void GameMananager::Render()
{
	//Program select
	
	CubeObject->Render();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

