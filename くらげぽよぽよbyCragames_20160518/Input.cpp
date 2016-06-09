/*******************************************************************************
* �^�C�g��:		���͏���
* �v���O������:	Input.cpp
* �쐬��:		GP11A331 4�� �Ɍ��C�H
* �쐬��:		2015/10/21
********************************************************************************
* �X�V����:		- 2016/01/26	�Ɍ��C�H
*					- V1.00		Initial Version
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "Input.h"
#include "DebugProc.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NUM_KEY_MAX (256)
#define LIMIT_COUNT_REPEAT (20) // ���s�[�g�J�E���^���~�b�g

#define	NUM_MOUSE_BUTTON_MAX	(8)		// �}�E�X�̃{�^���ő吔
#define	MOUSE_BUTTON_LEFT		(0)		// �}�E�X�̍��{�^��
#define	MOUSE_BUTTON_RIGHT		(1)		// �}�E�X�̉E�{�^��
#define	MOUSE_BUTTON_CENTER		(2)		// �}�E�X�̒����{�^��

#define MAX_CONTROLER			(2)		// �R���g���[���ő吔(�g�����ɉ����ĕύX���邱��)

/*******************************************************************************
* �\���̒�`
*******************************************************************************/

/*******************************************************************************
* �v���g�^�C�v�錾
*******************************************************************************/
HRESULT InitInput(HINSTANCE hInstance, HWND hWnd);
void UninitInput(void);
void UpdateInput(void);

/*******************************************************************************
* �O���[�o���ϐ�
*******************************************************************************/
LPDIRECTINPUT8			g_pDInput = NULL;					// DirectInput�C���^�[�t�F�[�X�ւ̃|�C���^
LPDIRECTINPUTDEVICE8	g_pDIDevKeyboard = NULL;			// ���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
LPDIRECTINPUTDEVICE8	g_pDevMouse = NULL;					// ���̓f�o�C�X(�}�E�X)�ւ̃|�C���^
// �L�[�{�[�h���
BYTE					g_aKeyState[NUM_KEY_MAX];			// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
BYTE					g_aKeyStateTrigger[NUM_KEY_MAX];	// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
BYTE					g_aKeyStateRelease[NUM_KEY_MAX];	// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
BYTE					g_aKeyStateRepeat[NUM_KEY_MAX];		// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
BYTE					g_aKeyStateRepeatCnt[NUM_KEY_MAX];	// �L�[�{�[�h�̃��s�[�g�J�E���^
// �}�E�X���
DIMOUSESTATE2			g_mouseState;						// �}�E�X�̓��͏�񃏁[�N
DIMOUSESTATE2			g_mouseStateTrigger;				// �}�E�X�̃g���K�[��񃏁[�N
DIMOUSESTATE2			g_mouseStateRelease;				// �}�E�X�̃����[�X��񃏁[�N
POINT					g_mouseScreenPos;
POINT					g_mouseClientPos;
POINT					g_mouseWindowPos;
HCURSOR					g_hCursor[MAX_CURSOR];
bool					g_bClipCursor = true;				// �}�E�X���E�C���h�E���ɗ��߂�t���O
// �p�b�h���
DIJOYSTATE				g_joyState[MAX_CONTROLER];			// �W���C�p�b�h���z��
DIJOYSTATE				g_joyStatePrev[MAX_CONTROLER];		// �W���C�p�b�h���z��i���O�j
LPDIRECTINPUTDEVICE8	g_pDIDevJoypad[MAX_CONTROLER];		// IDirectInputDevice8�C���^�[�t�F�[�X�ւ̃|�C���^(�W���C�p�b�h)
int						g_nJoypadNum = 0;					// ���������W���C�p�b�h�̐�
BYTE					g_joyStateTrigger[MAX_CONTROLER][32];

