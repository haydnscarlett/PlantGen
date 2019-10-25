#include "Application.h"

Application::Application()
	:
	wnd(1280, 780, "Plant Generator")
{}

int Application::Go()
{
	timer.Start();
	while (true)
	{
		// process all messages pending, but to not block for new messages
		if (const auto ecode = Window::ProcessMessages())
		{
			// if return optional has value, means we're quitting so return exit code
			return *ecode;
		}
		Update();
		DoFrame();
	}
}

void Application::Update()
{
	float dt = timer.GetMillisecondsElapsed();
	timer.Restart();
	const float cameraSpeed = 0.006f;

	if (!wnd.mouse.LeftIsPressed() && wnd.mouse.RightIsPressed())
	{
		Mouse::Event me = wnd.mouse.Read();
		if (me.GetType() == Mouse::Event::Type::Move)
		{
			wnd.Gfx().cam.AdjustRot(me.GetPosY() * 0.01f, me.GetPosX() * 0.01f, 0.0f);	
		}
		
	}


	if (wnd.kbd.KeyIsPressed('W'))
	{
		DirectX::XMVECTOR move = DirectX::XMVectorScale(wnd.Gfx().cam.GetForwardVector(), cameraSpeed);
		move = DirectX::XMVectorScale(move, dt);
		wnd.Gfx().cam.AdjustPos(move);
	}
	if (wnd.kbd.KeyIsPressed('A'))
	{
		DirectX::XMVECTOR move = DirectX::XMVectorScale(wnd.Gfx().cam.GetLeftVector(), cameraSpeed);
		move = DirectX::XMVectorScale(move, dt);
		wnd.Gfx().cam.AdjustPos(move);
	}
	if (wnd.kbd.KeyIsPressed('S'))
	{
		DirectX::XMVECTOR move = DirectX::XMVectorScale(wnd.Gfx().cam.GetBackwardVector(), cameraSpeed);
		move = DirectX::XMVectorScale(move, dt);
		wnd.Gfx().cam.AdjustPos(move);
	}
	if (wnd.kbd.KeyIsPressed('D'))
	{
		DirectX::XMVECTOR move = DirectX::XMVectorScale(wnd.Gfx().cam.GetRightVector(), cameraSpeed);
		move = DirectX::XMVectorScale(move, dt);
		wnd.Gfx().cam.AdjustPos(move);
	}
	if (wnd.kbd.KeyIsPressed('Q'))
	{
		wnd.Gfx().cam.AdjustPos(0.0f, cameraSpeed * dt, 0.0f);
	}
	if (wnd.kbd.KeyIsPressed('E'))
	{
		wnd.Gfx().cam.AdjustPos(0.0f, -cameraSpeed * dt, 0.0f);
	}
}
void Application::DoFrame()
{
	wnd.Gfx().ClearBuffer(0.05f,0.05f, 0.2f);
	wnd.Gfx().RenderFrame();


	wnd.Gfx().EndFrame();
}