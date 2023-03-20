//-------------------------------
//Clear_screen.h
//-------------------------------
#ifndef _CLEAR_SCREEN_H
#define _CLEAR_SCREEN_H
#pragma once
//ヘッダーファイル
#include "mylib.h"
#include "screen.h"
#include"Sound.h"

//ゲームクリアスクリーンクラス
class CClearScreen :public CScreen
{
private:
	DWORD m_Timer;
public:
	CClearScreen();
	~CClearScreen();
	void Update();
	void Draw()const;

};

#endif  _CLEAR_SCREEN_H