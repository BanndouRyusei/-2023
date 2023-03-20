//-------------------------------
//Clear_screen.cpp
//-------------------------------
//�w�b�_�[�t�@�C��
#include"Clear_Screen.h"
#include"Clear.h"

//�R���X�g���N�^
CClearScreen::CClearScreen() {
	m_state = CLEAR_SCREEN;
	m_Timer = 0;
	CTaskManager::Instance()->GuardKillTask();
	new CClear(0.1f);
	CControlSound::GetInstance()->CreateBGM(e_BGM::CLEAR);
}

//�f�X�g���N�^
CClearScreen::~CClearScreen() {
}

//���s����
void CClearScreen::Update() {
	try
	{
		CTaskManager::Instance()->Update();
	}
	catch (int menu)
	{
		if (menu == 0) {
			CTaskManager::Instance()->GuardKillTask();
			m_state = TITLE_SCREEN;
		}
	}

#if defined(_DEBUG)|defined(DEBUG)
	if (CheckHitKey(KEY_INPUT_A)) {
		CTaskManager::Instance()->GuardKillTask();
		m_state = TITLE_SCREEN;
	}
#endif
}

//�`�揈��
void CClearScreen::Draw()const {
	clsDx();
	ClearDrawScreen();
	CTaskManager::Instance()->Draw();

#if defined(_DEBUG)|defined(DEBUG)
	DrawString(10, 100, "Clear Screen Hit A key to GameTitle Screen", GetColor(255, 255, 255));
#endif
}