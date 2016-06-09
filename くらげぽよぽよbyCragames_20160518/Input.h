/*******************************************************************************
* �^�C�g��:		���͏����w�b�_�[�t�@�C��
* �v���O������:	input.h
* �쐬��:		GP11A331 4�� �Ɍ��C�H
* �쐬��:		2015/10/21
********************************************************************************
* �X�V����:		- 2015/11/16	�Ɍ��C�H
*					- V1.00		Initial Version
*******************************************************************************/
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

/*******************************************************************************
* �񋓑̒�`
*******************************************************************************/
typedef enum
{
	CURSOR_HAND = 0,
	CURSOR_SWORD,
	CURSOR_HAND_ORANGE,
	MAX_CURSOR
} CURSOR;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
// �L�[�{�[�h�֘A
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nkey);
bool GetKeyboardTrigger(int nkey);
bool GetKeyboardRelease(int nkey);
bool GetKeyboardRepeat(int nkey);

// �}�E�X�֘A
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

// �W���C�p�b�h�֘A
HRESULT InitJoypad(HINSTANCE hInstance, HWND hWnd);
void UninitJoypad(void);
void UpdateJoypad(void);
BOOL CALLBACK EnumJoyCallback(const DIDEVICEINSTANCE* lpddi, VOID* pvRef);

#endif