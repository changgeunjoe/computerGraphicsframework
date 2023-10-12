#pragma once
class CObject;
class CCamera;
class CPhysx;
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
	void MouseInput(int button, int state, int x, int y);
	void MotionInput(float x, float y);
	
	void KeyInput(unsigned char key, int x, int y);
	void Animate(float fTimeelapsed);
	//void GetGLPosition(float x, float y, float *newX, float *newY);
private:
	
	bool m_Initialized = false;
	
	unsigned int m_WindowSizeX{};
	unsigned int m_WindowSizeY{};
protected:

	CPhysx* m_pPhysisc{};
	CObject* m_pCubeObject{};
	CObject* m_pPlaneObject{};
	CCamera* m_pMainCamera{};
	
	vector<CObject*> m_ppObjects{};
	GLuint m_SolidRectShader{};
};



