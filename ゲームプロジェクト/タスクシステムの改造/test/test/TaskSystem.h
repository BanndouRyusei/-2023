//-----------------
//TaskSystem.h
//-----------------
#ifndef _TASKSYSTEM_H_
#define _TASKSTSTEM_H_
#pragma once

//�w�b�_�[�t�@�C��
#include "Dxlib.h"
#include "mylib.h"
#include <algorithm>


//�^�X�N�̎��ʎq
enum class CAST
{
	CONTROLSOUND,SE, BGM, NONE	//�^�X�N����鎖�ɁA���ʎq�������ɓo�^����
};

//�^�X�N�N���X
//�^�X�N�V�X�e���̌��ɂȂ�N���X
class Task
{
protected:
	VECTOR m_pos;		//3D���W
public:
	float	m_priority;	//�X�V�D��x
	float m_DrawPriority;		//�`��D��x
	bool	m_isActive;	//�^�X�N�̐����@true=�� false=��
	CAST	m_id;		//�O���[�v���ʎq
	bool m_guard;		//�^�X�N�����ȂȂ��悤�ɂ��邽�߂̎��ʎq

	Task() : m_priority(0),m_DrawPriority(0), m_isActive(false), m_id(CAST::NONE), m_guard(false),m_pos(VGet(0.0f,0.0f,0.0f)){}
	virtual ~Task() {}
	virtual void Update() {}			//�^�X�N�̍X�V����
	virtual void Draw() const {}		//�^�X�N�̕`��
	virtual void Deth() {}		//�f�X�g���N�^�ł��鏈�������s����֐�(MV1DeleteModel�Ȃ�)�^�X�N�̃f�X�g���N�^�������Ȃ�����
};

//�e�N���X����������o�����߂̍\����
struct DATA
{
	VECTOR pos;
};

#endif _TASKSTSTEM_H_