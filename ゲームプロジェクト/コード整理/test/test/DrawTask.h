#pragma once
#include <functional>

class CTask;
class CTaskManager;

class CDrawTask
{
	friend CTaskManager;

private:
	CDrawTask* m_prev;		//�O�̃^�X�N�ւ̃|�C���^
	CDrawTask* m_next;		//���̃^�X�N�ւ̃|�C���^
	float m_priority;		//�D��x(�l���������قǐ�ɕ`��)

	CTask* m_task;
	std::function<void()> m_func;

public:
	//�R���X�g���N�^
	CDrawTask();
	//�f�X�g���N�^
	~CDrawTask();
	void Init(CTask* task, std::function<void()> _func, float _priority);

	//�D��x��ݒ�
	void SetPriority(float prio);
	//�D��x���擾
	float GetPriority() const;

	//�`�揈��
	void Draw();
};