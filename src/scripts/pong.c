/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pong.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxim <maxim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 18:30:00 by maxim             #+#    #+#             */
/*   Updated: 2026/02/27 18:30:00 by maxim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include <stdio.h>

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

// Функция проверки столкновения мяча с ракеткой
int check_paddle_collision(int paddle_y, int ball_x, int ball_y,
                           int is_left_paddle) {
  int paddle_x;
  int result;

  result = 0;

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

// Функция обновления позиции мяча
int update_ball_x(int ball_x, int ball_dx) { return ball_x + ball_dx; }

int update_ball_y(int ball_y, int ball_dy) { return ball_y + ball_dy; }

int update_ball_dx(int ball_x, int ball_dx, int paddle1_y, int paddle2_y,
                   int ball_y) {
  int new_dx;

  new_dx = ball_dx;

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
  int new_dy;

  new_dy = ball_dy;

  // Проверка столкновения с верхней и нижней стенками
  if (ball_y <= TOP_WALL + 1) {
    new_dy = 1;
  } else if (ball_y >= BOTTOM_WALL - 1) {
    new_dy = -1;
  }

  return new_dy;
}

// Функция сброса мяча после гола
int reset_ball_x(int ball_x, int score1, int score2, int game_over,
                 int current_ball_x) {
  int new_ball_x;

  new_ball_x = current_ball_x;

  if ((ball_x <= LEFT_WALL + 1 || ball_x >= RIGHT_WALL - 1) && game_over == 0) {
    if (score1 < WIN_SCORE && score2 < WIN_SCORE) {
      new_ball_x = 40;
    }
  }
  return new_ball_x;
}

int reset_ball_y(int ball_x, int score1, int score2, int game_over,
                 int current_ball_y) {
  int new_ball_y;

  new_ball_y = current_ball_y;

  if ((ball_x <= LEFT_WALL + 1 || ball_x >= RIGHT_WALL - 1) && game_over == 0) {
    if (score1 < WIN_SCORE && score2 < WIN_SCORE) {
      new_ball_y = 12;
    }
  }
  return new_ball_y;
}

int reset_ball_dx(int ball_x, int score1, int score2, int game_over,
                  int current_ball_dx) {
  int new_ball_dx;

  new_ball_dx = current_ball_dx;

  if (ball_x <= LEFT_WALL + 1 && game_over == 0) {
    if (score1 < WIN_SCORE && score2 < WIN_SCORE) {
      new_ball_dx = 1;
    }
  } else if (ball_x >= RIGHT_WALL - 1 && game_over == 0) {
    if (score1 < WIN_SCORE && score2 < WIN_SCORE) {
      new_ball_dx = -1;
    }
  }
  return new_ball_dx;
}

int reset_ball_dy(int ball_x, int score1, int score2, int game_over,
                  int current_ball_dy) {
  int new_ball_dy;

  new_ball_dy = current_ball_dy;

  if ((ball_x <= LEFT_WALL + 1 || ball_x >= RIGHT_WALL - 1) && game_over == 0) {
    if (score1 < WIN_SCORE && score2 < WIN_SCORE) {
      new_ball_dy = 1;
    }
  }
  return new_ball_dy;
}

// Функция отрисовки игрового поля
void draw_field(int paddle1_y, int paddle2_y, int ball_x, int ball_y,
                int score1, int score2) {
  int row;
  int col;
  int is_paddle1;
  int is_paddle2;
  int is_ball;

  clear_screen();

  // Верхняя граница
  for (col = 0; col < WIDTH; col++) {
    printf("%c", HOR);
  }
  printf("\n");

  // Основное поле
  for (row = 1; row < HEIGHT - 1; row++) {
    // Левая граница
    printf("%c", VER);

    for (col = 1; col < WIDTH - 1; col++) {
      is_paddle1 = 0;
      is_paddle2 = 0;
      is_ball = 0;

      // Левая ракетка
      if (col == 1 && row >= paddle1_y && row < paddle1_y + PADDLE_HEIGHT) {
        is_paddle1 = 1;
      }
      // Правая ракетка
      else if (col == WIDTH - 2 && row >= paddle2_y &&
               row < paddle2_y + PADDLE_HEIGHT) {
        is_paddle2 = 1;
      }
      // Мяч
      else if (col == ball_x && row == ball_y) {
        is_ball = 1;
      }

      if (is_paddle1 == 1 || is_paddle2 == 1) {
        printf("%c", VER);
      } else if (is_ball == 1) {
        printf("%c", BALL);
      } else {
        printf(" ");
      }
    }

    // Правая граница
    printf("%c\n", VER);
  }

  // Нижняя граница
  for (col = 0; col < WIDTH; col++) {
    printf("%c", HOR);
  }
  printf("\n");

  // Отображение счета
  printf("Player 1 (A/Z): %d\t\tPlayer 2 (K/M): %d\n", score1, score2);
  printf("Press SPACE to skip turn, 'q' to quit\n");
}

int main(void) {
  // Инициализация переменных игры
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

  int temp_ball_x;
  int temp_ball_y;
  int temp_score1;
  int temp_score2;

  // Начальные значения
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

  // Ожидание нажатия Enter для начала игры
  c = getchar();

  // Основной игровой цикл
  while (game_over == 0) {
    // Отрисовка поля
    draw_field(paddle1_y, paddle2_y, ball_x, ball_y, score1, score2);
    // Ожидание ввода
    c = getchar();
    // Обработка ввода без указателей
    if (c == 'a' || c == 'A') {
      paddle1_y = move_paddle1_up(paddle1_y);
    } else if (c == 'z' || c == 'Z') {
      paddle1_y = move_paddle1_down(paddle1_y);
    } else if (c == 'k' || c == 'K') {
      paddle2_y = move_paddle2_up(paddle2_y);
    } else if (c == 'm' || c == 'M') {
      paddle2_y = move_paddle2_down(paddle2_y);
    } else if (c == 'q' || c == 'Q') {
      game_over = 1;
    }
    // Пробел - просто пропуск хода

    // Обновление состояния мяча (только если игра не окончена)
    if (game_over == 0) {
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
      if (game_over == 0) {
        ball_x = update_ball_x(ball_x, ball_dx);
        ball_y = update_ball_y(ball_y, ball_dy);
      }

      // Сбрасываем мяч после гола (если игра не окончена)
      if (game_over == 0) {
        ball_x = reset_ball_x(temp_ball_x, score1, score2, game_over, ball_x);
        ball_y = reset_ball_y(temp_ball_y, score1, score2, game_over, ball_y);

        ball_dx =
            reset_ball_dx(temp_ball_x, score1, score2, game_over, ball_dx);
        ball_dy =
            reset_ball_dy(temp_ball_x, score1, score2, game_over, ball_dy);
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