//-------------------------------
//Over_screen.cpp
//-------------------------------
//�w�b�_�[�t�@�C��
#include"Over_Screen.h"

//�R���X�g���N�^
COverScreen::COverScreen() {
	m_state = OVER_SCREEN;
	m_Timer = 0;
	CTaskManager::Instance()->GuardKillTask();
	//CControlSound::GetInstance()->CreateBGM(BGM::TITLE);
}

//�f�X�g���N�^
COverScreen::~COverScreen() {
}

//���s����
void COverScreen::Update() {
	CTaskManager::Instance()->Update();
	/*try
	{
		CTaskManager::Instance()->RunTask();
	}
	catch (int menu)
	{
		if (0) {
			CTaskManager::Instance()->DethTask();
			CTaskManager::Instance()->DeleteDeathTask();
			m_state = TITLE_SCREEN;
		}
	}*/

#if defined(_DEBUG)|defined(DEBUG)
	if (CheckHitKey(KEY_INPUT_Z)) {
		CTaskManager::Instance()->GuardKillTask();
		m_state = TITLE_SCREEN;
	}
#endif
}

//�`�揈��
void COverScreen::Draw()const {
	ClearDrawScreen();
	CTaskManager::Instance()->Draw();
	clsDx();
#if defined(_DEBUG)|defined(DEBUG)
	clsDx();
	DrawString(10, 100, "Over Screen Hit Z key to GameTitle Screen", GetColor(255, 255, 255));
#endif
}
