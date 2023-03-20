//-----------------
//Player.h
//-----------------
#ifndef _PLAYER_H_
#define _PLAYER_H_
#pragma once

//ヘッダーファイル
#include"CharaBase.h"

enum class e_PLAYERSTATE { NEUTRAL, WALK, JUMP, ATTACK, DAMAGE, DEATH, NONE };		//プレイヤーの状態
enum class e_PLAYERHITS { ITEM_RECOVERY, ITEM_POWERUP, ENEMYSHOT, NONE };		//プレイヤーにヒットするものの種類

//定数
//体力をHPとする
const int PLAYER_HP = 5;			//プレイヤーの体力
const int PLAYER_ANIM = 4;		//プレイヤーのアニメーション枚数

class CControlPlayer :public CTask {
private:
	int m_Life;			//プレイヤーの残機
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
	bool m_ShotFlag;			//弾を撃ったかどうかのフラグ　true 撃った
	int m_Alpha;	
	float m_JumpPower;
	bool m_Inv;			//無敵状態かどうか　true 無敵状態
	int m_InvTimer;			//無敵時間
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