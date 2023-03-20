//-----------------
//ShadowManager.h
//-----------------
#ifndef _SHADOWMANAGER_H_
#define _SHADOWMANAGER_H_
#pragma once

//ヘッダーファイル
#include"myLib.h"
#include"Shadow.h"

//定数

//丸影クラス
class CShadowManager : public CTask {
private:
	CDrawTask m_DrawTask;
	std::list<CShadow*> m_ShadowList;			//影を管理するリスト
	static CShadowManager* ms_Instance;			//このクラスにアクセスするためのインスタンス
public:
	CShadowManager(float _priority = 0.2f);
	~CShadowManager();
	void Update();			//影のリストに登録されているアップデートを実行
	void Draw()const;		//影のリストに登録されているDrawを実行
	bool Regist(CShadow* _shadow);		//影のリストに追加
	bool Remove(CShadow* _shadow);		//影のリストから解除
	void InitShadowList();		//影のリストを空にする
	static CShadowManager* GetInstance();		//このクラスのインスタンスを取得
};

#endif _SHADOWMANAGER_H_

