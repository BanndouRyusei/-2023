//---------------------------
// LIFE
//---------------------------
#include"UI.h"

CLife::CLife(float _priority) :CTask(_priority, CAST::LIFE) {
	m_DrawTask.Init(this, std::bind(&CLife::Draw, this), _priority);
	m_LifeImage = LoadGraph("Data\\img\\UI_Life.png");
	m_LifeBar = LoadGraph("Data\\img\\UI_LifeBae.png");
}

CLife::~CLife() {
	DeleteGraph(m_LifeBar);
	DeleteGraph(m_LifeImage);
}

// プレイヤーの残機を格納する
void CLife::SetPlayerLife(const int _life) {
	m_Life = _life;
}

void CLife::Update() {

}

void CLife::Draw() const {

	const int LIFE_MAX = 3;
	const int LIFE_SIZE = 50;

	const int LIFEBAR_WPOS = 200;
	const int LIFEBAR_HPOS = 95;
	const int LIFE_WPOS = LIFEBAR_WPOS + LIFE_SIZE;

	DrawGraph(LIFEBAR_WPOS, LIFEBAR_HPOS, m_LifeBar, true);
	for (int i = 0; i < m_Life; i++) {
		DrawGraph(LIFE_WPOS + (LIFE_SIZE * i), LIFEBAR_HPOS, m_LifeImage, true);
	}
}