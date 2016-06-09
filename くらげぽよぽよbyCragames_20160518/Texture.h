/*******************************************************************************
* タイトル:		Textureヘッダーファイル
* プログラム名:	Texture.h
* 作成者:		GP11A331 4 伊原佑稀
* 作成日:		2016/01/29
********************************************************************************
* 更新履歴:		- 2016/02/23	GP11A331 4 伊原佑稀
*					- V1.00		Initial Version
*******************************************************************************/
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "Main.h"

/*******************************************************************************
* 構造体定義
*******************************************************************************/

/*******************************************************************************
* 列挙体定義
*******************************************************************************/
typedef enum
{
	TEX_SHADOW = 0,
	MAX_SPACE_TEXTURE
} SPACE_TEXTURE;

typedef enum
{
	UI_TEXTURE_OPTION_WINDOW = 0,					// オプションのウィンドウ
	UI_TEXTURE_BGM_MIXERBAR,							// BGMのミキサーバー
	UI_TEXTURE_SE_MIXERBAR,							// SEのミキサーバー
	UI_TEXTURE_MENUBER_INDICATE,						// メニューバーを表示するチェックボックス
	UI_TEXTURE_CHECKBOX_CHECKIN,						// チェックがついてるチェックボックス
	UI_TEXTURE_CHECKBOX_CHECKOUT,					// チェックがついてないチェックボックス
	UI_TEXTURE_OPTION_WINDOW_CLOSEBUTTON,				// オプションのウィンドウの閉じるボタン
	UI_TEXTURE_MIXERBAR_ICON,						// BGM,SEミキサーバーのアイコン
	MAX_UI_TEXTURE
} UI_TEXTURE, USER_INTERFACE_TEXTURE;

typedef enum
{
	MAX_UTILITY_TEXTURE = 1
} UTILITY_TEXTURE;

typedef enum
{
	MAX_TITLE_TEXTURE = 1
} TITLE_TEXTURE;

typedef enum
{
	MAX_RESULT_TEXTURE = 1
} RESULT_TEXTURE;

//*****************************************************************************
// マクロ定義
//*****************************************************************************

/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/
HRESULT InitTexture(void);
void UninitTexture(void);
LPDIRECT3DTEXTURE9 *GetTitleTexture(void);
LPDIRECT3DTEXTURE9 *GetResultTexture(void);
LPDIRECT3DTEXTURE9 *GetSpaceTexture(void);
LPDIRECT3DTEXTURE9 *GetUITexture(void);
LPDIRECT3DTEXTURE9 *GetUtilityTexture(void);
#endif