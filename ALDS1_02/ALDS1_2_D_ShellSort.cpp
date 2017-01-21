#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void insertion_sort(int A[],int N,int g,int *cnt) {
  for(int i=g;i<N;i++) {
    int v = A[i];
    int j = i - g;
    while(j >= 0 && A[j] > v) {
      A[j+g] = A[j];
      j = j - g;
      *cnt = *cnt + 1;
    }
    A[j+g] = v;
  }
}

void shell_sort(int A[],int N) {
  int cnt = 0;
  int m = 1;
  // h_i+1 = 3 * h_i + 1
  int G[13] = { 1, 4, 13, 40, 121, 364, 1093, 3280, 9841, 29524, 88573, 265720, 797161 };

  bool first = false;
  for(int i=12;i>=0;i--) {
    if(G[i] < N) {
      if(!first) {
        first = true;
        m = i + 1;
      }
      insertion_sort(A,N,G[i],&cnt);
    }
  }
  cout << m << endl;
  for(int i=m-1;i>=0;i--) {
    cout << G[i] << (i == 0 ? "" : " ");
  }
  cout << endl;

  cout << cnt << endl;
  for(int i=0;i<N;i++) {
    cout << A[i] << endl;
  }
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int N;
  int A[1000000];

  cin >> N;
  for(int i=0;i<N;i++) {
    cin >> A[i];
  }
  shell_sort(A,N);
}

