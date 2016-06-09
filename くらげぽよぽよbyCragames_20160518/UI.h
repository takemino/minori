/*******************************************************************************
* タイトル:		UI処理
* プログラム名:	UI.h
* 作成者:		GP11A331 4番 伊原佑稀
* 作成日:		2016/02/01
********************************************************************************
* 更新履歴:		- 2016/02/25	伊原佑稀
*					- V1.00		Initial Version
*******************************************************************************/
#ifndef _UI_H_
#define _UI_H_

#include "Main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

/*******************************************************************************
* 列挙体定義
*******************************************************************************/
typedef enum OPTION
{
	OPTION_WINDOW = 0,
	BGM_MIXERBAR,
	SE_MIXERBAR,
	MENUBAR_INDICATE,
	CHECKBOX,
	OPTION_WINDOW_CLOSEBUTTON,
	BGM_MIXERBAR_ICON,
	SE_MIXERBAR_ICON,
	MAX_OPTION
};

//*****************************************************************************
// 構造体
//*****************************************************************************
typedef struct UI_2D
{
	LPDIRECT3DVERTEXBUFFER9	pD3DVtxBuff;			// 頂点バッファインターフェースへのポインタ
	D3DXVECTOR3 vPos;								// 座標
	D3DXVECTOR3 vPos2;
	D3DXVECTOR3 vScl;								// サイズ
	D3DXCOLOR	col;								// 色
	int			nCnt;
	bool		bUse;								// 使用してるかどうか
	bool		bChoice;							// 選択フラグ
	D3DXVECTOR2 vTexPatSize;						// テクスチャのどの部分をポリゴンに貼るか決める変数
};

typedef struct UI_3D
{
	D3DXMATRIX mtxWorld;							// ワールドマトリックス
	LPDIRECT3DVERTEXBUFFER9	pD3DVtxBuff;			// 頂点バッファインターフェースへのポインタ
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vRot;
	D3DXVECTOR3 vScl;
	D3DXCOLOR	col;
	int			nCnt;
	bool		bUse;
	bool		bChoice;
	D3DXVECTOR2 vTexPatSize;				
	D3DXVECTOR3 vVtxPos[4];					//ビルボード当たり判定用の頂点座標
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitUI(void);
void UninitUI(void);
void UpdateUI(void);
void DrawUI(void);

#endif
