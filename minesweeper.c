#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10
#define NUM_MINE 10
#define RESET "\033[0m"
#define COLOR_1 "\033[1;36m"
#define COLOR_2 "\033[1;32m"
#define COLOR_3 "\033[0;31m"
#define COLOR_4 "\033[1;34m"
#define COLOR_5 "\033[1;31m"
#define COLOR_6 "\033[1;36m"
#define COLOR_7 "\033[1;30m"
#define COLOR_8 "\033[1;37m"
#define MINE_CLR "\033[1;31m"
#define FLAG_CLR "\033[1;33m"

void saveGameResult(char board[SIZE][SIZE], int win, double timeTaken)
{
    FILE *f = fopen("result.txt", "a");
    if (f == NULL) {
        printf("ERROR!\n");
        return;
    }

    fprintf(f, "--------------- RESULT ------------------\n");
    fprintf(f, "Game: %s\n", win ? "WIN" : "LOSE");
    fprintf(f, "Time: %.2fs\n", timeTaken);
    fprintf(f, "Map:\n");

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            fprintf(f, "| %c ", board[i][j]);
        }
        fprintf(f, "|\n");
    }
    fprintf(f, "-----------------------------------------\n\n");
    fclose(f);
}

void printBoard(char board[SIZE][SIZE])
{
    system("clear");
    printf("    ");
    for(int i=0; i<SIZE; i++)
    {
        printf("%2d  ", i+1);
    }
    printf("\n");
    for(int i=0; i<SIZE; i++)
    {
        printf("%2d ", i+1);
        for(int j=0; j<SIZE; j++)
        {
            printf("| ");
            char c = board[i][j];
            
            switch(c)
            {
                case '1': printf("%s%c%s ", COLOR_1, c, RESET); break;
                case '2': printf("%s%c%s ", COLOR_2, c, RESET); break;
                case '3': printf("%s%c%s ", COLOR_3, c, RESET); break;
                case '4': printf("%s%c%s ", COLOR_4, c, RESET); break;
                case '5': printf("%s%c%s ", COLOR_5, c, RESET); break;
                case '6': printf("%s%c%s ", COLOR_6, c, RESET); break;
                case '7': printf("%s%c%s ", COLOR_7, c, RESET); break;
                case '8': printf("%s%c%s ", COLOR_8, c, RESET); break;
                case 'B': printf("%s%c%s ", MINE_CLR, c, RESET); break;
                case 'F': printf("%s%c%s ", FLAG_CLR, c, RESET); break;
                default:  printf("%c ", c);
            }
        }
        printf("|");
        printf("\n");
    }
    printf("\n>>\033[1;31m %d mines \033[0m<<\n\n", NUM_MINE);
    printf("\033[1;36mType {O: open | F: flag | U: unflag}\033[0m\n");
    printf("\nEnter your choice: ([row] [column] [type]): ");
}

void setNumbers(char board[SIZE][SIZE])
{
    for(int i=0; i<SIZE; i++)
    {
        for(int j=0; j<SIZE; j++)
        {
            if(board[i][j] == 'B')
            {
                continue;
            }

            int count = 0;
            
            for(int x=i-1; x<=i+1; x++)
            {
                for(int y=j-1; y<=j+1; y++)
                {
                    if(x>=0 && x<SIZE && y>=0 && y<SIZE)
                    {
                        if(board[x][y] == 'B')
                        {
                            count++;
                        }
                    }
                }
            }

            if(count == 0)
            {
                board[i][j] = ' ';
            }
            else
            {
                board[i][j] = count + '0';
            }
        }
    }
}

void setMines(char board[SIZE][SIZE])
{
    for(int i=0; i<NUM_MINE; )
    {
        int x = rand() % SIZE;
        int y = rand() % SIZE;
        if(board[x][y] != 'B')
        {
            board[x][y] = 'B';
            i++;
        }
    }
}

void reveal(char board[SIZE][SIZE], char display_board[SIZE][SIZE], int x, int y, int* cellsOpened)
{
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) return;
    if (display_board[x][y] != '*') return;

    display_board[x][y] = board[x][y];
    (*cellsOpened)++;

    if (board[x][y] == ' ')
    {
        for (int i=-1; i<=1; i++)
        {
            for (int j=-1; j<=1; j++)
            {
                if (i == 0 && j == 0) continue;
                reveal(board, display_board, x+i, y+j, cellsOpened);
            }
        }
    }
}

void play(char board[SIZE][SIZE], char display_board[SIZE][SIZE])
{
    int r, c;
    char t;
    int cellsOpened = 0;
    int totalCellsToOpen = (SIZE * SIZE) - NUM_MINE;

    time_t start_time = time(NULL);

    while(1)
    {
        printBoard(display_board);

        if(scanf("%d %d %c", &r, &c, &t) != 3)
        {
            while(getchar() != '\n');
            continue;
        }

        if(r<1 || r>SIZE || c<1 || c>SIZE)
        {
            printf("\nInvalid choice! Please try again!\n");
            while(getchar() != '\n');
            getchar();
            continue;
        }
        if(t == 'f' || t == 'F')
        {
            if(display_board[r-1][c-1] != '*')
            {
                while(getchar() != '\n');
                printf("\nInvalid choice! Please try again!\n");
                getchar();
                continue;
            }
            display_board[r-1][c-1] = 'F';
            continue;
        }
        if(t == 'u' || t == 'U')
        {
            if(display_board[r-1][c-1] != 'F')
            {
                while(getchar() != '\n');
                printf("\nInvalid choice! Please try again!\n");
                getchar();
                continue;
            }
            display_board[r-1][c-1] = '*';
            continue;
        }
        if(t == 'o' || t == 'O')
        {
            if(display_board[r-1][c-1] != '*')
            {
                if(display_board[r-1][c-1] == 'F')
                {
                    while(getchar() != '\n');
                    printf("\nInvalid choice! Please try again!\n");
                    getchar();
                    continue;
                }
                while(getchar() != '\n');
                printf("\nCell opened! Please try again!\n");
                getchar();
                continue;
            }
            if(board[r-1][c-1] == 'B')
            {
                printBoard(board);
                time_t end_time = time(NULL);
                double time_spent = difftime(end_time, start_time);
                while(getchar() != '\n');
                printf("\nThis cell has mine! You lose!\n");
                getchar();
                saveGameResult(board, 0, time_spent);
                break;
            }

            reveal(board, display_board, r-1, c-1, &cellsOpened);
        }
        else
        {
            while(getchar() != '\n');
            printf("\nInvalid choice! Please try again!\n");
            getchar();
            continue;
        }

        if (cellsOpened >= totalCellsToOpen)
        {
            printBoard(board);
            time_t end_time = time(NULL);
            double time_spent = difftime(end_time, start_time);
            while(getchar() != '\n');
            printf("\nCongratulation! You win!\n");
            getchar();
            saveGameResult(board, 1, time_spent);
            break;
        }
    }
}

int main()
{
    char board[SIZE][SIZE];
    char display_board[SIZE][SIZE];
    for(int i=0; i<SIZE; i++)
    {
        for(int j=0; j<SIZE; j++)
        {
            board[i][j] = ' ';
            display_board[i][j] = '*';
        }
    }
    srand(time(NULL));
    setMines(board);
    setNumbers(board);

    play(board, display_board);
    return 0;
}