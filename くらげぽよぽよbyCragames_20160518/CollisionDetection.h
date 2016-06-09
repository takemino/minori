/*******************************************************************************
* タイトル:		当たり判定処理
* プログラム名:	CollisionDetection.h
* 作成者:		GP11A331 4番 伊原佑稀
* 作成日:		2015/11/24
********************************************************************************
* 更新履歴:		- 2015/11/24	伊原佑稀
*					- V1.00		Initial Version
*******************************************************************************/
#ifndef _COLLISION_DETECTION_H_
#define _COLLISION_DETECTION_H_

#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
float dotProduct( D3DXVECTOR3 vl, D3DXVECTOR3 vr);
D3DXVECTOR3 crossProduct( D3DXVECTOR3 vl, D3DXVECTOR3 vr );
int CollisionDetection(D3DXVECTOR3 p0, D3DXVECTOR3 p1, D3DXVECTOR3 p2, D3DXVECTOR3 posOld, D3DXVECTOR3 posNow);

#endif