/*******************************************************************************
�֐���:	HRESULT InitInput(HINSTANCE hInstance, HWND hWnd)
����:	HINSTANCE hInstance, HWND hWnd
�߂�l:	HRESULT�^	S_OK:����I��
					E_FAIL:���������s
����:	input�̏�����
*******************************************************************************/
HRESULT InitInput(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr;

	if(g_pDInput == NULL) // !g_pDInput
	{
		// DirectInput�I�u�W�F�N�g�̍쐬
		hr = DirectInput8Create(hInstance,DIRECTINPUT_VERSION,IID_IDirectInput8,(void**)&g_pDInput,NULL);
		
		return hr;
	}

	return S_OK;
}
/*******************************************************************************
�֐���:	void UninitInput(void)
����:	�Ȃ�
�߂�l:	�Ȃ�
����:	input�̏I������
*******************************************************************************/
void UninitInput(void)
{
	if(g_pDInput != NULL)
	{// DirectInput�I�u�W�F�N�g�̊J��
		g_pDInput -> Release();
		g_pDInput = NULL;	
	}
}
/*******************************************************************************
�֐���:	void UpdateInput(void)
����:	�Ȃ�
�߂�l:	�Ȃ�
����:	input�̍X�V����
*******************************************************************************/
void UpdateInput(void)
{
}
/*******************************************************************************
�֐���:	HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
����:	HINSTANCE hInstance, HWND hWnd
�߂�l:	HRESULT�^
����:	Keyboard�̏���������
*******************************************************************************/
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr;

	// ���͏����̏�����
	hr = InitInput(hInstance, hWnd);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "DirectInput�I�u�W�F�N�g�����˂��I", "�x���I", MB_ICONWARNING);
		return hr;
	}

	// �f�o�C�X�I�u�W�F�N�g���쐬
	hr = g_pDInput -> CreateDevice(GUID_SysKeyboard,&g_pDIDevKeyboard,NULL);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "�L�[�{�[�h���˂��I", "�x���I", MB_ICONWARNING);
		return hr;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	hr = g_pDIDevKeyboard -> SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return hr;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	hr = g_pDIDevKeyboard -> SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if(FAILED(hr))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̋������[�h��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return hr;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	g_pDIDevKeyboard -> Acquire();
	
	return S_OK;
}
/*******************************************************************************
�֐���:	void UninitKeyboard(void)
����:	�Ȃ�
�߂�l:	�Ȃ�
����:	Keyboard�̏I������
*******************************************************************************/
void UninitKeyboard(void)
{
	if(g_pDIDevKeyboard != NULL)
	{// ���̓f�o�C�X(�L�[�{�[�h)�̊J��
		// �L�[�{�[�h�ւ̃A�N�Z�X�����J��(���͐���I��)
		g_pDIDevKeyboard -> Unacquire();
		g_pDIDevKeyboard -> Release();
		g_pDIDevKeyboard = NULL;
		
	}

	// ���͏����̏I������
	UninitInput();
}
/*******************************************************************************
�֐���:	void UpdateKeyboard(void)
����:	�Ȃ�
�߂�l:	�Ȃ�
����:	Keyboard�̍X�V����
*******************************************************************************/
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];
	// �f�o�C�X����f�[�^���擾
	if(SUCCEEDED(g_pDIDevKeyboard -> GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for(int nCntkey = 0; nCntkey < NUM_KEY_MAX; nCntkey++)
		{
			// �L�[�g���K�[ �����[�X���𐶐�
			g_aKeyStateTrigger[nCntkey] = (g_aKeyState[nCntkey] ^ aKeyState[nCntkey]) & aKeyState[nCntkey];
			g_aKeyStateRelease[nCntkey] = (g_aKeyState[nCntkey] ^ aKeyState[nCntkey]) & ~aKeyState[nCntkey];
			// ���s�[�g���𐶐�
			if(aKeyState[nCntkey])
			{
				if(g_aKeyStateRepeatCnt[nCntkey] < LIMIT_COUNT_REPEAT)
				{
					g_aKeyStateRepeatCnt[nCntkey]++;
					if(g_aKeyStateRepeatCnt[nCntkey] == 1 || g_aKeyStateRepeatCnt[nCntkey] >= LIMIT_COUNT_REPEAT)
					{// �L�[�������n�߂��ŏ��̃t���[���A�܂��͈�莞�Ԍo�߂ŏ��ON
						g_aKeyStateRepeat[nCntkey] = aKeyState[nCntkey];
					}
					else
					{
						g_aKeyStateRepeat[nCntkey] = 0;
					}
				}
			}
			else
			{
				g_aKeyStateRepeatCnt[nCntkey] = 0;
				g_aKeyStateRepeat[nCntkey] = 0;
			}
			// �L�[�v���X����ۑ�
			g_aKeyState[nCntkey] = aKeyState[nCntkey];
		}
	}
	else
	{
		g_pDIDevKeyboard -> Acquire();
	}
}
/*******************************************************************************
�֐���:	bool GetKeyboardPress(int nkey)
����:	int nkey
�߂�l:	bool�^
����:	Keyboard�̃v���X��Ԃ̎擾
*******************************************************************************/
bool GetKeyboardPress(int nkey)
{
	return (g_aKeyState[nkey] & 0x80 ? true:false);
}
/*******************************************************************************
�֐���:	bool GetKeyboardTrigger(int nkey)
����:	int nkey
�߂�l:	bool�^
����:	Keyboard�̃g���K�[��Ԃ̎擾
*******************************************************************************/
bool GetKeyboardTrigger(int nkey)
{
	return (g_aKeyStateTrigger[nkey] & 0x80 ? true:false);
}
/*******************************************************************************
�֐���:	bool GetKeyboardRelease(int nkey)
����:	int nkey
�߂�l:	bool�^
����:	Keyboard�̃����[�X��Ԃ̎擾
*******************************************************************************/
bool GetKeyboardRelease(int nkey)
{
	return (g_aKeyStateRelease[nkey] & 0x80 ? true:false);
}
/*******************************************************************************
�֐���:	bool GetKeyboardRepeat(int nkey)
����:	int nkey
�߂�l:	bool�^
����:	Keyboard�̃��s�[�g��Ԃ̎擾
*******************************************************************************/
bool GetKeyboardRepeat(int nkey)
{
	return (g_aKeyStateRepeat[nkey] & 0x80 ? true:false);
}
//=============================================================================
// �}�E�X�̏�����
//=============================================================================
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr;

	// ���͏����̏�����
	hr = InitInput(hInstance, hWnd);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "DirectInput�I�u�W�F�N�g�����˂��I", "�x���I", MB_ICONWARNING);
		return hr;
	}

	// �f�o�C�X�I�u�W�F�N�g���쐬
	hr = g_pDInput->CreateDevice(GUID_SysMouse, &g_pDevMouse, NULL);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "�}�E�X���˂��I", "�x���I", MB_ICONWARNING);
		return hr;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	hr = g_pDevMouse->SetDataFormat(&c_dfDIMouse2);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "�}�E�X�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return hr;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	hr = g_pDevMouse->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if(FAILED(hr))
	{
		MessageBox(hWnd, "�}�E�X�̋������[�h��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return hr;
	}

	// �f�o�C�X�̃v���p�e�B��ݒ�
	{
		DIPROPDWORD dipdw;

		dipdw.diph.dwSize = sizeof(dipdw);
		dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
		dipdw.diph.dwObj = 0;
		dipdw.diph.dwHow = DIPH_DEVICE;
		dipdw.dwData = DIPROPAXISMODE_REL;

		hr = g_pDevMouse->SetProperty(DIPROP_AXISMODE, &dipdw.diph);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "�}�E�X�̃f�o�C�X�̃v���p�e�B��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
			return hr;
		}
	}

	// �}�E�X�ւ̃A�N�Z�X�����l��(���͐���J�n)
	g_pDevMouse->Acquire();

	/* �}�E�X�J�[�\���摜�̓ǂݍ��� */
	{
		g_hCursor[0] = LoadCursorFromFile("data/MOUSE/MouseCursorHand.cur");
		g_hCursor[1] = LoadCursorFromFile("data/MOUSE/MouseCursorSword.cur");
		g_hCursor[2] = LoadCursorFromFile("data/MOUSE/MouseCursorHandOrange.cur");
	}
	return S_OK;
}

