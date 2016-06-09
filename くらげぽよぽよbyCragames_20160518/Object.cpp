/*******************************************************************************
* タイトル:		3D空間内のオブジェクト・ポリゴンの処理
* プログラム名:	Object.cpp
* 作成者:		GP11A331 4番 伊原佑稀
* 作成日:		2016/01/24
********************************************************************************
* 更新履歴:		- 2016/01/24	伊原佑稀
*					- V1.00		Initial Version
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "Object.h"
#include "XFile.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define KURAGEMOVE					(0.50f)			// くらげの移動速度
#define KURAGEROTATE				(0.20f)			// くらげの回転速度
#define KURAGESIZEX					(1.0f)			// くらげのサイズ(X方向)
#define KURAGESIZEY					(1.0f)			// くらげのサイズ(Y方向)

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
OBJECT g_Object;

/*******************************************************************************
関数名:	void InitObject(void)
引数:	なし
戻り値:	なし
説明:	オブジェクトの初期化処理
*******************************************************************************/
void InitObject(void)
{
	// 位置を設定
	g_Object.pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	// 向きを設定
	g_Object.rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	// スケールを設定
	g_Object.scl = D3DXVECTOR3(20.0f,20.0f,20.0f);

}
/*******************************************************************************
関数名:	void UpdateObject(void)
引数:	なし
戻り値:	なし
説明:	オブジェクトの更新処理
*******************************************************************************/
void UpdateObject(void)
{

}
/*******************************************************************************
関数名:	void DrawObject(void)
引数:	なし
戻り値:	なし
説明:	オブジェクトの描画
*******************************************************************************/
void DrawObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	XFILE *pJellyfishXFile = GetpJellyfishXFile();
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	
	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Object.mtxWorld);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl,g_Object.scl.x,g_Object.scl.y,g_Object.scl.z);
	D3DXMatrixMultiply(&g_Object.mtxWorld,&g_Object.mtxWorld,&mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,g_Object.rot.y,g_Object.rot.x,g_Object.rot.z);
	D3DXMatrixMultiply(&g_Object.mtxWorld,&g_Object.mtxWorld,&mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate,g_Object.pos.x,g_Object.pos.y,g_Object.pos.z);
	D3DXMatrixMultiply(&g_Object.mtxWorld,&g_Object.mtxWorld,&mtxTranslate);

	// ワールドマトリックスの設定
	pDevice -> SetTransform(D3DTS_WORLD,&g_Object.mtxWorld);

	// 現在のマテリアルを取得
	pDevice -> GetMaterial(&matDef);

	// マテリアル情報に対するポインタを取得
	pD3DXMat = (D3DXMATERIAL * )pJellyfishXFile[XFILE_TEST_FILE].pD3DXBuffMate -> GetBufferPointer();

	// マテリアルの設定
	pDevice -> SetMaterial(&pD3DXMat[XFILE_TEST_FILE].MatD3D);

	// テクスチャの設定
	pDevice -> SetTexture(0,pJellyfishXFile[XFILE_TEST_FILE].pD3DTexture);

	// 描画
	pJellyfishXFile[XFILE_TEST_FILE].pD3DXMesh -> DrawSubset(0);

	// マテリアルをデフォルトに戻す
	pDevice -> SetMaterial(&matDef);
}

