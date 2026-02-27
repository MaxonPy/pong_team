//padle
int move_paddle1_down(int paddle1_y);

int move_paddle1_up(int paddle1_y);

int move_paddle2_up(int paddle2_y);

int move_paddle2_down(int paddle2_y);

//win
int check_game_over(int score1, int score2);

void show_winner(int score1, int score2);

int check_goal_left(int ball_x, int score2);

int check_goal_right(int ball_x, int score1);

//clear
void clear_screen(void);