#pragma once
#include"Task.h"
#include"DrawTask.h"

class TaskManager
{
private:
	static TaskManager* ms_instance;		//TaskManagerのインスタンス
	Task* m_Uhead;		//先頭タスクのポインタ　更新用
	DrawTask* m_Dhead;		//先頭タスクのポインタ　描画用

public:
	//コンストラクタ
	TaskManager();
	//デストラクタ
	~TaskManager();

	//TaskManagerのインスタンスを取得
	static TaskManager* Instance();
	//TaskManagerのインスタンスを破棄　タスクシステムの初期化に使える
	static void ClearInstance();

	//リストにタスクを追加　更新用
	void AddTask(Task* task);
	//リストにタスクを追加　描画用
	void AddTask(DrawTask* task);
	//リストからタスクを取り除く　更新用
	void RemoveTask(Task* task);
	//リストからタスクを取り除く　描画用
	void RemoveTask(DrawTask* task);
	//タスクを削除する　更新用
	void DeleteTask(Task* task);
	//タスクを削除する　描画用
	void DeleteTask(DrawTask* task);
	//死んでいるタスクを削除する
	void DeleteDeathTask();
	//指定したグループのタスク数を返す
	int GetCount(CAST _id);
	//指定したidを持ち、指定した番号のタスクを返す
	void* GetTask(CAST _id, int _number = 0);
	//ガードしているタスク以外のタスクを消す
	void GuardKillTask();
	//DrawTaskを優先度順に並び変える
	void DrawSort();

	//更新処理
	void Update();

	//描画処理
	void Draw();
};