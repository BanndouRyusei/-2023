//-----------------
//game.h
//-----------------
#ifndef _GAME_H_
#define _GAME_H_
#pragma once

//�w�b�_�[�t�@�C��
#include"myLib.h"
#include"Title_screen.h"
#include"Clear_Screen.h"
#include"game_screen.h"
#include"screen.h"
#include"Sound.h"

//�v���g�^�C�v
enum SCREEN;
class CScreen;

//�Q�[���N���X
class CGame
{
public:
	CGame();
	~CGame();
	void Update();
	void Draw();
private:
	CScreen*	m_pScreen;	//���݂̃X�N���[���N���X�̃|�C���^
	SCREEN		m_now_screen;	//��ʏ��
};

#endif _GAME_H_

