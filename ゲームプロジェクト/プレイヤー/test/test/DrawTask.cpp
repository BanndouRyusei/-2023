#include"DrawTask.h"
#include"TaskManager.h"
#include"Task.h"

//�R���X�g���N�^
DrawTask::DrawTask()
	: m_prev(nullptr)
	, m_next(nullptr)
	, m_priority(0.0f)
	,m_task(nullptr)
	,m_func(nullptr)
{
}

//�f�X�g���N�^
DrawTask::~DrawTask()
{
	TaskManager::Instance()->RemoveTask(this);

	m_prev = nullptr;
	m_next = nullptr;
	m_priority = 0.0f;
	m_task = nullptr;
	m_func = nullptr;
}

//������
void DrawTask::Init(Task* task, std::function<void()> _func, float _priority) 
{
	m_prev = nullptr;
	m_next = nullptr;
	m_priority = _priority;
	m_task = task;
	m_func = _func;
	TaskManager::Instance()->AddTask(this);
}

//�D��x��ݒ�
void DrawTask::SetPriority(float prio)
{
	//�V�����D��x�ɕύX
	m_priority = prio;
	//�^�X�N�����X�g�����菜���A�ēx���X�g�ɒǉ����Ă�邱�Ƃ�
	//�V�����D��x�̈ʒu�Ƀ^�X�N��z�u
	TaskManager::Instance()->RemoveTask(this);
	TaskManager::Instance()->AddTask(this);
}

//�D��x���擾
float DrawTask::GetPriority() const
{
	return m_priority;
}

//�`�揈��
void DrawTask::Draw()
{
	if (m_task == nullptr) return;
	if (m_func == nullptr) return;

	m_func();
}