//---------------------------
//Player.cpp
//---------------------------
#include"Player.h"
#include"Stage.h"
#include"PlayerShot.h"
#include"UI.h"
#include"Effect.h"
#include"Sound.h"
#if defined(_DEBUG) | defined(DEBUG)
#include"Item.h"		//���ŃA�C�e�����o�����߂ɓǂ݂�ł���
#endif

//�萔
const int PLAYER_ATTACKFLAME = 2;			//�v���C���[�̍U���t���[��
const int PLAYER_JUMPFLAME = 1;				//�v���C���[�̏㏸�I���t���[��
const int PLAYER_FALLFLAME = 3;				//�v���C���[�̗����I���t���[��
//�v���C���[�摜�̑傫��
const int PLAYER_H = 200;
const int PLAYER_W = 200;
//�v���C���[�̈ړ��\�ʒuX
const float PLAYER_X_MAX = WINDOW_W / 2 - PLAYER_W;
//�v���C���[��Z���̌���
const float PLAYER_Z_WIDTH = 40.0f;
const float PLAYER_SHOT_POSY = 60.0f;			//�v���C���[�V���b�g�̍���(�摜�̍����ɍ��킹��)
const float GRAVITY = 30.0f;		//�d��
const float JUMP_POWER = 920.0f;		//�W�����v��
const float PLAYER_SHADOW_Y = WINDOW_H - PLAYER_H - 50.0f - OBJECT_Z_MAX;			//�v���C���[�̉e��Y�̍ő�l(50�͒����l)
const int PLAYER_POWER_MAX = 2;				//�v���C���[�̍ő�U����
const float PLAYER_POWERUP_TIME = 10 * MAX_FPS;			//�U���̓A�b�v����

CPlayer::CPlayer(float _priority) :CCharaBase(_priority, CAST::PLAYER),m_AnimImage() {
	m_Pos = VGet(0.0f, 0.0f, 39.0f);
	m_HP = PLAYER_HP;
	char buf[30];
	for (int i = 0; i < (int)e_PLAYERSTATE::NONE; i++) {
		sprintf_s(buf, "Data\\img\\Player_Anim%d.png", i);
		LoadDivGraph(buf, PLAYER_ANIM, PLAYER_ANIM, 1, PLAYER_W, PLAYER_H, m_AnimImage[i]);
		if (m_AnimImage[i][0] == -1)assert(false);
	}
	m_NowState = e_PLAYERSTATE::NEUTRAL;
	m_Speed = 4.0f;
	m_Power = 1;
	m_PowerUpTimer = 0;
	m_Turn = false;
	m_Frame = 0;
	m_Timer = 0;
	m_ShotFlag = false;
	m_Alpha = ALPHA_MAX;
	m_JumpPower = 0.0f;
	m_Inv = true;
	m_InvTimer = 0;
	m_DrawFlag = true;
	m_ShadowImage = LoadGraph("Data\\img\\PlayerShadow.png");
	if (m_ShadowImage == -1)assert(false);
	m_Shadow.SetShadow(m_ShadowImage, m_Pos, m_Turn, PLAYER_SHADOW_Y);
}

CPlayer::~CPlayer() {
	CTaskManager::Instance()->EraseTask(CAST::EFFECT);
	for (int i = 0; i < (int)e_PLAYERSTATE::NONE; i++) {
		for (int j = 0; j < PLAYER_ANIM; j++) {
			DeleteGraph(m_AnimImage[i][j]);
		}
	}
	DeleteGraph(m_ShadowImage);
}

