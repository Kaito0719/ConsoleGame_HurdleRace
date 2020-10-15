// Ｃ言語　　コンソールゲーム
// 日付　　　2018/07/31
// 製作者　　間野凱斗
// タイトル　ハードル走

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Console.h"
#include <string.h>
#include <conio.h>
#include <Windows.h>

#define BULLETNUM 4

enum
{
	GAMETITLE,
	GAMEPLAY,
	GAMEOVER
};

typedef struct tag_object {
	int pos_x;
	int pos_y;
	int speed;
	int spd_x;
	int spd_y;
	int state;
	int move;
	int count;
}OBJECT;

OBJECT player;
OBJECT hurdle;
int g_keyCode;
int g_keyCodeList[] = { KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_ENTER, KEY_SPACE };
int g_scene;
int g_game_main = 1;
int g_start_cnt;
int g_play_time;
int g_run_count = 1;
int g_player_state;
int g_hit_state;
int g_jump_count;
int g_jump_state;
int g_speed_up;
int g_score;

void GameTitle();
void GamePlay();
void GameOver();

void PlayerMove(void);         //Playerの移動処理
void EnemyMove(void);          //Enemyの移動処理
void Judgment(void);           //勝敗判定
void RenderPlay(void);         //プレイ中の描画処理
void Wait(clock_t waitTime);
void run1();
void run2();
void run3();
void jump();
void hurdle1();
void miss();

int main(void)
{
	g_scene = GAMETITLE;
	while (1)
	{
		switch (g_scene)
		{
		case GAMETITLE:
			GameTitle();
			break;
		case GAMEPLAY:
			GamePlay();
			break;
		case GAMEOVER:
			GameOver();
			break;
		}
	}
}



void GameTitle(void)
{
	ClearScreen();
	printf("\n\n");
	SetTextColor(COLOR_GREEN);
	printf("                                                                                                      ■■　　　  　 \n");
	printf("  　　　■■　　　■■　　　　　　　　　　　　　　■■　 ■　■　　　 ■■　　■■　　　　　　　  ■■■■■■  　　 \n");
	printf("  　　　■■　　　■■　　　　　　　　　　　　　　■■　　■　■　　　■■　　■■　　　　　　　　■■■■■■　　　 \n");
	printf("  　　　■■　　　■■　　　　　　　　　　　　　　■■　　　　　　　　■■　　■■　　　　　　　　　　■■　　　　　 \n");
	printf("  　　　■■　　　■■　　 ■■■■■■■■■■　 ■■　　　　　　　　■■　　■■　　　　　　　■■■■■■■■　   \n");
	printf("  　　 ■■　　　　■■　　■■■■■■■■■■　 ■■■■　　　　　　■■　　■■　　　■　　　■■■■■■■■　   \n");
	printf("  　　 ■■　　　　■■　　■■■■■■■■■■　 ■■■■■■　　　 ■■　　 ■■　　　■　　　　　　■■　　　　　 \n");
	printf("  　　■■　 　　　 ■■　　　　　　　　　　　　　■■　　■■■　　 ■■　　 ■■　　■■　　■■　  ■■■■　  　 \n");
	printf("  　　■■　　  　　■■　　　　　　　　　　　　　■■　　  ■■　　■■　　　■■　■■　　　■■    ■■■■　　　 \n");
	printf("  　 ■■　　　　    ■■　　　　　　　　　　　　 ■■　　　　　　　■　　　　■■■■　　　　■■■■■■　　　　   \n");
	printf("  　■■　　　　        ■　　　　　　　　　　　　■■　　　　　　 ■ 　　　　■■■　　　　 ■■  ■■■■■■■■■\n");
	printf("                                                                  ■          ■■          ■■      ■■■■■■■ \n");
	printf("                                                 　　										                  \n\n");
	printf("          　　                                     　　　 　　　　　　　　　　　　　　　　　　　　\n\n");
	SetTextColor(COLOR_WHITE);
	printf("                                             ～ スペースキーでスタート ～　　　　 　　　　　　　　　　　　　　　　　　 \n");

	g_player_state = 0;
	//hurdleの中心座標
	hurdle.pos_x = 110;
	//hurdleの下座標
	hurdle.pos_y = 29;

	//グロ－バル変数の初期化
	g_jump_count = 0;
	g_jump_state = 0;
	g_play_time  = 0;
	g_hit_state  = 0;
	g_speed_up   = 0;
	g_score      = 0;

	//シーン遷移
	g_keyCode = WaitKey();
	switch (g_keyCode)
	{
	case KEY_SPACE:
		g_scene = GAMEPLAY;
		break;
	}
}

void GamePlay(void)
{   
		g_play_time++;
		g_score++;
		PlayerMove();
		EnemyMove();
		Judgment();
		RenderPlay();

		if (g_hit_state == 1)
		{
			g_scene = GAMEOVER;
		}
}

