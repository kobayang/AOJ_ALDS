#include <iostream>
#include <stack>
#include <vector>
#include <utility>
using namespace std;

int main() {
  stack<pair<int,int> > ls;
  stack<pair<int,int> > ll;

  char c;
  int px = 0;
  int py = 0;
  while(cin >> c) {
    if(c == '\\') {
      ls.push( make_pair(px,py ) );
      py--;
    }
    else if(c == '/') {
      py++;
      if(!ls.empty()) {
        if(ls.top().second == py) {
          int w = 0;
          while(!ll.empty()) {
            if(ll.top().second > ls.top().first) {
              w += ll.top().first;
              ll.pop();
            }
            else {
              break;
            }
          }
          int st = ls.top().first;
          w += px - ls.top().first;
          ll.push( make_pair(w,st) );
          ls.pop();
        }
      }
    }
    px++;
  }

  // output
  vector<int> vec;
  int A = 0;
  int k = ll.size();
  while(!ll.empty()) {
    vec.push_back(ll.top().first);
    A += ll.top().first;
    ll.pop();
  }
  cout << A << endl;
  if(k == 0) {
    cout << k << endl;
  }
  else {
    cout << k << " ";
    for(int i=k-1;i>=0;i--) {
      cout << vec[i] << (i == 0 ? "" : " ");
    }
    cout << endl;
  }
}