/*******************************************************************************
* �^�C�g��:		�����蔻�菈��
* �v���O������:	CollisionDetection.cpp
* �쐬��:		GP11A331 4�� �Ɍ��C�H
* �쐬��:		2015/11/24
********************************************************************************
* �X�V����:		- 2015/11/24	�Ɍ��C�H
*					- V1.00		Initial Version
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "CollisionDetection.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define		NO_USE_D3DX	// �錾���R�����g�ɂ����D3DXVec3Dot�����g�p����

//**************************************
// �\����
//**************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//=============================================================================
// ����
//=============================================================================
float dotProduct( D3DXVECTOR3 vl, D3DXVECTOR3 vr)
{
	float ans = (vl.x * vr.x + vl.y * vr.y + vl.z * vr.z);

#ifdef NO_USE_D3DX


#else
	// �_�C���N�g�w�ł́A�A�A
	

#endif

	return(ans);


}


//=============================================================================
// �O��
//=============================================================================
D3DXVECTOR3 crossProduct( D3DXVECTOR3 vl, D3DXVECTOR3 vr )
{
	D3DXVECTOR3 ret;

	ret.x = vl.y * vr.z - vl.z * vr.y;
	ret.y = vl.z * vr.x - vl.x * vr.z;
	ret.z = vl.x * vr.y - vl.y * vr.x;
#ifdef NO_USE_D3DX



#else
	// �_�C���N�g�w�ł́A�A�A

#endif

	return(ret);
}


//=============================================================================
// �|���S���Ɛ����Ƃ̓����蔻��
// p0  :�|���S���̒��_1
// p1  :�|���S���̒��_2
// p2  :�|���S���̒��_3
// pos0:�n�_�i�ړ��O�j
// pos1:�I�_�i�ړ���j
// �Ԃ�l�F0�͓������Ă��Ȃ�  1:�������Ă���
//=============================================================================
int CollisionDetection(D3DXVECTOR3 p0, D3DXVECTOR3 p1, D3DXVECTOR3 p2, D3DXVECTOR3 posOld, D3DXVECTOR3 posNow)
{
	D3DXVECTOR3		nor;		// �|���S���̖@��

	{	// �|���S���̊O�ς��Ƃ��Ė@�������߂�
		D3DXVECTOR3 vec01 = p1 - p0;
		D3DXVECTOR3 vec02 = p2 - p0;
		nor = crossProduct(vec01, vec02);
		D3DXVec3Normalize(&nor, &nor);
	}

	{	// ���ʂƐ����̓��ςƂ��ďՓ˂��Ă���\���𒲂ׂ�
		// ���߂��@���ƃx�N�g���Q�i�����̗��[�ƃ|���S����̔C�ӂ̓_�j�̓��ςƂ��ďՓ˂��Ă���\���𒲂ׂ�
		D3DXVECTOR3 vec1 = posOld - p0;
		D3DXVECTOR3 vec2 = posNow - p0;
		float a = dotProduct(vec1, nor);
		float b = dotProduct(vec2, nor);
		if((a * b) > 0) return 0; // �������Ă���\���͂Ȃ��I
	}

	{	// �|���S���Ɛ����̌�_�����߂�
		D3DXVECTOR3 vec1 = posOld - p0;
		D3DXVECTOR3 vec2 = posNow - p0;
		float			d1 = fabs(dotProduct(vec1, nor));	// ����������߂�ׂ̓_�ƃ|���S���Ƃ̋���
		float			d2 = fabs(dotProduct(vec2, nor));	// ����������߂�ׂ̓_�ƃ|���S���Ƃ̋���
		float			a = d1 / (d1 + d2);					// ������


		// pos0����pos1�ւ̃x�N�g���i�ړ��x�N�g���j
		D3DXVECTOR3 vec3 = posNow - posOld;

		// ��_
		D3DXVECTOR3 p3 = posOld + vec3 * a; // p3�͌�_


		{	// ���߂���_���|���S���̒��ɂ��邩���ׂ�
			
			// �|���S���̊e�ӂ̃x�N�g��
			D3DXVECTOR3 v1 = p1 - p0;
			D3DXVECTOR3 v2 = p2 - p1;
			D3DXVECTOR3 v3 = p0 - p2;

			// �e���_�ƌ�_�Ƃ̃x�N�g��
			D3DXVECTOR3 v4 = p3 - p1;
			D3DXVECTOR3 v5 = p3 - p2;
			D3DXVECTOR3 v6 = p3 - p0;

			// �e�ӂƂ̊O�ςŖ@�������߂�
			D3DXVECTOR3 n1 = crossProduct(v1, v4);
			D3DXVECTOR3 n2 = crossProduct(v2, v5);
			D3DXVECTOR3 n3 = crossProduct(v3, v6);

			// ���ꂼ��̃x�N�g���̌�������ςŃ`�F�b�N
			if(dotProduct(n1, n2) < -0.02f) return 0;
			if(dotProduct(n1, n3) < -0.02f) return 0;
		}
	}

	return(1); // �������Ă���I
}

//==================================================================================================================================================================//

/*******************************************************************************
�֐���:	D3DXVECTOR3* CalcScreenToWorld
����:	D3DXVECTOR3 *pOut,
		int Sx,  // �X�N���[��X���W
		int Sy,  // �X�N���[��Y���W
		float fZ,  // �ˉe��Ԃł�Z�l�i0�`1�j
		int Screen_w,
		int Screen_h,
		D3DXMATRIX *View,
		D3DXMATRIX *Prj
�߂�l:	D3DXVECTOR3*�^	pOut
����:	// �X�N���[�����W�����[���h���W�ɕϊ�
*******************************************************************************/
D3DXVECTOR3 *CalcScreenToWorld(
   D3DXVECTOR3 *pOut,
   int Sx,  // �X�N���[��X���W
   int Sy,  // �X�N���[��Y���W
   float fZ,  // �ˉe��Ԃł�Z�l�i0�`1�j
   int Screen_w,
   int Screen_h,
   D3DXMATRIX *View,
   D3DXMATRIX *Prj
)
{
   /* �e�s��̋t�s����Z�o */
   D3DXMATRIX InvView, InvPrj, VP, InvViewport;
   // �r���[�s��
   D3DXMatrixInverse( &InvView, NULL, View );
   // �v���W�F�N�V�����s��
   D3DXMatrixInverse( &InvPrj, NULL, Prj );
   D3DXMatrixIdentity( &VP );
   // �r���[�|�[�g�s��
   VP._11 = Screen_w/2.0f; VP._22 = -Screen_h/2.0f;
   VP._41 = Screen_w/2.0f; VP._42 = Screen_h/2.0f;
   D3DXMatrixInverse( &InvViewport, NULL, &VP );

   // �t�ϊ�
   D3DXMATRIX ScreenToWorldMat = InvViewport * InvPrj * InvView;
   D3DXVec3TransformCoord( pOut, &D3DXVECTOR3(Sx,Sy,fZ), &ScreenToWorldMat );

   return pOut;
}
/*******************************************************************************
�֐���:	D3DXVECTOR3 *CalcScreenToXZ
����:	D3DXVECTOR3 *pout,
		int Sx,
		int Sy,
		int Screen_w,
		int Screen_h,
		D3DXMATRIX *View,
		D3DXMATRIX *Prj
�߂�l:	D3DXVECTOR3*�^	pOut
����:	�X�N���[�����W����XZ���ʂ̃��[���h���W���o��
*******************************************************************************/
D3DXVECTOR3 *CalcScreenToXZ(
   D3DXVECTOR3 *pOut,
   int Sx,
   int Sy,
   int Screen_w,
   int Screen_h,
   D3DXMATRIX *View,
   D3DXMATRIX *Prj
)
{
   D3DXVECTOR3 nearpos;	// �ˉe��Ԃ�Z=0�̓_�����[���h��Ԃ̍��W�ɂ����_(�ŋߓ_)
   D3DXVECTOR3 farpos;	// �ˉe��Ԃ�Z=1�̓_�����[���h��Ԃ̍��W�ɂ����_(�ŉ��_)
   D3DXVECTOR3 ray;		// �ŋߓ_����ŉ��_�֌������x�N�g��
   CalcScreenToWorld( &nearpos, Sx, Sy, 0.0f, Screen_w, Screen_h, View, Prj );
   CalcScreenToWorld( &farpos, Sx, Sy, 1.0f, Screen_w, Screen_h, View, Prj );
   ray = farpos - nearpos;
   D3DXVec3Normalize( &ray, &ray );

   /* ray�Ə��Ƃ̌���������ꍇ�͌�_���A�Ȃ��ꍇ�͉����̕ǂƂ̌�_���o��(�΂ߏォ�珰�����Ă�����̂Ƃ���) */
   if( ray.y <= 0 ) 
   {// ���Ƃ̌���������ꍇ
      // ����_
      float Lray = D3DXVec3Dot( &ray, &D3DXVECTOR3(0,1,0) );
      float LP0 = D3DXVec3Dot( &(-nearpos), &D3DXVECTOR3(0,1,0) );
      *pOut = nearpos + (LP0/Lray)*ray;
   }
   else 
   {// �ŋߓ_����ŉ��_�֌������x�N�g�������ƌ������Ă��Ȃ��ꍇ
      *pOut = farpos;
   }

   return pOut;
}