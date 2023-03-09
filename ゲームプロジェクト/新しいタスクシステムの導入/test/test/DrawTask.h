#pragma once
#include <functional>

class Task;
class TaskManager;

class DrawTask
{
	friend TaskManager;

private:
	DrawTask* m_prev;		//前のタスクへのポインタ
	DrawTask* m_next;		//次のタスクへのポインタ
	float m_priority;		//優先度(値が小さいほど先に描画)

	Task* m_task;
	std::function<void()> m_func;

public:
	//コンストラクタ
	DrawTask();
	//デストラクタ
	~DrawTask();
	void Init(Task* task, std::function<void()> _func, float _priority);

	//優先度を設定
	void SetPriority(float prio);
	//優先度を取得
	float GetPriority() const;

	//描画処理
	void Draw();
};