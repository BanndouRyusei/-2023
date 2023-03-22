//----------
//Enemy.h
//----------
#pragma once
#ifndef __ENEMY_H__
#define __ENEMY_H__

//ヘッダーファイル
#include "CharaBase.h"

struct enemydata {
	int Type;
	VECTOR Pos;
};

const int ENEMY_ANIM = 4;     //エネミーのアニメーション枚数

//エネミーの種類
enum class EnemyType
{
	ZAKO_A=1,ZAKO_B,BOSS
};

enum class e_ENEMYSTATE { NEUTRAL, ATTACK, DAMAGE, DEATH, NONE };  //敵の状態
enum class e_ENEMYHITS { PLAYERSHOT, NONE };

class CControlEnemy :public CTask
{
private:
	int m_ScrollX;
	bool m_BossFlag;
public:
	FILE * fp;
	int enemynum;
	int EnemyNo;
	int m_EnemyNo = 0;
	float m_EnemyPosX = 0;
	enemydata temp;
	CControlEnemy(float _priority);
	~CControlEnemy();
	void Update();
	void LoadEnemy();
	void MakeBoss();
	list<enemydata>m_EnemyData;
};

class CZakoA:public CCharaBase
{
private:
	float m_ShotPosX;
	int m_AttackTimer;
	int m_Alpha;
	int m_AnimImage[(int)e_ENEMYSTATE::NONE][ENEMY_ANIM];
	e_ENEMYSTATE m_NowState;
	bool m_ShotFlag;
public:
	CZakoA(float _ex,float _ey,float _ez,float _priority);
	~CZakoA();
	void Update();
	void Draw()const;
	void AnimEnemy();
	void EnemyDeth();
	void CheckPos();
	bool HitCheck(const VECTOR &_pos, float _zwidth, int _ghandle);
};



class CZakoB:public CCharaBase
{
private:
	float m_ShotPosX;
	int m_AttackTimer;
	int m_Alpha;
	int m_AnimImage[(int)e_ENEMYSTATE::NONE][ENEMY_ANIM];
	e_ENEMYSTATE m_NowState;
	bool m_ShotFlag;
public:
	CZakoB(float _ex, float _ey, float _ez, float _priority);
	~CZakoB();
	void Update();
	void Draw()const;
	void AnimEnemy();
	void EnemyDeth();
	void CheckPos();
	bool HitCheck(const VECTOR &_pos, float _zwidth, int _ghandle);
};


class CBoss:public CCharaBase
{
private:
	float m_ShotPosX;
	int m_AttackTimer;
	int m_Alpha;
	int m_AnimImage[(int)e_ENEMYSTATE::NONE][ENEMY_ANIM];
	e_ENEMYSTATE m_NowState;
	bool m_ShotFlag;
	bool m_Inv;			//無敵状態かどうか　true 無敵状態
	int m_InvTimer;			//無敵時間
	bool m_DrawFlag;
public:
	CBoss(float _ex, float _ey, float _ez, float _priority);
	~CBoss();
	void Update();
	void Draw()const;
	void AnimEnemy();
	void EnemyDeth();
	bool HitCheck(const VECTOR &_pos, float _zwidth, int _ghandle);
	void BlinkBoss();
};

#endif   __ENEMY_H__