// �b����@�@�R���\�[���Q�[��
// ���t�@�@�@2018/07/31
// ����ҁ@�@�Ԗ�M�l
// �^�C�g���@�n�[�h����

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

void PlayerMove(void);         //Player�̈ړ�����
void EnemyMove(void);          //Enemy�̈ړ�����
void Judgment(void);           //���s����
void RenderPlay(void);         //�v���C���̕`�揈��
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
	printf("                                                                                                      �����@�@�@  �@ \n");
	printf("  �@�@�@�����@�@�@�����@�@�@�@�@�@�@�@�@�@�@�@�@�@�����@ ���@���@�@�@ �����@�@�����@�@�@�@�@�@�@  ������������  �@�@ \n");
	printf("  �@�@�@�����@�@�@�����@�@�@�@�@�@�@�@�@�@�@�@�@�@�����@�@���@���@�@�@�����@�@�����@�@�@�@�@�@�@�@�������������@�@�@ \n");
	printf("  �@�@�@�����@�@�@�����@�@�@�@�@�@�@�@�@�@�@�@�@�@�����@�@�@�@�@�@�@�@�����@�@�����@�@�@�@�@�@�@�@�@�@�����@�@�@�@�@ \n");
	printf("  �@�@�@�����@�@�@�����@�@ ���������������������@ �����@�@�@�@�@�@�@�@�����@�@�����@�@�@�@�@�@�@�����������������@   \n");
	printf("  �@�@ �����@�@�@�@�����@�@���������������������@ ���������@�@�@�@�@�@�����@�@�����@�@�@���@�@�@�����������������@   \n");
	printf("  �@�@ �����@�@�@�@�����@�@���������������������@ �������������@�@�@ �����@�@ �����@�@�@���@�@�@�@�@�@�����@�@�@�@�@ \n");
	printf("  �@�@�����@ �@�@�@ �����@�@�@�@�@�@�@�@�@�@�@�@�@�����@�@�������@�@ �����@�@ �����@�@�����@�@�����@  ���������@  �@ \n");
	printf("  �@�@�����@�@  �@�@�����@�@�@�@�@�@�@�@�@�@�@�@�@�����@�@  �����@�@�����@�@�@�����@�����@�@�@����    ���������@�@�@ \n");
	printf("  �@ �����@�@�@�@    �����@�@�@�@�@�@�@�@�@�@�@�@ �����@�@�@�@�@�@�@���@�@�@�@���������@�@�@�@�������������@�@�@�@   \n");
	printf("  �@�����@�@�@�@        ���@�@�@�@�@�@�@�@�@�@�@�@�����@�@�@�@�@�@ �� �@�@�@�@�������@�@�@�@ ����  ������������������\n");
	printf("                                                                  ��          ����          ����      �������������� \n");
	printf("                                                 �@�@										                  \n\n");
	printf("          �@�@                                     �@�@�@ �@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@\n\n");
	SetTextColor(COLOR_WHITE);
	printf("                                             �` �X�y�[�X�L�[�ŃX�^�[�g �`�@�@�@�@ �@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@ \n");

	g_player_state = 0;
	//hurdle�̒��S���W
	hurdle.pos_x = 110;
	//hurdle�̉����W
	hurdle.pos_y = 29;

	//�O���|�o���ϐ��̏�����
	g_jump_count = 0;
	g_jump_state = 0;
	g_play_time  = 0;
	g_hit_state  = 0;
	g_speed_up   = 0;
	g_score      = 0;

	//�V�[���J��
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
	printf("                                                                   �X�R�A�@�F�@%d\n", g_score);
	printf("\n");
	printf("\n");
	printf("                                                              �` �G���^�[�L�[�Ń^�C�g���� �`\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("                                     ������         \n");
	printf("                                    ��������        \n");
	printf("                                    ��������      ��\n");
	printf("                                     ������       ��\n");
	printf("                                       ����       ��\n");
	printf("                                ������������������  \n");
	printf("                            ����     ������         \n");
	printf("                           ��       ������          \n");
	printf("                         ��       ������      ��    \n");
	printf("                              �@������      ��      \n");
	printf("                             �@������       ��      \n");
	printf("                             ������������  ��       \n");
	printf("                            ����      ��������      \n");
	printf("                           ����          ����       \n");
	printf("                          ����         ����         \n");
	printf("                         ��        ����  ��         \n");
	printf("                        ��         ��   ��          \n");
	printf("                       ��           ��  ��          \n");
	printf("                      ����    ������   ��           \n");
	printf("                       ������     ������            \n");
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
	//player�̒��S���W
	player.pos_x = 35;//+-7
	//player�̉����W
	player.pos_y = 29;//sita
	
	//���Ԍo�߂ŉ���
	
	if (g_play_time > 70 && g_speed_up <= 14)
	{
		g_speed_up++;
		g_play_time = 0;
	}

	if (g_jump_state == 1)
	{
		g_jump_count++;
		//player�̒��S���W
		player.pos_x = 35;//+-7
		//player�̉����W
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
			//jump����
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
	printf("                                      ������             \n");
	printf("                                     ��������            \n");
	printf("                                     ��������            \n");
	printf("                                      ������             \n");
	printf("                                      ����         ��    \n");
	printf("                                 ������������     ��     \n");
	printf("                             ����   ������   ������      \n");
	printf("                           ��      ������                \n");
	printf("                          ��      ������                 \n");
	printf("                         ��      ������                  \n");
	printf("                                ������                   \n");
	printf("                               ������                  ��\n");
	printf("                           ������������������         �� \n");
	printf("                  ��������������   ��������������������  \n");
	printf("                  ��                                     \n");
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
	printf("                                    ������         \n");
	printf("                                   ��������        \n");
	printf("                                   ��������      ��\n");
	printf("                                    ������       ��\n");
	printf("                                    ����       ��  \n");
	printf("                             ������������������    \n");
	printf("                         ����     ������           \n");
	printf("                        ��       ������            \n");
	printf("                       ��       ������             \n");
	printf("                               ������              \n");
	printf("                              ������               \n");
	printf("                             ������������          \n");
	printf("                            ����      ������       \n");
	printf("                           ����          ����      \n");
	printf("                          ����         ����        \n");
	printf("                         ��        ����            \n");
	printf("                        ��         ��              \n");
	printf("                       ��           ��             \n");
	printf("                      ����                         \n");
	printf("                       ������                      \n");
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
	printf("                                    ������         \n");
	printf("                                   ��������        \n");
	printf("                                   ��������        \n");
	printf("                                    ������         \n");
	printf("                                    ����         ��\n");
	printf("                               ������������     �� \n");
	printf("                           ����   ������   ������  \n");
	printf("                         ��      ������            \n");
	printf("                        ��      ������             \n");
	printf("                       ��      ������              \n");
	printf("                              ������               \n");
	printf("                             ������                \n");
	printf("                             ������                \n");
	printf("                ������     ����  ����              \n");
	printf("                ��    ��������    ����             \n");
	printf("                ��      ����        ����           \n");
	printf("                                      ��           \n");
	printf("                                       ��          \n");
	printf("                                        ��         \n");
	printf("                                        ������     \n");
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
	printf("                                   ������ \n");
	printf("                                  ��������\n");
	printf("                                  ��������\n");
	printf("                                   ������ \n");
	printf("                                   ����   \n");
	printf("                                 ������   \n");
	printf("                                ������    \n");
	printf("                               ������     \n");
	printf("                              ������    ��\n");
	printf("                              ������������\n");
	printf("                             ������   ����\n");
	printf("                             ������       \n");
	printf("                             ������       \n");
	printf("                                ����      \n");
	printf("                                 ����     \n");
	printf("                           ������������   \n");
	printf("                           ��      ����   \n");
	printf("                           ��       ��    \n");
	printf("                                   ��     \n");
	printf("                                  ������  \n");
}

void hurdle1()
{
	SetTextColor(COLOR_WHITE);
	SetCursorPosition(hurdle.pos_x, 18);
	printf("      ��\n");
	SetCursorPosition(hurdle.pos_x, 19);
	printf("      ��\n");
	SetCursorPosition(hurdle.pos_x, 20);
	printf("      ��\n");
	SetCursorPosition(hurdle.pos_x, 21);
	printf("      ��\n");
	SetCursorPosition(hurdle.pos_x, 22);
	printf("      ��\n");
	SetCursorPosition(hurdle.pos_x, 23);
	printf("      ��\n");
	SetCursorPosition(hurdle.pos_x, 24);
	printf("      ��\n");
	SetCursorPosition(hurdle.pos_x, 25);
	printf("      ��\n");
	SetCursorPosition(hurdle.pos_x, 26);
	printf("      ��\n");
	SetCursorPosition(hurdle.pos_x, 27);
	printf("      ��\n");
	SetCursorPosition(hurdle.pos_x, 28);
	printf("      ��\n");
	SetCursorPosition(hurdle.pos_x, 29);
	printf("��������\n");
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
	printf("                                     ������         \n");
	printf("                                    ��������        \n");
	printf("                                    ��������      ��\n");
	printf("                                     ������       ��\n");
	printf("                                       ����       ��\n");
	printf("                                ������������������  \n");
	printf("                            ����     ������         \n");
	printf("                           ��       ������          \n");
	printf("                         ��       ������      ��    \n");
	printf("                              �@������      ��      \n");
	printf("                             �@������       ��      \n");
	printf("                             ������������  ��       \n");
	printf("                            ����      ��������      \n");
	printf("                           ����          ����       \n");
	printf("                          ����         ����         \n");
	printf("                         ��        ����  ��         \n");
	printf("                        ��         ��   ��          \n");
	printf("                       ��           ��  ��          \n");
	printf("                      ����    ������   ��           \n");
	printf("                       ������     ������            \n");
	printf("                                                    \n");
}

//=====================================================================
//! @brief �w�肳�ꂽ���ԕ������ҋ@
//!
//! @param[in] waitTime - �ҋ@����[�~���b]
//!
//! @return �Ȃ�
//=======================================================================
void Wait(clock_t waitTime)
{
	// �ҋ@���Ԃ��^�C�}�[���݂̒P�ʂɕϊ�
	clock_t waitClocks = waitTime * CLOCKS_PER_SEC / 1000;
	// �v���J�n���Ԃ̎擾
	clock_t start = clock();
	// �w�肳�ꂽ���Ԃ܂őҋ@������
	while (clock() - start < waitClocks);
}