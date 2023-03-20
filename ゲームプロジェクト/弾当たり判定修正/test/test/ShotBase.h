//-----------------
//ShotBase.h
//-----------------
#ifndef _SHOTBASE_H_
#define _SHOTBASE_H_
#pragma once

//ヘッダーファイル
#include"CharaBase.h"

class CShotBase :public CCharaBase {
protected:
	float m_Speed;
	float m_IsRight;			//進む方向　右だと1.0　左だと-1.0
public:
	CShotBase(float _priority, CAST _id) : CCharaBase(_priority, _id),m_Speed(0.0f),m_IsRight(0.0f) {};
	virtual ~CShotBase() {};
	virtual void Update() {};
	virtual void Draw() const {};
};

#endif _CHARABASE_H_