void CPlayer::Update() {
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	CHP* hp = (CHP*)CTaskManager::Instance()->GetTask(CAST::HP);
	hp->SetPlayerHp(m_HP);
	switch (m_NowState)
	{
	case e_PLAYERSTATE::NEUTRAL:
	case e_PLAYERSTATE::WALK:
		MovePlayer(key);
		AnimPlayer();
		break;
	case e_PLAYERSTATE::JUMP:
		MovePlayer(key);
		PlayerJumping();
		break;
	case e_PLAYERSTATE::ATTACK:
		if (!m_ShotFlag&&m_Frame == PLAYER_ATTACKFLAME) {			//�e���o���Ă��Ȃ��Ēe���o���t���[����������e���o���B
			float shotposx;
			if (m_Turn) {			//�����Ă�������ɂ����X���ˈʒu��ς���
				shotposx = -PLAYER_SHOT_SIZE;
			}
			else {
				shotposx = PLAYER_W;
			}
			//�e����
			new CPlayerShot(0.5f, m_Turn, VAdd(m_Pos, VGet(shotposx, PLAYER_SHOT_POSY, 0.0f)));
			CControlSound::GetInstance()->CreateSE(e_SE::SHOT);
			m_ShotFlag = true;
		}
		if (m_Frame == PLAYER_ANIM - 1) {		//�A�j���[�V���������ׂčĐ����ꂽ��j���[�g����
			m_NowState = e_PLAYERSTATE::NEUTRAL;
		}
		AnimPlayer();
		break;
	case e_PLAYERSTATE::DAMAGE:
		if (m_Frame == PLAYER_ANIM - 1) {		//�A�j���[�V���������ׂčĐ����ꂽ��
			if (m_HP <= 0) {		//�̗͂�0�ȉ��Ȃ玀�S
				m_NowState = e_PLAYERSTATE::DEATH;
				m_Frame = 0;
				m_Timer = 0;
			}
			else {
				m_NowState = e_PLAYERSTATE::NEUTRAL;
			}
		}
		AnimPlayer();
		break;
	case e_PLAYERSTATE::DEATH:
		if (m_Frame == PLAYER_ANIM - 1) {		//�A�j���[�V���������ׂčĐ����ꂽ��
			PlayerDeth();
		}
		else {
			AnimPlayer();
		}
		break;
	case e_PLAYERSTATE::NONE:
		break;
	default:
		break;
	}

	m_JumpPower -= GRAVITY;
	m_Pos.y += (m_JumpPower*FRAMETIME_S);

	if (m_Pos.y <= 0.0f) {		//�n�ʂɂ߂荞�܂Ȃ��悤�ɂ���
		m_Pos.y = 0.0f;
	}

	if (m_Power >= PLAYER_POWER_MAX) {			//�U���̓A�b�v��ԂȂ�
		if (m_PowerUpTimer++ >= PLAYER_POWERUP_TIME) {			//�U���̓A�b�v���Ԃ��߂�����
			m_Power = 1;
		}
	}

	m_Shadow.ObjectPosGet(m_Pos, m_Turn);

	BlinkPlayer();
	m_DrawTask.SetPriority(ChangePriority(m_Pos.z));
}

void CPlayer::Draw() const {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_Alpha);
	if (m_DrawFlag) {
		DrawObject(m_Pos, m_AnimImage[(int)m_NowState][m_Frame], m_Turn, 0.0f);
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, ALPHA_MAX);
#if defined(_DEBUG) | defined(DEBUG)
	DrawCircle(m_Pos.x + PLAYER_W / 2, WINDOW_H - m_Pos.y - m_Pos.z - PLAYER_H / 2.0f, 5.0f,GetColor(0, 0, 255), TRUE);
	printfDx("�v���C���[���W�@X%f,Y%f,Z%f\n", m_Pos.x, m_Pos.y, m_Pos.z);
	printfDx("�v���C���[�̗̑́@%d�@�v���C���[�̍U����%d\n", m_HP,m_Power);
	printfDx("������@ �����L�[�ňړ�(X,Z),Z�L�[�Œe����,�X�y�[�X�L�[�ŃW�����v,X�L�[�Ń_���[�W����\n");
	printfDx("C�L�[�ŃA�C�e���o��\n");
	printf("�v���C���[���W�@X%f,Y%f,Z%f\n", m_Pos.x, m_Pos.y, m_Pos.z);
