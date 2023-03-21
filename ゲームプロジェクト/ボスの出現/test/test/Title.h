//---------------
//Title.h
//---------------
#ifndef _TITLE_
#define _TITLE_
#pragma once

//�w�b�_�[�t�@�C��
#include"myLib.h"

//�萔
const int TITLE_MENU = 2;			//�^�C�g�����j���[��
const int MENU_MAX = TITLE_MENU - 1;
const int MENU_MIN = 0;
//�^�C�g�����j���[�̕\���ʒu
const int TITLE_MENU_X = 335;
const int TITLE_MENU_Y = 600;
const int TITLE_MENU_SPECE = 60;		//���j���[�̊Ԃ̊Ԋu
const int TITLE_CORSOR_SIZE = 60;		//�^�C�g���J�[�\���̉摜�T�C�Y
const int TITLE_MENU_ALPHA_STEP = 5;			//�I�΂�Ă��郁�j���[�̓_�łɑ���ALPHA_STEP
const int TITLE_MENU_ALPHA_MIN = 50;			//���j���[�_�ł�ALPHA�ŏ��l

//�^�C�g���i�w�i�j�N���X
class CTitle : public CTask
{
private:
	CDrawTask m_DrawTask;
	int m_Image;
	DWORD	m_Timer;
	PHASE m_Phase;
	int m_Alpha;
public:
	CTitle(float _priority);
	~CTitle();
	void Update();
	void Draw() const;
};

//�^�C�g����ʗp���j���[�N���X
class CTitleMenu :public CTask {
private:
	CDrawTask m_DrawTask;
	int m_Item;
	int m_SelectMenu;
	int m_Alpha;
	int m_AlphaTurn;
	bool	m_IsDecide;		//����L�[�������ꂽ���ǂ���
	int m_MenuImage[TITLE_MENU];
	int m_CusorImage;
public:
	CTitleMenu(float _priority);
	~CTitleMenu();
	void Update();
	void Draw() const;
};

#endif _TITLE_
