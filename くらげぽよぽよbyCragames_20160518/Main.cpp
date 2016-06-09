/*******************************************************************************
* �^�C�g��:		���C������
* �v���O������:	Main.cpp
* �쐬��:		GP11A331 4�� �Ɍ��C�H
* �쐬��:		2016/01/18
********************************************************************************
* �X�V����:		- 2016/01/18	�Ɍ��C�H
*					- V1.00		Initial Version
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "Main.h"
#include "Title.h"
#include "Game.h"
#include "Result.h"
#include "XFile.h"
#include "Texture.h"
#include "Input.h"
#include "Camera.h"
#include "Light.h"
#include "DebugProc.h"
#include "Player.h"
#include "Object.h"
#include "Shadow.h"
#include "UI.h"
#include "Fade.h"
#include "Effect.h"
#include "Sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CLASS_NAME		"AppClass"				// �E�C���h�E�̃N���X��
#define WINDOW_NAME		"���炰�ۂ�ۂ�"		// �E�C���h�E�̃L���v�V������

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
#ifdef _DEBUG
void UpdateFPS(void);
#endif

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
LPDIRECT3D9			g_pD3D = NULL;			// Direct3D�I�u�W�F�N�g
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	// �f�o�C�X�I�u�W�F�N�g(�`��ɕK�v)

HWND		g_hWnd;							// �e�E�B���h�E�n���h��
HINSTANCE	g_hInstance;					// �C���X�^���X�n���h��
MODE		g_Mode = MODE_TITLE;

SCREEN g_Screen = {SCREEN_WIDTH,SCREEN_HEIGHT};

#ifdef _DEBUG
int			g_nCountFPS;					// FPS�J�E���^
#endif

/*******************************************************************************
�֐���:	int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
����:	HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow
�߂�l:	����I��: int�^�� 0
����:	���C���֐�
*******************************************************************************/
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	g_hInstance = hInstance;
	
	UNREFERENCED_PARAMETER(hPrevInstance);	// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j
	UNREFERENCED_PARAMETER(lpCmdLine);		// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j

	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	// �N���X�̍쐬
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};

	//HWND hWnd;
	MSG msg;
	
	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �E�B���h�E�̍쐬
	g_hWnd = CreateWindowEx(0,
						CLASS_NAME,				// �o�^����Ă���N���X��
						WINDOW_NAME,
						WS_OVERLAPPEDWINDOW,
						0,//CW_USEDEFAULT,
						0,//CW_USEDEFAULT,
						SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2,
						SCREEN_HEIGHT + GetSystemMetrics(SM_CYDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),
						NULL,
						NULL,
						hInstance,
						NULL);					// WM_CREATE��LPARAM�ɓn�������l�B�n�������f�[�^���Ȃ��Ƃ��́ANULL�B
												// WM_CREATE�́A�E�C���h�E���������ꂽ�Ƃ��ɂP�񂾂����s�����B

	// ����������(�E�B���h�E���쐬���Ă���s��)
	if(FAILED(Init(hInstance, g_hWnd, TRUE)))
	{
		return -1;
	}

	//�t���[���J�E���g������
	timeBeginPeriod(1);				// ����\��ݒ�
	dwExecLastTime = 
	dwFPSLastTime = timeGetTime();
	dwCurrentTime =
	dwFrameCount = 0;

	// �E�C���h�E�̕\��(�����������̌�ɌĂ΂Ȃ��Ƒʖ�)
	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	// ���b�Z�[�W���[�v
	while(1)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��Ƒ��o
				TranslateMessage(&msg); // ������Ă���L�[�{�[�h�̏����A�A�v���P�[�V�������擾�ł���`�ɕϊ�
				DispatchMessage(&msg);	// �擾�������b�Z�[�W���A�E�C���h�E�v���V�[�W���ɑ���
			}
        }
		else
		{
			dwCurrentTime = timeGetTime();
			if((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5�b���ƂɎ��s
			{
#ifdef _DEBUG
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
#endif
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				// �X�V����
				Update();

				// �`�揈��
				Draw();

				dwFrameCount++;
			}
		}
	}
	
	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// �I������
	Uninit();

	timeEndPeriod(1);				// ����\��߂�

	return (int)msg.wParam;
}

