//-----------------
//Sound.h
//-----------------
#ifndef _SOUND_H_
#define _SOUND_H_
#pragma once

//�w�b�_�[�t�@�C��
#include"myLib.h"

//------SOUND EFFECT--------
enum class e_SE { CHANGE, SELECT, SHOT, HIT, RECOVERY, POWERUP, JUMP, DEATH, GAMEOVER, NONE };		//e_SE�̎��
enum class e_BGM { TITLE, GAME, BOSS, CLEAR, NONE };		//e_BGM�̎��

class CControlSound :public CTask {
private:
	int m_Se[(int)e_SE::NONE] = { 0 };
	int m_Bgm[(int)e_BGM::NONE] = { 0 };
	const char* m_SeItem[(int)e_SE::NONE] = { "Data\\SE\\����{�^��������12.mp3","Data\\SE\\�J�[�\���ړ�7.mp3","Data\\SE\\�i�C�t�𓊂���.mp3",
		"Data\\SE\\���p���`.mp3","Data\\SE\\�X�e�[�^�X����1.mp3","Data\\SE\\�p���[�A�b�v.mp3",
		"Data\\SE\\�����W�����v.mp3","Data\\SE\\�o�^���Ɠ|���.mp3","Data\\SE\\gameover.mp3" };		//e_SE�t�@�C����
	const char* m_BgmItem[(int)e_BGM::NONE] = { "Data\\BGM\\gametitle.mp3","Data\\BGM\\normal_A.mp3",
		"Data\\BGM\\bossbattle.mp3","Data\\BGM\\scoreandclear.mp3", };		//e_BGM�t�@�C����
	static CControlSound* ms_Instance;			//���̃N���X�ɃA�N�Z�X���邽�߂̃C���X�^���X
public:
	CControlSound(float _priority = 0.5f);
	~CControlSound();
	void Update();
	void CreateSE(e_SE _number = e_SE::NONE, int _playtype = DX_PLAYTYPE_BACK);
	void CreateBGM(e_BGM _number = e_BGM::NONE);
	static CControlSound* GetInstance();	
};

class CSE :public CTask {
private:
	int m_Se;
public:
	CSE(const int _se,  float _priority = 0.5f,int _playtype = DX_PLAYTYPE_BACK);
	~CSE();
	void Update();
};
class CBGM :public CTask {
private:
	int *m_Bgm;
	int m_Volume;
	PHASE m_Phase;
public:
	CBGM(const float _priority,  int *_bgm);
	~CBGM();
	void Update();
	void ChangePhase(PHASE _phase);
};


#endif _SOUND_H_