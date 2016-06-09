/*******************************************************************************
* �^�C�g��:		Texture����
* �v���O������:	Texture.cpp
* �쐬��:		GP11A331 4 �Ɍ��C�H
* �쐬��:		2016/01/29
********************************************************************************
* �X�V����:		- 2016/02/23	�Ɍ�
*					- V1.00		Initial Version
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "Texture.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

/*******************************************************************************
* �\���̒�`
*******************************************************************************/

/*******************************************************************************
* �v���g�^�C�v�錾
*******************************************************************************/

/*******************************************************************************
* �O���[�o���ϐ�
*******************************************************************************/
LPDIRECT3DTEXTURE9		g_pD3DTextureSpace[MAX_SPACE_TEXTURE];
LPDIRECT3DTEXTURE9		g_pD3DTextureTitle[MAX_TITLE_TEXTURE];
LPDIRECT3DTEXTURE9		g_pD3DTextureResult[MAX_RESULT_TEXTURE];
LPDIRECT3DTEXTURE9		g_pD3DTextureUI[MAX_UI_TEXTURE];
LPDIRECT3DTEXTURE9		g_pD3DTextureUtility[MAX_UTILITY_TEXTURE];			

/* 3D��ԓ��̃e�N�X�`�� */
char *g_SpaceTexName[MAX_SPACE_TEXTURE] = 
{// �e�N�X�`���t�@�C����

};
/* �^�C�g���e�N�X�`�� */
char *g_TitleTexName[MAX_TITLE_TEXTURE] = 
{// �e�N�X�`���t�@�C����

};
/* ���U���g�e�N�X�`�� */
char *g_ResultTexName[MAX_RESULT_TEXTURE] = 
{// �e�N�X�`���t�@�C����
	
};
/* UI�e�N�X�`�� */
char *g_UITexName[MAX_UI_TEXTURE] = 
{// �e�N�X�`���t�@�C����
	"data/TEXTURE/OptionWindow.png",
	"data/TEXTURE/BGMmixerber.png",
	"data/TEXTURE/SEmixerber.png",
	"data/TEXTURE/MenuberIndicate.png",
	"data/TEXTURE/CheckBox_Checkin.png",
	"data/TEXTURE/CheckBox_Checkout.png",
	"data/TEXTURE/OptionWindowCloseButton.png",
	"data/TEXTURE/BGMMixerBarIcon.png"
};
/* ���[�e�B���e�B�e�N�X�`�� */
char *g_UtilityTexName[MAX_UTILITY_TEXTURE] = 
{// �e�N�X�`���t�@�C����
	
};

