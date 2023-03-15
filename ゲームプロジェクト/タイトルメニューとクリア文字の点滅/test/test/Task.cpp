#include"Task.h"
#include"TaskManager.h"

//コンストラクタ
CTask::CTask(float prio,CAST _id)
	:m_prev(nullptr)
	, m_next(nullptr)
	, m_priority(prio)
	, m_isActive(true)
	,m_id(_id)
	,m_guard(false)
{
	CTaskManager::Instance()->AddTask(this);

}

//デストラクタ
CTask::~CTask()
{
	CTaskManager::Instance()->RemoveTask(this);
}

//優先度を設定
void CTask::SetPriority(float prio)
{
	//新しい優先度に変更
	m_priority = prio;
	//タスクをリストから取り除き、再度リストに追加してやることで
	//新しい優先度の位置にタスクを配置
	CTaskManager::Instance()->RemoveTask(this);
	CTaskManager::Instance()->AddTask(this);
}

//優先度を取得
float CTask::GetPriority() const
{
	return m_priority;
}

//タスクを削除
void CTask::Delete()
{
	m_isActive = false;
}