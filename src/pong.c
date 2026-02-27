/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pong.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxim <maxim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 18:30:00 by maxim             #+#    #+#             */
/*   Updated: 2026/02/27 19:30:00 by maxim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>   // вместо stdio.h, так как используем только ncurses
#include <stdlib.h>

#define WIDTH 80
#define HEIGHT 25
#define LEFT_WALL 0
#define RIGHT_WALL 79
#define TOP_WALL 0
#define BOTTOM_WALL 24
#define PADDLE_HEIGHT 3
#define WIN_SCORE 21

#define HOR '-'
#define VER '|'
#define BALL '*'

// Функция для очистки экрана
void clear_screen(void) {
    clear();
    // refresh() будет вызван в draw_field, здесь не нужен
}

// Функция проверки столкновения мяча с ракеткой
int check_paddle_collision(int paddle_y, int ball_x, int ball_y,
                           int is_left_paddle) {
    int paddle_x;
    int result = 0;

    if (is_left_paddle)
        paddle_x = 1;
    else
        paddle_x = 78;

    if (ball_x == paddle_x && ball_y >= paddle_y &&
        ball_y < paddle_y + PADDLE_HEIGHT) {
        result = 1;
    }
    return result;
}

// Функции обновления позиции мяча
int update_ball_x(int ball_x, int ball_dx) { return ball_x + ball_dx; }
int update_ball_y(int ball_y, int ball_dy) { return ball_y + ball_dy; }

int update_ball_dx(int ball_x, int ball_dx, int paddle1_y, int paddle2_y,
                   int ball_y) {
    int new_dx = ball_dx;

    // Проверка столкновения с левой ракеткой
    if (ball_x == 2 && check_paddle_collision(paddle1_y, ball_x - 1, ball_y, 1)) {
        new_dx = 1;
    }
    // Проверка столкновения с правой ракеткой
    else if (ball_x == 77 &&
             check_paddle_collision(paddle2_y, ball_x + 1, ball_y, 0)) {
        new_dx = -1;
    }
    return new_dx;
}

int update_ball_dy(int ball_y, int ball_dy) {
    int new_dy = ball_dy;

    // Проверка столкновения с верхней и нижней стенками
    if (ball_y <= TOP_WALL + 1) {
        new_dy = 1;
    } else if (ball_y >= BOTTOM_WALL - 1) {
        new_dy = -1;
    }
    return new_dy;
}

// Функции проверки гола и обновления счета
int check_goal_left(int ball_x, int score2) {
    if (ball_x <= LEFT_WALL + 1)
        return score2 + 1;
    return score2;
}

int check_goal_right(int ball_x, int score1) {
    if (ball_x >= RIGHT_WALL - 1)
        return score1 + 1;
    return score1;
}

// Функции сброса мяча после гола
int reset_ball_x(int ball_x, int score1, int score2, int game_over,
                 int current_ball_x) {
    if ((ball_x <= LEFT_WALL + 1 || ball_x >= RIGHT_WALL - 1) && !game_over) {
        if (score1 < WIN_SCORE && score2 < WIN_SCORE)
            return 40;
    }
    return current_ball_x;
}

int reset_ball_y(int ball_x, int score1, int score2, int game_over,
                 int current_ball_y) {
    if ((ball_x <= LEFT_WALL + 1 || ball_x >= RIGHT_WALL - 1) && !game_over) {
        if (score1 < WIN_SCORE && score2 < WIN_SCORE)
            return 12;
    }
    return current_ball_y;
}

int reset_ball_dx(int ball_x, int score1, int score2, int game_over,
                  int current_ball_dx) {
    if (ball_x <= LEFT_WALL + 1 && !game_over) {
        if (score1 < WIN_SCORE && score2 < WIN_SCORE)
            return 1;
    } else if (ball_x >= RIGHT_WALL - 1 && !game_over) {
        if (score1 < WIN_SCORE && score2 < WIN_SCORE)
            return -1;
    }
    return current_ball_dx;
}

int reset_ball_dy(int ball_x, int score1, int score2, int game_over,
                  int current_ball_dy) {
    if ((ball_x <= LEFT_WALL + 1 || ball_x >= RIGHT_WALL - 1) && !game_over) {
        if (score1 < WIN_SCORE && score2 < WIN_SCORE)
            return 1;
    }
    return current_ball_dy;
}

// Функция проверки окончания игры
int check_game_over(int score1, int score2) {
    return (score1 >= WIN_SCORE || score2 >= WIN_SCORE);
}

// Функция отрисовки игрового поля (оптимизировано — один refresh в конце)
void draw_field(int paddle1_y, int paddle2_y, int ball_x, int ball_y,
                int score1, int score2) {
    int row, col;

    clear_screen();

    // Верхняя граница
    for (col = 0; col < WIDTH; col++)
        printw("%c", HOR);
    printw("\n");

    // Основное поле
    for (row = 1; row < HEIGHT - 1; row++) {
        // Левая граница
        printw("%c", VER);

        for (col = 1; col < WIDTH - 1; col++) {
            int is_paddle1 = 0, is_paddle2 = 0, is_ball = 0;

            if (col == 1 && row >= paddle1_y && row < paddle1_y + PADDLE_HEIGHT)
                is_paddle1 = 1;
            else if (col == WIDTH - 2 && row >= paddle2_y &&
                     row < paddle2_y + PADDLE_HEIGHT)
                is_paddle2 = 1;
            else if (col == ball_x && row == ball_y)
                is_ball = 1;

            if (is_paddle1 || is_paddle2)
                printw("%c", VER);
            else if (is_ball)
                printw("%c", BALL);
            else
                printw(" ");
        }

        // Правая граница
        printw("%c\n", VER);
    }

    // Нижняя граница
    for (col = 0; col < WIDTH; col++)
        printw("%c", HOR);
    printw("\n");

    // Отображение счета
    printw("Player 1 (A/Z): %d\t\tPlayer 2 (K/M): %d\n", score1, score2);
    printw("Press SPACE to skip turn, 'q' to quit\n");

    refresh();  // единственный refresh за кадр
}

// Функции движения ракеток
int move_paddle1_up(int paddle1_y) {
    return (paddle1_y > 1) ? paddle1_y - 1 : paddle1_y;
}
int move_paddle1_down(int paddle1_y) {
    return (paddle1_y < HEIGHT - PADDLE_HEIGHT - 1) ? paddle1_y + 1 : paddle1_y;
}
int move_paddle2_up(int paddle2_y) {
    return (paddle2_y > 1) ? paddle2_y - 1 : paddle2_y;
}
int move_paddle2_down(int paddle2_y) {
    return (paddle2_y < HEIGHT - PADDLE_HEIGHT - 1) ? paddle2_y + 1 : paddle2_y;
}

// Функция отображения победителя
void show_winner(int score1, int score2) {
    clear_screen();
    for (int i = 0; i < 10; i++)
        printw("\n");

    if (score1 >= WIN_SCORE) {
        printw("****************************************\n");
        printw("*                                      *\n");
        printw("*         PLAYER 1 WINS!               *\n");
        printw("*                                      *\n");
        printw("****************************************\n");
    } else if (score2 >= WIN_SCORE) {
        printw("****************************************\n");
        printw("*                                      *\n");
        printw("*         PLAYER 2 WINS!               *\n");
        printw("*                                      *\n");
        printw("****************************************\n");
    } else {
        printw("****************************************\n");
        printw("*                                      *\n");
        printw("*         GAME OVER                    *\n");
        printw("*                                      *\n");
        printw("****************************************\n");
    }
    printw("\n\nFinal Score: %d - %d\n", score1, score2);
    refresh();
}

int main(void) {
    // Инициализация ncurses (теперь в самом начале)
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);  // скрыть курсор

    // Переменные игры
    int paddle1_y = 11;
    int paddle2_y = 11;
    int ball_x = 40;
    int ball_y = 12;
    int ball_dx = 1;
    int ball_dy = 1;
    int score1 = 0;
    int score2 = 0;
    int game_over = 0;
    int c;

    // Стартовый экран (используем printw вместо printf)
    printw("PONG GAME - Two Player\n");
    printw("Controls:\n");
    printw("Player 1: A (up) / Z (down)\n");
    printw("Player 2: K (up) / M (down)\n");
    printw("SPACE - skip turn\n");
    printw("Press any key to start...\n");
    refresh();
    getch();  // ожидание любого нажатия вместо Enter

    // Основной игровой цикл
    while (!game_over) {
        draw_field(paddle1_y, paddle2_y, ball_x, ball_y, score1, score2);

        c = getch();  // используем ncurses-ввод

        // Обработка ввода
        if (c == 'a' || c == 'A')
            paddle1_y = move_paddle1_up(paddle1_y);
        else if (c == 'z' || c == 'Z')
            paddle1_y = move_paddle1_down(paddle1_y);
        else if (c == 'k' || c == 'K')
            paddle2_y = move_paddle2_up(paddle2_y);
        else if (c == 'm' || c == 'M')
            paddle2_y = move_paddle2_down(paddle2_y);
        else if (c == 'q' || c == 'Q')
            game_over = 1;
        // Пробел - просто пропуск, ничего не делаем

        if (!game_over) {
            // Сохраняем позицию мяча для сброса
            int old_ball_x = ball_x;
            int old_ball_y = ball_y;

            // Проверяем голы и обновляем счёт
            score1 = check_goal_right(ball_x, score1);
            score2 = check_goal_left(ball_x, score2);

            game_over = check_game_over(score1, score2);

            if (!game_over) {
                // Обновляем направление
                ball_dx = update_ball_dx(ball_x, ball_dx, paddle1_y, paddle2_y, ball_y);
                ball_dy = update_ball_dy(ball_y, ball_dy);

                // Обновляем позицию
                ball_x = update_ball_x(ball_x, ball_dx);
                ball_y = update_ball_y(ball_y, ball_dy);

                // Сброс мяча после гола (если игра не окончена)
                ball_x = reset_ball_x(old_ball_x, score1, score2, game_over, ball_x);
                ball_y = reset_ball_y(old_ball_x, score1, score2, game_over, ball_y);
                ball_dx = reset_ball_dx(old_ball_x, score1, score2, game_over, ball_dx);
                ball_dy = reset_ball_dy(old_ball_x, score1, score2, game_over, ball_dy);
            }
        }
    }

    // Показ победителя (ncurses ещё активен)
    show_winner(score1, score2);

    printw("\nPress any key to exit...\n");
    refresh();
    getch();  // ждём нажатия для выхода

    endwin();  // корректное завершение ncurses
    return 0;
}