/*******************************************************************************
�֐���:	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
����:	HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam
�߂�l:	����I��: int�^�� 0
����:	���C���֐�
*******************************************************************************/
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		default:
			break;
		}
		break;
		return 0;
	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

/*******************************************************************************
�֐���:	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
����:	hInstance : �C���X�^���X�̃n���h��
		hWnd      : �E�C���h�E�̃n���h��
		bWindow   : �E�C���h�E���[�h�ɂ��邩�ǂ���
�߂�l:	HRESULT�^	S_OK:����I��
					E_FAIL:���������s
����:	DirectX �������֐�
*******************************************************************************/
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
    D3DDISPLAYMODE d3ddm;

	// Direct3D�I�u�W�F�N�g�̍쐬
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
    if(FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ���[�N���[���N���A
	d3dpp.BackBufferCount			= 1;						// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth			= SCREEN_WIDTH;				// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight			= SCREEN_HEIGHT;			// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat			= d3ddm.Format;				// �o�b�N�o�b�t�@�t�H�[�}�b�g�̓f�B�X�v���C���[�h�ɍ��킹�Ďg��
	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;	// �f���M���ɓ������ăt���b�v����
	d3dpp.Windowed					= bWindow;					// �E�B���h�E���[�h
	d3dpp.EnableAutoDepthStencil	= TRUE;						// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D16;				// �f�v�X�o�b�t�@�Ƃ���16bit���g��

	if(bWindow)
	{// �E�B���h�E���[�h
		d3dpp.FullScreen_RefreshRateInHz = 0;								// ���t���b�V�����[�g
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;	// �C���^�[�o��
	}
	else
	{// �t���X�N���[�����[�h
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// ���t���b�V�����[�g
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT;		// �C���^�[�o��
	}

	// �f�o�C�X�I�u�W�F�N�g�̐���
	// [�f�o�C�X�쐬����]<�`��>��<���_����>���n�[�h�E�F�A�ōs�Ȃ�
	if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
									D3DDEVTYPE_HAL, 
									hWnd, 
									D3DCREATE_HARDWARE_VERTEXPROCESSING, 
									&d3dpp, &g_pD3DDevice)))
	{
		// ��L�̐ݒ肪���s������
		// [�f�o�C�X�쐬����]<�`��>���n�[�h�E�F�A�ōs���A<���_����>��CPU�ōs�Ȃ�
		if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
										D3DDEVTYPE_HAL, 
										hWnd, 
										D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
										&d3dpp, &g_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// [�f�o�C�X�쐬����]<�`��>��<���_����>��CPU�ōs�Ȃ�
			if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
											D3DDEVTYPE_REF,
											hWnd, 
											D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
											&d3dpp, &g_pD3DDevice)))
			{
				// ���������s
				return E_FAIL;
			}
		}
	}

	// �����_�[�X�e�[�g�p�����[�^�̐ݒ�
    g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ���ʂ��J�����O
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Z�o�b�t�@���g�p
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h���s��
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��

	// �T���v���[�X�e�[�g�p�����[�^�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k���t�B���^���[�h��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g��t�B���^���[�h��ݒ�

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �A���t�@�u�����f�B���O������ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �ŏ��̃A���t�@����
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// �Q�Ԗڂ̃A���t�@����
	
	// �E�B���h�E�T�C�Y�̏�����
	InitWindowSize();
	// ���y�̏�����
	//InitSound(hWnd);
	// ���͂̏�����
	InitKeyboard(hInstance, hWnd);
	InitMouse(hInstance, hWnd);
	// �f�o�b�O�v���b�N�̏�����
	InitDebugProc();
	// �t�F�[�h�̏�����
	InitFade();
	// �t�@�C���̓ǂݍ���
	InitXFile();
	InitTexture();
	// ���[�h�̃Z�b�g
	SetMode(MODE_GAME); // MODE_RESULT // MODE_TITLE // MODE_GAME

	return S_OK;
}

