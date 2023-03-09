//---------------------------
//Stage.cpp
//---------------------------
#include"Stage.h"

CStage::CStage(float _priority) :Task(_priority, CAST::STAGE) {
	m_drawTask.Init(this, std::bind(&CStage::Draw, this), _priority);
	m_Cx[(int)e_STAGES::BACK] = 0.0f;
	m_Cx[(int)e_STAGES::FRONT ] = 0.0f;
	char buf[30];
	for (auto i = 0; i < (int)e_STAGES::NONE; i++) {
		sprintf_s(buf, "Data\\img\\Stage%d.png",  i);
		m_Image[i] = LoadGraph(buf);
		if (m_Image[i] == -1)assert(false);
	}
}

CStage::~CStage() {
	for (auto i = 0; i < (int)e_STAGES::NONE; i++) {
		DeleteGraph(m_Image[i]);
	}
}

void CStage::Update() {
	//m_Cx[(int)e_STAGES::FRONT]--;
	if (m_Cx[(int)e_STAGES::FRONT] < -WINDOW_W) {
		m_Cx[(int)e_STAGES::FRONT] = 0.0f;
	}
}

void CStage::Draw() const {
	DrawGraphF(m_Cx[(int)e_STAGES::BACK], GROUND_H, m_Image[(int)e_STAGES::BACK], TRUE);
	DrawGraphF(m_Cx[(int)e_STAGES::BACK] + WINDOW_W, GROUND_H, m_Image[(int)e_STAGES::BACK], TRUE);
	DrawGraphF(m_Cx[(int)e_STAGES::FRONT], GROUND_H, m_Image[(int)e_STAGES::FRONT], TRUE);
	DrawGraphF(m_Cx[(int)e_STAGES::FRONT] + WINDOW_W, GROUND_H, m_Image[(int)e_STAGES::FRONT], TRUE);
	DrawGraphF(m_Cx[(int)e_STAGES::FRONT], GROUND_H + STAGE_H, m_Image[(int)e_STAGES::GROUND], TRUE);
	DrawGraphF(m_Cx[(int)e_STAGES::FRONT] + WINDOW_W, GROUND_H + STAGE_H, m_Image[(int)e_STAGES::GROUND], TRUE);
}