#include"DrawTask.h"
#include"TaskManager.h"
#include"Task.h"

//コンストラクタ
CDrawTask::CDrawTask()
	: m_prev(nullptr)
	, m_next(nullptr)
	, m_priority(0.0f)
	,m_task(nullptr)
	,m_func(nullptr)
{
}

//デストラクタ
CDrawTask::~CDrawTask()
{
	CTaskManager::Instance()->RemoveTask(this);

	m_prev = nullptr;
	m_next = nullptr;
	m_priority = 0.0f;
	m_task = nullptr;
	m_func = nullptr;
}

//初期化
void CDrawTask::Init(CTask* task, std::function<void()> _func, float _priority) 
{
	m_prev = nullptr;
	m_next = nullptr;
	m_priority = _priority;
	m_task = task;
	m_func = _func;
	CTaskManager::Instance()->AddTask(this);
}

//優先度を設定
void CDrawTask::SetPriority(float prio)
{
	//新しい優先度に変更
	m_priority = prio;
	//タスクをリストから取り除き、再度リストに追加してやることで
	//新しい優先度の位置にタスクを配置
	CTaskManager::Instance()->RemoveTask(this);
	CTaskManager::Instance()->AddTask(this);
}

//優先度を取得
float CDrawTask::GetPriority() const
{
	return m_priority;
}

//描画処理
void CDrawTask::Draw()
{
	if (m_task == nullptr) return;
	if (m_func == nullptr) return;

	m_func();
}