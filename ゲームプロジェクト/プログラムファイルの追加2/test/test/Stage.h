//-----------------
//Stage.h
//-----------------
#ifndef _STAGE_H_
#define _STAGE_H_
#pragma once

//ヘッダーファイル
#include"myLib.h"

enum class e_STAGES { BACK, FRONT, GROUND, NONE };

//定数
//背景画像の大きさ
const float STAGE_H = 400.0f;
const float STAGE_W = 960.0f;
//地面画像の大きさ
const float GROUND_H = 200.0f;
//画面の一回のスクロール量
const float STAGE_SCROLLX = 2.0f;

class CStage :public CTask {
private:
	CDrawTask m_DrawTask;
	float m_Cx[(int)e_STAGES::NONE];			//各画像の表示座標(X)
	int m_Image[(int)e_STAGES::NONE];	
	float m_ScrollX;			//スクロール量を記録する変数
public:
	CStage(float _priority = 0.5f);
	~CStage();
	void Update();
	void Draw() const;
	float GetScrollX();
	void MoveScrollX();
};

#endif _STAGE_H_