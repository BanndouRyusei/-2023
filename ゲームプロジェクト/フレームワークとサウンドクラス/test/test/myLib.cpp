//-----------------------
//myLib.cpp
//-----------------------
#include "myLib.h"

//�L�[���s�[�g�𖳌������āA�L�[���͂��s��
bool IsKeyTrigger(int key, int key_type) {
	static bool g_key_prev[256] = { false };
	if (key & key_type) {
		if (!g_key_prev[key_type]) {
			g_key_prev[key_type] = true;
			return true;
		}
	}
	else {
		g_key_prev[key_type] = false;
	}
	return false;
}

//��̍��W�̕�����Ԃ�
int IsSign(float a) {
	return (a > 0) - (a < 0);
}

//�w��͈̔͂��烉���_���Ō��肵���l���擾����i���������_�l�j
//		�߂�l�F�����_���Ō��肵���l
float GetRandomFloat(
	//�ő�l
	float MaxF,

	//�ŏ��l
	float MinF
)
{
	return GetRand(10000)*(MaxF - MinF) / 10000.0f + MinF;
}

//2�̃x�N�g�����󂯎��Ac����p�ւ̃x�N�g�������߂�
//�߂�l : ���K���ς݂̃x�N�g��(xyz)
VECTOR VectorAngle(const VECTOR &p, const VECTOR &c) {
	VECTOR p1, p2;
	p1 = p;
	p2 = c;
	return VNorm(VSub(p1, p2));
}

//2�̃x�N�g�����󂯎��Ac����p�ւ̃x�N�g�������߂�
//�߂�l : ���K���ς݂̃x�N�g��(xz)
VECTOR VectorAngle_xz(const VECTOR &p, const VECTOR &c) {
	VECTOR p1, p2;
	p1 = VGet(p.x, 0, p.z);
	p2 = VGet(c.x, 0, c.z);
	return VNorm(VSub(p1, p2));
}

//2�̃x�N�g�����󂯎��Ac����p�ւ̃x�N�g�������߂�
//�߂�l : ���K���ς݂̃x�N�g��(yz)
VECTOR VectorAngle_yz(const VECTOR &p, const VECTOR &c) {
	VECTOR p1, p2;
	p1 = VGet(0, p.y, p.z);
	p2 = VGet(0, c.y, c.z);
	return VNorm(VSub(p1, p2));
}

//_src����_dist�ւ̉�]��_time�ŕ��������p�x�����߂�
//���� _dist : �ړI�p _src : �����p
//�ԋp�l:�����p
float MovementDirection(const float _dist, const float _src, const int _time) {
	float angle;
	angle = _dist - _src;

	if (angle >= DX_PI_F) angle = -DX_TWO_PI_F + angle;
	else if (angle <= -DX_PI_F) angle = DX_TWO_PI_F + angle;

	return (angle / _time);
}

//2�̍��W���󂯎��A���������ǂ����𔻒f����
//�߂�l : bool�^
bool VectorEqual(const VECTOR &p, const VECTOR &c) {
	if (
		p.x == c.x&&
		p.y == c.y&&
		p.z == c.z
		) {
		return true;
	}
	else {
		return false;
	}
}

//�f�o�b�O�p�R���\�[���Ăяo��
void DebugModeOn(void) {
	//�f�o�b�O�p�ɃR���\�[�����Ăяo��
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONIN$", "r", stdin);
	//�f�o�b�O�R���\�[�����A�N�e�B�u�E�B���h�E�ɂȂ�̂�
	//�Q�[���{�̂̃E�B���h�E���A�N�e�B�u�ɂ���
	SetForegroundWindow(GetMainWindowHandle());
}

//����p���̍쐬
void MakePlayerCapsule(const VECTOR& _pos, const VECTOR& _cenpos,
	const float _height, VECTOR* _cap1, VECTOR* _cap2) {
	*_cap1 = *_cap2 = VAdd(_pos, _cenpos);
	_cap1->y -= _height / 2.0f;
	_cap2->y += _height / 2.0f;
}

//�{�b�N�X��2D���W�̓����蔻��
bool IsHitCheckBox_Point(const int *_x, const int *_y, const int _width, const int _height, const int *_2x, const int *_2y) {
	const int BOX_UL_X = *_x;		//�{�b�N�X����(X���W)�A�{�b�N�X����(X���W)
	const int BOX_UL_Y = *_y;		//�{�b�N�X����(Y���W)�A�{�b�N�X�E��(Y���W)
	const int BOX_UR_X = *_x + _width;		//�{�b�N�X�E��(X���W)�A�{�b�N�X�E��(X���W)
	const int BOX_UR_Y = *_y + _height;		//�{�b�N�X����(Y���W)�A�{�b�N�X�E��(Y���W)

	if (BOX_UL_X <= *_2x && BOX_UR_X >= *_2x && BOX_UL_Y <= *_2y && BOX_UR_Y >= *_2y) {
		return true;
	}
	else
		return false;
}