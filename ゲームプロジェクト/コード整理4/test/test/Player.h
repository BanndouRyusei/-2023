//-----------------
//Player.h
//-----------------
#ifndef _PLAYER_H_
#define _PLAYER_H_
#pragma once

//�w�b�_�[�t�@�C��
#include"CharaBase.h"

enum class e_PLAYERSTATE { NEUTRAL, WALK, JUMP, ATTACK, DAMAGE, DEATH, NONE };		//�v���C���[�̏��
enum class e_PLAYERHITS { ITEM_RECOVERY, ITEM_POWERUP, ENEMYSHOT, NONE };		//�v���C���[�Ƀq�b�g������̂̎��

//�萔
//�̗͂�HP�Ƃ���
const int PLAYER_HP = 5;			//�v���C���[�̗̑�
const int PLAYER_ANIM = 4;		//�v���C���[�̃A�j���[�V��������

class CControlPlayer :public CTask {
private:
	int m_Life;			//�v���C���[�̎c�@
	PHASE m_Phase;	
public:
	CControlPlayer(float _priority);
	~CControlPlayer();
	void Update();
	void CreatePlayer();
};

class CPlayer :public CCharaBase {
private:
	int m_AnimImage[(int)e_PLAYERSTATE::NONE][PLAYER_ANIM];
	e_PLAYERSTATE m_NowState;
	float m_Speed;
	int m_Power;
	float m_PowerUpTimer;
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
	void AnimPlayer();
	bool HitCheck(const VECTOR &_pos,float _zwidth ,int _ghandle, e_PLAYERHITS _hits);
	void PlayerDeth();
	void PlayerJumping();
	void BlinkPlayer();
	float GetHP();
	const VECTOR& GetPos();
	bool GetPower();
};

#endif _PLAYER_H_