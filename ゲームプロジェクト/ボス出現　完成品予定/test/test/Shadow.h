//-----------------
//Shadow.h
//-----------------
#ifndef _SHADOW_H_
#define _SHADOW_H_
#pragma once

//�w�b�_�[�t�@�C��
#include"myLib.h"

//�ۉe�֌W

//�萔

//�ۉe�N���X
class CShadow {
private:
	int m_Image;
	VECTOR m_Pos;
	float m_MaxY;
	double m_ExtRateX, m_ExtRateY;
	int m_SizeX, m_SizeY;
	bool m_Turn;
	bool m_Regist;
public:
	CShadow();
	~CShadow();
	void Update();
	void Draw();
	void ObjectPosGet(const VECTOR& _pos, bool _turn);							//�e�̍��W�X�V���̊֐����e���o���L�����̃A�b�v�f�[�g�ŌĂԂ��Ƃɂ��e���L�����ɂ��Ă���
	void SetShadow(int _shadow, const VECTOR& _pos, bool _turn, float _maxy = 1.0f);			//�e�̏����l��ݒ肷��B�L�������Ƃɉe�̉摜���w��B_maxy�̓L������Y���̍ő�l(��΂Ȃ��L�����̏ꍇ�̓f�t�H���g�������g�p����)
	void RegistShadow();		//�e�̃��X�g�ɒǉ�
	void RemoveShadow();		//�e�̃��X�g�������
};

#endif _SHADOW_H