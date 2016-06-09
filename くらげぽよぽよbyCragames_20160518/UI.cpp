/*******************************************************************************
* タイトル:		UI処理
* プログラム名:	UI.cpp
* 作成者:		GP11A331 4番 伊原佑稀
* 作成日:		2016/02/01
********************************************************************************
* 更新履歴:		- 2016/02/25	伊原佑稀
*					- V1.00		Initial Version
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "UI.h"
#include "DebugProc.h"
#include "Texture.h"
#include "Input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
UI_2D g_Option[MAX_OPTION];

RECT g_RectClient,g_RectWindow;

bool g_bOptionWindow;																		// オプションウィンドウを表示中かどうか(true→表示中)
bool g_bIndicateMenuBar;																	// メニューバーを表示するかどうか(true→表示する)

/*******************************************************************************
* プロトタイプ宣言
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
関数名	void InitUI(void)
作成者	竹本
説明	UIの初期化処理
*******************************************************************************/
void InitUI(void)
{
	// オプションの初期化処理
	InitOption();
}

/*******************************************************************************
関数名	void UninitUI(void)
作成者	竹本
説明	UIの終了処理
*******************************************************************************/
void UninitUI(void)
{
}

/*******************************************************************************
関数名	void UpdataUI(void)
作成者	竹本
説明	UIの更新処理
*******************************************************************************/
void UpdateUI(void)
{
	// オプションの更新処理
	UpdateOption();
}

/*******************************************************************************
関数名	void DrawUI(void)
作成者	竹本
説明	UIの描画処理
*******************************************************************************/
void DrawUI(void)
{
	// オプションの描画処理
	DrawOption();
}

/*******************************************************************************
関数名	void InitOption(void);
作成者	竹本
説明	オプションの初期化処理
*******************************************************************************/
void InitOption(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	HWND hWnd = GetHandleWindow();
	SCREEN Screen = GetScreenInfo();

	// オプションウィンドウの初期化
#if 1
	g_Option[OPTION_WINDOW].vScl = D3DXVECTOR3(Screen.nWidth / 16 * 6,Screen.nHeight / 9 * 6,0.0f);
	g_Option[OPTION_WINDOW].vPos = D3DXVECTOR3(Screen.nWidth / 2,Screen.nHeight / 2,0.0f);
#else
	g_Option[OPTION_WINDOW].vScl = D3DXVECTOR3(SCREEN_WIDTH / 16 * 6,SCREEN_HEIGHT / 9 * 6,0.0f);
	g_Option[OPTION_WINDOW].vPos = D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f);
