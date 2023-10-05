#pragma once

struct ImGuiContext;

class GUIMgr
{
private:
	ImGuiContext* gui_context;
	float Scale = 1.0f;
	int counter = 0;
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
public:
	static GUIMgr& GetInstance();   // mgr getter

	void Init();   // initialization
	void Render();   // render
	float GetScale(); //Scale
public:
	GUIMgr() {};
	~GUIMgr();
	
};