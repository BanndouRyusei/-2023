//-----------------
//ShadowManager.h
//-----------------
#ifndef _SHADOWMANAGER_H_
#define _SHADOWMANAGER_H_
#pragma once

//�w�b�_�[�t�@�C��
#include"myLib.h"
#include"Shadow.h"

//�萔

//�ۉe�N���X
class CShadowManager : public CTask {
private:
	CDrawTask m_DrawTask;
	std::list<CShadow*> m_ShadowList;			//�e���Ǘ����郊�X�g
	static CShadowManager* ms_Instance;			//���̃N���X�ɃA�N�Z�X���邽�߂̃C���X�^���X
public:
	CShadowManager(float _priority = 0.2f);
	~CShadowManager();
	void Update();			//�e�̃��X�g�ɓo�^����Ă���A�b�v�f�[�g�����s
	void Draw()const;		//�e�̃��X�g�ɓo�^����Ă���Draw�����s
	bool Regist(CShadow* _shadow);		//�e�̃��X�g�ɒǉ�
	bool Remove(CShadow* _shadow);		//�e�̃��X�g�������
	void InitShadowList();		//�e�̃��X�g����ɂ���
	static CShadowManager* GetInstance();		//���̃N���X�̃C���X�^���X���擾
};

#endif _SHADOWMANAGER_H_

