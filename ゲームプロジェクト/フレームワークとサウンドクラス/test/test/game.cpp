//----------------
//game.cpp
//----------------
#include "game.h"
#include"Task.h"
#include"TaskSystemEx.h"

CGame::CGame() {
	TaskEx::InitTaskList();			//�^�X�N�V�X�e���̏�����
	//TaskEx::AddTask(new CControlSound(0.9f));			//�����ɓǂݍ���ł���
	m_now_screen = TITLE_SCREEN;
	m_pScreen = NULL;
}

CGame::~CGame() {
	TaskEx::GuardDethTask();		//�����Ă���^�X�N�̏I������
	TaskEx::DeleteDeathTask();
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