#endif
}

//�v���C���[�̈ړ�����
void CPlayer::MovePlayer(int _key) {
	VECTOR temp = m_Pos;
	if (m_NowState <= e_PLAYERSTATE::WALK) {
		if (_key&PAD_INPUT_A) {			//Z�L�[��������
			m_NowState = e_PLAYERSTATE::ATTACK;
			m_Frame = 0;
			m_Timer = 0;
			m_ShotFlag = false;
		}
		if (_key&PAD_INPUT_10) {	//�W�����v��Ԃ�
			m_NowState = e_PLAYERSTATE::JUMP;
			m_Frame = 0;
			m_Timer = 0;
			m_JumpPower = JUMP_POWER;
			CControlSound::GetInstance()->CreateSE(e_SE::JUMP);
		}
	}
	if (_key & PAD_INPUT_RIGHT) {
		temp.x += m_Speed;
		m_Pos.x = min(temp.x, PLAYER_X_MAX + 1.0f);		//�ړ��\�ʒu����ɂ���Ȃ��ʃX�N���[������̂��߂Ɉړ��\�ʒu��菭����ɍ��W��ݒ肷��
		m_Turn = false;
	}
	if (_key & PAD_INPUT_LEFT) {
		temp.x -= m_Speed;
		m_Pos.x = max(temp.x, 0);
		m_Turn = true;
	}
	if (_key & PAD_INPUT_UP) {
		temp.z += m_Speed;
		m_Pos.z = min(temp.z, OBJECT_Z_MAX);
	}
	if (_key & PAD_INPUT_DOWN) {
		temp.z -= m_Speed;
		m_Pos.z = max(temp.z, 0);
	}
	if (_key == 0) {
		if (m_NowState == e_PLAYERSTATE::WALK){
			m_NowState = e_PLAYERSTATE::NEUTRAL;
			m_Frame = 0;
			m_Timer = 0;
		}
	}
	else {
		if (m_NowState == e_PLAYERSTATE::NEUTRAL) {
			m_NowState = e_PLAYERSTATE::WALK;
			m_Frame = 0;
			m_Timer = 0;
		}
	}
#if defined(_DEBUG) | defined(DEBUG)
	if (IsKeyTrigger(_key, PAD_INPUT_B)) {			//���Ń_���[�W���[�V�����𗬂�
		m_NowState = e_PLAYERSTATE::DAMAGE;
		m_Frame = 0;
		m_Timer = 0;
		m_HP--;
		m_Inv = true;
		m_InvTimer = 0;
		CControlSound::GetInstance()->CreateSE(e_SE::HIT);
	}
	if (IsKeyTrigger(_key, PAD_INPUT_C)) {			//���ŃA�C�e�����o��
		float items = (float)CTaskManager::Instance()->GetCount(CAST::ITEM);
		if ((float)GetRand(100) < (APPER_RAND - (float)GetRand(30) - ((float)m_HP + items) / (float)PLAYER_HP * APPER_RAND)) {
			new CItem(0.6f, VGet(m_Pos.x + 200.0f, m_Pos.y, m_Pos.z));
		}
	}
#endif
	if (m_Pos.x > PLAYER_X_MAX) {
		CStage* stage = (CStage*)CTaskManager::Instance()->GetTask(CAST::STAGE);
		stage->MoveScrollX();
		m_Pos.x = PLAYER_X_MAX;
	}
}

//�v���C���[�̃A�j���[�V��������
void CPlayer::AnimPlayer() {
	m_Timer++;
	if (m_Timer % ANIM_TIME == 0) {
		m_Frame++;
		if (m_Frame >= PLAYER_ANIM) {
			m_Frame = 0;
		}
		m_Timer = 0;
	}
}

