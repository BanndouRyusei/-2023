//---------------------------
//Chara_Shadow.cpp
//---------------------------
#include"Shadow.h"
#include"ShadowManager.h"

CShadow::CShadow() : m_Image(0),m_Pos(VGet(0.0f,0.0f,0.0f)),m_ExtRateX(0.0),m_ExtRateY(0.0),m_SizeX(0),m_SizeY(0),m_MaxY(0),m_Regist(false) {
}

CShadow::~CShadow() {
	RemoveShadow();
	DeleteGraph(m_Image);
}

void CShadow::Update() {}

void CShadow::Draw()const {
	DrawRotaGraph3(m_Pos.x + m_SizeX / 2, WINDOW_H - m_Pos.z - m_SizeY / 2.0f, m_SizeX / 2.0f, m_SizeY / 2.0f, m_ExtRateX, m_ExtRateY, 0.0, m_Image, TRUE, FALSE);
#if defined(_DEBUG) | defined(DEBUG)
	DrawCircle(m_Pos.x + m_SizeX / 2, WINDOW_H - m_Pos.z - m_SizeY / 2.0f, 5.0f, GetColor(0, 0, 255), TRUE);
#endif
}

//�e�̍��W�X�V���̊֐����e���o���L�����̃A�b�v�f�[�g�ŌĂԂ��Ƃɂ��e���L�����ɂ��Ă���
void CShadow::CharaPosGet(const VECTOR& _pos) {
	m_Pos = _pos;
	m_ExtRateX = 1.0 - (double)(m_Pos.y / m_MaxY);
	m_ExtRateY = m_ExtRateX;
}

//�e�̏����l��ݒ肷��B
//���� : _shadow �e�̃C���[�W�摜 : _pos ���W : _maxy ���̃I�u�W�F�N�g��Y���W���E�l
void CShadow::SetShadow(int _shadow, const VECTOR& _pos,float _maxy) {
	m_Image = _shadow;
	m_Pos = _pos;
	m_ExtRateX = 1.0 - (double)(m_Pos.y / m_MaxY);
	m_ExtRateY = m_ExtRateX;
	m_MaxY = _maxy;
	GetGraphSize(m_Image, &m_SizeX, &m_SizeY);
	//�摜�ϐ��Ȃǂ�����������ĂȂ��ăo�O�邩��
	m_Regist = false;
	RegistShadow();
}

//�e�̃��X�g�ɒǉ�
void CShadow::RegistShadow() {
	//�o�^����Ă��邩�ǂ������ɒ��ׂ�
	assert(!m_Regist);
	m_Regist = CShadowManager::GetInstance()->Regist(this);
}

//�e�̃��X�g�������
void CShadow::RemoveShadow() {
	//�o�^����Ă��邩�ǂ������ɒ��ׂ�
	assert(m_Regist);
	m_Regist = CShadowManager::GetInstance()->Remove(this);
}

//�e�����X�g�ɓo�^����Ă��邩�ǂ������ׂ�֐�
//bool CShadow::IsRegist() {
//	return m_Regist;
//}