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
//数字の画像のサイズ
const int SCORE_DIGI_W = 40;
const int SCORE_DIGI_H = 40;
//プレイヤースコアの表示位置
const int PLAYER_SCORE_RIGHT = 500;
const int PLAYER_SCORE_TOP = 550;
//ランキングスコアの表示位置
const int RANK_SCORE_RIGHT = 500;
const int RANK_SCORE_TOP = 200;
const int RANK_SCORE_SPECE = 90;			//ランキングスコアの間隔
const int MIN_DIGIT = 6;			//表示する0の数

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
