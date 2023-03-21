#include"Task.h"
#include"TaskManager.h"

//�R���X�g���N�^
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

//�f�X�g���N�^
CTask::~CTask()
{
	CTaskManager::Instance()->RemoveTask(this);
}

//�D��x��ݒ�
void CTask::SetPriority(float prio)
{
	//�V�����D��x�ɕύX
	m_priority = prio;
	//�^�X�N�����X�g�����菜���A�ēx���X�g�ɒǉ����Ă�邱�Ƃ�
	//�V�����D��x�̈ʒu�Ƀ^�X�N��z�u
	CTaskManager::Instance()->RemoveTask(this);
	CTaskManager::Instance()->AddTask(this);
}

//�D��x���擾
float CTask::GetPriority() const
{
	return m_priority;
}

//�^�X�N���폜
void CTask::Delete()
{
	m_isActive = false;
}