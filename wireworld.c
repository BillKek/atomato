// https://en.wikipedia.org/wiki/Wireworld

#include <assert.h>
#include <string.h>
#include <errno.h>
#include "./life.h"

typedef enum
{
    EMPTY = 0,
    HEAD,
    TAIL,
    CONDUCTOR,
    CELL_COUNT
} Wireworld_Cell;

Color cell_color[CELL_COUNT] =
{
    [EMPTY] = 0,
    [HEAD] = 0xFFFFFFFF,
    [TAIL] = 0x0080FFFF,
    [CONDUCTOR] = 0xFF8000FF,
};

Color parse_color[CELL_COUNT] =
{
    // [EMPTY] = 0,
    // [HEAD] = BLUE_COLOR,
    // [TAIL] = PINK_COLOR,
    // [CONDUCTOR] = YELLOW_COLOR
    [EMPTY] = 0xFF000000,
    [HEAD] = 0xFFFFFFFF,
    [TAIL] = 0xFFFF8000,
    [CONDUCTOR] = 0xFF0080FF,
};

void wireworld_rule(Cell* prev, Cell* next)
{
    for (int row = 0; row < ROWS; ++row)
    {
        for (int col = 0; col < COLS; ++col)
        {
            const int nbor_heads = life_board_nbors(prev, row, col, HEAD);

            switch (prev[iter_cell(col,row)])
            {
            case EMPTY:
                next[iter_cell(col,row)] = EMPTY;
                break;
            case HEAD:
                next[iter_cell(col,row)] = TAIL;
                break;
            case TAIL:
                next[iter_cell(col,row)] = CONDUCTOR;
                break;
            case CONDUCTOR:
                next[iter_cell(col,row)] =  (nbor_heads == 1 || nbor_heads == 2) ? HEAD : CONDUCTOR;
                break;
            default:
                assert(false && "wireworld_rule: unreachable");
            }
        }
    }
}

int main(int argc, char **argv)
{
    char arg1_default[] = "./images/ww800x600.gif\x0";
    char *arg1_copy = arg1_default;
    if (argc < 2)
    {
        fprintf(stderr, "USAGE: ./wireworld <image.gif>\n");
        fprintf(stderr, "ERROR: no input is provided\n");
        //exit(1);
    }
    else
        arg1_copy = argv[1];

    Board board = {0};

    life_load_board_from_image(&board, arg1_copy, CELL_COUNT, parse_color);

    life_go(&board,
            wireworld_rule,
            CELL_COUNT,
            cell_color,
            "wireworld.png");

    return 0;
}
