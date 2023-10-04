#pragma once

struct ImGuiContext;

class GUIMgr
{
private:
	ImGuiContext* gui_context;

public:
	static GUIMgr& GetInstance();   // mgr getter

	void Init();   // initialization
	void Render();   // render

private:
	GUIMgr() {};

public:
	~GUIMgr();
};