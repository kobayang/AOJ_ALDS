// using A star algorithm
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <map>
using namespace std;
const int N = 16;
const int XY = 4;
const int LIMIT = 45;

vector<int> solve(N);
int dx[] = {0,-1,1,0};
int dy[] = {-1,0,0,1};

struct state {
  vector<int> board;
  int g;
  state(vector<int> &board,int g) {
    this->board = board;
    this->g = g;
  }
};
int h_func(state &s) {
  // using Manhattan distance
  int distance = 0;
  int solve_x,solve_y;
  int board_x,board_y;
  for(int i=0;i<N;i++) {
    for(int j=0;j<N;j++) {
      if(solve[i] == s.board[j]) {
        solve_x = i % XY; solve_y = i / XY;
        board_x = j % XY; board_y = j / XY;
        distance += abs(solve_x - board_x) + abs(solve_y - board_y);
        break;
      }
    }
  }
  return distance;
}
struct compare_state {
  bool operator() (state &a,state &b) {
    return (a.g + h_func(a)) > (b.g + h_func(b));
  }
};
priority_queue<state,vector<state>,compare_state> que;
map<vector<int>,int> cost_table;

bool is_infield(int x,int y) {
  return (x < XY && y < XY && x >= 0 && y >= 0);
}

int search(state &start) {
  // initialize process
  que.push(start);
  cost_table[start.board] = 0;
  while(!que.empty()) {
    state current = que.top(); que.pop();
    int distance = h_func(current);
    // approach goal
    if(distance == 0) {
      return current.g;
    }
    // not find goal
    if(current.g + distance > LIMIT) {
      continue;
    }
    // find zero brocks
    int zero_pos;
    for(int i=0;i<N;i++)
      if(current.board[i] == 0)
        zero_pos = i;
    int x = zero_pos % XY;
    int y = zero_pos / XY;
    // swap zero brocks and find next state
    for(int d=0;d<4;d++) {
      if(!is_infield(x+dx[d],y+dy[d])) continue;
      vector<int> next_board = current.board;
      swap(next_board[x+y*XY],next_board[(x+dx[d])+(y+dy[d])*XY]);
      // make and update cost table
      if(!cost_table.count(next_board)) {
        cost_table[next_board] = current.g + 1;
        state next = *(new state(next_board,current.g+1));
        que.push(next);
      }
      else {
        if((current.g+1) < cost_table[next_board]) {
          cost_table[next_board] = current.g + 1;
          state next = *(new state(next_board,current.g+1));
          que.push(next);
        }
      }
    }
  }
  return -1;
}

int main() {
  vector<int> start_vec(N,-1);
  for(int i=0;i<N;i++) {
    cin >> start_vec[i];
    solve[i] = i+1;
  }
  solve[N-1] = 0;

  state start = *(new state(start_vec,0));

  cout << search(start) << endl;
}