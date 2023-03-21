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
	m_IsScroll = false;
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
	DrawGraphF(m_Cx[(int)e_STAGES::BACK], GROUND_H, m_Image[(int)e_STAGES::BACK], TRUE);			//�ꖇ�ډ摜	(�^�񒆂���E�ɗ����摜)
	DrawGraphF(m_Cx[(int)e_STAGES::BACK] + WINDOW_W, GROUND_H, m_Image[(int)e_STAGES::BACK], TRUE);			//�񖇖ډ摜	(�E���痬��Ă���摜)
	DrawGraphF(m_Cx[(int)e_STAGES::FRONT], GROUND_H, m_Image[(int)e_STAGES::FRONT], TRUE);
	DrawGraphF(m_Cx[(int)e_STAGES::FRONT] + WINDOW_W, GROUND_H, m_Image[(int)e_STAGES::FRONT], TRUE);
	DrawGraphF(m_Cx[(int)e_STAGES::FRONT], GROUND_H + STAGE_H, m_Image[(int)e_STAGES::GROUND], TRUE);
	DrawGraphF(m_Cx[(int)e_STAGES::FRONT] + WINDOW_W, GROUND_H + STAGE_H, m_Image[(int)e_STAGES::GROUND], TRUE);
}

//�ǂꂾ���X�N���[����������Ԃ�
float CStage::GetScrollX() {
	return m_ScrollX;
}

//��ʂ��X�N���[��������
void CStage::MoveScrollX() {
	if (!m_IsScroll) {
		m_ScrollX++;
		m_Cx[(int)e_STAGES::FRONT] -= STAGE_SCROLLX;
		m_Cx[(int)e_STAGES::GROUND] -= STAGE_SCROLLX;
		if (fmod(m_ScrollX, 2) == 0) {			//���Ǝ�O�̔w�i�ɍ���^���邱�ƂŔw�i�������摜�̌J��Ԃ��\���ɂȂ�̂�h��
			m_Cx[(int)e_STAGES::BACK] -= STAGE_SCROLLX;
		}
	}
}

//��ʃX�N���[�������b�N����
void CStage::ScrollLock() {
	m_IsScroll = true;
}