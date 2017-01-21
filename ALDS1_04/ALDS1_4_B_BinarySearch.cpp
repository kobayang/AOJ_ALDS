#include <iostream>
#include <vector>
using namespace std;

bool binary_search(vector<int>& S,int st, int en, int key) {
  int bi;
  while(true) {
    bi = (st + en) / 2;
    if(S[bi] == key) {
      return true;
    }

    if(st == bi || en == bi) {
      break;
    }
    else if(S[bi] > key) {
      en = bi;
    }
    else if(S[bi] < key) {
      st = bi + 1;
    }
  }
  return false;
}

int main() {
  int n,q;
  vector<int> S,T;

  cin >> n;
  for(int i=0;i<n;i++) {
    int s;
    cin >> s;
    S.push_back(s);
  }
  cin >> q;
  for(int i=0;i<q;i++) {
    int t;
    cin >> t;
    T.push_back(t);
  }

  int C = 0;
  for(int t_itr=0;t_itr<q;t_itr++) {
    if(binary_search(S,0,n,T[t_itr])) {
      C++;
    }
  }

  cout << C << endl;
}