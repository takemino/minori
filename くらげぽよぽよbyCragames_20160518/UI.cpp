/*******************************************************************************
* �^�C�g��:		UI����
* �v���O������:	UI.cpp
* �쐬��:		GP11A331 4�� �Ɍ��C�H
* �쐬��:		2016/02/01
********************************************************************************
* �X�V����:		- 2016/02/25	�Ɍ��C�H
*					- V1.00		Initial Version
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "UI.h"
#include "DebugProc.h"
#include "Texture.h"
#include "Input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
UI_2D g_Option[MAX_OPTION];

RECT g_RectClient,g_RectWindow;

bool g_bOptionWindow;																		// �I�v�V�����E�B���h�E��\�������ǂ���(true���\����)
bool g_bIndicateMenuBar;																	// ���j���[�o�[��\�����邩�ǂ���(true���\������)

/*******************************************************************************
* �v���g�^�C�v�錾
*******************************************************************************/
void InitOption(void);
void UninitOption(void);
void UpdateOption(void);
void DrawOption(void);
HRESULT MakeVertexUI2D(LPDIRECT3DDEVICE9 pDevice, UI_2D *pUI, int nMaxNum);
void SetVertexUI2D(UI_2D *pUI, int nMaxNum);
HRESULT MakeVertexUI3D(LPDIRECT3DDEVICE9 pDevice, UI_3D *pUI, int nMaxNum);
void RecalculationOption(void);





/*******************************************************************************
�֐���	void InitUI(void)
�쐬��	�|�{
����	UI�̏���������
*******************************************************************************/
void InitUI(void)
{
	// �I�v�V�����̏���������
	InitOption();
}

/*******************************************************************************
�֐���	void UninitUI(void)
�쐬��	�|�{
����	UI�̏I������
*******************************************************************************/
void UninitUI(void)
{
}

/*******************************************************************************
�֐���	void UpdataUI(void)
�쐬��	�|�{
����	UI�̍X�V����
*******************************************************************************/
void UpdateUI(void)
{
	// �I�v�V�����̍X�V����
	UpdateOption();
}

/*******************************************************************************
�֐���	void DrawUI(void)
�쐬��	�|�{
����	UI�̕`�揈��
*******************************************************************************/
void DrawUI(void)
{
	// �I�v�V�����̕`�揈��
	DrawOption();
}

/*******************************************************************************
�֐���	void InitOption(void);
�쐬��	�|�{
����	�I�v�V�����̏���������
*******************************************************************************/
void InitOption(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	HWND hWnd = GetHandleWindow();
	SCREEN Screen = GetScreenInfo();

	// �I�v�V�����E�B���h�E�̏�����
#if 1
	g_Option[OPTION_WINDOW].vScl = D3DXVECTOR3(Screen.nWidth / 16 * 6,Screen.nHeight / 9 * 6,0.0f);
	g_Option[OPTION_WINDOW].vPos = D3DXVECTOR3(Screen.nWidth / 2,Screen.nHeight / 2,0.0f);
#else
	g_Option[OPTION_WINDOW].vScl = D3DXVECTOR3(SCREEN_WIDTH / 16 * 6,SCREEN_HEIGHT / 9 * 6,0.0f);
	g_Option[OPTION_WINDOW].vPos = D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f);
