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
	double m_ExtRateX, m_ExtRateY;
	int m_SizeX, m_SizeY;
	float m_MaxY;
	bool m_Regist;
public:
	CShadow();
	~CShadow();
	void Update();
	void Draw()const;
	void CharaPosGet(const VECTOR& _pos);							//�e�̍��W�X�V���̊֐����e���o���L�����̃A�b�v�f�[�g�ŌĂԂ��Ƃɂ��e���L�����ɂ��Ă���
	void SetShadow(int _shadow, const VECTOR& _pos, float _maxy = 0.0f);			//�e�̏����l��ݒ肷��B�L�������Ƃɉe�̉摜���w��ł����炢���ȂƎv�������ɓ���Ă���
	void RegistShadow();		//�e�̃��X�g�ɒǉ�
	void RemoveShadow();		//�e�̃��X�g�������
	//bool IsRegist();				//�e�����X�g�ɓo�^����Ă��邩�ǂ������ׂ�֐�
};

#endif _SHADOW_H