#pragma once
#include "stdafx.h"
class CCamera {
private:

	

	bool firstMouse;
	float yaw = -90.0f;
	float pitch = 0.0f;
	float lastX = 1600 / 2;
	float lastY = 900 / 2;
	GLuint m_Shader = 0;
public:
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 m_xm4x4ViewMatrix = mat4x4(1.0f);
	CCamera();
	~CCamera();
	void ProcessMouseInput(float xpos, float ypos);
	void Update(float deltaTime);
	void Render();
	void UpdateCamera();
};
