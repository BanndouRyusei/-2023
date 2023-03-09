#pragma once
#include"Task.h"
#include"DrawTask.h"

class TaskManager
{
private:
	static TaskManager* ms_instance;		//TaskManager�̃C���X�^���X
	Task* m_Uhead;		//�擪�^�X�N�̃|�C���^�@�X�V�p
	DrawTask* m_Dhead;		//�擪�^�X�N�̃|�C���^�@�`��p

public:
	//�R���X�g���N�^
	TaskManager();
	//�f�X�g���N�^
	~TaskManager();

	//TaskManager�̃C���X�^���X���擾
	static TaskManager* Instance();
	//TaskManager�̃C���X�^���X��j���@�^�X�N�V�X�e���̏������Ɏg����
	static void ClearInstance();

	//���X�g�Ƀ^�X�N��ǉ��@�X�V�p
	void AddTask(Task* task);
	//���X�g�Ƀ^�X�N��ǉ��@�`��p
	void AddTask(DrawTask* task);
	//���X�g����^�X�N����菜���@�X�V�p
	void RemoveTask(Task* task);
	//���X�g����^�X�N����菜���@�`��p
	void RemoveTask(DrawTask* task);
	//�^�X�N���폜����@�X�V�p
	void DeleteTask(Task* task);
	//�^�X�N���폜����@�`��p
	void DeleteTask(DrawTask* task);
	//����ł���^�X�N���폜����
	void DeleteDeathTask();
	//�w�肵���O���[�v�̃^�X�N����Ԃ�
	int GetCount(CAST _id);
	//�w�肵��id�������A�w�肵���ԍ��̃^�X�N��Ԃ�
	void* GetTask(CAST _id, int _number = 0);
	//�K�[�h���Ă���^�X�N�ȊO�̃^�X�N������
	void GuardKillTask();
	//DrawTask��D��x���ɕ��ѕς���
	void DrawSort();

	//�X�V����
	void Update();

	//�`�揈��
	void Draw();
};