#include <stdio.h>
#include "functions.h"

#define LEFT_WALL 0
#define RIGHT_WALL 79
#define TOP_WALL 0
#define WIN_SCORE 21

void clear_screen(void)
{
    printf("\033[2J\033[H");
}

 // Функция проверки окончания игры
int check_game_over(int score1, int score2)
{
    if (score1 >= WIN_SCORE || score2 >= WIN_SCORE)
    {
        return 1;
    }
    return 0;
}

// Функция отображения победителя
void show_winner(int score1, int score2)
{
    int i;
    
    clear_screen();
    
    // Очистка экрана пустыми строками для центрирования
    for (i = 0; i < 10; i++)
    {
        printf("\n");
    }
    
    if (score1 >= WIN_SCORE)
    {
        printf("****************************************\n");
        printf("*                                      *\n");
        printf("*         PLAYER 1 WINS!               *\n");
        printf("*                                      *\n");
        printf("****************************************\n");
    }
    else if (score2 >= WIN_SCORE)
    {
        printf("****************************************\n");
        printf("*                                      *\n");
        printf("*         PLAYER 2 WINS!               *\n");
        printf("*                                      *\n");
        printf("****************************************\n");
    }
    else
    {
        printf("****************************************\n");
        printf("*                                      *\n");
        printf("*         GAME OVER                    *\n");
        printf("*                                      *\n");
        printf("****************************************\n");
    }
    printf("\n\nFinal Score: %d - %d\n", score1, score2);
}

// Функция проверки гола и обновления счета
int check_goal_left(int ball_x, int score2)
{
    int new_score;
    
    new_score = score2;
    
    if (ball_x <= LEFT_WALL + 1)
    {
        new_score = score2 + 1;
    }
    
    return new_score;
}

int check_goal_right(int ball_x, int score1)
{
    int new_score;
    
    new_score = score1;
    
    if (ball_x >= RIGHT_WALL - 1)
    {
        new_score = score1 + 1;
    }
    
    return new_score;
}