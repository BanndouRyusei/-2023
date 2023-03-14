//-----------------
//sound.h
//-----------------
#ifndef _UI_H_
#define _UI_H_
#pragma once

//ヘッダーファイル
#include"myLib.h"

// 定数
const int UI_CHIPSIZE = 10;

//-------- UI ----------
class CUI : public CTask {
private:
	CDrawTask m_DrawTask;
	int m_Back;
	int m_Wipe;
public:
	CUI(float _priority);
	~CUI();
	void Update();
	void Draw() const;
};

//-------- HP ----------
class CHP : public CTask {
private:
	CDrawTask m_DrawTask;
	int m_HP;
	int m_HPImage;
	int m_HPBar;
public:
	CHP(float _priority);
	~CHP();
	void Update();
	void Draw() const;
	void SetPlayerHp(const int _hp);
};

//-------- Life ----------
class CLife : public CTask {
private:
	CDrawTask m_DrawTask;
	int m_Life;
	int m_LifeImage;
	int m_LifeBar;
public:
	CLife(float _priority);
	~CLife();
	void Update();
	void Draw() const;
	void SetPlayerLife(const int _life);
};

//-------- Time ----------
class CTime : public CTask {
private:
	const int WIDTH = 10;
	const int HEIGHT = 1;
	const int CHIPSIZE = 40;
	int m_TimeImage[10];

	CDrawTask m_DrawTask;
	int m_Time;
	int m_StartTime;
	int m_OneDigit;
	int m_TwoDigit;
	int m_ThreeDigit;
	int m_FourDigit;
public:
	CTime(float _priority);
	~CTime();
	void Update();
	void Draw() const;
	void m_GetDigits(int _num);	// 各桁の数字を取り出す
};

//-------- Score ----------
class CScore : public CTask {
private:
	const int WIDTH = 10;
	const int HEIGHT = 1;
	const int CHIPSIZE = 40;
	int m_TimeImage[10];


	CDrawTask m_DrawTask;
	int m_Score;
public:
	CScore(float _priority);
	~CScore();
	void Update();
	void Draw() const;
};

#endif _UI_H_