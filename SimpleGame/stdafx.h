#pragma once

#include "targetver.h"
#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include<vector>
#include "Dependencies\glew.h"
#include <stdio.h>
#include <tchar.h>
#include "Dependencies\freeglut.h"

#include "Dependencies/glm/glm.hpp"
#include "Dependencies/glm/gtc/matrix_transform.hpp"
#include "Dependencies/glm/gtc/type_ptr.hpp"

#include "Imgui/imgui_impl_glut.h"
#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_opengl3.h"

using namespace std;
using namespace glm;


bool ReadFile(char* filename, std::string* target);
void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
GLuint CompileShaders(char* filenameVS, char* filenameFS);
#define SCR_WIDTH  800
#define SCR_HEIGHT  800

