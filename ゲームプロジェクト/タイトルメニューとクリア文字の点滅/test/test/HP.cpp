//---------------------------
// HP
//---------------------------
#include"UI.h"

CHP::CHP(float _priority) :CTask(_priority, CAST::HP) {
	m_DrawTask.Init(this, std::bind(&CHP::Draw, this), _priority);
	m_HPImage = LoadGraph("Data\\img\\UI_HP.png");
	m_HPBar = LoadGraph("Data\\img\\UI_HPBar.png");
}

CHP::~CHP() {
	DeleteGraph(m_HPImage);
	DeleteGraph(m_HPBar);
}

// ÉvÉåÉCÉÑÅ[ÇÃHPÇäiî[Ç∑ÇÈ
void CHP::SetPlayerHp(const int _hp) {
	m_HP = _hp;
}

void CHP::Update() {

}

void CHP::Draw() const {

	const int HP_MAX = 5;
	const int HP_W = 54;
	const int HP_H = 30;
	const int HPBAR_W = UI_CHIPSIZE * 17;
	const int HPBAR_H = UI_CHIPSIZE * 5;

	DrawGraph(HPBAR_W, HPBAR_H, m_HPBar, true);
	for (int i = 0; i < m_HP; i++) {
		DrawGraph(HPBAR_W + (HP_W * i), HPBAR_H, m_HPImage, true);
	}
}