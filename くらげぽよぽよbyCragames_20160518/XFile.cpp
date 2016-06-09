/*******************************************************************************
* �^�C�g��:		X�t�@�C������
* �v���O������:	XFile.cpp
* �쐬��:		GP11A331 4�� �Ɍ��C�H
* �쐬��:		2016/01/18
********************************************************************************
* �X�V����:		- 2016/01/18	�Ɍ��C�H
*					- V1.00		Initial Version
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "XFile.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
XFILE g_aJellyfishXFile[MAX_JELLYFISH_XFILE];

char *g_pJellyfishXFileName[MAX_JELLYFISH_XFILE] = 
{ // X�t�@�C����
	{"data/XFILE/TestModel.x"},
};

//=============================================================================
// ����������
//=============================================================================
HRESULT InitXFile(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �v���C���[�L�����̓ǂݍ���
	for(int nIdx = 0; nIdx < MAX_JELLYFISH_XFILE; nIdx++)
	{
		 g_aJellyfishXFile[nIdx].pD3DXMesh = NULL;	
		 g_aJellyfishXFile[nIdx].pD3DXBuffMate = NULL;
		 g_aJellyfishXFile[nIdx].nNumMate = 0;
		 g_aJellyfishXFile[nIdx].pD3DTexture = NULL;	

		// X�t�@�C���̓ǂݍ���
		if(FAILED(D3DXLoadMeshFromX(
								g_pJellyfishXFileName[nIdx],			// �ǂݍ��ރ��f���t�@�C����(X�t�@�C��)
								D3DXMESH_SYSTEMMEM,						// ���b�V���̍쐬�I�v�V�������w��
								pDevice,								// IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
								NULL,									// �אڐ��f�[�^���܂ރo�b�t�@�ւ̃|�C���^
								&g_aJellyfishXFile[nIdx].pD3DXBuffMate,	// �}�e���A���f�[�^���܂ރo�b�t�@�ւ̃|�C���^
								NULL,									// �G�t�F�N�g�C���X�^���X�̔z����܂ރo�b�t�@�ւ̃|�C���^
								&g_aJellyfishXFile[nIdx].nNumMate,		// D3DXMATERIAL�\���̂̐�
								&g_aJellyfishXFile[nIdx].pD3DXMesh)))	// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�̃A�h���X
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitXFile(void)
{
	// �v���C���[�L�����̏I������
	for(int nIdx = 0; nIdx < MAX_JELLYFISH_XFILE; nIdx++)
	{
		if( g_aJellyfishXFile[nIdx].pD3DTexture != NULL)
		{// �e�N�X�`���̊J��
			 g_aJellyfishXFile[nIdx].pD3DTexture -> Release();
			 g_aJellyfishXFile[nIdx].pD3DTexture = NULL;
		}

		if( g_aJellyfishXFile[nIdx].pD3DXMesh != NULL)
		{// ���b�V���̊J��
			 g_aJellyfishXFile[nIdx].pD3DXMesh -> Release();
			 g_aJellyfishXFile[nIdx].pD3DXMesh = NULL;
		}

		if( g_aJellyfishXFile[nIdx].pD3DXBuffMate != NULL)
		{// �}�e���A���̊J��
			 g_aJellyfishXFile[nIdx].pD3DXBuffMate -> Release();
			 g_aJellyfishXFile[nIdx].pD3DXBuffMate = NULL;
		}
	}
	
}
//=============================================================================
// �v���C���[�L�����t�@�C���\���̃��[�N�̐擪�A�h���X���擾
//=============================================================================
XFILE *GetpJellyfishXFile(void)
{
	return &g_aJellyfishXFile[0];
}

