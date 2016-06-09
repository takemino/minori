/*******************************************************************************
* �^�C�g��:		Texture�w�b�_�[�t�@�C��
* �v���O������:	Texture.h
* �쐬��:		GP11A331 4 �Ɍ��C�H
* �쐬��:		2016/01/29
********************************************************************************
* �X�V����:		- 2016/02/23	GP11A331 4 �Ɍ��C�H
*					- V1.00		Initial Version
*******************************************************************************/
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "Main.h"

/*******************************************************************************
* �\���̒�`
*******************************************************************************/

/*******************************************************************************
* �񋓑̒�`
*******************************************************************************/
typedef enum
{
	TEX_SHADOW = 0,
	MAX_SPACE_TEXTURE
} SPACE_TEXTURE;

typedef enum
{
	UI_TEXTURE_OPTION_WINDOW = 0,					// �I�v�V�����̃E�B���h�E
	UI_TEXTURE_BGM_MIXERBAR,							// BGM�̃~�L�T�[�o�[
	UI_TEXTURE_SE_MIXERBAR,							// SE�̃~�L�T�[�o�[
	UI_TEXTURE_MENUBER_INDICATE,						// ���j���[�o�[��\������`�F�b�N�{�b�N�X
	UI_TEXTURE_CHECKBOX_CHECKIN,						// �`�F�b�N�����Ă�`�F�b�N�{�b�N�X
	UI_TEXTURE_CHECKBOX_CHECKOUT,					// �`�F�b�N�����ĂȂ��`�F�b�N�{�b�N�X
	UI_TEXTURE_OPTION_WINDOW_CLOSEBUTTON,				// �I�v�V�����̃E�B���h�E�̕���{�^��
	UI_TEXTURE_MIXERBAR_ICON,						// BGM,SE�~�L�T�[�o�[�̃A�C�R��
	MAX_UI_TEXTURE
} UI_TEXTURE, USER_INTERFACE_TEXTURE;

typedef enum
{
	MAX_UTILITY_TEXTURE = 1
} UTILITY_TEXTURE;

typedef enum
{
	MAX_TITLE_TEXTURE = 1
} TITLE_TEXTURE;

typedef enum
{
	MAX_RESULT_TEXTURE = 1
} RESULT_TEXTURE;

//*****************************************************************************
// �}�N����`
//*****************************************************************************

/*******************************************************************************
* �v���g�^�C�v�錾
*******************************************************************************/
HRESULT InitTexture(void);
void UninitTexture(void);
LPDIRECT3DTEXTURE9 *GetTitleTexture(void);
LPDIRECT3DTEXTURE9 *GetResultTexture(void);
LPDIRECT3DTEXTURE9 *GetSpaceTexture(void);
LPDIRECT3DTEXTURE9 *GetUITexture(void);
LPDIRECT3DTEXTURE9 *GetUtilityTexture(void);
#endif