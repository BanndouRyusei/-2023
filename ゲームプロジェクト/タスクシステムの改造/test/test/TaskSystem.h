//-----------------
//TaskSystem.h
//-----------------
#ifndef _TASKSYSTEM_H_
#define _TASKSTSTEM_H_
#pragma once

//ヘッダーファイル
#include "Dxlib.h"
#include "mylib.h"
#include <algorithm>


//タスクの識別子
enum class CAST
{
	CONTROLSOUND,SE, BGM, NONE	//タスクを作る事に、識別子をここに登録する
};

//タスククラス
//タスクシステムの元になるクラス
class Task
{
protected:
	VECTOR m_pos;		//3D座標
public:
	float	m_priority;	//更新優先度
	float m_DrawPriority;		//描画優先度
	bool	m_isActive;	//タスクの生死　true=生 false=死
	CAST	m_id;		//グループ識別子
	bool m_guard;		//タスクを死なないようにするための識別子

	Task() : m_priority(0),m_DrawPriority(0), m_isActive(false), m_id(CAST::NONE), m_guard(false),m_pos(VGet(0.0f,0.0f,0.0f)){}
	virtual ~Task() {}
	virtual void Update() {}			//タスクの更新処理
	virtual void Draw() const {}		//タスクの描画
	virtual void Deth() {}		//デストラクタでする処理を実行する関数(MV1DeleteModelなど)タスクのデストラクタが働かないため
};

//各クラスから情報を取り出すための構造体
struct DATA
{
	VECTOR pos;
};

#endif _TASKSTSTEM_H_