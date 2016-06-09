/*******************************************************************************
* �^�C�g��:		���C�g����
* �v���O������:	Light.cpp
* �쐬��:		GP11A331 4�� �Ɍ��C�H
* �쐬��:		2015/10/22
********************************************************************************
* �X�V����:		- 2015/10/22	�Ɍ��C�H
*					- V1.00		Initial Version
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "Light.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NUM_LIGHT (8)					// ���C�g�̐�

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
D3DLIGHT9 g_aLight[NUM_LIGHT];			// ���C�g���

/*******************************************************************************
�֐���:	void InitLight(void)
����:	�Ȃ�
�߂�l:	�Ȃ�
����:	���C�g�̏�����
*******************************************************************************/
HRESULT InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 vecDir;

	for(int nCntLight = 0; nCntLight < NUM_LIGHT; nCntLight++)
	{
		// D3DLIGHT9�\���̂�0�ŃN���A����
		ZeroMemory(&g_aLight[nCntLight], sizeof(D3DLIGHT9));
		// ���C�g0�̃^�C�v�̐ݒ�
		g_aLight[nCntLight].Type = D3DLIGHT_DIRECTIONAL;
		switch(nCntLight)
		{
		case 0:
			// ���C�g0�̊g�U���̐ݒ�
			g_aLight[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			// ���C�g0�̕����̐ݒ�
			vecDir = D3DXVECTOR3(0.50f, -0.50f, 0.50f);
			break;
		case 1:
			g_aLight[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			vecDir = D3DXVECTOR3(0.50f, -0.50f, -0.50f);
			break;
		case 2:
			g_aLight[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			vecDir = D3DXVECTOR3(-0.50f, -0.50f, -0.50f);
			break;
		case 3:
			g_aLight[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			vecDir = D3DXVECTOR3(-0.50f, -0.50f, 0.50f);
			break;
		case 4:
			g_aLight[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			vecDir = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
			break;
		case 5:
			g_aLight[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			vecDir = D3DXVECTOR3(0.0f, -1.0f, 1.0f);
			break;
		default:
			g_aLight[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			vecDir = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			break;
		}
		D3DXVec3Normalize((D3DXVECTOR3 *) &g_aLight[nCntLight].Direction, &vecDir);
		// ���C�g��Ambient�̐ݒ�
		g_aLight[nCntLight].Ambient = D3DXCOLOR(0.20f, 0.20f, 0.20f, 1.0f);
		// ���C�g0�������_�����O�p�C�v���C���ɐݒ�
		pDevice -> SetLight(nCntLight, &g_aLight[nCntLight]);
		// ���C�g0���g�p�g�p��Ԃ�
		pDevice -> LightEnable(nCntLight, TRUE);
	}
	// ���C�e�B���O���[�h��ON
	pDevice -> SetRenderState(D3DRS_LIGHTING, TRUE);

	return S_OK;
}

//=============================================================================
// ���C�g�̏I������
//=============================================================================
void UninitLight(void)
{
}

//=============================================================================
// ���C�g�̍X�V����
//=============================================================================
void UpdateLight(void)
{
}

