/*******************************************************************************
* タイトル:		影処理
* プログラム名:	shadow.cpp
* 作成者:		GP11A331 4番 伊原佑稀
* 作成日:		2015/11/10
********************************************************************************
* 更新履歴:		- 2015/11/10	伊原佑稀
*					- V1.00		Initial Version
*******************************************************************************/
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
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
