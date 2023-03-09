#include"TaskManager.h"

TaskManager* TaskManager::ms_instance = nullptr;

//コンストラクタ
TaskManager::TaskManager()
	:m_Uhead(nullptr),m_Dhead(nullptr)
{
}

//デストラクタ
TaskManager::~TaskManager()
{
	{
		Task* next = m_Uhead;
		while (next != nullptr)
		{
			Task* deleteTask = next;
			next = next->m_next;
			delete deleteTask;
		}
	}
	{
		DrawTask* next = m_Dhead;
		while (next != nullptr)
		{
			DrawTask* deleteTask = next;
			next = next->m_next;
			delete deleteTask;
		}
	}
}

//TaskManagerのインスタンスを取得
TaskManager* TaskManager::Instance()
{
	if (ms_instance == nullptr)
	{
		ms_instance = new TaskManager();
	}
	return ms_instance;
}

//TaskManagerのインスタンスを破棄
void TaskManager::ClearInstance()
{
	if (ms_instance != nullptr) 
	{
		delete ms_instance;
		ms_instance = nullptr;
	}
}

//リストにタスクを追加　更新用
void TaskManager::AddTask(Task* task)
{
	//リストにタスクが1つもない状態
	if (m_Uhead == nullptr)
	{
		//headに設定
		m_Uhead = task;
	}
	//リストに既にタスクが追加されている場合
	else 
	{
		Task* prev = nullptr;
		Task* next = m_Uhead;
		while (next != nullptr)
		{
			//追加するタスクより優先度が低いタスクが見つかった
			if (next->m_priority > task->m_priority)
			{
				//ループを抜ける
				break;
			}
			//追加するタスクより優先度が低いタスクが
			//見つかってないので次のタスクを調べる
			prev = next;
			next = next->m_next;
		}

		//追加するタスクのm_nextに優先度が低いタスクを設定
		//追加するタスクのm_prevを設定
		task->m_prev = prev;
		task->m_next = next;
		if (prev != nullptr) 
		{
			//追加するタスクより優先度が高いタスクの
			//m_nextに追加するタスクを設定
			prev->m_next = task;
		}
		//先頭タスクより優先度が高い場合
		else 
		{
			m_Uhead->m_prev = task;
			m_Uhead = task;
		}
		//優先度の低いタスクのm_prevの入れ替え
		if (next != nullptr)
		{
			next->m_prev = task;
		}
	}
}

//リストにタスクを追加　描画用
void TaskManager::AddTask(DrawTask* task)
{
	//リストにタスクが1つもない状態
	if (m_Dhead == nullptr)
	{
		//headに設定
		m_Dhead = task;
	}
	//リストに既にタスクが追加されている場合
	else
	{
		DrawTask* prev = nullptr;
		DrawTask* next = m_Dhead;
		while (next != nullptr)
		{
			//追加するタスクより優先度が低いタスクが見つかった
			if (next->m_priority > task->m_priority)
			{
				//ループを抜ける
				break;
			}
			//追加するタスクより優先度が低いタスクが
			//見つかってないので次のタスクを調べる
			prev = next;
			next = next->m_next;
		}

		//追加するタスクのm_nextに優先度が低いタスクを設定
		//追加するタスクのm_prevを設定
		task->m_prev = prev;
		task->m_next = next;
		if (prev != nullptr)
		{
			//追加するタスクより優先度が高いタスクの
			//m_nextに追加するタスクを設定
			prev->m_next = task;
		}
		//先頭タスクより優先度が高い場合
		else
		{
			m_Dhead->m_prev = task;
			m_Dhead = task;
		}
		//優先度の低いタスクのm_prevの入れ替え
		if (next != nullptr)
		{
			next->m_prev = task;
		}
	}
}

//リストから取り除く　更新用
void TaskManager::RemoveTask(Task* task)
{
	if (m_Uhead == task) {
		m_Uhead = task->m_next;
	}

	//取り除くタスクの前後のタスクを接続する
	Task* prev = task->m_prev;
	Task* next = task->m_next;

	if (prev != nullptr) 
	{
		prev->m_next = task->m_next;
	}
	if (next != nullptr) 
	{
		next->m_prev = task->m_prev;
	}

	//取り除くタスクの接続先は空にする
	task->m_prev = nullptr;
	task->m_next = nullptr;

}

//リストから取り除く　更新用
void TaskManager::RemoveTask(DrawTask* task)
{
	if (m_Dhead == task) {
		m_Dhead = task->m_next;
	}

	//取り除くタスクの前後のタスクを接続する
	DrawTask* prev = task->m_prev;
	DrawTask* next = task->m_next;

	if (prev != nullptr)
	{
		prev->m_next = task->m_next;
	}
	if (next != nullptr)
	{
		next->m_prev = task->m_prev;
	}

	//取り除くタスクの接続先は空にする
	task->m_prev = nullptr;
	task->m_next = nullptr;

}

//タスクを削除する　更新用
void TaskManager::DeleteTask(Task* task) 
{
	delete task;
}

//タスクを削除する　描画用
void TaskManager::DeleteTask(DrawTask* task)
{
	delete task;
}

//死んでいるタスクを削除する
void TaskManager::DeleteDeathTask() 
{
	Task* task = m_Uhead;		//死んでいれば削除するタスク
	while (task != nullptr)
	{
		if (!task->m_isActive) {
			Task* deleteTask = task;
			task = task->m_next;
			RemoveTask(deleteTask);
			delete deleteTask;
			continue;
		}
		task = task->m_next;
	}
}

//指定したグループのタスク数を返す
int TaskManager::GetCount(CAST _id) 
{
	int count = 0;

	Task* task = m_Uhead;
	while (task != nullptr)
	{
		if (task->m_id == _id) {
			count++;
		}
		task = task->m_next;
	}

	return count;
}

//指定したidを持ち、指定した番号のタスクを返す
void* TaskManager::GetTask(CAST _id, int _number) 
{
	int count = 0;
	Task* task = m_Uhead;
	while (task != nullptr)
	{
		if (task->m_id == _id && count++ == _number)return task;
		task = task->m_next;
	}
	return nullptr;
}

//ガードしているタスク以外のタスクを消す
void TaskManager::GuardKillTask()
{
	Task* task = m_Uhead;
	while (task != nullptr)
	{
		if (task->m_isActive && !task->m_guard)
		{
			Task* deleteTask = task;
			task = task->m_next;
			RemoveTask(deleteTask);
			delete deleteTask;
			continue;
		}
		task = task->m_next;
	}
}

//DrawTaskを並び替える
void TaskManager::DrawSort()
{

}

//更新処理
void TaskManager::Update()
{
	Task* next = m_Uhead;
	while (next != nullptr)
	{
		next->Update();
		next = next->m_next;
	}
	DeleteDeathTask();
}

//描画処理
void TaskManager::Draw()
{
	DrawTask* next = m_Dhead;
	while (next != nullptr)
	{
		next->Draw();
		next = next->m_next;
	}
}
