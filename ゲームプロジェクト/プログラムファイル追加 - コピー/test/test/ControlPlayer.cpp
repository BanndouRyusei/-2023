//---------------------------
//ControlPlayer.cpp
//---------------------------
#include"Player.h"
#include"Sound.h"

CControlPlayer::CControlPlayer(float _priority) :CTask(_priority, CAST::CONTROLPLAYER) {
	m_LIFE = PLAYER_LIFE;
	m_Phase = e_PLAYERPHASE::STATE;
}

CControlPlayer::~CControlPlayer() {
	
}

void CControlPlayer::Update() {
	CBGM* bgm;
	switch (m_Phase)
	{
	case e_PLAYERPHASE::STATE:
		new CPlayer(0.4f);
		m_Phase = e_PLAYERPHASE::PLAY;
		break;
	case e_PLAYERPHASE::PLAY:

		//if (CTaskManager::Instance()->GetCount(CAST::BGM)) {		//BGMが鳴り終わったらクリア
		//	throw(CAST::GAMECLEAR);
		//}

		if (CTaskManager::Instance()->GetCount(CAST::PLAYER) == FALSE) {
			CreatePlayer();
		}
		break;
	case e_PLAYERPHASE::END:
		/*bgm = (CBGM*)CTaskManager::Instance()->GetTask(CAST::BGM);
		if (bgm != nullptr) {
			bgm->ChangePhase(e_BGMPHASE::END);
		}
		if (CTaskManager::Instance()->GetCount(CAST::BGM)) {		//BGMが鳴り終わったらクリア
			throw(CAST::GAMEOVER);
		}*/
		break;
	case e_PLAYERPHASE::NONE:
	default:
		assert(false);
		break;
	}
}

//プレイヤークラスの生成
void CControlPlayer::CreatePlayer() {
	m_LIFE--;
	if (m_LIFE == FALSE) {
		m_Phase = e_PLAYERPHASE::END;
		return;
	}
	new CPlayer(0.4f);
}