//�v���C���[�̓����蔻��
bool CPlayer::HitCheck(const VECTOR &_pos, float _zwidth, int _ghandle, e_PLAYERHITS _hits) {
	if (IsHitObject(m_Pos, _pos, PLAYER_Z_WIDTH, _zwidth, m_AnimImage[(int)m_NowState][m_Frame], _ghandle)) {
		//�����蔻����s�����㓖���������̂̎�ނɂ���ď�����ς���
		switch (_hits)
		{
		case e_PLAYERHITS::ITEM_RECOVERY:
			m_HP = min(m_HP++, PLAYER_HP);
			new CEffect(0.7f, (e_EFFECTS)_hits);
			CControlSound::GetInstance()->CreateSE(e_SE::RECOVERY);
			break;
		case e_PLAYERHITS::ITEM_POWERUP:
			//�U���̓A�b�v
			m_Power = min(m_Power++, PLAYER_POWER_MAX);
			m_PowerUpTimer = 0.0f;
			new CEffect(0.7f, (e_EFFECTS)_hits);
			CControlSound::GetInstance()->CreateSE(e_SE::POWERUP);
			break;
		case e_PLAYERHITS::ENEMYSHOT:
			//���G��ԂȂ�_���[�W��H���Ȃ��悤�ɂ���
			if (!m_Inv&&m_NowState != e_PLAYERSTATE::DEATH) {
				m_NowState = e_PLAYERSTATE::DAMAGE;
				m_Frame = 0;
				m_Timer = 0;
				m_HP--;
				m_Inv = true;
				m_InvTimer = 0;
				CControlSound::GetInstance()->CreateSE(e_SE::HIT);
			}
			break;
		case e_PLAYERHITS::NONE:
		default:
			assert(false);
			break;
		}
		return true;
	}
	else {
		return false;
	}
}

//�v���C���[���S���̏����@�v���C���[�L���������X�ɓ����ɂ���
void CPlayer::PlayerDeth() {
	static bool seflag = false;
	if (!seflag) {
		CControlSound::GetInstance()->CreateSE(e_SE::DEATH);
		seflag = true;
	}
	m_Alpha -= ALPHA_STEP;
	if (m_Alpha <= 0) {		//���S�ɓ����ɂȂ�����Delete();
		Delete();
		seflag = false;
	}
}

//�v���C���[�̃W�����v���̏���
void CPlayer::PlayerJumping() {
	//�W�����v���̃A�j���[�V�����͏㏸���Ɨ�����������̂�
	//�A�j���[�V�����̃t���[���̏������قȂ�
	if (m_JumpPower > 0) {				//�㏸���͏㏸���A�j���[�V�������Đ�
		m_Timer++;
		if (m_Timer % ANIM_TIME == 0) {
			m_Frame++;
			if (m_Frame >= PLAYER_JUMPFLAME) {
				m_Frame = PLAYER_JUMPFLAME;
				m_Timer = 0;
			}
			m_Timer = 0;
		}
	}
	if (m_JumpPower <= 0) {			//�������͗����A�j���[�V�����ɐ؂�ւ���
		m_Timer++;
		if (m_Timer % ANIM_TIME == 0) {
			m_Frame++;
			if (m_Frame >= PLAYER_FALLFLAME) {
				m_Frame = PLAYER_FALLFLAME;
				m_Timer = 0;
			}
			m_Timer = 0;
		}
	}
	if (m_Pos.y <= 0) {			//�n�ʂ�艺�Ȃ�
		m_NowState = e_PLAYERSTATE::NEUTRAL;
	}
}

//���G��Ԃ̓_��
void CPlayer::BlinkPlayer() {
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

//�v���C���[�̗̑͂��擾
float CPlayer::GetHP() {
	return (float)m_HP;
}

//�v���C���[�̍��W���擾
const VECTOR& CPlayer::GetPos() {
	return m_Pos;
}

//�v���C���[�̍U���̓A�b�v��Ԃ𒲂ׂ�
//�A�b�v��ԂȂ�true
bool CPlayer::GetPower() {
	if (m_Power >= PLAYER_POWER_MAX) {
		return true;
	}
	return false;
}