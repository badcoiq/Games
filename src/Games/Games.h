#ifndef __GAMES_H_
#define __GAMES_H_

#include "badcoiq.h"

#include "badcoiq/system/bqWindow.h"
#include "badcoiq/GUI/bqGUI.h"

class FrameworkCallback : public bqFrameworkCallback
{
public:
    FrameworkCallback() {}
    virtual ~FrameworkCallback() {}
    virtual void OnMessage() {}
};

class MainWindowCallback : public bqWindowCallback
{
public:
    MainWindowCallback() {}
    virtual ~MainWindowCallback() {}

    virtual void OnClose(bqWindow*) override;
    virtual void OnSize(bqWindow* w) override;
    virtual void OnPopupMenu(bqWindow*, uint32_t /*id*/) override {}
};

class DrawTextCallback : public bqGUIDrawTextCallback
{
    bqColor m_color;
    bqGUIFont* m_defaultFont = 0;
public:
    DrawTextCallback() {}
    virtual ~DrawTextCallback() {}

    virtual bqGUIFont* OnFont(char32_t)
    {
        return m_defaultFont;
    }

    virtual bqColor* OnColor(char32_t)
    {
        return &m_color;
    }

    void SetFont(bqGUIFont* f)
    {
        m_defaultFont = f;
    }

    const bqColor& GetColor() { return m_color; }
    void SetColor(const bqColor& c) { m_color = c; }
};

class Game;
class Games
{
    friend class MainWindowCallback;

    bqGS* m_gs = 0;
    float32_t* m_deltaTime = 0;
    bqInputData* m_inputData = 0;
	bool m_run = true;
    bqWindow* m_mainWindow = 0;

	Game* m_activeGame = 0;
	FrameworkCallback m_frameworkCallback;
	MainWindowCallback m_mainWindowCallback;
	DrawTextCallback m_drawTextCallback;

    bqTexture* m_menuBG = 0;
    bqVec2f m_windowSize;

public:
	Games();
	~Games();

	bool Init();
	void Run();
	void OnMainMenu();
    void Stop();
};

#endif