#endif
	// BGM�~�L�T�[�o�[�̏�����
	g_Option[BGM_MIXERBAR].vScl = D3DXVECTOR3(g_Option[OPTION_WINDOW].vScl.x,g_Option[OPTION_WINDOW].vPos.y / 3,0.0f);
	g_Option[BGM_MIXERBAR].vPos = D3DXVECTOR3(g_Option[OPTION_WINDOW].vPos.x,g_Option[OPTION_WINDOW].vPos.y - (g_Option[OPTION_WINDOW].vScl.y / 4),0.0f);
	// SE�~�L�T�[�o�[�̏�����
	g_Option[SE_MIXERBAR].vScl = D3DXVECTOR3(g_Option[BGM_MIXERBAR].vScl.x,g_Option[BGM_MIXERBAR].vScl.y,0.0f);
	g_Option[SE_MIXERBAR].vPos = D3DXVECTOR3(g_Option[OPTION_WINDOW].vPos.x,g_Option[OPTION_WINDOW].vPos.y + (g_Option[OPTION_WINDOW].vScl.y / 10),0.0f);
	// �u���j���[�o�[��\������v�̕����̏�����
	g_Option[MENUBAR_INDICATE].vScl = D3DXVECTOR3(g_Option[OPTION_WINDOW].vScl.x / 3 * 2,g_Option[OPTION_WINDOW].vScl.y / 4,0.0f);
	g_Option[MENUBAR_INDICATE].vPos = D3DXVECTOR3(g_Option[OPTION_WINDOW].vPos.x - (g_Option[OPTION_WINDOW].vScl.x / 7),g_Option[OPTION_WINDOW].vPos.y + (g_Option[OPTION_WINDOW].vScl.y / 3),0.0f);
	// �`�F�b�N�{�b�N�X�̏�����
	g_Option[CHECKBOX].vScl = D3DXVECTOR3(g_Option[OPTION_WINDOW].vScl.x / 10,g_Option[OPTION_WINDOW].vScl.y / 10,0.0f);
	g_Option[CHECKBOX].vPos = D3DXVECTOR3(g_Option[OPTION_WINDOW].vPos.x + (g_Option[OPTION_WINDOW].vScl.x / 3),g_Option[OPTION_WINDOW].vPos.y + (g_Option[OPTION_WINDOW].vScl.y / 6 * 2),0.0f);
	// ����{�^���̏�����
	g_Option[OPTION_WINDOW_CLOSEBUTTON].vScl = D3DXVECTOR3(g_Option[OPTION_WINDOW].vScl.x / 10,g_Option[OPTION_WINDOW].vScl.y / 10,0.0f);
	g_Option[OPTION_WINDOW_CLOSEBUTTON].vPos = D3DXVECTOR3((g_Option[OPTION_WINDOW].vPos.x + (g_Option[OPTION_WINDOW].vScl.x / 2)) - (g_Option[OPTION_WINDOW_CLOSEBUTTON].vScl.x / 2),
															(g_Option[OPTION_WINDOW].vPos.y - (g_Option[OPTION_WINDOW].vScl.y / 2)) + (g_Option[OPTION_WINDOW_CLOSEBUTTON].vScl.y / 2)
															,0.0f);
	// BGM�~�L�T�[�o�[�̃A�C�R���̏�����
	g_Option[BGM_MIXERBAR_ICON].vScl = D3DXVECTOR3(g_Option[OPTION_WINDOW].vScl.x / 10,g_Option[OPTION_WINDOW].vScl.y / 10,0.0f);
	g_Option[BGM_MIXERBAR_ICON].vPos = D3DXVECTOR3(g_Option[OPTION_WINDOW].vPos.x,g_Option[OPTION_WINDOW].vPos.y - (g_Option[OPTION_WINDOW].vScl.y / 4),0.0f);
	// SE�~�L�T�[�o�[�̃A�C�R���̏�����
	g_Option[SE_MIXERBAR_ICON].vScl = D3DXVECTOR3(g_Option[OPTION_WINDOW].vScl.x / 10,g_Option[OPTION_WINDOW].vScl.y / 10,0.0f);
	g_Option[SE_MIXERBAR_ICON].vPos = D3DXVECTOR3(g_Option[OPTION_WINDOW].vPos.x,g_Option[OPTION_WINDOW].vPos.y + (g_Option[OPTION_WINDOW].vScl.y / 10),0.0f);


	for(int nCnt = 0;nCnt < MAX_OPTION;nCnt ++)
	{
		g_Option[nCnt].vTexPatSize = D3DXVECTOR2(1.0f,1.0f);
	}
	// �I�v�V�����E�B���h�E�̒��_���W�̐ݒ�
	MakeVertexUI2D(pDevice,&g_Option[0],MAX_OPTION);

	g_Option[BGM_MIXERBAR_ICON].bChoice = false;
	g_bOptionWindow = true;
	g_bIndicateMenuBar = true;

}

