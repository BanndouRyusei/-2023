//-----------------
//CharaBase.h
//-----------------
#ifndef _CHARABASE_H_
#define _CHARABASE_H_
#pragma once

//ヘッダーファイル
#include"ObjectBase.h"
//定数

class CCharaBase :public CObjectBase {
protected:
	int m_Frame, m_Timer;		//アニメーションフレームとタイマー
	bool m_Turn;			//画像の反転表示
public:
	CCharaBase(float _priority, CAST _id) : CObjectBase(_priority, _id)
	,m_Frame(0), m_Timer(0), m_Turn(false) {	};
	virtual ~CCharaBase() {};
	virtual void Update() {};
	virtual void Draw() const {};
};

#endif _CHARABASE_H_
