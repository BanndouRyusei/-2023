//-----------------------
//game_screen.h
//-----------------------
#ifndef _GAME_SCREEN_H_
#define _GAME_SCREEN_H_
#pragma once

//ヘッダーファイル
#include"Task.h"
#include"myLib.h"
#include"screen.h"
#include"Sound.h"

enum OPTIPN { ANTI };

//ゲームスクリーンクラス
class CGameScreen :public CScreen
{
private:
	DWORD m_timer;
public:
	CGameScreen();
	~CGameScreen();
	void Update();
	void Draw() const;
};


#endif _GAME_SCREEN_H_