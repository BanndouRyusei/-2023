#pragma once

class CTaskManager;

//�^�X�N�̎��ʎq
enum class CAST
{
	CONTROLPLAYER,PLAYER,PLAYERSHOT, CONTROLZAKOA, ZAKO_A,
	CONTROLZAKOB, ZAKO_B, CONTROLBOSS, BOSS,STAGE,LIFE,HP,UI,TIME,SCORE, CONTROLSOUND, BGM, SE ,GAMECLEAR,GAMEOVER, NONE //�^�X�N����鎖�ɁA���ʎq�������ɓo�^����
};

class CTask 
{
	friend CTaskManager;

private:
	CTask* m_prev;		//�O�̃^�X�N�ւ̃|�C���^
	CTask* m_next;		//���̃^�X�N�ւ̃|�C���^
	float m_priority;		//�D��x(�l���������قǐ�ɍX�V)
	bool m_isActive;		//�^�X�N�̐���
	CAST m_id;			//�^�X�N���ʎq
	bool m_guard;		//�^�X�N�����ȂȂ��悤�ɂ���ϐ�		true(�����Ȃ�)
public:
	//�R���X�g���N�^
	CTask(float prio,CAST _id);
	//�f�X�g���N�^
	virtual ~CTask();

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