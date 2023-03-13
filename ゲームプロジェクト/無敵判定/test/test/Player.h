//-----------------
//Player.h
//-----------------
#ifndef _PLAYER_H_
#define _PLAYER_H_
#pragma once

//ヘッダーファイル
#include"CharaBase.h"

enum class e_PLAYERPHASE { STATE, PLAY, END, NONE };		//コントロールプレイヤーの状態
enum class e_PLAYERSTATE { NEUTRAL, WALK, JUMP, ATTACK, DAMAGE, DEATH, NONE };		//プレイヤーの状態
enum class e_PLAYERHITS { ENEMYSHOT, ITEM_RECOVERY, ITEM_POWERUP, NONE };			//プレイヤーにヒットするものの種類

//定数
//残機をLIFE　体力をHPとする
const int PLAYER_LIFE = 3;		//プレイヤーの残機
const int PLAYER_HP = 5;			//プレイヤーの体力
//const int PLAYER_ANIM[(int)e_PLAYERSTATE::NONE] = { 4,4,4,4,4,4 };			//プレイヤーの各アニメーション枚数
const int PLAYER_ANIM = 4;		//プレイヤーのアニメーション枚数
const int PLAYER_ATTACKFLAME = 2;			//プレイヤーの攻撃フレーム
//プレイヤー画像の大きさ
const int PLAYER_H = 200;
const int PLAYER_W = 200;
//プレイヤーの移動可能位置X
const float PLAYER_X_MAX = WINDOW_W / 2 - PLAYER_W;

class CControlPlayer :public CTask {
private:
	int m_LIFE;			//プレイヤーの残機
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
	void ShotPlayer(int _key);
	void AnimPlayer();
	void HitCheck(e_PLAYERHITS _hits);
	void PlayerDeth();
	void PlayerJump(int _key);
	void PlayerJumping();
	void BlinkPlayer();
};

#endif _PLAYER_H_