/*******************************************************************************
�֐���:	void Uninit(void)
����:	�Ȃ�
�߂�l:	�Ȃ�
����:	�I������
*******************************************************************************/
void Uninit(void)
{
	if(g_pD3DDevice != NULL)
	{// �f�o�C�X�I�u�W�F�N�g�̊J��
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if(g_pD3D != NULL)
	{// Direct3D�I�u�W�F�N�g�̊J��
		g_pD3D->Release();
		g_pD3D = NULL;
	}
	// �t�@�C���̏I������
	UninitXFile();
	UninitTexture();
	// ���͂̏I������
	UninitKeyboard();
	UninitMouse();
	// �f�o�b�O�v���b�N�̏I������
	UninitDebugProc();
	// �t�F�[�h�̏I������
	UninitFade();
	// �^�C�g���̏I������
	UninitTitle();
	// �Q�[���̏I������
	UninitGame();
	// ���U���g�̏I������
	UninitResult();
	// �T�E���h�̏I������
	//UninitSound();
}
/*******************************************************************************
�֐���:	void Update(void)
����:	�Ȃ�
�߂�l:	�Ȃ�
����:	�X�V����
*******************************************************************************/
void Update(void)
{
	// FPS�X�V
#ifdef _DEBUG
	UpdateFPS();
#endif
	// �E�B���h�E�T�C�Y�X�V
	UpdateWindowSize();
	// ���͂̍X�V����
	UpdateKeyboard();
	UpdateMouse();
	// �f�o�b�O�v���b�N�̍X�V����
	UpdateDebugProc();
	// �t�F�[�h�̍X�V����
	UpdateFade();
	switch(g_Mode)
	{
	case MODE_TITLE:
		// �^�C�g���̍X�V����
		UpdateTitle();
		break;
	case MODE_GAME:
		// �Q�[���̍X�V����
		UpdateGame();
		break;
	case MODE_RESULT:
		// ���U���g�̍X�V����
		UpdateResult();
		break;
	default:
		break;
	}
}
/*******************************************************************************
�֐���:	void Draw(void)
����:	�Ȃ�
�߂�l:	�Ȃ�
����:	�`�揈��
*******************************************************************************/
void Draw(void)
{
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// �`��̊J�n
	if(SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		switch(g_Mode)
		{
		case MODE_TITLE:
			// �^�C�g���̕`�揈��
			DrawTitle();
			break;
		case MODE_GAME:
			// �Q�[���̕`�揈��
			DrawGame();
			break;
		case MODE_RESULT:
			// ���U���g�̕`�揈��
			DrawResult();
			break;
		default:
			break;
		}

		// �t�F�[�h�̕`��
		DrawFade();

#ifdef _DEBUG
		// �f�o�b�O�p�X�e�[�^�X��\��
		DrawDebugProc();
#endif
		// �`��̏I��
		g_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
/*******************************************************************************
�֐���:	LPDIRECT3DDEVICE9 GetDevice(void)
����:	�Ȃ�
�߂�l:	LPDIRECT3DDEVICE9�^	g_pD3DDevice
����:	�f�o�C�X�̎擾
*******************************************************************************/
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}
/*******************************************************************************
�֐���:	HWND GetHandleWindow(void)
����:	�Ȃ�
�߂�l:	HWND�^	g_hWnd
����:	�E�B���h�E�̃n���h���̎擾
*******************************************************************************/
HWND GetHandleWindow(void)
{
	return g_hWnd;
}
/*******************************************************************************
�֐���:	HINSTANCE GetHandleInstance(void)
����:	�Ȃ�
�߂�l:	HINSTANCE�^	g_hInstance
����:	�A�v���̃C���X�^���X�̎擾
*******************************************************************************/
HINSTANCE GetHandleInstance(void)
{
	return g_hInstance;
}
#ifdef _DEBUG
/*******************************************************************************
�֐���:	void DrawFPS(void)
����:	�Ȃ�
�߂�l:	�Ȃ�
����:	FPS�\������
*******************************************************************************/
void UpdateFPS(void)
{
	PrintDebugProc("FPS:%d\n", g_nCountFPS);
}
#endif
/*******************************************************************************
�֐���:	void InitWindowSize(void)
����:	�Ȃ�
�߂�l:	�Ȃ�
����:	�E�B���h�E�T�C�Y�̏�����
*******************************************************************************/
void InitWindowSize(void)
{
	RECT RectClient,RectWindow;

	GetClientRect(g_hWnd,&RectClient);
	GetWindowRect(g_hWnd,&RectWindow);

	int nNewWidth = (RectWindow.right - RectWindow.left) - (RectClient.right - RectClient.left) + g_Screen.nWidth;
	int nNewHeight = (RectWindow.bottom - RectWindow.top) - (RectClient.bottom - RectClient.top) + g_Screen.nHeight;

	SetWindowPos(g_hWnd, NULL, 0, 0, nNewWidth, nNewHeight, SWP_NOMOVE | SWP_NOZORDER);
}
/*******************************************************************************
�֐���:	void UpdateWindowSize(void)
����:	�Ȃ�
�߂�l:	�Ȃ�
����:	�E�B���h�E�T�C�Y�̍X�V
*******************************************************************************/
void UpdateWindowSize(void)
{
	RECT RectClient,RectWindow;

	GetClientRect(g_hWnd,&RectClient);
	GetWindowRect(g_hWnd,&RectWindow);

	PrintDebugProc("�E�B���h�E�T�C�Y�ƃN���C�A���g�T�C�Y�̕��̍���%d\n",(RectWindow.right - RectWindow.left) - (RectClient.right - RectClient.left));
	PrintDebugProc("�E�B���h�E�T�C�Y�ƃN���C�A���g�T�C�Y�̍����̍���%d\n",(RectWindow.bottom - RectWindow.top) - (RectClient.bottom - RectClient.top));
	PrintDebugProc("GetSystemMetrics(SM_CXDLGFRAME) * 2�̒l��%d\n",GetSystemMetrics(SM_CXDLGFRAME) * 2);
	PrintDebugProc("GetSystemMetrics(SM_CYDLGFRAME) * 2�̒l��%d\n",GetSystemMetrics(SM_CYDLGFRAME) * 2);
	PrintDebugProc("GetSystemMetrics(SM_CYCAPTION)�̒l��%d\n",GetSystemMetrics(SM_CYCAPTION));
	PrintDebugProc("[���݂̃N���C�A���g�̈�]\n");
	PrintDebugProc("����%d,������%d\n",(RectClient.right - RectClient.left),(RectClient.bottom - RectClient.top));
	PrintDebugProc("[���݂̃E�B���h�E�̈�]\n");
	PrintDebugProc("����%d,������%d\n",(RectWindow.right - RectWindow.left),(RectWindow.bottom - RectWindow.top));

	SetWindowPos(g_hWnd, NULL, 0, 0, RectWindow.right - RectWindow.left, RectWindow.bottom - RectWindow.top, SWP_NOMOVE | SWP_NOZORDER);

	g_Screen.nWidth = (float)RectClient.right - (float)RectClient.left;
	g_Screen.nHeight = (float)RectClient.bottom - (float)RectClient.top;
}
/*******************************************************************************
�֐���:	SCREEN GetScreenInfo(void)
����:	�Ȃ�
�߂�l:	�Ȃ�
����:	�X�N���[�����̎󂯓n��
*******************************************************************************/
SCREEN GetScreenInfo(void)
{
	return g_Screen;
}
/*******************************************************************************
�֐���:	MODE GetMainMode(void)
����:	�Ȃ�
�߂�l:	�Ȃ�
����:	���C�����[�h�̎擾
*******************************************************************************/
MODE GetMainMode(void)
{
	return g_Mode;
}
/*******************************************************************************
�֐���:	void SetMode(MODE mode)
����:	�Ȃ�
�߂�l:	�Ȃ�
����:	���[�h���Z�b�g
*******************************************************************************/
void SetMode(MODE Mode)
{
	g_Mode = Mode;

	switch(g_Mode)
	{
	case MODE_TITLE:
		InitTitle();
		break;
	case MODE_GAME:
		InitGame();
		break;
	case MODE_RESULT:
		InitResult();
		break;
	default:
		break;
	}
}
/*******************************************************************************
�֐���:	void EndMode(void)
����:	�Ȃ�
�߂�l:	�Ȃ�
����:	���[�h�̏I��
*******************************************************************************/
void EndMode(void)
{
	switch(g_Mode)
	{
	case MODE_TITLE:
		UninitTitle();
		break;
	case MODE_GAME:
		UninitGame();
		break;
	case MODE_RESULT:
		UninitResult();
		break;
	default:
		break;
	}
}
