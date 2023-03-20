//---------------------------
// UI
//---------------------------
#include"UI.h"

CUI::CUI(float _priority) :CTask(_priority, CAST::UI) {
	m_DrawTask.Init(this, std::bind(&CUI::Draw, this), _priority);
	m_Back = LoadGraph("Data\\img\\UI_Back.png");
	m_Wipe = LoadGraph("Data\\img\\UI_Wipe.png");
}

CUI::~CUI() {
	DeleteGraph(m_Back);
	DeleteGraph(m_Wipe);
}

void CUI::Update() {

}

void CUI::Draw() const {
	const int WIPE_W = UI_CHIPSIZE * 5;
	const int WIPE_H = UI_CHIPSIZE * 5;
	DrawGraph(0, 0, m_Back, true);
	DrawGraph(UI_CHIPSIZE * 5, UI_CHIPSIZE * 4, m_Wipe, true);
}
