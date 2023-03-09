#pragma once

class TaskManager;

//タスクの識別子
enum class CAST
{
	PLAYER, ENEMY, CONTROLSOUND, BGM, SE , NONE //タスクを作る事に、識別子をここに登録する
};

class Task 
{
	friend TaskManager;

private:
	Task* m_prev;		//前のタスクへのポインタ
	Task* m_next;		//次のタスクへのポインタ
	float m_priority;		//優先度(値が小さいほど先に更新)
	bool m_isActive;		//タスクの生死
	CAST m_id;			//タスク識別子
	bool m_guard;		//タスクが死なないようにする変数		true(消さない)
public:
	//コンストラクタ
	Task(float prio,CAST _id);
	//デストラクタ
	virtual ~Task();

	//優先度を設定
	void SetPriority(float prio);
	//優先度を取得
	float GetPriority() const;
	//死なないようにする変数を設定
	void IsGuardFlg(const bool _isGuard)
	{
		m_guard = _isGuard;
	}
	//タスクを削除
	void Delete();
	//更新処理
	virtual void Update() = 0;
};