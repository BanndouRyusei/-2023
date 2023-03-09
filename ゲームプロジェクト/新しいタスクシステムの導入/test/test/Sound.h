//-----------------
//sound.h
//-----------------
#ifndef _SOUND_H_
#define _SOUND_H_
#pragma once

//�w�b�_�[�t�@�C��
#include"myLib.h"

enum class BGMPHASE { START, PLAY, END, NONE };

//------SOUND EFFECT--------
enum class SE {  SELECT,NONE };		//SE�̎��
enum class BGM { TITLE,NONE };		//BGM�̎��

class CControlSound :public Task {
private:
	int m_Se[(int)SE::NONE] = { 0 };
	int m_Bgm[(int)BGM::NONE] = { 0 };
	const char* m_SeItem[(int)SE::NONE] = { "Data\\SE\\Select.mp3" };		//SE�t�@�C����
	const char* m_BgmItem[(int)BGM::NONE] = { "Data\\BGM\\yokoku.mp3" };		//BGM�t�@�C����
	static CControlSound* ms_Instance;			//���̃N���X�ɃA�N�Z�X���邽�߂̃C���X�^���X
public:
	CControlSound(float _priority = 0.5f);
	~CControlSound();
	void Update();
	void CreateSE(SE _number = SE::NONE, int _playtype = DX_PLAYTYPE_BACK);
	void CreateBGM(BGM _number = BGM::NONE);
	static CControlSound* GetInstance();	
};

class CSE :public Task {
private:
	int m_Se;
public:
	CSE(const int _se,  float _priority = 0.5f,int _playtype = DX_PLAYTYPE_BACK);
	~CSE();
	void Update();
};
class CBGM :public Task {
private:
	int *m_Bgm;
	int m_Volume;
	BGMPHASE m_Phase;
public:
	CBGM(const float _priority,  int *_bgm);
	~CBGM();
	void Update();
	void ChangePhase(BGMPHASE _phase);
};


#endif _PLAYER_H_