void GameOver(void)
{
	ClearScreen;
	SetTextColor(COLOR_RED);
	printf("\n");
	printf("\n");
	printf("                                                                   スコア　：　%d\n", g_score);
	printf("\n");
	printf("\n");
	printf("                                                              ～ エンターキーでタイトルへ ～\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("                                     ■■■         \n");
	printf("                                    ■■■■        \n");
	printf("                                    ■■■■      ■\n");
	printf("                                     ■■■       ■\n");
	printf("                                       ■■       ■\n");
	printf("                                ■■■■■■■■■  \n");
	printf("                            ■■     ■■■         \n");
	printf("                           ■       ■■■          \n");
	printf("                         ■       ■■■      ■    \n");
	printf("                              　■■■      ■      \n");
	printf("                             　■■■       ■      \n");
	printf("                             ■■■■■■  ■       \n");
	printf("                            ■■      ■■■■      \n");
	printf("                           ■■          ■■       \n");
	printf("                          ■■         ■■         \n");
	printf("                         ■        ■■  ■         \n");
	printf("                        ■         ■   ■          \n");
	printf("                       ■           ■  ■          \n");
	printf("                      ■■    ■■■   ■           \n");
	printf("                       ■■■     ■■■            \n");
	g_keyCode = WaitKey();
	switch (g_keyCode)
	{
	case KEY_ENTER:
		g_scene = GAMETITLE;
		break;
	}
}

void PlayerMove(void)
{
	//playerの中心座標
	player.pos_x = 35;//+-7
	//playerの下座標
	player.pos_y = 29;//sita
	
	//時間経過で加速
	
	if (g_play_time > 70 && g_speed_up <= 14)
	{
		g_speed_up++;
		g_play_time = 0;
	}

	if (g_jump_state == 1)
	{
		g_jump_count++;
		//playerの中心座標
		player.pos_x = 35;//+-7
		//playerの下座標
		player.pos_y = 10;
		if ((g_jump_count + g_speed_up) >= 15)
		{
			g_jump_state = 0;
			g_jump_count = 0;
		}
	}
	else
	{
		switch (g_player_state)
		{
		case 0:
			g_player_state = 1;
			break;
		case 1:
			g_player_state = 2;
			break;
		case 2:
			g_player_state = 3;
		}
		int g_key_code = GetKeyInput();
		if ((g_key_code & KEY_SPACE) != 0)
		{
			//jump処理
			g_jump_count++;
			g_jump_state = 1;
		}
	}
}
void EnemyMove(void)
{
	if (hurdle.pos_x >= 0)
		hurdle.pos_x -= 2 + g_speed_up;

	if (hurdle.pos_x <= 0)
	{
		hurdle.pos_x = 110;
	}
}
void Judgment(void)
{
	int p_l = player.pos_x - 10;
	int p_r = player.pos_x + 7;
	int p_b = player.pos_y;

	int h_l = hurdle.pos_x;
	int h_r = hurdle.pos_x + 8;
	int h_t = hurdle.pos_y - 12;
	

	if (p_l < h_r && p_r > h_l && p_b > h_t)
	{
		g_hit_state = 1;
	}
}
void RenderPlay(void)
{
	ClearScreen();
	int i;
	if (g_hit_state != 1)
	{
		if (g_jump_state == 1)
		{
			jump();
		}
		else
		{
			switch (g_player_state)
			{
			case 1:
				run1();
				g_run_count++;
				break;
			case 2:
				run2();
				g_run_count++;
				break;
			case 3:
				run3();
				g_run_count++;
				g_player_state = 0;
				break;
			}
		}
		hurdle1();
		for (i = 0; i < 30000000; i++);
	}

}

void jump()
{
	SetTextColor(COLOR_WHITE);
	printf("\n");
	printf("                                      ■■■             \n");
	printf("                                     ■■■■            \n");
	printf("                                     ■■■■            \n");
	printf("                                      ■■■             \n");
	printf("                                      ■■         ■    \n");
	printf("                                 ■■■■■■     ■     \n");
	printf("                             ■■   ■■■   ■■■      \n");
	printf("                           ■      ■■■                \n");
	printf("                          ■      ■■■                 \n");
	printf("                         ■      ■■■                  \n");
	printf("                                ■■■                   \n");
	printf("                               ■■■                  ■\n");
	printf("                           ■■■■■■■■■         ■ \n");
	printf("                  ■■■■■■■   ■■■■■■■■■■  \n");
	printf("                  ■                                     \n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
}

void run1()
{
	SetTextColor(COLOR_WHITE);
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("                                    ■■■         \n");
	printf("                                   ■■■■        \n");
	printf("                                   ■■■■      ■\n");
	printf("                                    ■■■       ■\n");
	printf("                                    ■■       ■  \n");
	printf("                             ■■■■■■■■■    \n");
	printf("                         ■■     ■■■           \n");
	printf("                        ■       ■■■            \n");
	printf("                       ■       ■■■             \n");
	printf("                               ■■■              \n");
	printf("                              ■■■               \n");
	printf("                             ■■■■■■          \n");
	printf("                            ■■      ■■■       \n");
	printf("                           ■■          ■■      \n");
	printf("                          ■■         ■■        \n");
	printf("                         ■        ■■            \n");
	printf("                        ■         ■              \n");
	printf("                       ■           ■             \n");
	printf("                      ■■                         \n");
	printf("                       ■■■                      \n");
	printf("                                                   \n");
}

void run2()
{
	SetTextColor(COLOR_WHITE);
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("                                                   \n");
	printf("                                    ■■■         \n");
	printf("                                   ■■■■        \n");
	printf("                                   ■■■■        \n");
	printf("                                    ■■■         \n");
	printf("                                    ■■         ■\n");
	printf("                               ■■■■■■     ■ \n");
	printf("                           ■■   ■■■   ■■■  \n");
	printf("                         ■      ■■■            \n");
	printf("                        ■      ■■■             \n");
	printf("                       ■      ■■■              \n");
	printf("                              ■■■               \n");
	printf("                             ■■■                \n");
	printf("                             ■■■                \n");
	printf("                ■■■     ■■  ■■              \n");
	printf("                ■    ■■■■    ■■             \n");
	printf("                ■      ■■        ■■           \n");
	printf("                                      ■           \n");
	printf("                                       ■          \n");
	printf("                                        ■         \n");
	printf("                                        ■■■     \n");
}

void run3()
{
	SetTextColor(COLOR_WHITE);
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("                                          \n");
	printf("                                   ■■■ \n");
	printf("                                  ■■■■\n");
	printf("                                  ■■■■\n");
	printf("                                   ■■■ \n");
	printf("                                   ■■   \n");
	printf("                                 ■■■   \n");
	printf("                                ■■■    \n");
	printf("                               ■■■     \n");
	printf("                              ■■■    ■\n");
	printf("                              ■■■■■■\n");
	printf("                             ■■■   ■■\n");
	printf("                             ■■■       \n");
	printf("                             ■■■       \n");
	printf("                                ■■      \n");
	printf("                                 ■■     \n");
	printf("                           ■■■■■■   \n");
	printf("                           ■      ■■   \n");
	printf("                           ■       ■    \n");
	printf("                                   ■     \n");
	printf("                                  ■■■  \n");
}

void hurdle1()
{
	SetTextColor(COLOR_WHITE);
	SetCursorPosition(hurdle.pos_x, 18);
	printf("      ■\n");
	SetCursorPosition(hurdle.pos_x, 19);
	printf("      ■\n");
	SetCursorPosition(hurdle.pos_x, 20);
	printf("      ■\n");
	SetCursorPosition(hurdle.pos_x, 21);
	printf("      ■\n");
	SetCursorPosition(hurdle.pos_x, 22);
	printf("      ■\n");
	SetCursorPosition(hurdle.pos_x, 23);
	printf("      ■\n");
	SetCursorPosition(hurdle.pos_x, 24);
	printf("      ■\n");
	SetCursorPosition(hurdle.pos_x, 25);
	printf("      ■\n");
	SetCursorPosition(hurdle.pos_x, 26);
	printf("      ■\n");
	SetCursorPosition(hurdle.pos_x, 27);
	printf("      ■\n");
	SetCursorPosition(hurdle.pos_x, 28);
	printf("      ■\n");
	SetCursorPosition(hurdle.pos_x, 29);
	printf("■■■■\n");
}

void miss()
{
	SetTextColor(COLOR_WHITE);
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("                                     ■■■         \n");
	printf("                                    ■■■■        \n");
	printf("                                    ■■■■      ■\n");
	printf("                                     ■■■       ■\n");
	printf("                                       ■■       ■\n");
	printf("                                ■■■■■■■■■  \n");
	printf("                            ■■     ■■■         \n");
	printf("                           ■       ■■■          \n");
	printf("                         ■       ■■■      ■    \n");
	printf("                              　■■■      ■      \n");
	printf("                             　■■■       ■      \n");
	printf("                             ■■■■■■  ■       \n");
	printf("                            ■■      ■■■■      \n");
	printf("                           ■■          ■■       \n");
	printf("                          ■■         ■■         \n");
	printf("                         ■        ■■  ■         \n");
	printf("                        ■         ■   ■          \n");
	printf("                       ■           ■  ■          \n");
	printf("                      ■■    ■■■   ■           \n");
	printf("                       ■■■     ■■■            \n");
	printf("                                                    \n");
}

//=====================================================================
//! @brief 指定された時間分だけ待機
//!
//! @param[in] waitTime - 待機時間[ミリ秒]
//!
//! @return なし
//=======================================================================
void Wait(clock_t waitTime)
{
	// 待機時間をタイマー刻みの単位に変換
	clock_t waitClocks = waitTime * CLOCKS_PER_SEC / 1000;
	// 計測開始時間の取得
	clock_t start = clock();
	// 指定された時間まで待機させる
	while (clock() - start < waitClocks);
}