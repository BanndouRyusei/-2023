//-------------------------------
//Clear_screen.h
//-------------------------------
#ifndef _CLEAR_SCREEN_H
#define _CLEAR_SCREEN_H
#pragma once
//�w�b�_�[�t�@�C��
#include "mylib.h"
#include "screen.h"
#include"Sound.h"

//�Q�[���N���A�X�N���[���N���X
class CClearScreen :public CScreen
{
private:
	DWORD m_Timer;
public:
	CClearScreen();
	~CClearScreen();
	void Update();
	void Draw()const;

};

#endif  _CLEAR_SCREEN_H