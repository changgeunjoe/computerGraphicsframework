#pragma once
class CObject;


class GameMananager
{
public:
	GameMananager(int windowSizeX, int windowSizeY);
	~GameMananager();

	bool IsInitialized();
	virtual void Render();

public:

	void Initialize(int windowSizeX, int windowSizeY);
	virtual void BuildObjects();
	bool ReadFile(char* filename, std::string *target);
	void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
	GLuint CompileShaders(char* filenameVS, char* filenameFS);
	void KeyInput(unsigned char key, int x, int y);
	//void GetGLPosition(float x, float y, float *newX, float *newY);
private:
	
	bool m_Initialized = false;
	
	unsigned int m_WindowSizeX{};
	unsigned int m_WindowSizeY{};
protected:
	CObject* CubeObject{};
	
};



