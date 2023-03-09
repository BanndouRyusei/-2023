//---------------------------
//SoundEffect.cpp
//---------------------------
#include"Sound.h"

CControlSound* CControlSound::ms_Instance = nullptr;

CControlSound::CControlSound(float _priority) :Task(_priority, CAST::CONTROLSOUND) {
	IsGuardFlg(true);
	ms_Instance = this;
	//音ファイル読込
	for (int i = 0; i < (int)e_SE::NONE; i++) {
		m_Se[i] = LoadSoundMem(m_SeItem[i]);
		if (m_Se[i] == -1)assert(false);
	}
	for (int i = 0; i < (int)e_BGM::NONE; i++) {
		m_Bgm[i] = LoadSoundMem(m_BgmItem[i]);
		if (m_Bgm[i] == -1)assert(false);
	}
}

CControlSound::~CControlSound() {
	ms_Instance = nullptr;
	for (int i = 0; i < (int)e_SE::NONE; i++) {
		DeleteSoundMem(m_Se[i]);
	}
	for (int i = 0; i < (int)e_BGM::NONE; i++) {
		DeleteSoundMem(m_Bgm[i]);
	}
}

void CControlSound::Update() {
}


CControlSound* CControlSound::GetInstance() {
	return ms_Instance;
}

//e_SEタスクを追加
void CControlSound::CreateSE(e_SE _number, int _playtype) {
	new CSE(DuplicateSoundMem(m_Se[(int)_number]), 0.6f, _playtype);
}

//e_BGMタスク追加
void CControlSound::CreateBGM(e_BGM _number) {
	new CBGM(0.8f, &m_Bgm[(int)_number]);
}

CSE::CSE(const int _se, float _priority, int _playtype) :Task(_priority, CAST::SE) {
	m_Se = _se;

	PlaySoundMem(m_Se, _playtype);
}

CSE::~CSE() {
	if (CheckSoundMem(m_Se) == TRUE) {
		StopSoundMem(m_Se);
	}
	DeleteSoundMem(m_Se);
}

void CSE::Update() {
	if (!CheckSoundMem(m_Se)) {
		Delete();
	}
}

CBGM::CBGM(const float _priority, int *_bgm) :Task(_priority, CAST::BGM) {
	m_Phase = e_BGMPHASE::START;
	m_Volume = 255;
	m_Bgm = _bgm;
}

CBGM::~CBGM() {
	if (CheckSoundMem(*m_Bgm) == TRUE) {
		StopSoundMem(*m_Bgm);
	}
}

void CBGM::Update(void) {
	const int VOLUMESTEP = 3;
	switch (m_Phase)
	{
	case e_BGMPHASE::START:
		//初期音量をセットしてからe_BGM再生
		ChangeVolumeSoundMem(m_Volume, *m_Bgm);
		PlaySoundMem(*m_Bgm, DX_PLAYTYPE_LOOP);
		m_Phase = e_BGMPHASE::PLAY;
		break;
	case e_BGMPHASE::PLAY:
		break;
	case e_BGMPHASE::END:
		//音量を徐々に小さくしていく
		m_Volume -= VOLUMESTEP;
		ChangeVolumeSoundMem(m_Volume, *m_Bgm);
		if (m_Volume <= 0) {
			StopSoundMem(*m_Bgm);
			Delete();
		}
		break;
	default:
		assert(false);
	}
}

void CBGM::ChangePhase(e_BGMPHASE _phase) {
	m_Phase = _phase;
}