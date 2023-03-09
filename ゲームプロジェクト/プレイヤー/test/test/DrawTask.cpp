#include"DrawTask.h"
#include"TaskManager.h"
#include"Task.h"

//コンストラクタ
DrawTask::DrawTask()
	: m_prev(nullptr)
	, m_next(nullptr)
	, m_priority(0.0f)
	,m_task(nullptr)
	,m_func(nullptr)
{
}

//デストラクタ
DrawTask::~DrawTask()
{
	TaskManager::Instance()->RemoveTask(this);

	m_prev = nullptr;
	m_next = nullptr;
	m_priority = 0.0f;
	m_task = nullptr;
	m_func = nullptr;
}

//初期化
void DrawTask::Init(Task* task, std::function<void()> _func, float _priority) 
{
	m_prev = nullptr;
	m_next = nullptr;
	m_priority = _priority;
	m_task = task;
	m_func = _func;
	TaskManager::Instance()->AddTask(this);
}

//優先度を設定
void DrawTask::SetPriority(float prio)
{
	//新しい優先度に変更
	m_priority = prio;
	//タスクをリストから取り除き、再度リストに追加してやることで
	//新しい優先度の位置にタスクを配置
	TaskManager::Instance()->RemoveTask(this);
	TaskManager::Instance()->AddTask(this);
}

//優先度を取得
float DrawTask::GetPriority() const
{
	return m_priority;
}

//描画処理
void DrawTask::Draw()
{
	if (m_task == nullptr) return;
	if (m_func == nullptr) return;

	m_func();
}