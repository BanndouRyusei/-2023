//---------------------------
//ControlPlayer.cpp
//---------------------------
#include"Player.h"
#include"Stage.h"
#include"PlayerShot.h"
#include"UI.h"

//�萔
const float PLAYER_SHOT_POSY = 60.0f;			//�v���C���[�V���b�g�̍���(�摜�̍����ɍ��킹��)
const float GRAVITY = 30.0f;		//�d��
const float JUMP_POWER = 920.0f;		//�W�����v��

CPlayer::CPlayer(float _priority) :CCharaBase(_priority, CAST::PLAYER),m_AnimImage(),m_Shadow() {
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_HP = PLAYER_HP;
	char buf[30];
	for (int i = 0; i < (int)e_PLAYERSTATE::NONE; i++) {
		sprintf_s(buf, "Data\\img\\Player_Anim%d.png", i);
		LoadDivGraph(buf, PLAYER_ANIM, PLAYER_ANIM, 1, PLAYER_W, PLAYER_H, m_AnimImage[i]);
		if (m_AnimImage[i][0] == -1)assert(false);
	}
	m_NowState = e_PLAYERSTATE::NEUTRAL;
	m_Speed = 4.0f;
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
	m_Shadow.SetShadow(m_ShadowImage, m_Pos, 228.0f);
}

CPlayer::~CPlayer() {
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
		//ShotPlayer(key);
		//PlayerJump(key);
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

	m_Shadow.CharaPosGet(m_Pos);

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
	printfDx("�v���C���[�̗̑́@%d\n", m_HP);
	printfDx("������@ �����L�[�ňړ�(X,Z),Z�L�[�Œe����,�X�y�[�X�L�[�ŃW�����v,X�L�[�Ń_���[�W����\n");
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
			m_Frame = 1;			//�㏸���A�j���[�V�����t���[���ɂ���
			m_Timer = 0;
			m_JumpPower = JUMP_POWER;
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
	if (IsKeyTrigger(_key, PAD_INPUT_B)) {			//���Ń_���[�W���[�V�����𗬂�
		m_NowState = e_PLAYERSTATE::DAMAGE;
		m_Frame = 0;
		m_Timer = 0;
		m_HP--;
		m_Inv = true;
		m_InvTimer = 0;
	}
	if (m_Pos.x > PLAYER_X_MAX) {
		CStage* stage = (CStage*)CTaskManager::Instance()->GetTask(CAST::STAGE);
		stage->MoveScrollX();
		m_Pos.x = PLAYER_X_MAX;
	}
}

//�v���C���[�̒e���ˏ���
/*void CPlayer::ShotPlayer(int _key) {
	if (_key&PAD_INPUT_A) {			//Z�L�[��������
		m_NowState = e_PLAYERSTATE::ATTACK;
		m_Frame = 0;
		m_Timer = 0;
		m_ShotFlag = false;
	}
}*/

//�v���C���[�̃A�j���[�V��������
void CPlayer::AnimPlayer() {
	m_Timer++;
	if (m_Timer % (MAX_FPS / 3) == 0) {
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
		printfDx("Hit\n");
		return true;
	}
	else {
		return false;
	}

	//�����蔻����s�����㓖���������̂̎�ނɂ���ď�����ς���
	/*switch (_hits)
	{
	case e_PLAYERHITS::ENEMYSHOT:
		//���G��ԂȂ�_���[�W��H���Ȃ��悤�ɂ���
		m_NowState = e_PLAYERSTATE::DAMAGE;
		m_Frame = 0;
		m_Timer = 0;
		m_HP--;
		break;
	case e_PLAYERHITS::ITEM_RECOVERY:
		m_HP++;
		break;
	case e_PLAYERHITS::ITEM_POWERUP:
		break;
	case e_PLAYERHITS::NONE:
	default:
		assert(false);
		break;
	}*/
}

//�v���C���[���S���̏����@�v���C���[�L���������X�ɓ����ɂ���
void CPlayer::PlayerDeth() {
	m_Alpha -= ALPHA_STEP;
	if (m_Alpha <= 0)			//���S�ɓ����ɂȂ�����Delete();
		Delete();
}

//�v���C���[�̃W�����v
/*void CPlayer::PlayerJump(int _key) {
	if (_key&PAD_INPUT_10) {	//�W�����v��Ԃ�
		m_NowState = e_PLAYERSTATE::JUMP;
		m_Frame = 1;			//�㏸���A�j���[�V�����t���[���ɂ���
		m_Timer = 0;
		m_JumpPower = JUMP_POWER;
	}
}*/

//�v���C���[�̃W�����v���̏���
void CPlayer::PlayerJumping() {
	//�W�����v���̃A�j���[�V�����͏㏸���Ɨ�����������̂�
	//�A�j���[�V�����̃t���[���̏������قȂ�
	if (m_JumpPower <= 0) {			//�������͗����t���[���ɐ؂�ւ���
		m_Frame = 2;
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