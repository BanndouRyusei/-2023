//-----------------
//Sound.h
//-----------------
#ifndef _SOUND_H_
#define _SOUND_H_
#pragma once

//ヘッダーファイル
#include"myLib.h"

//------SOUND EFFECT--------
enum class e_SE { SELECT, GAMEOVER, NONE };		//e_SEの種類
enum class e_BGM { TITLE,NONE };		//e_BGMの種類

class CControlSound :public CTask {
private:
	int m_Se[(int)e_SE::NONE] = { 0 };
	int m_Bgm[(int)e_BGM::NONE] = { 0 };
	const char* m_SeItem[(int)e_SE::NONE] = { "Data\\SE\\Select.mp3","Data\\SE\\gameover.mp3" };		//e_SEファイル名
	const char* m_BgmItem[(int)e_BGM::NONE] = { "Data\\BGM\\yokoku.mp3" };		//e_BGMファイル名
	static CControlSound* ms_Instance;			//このクラスにアクセスするためのインスタンス
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