#pragma once
#include"Task.h"
#include"DrawTask.h"

class CTaskManager
{
private:
	static CTaskManager* ms_instance;		//CTaskManager�̃C���X�^���X
	CTask* m_Uhead;		//�擪�^�X�N�̃|�C���^�@�X�V�p
	CDrawTask* m_Dhead;		//�擪�^�X�N�̃|�C���^�@�`��p

public:
	//�R���X�g���N�^
	CTaskManager();
	//�f�X�g���N�^
	~CTaskManager();

	//CTaskManager�̃C���X�^���X���擾
	static CTaskManager* Instance();
	//CTaskManager�̃C���X�^���X��j���@�^�X�N�V�X�e���̏������Ɏg����
	static void ClearInstance();

	//���X�g�Ƀ^�X�N��ǉ��@�X�V�p
	void AddTask(CTask* task);
	//���X�g�Ƀ^�X�N��ǉ��@�`��p
	void AddTask(CDrawTask* task);
	//���X�g����^�X�N����菜���@�X�V�p
	void RemoveTask(CTask* task);
	//���X�g����^�X�N����菜���@�`��p
	void RemoveTask(CDrawTask* task);
	//�^�X�N���폜����@�X�V�p
	void DeleteTask(CTask* task);
	//�^�X�N���폜����@�`��p
	void DeleteTask(CDrawTask* task);
	//����ł���^�X�N���폜����
	void DeleteDeathTask();
	//�w�肵���O���[�v�̃^�X�N����Ԃ�
	int GetCount(CAST _id);
	//�w�肵���O���[�v�̃^�X�N���폜
	void EraseTask(CAST id);
	//�w�肵��id�������A�w�肵���ԍ��̃^�X�N��Ԃ�
	void* GetTask(CAST _id, int _number = 0);
	//�K�[�h���Ă���^�X�N�ȊO�̃^�X�N������
	void GuardKillTask();
	//CDrawTask��D��x���ɕ��ѕς���
	void DrawSort();

	//�X�V����
	void Update();

	//�`�揈��
	void Draw();
};