#endif
	// BGMミキサーバーの初期化
	g_Option[BGM_MIXERBAR].vScl = D3DXVECTOR3(g_Option[OPTION_WINDOW].vScl.x,g_Option[OPTION_WINDOW].vPos.y / 3,0.0f);
	g_Option[BGM_MIXERBAR].vPos = D3DXVECTOR3(g_Option[OPTION_WINDOW].vPos.x,g_Option[OPTION_WINDOW].vPos.y - (g_Option[OPTION_WINDOW].vScl.y / 4),0.0f);
	// SEミキサーバーの初期化
	g_Option[SE_MIXERBAR].vScl = D3DXVECTOR3(g_Option[BGM_MIXERBAR].vScl.x,g_Option[BGM_MIXERBAR].vScl.y,0.0f);
	g_Option[SE_MIXERBAR].vPos = D3DXVECTOR3(g_Option[OPTION_WINDOW].vPos.x,g_Option[OPTION_WINDOW].vPos.y + (g_Option[OPTION_WINDOW].vScl.y / 10),0.0f);
	// 「メニューバーを表示する」の文字の初期化
	g_Option[MENUBAR_INDICATE].vScl = D3DXVECTOR3(g_Option[OPTION_WINDOW].vScl.x / 3 * 2,g_Option[OPTION_WINDOW].vScl.y / 4,0.0f);
	g_Option[MENUBAR_INDICATE].vPos = D3DXVECTOR3(g_Option[OPTION_WINDOW].vPos.x - (g_Option[OPTION_WINDOW].vScl.x / 7),g_Option[OPTION_WINDOW].vPos.y + (g_Option[OPTION_WINDOW].vScl.y / 3),0.0f);
	// チェックボックスの初期化
	g_Option[CHECKBOX].vScl = D3DXVECTOR3(g_Option[OPTION_WINDOW].vScl.x / 10,g_Option[OPTION_WINDOW].vScl.y / 10,0.0f);
	g_Option[CHECKBOX].vPos = D3DXVECTOR3(g_Option[OPTION_WINDOW].vPos.x + (g_Option[OPTION_WINDOW].vScl.x / 3),g_Option[OPTION_WINDOW].vPos.y + (g_Option[OPTION_WINDOW].vScl.y / 6 * 2),0.0f);
	// 閉じるボタンの初期化
	g_Option[OPTION_WINDOW_CLOSEBUTTON].vScl = D3DXVECTOR3(g_Option[OPTION_WINDOW].vScl.x / 10,g_Option[OPTION_WINDOW].vScl.y / 10,0.0f);
	g_Option[OPTION_WINDOW_CLOSEBUTTON].vPos = D3DXVECTOR3((g_Option[OPTION_WINDOW].vPos.x + (g_Option[OPTION_WINDOW].vScl.x / 2)) - (g_Option[OPTION_WINDOW_CLOSEBUTTON].vScl.x / 2),
															(g_Option[OPTION_WINDOW].vPos.y - (g_Option[OPTION_WINDOW].vScl.y / 2)) + (g_Option[OPTION_WINDOW_CLOSEBUTTON].vScl.y / 2)
															,0.0f);
	// BGMミキサーバーのアイコンの初期化
	g_Option[BGM_MIXERBAR_ICON].vScl = D3DXVECTOR3(g_Option[OPTION_WINDOW].vScl.x / 10,g_Option[OPTION_WINDOW].vScl.y / 10,0.0f);
	g_Option[BGM_MIXERBAR_ICON].vPos = D3DXVECTOR3(g_Option[OPTION_WINDOW].vPos.x,g_Option[OPTION_WINDOW].vPos.y - (g_Option[OPTION_WINDOW].vScl.y / 4),0.0f);
	// SEミキサーバーのアイコンの初期化
	g_Option[SE_MIXERBAR_ICON].vScl = D3DXVECTOR3(g_Option[OPTION_WINDOW].vScl.x / 10,g_Option[OPTION_WINDOW].vScl.y / 10,0.0f);
	g_Option[SE_MIXERBAR_ICON].vPos = D3DXVECTOR3(g_Option[OPTION_WINDOW].vPos.x,g_Option[OPTION_WINDOW].vPos.y + (g_Option[OPTION_WINDOW].vScl.y / 10),0.0f);


	for(int nCnt = 0;nCnt < MAX_OPTION;nCnt ++)
	{
		g_Option[nCnt].vTexPatSize = D3DXVECTOR2(1.0f,1.0f);
	}
	// オプションウィンドウの頂点座標の設定
	MakeVertexUI2D(pDevice,&g_Option[0],MAX_OPTION);

	g_Option[BGM_MIXERBAR_ICON].bChoice = false;
	g_bOptionWindow = true;
	g_bIndicateMenuBar = true;

}

