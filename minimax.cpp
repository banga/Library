/**
 * Author: Shrey Banga
 */
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <list>
#include <deque>
#include <algorithm>
#include <typeinfo>
#include <ctime>
#include <conio.h>

using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); i++)
#define REP(i,n) FOR(i,0,n)
#define FORE(i,v) for(typeof(v.begin()) i = v.begin(); i != v.end(); i++)

#define GRID_SIZE 4
#define GRID_CELLS (GRID_SIZE * GRID_SIZE)

enum CellState { EMPTY = 0, CROSS = 1, ZERO = -1 };

CellState toCellState(char c) {
  if(c >= 'A' && c <= 'Z')
    c += 'a' - 'A';
  return ((c == 'x') ? CROSS : (c == 'o' ? ZERO : EMPTY));
}

class State {
 public:
  State(const char str[GRID_CELLS]) {
    REP(i, GRID_CELLS)
      s[i] = toCellState(str[i]);
  }

  CellState& operator () (int i, int j) {
    return s[i * GRID_SIZE + j];
  }

  bool operator < (const State& st) const {
    // Horizontal reflection
    bool eq = true;
    REP(i, GRID_SIZE)
      REP(j, GRID_SIZE)
        if(s[i * GRID_SIZE + j] != st.s[i * GRID_SIZE + (GRID_SIZE-1-j)]) {
          eq = false;
          break;
        }
    if(eq) return false;

    // Vertical reflection
    eq = true;
    REP(i, GRID_SIZE)
      REP(j, GRID_SIZE)
        if(s[i * GRID_SIZE + j] != st.s[(GRID_SIZE-1-i) * GRID_SIZE + j]) {
          eq = false;
          break;
        }
    if(eq) return false;

    // Major Diagonal reflection
    eq = true;
    REP(i, GRID_SIZE)
      REP(j, GRID_SIZE)
        if(s[i * GRID_SIZE + j] != st.s[j * GRID_SIZE + i]) {
          eq = false;
          break;
        }
    if(eq) return false;

    // Minor Diagonal reflection
    eq = true;
    REP(i, GRID_SIZE)
      REP(j, GRID_SIZE)
        if(s[i * GRID_SIZE + j] != st.s[(GRID_SIZE-1-j) * GRID_SIZE + (GRID_SIZE-1-i)]) {
          eq = false;
          break;
        }
    if(eq) return false;

    // Rotate 90 CW
    eq = true;
    REP(i, GRID_SIZE)
      REP(j, GRID_SIZE) {
        int ii = j;
        int jj = GRID_SIZE-1-i;
        if(s[i * GRID_SIZE + j] != st.s[ii * GRID_SIZE + jj]) {
          eq = false;
          break;
        }
      }
    if(eq) return false;

    // Rotate -90 CW
    eq = true;
    REP(i, GRID_SIZE)
      REP(j, GRID_SIZE) {
        int ii = GRID_SIZE-1-j;
        int jj = i;
        if(s[i * GRID_SIZE + j] != st.s[ii * GRID_SIZE + jj]) {
          eq = false;
          break;
        }
      }
    if(eq) return false;

    // Original
    REP(i, GRID_CELLS)
      if(s[i] != st.s[i])
        return s[i] < st.s[i];

    return false;
  }

  char toChar(CellState c) const {
    return ((c == EMPTY) ? ' ' : ((c == CROSS) ? 'X' : 'O'));
  }

  void print() const {
    REP(i,GRID_SIZE) {
      REP(j,GRID_SIZE) {
        printf(" %c ", toChar(s[i * GRID_SIZE + j]));
        if(j < GRID_SIZE-1)
          printf("|");
      }
      printf("\n");
      if(i < GRID_SIZE-1) {
        REP(j,GRID_SIZE) {
          printf("---");
          if(j < GRID_SIZE-1)
            printf("+");
        }
        printf("\n");
      }
    }
    printf("\n");
  }

 private:
  CellState s[GRID_CELLS];
};


