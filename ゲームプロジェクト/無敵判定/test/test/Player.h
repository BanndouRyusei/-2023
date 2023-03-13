//-----------------
//Player.h
//-----------------
#ifndef _PLAYER_H_
#define _PLAYER_H_
#pragma once

//�w�b�_�[�t�@�C��
#include"CharaBase.h"

enum class e_PLAYERPHASE { STATE, PLAY, END, NONE };		//�R���g���[���v���C���[�̏��
enum class e_PLAYERSTATE { NEUTRAL, WALK, JUMP, ATTACK, DAMAGE, DEATH, NONE };		//�v���C���[�̏��
enum class e_PLAYERHITS { ENEMYSHOT, ITEM_RECOVERY, ITEM_POWERUP, NONE };			//�v���C���[�Ƀq�b�g������̂̎��

//�萔
//�c�@��LIFE�@�̗͂�HP�Ƃ���
const int PLAYER_LIFE = 3;		//�v���C���[�̎c�@
const int PLAYER_HP = 5;			//�v���C���[�̗̑�
//const int PLAYER_ANIM[(int)e_PLAYERSTATE::NONE] = { 4,4,4,4,4,4 };			//�v���C���[�̊e�A�j���[�V��������
const int PLAYER_ANIM = 4;		//�v���C���[�̃A�j���[�V��������
const int PLAYER_ATTACKFLAME = 2;			//�v���C���[�̍U���t���[��
//�v���C���[�摜�̑傫��
const int PLAYER_H = 200;
const int PLAYER_W = 200;
//�v���C���[�̈ړ��\�ʒuX
const float PLAYER_X_MAX = WINDOW_W / 2 - PLAYER_W;

class CControlPlayer :public CTask {
private:
	int m_LIFE;			//�v���C���[�̎c�@
	e_PLAYERPHASE m_Phase;	
public:
	CControlPlayer(float _priority);
	~CControlPlayer();
	void Update();
	void CreatePlayer();
};

class CPlayer :public CCharaBase {
private:
	int m_HP;
	int m_AnimImage[(int)e_PLAYERSTATE::NONE][PLAYER_ANIM];
	e_PLAYERSTATE m_NowState;
	float m_Speed;
	bool m_ShotFlag;			//�e�����������ǂ����̃t���O�@true ������
	int m_Alpha;	
	float m_JumpPower;
	bool m_Inv;			//���G��Ԃ��ǂ����@true ���G���
	int m_InvTimer;			//���G����
	bool m_DrawFlag;
public:
	CPlayer(float _priority);
	~CPlayer();
	void Update();
	void Draw() const;
	void MovePlayer(int _key);
	void ShotPlayer(int _key);
	void AnimPlayer();
	void HitCheck(e_PLAYERHITS _hits);
	void PlayerDeth();
	void PlayerJump(int _key);
	void PlayerJumping();
	void BlinkPlayer();
};

#endif _PLAYER_H_