/*******************************************************************************
�֐���:	HRESULT InitTexture(void)
����:	�Ȃ�
�߂�l:	HRESULT�^	S_OK:����I��
					E_FAIL:���������s
����:	Texture�̏�����
*******************************************************************************/
HRESULT InitTexture(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �^�C�g���e�N�X�`���̓ǂݍ���
	for (int nIdxTexture = 0 ; nIdxTexture < MAX_TITLE_TEXTURE ; nIdxTexture++)
	{
		D3DXCreateTextureFromFile(pDevice, g_TitleTexName[nIdxTexture], &g_pD3DTextureTitle[nIdxTexture]);
	}
	// ���U���g�e�N�X�`���̓ǂݍ���
	for (int nIdxTexture = 0 ; nIdxTexture < MAX_RESULT_TEXTURE ; nIdxTexture++)
	{
		D3DXCreateTextureFromFile(pDevice, g_ResultTexName[nIdxTexture], &g_pD3DTextureResult[nIdxTexture]);
	}
	// 3D��ԓ��̃e�N�X�`���̓ǂݍ���
	for (int nIdxTexture = 0 ; nIdxTexture < MAX_SPACE_TEXTURE ; nIdxTexture++)
	{
		D3DXCreateTextureFromFile(pDevice, g_SpaceTexName[nIdxTexture], &g_pD3DTextureSpace[nIdxTexture]);
	}
	// UI�e�N�X�`���̓ǂݍ���
	for (int nIdxTexture = 0 ; nIdxTexture < MAX_UI_TEXTURE ; nIdxTexture++)
	{
		D3DXCreateTextureFromFile(pDevice, g_UITexName[nIdxTexture], &g_pD3DTextureUI[nIdxTexture]);
	}
	// ���[�e�B���e�B�e�N�X�`���̓ǂݍ���
	for (int nIdxTexture = 0 ; nIdxTexture < MAX_UTILITY_TEXTURE ; nIdxTexture++)
	{
		D3DXCreateTextureFromFile(pDevice, g_UtilityTexName[nIdxTexture], &g_pD3DTextureUtility[nIdxTexture]);
	}
	

	return S_OK;
}
/*******************************************************************************
�֐���:	void UninitTexture(void)
����:	�Ȃ�
�߂�l:	�Ȃ�
����:	Texture�̏I������
*******************************************************************************/
void UninitTexture(void)
{
	// �^�C�g���e�N�X�`���̏I��
	for (int nIdxTexture = 0 ; nIdxTexture < MAX_TITLE_TEXTURE ; nIdxTexture++)
	{
		if(g_pD3DTextureTitle[nIdxTexture] != NULL)
		{
			g_pD3DTextureTitle[nIdxTexture] -> Release();
			g_pD3DTextureTitle[nIdxTexture] = NULL;
		}
	}
	// ���U���g�e�N�X�`���̏I��
	for (int nIdxTexture = 0 ; nIdxTexture < MAX_RESULT_TEXTURE ; nIdxTexture++)
	{
		if(g_pD3DTextureResult[nIdxTexture] != NULL)
		{
			g_pD3DTextureResult[nIdxTexture] -> Release();
			g_pD3DTextureResult[nIdxTexture] = NULL;
		}
	}
	// 3D��ԓ��̃e�N�X�`���̏I��
	for (int nIdxTexture = 0 ; nIdxTexture < MAX_SPACE_TEXTURE ; nIdxTexture++)
	{
		if(g_pD3DTextureSpace[nIdxTexture] != NULL)
		{
			g_pD3DTextureSpace[nIdxTexture] -> Release();
			g_pD3DTextureSpace[nIdxTexture] = NULL;
		}
	}
	// UI�e�N�X�`���̏I��
	for (int nIdxTexture = 0 ; nIdxTexture < MAX_UI_TEXTURE ; nIdxTexture++)
	{
		if(g_pD3DTextureUI[nIdxTexture] != NULL)
		{
			g_pD3DTextureUI[nIdxTexture] -> Release();
			g_pD3DTextureUI[nIdxTexture] = NULL;
		}
	}
	// ���[�e�B���e�B�e�N�X�`���̏I��
	for (int nIdxTexture = 0 ; nIdxTexture < MAX_UTILITY_TEXTURE ; nIdxTexture++)
	{
		if(g_pD3DTextureUtility[nIdxTexture] != NULL)
		{
			g_pD3DTextureUtility[nIdxTexture] -> Release();
			g_pD3DTextureUtility[nIdxTexture] = NULL;
		}
	}
}
/*******************************************************************************
�֐���:	LPDIRECT3DTEXTURE9 *GetTitleTexture(void)
����:	�Ȃ�
�߂�l:	LPDIRECT3DTEXTURE9�^	g_pD3DTextureTitle[0]�̃A�h���X
����:	�^�C�g���e�N�X�`���̃|�C���^�z��̐擪�A�h���X���擾
*******************************************************************************/
LPDIRECT3DTEXTURE9 *GetTitleTexture(void)
{
	// �^�C�g���e�N�X�`���̃|�C���^�z��̐擪�A�h���X��Ԃ�
	return &g_pD3DTextureTitle[0];
}
/*******************************************************************************
�֐���:	LPDIRECT3DTEXTURE9 *GetResultTexture(void)
����:	�Ȃ�
�߂�l:	LPDIRECT3DTEXTURE9�^	g_pD3DTextureResult[0]�̃A�h���X
����:	�^�C�g���e�N�X�`���̃|�C���^�z��̐擪�A�h���X���擾
*******************************************************************************/
LPDIRECT3DTEXTURE9 *GetResultTexture(void)
{
	// ���U���g�e�N�X�`���̃|�C���^�z��̐擪�A�h���X��Ԃ�
	return &g_pD3DTextureResult[0];
}
/*******************************************************************************
�֐���:	LPDIRECT3DTEXTURE9 *GetOnFieldTexture(void)
����:	�Ȃ�
�߂�l:	LPDIRECT3DTEXTURE9�^	g_pD3DTextureSpace[0]�̃A�h���X
����:	3D��ԓ��̃e�N�X�`���ւ̃|�C���^�z��̐擪�A�h���X���擾
*******************************************************************************/
LPDIRECT3DTEXTURE9 *GetSpaceTexture(void)
{
	// 3D��ԓ��̃e�N�X�`���ւ̃|�C���^�z��̐擪�A�h���X��Ԃ�
	return &g_pD3DTextureSpace[0];
}
/*******************************************************************************
�֐���:	LPDIRECT3DTEXTURE9 *GetUITexture(void)
����:	�Ȃ�
�߂�l:	LPDIRECT3DTEXTURE9�^	g_pD3DTextureUI[0]�̃A�h���X
����:	UI�e�N�X�`���ւ̃|�C���^�z��̐擪�A�h���X���擾
*******************************************************************************/
LPDIRECT3DTEXTURE9 *GetUITexture(void)
{
	// UI�e�N�X�`���ւ̃|�C���^�z��̐擪�A�h���X��Ԃ�
	return &g_pD3DTextureUI[0];
}
/*******************************************************************************
�֐���:	LPDIRECT3DTEXTURE9 *GetUtilityTexture(void)
����:	�Ȃ�
�߂�l:	LPDIRECT3DTEXTURE9�^	g_pD3DTextureUtility[0]�̃A�h���X
����:	���[�e�B���e�B�e�N�X�`���ւ̃|�C���^�z��̐擪�A�h���X���擾
*******************************************************************************/
LPDIRECT3DTEXTURE9 *GetUtilityTexture(void)
{
	// ���[�e�B���e�B�e�N�X�`���ւ̃|�C���^�z��̐擪�A�h���X��Ԃ�
	return &g_pD3DTextureUtility[0];
}
