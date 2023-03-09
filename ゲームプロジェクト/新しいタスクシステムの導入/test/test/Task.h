#pragma once

class TaskManager;

//�^�X�N�̎��ʎq
enum class CAST
{
	PLAYER, ENEMY, CONTROLSOUND, BGM, SE , NONE //�^�X�N����鎖�ɁA���ʎq�������ɓo�^����
};

class Task 
{
	friend TaskManager;

private:
	Task* m_prev;		//�O�̃^�X�N�ւ̃|�C���^
	Task* m_next;		//���̃^�X�N�ւ̃|�C���^
	float m_priority;		//�D��x(�l���������قǐ�ɍX�V)
	bool m_isActive;		//�^�X�N�̐���
	CAST m_id;			//�^�X�N���ʎq
	bool m_guard;		//�^�X�N�����ȂȂ��悤�ɂ���ϐ�		true(�����Ȃ�)
public:
	//�R���X�g���N�^
	Task(float prio,CAST _id);
	//�f�X�g���N�^
	virtual ~Task();

	//�D��x��ݒ�
	void SetPriority(float prio);
	//�D��x���擾
	float GetPriority() const;
	//���ȂȂ��悤�ɂ���ϐ���ݒ�
	void IsGuardFlg(const bool _isGuard)
	{
		m_guard = _isGuard;
	}
	//�^�X�N���폜
	void Delete();
	//�X�V����
	virtual void Update() = 0;
};