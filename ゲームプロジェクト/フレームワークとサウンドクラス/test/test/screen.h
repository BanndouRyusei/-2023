//-----------------------
//screen.h
//-----------------------


#ifndef _SCREEN_H_
#define _SCREEN_H_
#pragma once

//�Q�[���X�N���[���̎��
enum SCREEN{
	TITLE_SCREEN,
	GAME_SCREEN,
	CLEAR_SCREEN,
	OVER_SCREEN
};

//�x�[�X�ƂȂ�CScreen�N���X�̒�`
class CScreen
{
protected:
	SCREEN m_state;
public:
	CScreen() : m_state(SCREEN::TITLE_SCREEN) {}
	virtual ~CScreen(){}
	virtual void	Update() {}
	virtual void	Draw() const {}
	SCREEN GetNextScreen() { return(m_state); }//���̃X�N���[��������
};

#endif _SCREEN_H_

