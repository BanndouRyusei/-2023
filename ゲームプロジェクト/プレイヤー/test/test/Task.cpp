#include"Task.h"
#include"TaskManager.h"

//�R���X�g���N�^
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

//�f�X�g���N�^
Task::~Task()
{
	TaskManager::Instance()->RemoveTask(this);
}

//�D��x��ݒ�
void Task::SetPriority(float prio)
{
	//�V�����D��x�ɕύX
	m_priority = prio;
	//�^�X�N�����X�g�����菜���A�ēx���X�g�ɒǉ����Ă�邱�Ƃ�
	//�V�����D��x�̈ʒu�Ƀ^�X�N��z�u
	TaskManager::Instance()->RemoveTask(this);
	TaskManager::Instance()->AddTask(this);
}

//�D��x���擾
float Task::GetPriority() const
{
	return m_priority;
}

//�^�X�N���폜
void Task::Delete()
{
	m_isActive = false;
}