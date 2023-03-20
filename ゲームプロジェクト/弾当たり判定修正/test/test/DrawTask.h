#pragma once
#include <functional>

class CTask;
class CTaskManager;

class CDrawTask
{
	friend CTaskManager;

private:
	CDrawTask* m_prev;		//前のタスクへのポインタ
	CDrawTask* m_next;		//次のタスクへのポインタ
	float m_priority;		//優先度(値が小さいほど先に描画)

	CTask* m_task;
	std::function<void()> m_func;

public:
	//コンストラクタ
	CDrawTask();
	//デストラクタ
	~CDrawTask();
	void Init(CTask* task, std::function<void()> _func, float _priority);

	//優先度を設定
	void SetPriority(float prio);
	//優先度を取得
	float GetPriority() const;

	//描画処理
	void Draw();
};