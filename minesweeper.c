#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 9
#define NUM_MINE 6

void printBoard(char board[SIZE][SIZE])
{
    system("clear");
    printf("    ");
    for(int i=0; i<SIZE; i++)
    {
        printf("%d   ", i+1);
    }
    printf("\n");
    for(int i=0; i<SIZE; i++)
    {
        printf("%d ", i+1);
        for(int j=0; j<SIZE; j++)
        {
            printf("| %c ", board[i][j]);
        }
        printf("|");
        printf("\n");
    }
    printf("\n>> %d mines <<\n\n", NUM_MINE);
    printf("Type {O: open | F: flag | U: unflag}\n");
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
        else if(t == 'u' || t == 'U')
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
        else if(t == 'o' || t == 'O')
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
                while(getchar() != '\n');
                printf("\nThis cell has mine! You lose!\n");
                getchar();
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

        if (cellsOpened == totalCellsToOpen)
        {
            printBoard(board);
            while(getchar() != '\n');
            printf("\nongratulation! You win!\n");
            getchar();
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