//-------------------------------
//Over_screen.cpp
//-------------------------------
//ヘッダーファイル
#include"Over_Screen.h"

//コンストラクタ
COverScreen::COverScreen() {
	m_state = OVER_SCREEN;
	m_Phase = PHASE::START;
	m_Timer = 0;
	m_LastTime = GetNowCount() & INT_MAX;
	m_Image = LoadGraph("Data\\img\\OverScreen.png");
	CTaskManager::Instance()->GuardKillTask();
	CControlSound::GetInstance()->CreateSE(e_SE::GAMEOVER);
}

//デストラクタ
COverScreen::~COverScreen() {
	DeleteGraph(m_Image);
}

//実行処理
void COverScreen::Update() {
	CTaskManager::Instance()->Update();

	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	const int ALPHA_MAX = 255;
	const int ALPHA_STEP = 5;

	m_Timer++;
	switch (m_Phase){
	case PHASE::START:
		m_Alpha = m_Timer * ALPHA_STEP;
		if (key || m_Alpha >= ALPHA_MAX) {
			m_Phase = PHASE::PLAY;
			m_Alpha = ALPHA_MAX;
		}
		break;
	case PHASE::PLAY:
		if (IsKeyTrigger(key, PAD_INPUT_A)) {
			m_Phase = PHASE::END;
		}
	case PHASE::END:
		if (!CTaskManager::Instance()->GetCount(CAST::SE)) {
			m_state = TITLE_SCREEN;
		}
		break;
	default:
		assert(false);
	}
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

//描画処理
void COverScreen::Draw()const {
	ClearDrawScreen();
	CTaskManager::Instance()->Draw();
	clsDx();

	SetDrawBright(m_Alpha, m_Alpha, m_Alpha);
	DrawGraph(0, 0, m_Image, TRUE);
	SetDrawBright(ALPHA_MAX, ALPHA_MAX, ALPHA_MAX);

#if defined(_DEBUG)|defined(DEBUG)
	clsDx();
	DrawString(10, 100, "Over Screen Hit Z key to GameTitle Screen", GetColor(255, 255, 255));
#endif
}
