//---------------
//Clear.h
//---------------
#ifndef _CLEAR_
#define _CLEAR_
#pragma once

//ヘッダーファイル
#include"myLib.h"

//定数
const int RANK = 3;			//表示するランキング数

//クリア画面クラス
class CClear : public CTask
{
private:
	CDrawTask m_DrawTask;
	PHASE m_Phase;
	DWORD	m_Timer;
	int m_Alpha;
	int m_CharAlpha;
	int m_AlphaTurn;
	int m_PlayerScore;
	int m_RankScore[RANK];
	int m_Image;
	int m_CharImage;
	int m_Digits[DIGITS];
public:
	CClear(float _priority);
	~CClear();
	void Update();
	void Draw() const;
	void LoadScore();
	void SaveScore();
	void SortScore();
};

#endif _CLEAR_
