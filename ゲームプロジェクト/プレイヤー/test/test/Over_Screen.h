//-------------------------------
//Over_screen.h
//-------------------------------
#ifndef _OVER_SCREEN_H
#define _OVER_SCREEN_H
#pragma once
//�w�b�_�[�t�@�C��
#include "mylib.h"
#include "screen.h"
#include"Sound.h"

//�Q�[���N���A�X�N���[���N���X
class COverScreen :public CScreen
{
private:
	DWORD m_Timer;
public:
	COverScreen();
	~COverScreen();
	void Update();
	void Draw()const;

};

#endif  _OVER_SCREEN_H
