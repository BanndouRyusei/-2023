//-----------------
//TaskSystemEx.h
//-----------------
#ifndef _TASKEX_H_
#define _TASKEX_H_
#pragma once

#include "TaskSystem.h"

class TaskEx :public Task
{
public:

	//�R���X�g���N�^
	TaskEx();

	//�f�X�g���N�^
	~TaskEx();

	//�^�X�N�V�X�e��������
	static void InitTaskList(void);

	//�^�X�N���^�X�N���X�g�ɒǉ�����
	static void AddTask(Task* p_task);

	//�w�肵���O���[�v�̃^�X�N���폜
	void EraseTask(CAST id);

	//���S�����^�X�N�������폜
	static void DeleteDeathTask(void);

	//���ׂẴ^�X�N�����s�i�X�V�j����
	static void RunTask(void);

	//���ׂẴ^�X�N��`�悷��
	static void DrawTask(void);

	//�w�肵��id�̃^�X�N������`�悷��
	void DrawTask(CAST _id);

	//�w�肵���O���[�v�̃^�X�N����Ԃ�
	DWORD GetCount(CAST _id);

	//�w�肵��id�������A�w�肵���ԍ��̃^�X�N��Ԃ�
	void* GetTask(CAST _id, DWORD _number = 0);

	//�����̃f�[�^���擾
	void GetData(DATA* _pdata)const;

	//�����Ă���^�X�N���ׂẴf�X�g���N�^�ōs������������
	static void GuardDethTask(void);

	//�K�[�h����Ă���^�X�N�ȊO�̃f�X�g���N�^�ōs������������
	static void DethTask(void);

	//�`��^�X�N���X�g��`��D��x���ɕ��ѕς���
	static void UpdateDraw(void);

};

#endif _TASKEX_H_