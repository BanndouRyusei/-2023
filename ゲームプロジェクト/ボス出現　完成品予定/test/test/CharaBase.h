//-----------------
//CharaBase.h
//-----------------
#ifndef _CHARABASE_H_
#define _CHARABASE_H_
#pragma once

//ヘッダーファイル
#include"ObjectBase.h"
#include"Shadow.h"
//定数

class CCharaBase :public CObjectBase {
protected:
	int m_Frame, m_Timer;		//アニメーションフレームとタイマー
	bool m_Turn;			//画像の反転表示
	int m_HP;		//キャラクターの体力
	CShadow m_Shadow;
	int m_ShadowImage;
	float m_Speed;
	VECTOR m_Temp;
	float m_ScrollX;
public:
	CCharaBase(float _priority, CAST _id) : CObjectBase(_priority, _id)
	,m_Frame(0), m_Timer(0), m_Turn(false),m_HP(0),m_Shadow(),m_ShadowImage(0) {};
	virtual ~CCharaBase() {};
	virtual void Update() {};
	virtual void Draw() const {};
};

#endif _CHARABASE_H_