/*******************************************************************************
�֐���	void UpdateOption(void)
�쐬��	�|�{
����	�I�v�V�����̍X�V����
*******************************************************************************/
void UpdateOption(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	POINT MouseClientPos = GetMouseClientPos();

	RecalculationOption();

	if(g_bOptionWindow == true)
	{
		if(MouseClientPos.x > g_Option[CHECKBOX].vPos.x - (g_Option[CHECKBOX].vScl.x / 2) &&
		   MouseClientPos.x < g_Option[CHECKBOX].vPos.x + (g_Option[CHECKBOX].vScl.x / 2) &&
		   MouseClientPos.y > g_Option[CHECKBOX].vPos.y - (g_Option[CHECKBOX].vScl.y / 2) &&
		   MouseClientPos.y < g_Option[CHECKBOX].vPos.y + (g_Option[CHECKBOX].vScl.y / 2))
		{// ���j���[�o�[�̕\���̐ݒ�
			PrintDebugProc("�����Ă��\n");
			if(g_bIndicateMenuBar == true)
			{
				if(GetMouseLeftTrigger())
				{// �u���j���[�o�[��\������v�̃`�F�b�N���O��
					g_bIndicateMenuBar = false;
				}
			}
			else
			{
				if(GetMouseLeftTrigger())
				{// �u���j���[�o�[��\������v�Ƀ`�F�b�N������
					g_bIndicateMenuBar = true;
				}
			}
		}
		if(MouseClientPos.x > g_Option[BGM_MIXERBAR_ICON].vPos.x - (g_Option[BGM_MIXERBAR_ICON].vScl.x / 2) &&
		   MouseClientPos.x < g_Option[BGM_MIXERBAR_ICON].vPos.x + (g_Option[BGM_MIXERBAR_ICON].vScl.x / 2) &&
		   MouseClientPos.y > g_Option[BGM_MIXERBAR_ICON].vPos.y - (g_Option[BGM_MIXERBAR_ICON].vScl.y / 2) &&
		   MouseClientPos.y < g_Option[BGM_MIXERBAR_ICON].vPos.y + (g_Option[BGM_MIXERBAR_ICON].vScl.y / 2))
		{// BGM�̉��ʒ���
			PrintDebugProc("�����Ă��\n");
			if(GetMouseLeftTrigger())
			{
				g_Option[BGM_MIXERBAR_ICON].bChoice = true;
			}
		}
		if(g_Option[BGM_MIXERBAR_ICON].bChoice == true)
		{
			g_Option[BGM_MIXERBAR_ICON].vPos.x = MouseClientPos.x;
			if((MouseClientPos.x <= g_Option[BGM_MIXERBAR].vPos.x - (g_Option[BGM_MIXERBAR].vScl.x / 7)))
			{
				g_Option[BGM_MIXERBAR_ICON].vPos.x = g_Option[BGM_MIXERBAR].vPos.x - (g_Option[BGM_MIXERBAR].vScl.x / 7);
			}
			if(MouseClientPos.x >= g_Option[BGM_MIXERBAR].vPos.x + (g_Option[BGM_MIXERBAR].vScl.x / 7 * 3))
			{
				g_Option[BGM_MIXERBAR_ICON].vPos.x = g_Option[BGM_MIXERBAR].vPos.x + (g_Option[BGM_MIXERBAR].vScl.x / 7 * 3);
			}
			SetVertexUI2D(&g_Option[BGM_MIXERBAR_ICON] ,1);
			if(GetMouseLeftRelease())
			{
				g_Option[BGM_MIXERBAR_ICON].bChoice = false;
			}
		}
		if(MouseClientPos.x > g_Option[SE_MIXERBAR_ICON].vPos.x - (g_Option[SE_MIXERBAR_ICON].vScl.x / 2) &&
		   MouseClientPos.x < g_Option[SE_MIXERBAR_ICON].vPos.x + (g_Option[SE_MIXERBAR_ICON].vScl.x / 2) &&
		   MouseClientPos.y > g_Option[SE_MIXERBAR_ICON].vPos.y - (g_Option[SE_MIXERBAR_ICON].vScl.y / 2) &&
		   MouseClientPos.y < g_Option[SE_MIXERBAR_ICON].vPos.y + (g_Option[SE_MIXERBAR_ICON].vScl.y / 2))
		{// SE�̉��ʒ���
			PrintDebugProc("�����Ă��\n");
			if(GetMouseLeftPress())
			{
				g_Option[SE_MIXERBAR_ICON].bChoice = true;
			}
		}
		if(g_Option[SE_MIXERBAR_ICON].bChoice == true)
		{
			g_Option[SE_MIXERBAR_ICON].vPos.x = MouseClientPos.x;
			if((MouseClientPos.x <= g_Option[SE_MIXERBAR].vPos.x - (g_Option[SE_MIXERBAR].vScl.x / 7)))
			{
				g_Option[SE_MIXERBAR_ICON].vPos.x = g_Option[SE_MIXERBAR].vPos.x - (g_Option[SE_MIXERBAR].vScl.x / 7);
			}
			if(MouseClientPos.x >= g_Option[BGM_MIXERBAR].vPos.x + (g_Option[BGM_MIXERBAR].vScl.x / 7 * 3))
			{
				g_Option[SE_MIXERBAR_ICON].vPos.x = g_Option[SE_MIXERBAR].vPos.x + (g_Option[SE_MIXERBAR].vScl.x / 7 * 3);
			}
			SetVertexUI2D(&g_Option[SE_MIXERBAR_ICON] ,1);
			if(GetMouseLeftRelease())
			{
				g_Option[SE_MIXERBAR_ICON].bChoice = false;
			}
		}
//		if(MouseClientPos.x > g_Option[BGM_MIXERBAR_ICON].vPos.x - (g_Option[BGM_MIXERBAR_ICON].vScl.x / 2) &&
//		   MouseClientPos.x < g_Option[BGM_MIXERBAR_ICON].vPos.x + (g_Option[BGM_MIXERBAR_ICON].vScl.x / 2) &&
//		   MouseClientPos.y > g_Option[BGM_MIXERBAR_ICON].vPos.y - (g_Option[BGM_MIXERBAR_ICON].vScl.y / 2) &&
//		   MouseClientPos.y < g_Option[BGM_MIXERBAR_ICON].vPos.y + (g_Option[BGM_MIXERBAR_ICON].vScl.y / 2))
//		{// BGM�̉��ʒ���
//			PrintDebugProc("�����Ă��\n");
//			if(GetMouseLeftTrigger())
//			{
//				g_Option[BGM_MIXERBAR_ICON].bChoice = true;
//			}
//		}
//		if(g_Option[BGM_MIXERBAR_ICON].bChoice == true)
//		{
//			g_Option[BGM_MIXERBAR_ICON].vPos.x = MouseClientPos.x;
//			if((MouseClientPos.x <= g_Option[BGM_MIXERBAR].vPos.x - (g_Option[BGM_MIXERBAR].vScl.x / 7)))
//			{
//				g_Option[BGM_MIXERBAR_ICON].vPos.x = g_Option[BGM_MIXERBAR].vPos.x - (g_Option[BGM_MIXERBAR].vScl.x / 7);
//			}
//			if(MouseClientPos.x >= g_Option[BGM_MIXERBAR].vPos.x + (g_Option[BGM_MIXERBAR].vScl.x / 7 * 3))
//			{
//				g_Option[BGM_MIXERBAR_ICON].vPos.x = g_Option[BGM_MIXERBAR].vPos.x + (g_Option[BGM_MIXERBAR].vScl.x / 7 * 3);
//			}
//			SetVertexUI2D(&g_Option[BGM_MIXERBAR_ICON] ,1);
//			if(GetMouseLeftRelease())
//			{
//				g_Option[BGM_MIXERBAR_ICON].bChoice = false;
//			}
//		}
//		if(MouseClientPos.x > g_Option[SE_MIXERBAR_ICON].vPos.x - (g_Option[SE_MIXERBAR_ICON].vScl.x / 2) &&
//		   MouseClientPos.x < g_Option[SE_MIXERBAR_ICON].vPos.x + (g_Option[SE_MIXERBAR_ICON].vScl.x / 2) &&
//		   MouseClientPos.y > g_Option[SE_MIXERBAR_ICON].vPos.y - (g_Option[SE_MIXERBAR_ICON].vScl.y / 2) &&
//		   MouseClientPos.y < g_Option[SE_MIXERBAR_ICON].vPos.y + (g_Option[SE_MIXERBAR_ICON].vScl.y / 2))
//		{// SE�̉��ʒ���
//			PrintDebugProc("�����Ă��\n");
//			if(GetMouseLeftPress())
//			{
//				g_Option[SE_MIXERBAR_ICON].bChoice = true;
//			}
//		}
//		if(g_Option[SE_MIXERBAR_ICON].bChoice == true)
//		{
//			g_Option[SE_MIXERBAR_ICON].vPos.x = MouseClientPos.x;
//			if((MouseClientPos.x <= g_Option[SE_MIXERBAR].vPos.x - (g_Option[SE_MIXERBAR].vScl.x / 7)))
//			{
//				g_Option[SE_MIXERBAR_ICON].vPos.x = g_Option[SE_MIXERBAR].vPos.x - (g_Option[SE_MIXERBAR].vScl.x / 7);
//			}
//			if(MouseClientPos.x >= g_Option[BGM_MIXERBAR].vPos.x + (g_Option[BGM_MIXERBAR].vScl.x / 7 * 3))
//			{
//				g_Option[SE_MIXERBAR_ICON].vPos.x = g_Option[SE_MIXERBAR].vPos.x + (g_Option[SE_MIXERBAR].vScl.x / 7 * 3);
//			}
//			MakeVertexUI2D(pDevice, &g_Option[SE_MIXERBAR_ICON] ,1);
//			if(GetMouseLeftRelease())
//			{
//				g_Option[SE_MIXERBAR_ICON].bChoice = false;
//			}
//		}
		if(MouseClientPos.x > g_Option[OPTION_WINDOW_CLOSEBUTTON].vPos.x - (g_Option[OPTION_WINDOW_CLOSEBUTTON].vScl.x / 2) &&
		   MouseClientPos.x < g_Option[OPTION_WINDOW_CLOSEBUTTON].vPos.x + (g_Option[OPTION_WINDOW_CLOSEBUTTON].vScl.x / 2) &&
		   MouseClientPos.y > g_Option[OPTION_WINDOW_CLOSEBUTTON].vPos.y - (g_Option[OPTION_WINDOW_CLOSEBUTTON].vScl.y / 2) &&
		   MouseClientPos.y < g_Option[OPTION_WINDOW_CLOSEBUTTON].vPos.y + (g_Option[OPTION_WINDOW_CLOSEBUTTON].vScl.y / 2))
		{// ����{�^��
			PrintDebugProc("�����Ă��\n");
			if(GetMouseLeftTrigger())
			{// �I�v�V�����̃E�B���h�E������
				g_bOptionWindow = false;
			}
		}
	}
	else
	{
		if(GetMouseLeftTrigger())
		{// �I�v�V�����̃E�B���h�E��\������
			g_bOptionWindow = true;
		}
	}
}

