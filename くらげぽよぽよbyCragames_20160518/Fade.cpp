/*******************************************************************************
* �^�C�g��:		Fade����
* �v���O������:	Fade.cpp
* �쐬��:		GP11A331 4 �Ɍ��C�H
* �쐬��:		2015/11/16
********************************************************************************
* �X�V����:		- 2015/11/16	 �Ɍ�
*					- V1.00		Initial Version
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "Fade.h"
#include "input.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FADE_POS_X (0)// �|���S���̍���
#define FADE_POS_Y (0) // �|���S���̍���
#define FADE_SIZE_X (SCREEN_WIDTH) // �|���S���T�C�YX
#define FADE_SIZE_Y (SCREEN_HEIGHT) // �|���S���T�C�YY
#define FADE_TEXTURENAME ""

/*******************************************************************************
* �\���̒�`
*******************************************************************************/

/*******************************************************************************
* �v���g�^�C�v�錾
*******************************************************************************/
HRESULT MakeVertexFade(LPDIRECT3DDEVICE9 pDevice);

/*******************************************************************************
* �O���[�o���ϐ�
*******************************************************************************/
LPDIRECT3DVERTEXBUFFER9		g_pVtxBufferFade = NULL;	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
LPDIRECT3DTEXTURE9			g_pTextureFade = NULL;		// �e�N�X�`���ւ̃|�C���^
int							g_AlphaValue = 0;			// ���l
int							g_fade = FADE_NONE;
/*******************************************************************************
�֐���:	HRESULT InitFade(void)
����:	
�߂�l:	HRESULT�^	S_OK:����I��
					E_FAIL:���������s
����:	FADE�̏�����
*******************************************************************************/
HRESULT InitFade(void) // ���_�̃f�[�^���\���̔z��ɐݒ�
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// ���_���̍쐬
	if(FAILED(MakeVertexFade(pDevice)))
	{
		return E_FAIL;
	}
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		FADE_TEXTURENAME,
		&g_pTextureFade
	);
	return S_OK;
}
/*******************************************************************************
�֐���:	HRESULT MakeVertexFade(LPDIRECT3DDEVICE9 pDevice)
����:	LPDIRECT3DDEVICE9 pDevice
�߂�l:	HRESULT�^	S_OK:����I��
					E_FAIL:���������s
����:	FADE���_�̍쐬
*******************************************************************************/
HRESULT MakeVertexFade(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@���쐬
	if(FAILED(pDevice -> CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,
											D3DUSAGE_WRITEONLY,
											FVF_VERTEX_2D,
											D3DPOOL_MANAGED,
											&g_pVtxBufferFade,
											NULL)))
	{
		return E_FAIL;
	}

	{// ���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;
		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pVtxBufferFade -> Lock(0,0,(void**)&pVtx,0);
		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(FADE_POS_X, FADE_POS_Y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(FADE_POS_X + FADE_SIZE_X, FADE_POS_Y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(FADE_POS_X, FADE_POS_Y + FADE_SIZE_Y, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(FADE_POS_X + FADE_SIZE_X, FADE_POS_Y + FADE_SIZE_Y, 0.0f);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 0);
		pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 0);
		pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 0);
		pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 0);
		
		// �e�N�X�`�����W�w��
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		g_pVtxBufferFade -> Unlock();
	}
	return S_OK;
}
/*******************************************************************************
�֐���:	void UpdateFade(void)
����:	�Ȃ�
�߂�l:	�Ȃ�
����:	FADE�̍X�V����
*******************************************************************************/
void UpdateFade(void)
{
	{// ���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;
		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pVtxBufferFade -> Lock(0,0,(void**)&pVtx,0);
		switch(g_fade)
		{
		case FADE_NONE:
			break;
		case FADE_IN:
			if(g_AlphaValue > 0)
			{
				g_AlphaValue -= 8;
			}
			if(g_AlphaValue <= 0)// ���l���O�`�Q�T�T�Ɏ��܂�悤�ɐݒ�
			{
				g_AlphaValue = 0;
				g_fade = FADE_NONE;
			}
			break;
		case FADE_OUT:
			if(g_AlphaValue < 255)
			{
				g_AlphaValue += 8;
			}
			if(g_AlphaValue >= 255)
			{
				g_AlphaValue = 255;
			}
			break;
		default:
			break;
		}
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, g_AlphaValue);
		pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, g_AlphaValue);
		pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, g_AlphaValue);
		pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, g_AlphaValue);
		// ���_�f�[�^���A�����b�N����
		g_pVtxBufferFade -> Unlock();
	}
}
/*******************************************************************************
�֐���:	void DrawFade(void)
����:	�Ȃ�
�߂�l:	�Ȃ�
����:	FADE�̕`�揈��
*******************************************************************************/
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice -> SetStreamSource(0, g_pVtxBufferFade, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g
	pDevice -> SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice -> SetTexture(0,g_pTextureFade);

	// �|���S���̕`��
	pDevice -> DrawPrimitive(
							D3DPT_TRIANGLESTRIP,
							0,
							NUM_POLYGON);

}
/*******************************************************************************
�֐���:	void UninitFade(void)
����:	�Ȃ�
�߂�l:	�Ȃ�
����:	FADE�̏I������
*******************************************************************************/
void UninitFade(void)
{
	if(g_pTextureFade != NULL)
	{
		g_pTextureFade -> Release();
		g_pTextureFade = NULL;
	}
	if(g_pVtxBufferFade != NULL)
	{
		g_pVtxBufferFade -> Release();
		g_pVtxBufferFade = NULL;
	}
}
/*******************************************************************************
�֐���:	void SetFade(FADE fade)
����:	�Ȃ�
�߂�l:	�Ȃ�
����:	FADE�̃Z�b�g
*******************************************************************************/
void SetFade(FADE fade)
{
	g_fade = fade;
}
/*******************************************************************************
�֐���:	int GetAlphaValue(void)
����:	�Ȃ�
�߂�l:	int
����:	���l���擾
*******************************************************************************/
int GetAlphaValue(void)
{
	return g_AlphaValue;
}