//=============================================================================
// �}�E�X�̏I������
//=============================================================================
void UninitMouse(void)
{
	// ���͏����̏I������
	UninitInput();

	if(g_pDevMouse)
	{
		// �}�E�X�ւ̃A�N�Z�X�����J��
		g_pDevMouse->Unacquire();

		g_pDevMouse->Release();
		g_pDevMouse = NULL;
	}
}

//=============================================================================
// �}�E�X�̍X�V����
//=============================================================================
void UpdateMouse(void)
{
	DIMOUSESTATE2 mouseState;
	HWND hWnd = GetHandleWindow();
	POINT mousePos;

	// �}�E�X�̌��݂̍��W���擾����
	GetCursorPos(&mousePos);
	// �}�E�X�̃X�N���[�����W����
	g_mouseScreenPos = mousePos;
	// �}�E�X�̃X�N���[�����W���N���C�A���g���W�֕ϊ�
	ScreenToClient(hWnd, &mousePos);
	// �}�E�X�̃N���C�A���g���W����
	g_mouseClientPos = mousePos;
	PrintDebugProc("[�}�E�XX���W : (%d)]\n",g_mouseClientPos.x);
	PrintDebugProc("[�}�E�XY���W : (%d)]\n\n",g_mouseClientPos.y);
	
#if 0
	// �Q�[�����}�E�X������ʓ��ɌŒ肷�鏈��
	if(g_bClipCursor)
	{
		POINT ClientOrigin = {0,0};
		RECT Rect;
		ClientToScreen(hWnd,  &ClientOrigin);
		Rect.left = ClientOrigin.x;
		Rect.right = Rect.left + SCREEN_WIDTH - GetSystemMetrics(SM_CXDLGFRAME) * 4;
		Rect.top = ClientOrigin.y;
		Rect.bottom = Rect.top + SCREEN_HEIGHT - GetSystemMetrics(SM_CXDLGFRAME) * 4;
		ClipCursor(&Rect);
	}
	if(GetKeyboardPress(DIK_LCONTROL) && GetKeyboardTrigger(DIK_SPACE))
	{
		if(g_bClipCursor)
		{
			g_bClipCursor = false;
			ClipCursor(NULL);
		}
		else
		{
			g_bClipCursor = true;
		}
	}
#endif

	// �f�o�C�X����f�[�^���擾
	if(SUCCEEDED(g_pDevMouse->GetDeviceState(sizeof(mouseState), &mouseState)))
	{
		g_mouseStateTrigger.lX = ((g_mouseState.lX ^ mouseState.lX) & mouseState.lX);
		g_mouseStateTrigger.lY = ((g_mouseState.lY ^ mouseState.lY) & mouseState.lY);
		g_mouseStateTrigger.lZ = ((g_mouseState.lZ ^ mouseState.lZ) & mouseState.lZ);

		
		for(int nCntKey = 0; nCntKey < NUM_MOUSE_BUTTON_MAX; nCntKey++)
		{
			g_mouseStateTrigger.rgbButtons[nCntKey] = ((g_mouseState.rgbButtons[nCntKey] ^ mouseState.rgbButtons[nCntKey]) & mouseState.rgbButtons[nCntKey]);
			g_mouseStateRelease.rgbButtons[nCntKey] = ((g_mouseState.rgbButtons[nCntKey] ^ mouseState.rgbButtons[nCntKey]) & ~mouseState.rgbButtons[nCntKey]);
		}

		g_mouseState = mouseState;
	}
	else
	{
		// �}�E�X�ւ̃A�N�Z�X�����l��(���͐���J�n)
		g_pDevMouse->Acquire();
	}
}
/*******************************************************************************
�֐���:	void SetCursor(CURSOR Cursor)
����:	CURSOR Cursor
�߂�l:	�Ȃ�
����:	�J�[�\�����Z�b�g
*******************************************************************************/
void SetCursor(CURSOR Cursor)
{
	HWND hWnd;
	hWnd = GetHandleWindow();
	SetClassLong(hWnd, GCL_HCURSOR, (LONG)g_hCursor[Cursor]);
}
//=============================================================================
// �}�E�X�J�[�\���摜�n���h���擾
//=============================================================================
HCURSOR *GetpHandleCursor(void)
{
	return &g_hCursor[0];
}
//=============================================================================
// �}�E�X�f�[�^�擾(���v���X)
//=============================================================================
bool GetMouseLeftPress(void)
{
	return (g_mouseState.rgbButtons[MOUSE_BUTTON_LEFT] & 0x80 ? true: false);
}

