//-----------------
//ObjectBase.h
//-----------------
#ifndef _OBJECTBASE_H_
#define _OBJECTBASE_H_
#pragma once

//ヘッダーファイル
#include"myLib.h"

//定数
const int ANIM_TIME = MAX_FPS / 3;			//アニメーションのフレーム更新時間

class CObjectBase :public CTask {
protected:
	CDrawTask m_DrawTask;
	VECTOR m_Pos;
public:
	 CObjectBase(float _priority,CAST _id) : CTask(_priority, _id), m_DrawTask()
		, m_Pos(VGet(0.0f, 0.0f, 0.0f)){
		 m_DrawTask.Init(this, std::bind(&CObjectBase::Draw, this), OBJECT_DRAWPRIORITY_MIN);
	 };
	virtual ~CObjectBase() {};
	virtual void Update() {};
	virtual void Draw() const {};
};

#endif _OBJECTBASE_H_

