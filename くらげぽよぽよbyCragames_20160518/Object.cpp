/*******************************************************************************
* �^�C�g��:		3D��ԓ��̃I�u�W�F�N�g�E�|���S���̏���
* �v���O������:	Object.cpp
* �쐬��:		GP11A331 4�� �Ɍ��C�H
* �쐬��:		2016/01/24
********************************************************************************
* �X�V����:		- 2016/01/24	�Ɍ��C�H
*					- V1.00		Initial Version
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "Object.h"
#include "XFile.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define KURAGEMOVE					(0.50f)			// ���炰�̈ړ����x
#define KURAGEROTATE				(0.20f)			// ���炰�̉�]���x
#define KURAGESIZEX					(1.0f)			// ���炰�̃T�C�Y(X����)
#define KURAGESIZEY					(1.0f)			// ���炰�̃T�C�Y(Y����)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
OBJECT g_Object;

/*******************************************************************************
�֐���:	void InitObject(void)
����:	�Ȃ�
�߂�l:	�Ȃ�
����:	�I�u�W�F�N�g�̏���������
*******************************************************************************/
void InitObject(void)
{
	// �ʒu��ݒ�
	g_Object.pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	// ������ݒ�
	g_Object.rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	// �X�P�[����ݒ�
	g_Object.scl = D3DXVECTOR3(20.0f,20.0f,20.0f);

}
/*******************************************************************************
�֐���:	void UpdateObject(void)
����:	�Ȃ�
�߂�l:	�Ȃ�
����:	�I�u�W�F�N�g�̍X�V����
*******************************************************************************/
void UpdateObject(void)
{

}
/*******************************************************************************
�֐���:	void DrawObject(void)
����:	�Ȃ�
�߂�l:	�Ȃ�
����:	�I�u�W�F�N�g�̕`��
*******************************************************************************/
void DrawObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	XFILE *pJellyfishXFile = GetpJellyfishXFile();
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	
	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Object.mtxWorld);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl,g_Object.scl.x,g_Object.scl.y,g_Object.scl.z);
	D3DXMatrixMultiply(&g_Object.mtxWorld,&g_Object.mtxWorld,&mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,g_Object.rot.y,g_Object.rot.x,g_Object.rot.z);
	D3DXMatrixMultiply(&g_Object.mtxWorld,&g_Object.mtxWorld,&mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate,g_Object.pos.x,g_Object.pos.y,g_Object.pos.z);
	D3DXMatrixMultiply(&g_Object.mtxWorld,&g_Object.mtxWorld,&mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice -> SetTransform(D3DTS_WORLD,&g_Object.mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice -> GetMaterial(&matDef);

	// �}�e���A�����ɑ΂���|�C���^���擾
	pD3DXMat = (D3DXMATERIAL * )pJellyfishXFile[XFILE_TEST_FILE].pD3DXBuffMate -> GetBufferPointer();

	// �}�e���A���̐ݒ�
	pDevice -> SetMaterial(&pD3DXMat[XFILE_TEST_FILE].MatD3D);

	// �e�N�X�`���̐ݒ�
	pDevice -> SetTexture(0,pJellyfishXFile[XFILE_TEST_FILE].pD3DTexture);

	// �`��
	pJellyfishXFile[XFILE_TEST_FILE].pD3DXMesh -> DrawSubset(0);

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice -> SetMaterial(&matDef);
}

