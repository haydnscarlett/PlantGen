#pragma once
#include "Window.h"
#include "Timer.h"

class Application
{
public:
	Application();
	int Go();
private:
	void DoFrame();
private:
	Window wnd;
	Timer timer;
};

