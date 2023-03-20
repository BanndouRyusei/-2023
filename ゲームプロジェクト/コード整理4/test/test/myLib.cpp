//-----------------------
//myLib.cpp
//-----------------------
#include "myLib.h"

//�O���[�o���ϐ�
int g_Score = 0;

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

//�����`���m�̓����蔻��
//a=�����`a�@b=�����`b
//l=���[t=��[r=�E�[b=���[
bool IsHitBox(float _ax, float _ay, float _bx, float _by, Rect _arect, Rect _brect) {
	float al = _ax;
	float at = _ay + _arect.Height;
	float ar = al + _arect.Width;
	float ab = at + _arect.Height;

	float bl = _bx;
	float bt = _by + _arect.Height;
	float br = bl + _brect.Width;
	float bb = bt + _brect.Height;

	if (al < br&&bl < ar&&at < bb&&bt < ab) {
		return true;
	}
	else {
		return false;
	}
}

//�������m�̓����蔻��
//Z���W���m�̓����蔻�������
bool IsHitZLine(float _az, float _bz, float _awidth, float _bwidth) {
	float at = _az + _awidth / 2;
	float au = _az - _awidth / 2;
	
	float bt = _bz + _bwidth / 2;
	float bu = _bz - _bwidth / 2;

	if (at >= bu && au <= bt) {
		return true;
	}
	else {
		return false;
	}
}

//�I�u�W�F�N�g���m�̓����蔻��
//�����@���W _apos _bpos�@�I�u�W�F�N�g�̌���(Z����) _awidth _bwidth�@�摜�n���h�� _aghandle _bghandle
bool IsHitObject(const VECTOR& _apos, const VECTOR& _bpos, float _awidth, float _bwidth, int _aghandle, int _bghandle) {
	//�摜�T�C�Y���擾
	int aSizeX, aSizeY;
	int bSizeX, bSizeY;
	GetGraphSize(_aghandle, &aSizeX, &aSizeY);
	GetGraphSize(_bghandle, &bSizeX, &bSizeY);

	Rect arect, brect;
	arect.Width = aSizeX; arect.Height = aSizeY;
	brect.Width = bSizeX; brect.Height = bSizeY;

	if (IsHitBox(_apos.x, _apos.y, _bpos.x, _bpos.y, arect, brect) && IsHitZLine(_apos.z, _bpos.z, _awidth, _bwidth)) {
		return true;
	}
	else {
		return false;
	}
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

//�O�������W���(VECTOR�^)��Z�̒l�̈�����������ĕ`��D��x(float�^)��n���֐�
//�n���`��D��x��OBJECT_DRAWPRIORITY_MIN����OBJECT_DRAWPRIORITY_MAX�̊�
float ChangePriority(const float &_z) {
	return OBJECT_DRAWPRIORITY_MAX - _z / OBJECT_Z_MAX;
}

//�x���g�X�N���[���p�I�u�W�F�N�g�`��֐�
void DrawObject(const VECTOR& _pos, const int _Grhandle, const bool _isturn,const float _rot) {
	//�摜�T�C�Y���擾
	float SizeX, SizeY;
	GetGraphSizeF(_Grhandle, &SizeX, &SizeY);
	DrawRotaGraph2F(_pos.x + SizeX / 2, WINDOW_H - _pos.y - _pos.z - SizeY / 2.0f, SizeX / 2.0f, SizeY / 2.0f, 1.0, DEG2RAD(_rot), _Grhandle, TRUE, _isturn);
}

#if defined(_DEBUG) | defined(DEBUG)
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
#endif

//CVector2D
CVector2D& CVector2D::operator+=(const CVector2D& ope) {
	x += ope.x;
	y += ope.y;
	return *this;
}

CVector2D& CVector2D::operator-=(const CVector2D& ope) {
	x -= ope.x;
	y -= ope.y;
	return *this;
}
CVector2D& CVector2D::operator=(const CVector2D& ope) {
	x = ope.x;
	y = ope.y;
	return *this;
}
CVector2D CVector2D::operator+(const CVector2D& ope) {
	float tempX, tempY;
	tempX = x + ope.x;
	tempY = y + ope.y;
	return CVector2D(tempX, tempY);
}
bool CVector2D::operator==(const CVector2D& ope) {
	if ((x == ope.x) && (y == ope.y))
		return true;
	else
		return false;
}
bool CVector2D::operator!=(const CVector2D& ope) {
	if ((x != ope.x) && (y != ope.y))
		return true;
	else
		return false;
}

//2D���W���擾
CVector2D VGet2D(float x, float y) {
	return CVector2D(x, y);
}