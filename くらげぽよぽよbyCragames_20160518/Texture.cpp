/*******************************************************************************
* タイトル:		Texture処理
* プログラム名:	Texture.cpp
* 作成者:		GP11A331 4 伊原佑稀
* 作成日:		2016/01/29
********************************************************************************
* 更新履歴:		- 2016/02/23	伊原
*					- V1.00		Initial Version
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "Texture.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

/*******************************************************************************
* 構造体定義
*******************************************************************************/

/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/

/*******************************************************************************
* グローバル変数
*******************************************************************************/
LPDIRECT3DTEXTURE9		g_pD3DTextureSpace[MAX_SPACE_TEXTURE];
LPDIRECT3DTEXTURE9		g_pD3DTextureTitle[MAX_TITLE_TEXTURE];
LPDIRECT3DTEXTURE9		g_pD3DTextureResult[MAX_RESULT_TEXTURE];
LPDIRECT3DTEXTURE9		g_pD3DTextureUI[MAX_UI_TEXTURE];
LPDIRECT3DTEXTURE9		g_pD3DTextureUtility[MAX_UTILITY_TEXTURE];			

/* 3D空間内のテクスチャ */
char *g_SpaceTexName[MAX_SPACE_TEXTURE] = 
{// テクスチャファイル名

};
/* タイトルテクスチャ */
char *g_TitleTexName[MAX_TITLE_TEXTURE] = 
{// テクスチャファイル名

};
/* リザルトテクスチャ */
char *g_ResultTexName[MAX_RESULT_TEXTURE] = 
{// テクスチャファイル名
	
};
/* UIテクスチャ */
char *g_UITexName[MAX_UI_TEXTURE] = 
{// テクスチャファイル名
	"data/TEXTURE/OptionWindow.png",
	"data/TEXTURE/BGMmixerber.png",
	"data/TEXTURE/SEmixerber.png",
	"data/TEXTURE/MenuberIndicate.png",
	"data/TEXTURE/CheckBox_Checkin.png",
	"data/TEXTURE/CheckBox_Checkout.png",
	"data/TEXTURE/OptionWindowCloseButton.png",
	"data/TEXTURE/BGMMixerBarIcon.png"
};
/* ユーティリティテクスチャ */
char *g_UtilityTexName[MAX_UTILITY_TEXTURE] = 
{// テクスチャファイル名
	
};

