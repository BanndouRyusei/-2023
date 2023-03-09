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

class CStage :public Task {
private:
	DrawTask m_drawTask;
	float m_Cx[(int)e_STAGES::GROUND];
	int m_Image[(int)e_STAGES::NONE];
public:
	CStage(float _priority = 0.5f);
	~CStage();
	void Update();
	void Draw() const;
};

#endif _STAGE_H_