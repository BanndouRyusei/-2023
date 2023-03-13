//----------------------
//gametitle_screen.cpp
//----------------------

//�w�b�_�[�t�@�C��
#include"Title_screen.h"

//�R���X�g���N�^
CTitleScreen::CTitleScreen() {
	m_state = TITLE_SCREEN;
	m_Timer = 0;
	CTaskManager::Instance()->GuardKillTask();
	//CControlSound::GetInstance()->CreateBGM(BGM::TITLE);
}

//�f�X�g���N�^
CTitleScreen::~CTitleScreen() {}

//���s����
void CTitleScreen::Update() {
	CTaskManager::Instance()->Update();
	//CTaskManager::Instance()->UpdateDrawPriority();
	/*try {
		CTaskManager::Instance()->RunTask();
	}
	catch (int menu) {
		switch (0)
		{
		case 0:
			CTaskManager::Instance()->DethTask();	
			CTaskManager::Instance()->DeleteDeathTask();
			m_state = GAME_SCREEN;
			break;
		case 1:			//�����I��
			CTaskManager::Instance()->GuardDethTask();
			exit(0);
			break;
		default:
			assert(false);
		}
	}*/
#if defined( _DEBUG ) | defined( DEBUG )
	if (CheckHitKey(KEY_INPUT_E)) {
		CTaskManager::Instance()->GuardKillTask();
		m_state = GAME_SCREEN;
	}
#endif
}

//�`��
void CTitleScreen::Draw() const
{
	ClearDrawScreen();
	CTaskManager::Instance()->Draw();
	clsDx();

#if defined( _DEBUG) | defined( DEBUG )
	clsDx();
	DrawString(10, 100, "GameTitle Screen Hit E key to Game Screen", GetColor(255, 255, 255));
#endif
}