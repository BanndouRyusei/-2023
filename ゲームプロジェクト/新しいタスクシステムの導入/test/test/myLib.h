//--------------
//myLib.h
//--------------
#ifndef _MYLIB_H_
#define _MYLIB_H_
#pragma once

#define _CRT_SECURE_NO_DEPRECATE
//�w�b�_�[�t�@�C��
#include"DxLib.h"
#include"resource.h"
#include"assert.h"
#include<stdlib.h>
#include<time.h>
#include <list>
#include<math.h>
#include"TaskManager.h"

using namespace std;

//�v���v���Z�b�T
#define RANDMIZE()		(srand((unsigned)time(NULL)))
#define DEG2RAD(deg) (deg*3.141592f/180.0f)

const float FRAMETIME_S = 0.016666f;	//=(1.0f/MAX_FPS)
const float FRAMETIME_MS = 16.666f;		//=(1000ms/MAX_FPS)
const float DEG2RAD = 0.0174528f;		//=(2.0f*3.1415f/360.0f)
const float PI = 3.1415f;							//�~����

const int	WINDOW_W = 960;
const int	WINDOW_H = 800;

const int MAX_FPS = 60;					//�ő�FPS
const float SPF = (WORD)(1000.0 / MAX_FPS + 0.5);	//1�t���[���̎���[ms]
const bool	WINDOW_SCREEN = true;

const int ALPHA_MAX = 255;
const int ALPHA_STEP = 5;

const int DIGITS = 10; //�����̌�

const float OBJECT_DRAWPRIORITY_MAX = 2.0f;
const float OBJECT_DRAWPRIORITY_MIN = OBJECT_DRAWPRIORITY_MAX - 1.0f;
const float OBJECT_Z_MAX = 200.0f;

typedef unsigned char BYTE;
typedef unsigned long DWORD;

//�L�[���s�[�g�𖳌������āA�L�[���͂��s��
bool IsKeyTrigger(int key, int key_type);

//�^����ꂽ���l�̕�����Ԃ�
int IsSign(float a);

//�w��͈̔͂��烉���_���Ō��肵���l���擾����i���������_�l�j
//		�߂�l�F�����_���Ō��肵���l
float GetRandomFloat(
	//�ő�l
	float MaxF,

	//�ŏ��l
	float MinF
);

//2�̃x�N�g�����󂯎��Ac����p�ւ̃x�N�g�������߂�
//�߂�l : ���K���ς݂̃x�N�g��(xyz)
VECTOR VectorAngle(const VECTOR &p, const VECTOR &c);

//2�̃x�N�g�����󂯎��Ac����p�ւ̃x�N�g�������߂�
//�߂�l : ���K���ς݂̃x�N�g��(xz)
VECTOR VectorAngle_xz(const VECTOR &p, const VECTOR &c);

//2�̃x�N�g�����󂯎��Ac����p�ւ̃x�N�g�������߂�
//�߂�l : ���K���ς݂̃x�N�g��(yz)
VECTOR VectorAngle_yz(const VECTOR &p, const VECTOR &c);

//_src����_dist�ւ̉�]��_time�ŕ��������p�x�����߂�
//���� _dist : �ړI�p _src : �����p
//�ԋp�l:�����p
float MovementDirection(const float _dist, const float _src, const int _time);

//2�̍��W���󂯎��A���������ǂ����𔻒f����
//�߂�l : bool�^
bool VectorEqual(const VECTOR &p, const VECTOR &c);

//�f�o�b�O�p�R���\�[���Ăяo��
void DebugModeOn(void);

//����p���̍쐬
void MakePlayerCapsule(const VECTOR& _pos, const VECTOR& _cenpos,
	const float _height, VECTOR* _cap1, VECTOR* _cap2);

//�{�b�N�X��2D���W�̓����蔻��
bool IsHitCheckBox_Point(const int *_x, const int *_y, const int _width, const int _height, const int *_2x, const int *_2y);

//�O�������W���(VECTOR�^)��Z�̒l�̈�����������ĕ`��D��x(float�^)��n���֐�
//�n���`��D��x��CHARA_DRAWPRIORITY_MIN�`CHARA_DRAWPRIORITY_MAX�̊�
float ChangePriority(const float* _z);

#endif _MYLIB_H_

