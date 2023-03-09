#pragma once
#include <functional>

class Task;
class TaskManager;

class DrawTask
{
	friend TaskManager;

private:
	DrawTask* m_prev;		//�O�̃^�X�N�ւ̃|�C���^
	DrawTask* m_next;		//���̃^�X�N�ւ̃|�C���^
	float m_priority;		//�D��x(�l���������قǐ�ɕ`��)

	Task* m_task;
	std::function<void()> m_func;

public:
	//�R���X�g���N�^
	DrawTask();
	//�f�X�g���N�^
	~DrawTask();
	void Init(Task* task, std::function<void()> _func, float _priority);

	//�D��x��ݒ�
	void SetPriority(float prio);
	//�D��x���擾
	float GetPriority() const;

	//�`�揈��
	void Draw();
};