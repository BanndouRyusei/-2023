//----------------------
//Clear.cpp
//----------------------

//�w�b�_�[�t�@�C��
#include"Clear.h"
#include"Sound.h"

//�萔
//�����̉摜�̃T�C�Y
const int SCORE_DIGI_W = 40;
const int SCORE_DIGI_H = 40;
//�v���C���[�X�R�A�̕\���ʒu
const int PLAYER_SCORE_RIGHT = 550;
const int PLAYER_SCORE_TOP = 550;
//�����L���O�X�R�A�̕\���ʒu
const int RANK_SCORE_RIGHT = 550;
const int RANK_SCORE_TOP = 190;
const int RANK_SCORE_SPECE = 90;			//�����L���O�X�R�A�̊Ԋu
const int MIN_DIGIT = 5;			//�\������0�̐�

CClear::CClear(float _priority) :CTask(_priority, CAST::CLEAR), m_RankScore(), m_Digits() {
	m_DrawTask.Init(this, std::bind(&CClear::Draw, this), _priority);
	m_Phase = PHASE::START;
	m_Timer = 0;
	m_Alpha = 0;
	m_CharAlpha = 255;
	m_AlphaTurn = 1;
	//�O���[�o���ϐ��ɓ����Ă���v���C���[�̃X�R�A������
	m_PlayerScore = g_Score;
	LoadScore();
	SortScore();
	m_Image = LoadGraph("Data\\img\\ClearScreen.png");
	if (m_Image == -1)assert(false);
	m_CharImage= LoadGraph("Data\\img\\ClearChar.png");
	if (m_CharImage == -1)assert(false);
	LoadDivGraph("Data\\img\\UI_Num.png", DIGITS, DIGITS, 1, SCORE_DIGI_W, SCORE_DIGI_H, m_Digits);
	if (m_Digits[0] == -1)assert(false);
}

CClear::~CClear() {
	DeleteGraph(m_Image);
	for (int i = 0; i < DIGITS; i++) {
		DeleteGraph(m_Digits[0]);
	}
	SaveScore();
}

void CClear::Update() {
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	CBGM* bgm;

	m_Timer++;

	switch (m_Phase)
	{
	case PHASE::START:
		m_Alpha = m_Timer * ALPHA_STEP;
		if (key || m_Alpha >= ALPHA_MAX) {
			m_Phase = PHASE::PLAY;
			m_Alpha = ALPHA_MAX;
		}
		break;
	case PHASE::PLAY:
		//Z�L�[�Ń^�C�g���ւ̕�����_�ł�����
		m_CharAlpha += ALPHA_STEP * m_AlphaTurn;
		if (m_CharAlpha > ALPHA_MAX || m_CharAlpha < 0) {
			m_CharAlpha = ALPHA_MAX * m_AlphaTurn;			//�l�̏�����(ALPHA_MAX���傫���ꍇ��ALPHA_MAX)
			if (m_CharAlpha < 0) {			//0��菬�����ꍇ��0
				m_CharAlpha = 0;
			}
			m_AlphaTurn *= -1;			//�����l�̔��]
		}
		if (IsKeyTrigger(key, PAD_INPUT_A)) {			//Z�L�[��������
			bgm = (CBGM*)CTaskManager::Instance()->GetTask(CAST::BGM);		//BGM�̏I��
			bgm->ChangePhase(PHASE::END);
			m_CharAlpha = ALPHA_MAX;
			m_Phase = PHASE::END;
			CControlSound::GetInstance()->CreateSE(e_SE::SELECT);
		}
		break;
	case PHASE::END:
		if (!CTaskManager::Instance()->GetCount(CAST::BGM)) {			//BGM����I�������
			throw(0);
			Delete();
		}
		break;
	case PHASE::NONE:
	default:
		assert(false);
	}
}

void CClear::Draw() const {
	SetDrawBright(m_Alpha, m_Alpha, m_Alpha);
	DrawGraph(0, 0, m_Image, TRUE);
	for (int i = 0; i < RANK; i++) {
		for (int j = 0; j < MIN_DIGIT || m_RankScore[i] / (DWORD)pow(10, j); j++) {
			BYTE digit = (m_RankScore[i] / (DWORD)pow(10, j)) % 10;
			DrawGraph((RANK_SCORE_RIGHT - SCORE_DIGI_W * j), RANK_SCORE_TOP + RANK_SCORE_SPECE * i, m_Digits[digit], TRUE);
		}
	}
	for (int i = 0; i < MIN_DIGIT || m_PlayerScore / (DWORD)pow(10, i); i++) {
		BYTE digit = (m_PlayerScore / (DWORD)pow(10, i)) % 10;
		DrawGraph((PLAYER_SCORE_RIGHT - SCORE_DIGI_W * i), PLAYER_SCORE_TOP, m_Digits[digit], TRUE);
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_CharAlpha);
	DrawGraph(300, 700, m_CharImage, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, ALPHA_MAX);
	SetDrawBright(ALPHA_MAX, ALPHA_MAX, ALPHA_MAX);
}

//�e�L�X�g�t�@�C��������3�ʂ̃X�R�A��ǂݍ���
void CClear::LoadScore() {
	int fh;

	fh = FileRead_open("Data\\txt\\Rank.txt");

	if (fh == FALSE) {
		assert(false);
	}

	for (int i = 0; i < RANK; i++) {
		FileRead_scanf(fh, "%d", &m_RankScore[i]);
	}

	FileRead_close(fh);
}

//�e�L�X�g�t�@�C���ɏ�ʂR�ʂ̃X�R�A����������
void CClear::SaveScore() {
	FILE* fp;

	fopen_s(&fp, "Data\\txt\\Rank.txt", "wt");

	if (fp == NULL) {
		assert(false);
		return;
	}

	for (int i = 0; i < RANK; i++) {
		fprintf_s(fp, "%d\n", m_RankScore[i]);
	}

	fclose(fp);
}

//�v���C���[�̃X�R�A�ƃ����L���O�X�R�A�̕��ёւ����s��
void CClear::SortScore() {
	//����ւ����̃X�R�A�Ƀv���C���[�̃X�R�A������
	//���ёւ����p�̃X�R�A��p�ӂ��Ă���
	int shiftscore = m_PlayerScore, score;

	//���ёւ�
	for (int i = 0; i < RANK; i++) {
		//����ւ����̃X�R�A�Ə�ʂR�ʂ̃X�R�A���ׂ�
		//����ւ����̃X�R�A�̂ق����傫����Γ���ւ���
		if (shiftscore >= m_RankScore[i]) {
			score = m_RankScore[i];
			m_RankScore[i] = shiftscore;
			shiftscore = score;
		}
	}
}