/*******************************************************************************
* �I�v�V�����̕`�揈��
*******************************************************************************/
void DrawOption(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LPDIRECT3DTEXTURE9 *pUITexture = GetUITexture();

	for(int nCnt = 0;nCnt < MAX_UI_TEXTURE;nCnt ++)
	{
		if(g_bOptionWindow == true)
		{
			switch(nCnt)
			{
			case OPTION_WINDOW:	// �I�v�V�����E�B���h�E��`��
				// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
				pDevice -> SetStreamSource(0,g_Option[OPTION_WINDOW].pD3DVtxBuff,0,sizeof(VERTEX_2D));

				// ���_�t�H�[�}�b�g�̐ݒ�
				pDevice -> SetFVF(FVF_VERTEX_2D);

				// �e�N�X�`���̐ݒ�
				pDevice -> SetTexture(0,pUITexture[UI_TEXTURE_OPTION_WINDOW]);

				// �|���S���̕`��
				pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,
										 0,
										 NUM_POLYGON);
				break;
			case BGM_MIXERBAR:	// BGM�~�L�T�[�o�[��`��
				// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
				pDevice -> SetStreamSource(0,g_Option[BGM_MIXERBAR].pD3DVtxBuff,0,sizeof(VERTEX_2D));

				// ���_�t�H�[�}�b�g�̐ݒ�
				pDevice -> SetFVF(FVF_VERTEX_2D);

				// �e�N�X�`���̐ݒ�
				pDevice -> SetTexture(0,pUITexture[UI_TEXTURE_BGM_MIXERBAR]);

				// �|���S���̕`��
				pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,
										 0,
										 NUM_POLYGON);
				break;
			case SE_MIXERBAR:	// SE�~�L�T�[�o�[��`��
				// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
				pDevice -> SetStreamSource(0,g_Option[SE_MIXERBAR].pD3DVtxBuff,0,sizeof(VERTEX_2D));

				// ���_�t�H�[�}�b�g�̐ݒ�
				pDevice -> SetFVF(FVF_VERTEX_2D);

				// �e�N�X�`���̐ݒ�
				pDevice -> SetTexture(0,pUITexture[UI_TEXTURE_SE_MIXERBAR]);

				// �|���S���̕`��
				pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,
										 0,
										 NUM_POLYGON);
				break;
			case MENUBAR_INDICATE:	// �u���j���[�o�[��\���v�̕�����`��
				// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
				pDevice -> SetStreamSource(0,g_Option[MENUBAR_INDICATE].pD3DVtxBuff,0,sizeof(VERTEX_2D));

				// ���_�t�H�[�}�b�g�̐ݒ�
				pDevice -> SetFVF(FVF_VERTEX_2D);

				// �e�N�X�`���̐ݒ�
				pDevice -> SetTexture(0,pUITexture[UI_TEXTURE_MENUBER_INDICATE]);

				// �|���S���̕`��
				pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,
										 0,
										 NUM_POLYGON);
				break;
			case CHECKBOX:
				if(g_bIndicateMenuBar == true)
				{	// �`�F�b�N�����Ă�`�F�b�N�{�b�N�X��`��
					// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
					pDevice -> SetStreamSource(0,g_Option[CHECKBOX].pD3DVtxBuff,0,sizeof(VERTEX_2D));

					// ���_�t�H�[�}�b�g�̐ݒ�
					pDevice -> SetFVF(FVF_VERTEX_2D);

					// �e�N�X�`���̐ݒ�
					pDevice -> SetTexture(0,pUITexture[UI_TEXTURE_CHECKBOX_CHECKIN]);

					// �|���S���̕`��
					pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,
											 0,
											 NUM_POLYGON);
					break;
				}
				else
				{	// �`�F�b�N�����ĂȂ��`�F�b�N�{�b�N�X��`��
					// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
					pDevice -> SetStreamSource(0,g_Option[CHECKBOX].pD3DVtxBuff,0,sizeof(VERTEX_2D));

					// ���_�t�H�[�}�b�g�̐ݒ�
					pDevice -> SetFVF(FVF_VERTEX_2D);

					// �e�N�X�`���̐ݒ�
					pDevice -> SetTexture(0,pUITexture[UI_TEXTURE_CHECKBOX_CHECKOUT]);

					// �|���S���̕`��
					pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,
											 0,
											 NUM_POLYGON);
					break;
				}
			case OPTION_WINDOW_CLOSEBUTTON:	// �I�v�V�����E�B���h�E�̕���{�^����`��
				// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
				pDevice -> SetStreamSource(0,g_Option[OPTION_WINDOW_CLOSEBUTTON].pD3DVtxBuff,0,sizeof(VERTEX_2D));

				// ���_�t�H�[�}�b�g�̐ݒ�
				pDevice -> SetFVF(FVF_VERTEX_2D);

				// �e�N�X�`���̐ݒ�
				pDevice -> SetTexture(0,pUITexture[UI_TEXTURE_OPTION_WINDOW_CLOSEBUTTON]);

				// �|���S���̕`��
				pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,
										 0,
										 NUM_POLYGON);
				break;
			case BGM_MIXERBAR_ICON:
				// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
				pDevice -> SetStreamSource(0,g_Option[BGM_MIXERBAR_ICON].pD3DVtxBuff,0,sizeof(VERTEX_2D));

				// ���_�t�H�[�}�b�g�̐ݒ�
				pDevice -> SetFVF(FVF_VERTEX_2D);

				// �e�N�X�`���̐ݒ�
				pDevice -> SetTexture(0,pUITexture[UI_TEXTURE_MIXERBAR_ICON]);

				// �|���S���̕`��
				pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,
										 0,
										 NUM_POLYGON);
				break;
			case SE_MIXERBAR_ICON:
				// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
				pDevice -> SetStreamSource(0,g_Option[SE_MIXERBAR_ICON].pD3DVtxBuff,0,sizeof(VERTEX_2D));

				// ���_�t�H�[�}�b�g�̐ݒ�
				pDevice -> SetFVF(FVF_VERTEX_2D);

				// �e�N�X�`���̐ݒ�
				pDevice -> SetTexture(0,pUITexture[UI_TEXTURE_MIXERBAR_ICON]);

				// �|���S���̕`��
				pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,
										 0,
										 NUM_POLYGON);
				break;
			}
		}
	}
}

