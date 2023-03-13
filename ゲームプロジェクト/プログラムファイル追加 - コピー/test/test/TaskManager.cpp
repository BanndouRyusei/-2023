#include"TaskManager.h"

CTaskManager* CTaskManager::ms_instance = nullptr;

//�R���X�g���N�^
CTaskManager::CTaskManager()
	:m_Uhead(nullptr),m_Dhead(nullptr)
{
}

//�f�X�g���N�^
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

//CTaskManager�̃C���X�^���X���擾
CTaskManager* CTaskManager::Instance()
{
	if (ms_instance == nullptr)
	{
		ms_instance = new CTaskManager();
	}
	return ms_instance;
}

//CTaskManager�̃C���X�^���X��j��
void CTaskManager::ClearInstance()
{
	if (ms_instance != nullptr) 
	{
		delete ms_instance;
		ms_instance = nullptr;
	}
}

//���X�g�Ƀ^�X�N��ǉ��@�X�V�p
void CTaskManager::AddTask(CTask* task)
{
	//���X�g�Ƀ^�X�N��1���Ȃ����
	if (m_Uhead == nullptr)
	{
		//head�ɐݒ�
		m_Uhead = task;
	}
	//���X�g�Ɋ��Ƀ^�X�N���ǉ�����Ă���ꍇ
	else 
	{
		CTask* prev = nullptr;
		CTask* next = m_Uhead;
		while (next != nullptr)
		{
			//�ǉ�����^�X�N���D��x���Ⴂ�^�X�N����������
			if (next->m_priority > task->m_priority)
			{
				//���[�v�𔲂���
				break;
			}
			//�ǉ�����^�X�N���D��x���Ⴂ�^�X�N��
			//�������ĂȂ��̂Ŏ��̃^�X�N�𒲂ׂ�
			prev = next;
			next = next->m_next;
		}

		//�ǉ�����^�X�N��m_next�ɗD��x���Ⴂ�^�X�N��ݒ�
		//�ǉ�����^�X�N��m_prev��ݒ�
		task->m_prev = prev;
		task->m_next = next;
		if (prev != nullptr) 
		{
			//�ǉ�����^�X�N���D��x�������^�X�N��
			//m_next�ɒǉ�����^�X�N��ݒ�
			prev->m_next = task;
		}
		//�擪�^�X�N���D��x�������ꍇ
		else 
		{
			m_Uhead->m_prev = task;
			m_Uhead = task;
		}
		//�D��x�̒Ⴂ�^�X�N��m_prev�̓���ւ�
		if (next != nullptr)
		{
			next->m_prev = task;
		}
	}
}

//���X�g�Ƀ^�X�N��ǉ��@�`��p
void CTaskManager::AddTask(CDrawTask* task)
{
	//���X�g�Ƀ^�X�N��1���Ȃ����
	if (m_Dhead == nullptr)
	{
		//head�ɐݒ�
		m_Dhead = task;
	}
	//���X�g�Ɋ��Ƀ^�X�N���ǉ�����Ă���ꍇ
	else
	{
		CDrawTask* prev = nullptr;
		CDrawTask* next = m_Dhead;
		while (next != nullptr)
		{
			//�ǉ�����^�X�N���D��x���Ⴂ�^�X�N����������
			if (next->m_priority > task->m_priority)
			{
				//���[�v�𔲂���
				break;
			}
			//�ǉ�����^�X�N���D��x���Ⴂ�^�X�N��
			//�������ĂȂ��̂Ŏ��̃^�X�N�𒲂ׂ�
			prev = next;
			next = next->m_next;
		}

		//�ǉ�����^�X�N��m_next�ɗD��x���Ⴂ�^�X�N��ݒ�
		//�ǉ�����^�X�N��m_prev��ݒ�
		task->m_prev = prev;
		task->m_next = next;
		if (prev != nullptr)
		{
			//�ǉ�����^�X�N���D��x�������^�X�N��
			//m_next�ɒǉ�����^�X�N��ݒ�
			prev->m_next = task;
		}
		//�擪�^�X�N���D��x�������ꍇ
		else
		{
			m_Dhead->m_prev = task;
			m_Dhead = task;
		}
		//�D��x�̒Ⴂ�^�X�N��m_prev�̓���ւ�
		if (next != nullptr)
		{
			next->m_prev = task;
		}
	}
}

//���X�g�����菜���@�X�V�p
void CTaskManager::RemoveTask(CTask* task)
{
	if (m_Uhead == task) {
		m_Uhead = task->m_next;
	}

	//��菜���^�X�N�̑O��̃^�X�N��ڑ�����
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

	//��菜���^�X�N�̐ڑ���͋�ɂ���
	task->m_prev = nullptr;
	task->m_next = nullptr;

}

//���X�g�����菜���@�X�V�p
void CTaskManager::RemoveTask(CDrawTask* task)
{
	if (m_Dhead == task) {
		m_Dhead = task->m_next;
	}

	//��菜���^�X�N�̑O��̃^�X�N��ڑ�����
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

	//��菜���^�X�N�̐ڑ���͋�ɂ���
	task->m_prev = nullptr;
	task->m_next = nullptr;

}

//�^�X�N���폜����@�X�V�p
void CTaskManager::DeleteTask(CTask* task) 
{
	delete task;
}

//�^�X�N���폜����@�`��p
void CTaskManager::DeleteTask(CDrawTask* task)
{
	delete task;
}

//����ł���^�X�N���폜����
void CTaskManager::DeleteDeathTask() 
{
	CTask* task = m_Uhead;		//����ł���΍폜����^�X�N
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

//�w�肵���O���[�v�̃^�X�N����Ԃ�
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

//�w�肵��id�������A�w�肵���ԍ��̃^�X�N��Ԃ�
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

//�K�[�h���Ă���^�X�N�ȊO�̃^�X�N������
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

//CDrawTask����ёւ���
void CTaskManager::DrawSort()
{

}

//�X�V����
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

//�`�揈��
void CTaskManager::Draw()
{
	CDrawTask* next = m_Dhead;
	while (next != nullptr)
	{
		next->Draw();
		next = next->m_next;
	}
}
