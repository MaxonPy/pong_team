#include <ncurses.h>

int main() {
    initscr();              // инициализация ncurses
    printw("Hello, world!"); // вывод текста в буфер
    refresh();               // отображение буфера на экране
    getch();                 // ожидание нажатия клавиши
    endwin();                // восстановление терминала
    return 0;
}