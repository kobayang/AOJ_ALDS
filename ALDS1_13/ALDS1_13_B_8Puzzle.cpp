// using A star algorithm
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <map>
using namespace std;
const int N = 9;
const int XY = 3;
const int LIMIT = 45;

struct state {
  vector<int> board;
  int g;
  state(vector<int> &board) {
    this->board = board;
    this->g = 0;
  }
};
struct compare_state {
  int h_func(state &s) {
    // using Manhattan distance
    int distance = 0;
    vector<int> solve(N,0);
    for(int i=0;i<N;i++) {
      solve[i] = i+1;
    }
    solve[N-1] = 0;
    vector<int> board = s.board;
    int solve_x,solve_y;
    int board_x,board_y;
    for(int i=0;i<N;i++) {
      for(int j=0;j<N;j++) {
        if(solve[i] == board[j]) {
          solve_x = i % XY; solve_y = i / XY;
          board_x = j % XY; board_y = j / XY;
          distance += abs(solve_x - board_x) + abs(solve_y - board_y);
          break;
        }
      }
    }
    return distance;
  }
  bool operator() (state &a,state &b) {
    return (a.g + h_func(a)) > (b.g + h_func(b));
  }
};
priority_queue<state,vector<state>,compare_state> que;
map<vector<int>,int> cost_table;

bool check(state &current,state &end) {
  for(int i=0;i<N;i++) {
    if(current.board[i] != end.board[i])
      return false;
  }
  return true;
}

bool is_infield(int x,int y) {
  return (x < XY && y < XY && x >= 0 && y >= 0);
}

int search(state &start,state &end) {
  // initialize process
  que.push(start);
  cost_table[start.board] = 0;
  while(!que.empty()) {
    state current = que.top(); que.pop();
    // approach goal
    if(check(current,end)) {
      return current.g;
    }
    // not find goal
    if(current.g > LIMIT) {
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
    int dx[] = {0,-1,1,0};
    int dy[] = {-1,0,0,1};
    for(int d=0;d<4;d++) {
      if(!is_infield(x+dx[d],y+dy[d])) continue;
      vector<int> next_board = current.board;
      swap(next_board[x+y*XY],next_board[(x+dx[d])+(y+dy[d])*XY]);
      // make and update cost table
      if(!cost_table.count(next_board)) {
        cost_table[next_board] = current.g + 1;
        state next = *(new state(next_board));
        next.g = current.g + 1;
        que.push(next);
      }
      else {
        if((current.g+1) < cost_table[next_board]) {
          cost_table[next_board] = current.g + 1;
          state next = *(new state(next_board));
          next.g = current.g + 1;
          que.push(next);
        }
      }
    }
  }
  return -1;
}

int main() {
  vector<int> start_vec(N,-1);
  vector<int> end_vec(N,-1);
  for(int i=0;i<N;i++) {
    cin >> start_vec[i];
    end_vec[i] = i+1;
  }
  end_vec[N-1] = 0;

  state start = *(new state(start_vec));
  state end = *(new state(end_vec));

  cout << search(start,end) << endl;
}