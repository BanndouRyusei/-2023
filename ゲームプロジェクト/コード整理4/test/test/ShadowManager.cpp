//---------------------------
//ShadowManager.cpp
//---------------------------
#include"ShadowManager.h"
#include"Stage.h"

CShadowManager* CShadowManager::ms_Instance = nullptr;

//�X�V�^�X�N�̗D��x�͉e��\�����邷�ׂẴN���X�̍X�V�D��x���傫���l
//�`��^�X�N�̗D��x�̓X�e�[�W�̌�ɕ`��ł���悤�ɂ���
CShadowManager::CShadowManager(float _priority) : CTask(1.0f,CAST::SHADOW) {
	m_DrawTask.Init(this, std::bind(&CShadowManager::Draw, this), _priority);
	InitShadowList();
	if (ms_Instance == nullptr) {
		ms_Instance = this;
	}
}

CShadowManager::~CShadowManager() {
	InitShadowList();
	if (ms_Instance != nullptr) {
		ms_Instance = nullptr;
	}
}

//�e�̃��X�g�ɓo�^����Ă���A�b�v�f�[�g�����s
void CShadowManager::Update() {
}

//�e�̃��X�g�ɓo�^����Ă���Draw�����s
void CShadowManager::Draw()const {
	// �e��w�i�����ɕ\�������Ȃ��悤�ɂ���
	SetDrawArea(0, WINDOW_H - (int)GROUND_H, WINDOW_W, WINDOW_H);
	for (auto shadow : m_ShadowList) {
		shadow->Draw();
	}
	// �ݒ�����ɖ߂�
	SetDrawArea(0, 0, WINDOW_W, WINDOW_H);
}

//�e�̃��X�g�ɒǉ�
bool CShadowManager::Regist(CShadow* _shadow) {
	assert(_shadow);
	m_ShadowList.push_back(_shadow);
	return true;
}

//�e�̃��X�g�������
bool CShadowManager::Remove(CShadow* _shadow) {
	assert(_shadow);
	for (auto it = m_ShadowList.begin(); it != m_ShadowList.end(); ++it) {
		if ((*it) == _shadow) {
			m_ShadowList.erase(it);
		}
		return true;
	}
	return false;
}

//�e�̃��X�g����ɂ���
void CShadowManager::InitShadowList() {
	if (!m_ShadowList.empty()) {
		m_ShadowList.clear();
	}
}

//���̃N���X�̃C���X�^���X���擾
CShadowManager* CShadowManager::GetInstance() {
	return ms_Instance;
}