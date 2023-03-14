//---------------------------
//Stage.cpp
//---------------------------
#include"Stage.h"

CStage::CStage(float _priority) :CTask(_priority, CAST::STAGE),m_Cx(),m_Image() {
	m_DrawTask.Init(this, std::bind(&CStage::Draw, this), _priority);
	for (int i = 0; i < (int)e_STAGES::NONE; i++) {
		m_Cx[i] = 0.0f;
	}
	char buf[30];
	for (auto i = 0; i < (int)e_STAGES::NONE; i++) {
		sprintf_s(buf, "Data\\img\\Stage%d.png",  i);
		m_Image[i] = LoadGraph(buf);
		if (m_Image[i] == -1)assert(false);
	}
	m_ScrollX = 0.0f;
}

CStage::~CStage() {
	for (auto i = 0; i < (int)e_STAGES::NONE; i++) {
		DeleteGraph(m_Image[i]);
	}
}

void CStage::Update() {
	for (int i = 0; i < (int)e_STAGES::NONE; i++) {
		if (m_Cx[i] < -WINDOW_W) {
			m_Cx[i] = 0.0f;
		}
	}
}

void CStage::Draw() const {
	DrawGraphF(m_Cx[(int)e_STAGES::BACK], GROUND_H, m_Image[(int)e_STAGES::BACK], TRUE);			//ˆê–‡–Ú‰æ‘œ	(^‚ñ’†‚©‚ç‰E‚É—¬‚ê‚é‰æ‘œ)
	DrawGraphF(m_Cx[(int)e_STAGES::BACK] + WINDOW_W, GROUND_H, m_Image[(int)e_STAGES::BACK], TRUE);			//“ñ–‡–Ú‰æ‘œ	(‰E‚©‚ç—¬‚ê‚Ä‚­‚é‰æ‘œ)
	DrawGraphF(m_Cx[(int)e_STAGES::FRONT], GROUND_H, m_Image[(int)e_STAGES::FRONT], TRUE);
	DrawGraphF(m_Cx[(int)e_STAGES::FRONT] + WINDOW_W, GROUND_H, m_Image[(int)e_STAGES::FRONT], TRUE);
	DrawGraphF(m_Cx[(int)e_STAGES::FRONT], GROUND_H + STAGE_H, m_Image[(int)e_STAGES::GROUND], TRUE);
	DrawGraphF(m_Cx[(int)e_STAGES::FRONT] + WINDOW_W, GROUND_H + STAGE_H, m_Image[(int)e_STAGES::GROUND], TRUE);
}

//‚Ç‚ê‚¾‚¯ƒXƒNƒ[ƒ‹‚µ‚½‚©‚ð•Ô‚·
float CStage::GetScrollX() {
	return m_ScrollX;
}

//‰æ–Ê‚ðƒXƒNƒ[ƒ‹‚³‚¹‚é
void CStage::MoveScrollX() {
	m_ScrollX++;
	m_Cx[(int)e_STAGES::FRONT] -= STAGE_SCROLLX;
	m_Cx[(int)e_STAGES::GROUND] -= STAGE_SCROLLX;
	if (fmod(m_ScrollX, 2) == 0) {			//‰œ‚ÆŽè‘O‚Ì”wŒi‚É·‚ð—^‚¦‚é‚±‚Æ‚Å”wŒi‚ª“¯‚¶‰æ‘œ‚ÌŒJ‚è•Ô‚µ•\Ž¦‚É‚È‚é‚Ì‚ð–h‚®
		m_Cx[(int)e_STAGES::BACK] -= STAGE_SCROLLX;
	}
}