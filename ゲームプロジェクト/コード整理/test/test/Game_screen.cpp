//------------------
//game_screen.cpp
//------------------

//�w�b�_�[�t�@�C��
#include"Game_screen.h"
#include"Stage.h"
#include"Player.h"
#include "Enemy.h"

//�R���X�g���N�^
CGameScreen::CGameScreen()
{
	m_state = GAME_SCREEN;
	m_timer = 0;
	CTaskManager::Instance()->GuardKillTask();
	new CStage(0.1f);
	new CControlPlayer(0.1f);
	new CEnemyZakoA(1000.0, 20.0, 1, 0.2);
	//CControlSound::GetInstance()->CreateBGM(BGM::TITLE);
}

//�f�X�g���N�^
CGameScreen::~CGameScreen() {}

//�X�V����
void CGameScreen::Update()
{
	CTaskManager::Instance()->Update();			//�^�X�N�̍X�V
	/*try {
		CTaskManager::Instance()->RunTask();			//�^�X�N�̍X�V
	}
	catch (int menu) {
		if (0) {
			CTaskManager::Instance()->DethTask();		//�����Ă���^�X�N�̏I������
			CTaskManager::Instance()->DeleteDeathTask();
			m_state = CLEAR_SCREEN;
		}
	}*/
	//if (m_timer%MAX_FPS == 0)CTaskManager::Instance()->DeleteDeathTask();//�s�v�^�X�N�̍폜
#if defined(_DEBUG) | defined(DEBUG)
	if (CheckHitKey(KEY_INPUT_F)) {
		CTaskManager::Instance()->GuardKillTask();
		m_state = CLEAR_SCREEN;
	}
	if (CheckHitKey(KEY_INPUT_G)) {
		CTaskManager::Instance()->GuardKillTask();
		m_state = OVER_SCREEN;
	}
#endif
}

//�`�揈��
void CGameScreen::Draw() const
{
	clsDx();
	ClearDrawScreen();
	CTaskManager::Instance()->Draw();

#if defined(_DEBUG)|(DEBUG)
	DrawString(10, 100, "Game Screen Hit F key to GameClear Screen Hit G key to GameOver Screen", GetColor(255, 255, 255));
#endif
}
