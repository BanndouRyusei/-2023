//----------
//Enemy.h
//----------
#pragma once
#ifndef __ENEMY_H__
#define __ENEMY_H__

//ヘッダーファイル
#include "myLib.h"

const int ENEMY_ANIM = 4;     //エネミーのアニメーション枚数

//エネミーの種類
enum class EnemyType
{
	ZAKO_A,ZAKO_B,BOSS
};

enum class e_ENEMYSTATE { NEUTRAL, ATTACK, DAMAGE, DEATH, NONE };  //敵の状態

class CEnemyZakoA:public CTask
{
private:
	CDrawTask m_DrawTask;
	VECTOR m_Pos;
	int m_HP;
	int m_AnimImage[(int)e_ENEMYSTATE::NONE][ENEMY_ANIM];
	e_ENEMYSTATE m_Phase;
	float m_Speed;
public:
	CEnemyZakoA(float _ex,float _ez,float _speed,float _priority);
	~CEnemyZakoA();
	void Update();
	void Draw()const;
	bool HitCheck(const VECTOR &_pos, float _zwidth, int _ghandle);
};

class CControlZakoA :public CTask
{
	BYTE m_MaxEnemy;
	DWORD m_Timer;
	int m_EnemyCount;
public:
	CControlZakoA(BYTE _MaxEnemy, float _priority);
	~CControlZakoA();
	void Update();

};

class CEnemyZakoB:public CTask
{
private:
	CDrawTask m_DrawTask;
	VECTOR m_Pos;
	int m_HP;
	int m_AnimImage[(int)e_ENEMYSTATE::NONE][ENEMY_ANIM];
	e_ENEMYSTATE m_Phase;
public:
	CEnemyZakoB(float _priority);
	~CEnemyZakoB();
	void Update();
	void Draw()const;
};

class CControlZakoB :public CTask
{
	BYTE m_MaxEnemy;
	DWORD m_Timer;
	int m_EnemyCount;
public:
	CControlZakoB(BYTE _MaxEnemy, float _priority);
	~CControlZakoB();
	void Update();
};

class CEnemyBoss:public CTask
{
private:
	CDrawTask m_DrawTask;
	VECTOR m_Pos;
	int m_HP;
	int m_AnimImage[(int)e_ENEMYSTATE::NONE][ENEMY_ANIM];
	e_ENEMYSTATE m_Phase;
public:
	CEnemyBoss(float _priority);
	~CEnemyBoss();
	void Update();
	void Draw()const;
};

class CControlBoss :public CTask
{
	BYTE m_MaxEnemy;
	DWORD m_Timer;
	int m_EnemyCount;
public:
	CControlBoss(BYTE _MaxEnemy, float _priority);
	~CControlBoss();
	void Update();
};

#endif   __ENEMY_H__