/*******************************************************************************
* タイトル:		影処理
* プログラム名:	shadow.cpp
* 作成者:		GP11A331 4番 伊原佑稀
* 作成日:		2015/11/10
********************************************************************************
* 更新履歴:		- 2015/11/10	伊原佑稀
*					- V1.00		Initial Version
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "Shadow.h"
#include "Texture.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	SHADOW_SIZE_X		(50.0f)							// 影の幅
#define	SHADOW_SIZE_Z		(50.0f)							// 影の高さ

#define	MAX_SHADOW			(128)							// 影最大数

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXMATRIX mtxWorld;	// ワールドマトリックス
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;		// 回転
	bool bUse;				// 使用しているかどうか
}SHADOW;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;	// 頂点バッファへのポインタ

SHADOW	g_aShadow[MAX_SHADOW];						// 影ワーク

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	SHADOW *pShadow;

	// 影構造体のポインタに影ワークの先頭アドレスを代入
	pShadow = &g_aShadow[0];

	// 影ワークの初期化
	for(int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++, pShadow++)
	{
		pShadow->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pShadow->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pShadow->bUse = false;
	}

	// 頂点情報の作成
	MakeVertexShadow(pDevice);

	return S_OK;
}
/*******************************************************************************
関数名:	void InitShadowInGame(void)
引数:	なし
戻り値:	なし
説明:	シャドウのゲーム内初期化
*******************************************************************************/
void InitShadowInGame(void)
{
	SHADOW *pShadow;

	// 影構造体のポインタに影ワークの先頭アドレスを代入
	pShadow = &g_aShadow[0];

	// 影ワークの初期化
	for(int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++, pShadow++)
	{
		pShadow->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pShadow->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pShadow->bUse = false;
	}
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitShadow(void)
{
	if(g_pVtxBuffShadow != NULL)
	{// 頂点バッファの開放
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateShadow(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LPDIRECT3DTEXTURE9* pSpaceTex = GetSpaceTexture();
	D3DXMATRIX mtxRot, mtxTranslate;
	SHADOW *pShadow;

	// 減算合成
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);	 
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// 結果 = 転送先(DEST) - 転送元(SRC)
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// 影構造体のポインタに影ワークの先頭アドレスを代入
	pShadow = &g_aShadow[0];
	
	for(int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++, pShadow++)
	{
		if(pShadow->bUse)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&pShadow->mtxWorld);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, pShadow->rot.y, pShadow->rot.x, pShadow->rot.z);
			D3DXMatrixMultiply(&pShadow->mtxWorld, &pShadow->mtxWorld, &mtxRot);
			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, pShadow->pos.x, pShadow->pos.y, pShadow->pos.z);
			D3DXMatrixMultiply(&pShadow->mtxWorld, &pShadow->mtxWorld, &mtxTranslate);
			// ワールドマトリックスの設定
			pDevice -> SetTransform(D3DTS_WORLD, &pShadow->mtxWorld);
			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice -> SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));
				// 頂点フォーマットの設定
			pDevice -> SetFVF(FVF_VERTEX_3D);
			// テクスチャの設定
			pDevice -> SetTexture(0,pSpaceTex[TEX_SHADOW]);
			// ポリゴンの描画
			pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,	// プリミティブの描き方
											0,				// 描画を開始する頂点ナンバー
											NUM_POLYGON);	// ポリゴン数
		}
	}

	// 通常ブレンド
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);			// αブレンドを行う
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定D3DBLEND_SRCALPHA
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定	// 結果 = 転送元(SRC) + 転送先(DEST)D3DBLEND_INVSRCALPHA
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
HRESULT MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを作成
	if(FAILED(pDevice -> CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_SHADOW,
											D3DUSAGE_WRITEONLY,
											FVF_VERTEX_3D,
											D3DPOOL_MANAGED,
											&g_pVtxBuffShadow,
											NULL)))
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pVtxBuffShadow->Lock(0,0,(void**)&pVtx,0);

		for(int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++, pVtx += 4)
		{
			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(-SHADOW_SIZE_X / 2, 0.0f, SHADOW_SIZE_Z / 2);
			pVtx[1].vtx = D3DXVECTOR3( SHADOW_SIZE_X / 2, 0.0f, SHADOW_SIZE_Z / 2);
			pVtx[2].vtx = D3DXVECTOR3(-SHADOW_SIZE_X / 2, 0.0f, -SHADOW_SIZE_Z / 2);
			pVtx[3].vtx = D3DXVECTOR3( SHADOW_SIZE_X / 2, 0.0f, -SHADOW_SIZE_Z / 2);
			// 法線の設定
			pVtx[0].nor	= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].nor	= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[2].nor	= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].nor	= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			// 頂点カラーの設定
			pVtx[0].col	= D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.5f);
			pVtx[1].col	= D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.5f);
			pVtx[2].col	= D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.5f);
			pVtx[3].col	= D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.5f);
			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		// 頂点データをアンロックする
		g_pVtxBuffShadow->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexShadow(int nIdxShadow, float fSizeX, float fSizeZ)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pVtxBuffShadow->Lock(0,0,(void**)&pVtx,0);

		// pVtxをインデックス分ズラす
		pVtx += NUM_VERTEX * nIdxShadow;

		// 頂点座標の設定（引数を用いて設定）
		pVtx[0].vtx = D3DXVECTOR3(-fSizeX / 2, 0.0f, fSizeZ / 2);
		pVtx[1].vtx = D3DXVECTOR3( fSizeX / 2, 0.0f, fSizeZ / 2);
		pVtx[2].vtx = D3DXVECTOR3(-fSizeX / 2, 0.0f, -fSizeZ / 2);
		pVtx[3].vtx = D3DXVECTOR3( fSizeX / 2, 0.0f, -fSizeZ / 2);

		// 頂点データをアンロックする
		g_pVtxBuffShadow->Unlock();
	}
}