// Returns winner if finished, 2 if tied, 0 otherwise
bool isFinished(State& s, int& score) {
  // Rows
  REP(i,GRID_SIZE) {
    int j = 1;
    if(s(i,0) != EMPTY)
      while(j < GRID_SIZE && (s(i,j) == s(i,j-1)))
        j++;
    if(j == GRID_SIZE) {
      score = s(i,0);
      return true;
    }
  }

  // Columns
  REP(i,GRID_SIZE) {
    int j = 1;
    if(s(0,i) != EMPTY)
      while(j < GRID_SIZE && (s(j,i) == s(j-1,i)))
        j++;
    if(j == GRID_SIZE) {
      score = s(0,i);
      return true;
    }
  }

  // Major Diagonal
  if(s(0,0) != EMPTY) {
    int i = 1;
    while(i < GRID_SIZE && (s(i,i) == s(i-1,i-1)))
      i++;
    if(i == GRID_SIZE) {
      score = s(0,0);
      return true;
    }
  }

  // Minor Diagonal
  int n = GRID_SIZE-1;
  if(s(n,0) != EMPTY) {
    int i = 0;
    while(i < n && (s(i,n-i) == s(i+1,n-i-1)))
      i++;
    if(i == n) {
      score = s(n,0);
      return true;
    }
  }

  REP(i,GRID_SIZE)
    REP(j,GRID_SIZE)
      if(s(i,j) == EMPTY)
        return false;

  score = 0;
  return true;
}

int chooseMove(State& s, bool aiTurn, int alpha, int beta, int& bestI, int& bestJ, int& movesExamined) {
  ++movesExamined;

  int score;
  if(isFinished(s, score)) {
    bestI = -1;
    bestJ = -1;
    return score;
  }

  if(aiTurn) {
    int bi, bj;

    REP(i,GRID_SIZE)
      REP(j,GRID_SIZE) {
        if(s(i,j) == EMPTY) {
          s(i,j) = CROSS;
          score = chooseMove(s, false, alpha, beta, bi, bj, movesExamined);
          s(i,j) = EMPTY;
          
          if(score > alpha) {
            alpha = score;
            bestI = i;
            bestJ = j;

              if(beta <= alpha) {
//                s(i,j) = CROSS;
//                if(!isFinished(s, score)) {
//                  s.print();
//                  printf("%d %d\n\n", i, j);
//                }
//                s(i,j) = EMPTY;

              return alpha;
            }
          }
        }
      }

    return alpha;
  } else {
    int bi, bj;

    REP(i,GRID_SIZE)
      REP(j,GRID_SIZE) {
        if(s(i,j) == EMPTY) {
          s(i,j) = ZERO;
          score = chooseMove(s, true, alpha, beta, bi, bj, movesExamined);
          s(i,j) = EMPTY;
          
          if(score < beta) {
            beta = score;
            bestI = i;
            bestJ = j;

            if(beta <= alpha)
              return beta;
          }
        }
      }

    return beta;
  }
}

bool makeMove(State& state, int i, int j, bool& aiMove) {
  if(i < 0 || j < 0)
    return false;

  state(i,j) = (aiMove ? CROSS : ZERO);
  aiMove = !aiMove;

  return true;
}

int main() {
  char str[GRID_SIZE * GRID_SIZE];
  REP(i,GRID_SIZE)
    REP(j,GRID_SIZE)
      str[i*GRID_SIZE+j] = (' ');

  State state(str);

  char c;
  printf("Press n to play second:\n");
  c = getch();

  bool aiMove = (c == 'n');
  int i = -1, j = -1;
  if(c == 'n') {
    srand(time(NULL));
    i = rand() % GRID_SIZE;
    j = rand() % GRID_SIZE;
    makeMove(state, i, j, aiMove);
  }

  int w, movesExamined = 0;

  while(!isFinished(state, w)) {
    if(aiMove) {
      movesExamined = 0;
      chooseMove(state, aiMove, -2, 2, i, j, movesExamined);
    } else {
      system("cls");
      printf("[Examined: %d] Computer takes (%d,%d):\n", movesExamined, i, j);
      state.print();
      do {
        printf("\nEnter your move: ");
        scanf("%d %d", &i, &j);
      } while(i < 0 || i >= GRID_SIZE || j < 0 || j >= GRID_SIZE || state(i,j) != EMPTY);
    }
    makeMove(state, i, j, aiMove);
  }

  system("cls");
  state.print();

  if(w == CROSS)
    printf("Computer won!\n");
  else if(w == ZERO)
    printf("You won!\n");
  else
    printf("Tie!\n");

  return 0;
}

int main2() {
  char str[] = "XXOOX  O ";
  State state(str);
  state.print();
  int moves = 0;
  int i, j, s = chooseMove(state, true, -2, 2, i, j, moves);
  printf("%d %d %d\n", s, i, j);
  return 0;
}
