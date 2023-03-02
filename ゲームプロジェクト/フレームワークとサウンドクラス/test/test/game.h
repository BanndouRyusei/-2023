//-----------------
//game.h
//-----------------
#ifndef _GAME_H_
#define _GAME_H_
#pragma once

//ヘッダーファイル
#include"myLib.h"
#include"Title_screen.h"
#include"Clear_Screen.h"
#include"game_screen.h"
#include"screen.h"
#include"Sound.h"

//プロトタイプ
enum SCREEN;
class CScreen;

//ゲームクラス
class CGame
{
public:
	CGame();
	~CGame();
	void Update();
	void Draw();
private:
	CScreen*	m_pScreen;	//現在のスクリーンクラスのポインタ
	SCREEN		m_now_screen;	//画面情報
};

#endif _GAME_H_

