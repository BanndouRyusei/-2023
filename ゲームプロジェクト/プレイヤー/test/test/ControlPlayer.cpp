//---------------------------
//ControlPlayer.cpp
//---------------------------
#include"Player.h"
#include"Sound.h"

CControlPlayer::CControlPlayer(float _priority) :Task(_priority, CAST::CONTROLPLAYER) {
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

		//if (TaskManager::Instance()->GetCount(CAST::BGM)) {		//BGMが鳴り終わったらクリア
		//	throw(CAST::GAMECLEAR);
		//}

		if (TaskManager::Instance()->GetCount(CAST::PLAYER) == FALSE) {
			if (m_LIFE == FALSE) {
				m_Phase = e_PLAYERPHASE::END;
			}
			CreatePlayer();
		}
		break;
	case e_PLAYERPHASE::END:
		bgm = (CBGM*)TaskManager::Instance()->GetTask(CAST::BGM);
		if (bgm != nullptr) {
			bgm->ChangePhase(e_BGMPHASE::END);
		}
		if (TaskManager::Instance()->GetCount(CAST::BGM)) {		//BGMが鳴り終わったらクリア
			throw(CAST::GAMEOVER);
		}
		break;
	case e_PLAYERPHASE::NONE:
	default:
		assert(false);
		break;
	}
}

//プレイヤークラスの生成
void CControlPlayer::CreatePlayer() {
	new CPlayer(0.4f);
	m_LIFE--;
}
