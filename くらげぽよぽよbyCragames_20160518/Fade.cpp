/*******************************************************************************
* タイトル:		Fade処理
* プログラム名:	Fade.cpp
* 作成者:		GP11A331 4 伊原佑稀
* 作成日:		2015/11/16
********************************************************************************
* 更新履歴:		- 2015/11/16	 伊原
*					- V1.00		Initial Version
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "Fade.h"
#include "input.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FADE_POS_X (0)// ポリゴンの左上
#define FADE_POS_Y (0) // ポリゴンの左上
#define FADE_SIZE_X (SCREEN_WIDTH) // ポリゴンサイズX
#define FADE_SIZE_Y (SCREEN_HEIGHT) // ポリゴンサイズY
#define FADE_TEXTURENAME ""

/*******************************************************************************
* 構造体定義
*******************************************************************************/

/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/
HRESULT MakeVertexFade(LPDIRECT3DDEVICE9 pDevice);

/*******************************************************************************
* グローバル変数
*******************************************************************************/
LPDIRECT3DVERTEXBUFFER9		g_pVtxBufferFade = NULL;	// 頂点バッファインターフェースへのポインタ
LPDIRECT3DTEXTURE9			g_pTextureFade = NULL;		// テクスチャへのポインタ
int							g_AlphaValue = 0;			// α値
int							g_fade = FADE_NONE;
/*******************************************************************************
関数名:	HRESULT InitFade(void)
引数:	
戻り値:	HRESULT型	S_OK:正常終了
					E_FAIL:初期化失敗
説明:	FADEの初期化
*******************************************************************************/
HRESULT InitFade(void) // 頂点のデータを構造体配列に設定
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// 頂点情報の作成
	if(FAILED(MakeVertexFade(pDevice)))
	{
		return E_FAIL;
	}
	// テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice,
		FADE_TEXTURENAME,
		&g_pTextureFade
	);
	return S_OK;
}
/*******************************************************************************
関数名:	HRESULT MakeVertexFade(LPDIRECT3DDEVICE9 pDevice)
引数:	LPDIRECT3DDEVICE9 pDevice
戻り値:	HRESULT型	S_OK:正常終了
					E_FAIL:初期化失敗
説明:	FADE頂点の作成
*******************************************************************************/
HRESULT MakeVertexFade(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを作成
	if(FAILED(pDevice -> CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,
											D3DUSAGE_WRITEONLY,
											FVF_VERTEX_2D,
											D3DPOOL_MANAGED,
											&g_pVtxBufferFade,
											NULL)))
	{
		return E_FAIL;
	}

	{// 頂点バッファの中身を埋める
		VERTEX_2D *pVtx;
		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pVtxBufferFade -> Lock(0,0,(void**)&pVtx,0);
		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(FADE_POS_X, FADE_POS_Y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(FADE_POS_X + FADE_SIZE_X, FADE_POS_Y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(FADE_POS_X, FADE_POS_Y + FADE_SIZE_Y, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(FADE_POS_X + FADE_SIZE_X, FADE_POS_Y + FADE_SIZE_Y, 0.0f);

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 0);
		pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 0);
		pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 0);
		pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 0);
		
		// テクスチャ座標指定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点データをアンロックする
		g_pVtxBufferFade -> Unlock();
	}
	return S_OK;
}
/*******************************************************************************
関数名:	void UpdateFade(void)
引数:	なし
戻り値:	なし
説明:	FADEの更新処理
*******************************************************************************/
void UpdateFade(void)
{
	{// 頂点バッファの中身を埋める
		VERTEX_2D *pVtx;
		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pVtxBufferFade -> Lock(0,0,(void**)&pVtx,0);
		switch(g_fade)
		{
		case FADE_NONE:
			break;
		case FADE_IN:
			if(g_AlphaValue > 0)
			{
				g_AlphaValue -= 8;
			}
			if(g_AlphaValue <= 0)// α値が０～２５５に収まるように設定
			{
				g_AlphaValue = 0;
				g_fade = FADE_NONE;
			}
			break;
		case FADE_OUT:
			if(g_AlphaValue < 255)
			{
				g_AlphaValue += 8;
			}
			if(g_AlphaValue >= 255)
			{
				g_AlphaValue = 255;
			}
			break;
		default:
			break;
		}
		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, g_AlphaValue);
		pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, g_AlphaValue);
		pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, g_AlphaValue);
		pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, g_AlphaValue);
		// 頂点データをアンロックする
		g_pVtxBufferFade -> Unlock();
	}
}
/*******************************************************************************
関数名:	void DrawFade(void)
引数:	なし
戻り値:	なし
説明:	FADEの描画処理
*******************************************************************************/
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice -> SetStreamSource(0, g_pVtxBufferFade, 0, sizeof(VERTEX_2D));

	// 頂点フォーマット
	pDevice -> SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice -> SetTexture(0,g_pTextureFade);

	// ポリゴンの描画
	pDevice -> DrawPrimitive(
							D3DPT_TRIANGLESTRIP,
							0,
							NUM_POLYGON);

}
/*******************************************************************************
関数名:	void UninitFade(void)
引数:	なし
戻り値:	なし
説明:	FADEの終了処理
*******************************************************************************/
void UninitFade(void)
{
	if(g_pTextureFade != NULL)
	{
		g_pTextureFade -> Release();
		g_pTextureFade = NULL;
	}
	if(g_pVtxBufferFade != NULL)
	{
		g_pVtxBufferFade -> Release();
		g_pVtxBufferFade = NULL;
	}
}
/*******************************************************************************
関数名:	void SetFade(FADE fade)
引数:	なし
戻り値:	なし
説明:	FADEのセット
*******************************************************************************/
void SetFade(FADE fade)
{
	g_fade = fade;
}
/*******************************************************************************
関数名:	int GetAlphaValue(void)
引数:	なし
戻り値:	int
説明:	α値を取得
*******************************************************************************/
int GetAlphaValue(void)
{
	return g_AlphaValue;
}