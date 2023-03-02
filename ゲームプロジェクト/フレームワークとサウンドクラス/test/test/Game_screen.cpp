//------------------
//game_screen.cpp
//------------------

//�w�b�_�[�t�@�C��
#include"Game_screen.h"
#include"Task.h"
#include"TaskSystemEx.h"


//�R���X�g���N�^
CGameScreen::CGameScreen()
{
	m_state = GAME_SCREEN;
	m_timer = 0;
	TaskEx::DethTask();			//�^�X�N�V�X�e���̏�����
	//CControlSound::GetInstance()->CreateBGM(BGM::TITLE);
}

//�f�X�g���N�^
CGameScreen::~CGameScreen() {}

//�X�V����
void CGameScreen::Update()
{
	TaskEx::RunTask();			//�^�X�N�̍X�V
	/*try {
		TaskEx::RunTask();			//�^�X�N�̍X�V
	}
	catch (int menu) {
		if (0) {
			TaskEx::DethTask();		//�����Ă���^�X�N�̏I������
			TaskEx::DeleteDeathTask();
			m_state = CLEAR_SCREEN;
		}
	}*/
	if (m_timer%MAX_FPS == 0)TaskEx::DeleteDeathTask();//�s�v�^�X�N�̍폜
#if defined(_DEBUG) | defined(DEBUG)
	if (CheckHitKey(KEY_INPUT_F)) {
		TaskEx::DethTask();		//�����Ă���^�X�N�̏I������
		TaskEx::DeleteDeathTask();
		m_state = CLEAR_SCREEN;
	}
#endif
}

//�`�揈��
void CGameScreen::Draw() const
{
	ClearDrawScreen();
	TaskEx::DrawTask();
	clsDx();

#if defined(_DEBUG)|(DEBUG)
	DrawString(10, 100, "Game Screen Hit F key to GameClear Screen", GetColor(255, 255, 255));
#endif
}
