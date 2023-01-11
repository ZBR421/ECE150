#include <iostream>
#include "geesespotter_lib.h"
#include "geesespotter.h"

char *createBoard(std::size_t xdim, std::size_t ydim);
void cleanBoard(char *board);
void printBoard(char *board, std::size_t xdim, std::size_t ydim);
void computeNeighbors(char *board, std::size_t xdim, std::size_t ydim);
void hideBoard(char *board, std::size_t xdim, std::size_t ydim);
int reveal(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc);
int mark(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc);
bool isGameWon(char *board, std::size_t xdim, std::size_t ydim);

char *createBoard(std::size_t xdim, std::size_t ydim)
{

    char *board = new char[xdim * ydim];
    for (int i = 0; i < xdim * ydim; i++)
    {
        board[i] = 0;
    }
    return board;
}

void cleanBoard(char *board)
{
    delete []board;
}

void printBoard(char *board, std::size_t xdim, std::size_t ydim)
{
    char mark = 0;
    char hidden = 0;
    int value = 0;
    for (int i = 0; i < ydim; i++)
    {
        for (int j = 0; j < xdim; j++)
        {
            mark = board[i * xdim + j] & markedBit();
            hidden = board[i * xdim + j] & hiddenBit();
            value = board[i * xdim + j] & valueMask();
            if (mark == markedBit())
            {
                std::cout << "M";
            }
            else if (hidden == hiddenBit())
            {
                std::cout << "*";
            }
            else
            {
                std::cout << value;
            }
        }
        std::cout << std::endl;
    }
}
void computeNeighbors(char *board, std::size_t xdim, std::size_t ydim)
{
    for (int i = 0; i < ydim; i++)
    {
        for (int j = 0; j < xdim; j++)
        {
            int p = 0;
            if (board[i * xdim + j] != 9)
            {
                for (int a = i - 1; a <= i + 1; a++)
                {
                    for (int b = j - 1; b <= j + 1; b++)
                    {

                        if (a >= 0 && b >= 0 && board[a * xdim + b] == 9 && a < ydim && b < xdim)
                            p++;
                    }
                }
                board[i * xdim + j] = p;
            }
        }
    }
}
void hideBoard(char *board, std::size_t xdim, std::size_t ydim)
{
    for (int i = 0; i < ydim; i++)
    {
        for (int j = 0; j < xdim; j++)
        {
         board[i * xdim + j] ^= hiddenBit();
        }
    }
}
int reveal(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc)
{
    char mark = 0;
    char hidden = 0;
    int value = 0;

    mark = board[yloc * xdim + xloc] & markedBit();
    hidden = board[yloc * xdim + xloc] & hiddenBit();
    value = board[yloc * xdim + xloc] & valueMask();
    if (mark == markedBit())
    {
        return 1;
    }
    else if (hidden == 0)
    {
        return 2;
    }
    else if (value == 9)
    {
        board[yloc * xdim + xloc] ^= hiddenBit();
        return 9;
    }
    else if (value == 0)
    {

        for (int a = (int)yloc - 1; a <= (int)yloc + 1; a++)
        {
            for (int b = (int)xloc - 1; b <= (int)xloc + 1; b++)
            {
                if (a >= 0 && b >= 0 && a < ydim && b < xdim)
                {
                    if (!(board[a * xdim + b] & markedBit()) && ((board[a * xdim + b] & hiddenBit()) == hiddenBit()))
                    {
                        board[a * xdim + b] ^= hiddenBit();
                    }
                }
            }
        }
    }
    else
    {
        board[yloc * xdim + xloc] ^= hiddenBit();
    }

    return 0;
}

int mark(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc)
{
    if ((board[yloc * xdim + xloc] & hiddenBit()) != hiddenBit())
    {
        return 2;
    }
    else
    {
        board[yloc * xdim + xloc] ^= markedBit();
    }

    return 0;
}

bool isGameWon(char *board, std::size_t xdim, std::size_t ydim)
{
    for (int i = 0; i < xdim * ydim; ++i)
    {
        if (((board[i] & hiddenBit()) == hiddenBit()) && ((board[i] & valueMask()) != 9))
        {
            return false;
        }
    }
    return true;
}