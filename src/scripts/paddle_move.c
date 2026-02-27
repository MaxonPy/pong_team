#include <stdio.h>
#include "functions.h"

#define HEIGHT 25
#define PADDLE_HEIGHT 3

int move_paddle1_up(int paddle1_y)
{
    int new_paddle1_y;
    
    new_paddle1_y = paddle1_y;
    if (paddle1_y > 1)
    {
        new_paddle1_y = paddle1_y - 1;
    }
    return new_paddle1_y;
}

int move_paddle1_down(int paddle1_y)
{
    int new_paddle1_y;
    
    new_paddle1_y = paddle1_y;
    if (paddle1_y < HEIGHT - PADDLE_HEIGHT - 1)
    {
        new_paddle1_y = paddle1_y + 1;
    }
    return new_paddle1_y;
}

int move_paddle2_up(int paddle2_y)
{
    int new_paddle2_y;
    
    new_paddle2_y = paddle2_y;
    if (paddle2_y > 1)
    {
        new_paddle2_y = paddle2_y - 1;
    }
    return new_paddle2_y;
}

int move_paddle2_down(int paddle2_y)
{
    int new_paddle2_y;
    
    new_paddle2_y = paddle2_y;
    if (paddle2_y < HEIGHT - PADDLE_HEIGHT - 1)
    {
        new_paddle2_y = paddle2_y + 1;
    }
    return new_paddle2_y;
}