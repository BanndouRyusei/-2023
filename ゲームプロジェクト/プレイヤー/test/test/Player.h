//-----------------
//Player.h
//-----------------
#ifndef _PLAYER_H_
#define _PLAYER_H_
#pragma once

//�w�b�_�[�t�@�C��
#include"myLib.h"

enum class e_PLAYERPHASE { STATE, PLAY, END, NONE };		//�R���g���[���v���C���[�̏��
enum class e_PLAYERSTATE { NEUTRAL, WALK, JUMP, ATTACK, DAMAGE, DEATH, NONE };		//�v���C���[�̏��

//�萔
const int PLAYER_LIFE = 3;		//�v���C���[�̎c�@
const int PLAYER_HP = 5;			//�v���C���[�̗̑�
//const int PLAYER_ANIM[(int)e_PLAYERSTATE::NONE] = { 4,4,4,4,4,4 };			//�v���C���[�̊e�A�j���[�V��������
const int PLAYER_ANIM = 4;		//�v���C���[�̃A�j���[�V��������
//�v���C���[�摜�̑傫��
const int PLAYER_H = 200;
const int PLAYER_W = 200;
//�v���C���[�̈ړ��\�ʒuX
const float PLAYER_X_MAX = WINDOW_W / 2 - PLAYER_W;

class CControlPlayer :public Task {
private:
	int m_LIFE;
	e_PLAYERPHASE m_Phase;
public:
	CControlPlayer(float _priority);
	~CControlPlayer();
	void Update();
	void CreatePlayer();
};

class CPlayer :public Task {
private:
	DrawTask m_drawTask;
	VECTOR m_Pos;
	int m_HP;
	int m_AnimImage[(int)e_PLAYERSTATE::NONE][PLAYER_ANIM];
	e_PLAYERSTATE m_Phase;
	float m_Speed;
public:
	CPlayer(float _priority);
	~CPlayer();
	void Update();
	void Draw() const;
	void MovePlayer();
};

#endif _PLAYER_H_