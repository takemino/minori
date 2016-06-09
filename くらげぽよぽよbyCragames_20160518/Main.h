/*******************************************************************************
* タイトル:		メイン処理
* プログラム名:	Main.h
* 作成者:		GP11A331 4番 伊原佑稀
* 作成日:		2016/01/21
********************************************************************************
* 更新履歴:		- 2016/01/22	伊原佑稀
*					- V1.00		Initial Version
*******************************************************************************/
#ifndef _MAIN_H_
#define _MAIN_H_

#define USE_SOUND		// サウンド使用の有無
//#undef USE_SOUND
//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <windows.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800)
#include "dinput.h"
#include "input.h"

#ifdef USE_SOUND
#include "xaudio2.h"		// XAudio2関連のヘッダー
#endif

//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************
#if 1	// [ここを"0"にした場合、"構成プロパティ" -> "リンカ" -> "入力" -> "追加の依存ファイル"に対象ライブラリを設定する]
#pragma comment (lib, "d3d9.lib")		// 描画処理に必要
#pragma comment (lib, "d3dx9.lib")		// [d3d9.lib]の拡張ライブラリ
#pragma comment (lib, "dxguid.lib")		// DirectXコンポーネント使用に必要
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "winmm.lib")
#endif

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

#if 0
#define SCREEN_WIDTH					(1760)//(1280)	// ウインドウの幅
#define SCREEN_HEIGHT					(990)//(720)	// ウインドウの高さ
#else
#define SCREEN_WIDTH					(800)//(1280)	// ウインドウの幅
#define SCREEN_HEIGHT					(450)//(720)	// ウインドウの高さ
#endif
#define SCREEN_WIDTH_DIFFERENCE			(10)
#define SCREEN_HEIGHT_DIFFERENCE		(10)

#define NUM_VERTEX (4)
#define NUM_POLYGON (2)

#define SAFE_RELEASE(ptr)			{ if(ptr) { (ptr)->Release(); (ptr) = NULL; } }

/*******************************************************************************
* 構造体定義
*******************************************************************************/
// 上記２Ｄポリゴン頂点フォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR3 vtx;	// 頂点座標
	float		rhw;	// テクスチャのパースペクティブコレクト用
	D3DCOLOR	col;	// 反射光(頂点カラー)
	D3DXVECTOR2 tex;	// テクスチャ座標
} VERTEX_2D;

// 上記３Ｄポリゴン頂点フォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR3 vtx;	// 頂点座標
	D3DXVECTOR3 nor;	// 法線ベクトル
	D3DCOLOR	col;	// 反射光
	D3DXVECTOR2 tex;	// テクスチャ座標
} VERTEX_3D;

typedef struct SCREEN
{
	float nWidth;
	float nHeight;
};

typedef struct
{
	LPDIRECT3DVERTEXBUFFER9	pD3DVtxBuff;	//頂点バッファインターフェースへのポインタ
	D3DXVECTOR3 pos;						//フレーム、ポイントの２つ
	D3DXVECTOR2 size;
	D3DXCOLOR	col;
	bool		bUse;
	int			nTransCnt;
	int			nCurKeyFrame;
	int			nNextKeyFrame;
} IMAGE_2D_STRUCT;

typedef struct
{
	D3DXMATRIX mtxWorld;					// ワールドマトリックス
	D3DXMATRIX mtxLocal;					// ローカルマトリックス
	LPDIRECT3DVERTEXBUFFER9	pD3DVtxBuff;	//頂点バッファインターフェースへのポインタ
	D3DXVECTOR3 pos;						//フレーム、ポイントの２つ
	D3DXVECTOR2 size;
	D3DXCOLOR	col;
	bool		bUse;
} IMAGE_3D_STRUCT;

/*******************************************************************************
* 列挙体定義
*******************************************************************************/
typedef enum
{
	MODE_TITLE = 0,
	MODE_GAME,
	MODE_RESULT,
	MODE_MAX
}MODE;

typedef enum
{
	FLICK_ON = 0,
	FLICK_OFF
} FLICK;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LPDIRECT3DDEVICE9 GetDevice(void);
MODE GetMainMode(void);
void SetMode(MODE mode);
void EndMode(void);
HWND GetHandleWindow(void);
HINSTANCE GetHandleInstance(void);
void UpdateWindowSize(void);
SCREEN GetScreenInfo(void);
void InitWindowSize(void);

#endif