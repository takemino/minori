/*******************************************************************************
* �^�C�g��:		�e����
* �v���O������:	shadow.cpp
* �쐬��:		GP11A331 4�� �Ɍ��C�H
* �쐬��:		2015/11/10
********************************************************************************
* �X�V����:		- 2015/11/10	�Ɍ��C�H
*					- V1.00		Initial Version
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "Shadow.h"
#include "Texture.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	SHADOW_SIZE_X		(50.0f)							// �e�̕�
#define	SHADOW_SIZE_Z		(50.0f)							// �e�̍���

#define	MAX_SHADOW			(128)							// �e�ő吔

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// ��]
	bool bUse;				// �g�p���Ă��邩�ǂ���
}SHADOW;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;	// ���_�o�b�t�@�ւ̃|�C���^

SHADOW	g_aShadow[MAX_SHADOW];						// �e���[�N

//=============================================================================
// ����������
//=============================================================================
HRESULT InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	SHADOW *pShadow;

	// �e�\���̂̃|�C���^�ɉe���[�N�̐擪�A�h���X����
	pShadow = &g_aShadow[0];

	// �e���[�N�̏�����
	for(int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++, pShadow++)
	{
		pShadow->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pShadow->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pShadow->bUse = false;
	}

	// ���_���̍쐬
	MakeVertexShadow(pDevice);

	return S_OK;
}
/*******************************************************************************
�֐���:	void InitShadowInGame(void)
����:	�Ȃ�
�߂�l:	�Ȃ�
����:	�V���h�E�̃Q�[����������
*******************************************************************************/
void InitShadowInGame(void)
{
	SHADOW *pShadow;

	// �e�\���̂̃|�C���^�ɉe���[�N�̐擪�A�h���X����
	pShadow = &g_aShadow[0];

	// �e���[�N�̏�����
	for(int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++, pShadow++)
	{
		pShadow->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pShadow->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pShadow->bUse = false;
	}
}
//=============================================================================
// �I������
//=============================================================================
void UninitShadow(void)
{
	if(g_pVtxBuffShadow != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateShadow(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LPDIRECT3DTEXTURE9* pSpaceTex = GetSpaceTexture();
	D3DXMATRIX mtxRot, mtxTranslate;
	SHADOW *pShadow;

	// ���Z����
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);	 
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���� = �]����(DEST) - �]����(SRC)
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �e�\���̂̃|�C���^�ɉe���[�N�̐擪�A�h���X����
	pShadow = &g_aShadow[0];
	
	for(int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++, pShadow++)
	{
		if(pShadow->bUse)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&pShadow->mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, pShadow->rot.y, pShadow->rot.x, pShadow->rot.z);
			D3DXMatrixMultiply(&pShadow->mtxWorld, &pShadow->mtxWorld, &mtxRot);
			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, pShadow->pos.x, pShadow->pos.y, pShadow->pos.z);
			D3DXMatrixMultiply(&pShadow->mtxWorld, &pShadow->mtxWorld, &mtxTranslate);
			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice -> SetTransform(D3DTS_WORLD, &pShadow->mtxWorld);
			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice -> SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));
				// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice -> SetFVF(FVF_VERTEX_3D);
			// �e�N�X�`���̐ݒ�
			pDevice -> SetTexture(0,pSpaceTex[TEX_SHADOW]);
			// �|���S���̕`��
			pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̕`����
											0,				// �`����J�n���钸�_�i���o�[
											NUM_POLYGON);	// �|���S����
		}
	}

	// �ʏ�u�����h
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);			// ���u�����h���s��
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��D3DBLEND_SRCALPHA
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��	// ���� = �]����(SRC) + �]����(DEST)D3DBLEND_INVSRCALPHA
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
HRESULT MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@���쐬
	if(FAILED(pDevice -> CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_SHADOW,
											D3DUSAGE_WRITEONLY,
											FVF_VERTEX_3D,
											D3DPOOL_MANAGED,
											&g_pVtxBuffShadow,
											NULL)))
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pVtxBuffShadow->Lock(0,0,(void**)&pVtx,0);

		for(int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++, pVtx += 4)
		{
			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(-SHADOW_SIZE_X / 2, 0.0f, SHADOW_SIZE_Z / 2);
			pVtx[1].vtx = D3DXVECTOR3( SHADOW_SIZE_X / 2, 0.0f, SHADOW_SIZE_Z / 2);
			pVtx[2].vtx = D3DXVECTOR3(-SHADOW_SIZE_X / 2, 0.0f, -SHADOW_SIZE_Z / 2);
			pVtx[3].vtx = D3DXVECTOR3( SHADOW_SIZE_X / 2, 0.0f, -SHADOW_SIZE_Z / 2);
			// �@���̐ݒ�
			pVtx[0].nor	= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].nor	= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[2].nor	= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].nor	= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			// ���_�J���[�̐ݒ�
			pVtx[0].col	= D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.5f);
			pVtx[1].col	= D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.5f);
			pVtx[2].col	= D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.5f);
			pVtx[3].col	= D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.5f);
			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		// ���_�f�[�^���A�����b�N����
		g_pVtxBuffShadow->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexShadow(int nIdxShadow, float fSizeX, float fSizeZ)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pVtxBuffShadow->Lock(0,0,(void**)&pVtx,0);

		// pVtx���C���f�b�N�X���Y����
		pVtx += NUM_VERTEX * nIdxShadow;

		// ���_���W�̐ݒ�i������p���Đݒ�j
		pVtx[0].vtx = D3DXVECTOR3(-fSizeX / 2, 0.0f, fSizeZ / 2);
		pVtx[1].vtx = D3DXVECTOR3( fSizeX / 2, 0.0f, fSizeZ / 2);
		pVtx[2].vtx = D3DXVECTOR3(-fSizeX / 2, 0.0f, -fSizeZ / 2);
		pVtx[3].vtx = D3DXVECTOR3( fSizeX / 2, 0.0f, -fSizeZ / 2);

		// ���_�f�[�^���A�����b�N����
		g_pVtxBuffShadow->Unlock();
	}
}

