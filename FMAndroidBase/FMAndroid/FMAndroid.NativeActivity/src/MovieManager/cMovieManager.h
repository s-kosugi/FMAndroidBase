#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cMovieManager.h												*/
/*  @brief		:	����Ǘ��N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2019/03/06													*/
/*																				*/
/*==============================================================================*/

#include "..\BaseObject\IBaseObject.h"
#include "MovieID.h"

class cMovieManager : public IBaseObject
{
public:
	// ����̍Đ����
	enum PlayState {
		STATE_WAIT = 0,
		STATE_PLAY,
		STATE_STOP,
	};

	// ������
	void Initialize(void) override;

	// �X�V
	void Update(void) override;

	// �j��
	IBaseObject* Finalize(void) override;

	// ����t�@�C���̓ǂݍ���
	void Load(std::string filename);
	void Load(MovieID id);

	// ����̍Đ��J�n
	void Start( void );

	// ����̍Đ�
	void Play(void);

	// ����̒�~
	void Stop(void);

	// ����f�[�^�̉��
	void Unload( void );

	// ����̍Đ���Ԃ��擾
	inline PlayState GetPlayState(void) { return m_ePlayState; };

private:
	int			m_nGraphHandle;		// ����t�@�C���̃n���h��
	PlayState	m_ePlayState;		// ����̍Đ����

	// ����Đ����̎��s���x
	static const int PLAYMOVIE_FPS = 30;
	// �n���h�����擾
	static const int LOADMOVIE_NONE = -1;

	// ����t�@�C�����e�[�u��
	std::string MOVIEFILE_TABLE[MOVIE_MAX] =
	{
		"data\\movie\\Start.avi",
	};

//-----------------------------------------------------------------------------------------------------
// �V���O���g���p
private:
	cMovieManager(void) { };     //  ������̐������֎~
	cMovieManager(IBaseObject* parent) {  };
	cMovieManager(IBaseObject* parent, const std::string& name) { };
	~cMovieManager(void) {};   // ������̍폜���֎~(�f�X�g���N�^��private�ɂ��鎖�ŊO���폜�s��)
	cMovieManager(const cMovieManager& t) {};       // �I�u�W�F�N�g�̕����֎~(�R�s�[�R���X�g���N�^�̃I�[�o���C�h)
	cMovieManager& operator = (const cMovieManager& t) { return *this; };  // �I�u�W�F�N�g�̕����֎~(������Z�q�̃I�[�o�[���[�h)
public:

	static cMovieManager& GetInstance(void) {
		static cMovieManager instance;   // �B��̎��̂ł���I�u�W�F�N�g�Astatic�ϐ����g�p���鎖�łP�̋��L�̕ϐ��ƂȂ�
		return instance;    // ��ɋ��ʂ̃C���X�^���X��Ԃ�
	};
//-----------------------------------------------------------------------------------------------------
};