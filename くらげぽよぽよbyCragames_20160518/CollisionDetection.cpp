/*******************************************************************************
* タイトル:		当たり判定処理
* プログラム名:	CollisionDetection.cpp
* 作成者:		GP11A331 4番 伊原佑稀
* 作成日:		2015/11/24
********************************************************************************
* 更新履歴:		- 2015/11/24	伊原佑稀
*					- V1.00		Initial Version
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "CollisionDetection.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define		NO_USE_D3DX	// 宣言をコメントにするとD3DXVec3Dot等を使用する

//**************************************
// 構造体
//**************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// 内積
//=============================================================================
float dotProduct( D3DXVECTOR3 vl, D3DXVECTOR3 vr)
{
	float ans = (vl.x * vr.x + vl.y * vr.y + vl.z * vr.z);

#ifdef NO_USE_D3DX


#else
	// ダイレクトＸでは、、、
	

#endif

	return(ans);


}


//=============================================================================
// 外積
//=============================================================================
D3DXVECTOR3 crossProduct( D3DXVECTOR3 vl, D3DXVECTOR3 vr )
{
	D3DXVECTOR3 ret;

	ret.x = vl.y * vr.z - vl.z * vr.y;
	ret.y = vl.z * vr.x - vl.x * vr.z;
	ret.z = vl.x * vr.y - vl.y * vr.x;
#ifdef NO_USE_D3DX



#else
	// ダイレクトＸでは、、、

#endif

	return(ret);
}


//=============================================================================
// ポリゴンと線分との当たり判定
// p0  :ポリゴンの頂点1
// p1  :ポリゴンの頂点2
// p2  :ポリゴンの頂点3
// pos0:始点（移動前）
// pos1:終点（移動後）
// 返り値：0は当たっていない  1:当たっている
//=============================================================================
int CollisionDetection(D3DXVECTOR3 p0, D3DXVECTOR3 p1, D3DXVECTOR3 p2, D3DXVECTOR3 posOld, D3DXVECTOR3 posNow)
{
	D3DXVECTOR3		nor;		// ポリゴンの法線

	{	// ポリゴンの外積をとって法線を求める
		D3DXVECTOR3 vec01 = p1 - p0;
		D3DXVECTOR3 vec02 = p2 - p0;
		nor = crossProduct(vec01, vec02);
		D3DXVec3Normalize(&nor, &nor);
	}

	{	// 平面と線分の内積とって衝突している可能性を調べる
		// 求めた法線とベクトル２つ（線分の両端とポリゴン上の任意の点）の内積とって衝突している可能性を調べる
		D3DXVECTOR3 vec1 = posOld - p0;
		D3DXVECTOR3 vec2 = posNow - p0;
		float a = dotProduct(vec1, nor);
		float b = dotProduct(vec2, nor);
		if((a * b) > 0) return 0; // 当たっている可能性はない！
	}

	{	// ポリゴンと線分の交点を求める
		D3DXVECTOR3 vec1 = posOld - p0;
		D3DXVECTOR3 vec2 = posNow - p0;
		float			d1 = fabs(dotProduct(vec1, nor));	// 内分比を求める為の点とポリゴンとの距離
		float			d2 = fabs(dotProduct(vec2, nor));	// 内分比を求める為の点とポリゴンとの距離
		float			a = d1 / (d1 + d2);					// 内分比


		// pos0からpos1へのベクトル（移動ベクトル）
		D3DXVECTOR3 vec3 = posNow - posOld;

		// 交点
		D3DXVECTOR3 p3 = posOld + vec3 * a; // p3は交点


		{	// 求めた交点がポリゴンの中にあるか調べる
			
			// ポリゴンの各辺のベクトル
			D3DXVECTOR3 v1 = p1 - p0;
			D3DXVECTOR3 v2 = p2 - p1;
			D3DXVECTOR3 v3 = p0 - p2;

			// 各頂点と交点とのベクトル
			D3DXVECTOR3 v4 = p3 - p1;
			D3DXVECTOR3 v5 = p3 - p2;
			D3DXVECTOR3 v6 = p3 - p0;

			// 各辺との外積で法線を求める
			D3DXVECTOR3 n1 = crossProduct(v1, v4);
			D3DXVECTOR3 n2 = crossProduct(v2, v5);
			D3DXVECTOR3 n3 = crossProduct(v3, v6);

			// それぞれのベクトルの向きを内積でチェック
			if(dotProduct(n1, n2) < -0.02f) return 0;
			if(dotProduct(n1, n3) < -0.02f) return 0;
		}
	}

	return(1); // 当たっている！
}

//==================================================================================================================================================================//

/*******************************************************************************
関数名:	D3DXVECTOR3* CalcScreenToWorld
引数:	D3DXVECTOR3 *pOut,
		int Sx,  // スクリーンX座標
		int Sy,  // スクリーンY座標
		float fZ,  // 射影空間でのZ値（0～1）
		int Screen_w,
		int Screen_h,
		D3DXMATRIX *View,
		D3DXMATRIX *Prj
戻り値:	D3DXVECTOR3*型	pOut
説明:	// スクリーン座標をワールド座標に変換
*******************************************************************************/
D3DXVECTOR3 *CalcScreenToWorld(
   D3DXVECTOR3 *pOut,
   int Sx,  // スクリーンX座標
   int Sy,  // スクリーンY座標
   float fZ,  // 射影空間でのZ値（0～1）
   int Screen_w,
   int Screen_h,
   D3DXMATRIX *View,
   D3DXMATRIX *Prj
)
{
   /* 各行列の逆行列を算出 */
   D3DXMATRIX InvView, InvPrj, VP, InvViewport;
   // ビュー行列
   D3DXMatrixInverse( &InvView, NULL, View );
   // プロジェクション行列
   D3DXMatrixInverse( &InvPrj, NULL, Prj );
   D3DXMatrixIdentity( &VP );
   // ビューポート行列
   VP._11 = Screen_w/2.0f; VP._22 = -Screen_h/2.0f;
   VP._41 = Screen_w/2.0f; VP._42 = Screen_h/2.0f;
   D3DXMatrixInverse( &InvViewport, NULL, &VP );

   // 逆変換
   D3DXMATRIX ScreenToWorldMat = InvViewport * InvPrj * InvView;
   D3DXVec3TransformCoord( pOut, &D3DXVECTOR3(Sx,Sy,fZ), &ScreenToWorldMat );

   return pOut;
}
/*******************************************************************************
関数名:	D3DXVECTOR3 *CalcScreenToXZ
引数:	D3DXVECTOR3 *pout,
		int Sx,
		int Sy,
		int Screen_w,
		int Screen_h,
		D3DXMATRIX *View,
		D3DXMATRIX *Prj
戻り値:	D3DXVECTOR3*型	pOut
説明:	スクリーン座標からXZ平面のワールド座標を出力
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
   D3DXVECTOR3 nearpos;	// 射影空間のZ=0の点をワールド空間の座標にした点(最近点)
   D3DXVECTOR3 farpos;	// 射影空間のZ=1の点をワールド空間の座標にした点(最遠点)
   D3DXVECTOR3 ray;		// 最近点から最遠点へ向かうベクトル
   CalcScreenToWorld( &nearpos, Sx, Sy, 0.0f, Screen_w, Screen_h, View, Prj );
   CalcScreenToWorld( &farpos, Sx, Sy, 1.0f, Screen_w, Screen_h, View, Prj );
   ray = farpos - nearpos;
   D3DXVec3Normalize( &ray, &ray );

   /* rayと床との交差がある場合は交点を、ない場合は遠くの壁との交点を出力(斜め上から床を見ているものとする) */
   if( ray.y <= 0 ) 
   {// 床との交差がある場合
      // 床交点
      float Lray = D3DXVec3Dot( &ray, &D3DXVECTOR3(0,1,0) );
      float LP0 = D3DXVec3Dot( &(-nearpos), &D3DXVECTOR3(0,1,0) );
      *pOut = nearpos + (LP0/Lray)*ray;
   }
   else 
   {// 最近点から最遠点へ向かうベクトルが床と交差していない場合
      *pOut = farpos;
   }

   return pOut;
}