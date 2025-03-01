#include "Games.h"
#include "badcoiq/input/bqInputEx.h"
#include "badcoiq/gs/bqGS.h"

BQ_LINK_LIBRARY("badcoiq");


int main(int argc, char* argv[])
{
	Games app;
	if (app.Init())
	{
		app.Run();
	}

	return EXIT_SUCCESS;
}

Games::Games()
{
}

Games::~Games()
{
//	BQ_SAFEDESTROY(m_gs);
	BQ_SAFEDESTROY(m_mainWindow);
	bqFramework::Stop();
}

void MainWindowCallback::OnClose(bqWindow* w)
{
	Games* app = dynamic_cast<Games*>((Games*)GetUserData());
	if (app)
	{
		app->Stop();
	}
}

void MainWindowCallback::OnSize(bqWindow* w)
{
	Games* app = dynamic_cast<Games*>((Games*)GetUserData());
	if (app)
	{
		app->m_windowSize.x = w->GetCurrentSize()->x;
		app->m_windowSize.y = w->GetCurrentSize()->y;
		if (app->m_gs)
		{
			app->m_gs->OnWindowSize();
			app->m_gs->SetViewport(0, 0, (uint32_t)w->GetCurrentSize()->x, (uint32_t)w->GetCurrentSize()->y);
			app->m_gs->SetScissorRect(bqVec4f(0.f, 0.f, (float)w->GetCurrentSize()->x, (float)w->GetCurrentSize()->y));
			//app->m_GUIWindow->Rebuild();
		}
	}
}

void Games::Stop()
{
	m_run = false;
}

bool Games::Init()
{
	bqFramework::Start(&m_frameworkCallback);
	m_deltaTime = bqFramework::GetDeltaTime();
	m_inputData = bqInput::GetData();

	m_mainWindowCallback.SetUserData(this);
	m_mainWindow = bqFramework::CreateSystemWindow(&m_mainWindowCallback);
	if (m_mainWindow && bqFramework::GetGSNum())
	{
		m_mainWindow->SetPositionAndSize(10, 10, 800, 600);
		m_mainWindow->SetVisible(true);
	}
	else
	{
		return false;
	}

	m_gs = bqFramework::CreateGS(bqFramework::GetGSUID(0));
	if (!m_gs)
	{
		return false;
	}

	if (!m_gs->Init(m_mainWindow, 0))
	{
		return false;
	}

	m_menuBG = bqFramework::CreateTexture(m_gs, bqFramework::GetPath("../data/images/MENU_BG.png").c_str());

	return true;
}

void Games::Run()
{
	while (m_run)
	{
		if (m_activeGame)
		{

		}
		else
		{
			OnMainMenu();
		}
	}
}

void Games::OnMainMenu()
{
	bqFramework::Update();
	m_mainWindow->UpdateGUI();

	m_gs->BeginGUI();
	if (m_menuBG)
	{
		m_gs->DrawGUIRectangle(bqVec4f(0,0, m_windowSize.x, m_windowSize.y),
			bq::ColorWhite, bq::ColorWhite, m_menuBG, 0);
	}
	m_gs->EndGUI();

	m_gs->SetRenderTargetDefault();
	m_gs->BeginDraw();
	m_gs->ClearAll();
	m_gs->EndDraw();
	m_gs->SwapBuffers();
}