//=============================================================================
// �}�E�X�f�[�^�擾(���g���K�[)
//=============================================================================
bool GetMouseLeftTrigger(void)
{
	return (g_mouseStateTrigger.rgbButtons[MOUSE_BUTTON_LEFT] & 0x80 ? true: false);
}

//=============================================================================
// �}�E�X�f�[�^�擾(�������[�X)
//=============================================================================
bool GetMouseLeftRelease(void)
{
	return (g_mouseStateRelease.rgbButtons[MOUSE_BUTTON_LEFT] & 0x80 ? true: false);
}

//=============================================================================
// �}�E�X�f�[�^�擾(�E�v���X)
//=============================================================================
bool GetMouseRightPress(void)
{
	return (g_mouseState.rgbButtons[MOUSE_BUTTON_RIGHT] & 0x80 ? true: false);
}

//=============================================================================
// �}�E�X�f�[�^�擾(�E�g���K�[)
//=============================================================================
bool GetMouseRightTrigger(void)
{
	return (g_mouseStateTrigger.rgbButtons[MOUSE_BUTTON_RIGHT] & 0x80 ? true: false);
}

//=============================================================================
// �}�E�X�f�[�^�擾(�E�����[�X)
//=============================================================================
bool GetMouseRightRelease(void)
{
	return (g_mouseStateRelease.rgbButtons[MOUSE_BUTTON_RIGHT] & 0x80 ? true: false);
}

