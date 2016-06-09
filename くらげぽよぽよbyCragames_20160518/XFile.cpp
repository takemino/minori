/*******************************************************************************
* タイトル:		Xファイル処理
* プログラム名:	XFile.cpp
* 作成者:		GP11A331 4番 伊原佑稀
* 作成日:		2016/01/18
********************************************************************************
* 更新履歴:		- 2016/01/18	伊原佑稀
*					- V1.00		Initial Version
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "XFile.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
XFILE g_aJellyfishXFile[MAX_JELLYFISH_XFILE];

char *g_pJellyfishXFileName[MAX_JELLYFISH_XFILE] = 
{ // Xファイル名
	{"data/XFILE/TestModel.x"},
};

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitXFile(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// プレイヤーキャラの読み込み
	for(int nIdx = 0; nIdx < MAX_JELLYFISH_XFILE; nIdx++)
	{
		 g_aJellyfishXFile[nIdx].pD3DXMesh = NULL;	
		 g_aJellyfishXFile[nIdx].pD3DXBuffMate = NULL;
		 g_aJellyfishXFile[nIdx].nNumMate = 0;
		 g_aJellyfishXFile[nIdx].pD3DTexture = NULL;	

		// Xファイルの読み込み
		if(FAILED(D3DXLoadMeshFromX(
								g_pJellyfishXFileName[nIdx],			// 読み込むモデルファイル名(Xファイル)
								D3DXMESH_SYSTEMMEM,						// メッシュの作成オプションを指定
								pDevice,								// IDirect3DDevice9インターフェイスへのポインタ
								NULL,									// 隣接性データを含むバッファへのポインタ
								&g_aJellyfishXFile[nIdx].pD3DXBuffMate,	// マテリアルデータを含むバッファへのポインタ
								NULL,									// エフェクトインスタンスの配列を含むバッファへのポインタ
								&g_aJellyfishXFile[nIdx].nNumMate,		// D3DXMATERIAL構造体の数
								&g_aJellyfishXFile[nIdx].pD3DXMesh)))	// ID3DXMeshインターフェイスへのポインタのアドレス
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitXFile(void)
{
	// プレイヤーキャラの終了処理
	for(int nIdx = 0; nIdx < MAX_JELLYFISH_XFILE; nIdx++)
	{
		if( g_aJellyfishXFile[nIdx].pD3DTexture != NULL)
		{// テクスチャの開放
			 g_aJellyfishXFile[nIdx].pD3DTexture -> Release();
			 g_aJellyfishXFile[nIdx].pD3DTexture = NULL;
		}

		if( g_aJellyfishXFile[nIdx].pD3DXMesh != NULL)
		{// メッシュの開放
			 g_aJellyfishXFile[nIdx].pD3DXMesh -> Release();
			 g_aJellyfishXFile[nIdx].pD3DXMesh = NULL;
		}

		if( g_aJellyfishXFile[nIdx].pD3DXBuffMate != NULL)
		{// マテリアルの開放
			 g_aJellyfishXFile[nIdx].pD3DXBuffMate -> Release();
			 g_aJellyfishXFile[nIdx].pD3DXBuffMate = NULL;
		}
	}
	
}
//=============================================================================
// プレイヤーキャラファイル構造体ワークの先頭アドレスを取得
//=============================================================================
XFILE *GetpJellyfishXFile(void)
{
	return &g_aJellyfishXFile[0];
}

