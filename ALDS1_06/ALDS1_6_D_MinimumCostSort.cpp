#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
void merge(int A[],int left, int mid, int right) {
  int n1 = mid - left;
  int n2 = right - mid;
  int L[n1+1]; int R[n2+1];
  for(int i=0;i<n1;i++) {
    L[i] = A[left+i];
  }
  for(int i=0;i<n2;i++) {
    R[i] = A[mid+i];
  }
  L[n1] = R[n2] = 0x7FFFFFFF;
  int i = 0; int j = 0;
  for(int k=left;k<right;k++) {
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
void merge_sort(int A[],int left, int right) {
  if(right - left > 1) {
    int mid = (left + right) / 2;
    merge_sort(A,left, mid);
    merge_sort(A,mid, right);
    merge(A,left, mid, right);
  }
}

int search(int W[],int left,int right, int key) {
  for(int i=0;i<n;i++) {
    if(W[i] == key)
      return i;
  }
  return -1;
}
int binary_search(int Sorted[],int left,int right, int key) {
  while(right >= left) {
    int mid = (left+right)/2;
    if(Sorted[mid] == key)
      return mid;
    else if(Sorted[mid] < key)
      left = mid + 1;
    else
      right = mid - 1;
  }
  return -1;
}


int main() {
  cin >> n;
  int W[n]; int Sorted[n];
  for(int i=0;i<n;i++) {
    int num; cin >> num;
    W[i] = Sorted[i] = num;
  }
  merge_sort(Sorted,0,n);

  // algorithm : https://www.ipsj.or.jp/07editj/promenade/4506.pdf
  vector<int> R;
  for(int i=0;i<n;i++) {
    if(binary_search(Sorted,i,n,W[i]) != i)
      R.push_back(Sorted[i]);
  }
  int Smin = Sorted[0];
  int Rmin = R[0];
  int sum = 0;
  for(int i=0;i<R.size();i++) {
    sum += R[i];
  }
  int cost;
  if(R.size() > 1)
    cost = min(sum+Rmin*(R.size()-2),sum+Rmin+Smin*(R.size()+1));
  else
    cost = 0;

  cout << cost << endl;
}