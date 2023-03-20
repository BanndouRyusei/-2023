//---------------------------
//Chara_Shadow.cpp
//---------------------------
#include"Shadow.h"
#include"ShadowManager.h"

CShadow::CShadow() : m_Image(0),m_Pos(VGet(0.0f,0.0f,0.0f)), m_MaxY(0),m_ExtRateX(0.0),m_ExtRateY(0.0),m_SizeX(0),m_SizeY(0),m_Turn(false),m_Regist(false) {
}

CShadow::~CShadow() {
	RemoveShadow();
	DeleteGraph(m_Image);
}

void CShadow::Update() {}

void CShadow::Draw() {

	//�摜�̎��R�ό`�̂��߂̍��W
	CVector2D LD, RD, LU, RU;		//�����A�E���A����A�E����W

	//�摜�̂S�̊p���w�肵�ĕό`���Ă���		
	//�e�̉摜�������̒����Ɍ������ďk������悤�ɕό`������
	//������ς������Ȃ����߉�����Y���W�ɂ͊g�k���𔽉f�����Ă��Ȃ�
	//������X���W��m_Pos.x�A�E����X���W��m_Pos.x+m_SizeX
	//������Y���W��WINDOW_H-m_Pos.z�A�㑤��Y���W��WINDOW_H-m_Pos.z-m_SizeY�i�e�Ȃ̂ŃI�u�W�F�N�g��Y���W�v�f�͍l�����Ȃ��j
	//�g��k���̂��߂�(m_SizeX / 2 - m_SizeX / 2 * m_ExtRateX)��������X���W�ɑ����Ă���B�E���̏ꍇ�͈����Ă���
	//�����l�̉摜�T�C�Y�����ׂ�2�Ŋ����Ă���͉̂摜�̉��T�C�Y�̔�����X���W�𒴂��Ȃ��悤�ɂ��邽��
	//Y�̊g�k�͏㑤�̂ݍs���̂�(m_SizeY - m_SizeY * m_ExtRateY)���㑤��Y���W�ɑ����Ă���
	//Y���W�̑����l�̉摜�T�C�Y��2�Ŋ����Ă��Ȃ��͉̂摜�{�̂̉����ɉe�����邽��
	LD = VGet2D(m_Pos.x + (m_SizeX / 2 - m_SizeX / 2 * (float)m_ExtRateX), WINDOW_H - m_Pos.z);
	RD = VGet2D((m_Pos.x + m_SizeX) - (m_SizeX / 2 - m_SizeX / 2 * (float)m_ExtRateX), WINDOW_H - m_Pos.z);
	LU = VGet2D(m_Pos.x + (m_SizeX / 2 - m_SizeX / 2 * (float)m_ExtRateX), (WINDOW_H - m_Pos.z - m_SizeY) + (m_SizeY - m_SizeY * (float)m_ExtRateY));
	RU = VGet2D((m_Pos.x + m_SizeX) - (m_SizeX / 2 - m_SizeX / 2 * (float)m_ExtRateX), (WINDOW_H - m_Pos.z - m_SizeY) + (m_SizeY - m_SizeY * (float)m_ExtRateY));

	//�摜��Y�����]����
	//�摜�̉����~���g�k���������đ���(���E��X���W�����ւ���)
	if (m_Turn) {
		LD.x += m_SizeX * (float)m_ExtRateX;
		LU.x += m_SizeX * (float)m_ExtRateX;
		RD.x -= m_SizeX * (float)m_ExtRateX;
		RU.x -= m_SizeX * (float)m_ExtRateX;
	}

	DrawModiGraphF(LU.x, LU.y, RU.x, RU.y, RD.x, RD.y, LD.x, LD.y, m_Image, TRUE);
}

//�e�̍��W�X�V���̊֐����e���o���L�����̃A�b�v�f�[�g�ŌĂԂ��Ƃɂ��e���L�����ɂ��Ă���
void CShadow::ObjectPosGet(const VECTOR& _pos, bool _turn) {
	m_Pos = _pos;
	m_Turn = _turn;
	if (m_MaxY == 1.0f) {
		m_Pos.y = 0.0f;
	}
	m_ExtRateX = 1.0 - (double)(m_Pos.y / m_MaxY);
	m_ExtRateY = m_ExtRateX;
}

//�e�̏����l��ݒ肷��B
//���� : _shadow �e�̃C���[�W�摜 : _pos  ���W : _turn ���W : _maxy ���̃I�u�W�F�N�g��Y���W���E�l(�w�肵�Ȃ���Ίg��k���͂��Ȃ�)
void CShadow::SetShadow(int _shadow, const VECTOR& _pos, bool _turn, float _maxy) {
	m_Image = _shadow;
	m_Pos = _pos;
	m_MaxY = _maxy;
	if (m_MaxY == 1.0f) {			//�f�t�H���g�������g���Ă�����Y���W���l�����Ȃ�
		m_Pos.y = 0.0f;
	}
	m_ExtRateX = 1.0 - (double)(m_Pos.y / m_MaxY);
	m_ExtRateY = m_ExtRateX;
	GetGraphSize(m_Image, &m_SizeX, &m_SizeY);
	m_Turn = _turn;
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