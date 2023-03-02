//---------------------------
//SoundEffect.cpp
//---------------------------
#include"Sound.h"

CControlSound* CControlSound::m_Instance = nullptr;

CControlSound::CControlSound(float _priority) {
	m_id = CAST::CONTROLSOUND;
	m_priority = _priority;
	m_isActive = true;
	m_guard = true;
	m_Instance = this;
	//音ファイル読込
	for (int i = 0; i < (int)SE::NONE; i++) {
		m_Se[i] = LoadSoundMem(m_SeItem[i]);
		if (m_Se[i] == -1)assert(false);
	}
	for (int i = 0; i < (int)BGM::NONE; i++) {
		m_Bgm[i] = LoadSoundMem(m_BgmItem[i]);
		if (m_Bgm[i] == -1)assert(false);
	}
}

CControlSound::~CControlSound() {
	m_Instance = nullptr;
	for (int i = 0; i < (int)SE::NONE; i++) {
		DeleteSoundMem(m_Se[i]);
	}
	for (int i = 0; i < (int)BGM::NONE; i++) {
		DeleteSoundMem(m_Bgm[i]);
	}
}

void CControlSound::Update() {
}

void CControlSound::Deth() {
	for (int i = 0; i < (int)SE::NONE; i++) {
		DeleteSoundMem(m_Se[i]);
	}
	for (int i = 0; i < (int)BGM::NONE; i++) {
		DeleteSoundMem(m_Bgm[i]);
	}
	m_Instance = nullptr;
	m_isActive = false;
}

CControlSound* CControlSound::GetInstance() {
	return m_Instance;
}

//SEタスクを追加
void CControlSound::CreateSE(SE _number, int _playtype) {
	TaskEx::AddTask(new CSe(DuplicateSoundMem(m_Se[(int)_number]), 0.6f, _playtype));
}

//BGMタスク追加
void CControlSound::CreateBGM(BGM _number) {
	TaskEx::AddTask(new CBgm(0.8f, &m_Bgm[(int)_number]));
}

CSe::CSe(const int _se,  float _priority, int _playtype){
	m_id = CAST::SE;
	m_priority = _priority;
	m_isActive = true;
	m_Se = _se;

	PlaySoundMem(m_Se, _playtype);
}

CSe::~CSe() {
	DeleteSoundMem(m_Se);
}

void CSe::Update() {
	if (!CheckSoundMem(m_Se)) {
		Deth();
	}
}

void CSe::Deth() {
	DeleteSoundMem(m_Se);
	m_isActive = false;
}

CBgm::CBgm(const float _priority,  int *_bgm) {
	m_id = CAST::BGM;
	m_Phase = BGMPHASE::START;
	m_priority = _priority;
	m_isActive = true;
	m_Volume = 255;
	m_Bgm = _bgm;
}

void CBgm::Update(void) {
	const int VOLUMESTEP = 3;
	switch (m_Phase)
	{
	case BGMPHASE::START:
		//初期音量をセットしてからBGM再生
		ChangeVolumeSoundMem(m_Volume, *m_Bgm);
		PlaySoundMem(*m_Bgm, DX_PLAYTYPE_LOOP);
		m_Phase = BGMPHASE::PLAY;
		break;
	case BGMPHASE::PLAY:
		break;
	case BGMPHASE::END:
		//音量を徐々に小さくしていく
		m_Volume -= VOLUMESTEP;
		ChangeVolumeSoundMem(m_Volume, *m_Bgm);
		if (m_Volume <= 0) {
			Deth();
		}
		break;
	default:
		assert(false);
	}
}

void CBgm::Deth() {
	StopSoundMem(*m_Bgm);
	m_isActive = false;
}

void CBgm::ChangePhase(BGMPHASE _phase) {
	m_Phase = _phase;
}