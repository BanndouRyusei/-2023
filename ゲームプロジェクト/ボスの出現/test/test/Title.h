//---------------
//Title.h
//---------------
#ifndef _TITLE_
#define _TITLE_
#pragma once

//ヘッダーファイル
#include"myLib.h"

//定数
const int TITLE_MENU = 2;			//タイトルメニュー数
const int MENU_MAX = TITLE_MENU - 1;
const int MENU_MIN = 0;
//タイトルメニューの表示位置
const int TITLE_MENU_X = 335;
const int TITLE_MENU_Y = 600;
const int TITLE_MENU_SPECE = 60;		//メニューの間の間隔
const int TITLE_CORSOR_SIZE = 60;		//タイトルカーソルの画像サイズ
const int TITLE_MENU_ALPHA_STEP = 5;			//選ばれているメニューの点滅に足すALPHA_STEP
const int TITLE_MENU_ALPHA_MIN = 50;			//メニュー点滅のALPHA最小値

//タイトル（背景）クラス
class CTitle : public CTask
{
private:
	CDrawTask m_DrawTask;
	int m_Image;
	DWORD	m_Timer;
	PHASE m_Phase;
	int m_Alpha;
public:
	CTitle(float _priority);
	~CTitle();
	void Update();
	void Draw() const;
};

//タイトル画面用メニュークラス
class CTitleMenu :public CTask {
private:
	CDrawTask m_DrawTask;
	int m_Item;
	int m_SelectMenu;
	int m_Alpha;
	int m_AlphaTurn;
	bool	m_IsDecide;		//決定キーが押されたかどうか
	int m_MenuImage[TITLE_MENU];
	int m_CusorImage;
public:
	CTitleMenu(float _priority);
	~CTitleMenu();
	void Update();
	void Draw() const;
};

#endif _TITLE_
