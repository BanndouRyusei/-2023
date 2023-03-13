#include"TaskManager.h"

CTaskManager* CTaskManager::ms_instance = nullptr;

//コンストラクタ
CTaskManager::CTaskManager()
	:m_Uhead(nullptr),m_Dhead(nullptr)
{
}

//デストラクタ
CTaskManager::~CTaskManager()
{
	{
		CTask* next = m_Uhead;
		while (next != nullptr)
		{
			CTask* deleteTask = next;
			next = next->m_next;
			delete deleteTask;
		}
	}
	{
		CDrawTask* next = m_Dhead;
		while (next != nullptr)
		{
			CDrawTask* deleteTask = next;
			next = next->m_next;
			delete deleteTask;
		}
	}
}

//CTaskManagerのインスタンスを取得
CTaskManager* CTaskManager::Instance()
{
	if (ms_instance == nullptr)
	{
		ms_instance = new CTaskManager();
	}
	return ms_instance;
}

//CTaskManagerのインスタンスを破棄
void CTaskManager::ClearInstance()
{
	if (ms_instance != nullptr) 
	{
		delete ms_instance;
		ms_instance = nullptr;
	}
}

//リストにタスクを追加　更新用
void CTaskManager::AddTask(CTask* task)
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
		CTask* prev = nullptr;
		CTask* next = m_Uhead;
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
void CTaskManager::AddTask(CDrawTask* task)
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
		CDrawTask* prev = nullptr;
		CDrawTask* next = m_Dhead;
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
void CTaskManager::RemoveTask(CTask* task)
{
	if (m_Uhead == task) {
		m_Uhead = task->m_next;
	}

	//取り除くタスクの前後のタスクを接続する
	CTask* prev = task->m_prev;
	CTask* next = task->m_next;

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
void CTaskManager::RemoveTask(CDrawTask* task)
{
	if (m_Dhead == task) {
		m_Dhead = task->m_next;
	}

	//取り除くタスクの前後のタスクを接続する
	CDrawTask* prev = task->m_prev;
	CDrawTask* next = task->m_next;

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
void CTaskManager::DeleteTask(CTask* task) 
{
	delete task;
}

//タスクを削除する　描画用
void CTaskManager::DeleteTask(CDrawTask* task)
{
	delete task;
}

//死んでいるタスクを削除する
void CTaskManager::DeleteDeathTask() 
{
	CTask* task = m_Uhead;		//死んでいれば削除するタスク
	while (task != nullptr)
	{
		if (!task->m_isActive) {
			CTask* deleteTask = task;
			task = task->m_next;
			RemoveTask(deleteTask);
			delete deleteTask;
			continue;
		}
		task = task->m_next;
	}
}

//指定したグループのタスク数を返す
int CTaskManager::GetCount(CAST _id) 
{
	int count = 0;

	CTask* task = m_Uhead;
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
void* CTaskManager::GetTask(CAST _id, int _number) 
{
	int count = 0;
	CTask* task = m_Uhead;
	while (task != nullptr)
	{
		if (task->m_id == _id && count++ == _number)return task;
		task = task->m_next;
	}
	return nullptr;
}

//ガードしているタスク以外のタスクを消す
void CTaskManager::GuardKillTask()
{
	CTask* task = m_Uhead;
	while (task != nullptr)
	{
		if (task->m_isActive && !task->m_guard)
		{
			CTask* deleteTask = task;
			task = task->m_next;
			RemoveTask(deleteTask);
			delete deleteTask;
			continue;
		}
		task = task->m_next;
	}
}

//CDrawTaskを並び替える
void CTaskManager::DrawSort()
{

}

//更新処理
void CTaskManager::Update()
{
	CTask* next = m_Uhead;
	while (next != nullptr)
	{
		next->Update();
		next = next->m_next;
	}
	DeleteDeathTask();
}

//描画処理
void CTaskManager::Draw()
{
	CDrawTask* next = m_Dhead;
	while (next != nullptr)
	{
		next->Draw();
		next = next->m_next;
	}
}
