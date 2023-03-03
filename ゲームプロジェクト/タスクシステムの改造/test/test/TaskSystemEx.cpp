//-------------------------
//TaskSystemEx.cpp
//-------------------------
#include "TaskSystemEx.h"

//list<Task *>m_TaskList;
list<Task *>m_TaskList;		//更新用リスト
list<Task *>m_DrawTaskList;		//描画用リスト

//タスクの初期値を設定
TaskEx::TaskEx() {
	m_pos = VGet(0.0f, 0.0f, 0.0f);
	m_id = CAST::NONE;
	m_priority = 0.0f;
	m_DrawPriority = 0.0f;
	m_isActive = false;
	m_guard = false;
}

//タスクリストを空にする
TaskEx::~TaskEx() {
	InitTaskList();
}

//タスクリストの初期化
void TaskEx::InitTaskList(void) {
	//更新用のタスクリストを初期化
	if (!m_TaskList.empty()) {
		m_TaskList.clear();
	}
	//描画用のタスクリストを初期化
	if (!m_DrawTaskList.empty()) {
		m_DrawTaskList.clear();
	}
}

//タスクをタスクリストに追加する
//p_task:タスク
void TaskEx::AddTask(Task* _ptask)
{
	//更新用のタスクリストに追加
	auto it = m_TaskList.begin();
	Task* _task;
	for (; it != m_TaskList.end(); ++it) {
		_task = *it;
		//自分より大きいpriorityのタスクがあったら
		if (_task->m_priority > _ptask->m_priority)
			break;
	}
	m_TaskList.insert(it, _ptask);

	//描画用のタスクリストに追加
	it = m_DrawTaskList.begin();
	for (; it != m_DrawTaskList.end(); ++it) {
		_task = *it;
		//自分より大きいDrawPriorityのタスクがあったら
		if (_task->m_DrawPriority > _ptask->m_DrawPriority)
			break;
	}
	m_DrawTaskList.insert(it, _ptask);
}

//死亡したすべてのタスクを消去する
//タスクリスト操作中は、使用禁止
void TaskEx::DeleteDeathTask(void)
{
	Task* _task;
	//更新用のタスクリストから削除
	for (auto it = m_TaskList.begin(); it != m_TaskList.end();)
	{
		_task = *it;
		if (!_task->m_isActive)
		{
			it = m_TaskList.erase(it);
			continue;
		}
		it++;
	}
	//描画用のタスクリストから削除
	for (auto it = m_DrawTaskList.begin(); it != m_DrawTaskList.end();)
	{
		_task = *it;
		if (!_task->m_isActive)
		{
			it = m_DrawTaskList.erase(it);
			continue;
		}
		it++;
	}
}

//指定したグループ(id)のタスクを削除
//タスクリスト操作中は、使用禁止
//特殊攻撃で一網打尽に使用可能
void TaskEx::EraseTask(CAST _id) {
	Task* p_task;
	//更新用のタスクリストから削除
	for (auto it = m_TaskList.begin(); it != m_TaskList.end();)
	{
		 p_task = *it;
		if (p_task->m_id == _id) {
			it = m_TaskList.erase(it);
			continue;
		}
		it++;
	}
	//描画用のタスクリストから削除
	for (auto it = m_DrawTaskList.begin(); it != m_DrawTaskList.end();)
	{
		p_task = *it;
		if (p_task->m_id == _id) {
			it = m_DrawTaskList.erase(it);
			continue;
		}
		it++;
	}
}

//生きているすべてのタスクを実行（更新）する
void TaskEx::RunTask(void)
{
	for (auto task : m_TaskList) {
		if (task->m_isActive)task->Update();
	}
	TaskEx::UpdateDraw();
}

//生きているすべてのタスクを描画する
void TaskEx::DrawTask(void)
{
	for (auto task : m_DrawTaskList) {
		if (task->m_isActive)task->Draw();
	}
}

//指定したグループ(id)のタスクだけを描画する
void TaskEx::DrawTask(CAST _id) {
	for (auto task : m_DrawTaskList) {
		if (task->m_id == _id)task->Draw();
	}
}

//指定したグループ(id)のタスク数を返す
DWORD TaskEx::GetCount(CAST _id) {
	DWORD count = 0;
	for (auto task : m_TaskList)
	{
		if (task->m_id == _id)count++;
	}
	return count;
}

//指定したグループ(id)を持ち、指定した番号のタスクを返す
//同じグループ(id)のものが複数いる場合は、number=0から付番されている
void* TaskEx::GetTask(CAST _id, DWORD _number) {
	int count = 0;
	for (auto task : m_TaskList) {
		if (task->m_id == _id && count++ == _number)return task;
	}
	return nullptr;
}

//自分のデータを取得
void TaskEx::GetData(DATA* _pdata)const {

	if (!_pdata)return;

	_pdata->pos = m_pos;
}

//生きているタスクのデストラクタで行う処理をする
void TaskEx::GuardDethTask(void) {
	for (auto task : m_TaskList) {
		if (task->m_isActive)task->Deth();
	}
}

//ガードされているタスク以外のデストラクタで行う処理をする
void TaskEx::DethTask(void) {
	for (auto task : m_TaskList) {
		if (task->m_isActive&&!(task->m_guard))task->Deth();
	}
}

//描画タスクリストを描画優先度順に並び変える
void TaskEx::UpdateDraw(void) {
	//一旦描画用タスクリストからすべて解除
	if (!m_DrawTaskList.empty()) {
		m_DrawTaskList.clear();
	}
	//更新用タスクリストにクラスを残しているので
	for (auto TaskIt = m_TaskList.begin(); TaskIt != m_TaskList.end(); ++TaskIt) {
		Task* _ptask = *TaskIt;
		//そこから描画用タスクリストに登録
		auto DrawTaskIt = m_DrawTaskList.begin();
		for (; DrawTaskIt != m_DrawTaskList.end(); ++DrawTaskIt) {
			Task* _task = *DrawTaskIt;
			//自分より大きいDrawPriorityのタスクがあったら
			if (_task->m_DrawPriority > _ptask->m_DrawPriority)
				break;
		}
		m_DrawTaskList.insert(DrawTaskIt, _ptask);
	}
}