//=============================================================================
// 頂点カラーの設定
//=============================================================================
void SetColorShadow(int nIdxShadow, D3DXCOLOR col)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pVtxBuffShadow->Lock(0,0,(void**)&pVtx,0);

		// pVtxをインデックス分ズラす
		pVtx += NUM_VERTEX * nIdxShadow;

		// 頂点カラーの設定
		pVtx[0].col	= col;
		pVtx[1].col	= col;
		pVtx[2].col	= col;
		pVtx[3].col	= col;

		// 頂点データをアンロックする
		g_pVtxBuffShadow->Unlock();
	}
}

//=============================================================================
// 影の作成
//=============================================================================
int CreateShadow(D3DXVECTOR3 pos, float fSizeX, float fSizeZ)
{
	SHADOW *pShadow;
	int nIdxShadow = -1;

	// 影構造体のポインタに影ワークの先頭アドレスを代入
	pShadow = &g_aShadow[0];

	for(int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++, pShadow++)
	{
		if(!pShadow->bUse)
		{
			// 影の位置、回転角を設定
			pShadow->pos = pos;
			pShadow->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			// 影ワークを使用状態に変更
			pShadow->bUse = true;
			// 頂点座標の設定関数を呼び出す
			SetVertexShadow(nCntShadow, fSizeX, fSizeZ);
			// 影の番号をnIdxShadowに設定
			nIdxShadow = nCntShadow;
			break;
		}
	}

	// nIdxShadowを返す
	return nIdxShadow;
}

//=============================================================================
// 影の破棄
//=============================================================================
void ReleaseShadow(int nIdxShadow)
{
	SHADOW *pShadow;
	pShadow = &g_aShadow[nIdxShadow];

	if(nIdxShadow < MAX_SHADOW) // 指定された影が影ワークの個数ないかどうか
	{
		// 影ワークを未使用状態に設定
		pShadow->bUse = false;
	}
}

//=============================================================================
// 位置の設定
//=============================================================================
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos)
{
	SHADOW *pShadow;
	pShadow = &g_aShadow[nIdxShadow];
	// 指定された影ワークに位置を設定
	pShadow->pos = pos;
	pShadow->pos.y = 0.2f;
}

