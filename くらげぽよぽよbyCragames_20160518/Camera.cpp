/*******************************************************************************
* タイトル:		カメラ処理
* プログラム名:	Camera.cpp
* 作成者:		GP11A331 4番 伊原佑稀
* 作成日:		2015/10/22
********************************************************************************
* 更新履歴:		- 2016/01/10	 伊原佑稀
*					- V1.00		Initial Version
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "Camera.h"
#include "Input.h"
#include "DebugProc.h"
#include "Player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	CAM_POS_V_X				(0.0f)				// カメラの視点初期位置(X座標)
#define	CAM_POS_V_Y				(1800.0f)			// カメラの視点初期位置(Y座標)
#define	CAM_POS_V_Z				(-1600.0f)			// カメラの視点初期位置(Z座標)
#define	CAM_POS_R_X				(0.0f)				// カメラの注視点初期位置(X座標)
#define	CAM_POS_R_Y				(-700.0f)			// カメラの注視点初期位置(Y座標)
#define	CAM_POS_R_Z				(200.0f)				// カメラの注視点初期位置(Z座標)

#define	VIEW_ANGLE				(D3DXToRadian(45.0f))							// ビュー平面の視野角
#define	VIEW_ASPECT				((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// ビュー平面のアスペクト比
#define	VIEW_NEAR_Z				(10.0f)											// ビュー平面のNearZ値
#define	VIEW_FAR_Z				(10000.0f)										// ビュー平面のFarZ値
#define	VALUE_MOVE_CAMERA		(10.0f)											// カメラの移動量
#define	VALUE_ROTATE_CAMERA		(D3DX_PI * 0.01f)								// カメラの回転量
#define	VALUE_ADJUST_DISTANCE	(2.0f)											// 視点と注視点の距離調整量
#define HALF_OF_PI				(D3DX_PI / 2)

#define	DISTANCE_CAMERA_R (30)					// モデルの視線の先までの距離

#define	CHASE_HEIGHT_V (CAM_POS_V_Y)			// 追跡時の視点の高さ
#define	CHASE_HEIGHT_R (CAM_POS_R_Y)			// 追跡時の注視点の高さ

//*****************************************************************************
// 列挙体
//*****************************************************************************
typedef enum
{
	RELEASE_CAMERA = 0,
	DEBUG_CAMERA,
} CAMERA_MODE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
CAMERA g_Camera;		// カメラ情報

CAMERA_MODE g_CameraMode = RELEASE_CAMERA;
/*******************************************************************************
関数名:	HRESULT InitCamera(void)
引数:	なし
戻り値:	HRESULT型
説明:	カメラの初期化
*******************************************************************************/
HRESULT InitCamera(void)
{
	/* メインモードによる初期化の分岐 */
	// 視点初期化
	g_Camera.posV = D3DXVECTOR3(0.0f, 100.0f, -200.0f);
	// 注視点初期化
	g_Camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// 上方向ベクトル初期化
	g_Camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	// 視点の目的位置
	g_Camera.posVDest = g_Camera.posV;
	// 注視点の目的位置
	g_Camera.posRDest = g_Camera.posR;
	// カメラ向き（回転角）の初期化
	g_Camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// 視点と注視点の距離を求める
	g_Camera.fDistance = sqrt(powf(g_Camera.posR.x - g_Camera.posV.x, 2.0f) +  powf(g_Camera.posR.y - g_Camera.posV.y, 2.0f) + powf(g_Camera.posR.z - g_Camera.posV.z, 2.0f));
	// 始めの視点と注視点の距離
	g_Camera.fInitialDistance = g_Camera.fDistance;
	// 視点の高さを初期化
	g_Camera.fChaseHeightV = CHASE_HEIGHT_V;
	// 注視点の高さを初期化
	g_Camera.fChaseHeightR = CHASE_HEIGHT_R;
	// 始めの視点と注視点が作る直角三角形の角度の初期化
	g_Camera.fInitialSin = fabs((g_Camera.posR.y - g_Camera.posV.y) / g_Camera.fInitialDistance);
	g_Camera.fInitialCos = fabs((g_Camera.posR.z - g_Camera.posV.z) / g_Camera.fInitialDistance);
	
	return S_OK;
}

