//---------------------------
// SCORE
//---------------------------
#include"UI.h"

const int SCORE_SIZE = 40;

const int SCORE_WPOS = 810;
const int SCORE_HPOS = 50;

const int MAX_SCORE = 99999;

const int MIN_FIGURE = 5;  // 0Çí«â¡Ç∑ÇÈå¬êî

CScore::CScore(float _priority) :CTask(_priority, CAST::SCORE){
	m_DrawTask.Init(this, std::bind(&CScore::Draw, this), _priority);
	LoadDivGraph("Data\\img\\UI_Num.png", DIGITS, DIGITS, 1, SCORE_SIZE, SCORE_SIZE, m_ScoreImage);
	m_Score = 0;
}

CScore::~CScore() {
	g_Score = m_Score;
	for (int i = 0; i < DIGITS; i++) {
		DeleteGraph(m_ScoreImage[i]);
	}
}

void CScore::Update() {

}

void CScore::Draw() const {
	for (int i = 0; i < MIN_FIGURE || m_Score / (DWORD)pow(10, i); i++) {
		BYTE digit = (m_Score / (DWORD)pow(10, i)) % 10;
		DrawGraph((SCORE_WPOS - SCORE_SIZE * i), SCORE_HPOS, m_ScoreImage[digit], TRUE);
	}
}

void CScore::Add(DWORD _score) {
	m_Score += _score;
}