//=============================================================================
// �}�E�X�f�[�^�擾(�����v���X)
//=============================================================================
bool GetMouseCenterPress(void)
{
	return (g_mouseState.rgbButtons[MOUSE_BUTTON_CENTER] & 0x80 ? true: false);
}

//=============================================================================
// �}�E�X�f�[�^�擾(�����g���K�[)
//=============================================================================
bool GetMouseCenterTrigger(void)
{
	return (g_mouseState.rgbButtons[MOUSE_BUTTON_CENTER] & 0x80 ? true: false);
}

//=============================================================================
// �}�E�X�f�[�^�擾(�w���ړ�)
//=============================================================================
long GetMouseAxisX(void)
{
	return g_mouseState.lX;
}
//=============================================================================
// �}�E�X�̃X�N���[�����W�擾
//=============================================================================
POINT GetMouseScreenPos(void)
{
	return g_mouseScreenPos;
}
//=============================================================================
// �}�E�X�̃N���C�A���g���W�擾
//=============================================================================
POINT GetMouseClientPos(void)
{
	return g_mouseClientPos;
}
//=============================================================================
// �}�E�X�f�[�^�擾(�x���ړ�)
//=============================================================================
long GetMouseAxisY(void)
{
	return g_mouseState.lY;
}

//=============================================================================
// �}�E�X�f�[�^�擾(�y���ړ�)
//=============================================================================
long GetMouseAxisZ(void)
{
	return g_mouseState.lZ;
}

