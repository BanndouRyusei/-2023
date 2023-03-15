//---------------------------
//ControlPlayer.cpp
//---------------------------
#include"Player.h"
#include"Sound.h"
#include"UI.h"

CControlPlayer::CControlPlayer(float _priority) :CTask(_priority, CAST::CONTROLPLAYER) {
	m_Life = PLAYER_LIFE;
	m_Phase = PHASE::START;
}

CControlPlayer::~CControlPlayer() {
	
}

void CControlPlayer::Update() {
	CBGM* bgm;
	CLife* life = (CLife*)CTaskManager::Instance()->GetTask(CAST::LIFE);
	life->SetPlayerLife(m_Life);
	switch (m_Phase)
	{
	case PHASE::START:
		new CPlayer(0.4f);
		m_Phase = PHASE::PLAY;
		break;
	case PHASE::PLAY:
		//if (CTaskManager::Instance()->GetCount(CAST::BGM)) {		//BGMが鳴り終わったらクリア
		//	throw(CAST::GAMECLEAR);
		//}

		if (CTaskManager::Instance()->GetCount(CAST::PLAYER) == FALSE) {
			CreatePlayer();
		}
		break;
	case PHASE::END:
		/*bgm = (CBGM*)CTaskManager::Instance()->GetTask(CAST::BGM);
		if (bgm != nullptr) {
			bgm->ChangePhase(PHASE::END);
		}
		if (CTaskManager::Instance()->GetCount(CAST::BGM)) {		//BGMが鳴り終わったらクリア
			throw(CAST::GAMEOVER);
		}*/
		break;
	case PHASE::NONE:
	default:
		assert(false);
		break;
	}
}

//プレイヤークラスの生成
void CControlPlayer::CreatePlayer() {
	m_Life--;
	if (m_Life == FALSE) {
		m_Phase = PHASE::END;
		return;
	}
	new CPlayer(0.4f);
}
