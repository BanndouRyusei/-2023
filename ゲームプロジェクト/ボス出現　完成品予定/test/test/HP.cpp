//---------------------------
// HP
//---------------------------
#include"UI.h"

CHP::CHP(float _priority) :CTask(_priority, CAST::HP) {
	m_DrawTask.Init(this, std::bind(&CHP::Draw, this), _priority);
	m_HP = 0;
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

	const int HPBAR_WPOS = 200;
	const int HPBAR_HPOS = 50;

	DrawGraph(HPBAR_WPOS, HPBAR_HPOS, m_HPBar, true);
	for (int i = 0; i < m_HP; i++) {
		DrawGraph(HPBAR_WPOS + (HP_W * i), HPBAR_HPOS, m_HPImage, true);
	}
}