/*******************************************************************************
* �^�C�g��:		���C������
* �v���O������:	Main.h
* �쐬��:		GP11A331 4�� �Ɍ��C�H
* �쐬��:		2016/01/21
********************************************************************************
* �X�V����:		- 2016/01/22	�Ɍ��C�H
*					- V1.00		Initial Version
*******************************************************************************/
#ifndef _MAIN_H_
#define _MAIN_H_

#define USE_SOUND		// �T�E���h�g�p�̗L��
//#undef USE_SOUND
//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <windows.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800)
#include "dinput.h"
#include "input.h"

#ifdef USE_SOUND
#include "xaudio2.h"		// XAudio2�֘A�̃w�b�_�[
#endif

//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************
#if 1	// [������"0"�ɂ����ꍇ�A"�\���v���p�e�B" -> "�����J" -> "����" -> "�ǉ��̈ˑ��t�@�C��"�ɑΏۃ��C�u������ݒ肷��]
#pragma comment (lib, "d3d9.lib")		// �`�揈���ɕK�v
#pragma comment (lib, "d3dx9.lib")		// [d3d9.lib]�̊g�����C�u����
#pragma comment (lib, "dxguid.lib")		// DirectX�R���|�[�l���g�g�p�ɕK�v
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "winmm.lib")
#endif

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

#if 0
#define SCREEN_WIDTH					(1760)//(1280)	// �E�C���h�E�̕�
#define SCREEN_HEIGHT					(990)//(720)	// �E�C���h�E�̍���
#else
#define SCREEN_WIDTH					(800)//(1280)	// �E�C���h�E�̕�
#define SCREEN_HEIGHT					(450)//(720)	// �E�C���h�E�̍���
#endif
#define SCREEN_WIDTH_DIFFERENCE			(10)
#define SCREEN_HEIGHT_DIFFERENCE		(10)

#define NUM_VERTEX (4)
#define NUM_POLYGON (2)

#define SAFE_RELEASE(ptr)			{ if(ptr) { (ptr)->Release(); (ptr) = NULL; } }

/*******************************************************************************
* �\���̒�`
*******************************************************************************/
// ��L�Q�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 vtx;	// ���_���W
	float		rhw;	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	D3DCOLOR	col;	// ���ˌ�(���_�J���[)
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
} VERTEX_2D;

// ��L�R�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 vtx;	// ���_���W
	D3DXVECTOR3 nor;	// �@���x�N�g��
	D3DCOLOR	col;	// ���ˌ�
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
} VERTEX_3D;

typedef struct SCREEN
{
	float nWidth;
	float nHeight;
};

typedef struct
{
	LPDIRECT3DVERTEXBUFFER9	pD3DVtxBuff;	//���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
	D3DXVECTOR3 pos;						//�t���[���A�|�C���g�̂Q��
	D3DXVECTOR2 size;
	D3DXCOLOR	col;
	bool		bUse;
	int			nTransCnt;
	int			nCurKeyFrame;
	int			nNextKeyFrame;
} IMAGE_2D_STRUCT;

typedef struct
{
	D3DXMATRIX mtxWorld;					// ���[���h�}�g���b�N�X
	D3DXMATRIX mtxLocal;					// ���[�J���}�g���b�N�X
	LPDIRECT3DVERTEXBUFFER9	pD3DVtxBuff;	//���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
	D3DXVECTOR3 pos;						//�t���[���A�|�C���g�̂Q��
	D3DXVECTOR2 size;
	D3DXCOLOR	col;
	bool		bUse;
} IMAGE_3D_STRUCT;

/*******************************************************************************
* �񋓑̒�`
*******************************************************************************/
typedef enum
{
	MODE_TITLE = 0,
	MODE_GAME,
	MODE_RESULT,
	MODE_MAX
}MODE;

typedef enum
{
	FLICK_ON = 0,
	FLICK_OFF
} FLICK;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LPDIRECT3DDEVICE9 GetDevice(void);
MODE GetMainMode(void);
void SetMode(MODE mode);
void EndMode(void);
HWND GetHandleWindow(void);
HINSTANCE GetHandleInstance(void);
void UpdateWindowSize(void);
SCREEN GetScreenInfo(void);
void InitWindowSize(void);

#endif