#include <iostream>
using namespace std;
#define MAX_N 100

int graph[MAX_N+1][MAX_N+1];

int main() {
  int n;
  int u,k,v;
  cin >> n;

  for(int i=0;i<n;i++) {
    cin >> u >> k;
    for(int j=0;j<k;j++) {
      cin >> v;
      if(graph[u][v] == 0)
        graph[u][v] = 1;
    }
  }

  for(int i=1;i<=n;i++) {
    for(int j=1;j<=n;j++) {
      cout << graph[i][j] << (j==n ? "\n" : " ");
    }
  }
}