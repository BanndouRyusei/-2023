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
	const int LIFE = 50;
	const int LIFEBAR_W = UI_CHIPSIZE * 17;
	const int LIFEBAR_H = UI_CHIPSIZE * 9;
	const int LIFE_W = LIFEBAR_W + LIFE;

	DrawGraph(LIFEBAR_W, LIFEBAR_H, m_LifeBar, true);
	for (int i = 0; i < m_Life; i++) {
		DrawGraph(LIFE_W + (LIFE * i), LIFEBAR_H, m_LifeImage, true);
	}
}