//=============================================================================
// カメラの終了処理
//=============================================================================
void UninitCamera(void)
{

}

//=============================================================================
// カメラの更新処理
//=============================================================================
void UpdateCamera(void)
{
	float fIntervalCamera, fMagnitudeMove;
	float fRateChaseCameraV, fRateChaseCameraR;

	// 注視点の目的位置
	g_Camera.posRDest.x = CAM_POS_R_X;
	g_Camera.posRDest.y = CAM_POS_R_Y;
	g_Camera.posRDest.z = CAM_POS_R_Z;

	// 視点の目的位置
	g_Camera.posVDest.x = CAM_POS_V_X;
	g_Camera.posVDest.y = CAM_POS_V_Y;// + g_Camera.fDistance * g_Camera.fInitialSin;
	g_Camera.posVDest.z = CAM_POS_V_Z;// - g_Camera.fDistance * g_Camera.fInitialCos;

	// 注視点の補正
	g_Camera.posR.x += (g_Camera.posRDest.x - g_Camera.posR.x);
	g_Camera.posR.y += (g_Camera.posRDest.y - g_Camera.posR.y);
	g_Camera.posR.z += (g_Camera.posRDest.z - g_Camera.posR.z);

	// 視点の補正
	g_Camera.posV.x += (g_Camera.posVDest.x - g_Camera.posV.x);
	g_Camera.posV.y += (g_Camera.posVDest.y - g_Camera.posV.y);
	g_Camera.posV.z += (g_Camera.posVDest.z - g_Camera.posV.z);

	//PrintDebugProc("[カメラの視点  ：(%f : %f : %f)]\n", g_Camera.posV.x, g_Camera.posV.y, g_Camera.posV.z);
	//PrintDebugProc("[カメラの注視点：(%f : %f : %f)]\n", g_Camera.posR.x, g_Camera.posR.y, g_Camera.posR.z);
	//PrintDebugProc("[カメラの向き  ：(%f)]\n", g_Camera.rot.y);
	//PrintDebugProc("\n");

	//PrintDebugProc("*** カメラ操作 ***\n");
	///*PrintDebugProc("視点上昇     : [ Ｙ ]\n");
	//PrintDebugProc("視点下降     : [ Ｎ ]\n");
	//PrintDebugProc("注視点上昇   : [ Ｔ ]\n");
	//PrintDebugProc("注視点下降   : [ Ｂ ]\n");*/
	//PrintDebugProc("ズームイン   : [ Ｕ ]\n");
	//PrintDebugProc("ズームアウト : [ Ｍ ]\n");
	//PrintDebugProc("\n");
}

//=============================================================================
// カメラの設定処理
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_Camera.mtxView);
	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_Camera.mtxView, &g_Camera.posV, &g_Camera.posR, &g_Camera.vecU);
	// ビューマトリックスの設定
	pDevice -> SetTransform(D3DTS_VIEW, &g_Camera.mtxView);
	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_Camera.mtxProjection);
	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&g_Camera.mtxProjection, VIEW_ANGLE, VIEW_ASPECT, VIEW_NEAR_Z, VIEW_FAR_Z);
	// プロジェクションマトリックスの設定(透視変換の設定)
	pDevice -> SetTransform(D3DTS_PROJECTION, &g_Camera.mtxProjection);
}

/*******************************************************************************
関数名:	CAMERA *GetCamera(void)
引数:	なし
戻り値:	CAMERA型
説明:	カメラのポインタを取得
*******************************************************************************/
CAMERA *GetCamera(void)
{
	return &g_Camera;
}
