/*******************************************************************************
* �^�C�g��:		�����蔻�菈��
* �v���O������:	CollisionDetection.h
* �쐬��:		GP11A331 4�� �Ɍ��C�H
* �쐬��:		2015/11/24
********************************************************************************
* �X�V����:		- 2015/11/24	�Ɍ��C�H
*					- V1.00		Initial Version
*******************************************************************************/
#ifndef _COLLISION_DETECTION_H_
#define _COLLISION_DETECTION_H_

#include "main.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
float dotProduct( D3DXVECTOR3 vl, D3DXVECTOR3 vr);
D3DXVECTOR3 crossProduct( D3DXVECTOR3 vl, D3DXVECTOR3 vr );
int CollisionDetection(D3DXVECTOR3 p0, D3DXVECTOR3 p1, D3DXVECTOR3 p2, D3DXVECTOR3 posOld, D3DXVECTOR3 posNow);

#endif