//=============================================================================
// �W���C�p�b�h�̏�����
//=============================================================================
HRESULT InitJoypad(HINSTANCE hInstance, HWND hWnd)
{
	int nLoop;

	HRESULT hr;

	// ���͏����̏�����
	hr = InitInput(hInstance, hWnd);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "DirectInput�I�u�W�F�N�g�����˂��I", "�x���I", MB_ICONWARNING);
		return hr;
	}

	// ������
	for(nLoop = 0; nLoop < MAX_CONTROLER; nLoop++)
		g_pDIDevJoypad[nLoop] = NULL;

	// �f�o�C�X�I�u�W�F�N�g���쐬(�ڑ�����Ă���W���C�p�b�h��񋓂���)
	if(FAILED(g_pDInput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoyCallback, NULL, DIEDFL_ATTACHEDONLY)))
		return E_FAIL;

	// �W���C�p�b�h�̐���������
	for(nLoop = 0; nLoop < MAX_CONTROLER; nLoop++)
	{
		// �W���C�p�b�h���Ȃ��ꍇ�͂�����΂�
		if(g_pDIDevJoypad[nLoop] == NULL)
			continue;

		// �f�[�^�t�H�[�}�b�g�̐ݒ�
		if(FAILED(g_pDIDevJoypad[nLoop]->SetDataFormat(&c_dfDIJoystick)))
			return E_FAIL;

		// �������x���̐ݒ�
		if(FAILED(g_pDIDevJoypad[nLoop]->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
			return E_FAIL;

		// �f�o�C�X�ւ̓��͐���J�n
		g_pDIDevJoypad[nLoop]->Acquire();	
	}

	return S_OK;
}

//=============================================================================
// �W���C�p�b�h�₢���킹�p�R�[���o�b�N�֐�
//=============================================================================
BOOL CALLBACK EnumJoyCallback(const DIDEVICEINSTANCE* lpddi, VOID* pvRef)
{
	DIDEVCAPS	diDevCaps;			// �f�o�C�X���

	// �W���C�p�b�h�p�f�o�C�X�I�u�W�F�N�g���쐬
	if(FAILED(g_pDInput->CreateDevice(lpddi->guidInstance, &g_pDIDevJoypad[g_nJoypadNum], NULL)))
		return DIENUM_CONTINUE;		// �񋓂𑱂���

	// �W���C�p�b�h�̔\�͂𒲂ׂ�
	diDevCaps.dwSize = sizeof(DIDEVCAPS);
	if(FAILED(g_pDIDevJoypad[g_nJoypadNum]->GetCapabilities(&diDevCaps)))
	{
		if(g_pDIDevJoypad[g_nJoypadNum])
			g_pDIDevJoypad[g_nJoypadNum]->Release();
		g_pDIDevJoypad[g_nJoypadNum] = NULL;
		return DIENUM_CONTINUE;		// �񋓂𑱂���
	}

	// �K�萔�ɒB������I��
	g_nJoypadNum++;
	if(g_nJoypadNum == MAX_CONTROLER)
		return DIENUM_STOP;			// �񋓂��I������
	else
		return DIENUM_CONTINUE;		// �񋓂𑱂���
}

//=============================================================================
// �W���C�p�b�h�̏I������
//=============================================================================
void UninitJoypad(void)
{
	for(int nLoop = 0; nLoop < MAX_CONTROLER; nLoop++)
		SAFE_RELEASE(g_pDIDevJoypad[nLoop]);
}

//=============================================================================
// �W���C�p�b�h�̍X�V����
//=============================================================================
void UpdateJoypad(void)
{
	int nLoop;
	
	for(nLoop = 0; nLoop < MAX_CONTROLER; nLoop++)
	{
		// ���O�W���C�p�b�h���̃o�b�N�A�b�v
		g_joyStatePrev[nLoop] = g_joyState[nLoop];

		if(g_pDIDevJoypad[nLoop])
		{
			// �f�o�C�X����f�[�^���擾
			if(FAILED(g_pDIDevJoypad[nLoop]->GetDeviceState(sizeof(DIJOYSTATE), &g_joyState[nLoop])))
				g_pDIDevJoypad[nLoop]->Acquire();
		}

		// �g���K�[���v�Z
		for( int i = 0; i < 32; i++ )
		{
			if( g_joyState[nLoop].rgbButtons[i] & 0x80 && 
				!(g_joyStatePrev[nLoop].rgbButtons[i] & 0x80) )
			{
				g_joyStateTrigger[nLoop][i] = 0x80;
			} else {
				g_joyStateTrigger[nLoop][i] = 0x00;
			}
		}
	}
}
