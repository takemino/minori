/*******************************************************************************
* �^�C�g��:		UI����
* �v���O������:	UI.h
* �쐬��:		GP11A331 4�� �Ɍ��C�H
* �쐬��:		2016/02/01
********************************************************************************
* �X�V����:		- 2016/02/25	�Ɍ��C�H
*					- V1.00		Initial Version
*******************************************************************************/
#ifndef _UI_H_
#define _UI_H_

#include "Main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

/*******************************************************************************
* �񋓑̒�`
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
// �\����
//*****************************************************************************
typedef struct UI_2D
{
	LPDIRECT3DVERTEXBUFFER9	pD3DVtxBuff;			// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
	D3DXVECTOR3 vPos;								// ���W
	D3DXVECTOR3 vPos2;
	D3DXVECTOR3 vScl;								// �T�C�Y
	D3DXCOLOR	col;								// �F
	int			nCnt;
	bool		bUse;								// �g�p���Ă邩�ǂ���
	bool		bChoice;							// �I���t���O
	D3DXVECTOR2 vTexPatSize;						// �e�N�X�`���̂ǂ̕������|���S���ɓ\�邩���߂�ϐ�
};

typedef struct UI_3D
{
	D3DXMATRIX mtxWorld;							// ���[���h�}�g���b�N�X
	LPDIRECT3DVERTEXBUFFER9	pD3DVtxBuff;			// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vRot;
	D3DXVECTOR3 vScl;
	D3DXCOLOR	col;
	int			nCnt;
	bool		bUse;
	bool		bChoice;
	D3DXVECTOR2 vTexPatSize;				
	D3DXVECTOR3 vVtxPos[4];					//�r���{�[�h�����蔻��p�̒��_���W
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitUI(void);
void UninitUI(void);
void UpdateUI(void);
void DrawUI(void);

#endif
