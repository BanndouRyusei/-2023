//-----------------
//Effect.h
//-----------------
#ifndef _EFFECT_H_
#define _EFFECT_H_
#pragma once

//�w�b�_�[�t�@�C��
#include"ObjectBase.h"

enum class e_EFFECTS { RECOVERY, POWERUP, NONE };			//�G�t�F�N�g�̎��

//�萔
const int EFFECT_ANIM = 12;			//�A�C�e���̃A�j���[�V��������

class CEffect :public CObjectBase {
private:
	e_EFFECTS m_Type;
	int m_Frame;
	int m_Timer;
	int m_Image[EFFECT_ANIM];
public:
	CEffect(float _priority, e_EFFECTS _type);
	~CEffect();
	void Update();
	void Draw() const;
	void AnimEffect();

};

#endif _EFFECT_H_
