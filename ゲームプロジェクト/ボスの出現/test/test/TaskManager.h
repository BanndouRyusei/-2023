#pragma once
#include"Task.h"
#include"DrawTask.h"

class CTaskManager
{
private:
	static CTaskManager* ms_instance;		//CTaskManagerのインスタンス
	CTask* m_Uhead;		//先頭タスクのポインタ　更新用
	CDrawTask* m_Dhead;		//先頭タスクのポインタ　描画用

public:
	//コンストラクタ
	CTaskManager();
	//デストラクタ
	~CTaskManager();

	//CTaskManagerのインスタンスを取得
	static CTaskManager* Instance();
	//CTaskManagerのインスタンスを破棄　タスクシステムの初期化に使える
	static void ClearInstance();

	//リストにタスクを追加　更新用
	void AddTask(CTask* task);
	//リストにタスクを追加　描画用
	void AddTask(CDrawTask* task);
	//リストからタスクを取り除く　更新用
	void RemoveTask(CTask* task);
	//リストからタスクを取り除く　描画用
	void RemoveTask(CDrawTask* task);
	//タスクを削除する　更新用
	void DeleteTask(CTask* task);
	//タスクを削除する　描画用
	void DeleteTask(CDrawTask* task);
	//死んでいるタスクを削除する
	void DeleteDeathTask();
	//指定したグループのタスク数を返す
	int GetCount(CAST _id);
	//指定したグループのタスクを削除
	void EraseTask(CAST id);
	//指定したidを持ち、指定した番号のタスクを返す
	void* GetTask(CAST _id, int _number = 0);
	//ガードしているタスク以外のタスクを消す
	void GuardKillTask();
	//CDrawTaskを優先度順に並び変える
	void DrawSort();

	//更新処理
	void Update();

	//描画処理
	void Draw();
};