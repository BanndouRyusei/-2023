//-------------------------------
//Over_screen.cpp
//-------------------------------
//�w�b�_�[�t�@�C��
#include"Over_Screen.h"
#include"Task.h"
#include"TaskSystemEx.h"

//�R���X�g���N�^
COverScreen::COverScreen() {
	m_state = OVER_SCREEN;
	m_Timer = 0;
	TaskEx::DethTask();
	//CControlSound::GetInstance()->CreateBGM(BGM::TITLE);
}

//�f�X�g���N�^
COverScreen::~COverScreen() {
}

//���s����
void COverScreen::Update() {
	TaskEx::RunTask();
	/*try
	{
		TaskEx::RunTask();
	}
	catch (int menu)
	{
		if (0) {
			TaskEx::DethTask();
			TaskEx::DeleteDeathTask();
			m_state = TITLE_SCREEN;
		}
	}*/

	if (m_Timer++%MAX_FPS == 0) TaskEx::DeleteDeathTask();//�s�v�^�X�N�̏���

#if defined(_DEBUG)|defined(DEBUG)
	if (CheckHitKey(KEY_INPUT_Z)) {
		TaskEx::DethTask();
		TaskEx::DeleteDeathTask();
		m_state = TITLE_SCREEN;
	}
#endif
}

//�`�揈��
void COverScreen::Draw()const {
	ClearDrawScreen();
	TaskEx::DrawTask();
	clsDx();
#if defined(_DEBUG)|defined(DEBUG)
	clsDx();
	DrawString(10, 100, "Over Screen Hit Z key to GameTitle Screen", GetColor(255, 255, 255));
#endif
}
