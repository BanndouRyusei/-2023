#include"TaskManager.h"

TaskManager* TaskManager::ms_instance = nullptr;

//�R���X�g���N�^
TaskManager::TaskManager()
	:m_Uhead(nullptr),m_Dhead(nullptr)
{
}

//�f�X�g���N�^
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

//TaskManager�̃C���X�^���X���擾
TaskManager* TaskManager::Instance()
{
	if (ms_instance == nullptr)
	{
		ms_instance = new TaskManager();
	}
	return ms_instance;
}

//TaskManager�̃C���X�^���X��j��
void TaskManager::ClearInstance()
{
	if (ms_instance != nullptr) 
	{
		delete ms_instance;
		ms_instance = nullptr;
	}
}

//���X�g�Ƀ^�X�N��ǉ��@�X�V�p
void TaskManager::AddTask(Task* task)
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
		Task* prev = nullptr;
		Task* next = m_Uhead;
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
void TaskManager::AddTask(DrawTask* task)
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
		DrawTask* prev = nullptr;
		DrawTask* next = m_Dhead;
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
void TaskManager::RemoveTask(Task* task)
{
	if (m_Uhead == task) {
		m_Uhead = task->m_next;
	}

	//��菜���^�X�N�̑O��̃^�X�N��ڑ�����
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

	//��菜���^�X�N�̐ڑ���͋�ɂ���
	task->m_prev = nullptr;
	task->m_next = nullptr;

}

//���X�g�����菜���@�X�V�p
void TaskManager::RemoveTask(DrawTask* task)
{
	if (m_Dhead == task) {
		m_Dhead = task->m_next;
	}

	//��菜���^�X�N�̑O��̃^�X�N��ڑ�����
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

	//��菜���^�X�N�̐ڑ���͋�ɂ���
	task->m_prev = nullptr;
	task->m_next = nullptr;

}

//�^�X�N���폜����@�X�V�p
void TaskManager::DeleteTask(Task* task) 
{
	delete task;
}

//�^�X�N���폜����@�`��p
void TaskManager::DeleteTask(DrawTask* task)
{
	delete task;
}

//����ł���^�X�N���폜����
void TaskManager::DeleteDeathTask() 
{
	Task* task = m_Uhead;		//����ł���΍폜����^�X�N
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

//�w�肵���O���[�v�̃^�X�N����Ԃ�
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

//�w�肵��id�������A�w�肵���ԍ��̃^�X�N��Ԃ�
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

//�K�[�h���Ă���^�X�N�ȊO�̃^�X�N������
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

//DrawTask����ёւ���
void TaskManager::DrawSort()
{

}

//�X�V����
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

//�`�揈��
void TaskManager::Draw()
{
	DrawTask* next = m_Dhead;
	while (next != nullptr)
	{
		next->Draw();
		next = next->m_next;
	}
}