/*******************************************************************************
関数名	void UpdateOption(void)
作成者	竹本
説明	オプションの更新処理
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
		{// メニューバーの表示の設定
			PrintDebugProc("あたてるよ\n");
			if(g_bIndicateMenuBar == true)
			{
				if(GetMouseLeftTrigger())
				{// 「メニューバーを表示する」のチェックを外す
					g_bIndicateMenuBar = false;
				}
			}
			else
			{
				if(GetMouseLeftTrigger())
				{// 「メニューバーを表示する」にチェックを入れる
					g_bIndicateMenuBar = true;
				}
			}
		}
		if(MouseClientPos.x > g_Option[BGM_MIXERBAR_ICON].vPos.x - (g_Option[BGM_MIXERBAR_ICON].vScl.x / 2) &&
		   MouseClientPos.x < g_Option[BGM_MIXERBAR_ICON].vPos.x + (g_Option[BGM_MIXERBAR_ICON].vScl.x / 2) &&
		   MouseClientPos.y > g_Option[BGM_MIXERBAR_ICON].vPos.y - (g_Option[BGM_MIXERBAR_ICON].vScl.y / 2) &&
		   MouseClientPos.y < g_Option[BGM_MIXERBAR_ICON].vPos.y + (g_Option[BGM_MIXERBAR_ICON].vScl.y / 2))
		{// BGMの音量調整
			PrintDebugProc("あたてるよ\n");
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
		{// SEの音量調整
			PrintDebugProc("あたてるよ\n");
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
//		{// BGMの音量調整
//			PrintDebugProc("あたてるよ\n");
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
//		{// SEの音量調整
//			PrintDebugProc("あたてるよ\n");
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
		{// 閉じるボタン
			PrintDebugProc("あたてるよ\n");
			if(GetMouseLeftTrigger())
			{// オプションのウィンドウを消す
				g_bOptionWindow = false;
			}
		}
	}
	else
	{
		if(GetMouseLeftTrigger())
		{// オプションのウィンドウを表示する
			g_bOptionWindow = true;
		}
	}
}

/*******************************************************************************
* オプションの描画処理
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
			case OPTION_WINDOW:	// オプションウィンドウを描画
				// 頂点バッファをデバイスのデータストリームにバインド
				pDevice -> SetStreamSource(0,g_Option[OPTION_WINDOW].pD3DVtxBuff,0,sizeof(VERTEX_2D));

				// 頂点フォーマットの設定
				pDevice -> SetFVF(FVF_VERTEX_2D);

				// テクスチャの設定
				pDevice -> SetTexture(0,pUITexture[UI_TEXTURE_OPTION_WINDOW]);

				// ポリゴンの描画
				pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,
										 0,
										 NUM_POLYGON);
				break;
			case BGM_MIXERBAR:	// BGMミキサーバーを描画
				// 頂点バッファをデバイスのデータストリームにバインド
				pDevice -> SetStreamSource(0,g_Option[BGM_MIXERBAR].pD3DVtxBuff,0,sizeof(VERTEX_2D));

				// 頂点フォーマットの設定
				pDevice -> SetFVF(FVF_VERTEX_2D);

				// テクスチャの設定
				pDevice -> SetTexture(0,pUITexture[UI_TEXTURE_BGM_MIXERBAR]);

				// ポリゴンの描画
				pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,
										 0,
										 NUM_POLYGON);
				break;
			case SE_MIXERBAR:	// SEミキサーバーを描画
				// 頂点バッファをデバイスのデータストリームにバインド
				pDevice -> SetStreamSource(0,g_Option[SE_MIXERBAR].pD3DVtxBuff,0,sizeof(VERTEX_2D));

				// 頂点フォーマットの設定
				pDevice -> SetFVF(FVF_VERTEX_2D);

				// テクスチャの設定
				pDevice -> SetTexture(0,pUITexture[UI_TEXTURE_SE_MIXERBAR]);

				// ポリゴンの描画
				pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,
										 0,
										 NUM_POLYGON);
				break;
			case MENUBAR_INDICATE:	// 「メニューバーを表示」の文字を描画
				// 頂点バッファをデバイスのデータストリームにバインド
				pDevice -> SetStreamSource(0,g_Option[MENUBAR_INDICATE].pD3DVtxBuff,0,sizeof(VERTEX_2D));

				// 頂点フォーマットの設定
				pDevice -> SetFVF(FVF_VERTEX_2D);

				// テクスチャの設定
				pDevice -> SetTexture(0,pUITexture[UI_TEXTURE_MENUBER_INDICATE]);

				// ポリゴンの描画
				pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,
										 0,
										 NUM_POLYGON);
				break;
			case CHECKBOX:
				if(g_bIndicateMenuBar == true)
				{	// チェックがついてるチェックボックスを描画
					// 頂点バッファをデバイスのデータストリームにバインド
					pDevice -> SetStreamSource(0,g_Option[CHECKBOX].pD3DVtxBuff,0,sizeof(VERTEX_2D));

					// 頂点フォーマットの設定
					pDevice -> SetFVF(FVF_VERTEX_2D);

					// テクスチャの設定
					pDevice -> SetTexture(0,pUITexture[UI_TEXTURE_CHECKBOX_CHECKIN]);

					// ポリゴンの描画
					pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,
											 0,
											 NUM_POLYGON);
					break;
				}
				else
				{	// チェックがついてないチェックボックスを描画
					// 頂点バッファをデバイスのデータストリームにバインド
					pDevice -> SetStreamSource(0,g_Option[CHECKBOX].pD3DVtxBuff,0,sizeof(VERTEX_2D));

					// 頂点フォーマットの設定
					pDevice -> SetFVF(FVF_VERTEX_2D);

					// テクスチャの設定
					pDevice -> SetTexture(0,pUITexture[UI_TEXTURE_CHECKBOX_CHECKOUT]);

					// ポリゴンの描画
					pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,
											 0,
											 NUM_POLYGON);
					break;
				}
			case OPTION_WINDOW_CLOSEBUTTON:	// オプションウィンドウの閉じるボタンを描画
				// 頂点バッファをデバイスのデータストリームにバインド
				pDevice -> SetStreamSource(0,g_Option[OPTION_WINDOW_CLOSEBUTTON].pD3DVtxBuff,0,sizeof(VERTEX_2D));

				// 頂点フォーマットの設定
				pDevice -> SetFVF(FVF_VERTEX_2D);

				// テクスチャの設定
				pDevice -> SetTexture(0,pUITexture[UI_TEXTURE_OPTION_WINDOW_CLOSEBUTTON]);

				// ポリゴンの描画
				pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,
										 0,
										 NUM_POLYGON);
				break;
			case BGM_MIXERBAR_ICON:
				// 頂点バッファをデバイスのデータストリームにバインド
				pDevice -> SetStreamSource(0,g_Option[BGM_MIXERBAR_ICON].pD3DVtxBuff,0,sizeof(VERTEX_2D));

				// 頂点フォーマットの設定
				pDevice -> SetFVF(FVF_VERTEX_2D);

				// テクスチャの設定
				pDevice -> SetTexture(0,pUITexture[UI_TEXTURE_MIXERBAR_ICON]);

				// ポリゴンの描画
				pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,
										 0,
										 NUM_POLYGON);
				break;
			case SE_MIXERBAR_ICON:
				// 頂点バッファをデバイスのデータストリームにバインド
				pDevice -> SetStreamSource(0,g_Option[SE_MIXERBAR_ICON].pD3DVtxBuff,0,sizeof(VERTEX_2D));

				// 頂点フォーマットの設定
				pDevice -> SetFVF(FVF_VERTEX_2D);

				// テクスチャの設定
				pDevice -> SetTexture(0,pUITexture[UI_TEXTURE_MIXERBAR_ICON]);

				// ポリゴンの描画
				pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,
										 0,
										 NUM_POLYGON);
				break;
			}
		}
	}
}

/*******************************************************************************
* 2D画面のUIの頂点情報作成
*******************************************************************************/
HRESULT MakeVertexUI2D(LPDIRECT3DDEVICE9 pDevice, UI_2D *pUI, int nMaxNum)
{
	for(int nNumUI = 0 ; nNumUI < nMaxNum ; nNumUI++, pUI++)
	{
		// オブジェクトの頂点バッファを作成(処理遅いけど一個ずつ作る　クラス化したときになんとかする)
		if(FAILED(pDevice -> CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,
												D3DUSAGE_WRITEONLY,
												FVF_VERTEX_2D,
												D3DPOOL_MANAGED,
												&pUI -> pD3DVtxBuff,
												NULL)))
		{
			return E_FAIL;
		}

		{// 頂点バッファの中身を埋める
			VERTEX_2D *pVtx;
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			pUI -> pD3DVtxBuff -> Lock(0,0,(void**)&pVtx,0);
			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(pUI -> vPos.x - pUI -> vScl.x / 2, pUI -> vPos.y - pUI -> vScl.y / 2, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(pUI -> vPos.x + pUI -> vScl.x / 2, pUI -> vPos.y - pUI -> vScl.y / 2, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(pUI -> vPos.x - pUI -> vScl.x / 2, pUI -> vPos.y + pUI -> vScl.y / 2, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(pUI -> vPos.x + pUI -> vScl.x / 2, pUI -> vPos.y + pUI -> vScl.y / 2, 0.0f);
			// rhwの設定
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;
			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
			// テクスチャ座標指定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(pUI -> vTexPatSize.x, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, pUI -> vTexPatSize.y);
			pVtx[3].tex = D3DXVECTOR2(pUI -> vTexPatSize.x, pUI -> vTexPatSize.y);
		
			// 頂点データをアンロックする
			pUI -> pD3DVtxBuff -> Unlock();
		}
	}
	return S_OK;
}

/*******************************************************************************
* 2D画面のUIの頂点情報変更
*******************************************************************************/
void SetVertexUI2D(UI_2D *pUI, int nMaxNum)
{
	for(int nNumUI = 0 ; nNumUI < nMaxNum ; nNumUI++, pUI++)
	{
		{// 頂点バッファの中身を埋める
			VERTEX_2D *pVtx;
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			pUI -> pD3DVtxBuff -> Lock(0,0,(void**)&pVtx,0);
			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(pUI -> vPos.x - pUI -> vScl.x / 2, pUI -> vPos.y - pUI -> vScl.y / 2, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(pUI -> vPos.x + pUI -> vScl.x / 2, pUI -> vPos.y - pUI -> vScl.y / 2, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(pUI -> vPos.x - pUI -> vScl.x / 2, pUI -> vPos.y + pUI -> vScl.y / 2, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(pUI -> vPos.x + pUI -> vScl.x / 2, pUI -> vPos.y + pUI -> vScl.y / 2, 0.0f);
			// rhwの設定
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;
			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
			// テクスチャ座標指定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(pUI -> vTexPatSize.x, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, pUI -> vTexPatSize.y);
			pVtx[3].tex = D3DXVECTOR2(pUI -> vTexPatSize.x, pUI -> vTexPatSize.y);
		
			// 頂点データをアンロックする
			pUI -> pD3DVtxBuff -> Unlock();
		}
	}
}


/*******************************************************************************
* 3D空間内のUIの頂点情報作成
*******************************************************************************/
HRESULT MakeVertexUI3D(LPDIRECT3DDEVICE9 pDevice, UI_3D *pUI, int nMaxNum)
{
	for(int nNumUI = 0 ; nNumUI < nMaxNum ; nNumUI++, pUI++)
	{
		// オブジェクトの頂点バッファを作成(処理遅いけど一個ずつ作る　クラス化したときになんとかする)
		if(FAILED(pDevice -> CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,
												D3DUSAGE_WRITEONLY,
												FVF_VERTEX_3D,
												D3DPOOL_MANAGED,
												&pUI -> pD3DVtxBuff,
												NULL)))
		{
			return E_FAIL;
		}

		{//頂点バッファの中身を埋める
			VERTEX_3D *pVtx;

			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			pUI -> pD3DVtxBuff -> Lock(0,0,(void**)&pVtx,0);
			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(pUI -> vPos.x - pUI -> vScl.x / 2, pUI -> vPos.y - pUI -> vScl.y / 2, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(pUI -> vPos.x + pUI -> vScl.x / 2, pUI -> vPos.y - pUI -> vScl.y / 2, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(pUI -> vPos.x - pUI -> vScl.x / 2, pUI -> vPos.y + pUI -> vScl.y / 2, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(pUI -> vPos.x + pUI -> vScl.x / 2, pUI -> vPos.y + pUI -> vScl.y / 2, 0.0f);
			// 法線の設定
			pVtx[0].nor	= D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[1].nor	= D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[2].nor	= D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[3].nor	= D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			// 頂点カラーの設定
			pVtx[0].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			// テクスチャ座標指定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(pUI -> vTexPatSize.x, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, pUI -> vTexPatSize.y);
			pVtx[3].tex = D3DXVECTOR2(pUI -> vTexPatSize.x, pUI -> vTexPatSize.y);

			// 頂点データをアンロックする
			pUI -> pD3DVtxBuff -> Unlock();
		}
	}
	return S_OK;
}

/*******************************************************************************
* オプションの位置とサイズを再計算する
*******************************************************************************/
void RecalculationOption(void)
{
	SCREEN Screen = GetScreenInfo();

	// オプションウィンドウの初期化
#if 1
	g_Option[OPTION_WINDOW].vScl = D3DXVECTOR3(Screen.nWidth / 16 * 6,Screen.nHeight / 9 * 6,0.0f);
	g_Option[OPTION_WINDOW].vPos = D3DXVECTOR3(Screen.nWidth / 2.0f,Screen.nHeight / 2,0.0f);
#else
	g_Option[OPTION_WINDOW].vScl = D3DXVECTOR3(SCREEN_WIDTH / 16 * 6,SCREEN_HEIGHT / 9 * 6,0.0f);
	g_Option[OPTION_WINDOW].vPos = D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f);
#endif
	// BGMミキサーバーの初期化
	g_Option[BGM_MIXERBAR].vScl = D3DXVECTOR3(g_Option[OPTION_WINDOW].vScl.x,g_Option[OPTION_WINDOW].vPos.y / 3,0.0f);
	g_Option[BGM_MIXERBAR].vPos = D3DXVECTOR3(g_Option[OPTION_WINDOW].vPos.x,g_Option[OPTION_WINDOW].vPos.y - (g_Option[OPTION_WINDOW].vScl.y / 4),0.0f);
	// SEミキサーバーの初期化
	g_Option[SE_MIXERBAR].vScl = D3DXVECTOR3(g_Option[BGM_MIXERBAR].vScl.x,g_Option[BGM_MIXERBAR].vScl.y,0.0f);
	g_Option[SE_MIXERBAR].vPos = D3DXVECTOR3(g_Option[OPTION_WINDOW].vPos.x,g_Option[OPTION_WINDOW].vPos.y + (g_Option[OPTION_WINDOW].vScl.y / 10),0.0f);
	// 「メニューバーを表示する」の文字の初期化
	g_Option[MENUBAR_INDICATE].vScl = D3DXVECTOR3(g_Option[OPTION_WINDOW].vScl.x / 3 * 2,g_Option[OPTION_WINDOW].vScl.y / 4,0.0f);
	g_Option[MENUBAR_INDICATE].vPos = D3DXVECTOR3(g_Option[OPTION_WINDOW].vPos.x - (g_Option[OPTION_WINDOW].vScl.x / 7),g_Option[OPTION_WINDOW].vPos.y + (g_Option[OPTION_WINDOW].vScl.y / 3),0.0f);
	// チェックボックスの初期化
	g_Option[CHECKBOX].vScl = D3DXVECTOR3(g_Option[OPTION_WINDOW].vScl.x / 10,g_Option[OPTION_WINDOW].vScl.y / 10,0.0f);
	g_Option[CHECKBOX].vPos = D3DXVECTOR3(g_Option[OPTION_WINDOW].vPos.x + (g_Option[OPTION_WINDOW].vScl.x / 3),g_Option[OPTION_WINDOW].vPos.y + (g_Option[OPTION_WINDOW].vScl.y / 6 * 2),0.0f);
	// 閉じるボタンの初期化
	g_Option[OPTION_WINDOW_CLOSEBUTTON].vScl = D3DXVECTOR3(g_Option[OPTION_WINDOW].vScl.x / 10,g_Option[OPTION_WINDOW].vScl.y / 10,0.0f);
	g_Option[OPTION_WINDOW_CLOSEBUTTON].vPos = D3DXVECTOR3((g_Option[OPTION_WINDOW].vPos.x + (g_Option[OPTION_WINDOW].vScl.x / 2)) - (g_Option[OPTION_WINDOW_CLOSEBUTTON].vScl.x / 2),
															(g_Option[OPTION_WINDOW].vPos.y - (g_Option[OPTION_WINDOW].vScl.y / 2)) + (g_Option[OPTION_WINDOW_CLOSEBUTTON].vScl.y / 2)
															,0.0f);
	// BGMミキサーバーのアイコンの初期化
	g_Option[BGM_MIXERBAR_ICON].vScl = D3DXVECTOR3(g_Option[OPTION_WINDOW].vScl.x / 10,g_Option[OPTION_WINDOW].vScl.y / 10,0.0f);
	g_Option[BGM_MIXERBAR_ICON].vPos = D3DXVECTOR3(g_Option[OPTION_WINDOW].vPos.x,g_Option[OPTION_WINDOW].vPos.y - (g_Option[OPTION_WINDOW].vScl.y / 4),0.0f);
	// SEミキサーバーのアイコンの初期化
	g_Option[SE_MIXERBAR_ICON].vScl = D3DXVECTOR3(g_Option[OPTION_WINDOW].vScl.x / 10,g_Option[OPTION_WINDOW].vScl.y / 10,0.0f);
	g_Option[SE_MIXERBAR_ICON].vPos = D3DXVECTOR3(g_Option[OPTION_WINDOW].vPos.x,g_Option[OPTION_WINDOW].vPos.y + (g_Option[OPTION_WINDOW].vScl.y / 10),0.0f);


	for(int nCnt = 0;nCnt < MAX_OPTION;nCnt ++)
	{
		g_Option[nCnt].vTexPatSize = D3DXVECTOR2(1.0f,1.0f);
	}
	// 頂点座標の変更
	//SetVertexUI2D(&g_Option[0],MAX_OPTION);

	PrintDebugProc("オプションウィンドウのSizeX=%f\n",g_Option[OPTION_WINDOW].vScl.x);
	PrintDebugProc("オプションウィンドウのSizeY=%f\n",g_Option[OPTION_WINDOW].vScl.y);
	PrintDebugProc("オプションウィンドウのPosX=%f\n",g_Option[OPTION_WINDOW].vPos.x);
	PrintDebugProc("オプションウィンドウのPosY=%f\n",g_Option[OPTION_WINDOW].vPos.y);
}