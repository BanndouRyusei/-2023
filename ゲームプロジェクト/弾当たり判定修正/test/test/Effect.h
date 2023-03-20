//-----------------
//Effect.h
//-----------------
#ifndef _EFFECT_H_
#define _EFFECT_H_
#pragma once

//ヘッダーファイル
#include"ObjectBase.h"

enum class e_EFFECTS { RECOVERY, POWERUP, NONE };			//エフェクトの種類

//定数
const int EFFECT_ANIM = 12;			//アイテムのアニメーション枚数

class CEffect :public CObjectBase {
private:
	e_EFFECTS m_Type;
	int m_Frame;
	int m_Timer;
	int m_Image[EFFECT_ANIM];
public:
	CEffect(float _priority, e_EFFECTS _type);
	~CEffect();
	void Update();
	void Draw() const;
	void AnimEffect();

};

#endif _EFFECT_H_
