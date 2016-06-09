/*******************************************************************************
* タイトル:		カメラ処理
* プログラム名:	CameraChase.h
* 作成者:		GP11A331 4番 伊原佑稀
* 作成日:		2016/01/24
********************************************************************************
* 更新履歴:		- 2016/01/24	伊原佑稀
*					- V1.00		Initial Version
*******************************************************************************/
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Main.h"

//*****************************************************************************
// カメラの構造体
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 posV;			// 視点
	D3DXVECTOR3 posR;			// 注視点
	D3DXVECTOR3 vecU;			// 上方向ベクトル
	D3DXVECTOR3	posVDest;		// 視点の目的位置
	D3DXVECTOR3	posRDest;		// 注視点の目的位置
	D3DXVECTOR3 vecVR;			// 視点から注視点方向への単位ベクトル
	D3DXVECTOR3 vecVerToVR;// ベクトルVRに垂直な単位ベクトル
	D3DXVECTOR3 rot;			// 向き（回転角）
	float fDistance;			// 視点と注視点の距離
	float fDistanceXZ;
	float fInitialDistance;		// 始めの視点と注視点の距離
	float fChaseHeightV;		// 視点の高さ
	float fChaseHeightR;		// 注視点の高さ
	D3DXMATRIX mtxProjection;	// プロジェクションマトリックス
	D3DXMATRIX mtxView;			// ビューマトリックス
	float fInitialSin;
	float fInitialCos;
} CAMERA;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);

CAMERA *GetCamera(void);

#endif
