//-------------------------
//TaskSystemEx.cpp
//-------------------------
#include "TaskSystemEx.h"

//list<Task *>m_TaskList;
list<Task *>m_TaskList;		//�X�V�p���X�g
list<Task *>m_DrawTaskList;		//�`��p���X�g

//�^�X�N�̏����l��ݒ�
TaskEx::TaskEx() {
	m_pos = VGet(0.0f, 0.0f, 0.0f);
	m_id = CAST::NONE;
	m_priority = 0.0f;
	m_DrawPriority = 0.0f;
	m_isActive = false;
	m_guard = false;
}

//�^�X�N���X�g����ɂ���
TaskEx::~TaskEx() {
	InitTaskList();
}

//�^�X�N���X�g�̏�����
void TaskEx::InitTaskList(void) {
	//�X�V�p�̃^�X�N���X�g��������
	if (!m_TaskList.empty()) {
		m_TaskList.clear();
	}
	//�`��p�̃^�X�N���X�g��������
	if (!m_DrawTaskList.empty()) {
		m_DrawTaskList.clear();
	}
}

//�^�X�N���^�X�N���X�g�ɒǉ�����
//p_task:�^�X�N
void TaskEx::AddTask(Task* _ptask)
{
	//�X�V�p�̃^�X�N���X�g�ɒǉ�
	auto it = m_TaskList.begin();
	Task* _task;
	for (; it != m_TaskList.end(); ++it) {
		_task = *it;
		//�������傫��priority�̃^�X�N����������
		if (_task->m_priority > _ptask->m_priority)
			break;
	}
	m_TaskList.insert(it, _ptask);

	//�`��p�̃^�X�N���X�g�ɒǉ�
	it = m_DrawTaskList.begin();
	for (; it != m_DrawTaskList.end(); ++it) {
		_task = *it;
		//�������傫��DrawPriority�̃^�X�N����������
		if (_task->m_DrawPriority > _ptask->m_DrawPriority)
			break;
	}
	m_DrawTaskList.insert(it, _ptask);
}

//���S�������ׂẴ^�X�N����������
//�^�X�N���X�g���쒆�́A�g�p�֎~
void TaskEx::DeleteDeathTask(void)
{
	Task* _task;
	//�X�V�p�̃^�X�N���X�g����폜
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
	//�`��p�̃^�X�N���X�g����폜
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

//�w�肵���O���[�v(id)�̃^�X�N���폜
//�^�X�N���X�g���쒆�́A�g�p�֎~
//����U���ň�ԑŐs�Ɏg�p�\
void TaskEx::EraseTask(CAST _id) {
	Task* p_task;
	//�X�V�p�̃^�X�N���X�g����폜
	for (auto it = m_TaskList.begin(); it != m_TaskList.end();)
	{
		 p_task = *it;
		if (p_task->m_id == _id) {
			it = m_TaskList.erase(it);
			continue;
		}
		it++;
	}
	//�`��p�̃^�X�N���X�g����폜
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

//�����Ă��邷�ׂẴ^�X�N�����s�i�X�V�j����
void TaskEx::RunTask(void)
{
	for (auto task : m_TaskList) {
		if (task->m_isActive)task->Update();
	}
	TaskEx::UpdateDraw();
}

//�����Ă��邷�ׂẴ^�X�N��`�悷��
void TaskEx::DrawTask(void)
{
	for (auto task : m_DrawTaskList) {
		if (task->m_isActive)task->Draw();
	}
}

//�w�肵���O���[�v(id)�̃^�X�N������`�悷��
void TaskEx::DrawTask(CAST _id) {
	for (auto task : m_DrawTaskList) {
		if (task->m_id == _id)task->Draw();
	}
}

//�w�肵���O���[�v(id)�̃^�X�N����Ԃ�
DWORD TaskEx::GetCount(CAST _id) {
	DWORD count = 0;
	for (auto task : m_TaskList)
	{
		if (task->m_id == _id)count++;
	}
	return count;
}

//�w�肵���O���[�v(id)�������A�w�肵���ԍ��̃^�X�N��Ԃ�
//�����O���[�v(id)�̂��̂���������ꍇ�́Anumber=0����t�Ԃ���Ă���
void* TaskEx::GetTask(CAST _id, DWORD _number) {
	int count = 0;
	for (auto task : m_TaskList) {
		if (task->m_id == _id && count++ == _number)return task;
	}
	return nullptr;
}

//�����̃f�[�^���擾
void TaskEx::GetData(DATA* _pdata)const {

	if (!_pdata)return;

	_pdata->pos = m_pos;
}

//�����Ă���^�X�N�̃f�X�g���N�^�ōs������������
void TaskEx::GuardDethTask(void) {
	for (auto task : m_TaskList) {
		if (task->m_isActive)task->Deth();
	}
}

//�K�[�h����Ă���^�X�N�ȊO�̃f�X�g���N�^�ōs������������
void TaskEx::DethTask(void) {
	for (auto task : m_TaskList) {
		if (task->m_isActive&&!(task->m_guard))task->Deth();
	}
}

//�`��^�X�N���X�g��`��D��x���ɕ��ѕς���
void TaskEx::UpdateDraw(void) {
	//��U�`��p�^�X�N���X�g���炷�ׂĉ���
	if (!m_DrawTaskList.empty()) {
		m_DrawTaskList.clear();
	}
	//�X�V�p�^�X�N���X�g�ɃN���X���c���Ă���̂�
	for (auto TaskIt = m_TaskList.begin(); TaskIt != m_TaskList.end(); ++TaskIt) {
		Task* _ptask = *TaskIt;
		//��������`��p�^�X�N���X�g�ɓo�^
		auto DrawTaskIt = m_DrawTaskList.begin();
		for (; DrawTaskIt != m_DrawTaskList.end(); ++DrawTaskIt) {
			Task* _task = *DrawTaskIt;
			//�������傫��DrawPriority�̃^�X�N����������
			if (_task->m_DrawPriority > _ptask->m_DrawPriority)
				break;
		}
		m_DrawTaskList.insert(DrawTaskIt, _ptask);
	}
}
