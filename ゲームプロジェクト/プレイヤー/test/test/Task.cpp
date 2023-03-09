#include"Task.h"
#include"TaskManager.h"

//コンストラクタ
Task::Task(float prio,CAST _id)
	:m_prev(nullptr)
	, m_next(nullptr)
	, m_priority(prio)
	, m_isActive(true)
	,m_id(_id)
	,m_guard(false)
{
	TaskManager::Instance()->AddTask(this);

}

//デストラクタ
Task::~Task()
{
	TaskManager::Instance()->RemoveTask(this);
}

//優先度を設定
void Task::SetPriority(float prio)
{
	//新しい優先度に変更
	m_priority = prio;
	//タスクをリストから取り除き、再度リストに追加してやることで
	//新しい優先度の位置にタスクを配置
	TaskManager::Instance()->RemoveTask(this);
	TaskManager::Instance()->AddTask(this);
}

//優先度を取得
float Task::GetPriority() const
{
	return m_priority;
}

//タスクを削除
void Task::Delete()
{
	m_isActive = false;
}