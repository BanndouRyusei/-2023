//-----------------
//sound.h
//-----------------
#ifndef _UI_H_
#define _UI_H_
#pragma once

//ヘッダーファイル
#include"myLib.h"

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
	CDrawTask m_DrawTask;
	int m_Time;
	int m_StartTime;

	int m_Digit;
	int m_DigitCount;
	int m_OneDgt;
	int m_TwoDgt;
	int m_ThreeDgt;
	int m_FourDgt;
	int m_NextPos;
public:
	int m_TimeImage[10];
	CTime(float _priority);
	~CTime();
	void Update();
	void Draw() const;
	void m_GetDigits(int _num);
};

//-------- Score ----------
class CScore : public CTask{
private:
	CDrawTask m_DrawTask;
	int m_Score;
	int m_ScoreImage[10];
public:
	CScore(float _priority);
	~CScore();
	void Update();
	void Draw() const;
	void Add(DWORD _score);
};

#endif _UI_H_