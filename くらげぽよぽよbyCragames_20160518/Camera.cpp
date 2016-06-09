/*******************************************************************************
* �^�C�g��:		�J��������
* �v���O������:	Camera.cpp
* �쐬��:		GP11A331 4�� �Ɍ��C�H
* �쐬��:		2015/10/22
********************************************************************************
* �X�V����:		- 2016/01/10	 �Ɍ��C�H
*					- V1.00		Initial Version
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "Camera.h"
#include "Input.h"
#include "DebugProc.h"
#include "Player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	CAM_POS_V_X				(0.0f)				// �J�����̎��_�����ʒu(X���W)
#define	CAM_POS_V_Y				(1800.0f)			// �J�����̎��_�����ʒu(Y���W)
#define	CAM_POS_V_Z				(-1600.0f)			// �J�����̎��_�����ʒu(Z���W)
#define	CAM_POS_R_X				(0.0f)				// �J�����̒����_�����ʒu(X���W)
#define	CAM_POS_R_Y				(-700.0f)			// �J�����̒����_�����ʒu(Y���W)
#define	CAM_POS_R_Z				(200.0f)				// �J�����̒����_�����ʒu(Z���W)

#define	VIEW_ANGLE				(D3DXToRadian(45.0f))							// �r���[���ʂ̎���p
#define	VIEW_ASPECT				((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// �r���[���ʂ̃A�X�y�N�g��
#define	VIEW_NEAR_Z				(10.0f)											// �r���[���ʂ�NearZ�l
#define	VIEW_FAR_Z				(10000.0f)										// �r���[���ʂ�FarZ�l
#define	VALUE_MOVE_CAMERA		(10.0f)											// �J�����̈ړ���
#define	VALUE_ROTATE_CAMERA		(D3DX_PI * 0.01f)								// �J�����̉�]��
#define	VALUE_ADJUST_DISTANCE	(2.0f)											// ���_�ƒ����_�̋���������
#define HALF_OF_PI				(D3DX_PI / 2)

#define	DISTANCE_CAMERA_R (30)					// ���f���̎����̐�܂ł̋���

#define	CHASE_HEIGHT_V (CAM_POS_V_Y)			// �ǐՎ��̎��_�̍���
#define	CHASE_HEIGHT_R (CAM_POS_R_Y)			// �ǐՎ��̒����_�̍���

//*****************************************************************************
// �񋓑�
//*****************************************************************************
typedef enum
{
	RELEASE_CAMERA = 0,
	DEBUG_CAMERA,
} CAMERA_MODE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
CAMERA g_Camera;		// �J�������

CAMERA_MODE g_CameraMode = RELEASE_CAMERA;
/*******************************************************************************
�֐���:	HRESULT InitCamera(void)
����:	�Ȃ�
�߂�l:	HRESULT�^
����:	�J�����̏�����
*******************************************************************************/
HRESULT InitCamera(void)
{
	/* ���C�����[�h�ɂ�鏉�����̕��� */
	// ���_������
	g_Camera.posV = D3DXVECTOR3(0.0f, 100.0f, -200.0f);
	// �����_������
	g_Camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// ������x�N�g��������
	g_Camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	// ���_�̖ړI�ʒu
	g_Camera.posVDest = g_Camera.posV;
	// �����_�̖ړI�ʒu
	g_Camera.posRDest = g_Camera.posR;
	// �J���������i��]�p�j�̏�����
	g_Camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// ���_�ƒ����_�̋��������߂�
	g_Camera.fDistance = sqrt(powf(g_Camera.posR.x - g_Camera.posV.x, 2.0f) +  powf(g_Camera.posR.y - g_Camera.posV.y, 2.0f) + powf(g_Camera.posR.z - g_Camera.posV.z, 2.0f));
	// �n�߂̎��_�ƒ����_�̋���
	g_Camera.fInitialDistance = g_Camera.fDistance;
	// ���_�̍�����������
	g_Camera.fChaseHeightV = CHASE_HEIGHT_V;
	// �����_�̍�����������
	g_Camera.fChaseHeightR = CHASE_HEIGHT_R;
	// �n�߂̎��_�ƒ����_����钼�p�O�p�`�̊p�x�̏�����
	g_Camera.fInitialSin = fabs((g_Camera.posR.y - g_Camera.posV.y) / g_Camera.fInitialDistance);
	g_Camera.fInitialCos = fabs((g_Camera.posR.z - g_Camera.posV.z) / g_Camera.fInitialDistance);
	
	return S_OK;
}

