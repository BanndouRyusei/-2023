//----------
//Zako.cpp
//----------
#include "Player.h"
#include "Enemy.h"
#include "EnemyShot.h"
#include "Stage.h"
#include"Sound.h"

const int BOSS_HP = 10;  //BOSS��HP
const int BOSS_W = 500; //��
const int BOSS_H = 500; //����
const int BOSS_ATTACKFLAME = 2;  //BOSS�̍U���^�C�~���O�t���[����
const float BOSS_SHOT_POSY = 0.0f; //�G�l�~�[�V���b�g�̍���
const float BOSS_SHOT_POSZ[4] = { 20.0f,60.0f,100.0f,140.0f };				//�U�����o���l�̃��[����Z���W
const int SHOT_WAIT = 120;     //�G�l�~�[��SHOT�Ԋu
const float BOSS_X = 500.0f;			//�{�X�̏o��X���W


CBoss::CBoss(float _ex, float _ey,float _ez, float _priortiy) :CCharaBase(_priortiy, CAST::BOSS) {
	m_Pos = VGet(_ex,_ey , _ez);
	m_HP = BOSS_HP;
	m_Speed = 4.0f;
	char buf[30];
	for (int i = 0; i < (int)e_ENEMYSTATE::NONE; i++) {
		sprintf_s(buf, "Data\\img\\Boss_Anim%d.png", i);
		LoadDivGraph(buf, ENEMY_ANIM, ENEMY_ANIM, 1, BOSS_W, BOSS_H, m_AnimImage[i]);
		if (m_AnimImage[i][0] == -1)assert(false);
	}
	m_NowState = e_ENEMYSTATE::NEUTRAL;
	m_ShotFlag = true;
	m_Inv = false;
	m_InvTimer = 0;
	m_DrawFlag = true;
	m_ShadowImage = LoadGraph("Data\\img\\BossShadow.png");
	if (m_ShadowImage == -1)assert(false);
	m_Shadow.SetShadow(m_ShadowImage, m_Pos, false);
	//BGM�؂�ւ�
	CBGM* bgm = (CBGM*)CTaskManager::Instance()->GetTask(CAST::BGM);
	bgm->ChangePhase(PHASE::END);
	CControlSound::GetInstance()->CreateBGM(e_BGM::BOSS);
	CStage* stage = (CStage*)CTaskManager::Instance()->GetTask(CAST::STAGE);
	m_ScrollX = stage->GetScrollX()*STAGE_SCROLLX;		//�{�X�̎����Ă���X�e�[�W�̃X�N���[���ʂ̏�����
}

CBoss::~CBoss() {
	//BGM���~�߂ăR���g���[���v���C���[�ɃN���A�����C����
	//�Q�[���I�[�o�[�̏ꍇ�͓����Ȃ�
	CBGM* bgm = (CBGM*)CTaskManager::Instance()->GetTask(CAST::BGM);
	if (bgm != nullptr) {
		bgm->ChangePhase(PHASE::END);
	}
	for (int i = 0; i < (int)e_ENEMYSTATE::NONE; i++) {
		for (int j = 0; j < ENEMY_ANIM; j++) {
			DeleteGraph(m_AnimImage[i][j]);
		}
	}
}

