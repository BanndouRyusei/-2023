//-----------------
//Stage.h
//-----------------
#ifndef _STAGE_H_
#define _STAGE_H_
#pragma once

//�w�b�_�[�t�@�C��
#include"myLib.h"

enum class e_STAGES { BACK, FRONT, GROUND, NONE };

//�萔
//�w�i�摜�̑傫��
const float STAGE_H = 400.0f;
const float STAGE_W = 960.0f;
//�n�ʉ摜�̑傫��
const float GROUND_H = 200.0f;
//��ʂ̈��̃X�N���[����
const float STAGE_SCROLLX = 2.0f;

class CStage :public CTask {
private:
	CDrawTask m_DrawTask;
	float m_Cx[(int)e_STAGES::NONE];			//�e�摜�̕\�����W(X)
	int m_Image[(int)e_STAGES::NONE];	
	float m_ScrollX;			//�X�N���[���ʂ��L�^����ϐ�
public:
	CStage(float _priority = 0.5f);
	~CStage();
	void Update();
	void Draw() const;
	float GetScrollX();
	void MoveScrollX();
};

#endif _STAGE_H_