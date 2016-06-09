/*******************************************************************************
* �^�C�g��:		�J��������
* �v���O������:	CameraChase.h
* �쐬��:		GP11A331 4�� �Ɍ��C�H
* �쐬��:		2016/01/24
********************************************************************************
* �X�V����:		- 2016/01/24	�Ɍ��C�H
*					- V1.00		Initial Version
*******************************************************************************/
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Main.h"

//*****************************************************************************
// �J�����̍\����
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 posV;			// ���_
	D3DXVECTOR3 posR;			// �����_
	D3DXVECTOR3 vecU;			// ������x�N�g��
	D3DXVECTOR3	posVDest;		// ���_�̖ړI�ʒu
	D3DXVECTOR3	posRDest;		// �����_�̖ړI�ʒu
	D3DXVECTOR3 vecVR;			// ���_���璍���_�����ւ̒P�ʃx�N�g��
	D3DXVECTOR3 vecVerToVR;// �x�N�g��VR�ɐ����ȒP�ʃx�N�g��
	D3DXVECTOR3 rot;			// �����i��]�p�j
	float fDistance;			// ���_�ƒ����_�̋���
	float fDistanceXZ;
	float fInitialDistance;		// �n�߂̎��_�ƒ����_�̋���
	float fChaseHeightV;		// ���_�̍���
	float fChaseHeightR;		// �����_�̍���
	D3DXMATRIX mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;			// �r���[�}�g���b�N�X
	float fInitialSin;
	float fInitialCos;
} CAMERA;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);

CAMERA *GetCamera(void);

#endif
