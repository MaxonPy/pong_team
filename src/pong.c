#include <stdio.h>

#define WIDTH 80 // ширина
#define HEIGHT 25 // высота
#define LEFT_WALL 0 // левая стена координата
#define RIGHT_WALL 79 // правая стена координата 
#define TOP_WALL 0 // координата верхней стены
#define BOTTOM_WALL 24 // координата нижней стены т.к двигаемся с левого верхнего угла
#define PADDLE_HEIGHT 3 // высота ракетки
#define WIN_SCORE 21 // количестов очков для победы 

#define HOR '-'
#define VER '|'
#define BALL '*'

// функция очистки экрана РАЗОБРАТЬ!!! 
void clear_screen(void)
{
    printf("\033[2J\033[H");
}

// Функция проверки столкновения мяча с ракеткой
int check_paddle_collision(int paddle_y, int ball_x, int ball_y, int is_left_paddle)
{
    int paddle_x;
    int result;
    
    result = 0;
    
    if (is_left_paddle)
        paddle_x = 1;
    else
        paddle_x = 78;
    
    if (ball_x == paddle_x && 
        ball_y >= paddle_y && 
        ball_y < paddle_y + PADDLE_HEIGHT)
    {
        result = 1;
    }
    return result;
}

// Функция обновления позиции мяча
int update_ball_x(int ball_x, int ball_dx)
{
    return ball_x + ball_dx;
}

int update_ball_y(int ball_y, int ball_dy)
{
    return ball_y + ball_dy;
}

int update_ball_dx(int ball_x, int ball_dx, int paddle1_y, int paddle2_y, int ball_y)
{
    int new_dx;
    
    new_dx = ball_dx;
    
    // Проверка столкновения с левой ракеткой
    if (ball_x == 2 && check_paddle_collision(paddle1_y, ball_x - 1, ball_y, 1))
    {
        new_dx = 1;
    }
    // Проверка столкновения с правой ракеткой
    else if (ball_x == 77 && check_paddle_collision(paddle2_y, ball_x + 1, ball_y, 0))
    {
        new_dx = -1;
    }
    
    return new_dx;
}

