/*******************************************************************************
* タイトル:		プレイヤー処理
* プログラム名:	Player.h
* 作成者:		GP11A331 4番 伊原佑稀
* 作成日:		2016/01/18
********************************************************************************
* 更新履歴:		- 2016/01/18	伊原佑稀
*					- V1.00		Initial Version
*******************************************************************************/
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 列挙体
//*****************************************************************************

//*****************************************************************************
// 構造体
//*****************************************************************************
typedef struct
{
	D3DXMATRIX mtxWorld;			// ワールドマトリックス
	D3DXVECTOR3 pos;				// ワールド空間内におけるローカル座標の原点の座標
	D3DXVECTOR3 posOld;				// 1フレーム前のモデルの位置
	D3DXVECTOR3 posDest;			// 移動先
	D3DXVECTOR3 rot;				// 回転角
	D3DXVECTOR3	rotDest;			// 目的の向き
	D3DXVECTOR3 scl;				// モデルの大きさ(スケール)
	D3DXVECTOR3	move;				// 移動量
	D3DXVECTOR3	DirVec;				// 方向ベクトル
	D3DXVECTOR3	UnitVelocity;		// 単位速度
	float	radius;					// プレイヤーの半径
	float	fScore;
	int		nIdxShadow;				// 使用している影のインデックス
	/* アニメ */
	int		nCntAnim;
	int		nPatAnim;
	int		nNextPatAnim;
}PLAYER;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetpPlayer(int nPlayer);

#endif