//=============================================================================
// �J�����̏I������
//=============================================================================
void UninitCamera(void)
{

}

//=============================================================================
// �J�����̍X�V����
//=============================================================================
void UpdateCamera(void)
{
	float fIntervalCamera, fMagnitudeMove;
	float fRateChaseCameraV, fRateChaseCameraR;

	// �����_�̖ړI�ʒu
	g_Camera.posRDest.x = CAM_POS_R_X;
	g_Camera.posRDest.y = CAM_POS_R_Y;
	g_Camera.posRDest.z = CAM_POS_R_Z;

	// ���_�̖ړI�ʒu
	g_Camera.posVDest.x = CAM_POS_V_X;
	g_Camera.posVDest.y = CAM_POS_V_Y;// + g_Camera.fDistance * g_Camera.fInitialSin;
	g_Camera.posVDest.z = CAM_POS_V_Z;// - g_Camera.fDistance * g_Camera.fInitialCos;

	// �����_�̕␳
	g_Camera.posR.x += (g_Camera.posRDest.x - g_Camera.posR.x);
	g_Camera.posR.y += (g_Camera.posRDest.y - g_Camera.posR.y);
	g_Camera.posR.z += (g_Camera.posRDest.z - g_Camera.posR.z);

	// ���_�̕␳
	g_Camera.posV.x += (g_Camera.posVDest.x - g_Camera.posV.x);
	g_Camera.posV.y += (g_Camera.posVDest.y - g_Camera.posV.y);
	g_Camera.posV.z += (g_Camera.posVDest.z - g_Camera.posV.z);

	//PrintDebugProc("[�J�����̎��_  �F(%f : %f : %f)]\n", g_Camera.posV.x, g_Camera.posV.y, g_Camera.posV.z);
	//PrintDebugProc("[�J�����̒����_�F(%f : %f : %f)]\n", g_Camera.posR.x, g_Camera.posR.y, g_Camera.posR.z);
	//PrintDebugProc("[�J�����̌���  �F(%f)]\n", g_Camera.rot.y);
	//PrintDebugProc("\n");

	//PrintDebugProc("*** �J�������� ***\n");
	///*PrintDebugProc("���_�㏸     : [ �x ]\n");
	//PrintDebugProc("���_���~     : [ �m ]\n");
	//PrintDebugProc("�����_�㏸   : [ �s ]\n");
	//PrintDebugProc("�����_���~   : [ �a ]\n");*/
	//PrintDebugProc("�Y�[���C��   : [ �t ]\n");
	//PrintDebugProc("�Y�[���A�E�g : [ �l ]\n");
	//PrintDebugProc("\n");
}

//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Camera.mtxView);
	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_Camera.mtxView, &g_Camera.posV, &g_Camera.posR, &g_Camera.vecU);
	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice -> SetTransform(D3DTS_VIEW, &g_Camera.mtxView);
	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Camera.mtxProjection);
	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&g_Camera.mtxProjection, VIEW_ANGLE, VIEW_ASPECT, VIEW_NEAR_Z, VIEW_FAR_Z);
	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�(�����ϊ��̐ݒ�)
	pDevice -> SetTransform(D3DTS_PROJECTION, &g_Camera.mtxProjection);
}

/*******************************************************************************
�֐���:	CAMERA *GetCamera(void)
����:	�Ȃ�
�߂�l:	CAMERA�^
����:	�J�����̃|�C���^���擾
*******************************************************************************/
CAMERA *GetCamera(void)
{
	return &g_Camera;
}
