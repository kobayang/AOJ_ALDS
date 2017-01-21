#include <iostream>
using namespace std;

#define MAX_N 500000
#define MAX_L 250000
#define MAX_R 250000

int cnt = 0;
int A[MAX_N+1];
int L[MAX_L+1];
int R[MAX_R+1];

void merge(int left, int mid, int right) {
  int n1 = mid - left;
  int n2 = right - mid;
  for(int i=0;i<n1;i++) {
    L[i] = A[left+i];
  }
  for(int i=0;i<n2;i++) {
    R[i] = A[mid+i];
  }
  L[n1] = 0x7FFFFFFF;
  R[n2] = 0x7FFFFFFF;
  int i = 0; int j = 0;
  for(int k=left;k<right;k++) {
    cnt++;
    if(L[i] <= R[j]) {
      A[k] = L[i];
      i++;
    }
    else {
      A[k] = R[j];
      j++;
    }
  }
}
void merge_sort(int left, int right) {
  if(right - left > 1) {
    int mid = (left + right) / 2;
    merge_sort(left, mid);
    merge_sort(mid, right);
    merge(left, mid, right);
  }
}

int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(false);

  int n;
  cin >> n;
  for(int i=0;i<n;i++) {
    cin >> A[i];
  }
  merge_sort(0, n);
  for(int i=0;i<n;i++) {
    cout << A[i] << (i+1 == n ? "" : " ");
  }
  cout << endl;
  cout << cnt << endl;

  // 4999950000
}