//-----------------
//CharaBase.h
//-----------------
#ifndef _CHARABASE_H_
#define _CHARABASE_H_
#pragma once

//�w�b�_�[�t�@�C��
#include"ObjectBase.h"
//�萔

class CCharaBase :public CObjectBase {
protected:
	int m_Frame, m_Timer;		//�A�j���[�V�����t���[���ƃ^�C�}�[
	bool m_Turn;			//�摜�̔��]�\��
public:
	CCharaBase(float _priority, CAST _id) : CObjectBase(_priority, _id)
	,m_Frame(0), m_Timer(0), m_Turn(false) {	};
	virtual ~CCharaBase() {};
	virtual void Update() {};
	virtual void Draw() const {};
};

#endif _CHARABASE_H_
