//-----------------
//CharaBase.h
//-----------------
#ifndef _CHARABASE_H_
#define _CHARABASE_H_
#pragma once

//�w�b�_�[�t�@�C��
#include"ObjectBase.h"
#include"Shadow.h"
//�萔

class CCharaBase :public CObjectBase {
protected:
	int m_Frame, m_Timer;		//�A�j���[�V�����t���[���ƃ^�C�}�[
	bool m_Turn;			//�摜�̔��]�\��
	int m_HP;		//�L�����N�^�[�̗̑�
	CShadow m_Shadow;
	int m_ShadowImage;
	float m_Speed;
	VECTOR m_Temp;
	float m_ScrollX;
public:
	CCharaBase(float _priority, CAST _id) : CObjectBase(_priority, _id)
	,m_Frame(0), m_Timer(0), m_Turn(false),m_HP(0),m_Shadow(),m_ShadowImage(0) {};
	virtual ~CCharaBase() {};
	virtual void Update() {};
	virtual void Draw() const {};
};

#endif _CHARABASE_H_