/*******************************************************************************
* 2D��ʂ�UI�̒��_���쐬
*******************************************************************************/
HRESULT MakeVertexUI2D(LPDIRECT3DDEVICE9 pDevice, UI_2D *pUI, int nMaxNum)
{
	for(int nNumUI = 0 ; nNumUI < nMaxNum ; nNumUI++, pUI++)
	{
		// �I�u�W�F�N�g�̒��_�o�b�t�@���쐬(�����x�����ǈ�����@�N���X�������Ƃ��ɂȂ�Ƃ�����)
		if(FAILED(pDevice -> CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,
												D3DUSAGE_WRITEONLY,
												FVF_VERTEX_2D,
												D3DPOOL_MANAGED,
												&pUI -> pD3DVtxBuff,
												NULL)))
		{
			return E_FAIL;
		}

		{// ���_�o�b�t�@�̒��g�𖄂߂�
			VERTEX_2D *pVtx;
			// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
			pUI -> pD3DVtxBuff -> Lock(0,0,(void**)&pVtx,0);
			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(pUI -> vPos.x - pUI -> vScl.x / 2, pUI -> vPos.y - pUI -> vScl.y / 2, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(pUI -> vPos.x + pUI -> vScl.x / 2, pUI -> vPos.y - pUI -> vScl.y / 2, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(pUI -> vPos.x - pUI -> vScl.x / 2, pUI -> vPos.y + pUI -> vScl.y / 2, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(pUI -> vPos.x + pUI -> vScl.x / 2, pUI -> vPos.y + pUI -> vScl.y / 2, 0.0f);
			// rhw�̐ݒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
			// �e�N�X�`�����W�w��
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(pUI -> vTexPatSize.x, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, pUI -> vTexPatSize.y);
			pVtx[3].tex = D3DXVECTOR2(pUI -> vTexPatSize.x, pUI -> vTexPatSize.y);
		
			// ���_�f�[�^���A�����b�N����
			pUI -> pD3DVtxBuff -> Unlock();
		}
	}
	return S_OK;
}

/*******************************************************************************
* 2D��ʂ�UI�̒��_���ύX
*******************************************************************************/
void SetVertexUI2D(UI_2D *pUI, int nMaxNum)
{
	for(int nNumUI = 0 ; nNumUI < nMaxNum ; nNumUI++, pUI++)
	{
		{// ���_�o�b�t�@�̒��g�𖄂߂�
			VERTEX_2D *pVtx;
			// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
			pUI -> pD3DVtxBuff -> Lock(0,0,(void**)&pVtx,0);
			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(pUI -> vPos.x - pUI -> vScl.x / 2, pUI -> vPos.y - pUI -> vScl.y / 2, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(pUI -> vPos.x + pUI -> vScl.x / 2, pUI -> vPos.y - pUI -> vScl.y / 2, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(pUI -> vPos.x - pUI -> vScl.x / 2, pUI -> vPos.y + pUI -> vScl.y / 2, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(pUI -> vPos.x + pUI -> vScl.x / 2, pUI -> vPos.y + pUI -> vScl.y / 2, 0.0f);
			// rhw�̐ݒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
			// �e�N�X�`�����W�w��
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(pUI -> vTexPatSize.x, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, pUI -> vTexPatSize.y);
			pVtx[3].tex = D3DXVECTOR2(pUI -> vTexPatSize.x, pUI -> vTexPatSize.y);
		
			// ���_�f�[�^���A�����b�N����
			pUI -> pD3DVtxBuff -> Unlock();
		}
	}
}


/*******************************************************************************
* 3D��ԓ���UI�̒��_���쐬
*******************************************************************************/
HRESULT MakeVertexUI3D(LPDIRECT3DDEVICE9 pDevice, UI_3D *pUI, int nMaxNum)
{
	for(int nNumUI = 0 ; nNumUI < nMaxNum ; nNumUI++, pUI++)
	{
		// �I�u�W�F�N�g�̒��_�o�b�t�@���쐬(�����x�����ǈ�����@�N���X�������Ƃ��ɂȂ�Ƃ�����)
		if(FAILED(pDevice -> CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,
												D3DUSAGE_WRITEONLY,
												FVF_VERTEX_3D,
												D3DPOOL_MANAGED,
												&pUI -> pD3DVtxBuff,
												NULL)))
		{
			return E_FAIL;
		}

		{//���_�o�b�t�@�̒��g�𖄂߂�
			VERTEX_3D *pVtx;

			// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
			pUI -> pD3DVtxBuff -> Lock(0,0,(void**)&pVtx,0);
			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(pUI -> vPos.x - pUI -> vScl.x / 2, pUI -> vPos.y - pUI -> vScl.y / 2, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(pUI -> vPos.x + pUI -> vScl.x / 2, pUI -> vPos.y - pUI -> vScl.y / 2, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(pUI -> vPos.x - pUI -> vScl.x / 2, pUI -> vPos.y + pUI -> vScl.y / 2, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(pUI -> vPos.x + pUI -> vScl.x / 2, pUI -> vPos.y + pUI -> vScl.y / 2, 0.0f);
			// �@���̐ݒ�
			pVtx[0].nor	= D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[1].nor	= D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[2].nor	= D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[3].nor	= D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			// ���_�J���[�̐ݒ�
			pVtx[0].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			// �e�N�X�`�����W�w��
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(pUI -> vTexPatSize.x, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, pUI -> vTexPatSize.y);
			pVtx[3].tex = D3DXVECTOR2(pUI -> vTexPatSize.x, pUI -> vTexPatSize.y);

			// ���_�f�[�^���A�����b�N����
			pUI -> pD3DVtxBuff -> Unlock();
		}
	}
	return S_OK;
}

/*******************************************************************************
* �I�v�V�����̈ʒu�ƃT�C�Y���Čv�Z����
*******************************************************************************/
void RecalculationOption(void)
{
	SCREEN Screen = GetScreenInfo();

	// �I�v�V�����E�B���h�E�̏�����
#if 1
	g_Option[OPTION_WINDOW].vScl = D3DXVECTOR3(Screen.nWidth / 16 * 6,Screen.nHeight / 9 * 6,0.0f);
	g_Option[OPTION_WINDOW].vPos = D3DXVECTOR3(Screen.nWidth / 2.0f,Screen.nHeight / 2,0.0f);
#else
	g_Option[OPTION_WINDOW].vScl = D3DXVECTOR3(SCREEN_WIDTH / 16 * 6,SCREEN_HEIGHT / 9 * 6,0.0f);
	g_Option[OPTION_WINDOW].vPos = D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f);
#endif
	// BGM�~�L�T�[�o�[�̏�����
	g_Option[BGM_MIXERBAR].vScl = D3DXVECTOR3(g_Option[OPTION_WINDOW].vScl.x,g_Option[OPTION_WINDOW].vPos.y / 3,0.0f);
	g_Option[BGM_MIXERBAR].vPos = D3DXVECTOR3(g_Option[OPTION_WINDOW].vPos.x,g_Option[OPTION_WINDOW].vPos.y - (g_Option[OPTION_WINDOW].vScl.y / 4),0.0f);
	// SE�~�L�T�[�o�[�̏�����
	g_Option[SE_MIXERBAR].vScl = D3DXVECTOR3(g_Option[BGM_MIXERBAR].vScl.x,g_Option[BGM_MIXERBAR].vScl.y,0.0f);
	g_Option[SE_MIXERBAR].vPos = D3DXVECTOR3(g_Option[OPTION_WINDOW].vPos.x,g_Option[OPTION_WINDOW].vPos.y + (g_Option[OPTION_WINDOW].vScl.y / 10),0.0f);
	// �u���j���[�o�[��\������v�̕����̏�����
	g_Option[MENUBAR_INDICATE].vScl = D3DXVECTOR3(g_Option[OPTION_WINDOW].vScl.x / 3 * 2,g_Option[OPTION_WINDOW].vScl.y / 4,0.0f);
	g_Option[MENUBAR_INDICATE].vPos = D3DXVECTOR3(g_Option[OPTION_WINDOW].vPos.x - (g_Option[OPTION_WINDOW].vScl.x / 7),g_Option[OPTION_WINDOW].vPos.y + (g_Option[OPTION_WINDOW].vScl.y / 3),0.0f);
	// �`�F�b�N�{�b�N�X�̏�����
	g_Option[CHECKBOX].vScl = D3DXVECTOR3(g_Option[OPTION_WINDOW].vScl.x / 10,g_Option[OPTION_WINDOW].vScl.y / 10,0.0f);
	g_Option[CHECKBOX].vPos = D3DXVECTOR3(g_Option[OPTION_WINDOW].vPos.x + (g_Option[OPTION_WINDOW].vScl.x / 3),g_Option[OPTION_WINDOW].vPos.y + (g_Option[OPTION_WINDOW].vScl.y / 6 * 2),0.0f);
	// ����{�^���̏�����
	g_Option[OPTION_WINDOW_CLOSEBUTTON].vScl = D3DXVECTOR3(g_Option[OPTION_WINDOW].vScl.x / 10,g_Option[OPTION_WINDOW].vScl.y / 10,0.0f);
	g_Option[OPTION_WINDOW_CLOSEBUTTON].vPos = D3DXVECTOR3((g_Option[OPTION_WINDOW].vPos.x + (g_Option[OPTION_WINDOW].vScl.x / 2)) - (g_Option[OPTION_WINDOW_CLOSEBUTTON].vScl.x / 2),
															(g_Option[OPTION_WINDOW].vPos.y - (g_Option[OPTION_WINDOW].vScl.y / 2)) + (g_Option[OPTION_WINDOW_CLOSEBUTTON].vScl.y / 2)
															,0.0f);
	// BGM�~�L�T�[�o�[�̃A�C�R���̏�����
	g_Option[BGM_MIXERBAR_ICON].vScl = D3DXVECTOR3(g_Option[OPTION_WINDOW].vScl.x / 10,g_Option[OPTION_WINDOW].vScl.y / 10,0.0f);
	g_Option[BGM_MIXERBAR_ICON].vPos = D3DXVECTOR3(g_Option[OPTION_WINDOW].vPos.x,g_Option[OPTION_WINDOW].vPos.y - (g_Option[OPTION_WINDOW].vScl.y / 4),0.0f);
	// SE�~�L�T�[�o�[�̃A�C�R���̏�����
	g_Option[SE_MIXERBAR_ICON].vScl = D3DXVECTOR3(g_Option[OPTION_WINDOW].vScl.x / 10,g_Option[OPTION_WINDOW].vScl.y / 10,0.0f);
	g_Option[SE_MIXERBAR_ICON].vPos = D3DXVECTOR3(g_Option[OPTION_WINDOW].vPos.x,g_Option[OPTION_WINDOW].vPos.y + (g_Option[OPTION_WINDOW].vScl.y / 10),0.0f);


	for(int nCnt = 0;nCnt < MAX_OPTION;nCnt ++)
	{
		g_Option[nCnt].vTexPatSize = D3DXVECTOR2(1.0f,1.0f);
	}
	// ���_���W�̕ύX
	//SetVertexUI2D(&g_Option[0],MAX_OPTION);

	PrintDebugProc("�I�v�V�����E�B���h�E��SizeX=%f\n",g_Option[OPTION_WINDOW].vScl.x);
	PrintDebugProc("�I�v�V�����E�B���h�E��SizeY=%f\n",g_Option[OPTION_WINDOW].vScl.y);
	PrintDebugProc("�I�v�V�����E�B���h�E��PosX=%f\n",g_Option[OPTION_WINDOW].vPos.x);
	PrintDebugProc("�I�v�V�����E�B���h�E��PosY=%f\n",g_Option[OPTION_WINDOW].vPos.y);
}