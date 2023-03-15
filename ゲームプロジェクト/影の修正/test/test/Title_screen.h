//---------------
//Title_screen.h
//---------------
#ifndef _TITLE_SCREEN_H_
#define _TITLE_SCREEN_H_
#pragma once

//ヘッダーファイル
#include"myLib.h"
#include"screen.h"
#include"Sound.h"


//タイトルスクリーンクラス
class CTitleScreen : public CScreen
{
private:
	DWORD m_Timer;
public:
	CTitleScreen();
	~CTitleScreen();
	void Update();
	void Draw() const;
};

#endif _TITLE_SCREEN_H_