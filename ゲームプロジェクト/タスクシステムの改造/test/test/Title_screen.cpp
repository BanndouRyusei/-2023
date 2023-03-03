//----------------------
//gametitle_screen.cpp
//----------------------

//ヘッダーファイル
#include"Title_screen.h"
#include"TaskSystemEx.h"

//コンストラクタ
CTitleScreen::CTitleScreen() {
	m_state = TITLE_SCREEN;
	m_Timer = 0;
	TaskEx::DethTask();
	//CControlSound::GetInstance()->CreateBGM(BGM::TITLE);
}

//デストラクタ
CTitleScreen::~CTitleScreen() {}

//実行処理
void CTitleScreen::Update() {
	TaskEx::RunTask();
	//TaskEx::UpdateDrawPriority();
	/*try {
		TaskEx::RunTask();
	}
	catch (int menu) {
		switch (0)
		{
		case 0:
			TaskEx::DethTask();	
			TaskEx::DeleteDeathTask();
			m_state = GAME_SCREEN;
			break;
		case 1:			//強制終了
			TaskEx::GuardDethTask();
			exit(0);
			break;
		default:
			assert(false);
		}
	}*/
	if (m_Timer++%MAX_FPS == 0) TaskEx::DeleteDeathTask();//不要タスクの消去
#if defined( _DEBUG ) | defined( DEBUG )
	if (CheckHitKey(KEY_INPUT_E)) {
		TaskEx::DethTask();
		TaskEx::DeleteDeathTask();
		m_state = GAME_SCREEN;
	}
#endif
}

//描画
void CTitleScreen::Draw() const
{
	ClearDrawScreen();
	TaskEx::DrawTask();
	clsDx();

#if defined( _DEBUG) | defined( DEBUG )
	clsDx();
	DrawString(10, 100, "GameTitle Screen Hit E key to Game Screen", GetColor(255, 255, 255));
#endif
}