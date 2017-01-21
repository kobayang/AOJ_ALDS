#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int bubble_sort(vector<int>& a,int N) {
  int cnt = 0;
  int flag = 1;
  while(flag) {
    flag = 0;
    for(int j=N-1;j>0;j--) {
      if(a[j-1] > a[j]) {
        swap(a[j-1],a[j]);
        flag = 1;
        cnt++;
      }
    }
  }
  return cnt;
}

int main(void) {
  int N;
  vector<int> a;

  /* input */
  cin >> N;
  for(int i=0;i<N;i++) {
    int _t;
    cin >> _t;
    a.push_back(_t);
  }

  int cnt = bubble_sort(a,N);
  for(int i=0;i<N;i++) {
    cout << a[i] << (i+1==N ? "" : " ");
  }
  cout << endl;
  cout << cnt << endl;
}