//---------------
//Clear.h
//---------------
#ifndef _CLEAR_
#define _CLEAR_
#pragma once

//�w�b�_�[�t�@�C��
#include"myLib.h"

//�萔
const int RANK = 3;			//�\�����郉���L���O��
//�����̉摜�̃T�C�Y
const int SCORE_DIGI_W = 40;
const int SCORE_DIGI_H = 40;
//�v���C���[�X�R�A�̕\���ʒu
const int PLAYER_SCORE_RIGHT = 500;
const int PLAYER_SCORE_TOP = 550;
//�����L���O�X�R�A�̕\���ʒu
const int RANK_SCORE_RIGHT = 500;
const int RANK_SCORE_TOP = 200;
const int RANK_SCORE_SPECE = 90;			//�����L���O�X�R�A�̊Ԋu
const int MIN_DIGIT = 6;			//�\������0�̐�

//�N���A��ʃN���X
class CClear : public CTask
{
private:
	CDrawTask m_DrawTask;
	PHASE m_Phase;
	DWORD	m_Timer;
	int m_Alpha;
	int m_CharAlpha;
	int m_AlphaTurn;
	int m_PlayerScore;
	int m_RankScore[RANK];
	int m_Image;
	int m_CharImage;
	int m_Digits[DIGITS];
public:
	CClear(float _priority);
	~CClear();
	void Update();
	void Draw() const;
	void LoadScore();
	void SaveScore();
	void SortScore();
};

#endif _CLEAR_
