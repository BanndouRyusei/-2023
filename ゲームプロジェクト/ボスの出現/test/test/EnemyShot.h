//-----------------
//EnemyShot.h
//-----------------
#ifndef __ENEMYSHOT_H__
#define __ENEMYSHOT_H__
#pragma once

//ƒwƒbƒ_[ƒtƒ@ƒCƒ‹
#include "ShotBase.h"

//’è”
const int ZAKOA_SHOT_SIZE = 50; //G‹›A‚Ì’e‚Ì‘å‚«‚³
const int ZAKOB_SHOT_SIZE = 50; //G‹›B‚Ì’e‚Ì‘å‚«‚³
const int BOSS_SHOT_SIZE = 150;  //Boss‚Ì’e‚Ì‘å‚«‚³

class CZakoAShot :public CShotBase {
private:
	int m_Image;
public:
	CZakoAShot(float _priority, bool _isright, const VECTOR _pos);
	~CZakoAShot();
	void Update();
	void Draw()const;
	void HitCheck();
	void MoveShot();
	void CheckPos();
};


class CZakoBShot :public CShotBase {
private:
	int m_Image;
public:
	CZakoBShot(float _priority, bool _isright, const VECTOR _pos);
	~CZakoBShot();
	void Update();
	void Draw()const;
	void HitCheck();
	void MoveShot();
	void CheckPos();
};

class CBossShot :public CShotBase {
private:
	int m_Image;
public:
	CBossShot(float _priority, bool _isright, const VECTOR _pos);
	~CBossShot();
	void Update();
	void Draw()const;
	void HitCheck();
	void MoveShot();
	void CheckPos();
};

#endif  __ENEMYSHOT_H__