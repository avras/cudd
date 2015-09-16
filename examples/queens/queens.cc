#include "cuddObj.hh"
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <cassert>

using namespace std;

void PositionConstraints(BDD& queen, BDD **board, int i, int j, int N, Cudd *mgr)
{
  BDD a = mgr->bddOne();
  BDD b = mgr->bddOne();
  BDD c = mgr->bddOne();
  BDD d = mgr->bddOne();

  // No queens in same column
  for (int l = 0; l < N; l++)
  {
    if (l != j)
    {
      a &= ((!board[i][j]) | (!board[i][l]));
    }
  }

  // No queens in same row
  for (int k = 0; k < N; k++)
  {
    if (k != i)
    {
      b &= ((!board[i][j]) | (!board[k][j]));
    }
  }

  // No queens in same up-right diagnol
  for (int k = 0; k < N; k++)
  {
    int ll = k-i+j;
    if ((ll >= 0) && (ll < N) && (k != i))
    {
      c &= ((!board[i][j]) | (!board[k][ll]));
    }
  }

  // No queens in same down-right diagnol
  for (int k = 0; k < N; k++)
  {
    int ll = i+j-k;
    if ((ll >= 0) && (ll < N) && (k != i))
    {
      d &= ((!board[i][j]) | (!board[k][ll]));
    }
  }

  queen &= (a & b & c & d);
}

int main(int ac, char **av)
{
   int N;            /* Size of the chess board */
   int b,c;
   
   if (ac != 4)
   {
      fprintf(stderr, "USAGE:  queen N b c\n");
      return 1;
   }

   N = atoi(av[1]);
   b = atoi(av[2]);
   c = atoi(av[3]);

   if (N <= 0)
   {
      fprintf(stderr, "USAGE:  queen N\n");
      return 1;
   }

   Cudd mgr(N*N, 0, 1 << b, 1 << c);
   BDD queen = mgr.bddOne();

    BDD **board;
    board = new BDD*[N];
    for (int i = 0; i < N; i++)
      board[i] = new BDD[N];

    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < N; j++)
      {
        board[i][j] = mgr.bddVar(i*N+j);
      }
    }
   
    BDD temp;
    // Each row has at least one queen
    for (int i = 0; i < N; i++)
    {
      temp = mgr.bddZero();
      for (int j = 0; j < N; j++)
      {
        temp |= board[i][j];
      }
      queen &= temp;
    }

    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < N; j++)
      {
        cout << "Adding position " << i << "," << j << endl << flush;
        PositionConstraints(queen, board, i, j, N, &mgr);
      }
    }

    cout << queen.CountMinterm(N*N)<< endl;

    for (int i = 0; i < N; i++)
      delete[] board[i];
    delete[] board;
     return 0;
}
