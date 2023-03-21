//-----------------
//Item.h
//-----------------
#ifndef _ITEM_H_
#define _ITEM_H_
#pragma once

//ヘッダーファイル
#include"ObjectBase.h"
#include"Player.h"
#include"Shadow.h"

//定数
const int ITEM_ANIM = 4;			//アイテムのアニメーション枚数

class CItem :public CObjectBase {
private:
	float m_Scroll;
	e_PLAYERHITS m_Type;
	int m_Frame;
	int m_Timer;
	int m_Image[ITEM_ANIM];
	CShadow m_Shadow;
	int m_ShadowImage;
public:
	CItem(float _priority,const VECTOR _pos);
	~CItem();
	void Update();
	void Draw() const;
	void AnimItem();
	void HitCheck();
	void PosCheck();
	void MoveItem();
};

#endif _ITEM_H_