void CBoss::Update() {
	CStage* stage = (CStage*)CTaskManager::Instance()->GetTask(CAST::STAGE);
	m_Pos.x -= stage->GetScrollX()*STAGE_SCROLLX - m_ScrollX;
	m_ScrollX = stage->GetScrollX()*STAGE_SCROLLX;

	switch (m_NowState)
	{
	case e_ENEMYSTATE::NEUTRAL:
		if (m_AttackTimer++ >= SHOT_WAIT) {
			m_NowState = e_ENEMYSTATE::ATTACK;
			m_AttackTimer = 0;
			m_ShotFlag = true;
			m_Frame = 0;
			m_Timer = 0;
		}
	case e_ENEMYSTATE::ATTACK:
		if (m_ShotFlag &&m_Frame == BOSS_ATTACKFLAME) {
			if (m_Turn) {
				m_ShotPosX = BOSS_W;
			}
			else {
				m_ShotPosX = -BOSS_SHOT_SIZE / 2;
			}
			m_AttackTimer = 0;
			for (int i = 0; i < 4; i++) {
				new CBossShot(0.6f, false, VAdd(VGet(m_Pos.x,0.0f,0.0f), VGet(m_ShotPosX, BOSS_SHOT_POSY, BOSS_SHOT_POSZ[i])));
			}
			CControlSound::GetInstance()->CreateSE(e_SE::SHOT);
			m_ShotFlag = false;
		}
		if (m_Frame == ENEMY_ANIM - 1) {		//�A�j���[�V���������ׂčĐ����ꂽ��j���[�g����
			m_NowState = e_ENEMYSTATE::NEUTRAL;
		}
		AnimEnemy();
		break;
	case e_ENEMYSTATE::DAMAGE:
		if (m_Frame == ENEMY_ANIM - 1) {		//�A�j���[�V���������ׂčĐ����ꂽ��
			if (m_HP <= 0) {		//�̗͂�0�ȉ��Ȃ玀�S
				m_NowState = e_ENEMYSTATE::DEATH;
				m_Frame = 0;
				m_Timer = 0;
			}
			else {
				m_NowState = e_ENEMYSTATE::NEUTRAL;
				m_AttackTimer = SHOT_WAIT;
			}
		}
		AnimEnemy();
		break;
	case e_ENEMYSTATE::DEATH:
		if (m_Frame == ENEMY_ANIM - 1) {		//�A�j���[�V���������ׂčĐ����ꂽ��
			EnemyDeth();
		}
		else {
			AnimEnemy();
		}
		break;
	case e_ENEMYSTATE::NONE:
		break;
	default:
		break;
	}

	if (m_Pos.x >=  BOSS_X) {			//�{�X�̏o���ʒu�܂ŋ����X�N���[��
		stage->MoveScrollX();
	}
	else {			//�o���ʒu�ɗ�����X�N���[�����Ȃ��悤�ɂ���
		stage->ScrollLock();
	}
	BlinkBoss();
	m_Shadow.ObjectPosGet(m_Pos, false);
	m_DrawTask.SetPriority(ChangePriority(m_Pos.z));
}

//�G�l�~�[�̃A�j���[�V��������
void CBoss::AnimEnemy() {
	m_Timer++;
	if (m_Timer % (MAX_FPS / 3) == 0) {
		m_Frame++;
		if (m_Frame >= ENEMY_ANIM) {
			m_Frame = 0;
		}
		m_Timer = 0;
	}
}

void CBoss::Draw()const {
	if (m_DrawFlag) {
		DrawObject(m_Pos, m_AnimImage[(int)m_NowState][m_Frame], false, 0.0f);
	}
}

bool CBoss::HitCheck(const VECTOR &_pos, float _zwidth, int _ghandle) {
	if (IsHitObject(m_Pos, _pos, 40.0f, _zwidth, m_AnimImage[(int)m_NowState][0], _ghandle)) {
		if (!m_Inv && m_NowState < e_ENEMYSTATE::DAMAGE) {			//���G����Ȃ��ă_���[�W���[�V�����⎀�S���[�V�������s���Ă��Ȃ����
			m_NowState = e_ENEMYSTATE::DAMAGE;
			m_Frame = 0;
			m_Timer = 0;
			CPlayer* player = (CPlayer*)CTaskManager::Instance()->GetTask(CAST::PLAYER);
			if (true == player->GetPower()) {
				m_HP -= 2;
			}
			else {
				m_HP--;
			}
			m_Inv = true;
			m_InvTimer = 0;
			CControlSound::GetInstance()->CreateSE(e_SE::HIT);
		}
		return true;
	}
	else {
		return false;
	}
}

//�G�l�~�[���S���̏����@�v���C���[�L���������X�ɓ����ɂ���
void CBoss::EnemyDeth() {
	m_Alpha -= ALPHA_STEP;
	if (m_Alpha <= 0)			//���S�ɓ����ɂȂ�����Delete();
		Delete();
}

//�{�X�̖��G����
void CBoss::BlinkBoss() {
	const float INV_TIME = 2 * MAX_FPS;		//���G����(�b���~�ő�FPS)
	const float RATE = 30;
	if (m_Inv) {		//���G��ԂȂ�
		m_InvTimer++;
		m_DrawFlag = (sinf(DEG2RAD*(m_InvTimer  * RATE)) >= 0.0f) ? true : false;
		if (m_InvTimer >= INV_TIME) {		//���G���Ԃ𒴂�����
			m_Inv = false;
			m_DrawFlag = true;
		}
	}
}