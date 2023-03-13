//----------------
//game.cpp
//----------------
#include "game.h"

CGame::CGame() {
	CTaskManager::ClearInstance();			//タスクシステムの初期化
	//new CControlSound(0.9f);		//音を先に読み込んでおく
	m_now_screen = TITLE_SCREEN;
	m_pScreen = NULL;
}

CGame::~CGame() {
	CTaskManager::ClearInstance();
	if (m_pScreen) {
		delete m_pScreen;
		m_pScreen = NULL;
	}
}

void CGame::Update()
{
	if (!m_pScreen) {
		switch (m_now_screen)
		{
		case TITLE_SCREEN:
			m_pScreen = new CTitleScreen();
			break;
		case GAME_SCREEN:
			m_pScreen = new CGameScreen();
			break;
		case CLEAR_SCREEN:
			m_pScreen = new CClearScreen();
			break;
		case OVER_SCREEN:
			m_pScreen = new COverScreen();
			break;
		default:
			assert(false);
		}
	}
	else {
		m_pScreen->Update();

		if (m_now_screen != m_pScreen->GetNextScreen()) {
			m_now_screen = m_pScreen->GetNextScreen();
			delete m_pScreen;
			m_pScreen = NULL;

		}
	}
}

void CGame::Draw()
{
	if (m_pScreen) {
		m_pScreen->Draw();
	}
}