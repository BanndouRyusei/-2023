#include"DrawTask.h"
#include"TaskManager.h"
#include"Task.h"

//�R���X�g���N�^
CDrawTask::CDrawTask()
	: m_prev(nullptr)
	, m_next(nullptr)
	, m_priority(0.0f)
	,m_task(nullptr)
	,m_func(nullptr)
{
}

//�f�X�g���N�^
CDrawTask::~CDrawTask()
{
	CTaskManager::Instance()->RemoveTask(this);

	m_prev = nullptr;
	m_next = nullptr;
	m_priority = 0.0f;
	m_task = nullptr;
	m_func = nullptr;
}

//������
void CDrawTask::Init(CTask* task, std::function<void()> _func, float _priority) 
{
	m_prev = nullptr;
	m_next = nullptr;
	m_priority = _priority;
	m_task = task;
	m_func = _func;
	CTaskManager::Instance()->AddTask(this);
}

//�D��x��ݒ�
void CDrawTask::SetPriority(float prio)
{
	//�V�����D��x�ɕύX
	m_priority = prio;
	//�^�X�N�����X�g�����菜���A�ēx���X�g�ɒǉ����Ă�邱�Ƃ�
	//�V�����D��x�̈ʒu�Ƀ^�X�N��z�u
	CTaskManager::Instance()->RemoveTask(this);
	CTaskManager::Instance()->AddTask(this);
}

//�D��x���擾
float CDrawTask::GetPriority() const
{
	return m_priority;
}

//�`�揈��
void CDrawTask::Draw()
{
	if (m_task == nullptr) return;
	if (m_func == nullptr) return;

	m_func();
}