int update_ball_dy(int ball_y, int ball_dy)
{
    int new_dy;
    
    new_dy = ball_dy;
    
    // Проверка столкновения с верхней и нижней стенками
    if (ball_y <= TOP_WALL + 1)
    {
        new_dy = 1;
    }
    else if (ball_y >= BOTTOM_WALL - 1)
    {
        new_dy = -1;
    }
    
    return new_dy;
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

// Функция сброса мяча после гола
int reset_ball_x(int ball_x, int score1, int score2, int game_over, int current_ball_x)
{
    int new_ball_x;
    
    new_ball_x = current_ball_x;
    
    if ((ball_x <= LEFT_WALL + 1 || ball_x >= RIGHT_WALL - 1) && game_over == 0)
    {
        if (score1 < WIN_SCORE && score2 < WIN_SCORE)
        {
            new_ball_x = 40;
        }
    }
    return new_ball_x;
}

int reset_ball_y(int ball_x, int score1, int score2, int game_over, int current_ball_y)
{
    int new_ball_y;
    
    new_ball_y = current_ball_y;
    
    if ((ball_x <= LEFT_WALL + 1 || ball_x >= RIGHT_WALL - 1) && game_over == 0)
    {
        if (score1 < WIN_SCORE && score2 < WIN_SCORE)
        {
            new_ball_y = 12;
        }
    }
    return new_ball_y;
}

int reset_ball_dx(int ball_x, int score1, int score2, int game_over, int current_ball_dx)
{
    int new_ball_dx;
    
    new_ball_dx = current_ball_dx;
    
    if (ball_x <= LEFT_WALL + 1 && game_over == 0)
    {
        if (score1 < WIN_SCORE && score2 < WIN_SCORE)
        {
            new_ball_dx = 1;
        }
    }
    else if (ball_x >= RIGHT_WALL - 1 && game_over == 0)
    {
        if (score1 < WIN_SCORE && score2 < WIN_SCORE)
        {
            new_ball_dx = -1;
        }
    }
    return new_ball_dx;
}

int reset_ball_dy(int ball_x, int score1, int score2, int game_over, int current_ball_dy)
{
    int new_ball_dy;
    
    new_ball_dy = current_ball_dy;
    
    if ((ball_x <= LEFT_WALL + 1 || ball_x >= RIGHT_WALL - 1) && game_over == 0)
    {
        if (score1 < WIN_SCORE && score2 < WIN_SCORE)
        {
            new_ball_dy = 1;
        }
    }
    return new_ball_dy;
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

// Функция отрисовки игрового поля
void draw_field(int paddle1_y, int paddle2_y, int ball_x, int ball_y, int score1, int score2)
{
    int row;
    int col;
    int is_paddle1;
    int is_paddle2;
    int is_ball;
    
    clear_screen();
    
    // Верхняя граница
    for (col = 0; col < WIDTH; col++) // от 0 пока col < 80
    {
        printf("%c", HOR);
    }
    printf("\n");
    
    // Основное поле
    for (row = 1; row < HEIGHT - 1; row++) // от 1 пока row < 24 не учитывая левую и правую границу
    {
        // сраpe отрисовываем вертикальную черту левой границы
        printf("%c", VER);
        
        for (col = 1; col < WIDTH - 1; col++) // от 1 пока col < 79
        {
            is_paddle1 = 0;
            is_paddle2 = 0;
            is_ball = 0;
            
            // Левая ракетка
            if (col == 1 && row >= paddle1_y && row < paddle1_y + PADDLE_HEIGHT)
            {
                is_paddle1 = 1;
            }
            // Правая ракетка
            else if (col == WIDTH - 2 && row >= paddle2_y && row < paddle2_y + PADDLE_HEIGHT)
            {
                is_paddle2 = 1;
            }
            // Мяч
            else if (col == ball_x && row == ball_y)
            {
                is_ball = 1;
            }
            if (is_paddle1 == 1 || is_paddle2 == 1)
            {
                printf("%c", VER);
            }
            else if (is_ball == 1)
            {
                printf("%c", BALL);
            }
            else
            {
                printf(" ");
            }
        }
        
        // Правая граница
        printf("%c\n", VER);
    }
    
    // Нижняя граница
    for (col = 0; col < WIDTH; col++)
    {
        printf("%c", HOR);
    }
    printf("\n");
    
    // Отображение счета
    printf("Player 1 (A/Z): %d\t\tPlayer 2 (K/M): %d\n", score1, score2);
    printf("Press SPACE to skip turn, 'q' to quit\n");
}

// функция двигает ракетки вверх
int move_paddle1_up(int paddle1_y)
{
    int new_paddle1_y;
    
    new_paddle1_y = paddle1_y;
    //  если ракетка не у верхней границы
    if (paddle1_y > 1)
    {
        // тк мы отсчитываем слева сверху 
        // если мы хотим поднять ракетку вверх - уменьшаем координату
        new_paddle1_y = paddle1_y - 1;
    }
    return new_paddle1_y;
}
// функция двигает ракетки вниз
int move_paddle1_down(int paddle1_y)
{
    int new_paddle1_y;
    
    new_paddle1_y = paddle1_y;
    // если Y ракетки < (высота поля - высота ракетки - 1)
    // мы считаем Y координату ракетки по ВЕРХНЕЙ точке самой ракетки
    if (paddle1_y < HEIGHT - PADDLE_HEIGHT - 1)
    {
        // прибавляем => 
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

int main(void)
{
    // инициализация переменных игры
    int paddle1_y;
    int paddle2_y;
    int ball_x;
    int ball_y;
    int ball_dx;
    int ball_dy;
    int score1;
    int score2;
    int game_over;
    
    char c;
    // сохранение пред изменений
    int temp_ball_x;
    int temp_ball_y;
    int temp_score1;
    int temp_score2;
    
    // нначальные значения
    paddle1_y = 11;
    paddle2_y = 11;
    ball_x = 40;
    ball_y = 12;
    ball_dx = 1;
    ball_dy = 1;
    score1 = 0;
    score2 = 0;
    game_over = 0;
    
    printf("PONG GAME - Two Player\n");
    printf("Controls:\n");
    printf("Player 1: A (up) / Z (down)\n");
    printf("Player 2: K (up) / M (down)\n");
    printf("SPACE - skip turn\n");
    printf("Press Enter to start...\n");
    
    // считываем 1 символ 
    c = getchar();
    
    // основной игровой цикл
    while (game_over == 0)
    {
        // Отрисовка поля
        draw_field(paddle1_y, paddle2_y, ball_x, ball_y, score1, score2);
        // Ожидание ввода
        c = getchar();
        // Обработка ввода без указателей
        if (c == 'a' || c == 'A')
        {
            paddle1_y = move_paddle1_up(paddle1_y);
        }
        else if (c == 'z' || c == 'Z')
        {
            paddle1_y = move_paddle1_down(paddle1_y);
        }
        else if (c == 'k' || c == 'K')
        {
            paddle2_y = move_paddle2_up(paddle2_y);
        }
        else if (c == 'm' || c == 'M')
        {
            paddle2_y = move_paddle2_down(paddle2_y);
        }
        else if (c == 'q' || c == 'Q')
        {
            game_over = 1;
        }
        // Пробел - просто пропуск хода
        
        // Обновление состояния мяча (только если игра не окончена)
        if (game_over == 0)
        {
            // Сохраняем текущие значения
            temp_ball_x = ball_x;
            temp_ball_y = ball_y;
            
            // Сначала проверяем голы и обновляем счет
            temp_score1 = check_goal_right(ball_x, score1);
            temp_score2 = check_goal_left(ball_x, score2);
            
            score1 = temp_score1;
            score2 = temp_score2;
            
            // Проверяем окончание игры
            game_over = check_game_over(score1, score2);
            
            // Обновляем направление мяча
            ball_dx = update_ball_dx(ball_x, ball_dx, paddle1_y, paddle2_y, ball_y);
            ball_dy = update_ball_dy(ball_y, ball_dy);
            
            // Обновляем позицию мяча
            if (game_over == 0)
            {
                ball_x = update_ball_x(ball_x, ball_dx);
                ball_y = update_ball_y(ball_y, ball_dy);
            }
            
            // Сбрасываем мяч после гола (если игра не окончена)
            if (game_over == 0)
            {
                ball_x = reset_ball_x(temp_ball_x, score1, score2, game_over, ball_x);
                ball_y = reset_ball_y(temp_ball_y, score1, score2, game_over, ball_y);
                
                ball_dx = reset_ball_dx(temp_ball_x, score1, score2, game_over, ball_dx);
                ball_dy = reset_ball_dy(temp_ball_x, score1, score2, game_over, ball_dy);
            }
        }
    }
    
    // Показ победителя
    show_winner(score1, score2);
    
    printf("\nPress Enter to exit...\n");
    getchar();
    getchar(); // Дополнительный getchar для обработки Enter
    
    return 0;
}