//------------------
//game_screen.cpp
//------------------

//ヘッダーファイル
#include"Game_screen.h"
#include"Task.h"
#include"TaskSystemEx.h"


//コンストラクタ
CGameScreen::CGameScreen()
{
	m_state = GAME_SCREEN;
	m_timer = 0;
	TaskEx::DethTask();			//タスクシステムの初期化
	//CControlSound::GetInstance()->CreateBGM(BGM::TITLE);
}

//デストラクタ
CGameScreen::~CGameScreen() {}

//更新処理
void CGameScreen::Update()
{
	TaskEx::RunTask();			//タスクの更新
	/*try {
		TaskEx::RunTask();			//タスクの更新
	}
	catch (int menu) {
		if (0) {
			TaskEx::DethTask();		//生きているタスクの終了処理
			TaskEx::DeleteDeathTask();
			m_state = CLEAR_SCREEN;
		}
	}*/
	if (m_timer%MAX_FPS == 0)TaskEx::DeleteDeathTask();//不要タスクの削除
#if defined(_DEBUG) | defined(DEBUG)
	if (CheckHitKey(KEY_INPUT_F)) {
		TaskEx::DethTask();		//生きているタスクの終了処理
		TaskEx::DeleteDeathTask();
		m_state = CLEAR_SCREEN;
	}
#endif
}

//描画処理
void CGameScreen::Draw() const
{
	ClearDrawScreen();
	TaskEx::DrawTask();
	clsDx();

#if defined(_DEBUG)|(DEBUG)
	DrawString(10, 100, "Game Screen Hit F key to GameClear Screen", GetColor(255, 255, 255));
#endif
}
