//---------------
//Title_screen.h
//---------------
#ifndef _TITLE_SCREEN_H_
#define _TITLE_SCREEN_H_
#pragma once

//�w�b�_�[�t�@�C��
#include"myLib.h"
#include"screen.h"
#include"Sound.h"


//�^�C�g���X�N���[���N���X
class CTitleScreen : public CScreen
{
private:
	DWORD m_Timer;
public:
	CTitleScreen();
	~CTitleScreen();
	void Update();
	void Draw() const;
};

#endif _TITLE_SCREEN_H_