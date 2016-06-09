/*******************************************************************************
* �^�C�g��:		�e����
* �v���O������:	shadow.cpp
* �쐬��:		GP11A331 4�� �Ɍ��C�H
* �쐬��:		2015/11/10
********************************************************************************
* �X�V����:		- 2015/11/10	�Ɍ��C�H
*					- V1.00		Initial Version
*******************************************************************************/
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitShadow(void);
void InitShadowInGame(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);

int CreateShadow(D3DXVECTOR3 pos, float fSizeX, float fSizeZ);
void ReleaseShadow(int nIdxShadow);
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos);
void SetVertexShadow(int nIdxShadow, float fSizeX, float fSizeZ);
void SetColorShadow(int nIdxShadow, D3DXCOLOR col);

#endif