//=============================================================================
// ���_�J���[�̐ݒ�
//=============================================================================
void SetColorShadow(int nIdxShadow, D3DXCOLOR col)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pVtxBuffShadow->Lock(0,0,(void**)&pVtx,0);

		// pVtx���C���f�b�N�X���Y����
		pVtx += NUM_VERTEX * nIdxShadow;

		// ���_�J���[�̐ݒ�
		pVtx[0].col	= col;
		pVtx[1].col	= col;
		pVtx[2].col	= col;
		pVtx[3].col	= col;

		// ���_�f�[�^���A�����b�N����
		g_pVtxBuffShadow->Unlock();
	}
}

//=============================================================================
// �e�̍쐬
//=============================================================================
int CreateShadow(D3DXVECTOR3 pos, float fSizeX, float fSizeZ)
{
	SHADOW *pShadow;
	int nIdxShadow = -1;

	// �e�\���̂̃|�C���^�ɉe���[�N�̐擪�A�h���X����
	pShadow = &g_aShadow[0];

	for(int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++, pShadow++)
	{
		if(!pShadow->bUse)
		{
			// �e�̈ʒu�A��]�p��ݒ�
			pShadow->pos = pos;
			pShadow->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			// �e���[�N���g�p��ԂɕύX
			pShadow->bUse = true;
			// ���_���W�̐ݒ�֐����Ăяo��
			SetVertexShadow(nCntShadow, fSizeX, fSizeZ);
			// �e�̔ԍ���nIdxShadow�ɐݒ�
			nIdxShadow = nCntShadow;
			break;
		}
	}

	// nIdxShadow��Ԃ�
	return nIdxShadow;
}

//=============================================================================
// �e�̔j��
//=============================================================================
void ReleaseShadow(int nIdxShadow)
{
	SHADOW *pShadow;
	pShadow = &g_aShadow[nIdxShadow];

	if(nIdxShadow < MAX_SHADOW) // �w�肳�ꂽ�e���e���[�N�̌��Ȃ����ǂ���
	{
		// �e���[�N�𖢎g�p��Ԃɐݒ�
		pShadow->bUse = false;
	}
}

//=============================================================================
// �ʒu�̐ݒ�
//=============================================================================
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos)
{
	SHADOW *pShadow;
	pShadow = &g_aShadow[nIdxShadow];
	// �w�肳�ꂽ�e���[�N�Ɉʒu��ݒ�
	pShadow->pos = pos;
	pShadow->pos.y = 0.2f;
}

