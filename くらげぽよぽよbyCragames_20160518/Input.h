/*******************************************************************************
* タイトル:		入力処理ヘッダーファイル
* プログラム名:	input.h
* 作成者:		GP11A331 4番 伊原佑稀
* 作成日:		2015/10/21
********************************************************************************
* 更新履歴:		- 2015/11/16	伊原佑稀
*					- V1.00		Initial Version
*******************************************************************************/
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

/*******************************************************************************
* 列挙体定義
*******************************************************************************/
typedef enum
{
	CURSOR_HAND = 0,
	CURSOR_SWORD,
	CURSOR_HAND_ORANGE,
	MAX_CURSOR
} CURSOR;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
// キーボード関連
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nkey);
bool GetKeyboardTrigger(int nkey);
bool GetKeyboardRelease(int nkey);
bool GetKeyboardRepeat(int nkey);

// マウス関連
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd);
void UninitMouse(void);
void UpdateMouse(void);
void SetCursor(CURSOR Cursor);
HCURSOR *GetpHandleCursor(void);
bool GetMouseLeftPress(void);
bool GetMouseLeftTrigger(void);
bool GetMouseLeftRelease(void);
bool GetMouseRightPress(void);
bool GetMouseRightTrigger(void);
bool GetMouseRightRelease(void);
bool GetMouseCenterPress(void);
bool GetMouseCenterTrigger(void);
POINT GetMouseScreenPos(void);
POINT GetMouseClientPos(void);
long GetMouseAxisX(void);
long GetMouseAxisY(void);
long GetMouseAxisZ(void);

// ジョイパッド関連
HRESULT InitJoypad(HINSTANCE hInstance, HWND hWnd);
void UninitJoypad(void);
void UpdateJoypad(void);
BOOL CALLBACK EnumJoyCallback(const DIDEVICEINSTANCE* lpddi, VOID* pvRef);

#endif