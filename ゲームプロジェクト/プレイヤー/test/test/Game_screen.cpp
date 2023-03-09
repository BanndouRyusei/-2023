//------------------
//game_screen.cpp
//------------------

//�w�b�_�[�t�@�C��
#include"Game_screen.h"
#include"Stage.h"
#include"Player.h"


//�R���X�g���N�^
CGameScreen::CGameScreen()
{
	m_state = GAME_SCREEN;
	m_timer = 0;
	TaskManager::Instance()->GuardKillTask();
	new CStage(0.1f);
	new CControlPlayer(0.1f);
	//CControlSound::GetInstance()->CreateBGM(BGM::TITLE);
}

//�f�X�g���N�^
CGameScreen::~CGameScreen() {}

//�X�V����
void CGameScreen::Update()
{
	TaskManager::Instance()->Update();			//�^�X�N�̍X�V
	/*try {
		TaskManager::Instance()->RunTask();			//�^�X�N�̍X�V
	}
	catch (int menu) {
		if (0) {
			TaskManager::Instance()->DethTask();		//�����Ă���^�X�N�̏I������
			TaskManager::Instance()->DeleteDeathTask();
			m_state = CLEAR_SCREEN;
		}
	}*/
	//if (m_timer%MAX_FPS == 0)TaskManager::Instance()->DeleteDeathTask();//�s�v�^�X�N�̍폜
#if defined(_DEBUG) | defined(DEBUG)
	if (CheckHitKey(KEY_INPUT_F)) {
		TaskManager::Instance()->GuardKillTask();
		m_state = CLEAR_SCREEN;
	}
	if (CheckHitKey(KEY_INPUT_G)) {
		TaskManager::Instance()->GuardKillTask();
		m_state = OVER_SCREEN;
	}
#endif
}

//�`�揈��
void CGameScreen::Draw() const
{
	ClearDrawScreen();
	TaskManager::Instance()->Draw();
	clsDx();

#if defined(_DEBUG)|(DEBUG)
	DrawString(10, 100, "Game Screen Hit F key to GameClear Screen Hit G key to GameOver Screen", GetColor(255, 255, 255));
#endif
}
