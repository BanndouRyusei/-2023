//-----------------
//PlayerShot.h
//-----------------
#ifndef _PLAYERSHOT_H_
#define _PLAYERSHOT_H_
#pragma once

//�w�b�_�[�t�@�C��
#include"ShotBase.h"

//�萔
//�v���C���[�̒e�̑傫��
const int PLAYER_SHOT_SIZE = 50;

class CPlayerShot :public CShotBase {
private:
	int m_Image;
public:
	CPlayerShot(float _priority,bool _isright,const VECTOR _pos);
	~CPlayerShot();
	void Update();
	void Draw() const;
	void HitCheck();
	void MoveShot();
	void CheckPos();
};

#endif _PLAYERSHOT_H_