/*******************************************************************************
関数名:	HRESULT InitTexture(void)
引数:	なし
戻り値:	HRESULT型	S_OK:正常終了
					E_FAIL:初期化失敗
説明:	Textureの初期化
*******************************************************************************/
HRESULT InitTexture(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// タイトルテクスチャの読み込み
	for (int nIdxTexture = 0 ; nIdxTexture < MAX_TITLE_TEXTURE ; nIdxTexture++)
	{
		D3DXCreateTextureFromFile(pDevice, g_TitleTexName[nIdxTexture], &g_pD3DTextureTitle[nIdxTexture]);
	}
	// リザルトテクスチャの読み込み
	for (int nIdxTexture = 0 ; nIdxTexture < MAX_RESULT_TEXTURE ; nIdxTexture++)
	{
		D3DXCreateTextureFromFile(pDevice, g_ResultTexName[nIdxTexture], &g_pD3DTextureResult[nIdxTexture]);
	}
	// 3D空間内のテクスチャの読み込み
	for (int nIdxTexture = 0 ; nIdxTexture < MAX_SPACE_TEXTURE ; nIdxTexture++)
	{
		D3DXCreateTextureFromFile(pDevice, g_SpaceTexName[nIdxTexture], &g_pD3DTextureSpace[nIdxTexture]);
	}
	// UIテクスチャの読み込み
	for (int nIdxTexture = 0 ; nIdxTexture < MAX_UI_TEXTURE ; nIdxTexture++)
	{
		D3DXCreateTextureFromFile(pDevice, g_UITexName[nIdxTexture], &g_pD3DTextureUI[nIdxTexture]);
	}
	// ユーティリティテクスチャの読み込み
	for (int nIdxTexture = 0 ; nIdxTexture < MAX_UTILITY_TEXTURE ; nIdxTexture++)
	{
		D3DXCreateTextureFromFile(pDevice, g_UtilityTexName[nIdxTexture], &g_pD3DTextureUtility[nIdxTexture]);
	}
	

	return S_OK;
}
/*******************************************************************************
関数名:	void UninitTexture(void)
引数:	なし
戻り値:	なし
説明:	Textureの終了処理
*******************************************************************************/
void UninitTexture(void)
{
	// タイトルテクスチャの終了
	for (int nIdxTexture = 0 ; nIdxTexture < MAX_TITLE_TEXTURE ; nIdxTexture++)
	{
		if(g_pD3DTextureTitle[nIdxTexture] != NULL)
		{
			g_pD3DTextureTitle[nIdxTexture] -> Release();
			g_pD3DTextureTitle[nIdxTexture] = NULL;
		}
	}
	// リザルトテクスチャの終了
	for (int nIdxTexture = 0 ; nIdxTexture < MAX_RESULT_TEXTURE ; nIdxTexture++)
	{
		if(g_pD3DTextureResult[nIdxTexture] != NULL)
		{
			g_pD3DTextureResult[nIdxTexture] -> Release();
			g_pD3DTextureResult[nIdxTexture] = NULL;
		}
	}
	// 3D空間内のテクスチャの終了
	for (int nIdxTexture = 0 ; nIdxTexture < MAX_SPACE_TEXTURE ; nIdxTexture++)
	{
		if(g_pD3DTextureSpace[nIdxTexture] != NULL)
		{
			g_pD3DTextureSpace[nIdxTexture] -> Release();
			g_pD3DTextureSpace[nIdxTexture] = NULL;
		}
	}
	// UIテクスチャの終了
	for (int nIdxTexture = 0 ; nIdxTexture < MAX_UI_TEXTURE ; nIdxTexture++)
	{
		if(g_pD3DTextureUI[nIdxTexture] != NULL)
		{
			g_pD3DTextureUI[nIdxTexture] -> Release();
			g_pD3DTextureUI[nIdxTexture] = NULL;
		}
	}
	// ユーティリティテクスチャの終了
	for (int nIdxTexture = 0 ; nIdxTexture < MAX_UTILITY_TEXTURE ; nIdxTexture++)
	{
		if(g_pD3DTextureUtility[nIdxTexture] != NULL)
		{
			g_pD3DTextureUtility[nIdxTexture] -> Release();
			g_pD3DTextureUtility[nIdxTexture] = NULL;
		}
	}
}
/*******************************************************************************
関数名:	LPDIRECT3DTEXTURE9 *GetTitleTexture(void)
引数:	なし
戻り値:	LPDIRECT3DTEXTURE9型	g_pD3DTextureTitle[0]のアドレス
説明:	タイトルテクスチャのポインタ配列の先頭アドレスを取得
*******************************************************************************/
LPDIRECT3DTEXTURE9 *GetTitleTexture(void)
{
	// タイトルテクスチャのポインタ配列の先頭アドレスを返す
	return &g_pD3DTextureTitle[0];
}
/*******************************************************************************
関数名:	LPDIRECT3DTEXTURE9 *GetResultTexture(void)
引数:	なし
戻り値:	LPDIRECT3DTEXTURE9型	g_pD3DTextureResult[0]のアドレス
説明:	タイトルテクスチャのポインタ配列の先頭アドレスを取得
*******************************************************************************/
LPDIRECT3DTEXTURE9 *GetResultTexture(void)
{
	// リザルトテクスチャのポインタ配列の先頭アドレスを返す
	return &g_pD3DTextureResult[0];
}
/*******************************************************************************
関数名:	LPDIRECT3DTEXTURE9 *GetOnFieldTexture(void)
引数:	なし
戻り値:	LPDIRECT3DTEXTURE9型	g_pD3DTextureSpace[0]のアドレス
説明:	3D空間内のテクスチャへのポインタ配列の先頭アドレスを取得
*******************************************************************************/
LPDIRECT3DTEXTURE9 *GetSpaceTexture(void)
{
	// 3D空間内のテクスチャへのポインタ配列の先頭アドレスを返す
	return &g_pD3DTextureSpace[0];
}
/*******************************************************************************
関数名:	LPDIRECT3DTEXTURE9 *GetUITexture(void)
引数:	なし
戻り値:	LPDIRECT3DTEXTURE9型	g_pD3DTextureUI[0]のアドレス
説明:	UIテクスチャへのポインタ配列の先頭アドレスを取得
*******************************************************************************/
LPDIRECT3DTEXTURE9 *GetUITexture(void)
{
	// UIテクスチャへのポインタ配列の先頭アドレスを返す
	return &g_pD3DTextureUI[0];
}
/*******************************************************************************
関数名:	LPDIRECT3DTEXTURE9 *GetUtilityTexture(void)
引数:	なし
戻り値:	LPDIRECT3DTEXTURE9型	g_pD3DTextureUtility[0]のアドレス
説明:	ユーティリティテクスチャへのポインタ配列の先頭アドレスを取得
*******************************************************************************/
LPDIRECT3DTEXTURE9 *GetUtilityTexture(void)
{
	// ユーティリティテクスチャへのポインタ配列の先頭アドレスを返す
	return &g_pD3DTextureUtility[0];
}
