//----------------------
//gametitle_screen.cpp
//----------------------

//�w�b�_�[�t�@�C��
#include"Title_screen.h"
#include"Title.h"

//�R���X�g���N�^
CTitleScreen::CTitleScreen() {
	m_state = TITLE_SCREEN;
	m_Timer = 0;
	CTaskManager::Instance()->GuardKillTask();
	new CTitle(0.1f);
	CControlSound::GetInstance()->CreateBGM(e_BGM::TITLE);
}

//�f�X�g���N�^
CTitleScreen::~CTitleScreen() {}

//���s����
void CTitleScreen::Update() {
	try {
		CTaskManager::Instance()->Update();
	}
	catch (int menu) {
		switch (menu)
		{
		case 0:
			CTaskManager::Instance()->GuardKillTask();
			m_state = GAME_SCREEN;
			break;
		case 1:			//�����I��
			CTaskManager::Instance()->GuardKillTask();
			exit(0);
			break;
		default:
			assert(false);
		}
	}
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
	clsDx();
	ClearDrawScreen();
	CTaskManager::Instance()->Draw();

#if defined( _DEBUG) | defined( DEBUG )
	clsDx();
	DrawString(10, 100, "GameTitle Screen Hit E key to Game Screen", GetColor(255, 255, 255));
#endif
}