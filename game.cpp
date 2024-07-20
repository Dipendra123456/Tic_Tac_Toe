#include <iostream>
using namespace std;

#define computer 1
#define human 2
#define side 3
#define computermove 'O'
#define humanmove 'X'

void showInstructions()
{
    printf("Choose a cell numbered from 1 to 0 as below and play \n\n");
    printf("\t\t\t 1 | 2 | 3 \n");
    printf("\t\t\t 4 | 5 | 6 \n");
    printf("\t\t\t 7 | 8 | 9 \n");
}

void initialise(char board[][side])
{
    for(int i=0; i<side; i++)
    {
        for(int j=0; j<side; j++)
        board[i][j] = '*';
    }
}

void declareWinner(int whoseTurn)
{
    if(whoseTurn == computer)
    printf("COMPUTER won \n");
    else
    printf("HUMAN won \n");
}

bool rowCrossed(char board[][side])
{
    for(int i=0; i<side; i++)
    {
        if(board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != '*')
        return true;
    }
    return false;
}

bool columnCrossed(char board[][side])
{
    for(int i=0; i<side; i++)
    {
        if(board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != '*')
        return true;
    }
    return false;
}

bool diagonalCrossed(char board[][side])
{
    if(board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != '*')
    return true;
    if(board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != '*')
    return true;
    return false;
}

bool gameOver(char board[][side])
{
    return (rowCrossed(board) || columnCrossed(board) || diagonalCrossed(board));
}

void showBoard(char board[][side])
{
    printf("\t\t\t %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("\t\t\t %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("\t\t\t %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
}

int minimax(char board[][side], int depth, bool isAI)
{
    int score = 0;
    int bestScore = 0;
    if(gameOver(board) == true)
    {
        if(isAI == true) return -10;
        if(isAI == false) return 10;
    }
    else
    {
        if(depth < 9)
        {
            if(isAI == true)
            {
                bestScore = -999;
                for(int i=0; i<side; i++)
                {
                    for(int j=0; j<side; j++)
                    {
                        if(board[i][j] == '*')
                        {
                            board[i][j] = computermove;
                            score = minimax(board, depth+1, false);
                            board[i][j] = '*';
                            if(score > bestScore) bestScore = score;
                        }
                    }
                }
                return bestScore;
            }
            else
            {
                bestScore = 999;
                for(int i=0; i<side; i++)
                {
                    for(int j=0; j<side; j++)
                    {
                        if(board[i][j] == '*')
                        {
                            board[i][j] = humanmove;
                            score = minimax(board, depth+1, false);
                            board[i][j] = '*';
                            if(score > bestScore) bestScore = score;
                        }
                    }
                }
                return bestScore;
            }
        }
        else
        return 0;
    }
    return -1;
}

int bestMove(char board[][side], int moveIndex)
{
    int x = -1, y = -1;
    int score = 0, bestScore = -999;
    for(int i=0; i<side; i++)
    {
        for(int j=0; j<side; j++)
        {
            if(board[i][j] == '*')
            {
                board[i][j] = computermove;
                score = minimax(board, moveIndex+1, false);
                board[i][j] = '*';
                if(score > bestScore)
                {
                    bestScore = score;
                    x = i;
                    y = j;
                }
            }
        }
    }
    return x*3+y;
}

void playGame(int whoseTurn)
{
    char board[side][side];
    int moveIndex = 0, x = 0, y = 0;
    initialise(board);
    showInstructions();

    while(gameOver(board) == false && moveIndex != side*side)
    {
        int n;
        if(whoseTurn == computer)
        {
            n= bestMove(board, moveIndex);
            x = n / side;
            y = n % side;
            board[x][y] = computermove;
            printf("COMPUTER has put a %c in cell %c.\n", computermove, n+1);
            showBoard(board);
            moveIndex++;
            whoseTurn = human;
        }
        else if(whoseTurn == human)
        {
            printf("You can insert in the following positions: ");
            for(int i=0; i<side; i++)
                for(int j=0; j<side; j++)
                    if(board[i][j] == '*')
                    printf("%d ", (i*3+j) + 1);
            printf("\nEnter the position: ");
            scanf("%d", &n);
            n--;
            x = n / side;
            y = n % side;
            if(board[x][y] == '*' && n<9 && n>=0)
            {
                board[x][y] = humanmove;
                printf("HUMAN has put a %c in cell %d\n", humanmove, n+1);
                showBoard(board);
                moveIndex++;
                whoseTurn = computer;
            }
            else if(board[x][y] != '*' && n<9 && n>=0)
            printf("Position is occupied, select any one place from the available places \n");
            else if(n<0 || n>8)
            printf("Invalid position \n");
        }
    }
    if(gameOver(board) == false && moveIndex == side*side)
    printf("It's a draw \n");
    else
    {
        if(whoseTurn == computer)
        whoseTurn = human;
        else if(whoseTurn == human)
        whoseTurn = computer;
    }
    declareWinner(whoseTurn);
}

int main()
{
    printf("\n-----------------------------------------------------\n");
    printf("\t\t\t Tic-Tac_Toe\n");
    printf("\n-----------------------------------------------------\n");
    char cont = 'y';
    do
    {
        char choice;
        printf("Do you want to start first? (y/n): ");
        scanf(" %c", &choice);
        if(choice == 'n')
        playGame(computer);
        else if(choice == 'y')
        playGame(human);
        else
        printf("Invalid choice\n");
        printf("Do you want to quit? (y/n): ");
        scanf(" %c", &cont);
    } while(cont == 'n');
    return 0;    
}