#include <string>
#include <iostream>
#include <sstream>
using namespace std;

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  string T,P;
  cin >> T;
  cin >> P;
  for(int it=0;it<T.length();it++) {
    int s = T.find(P,it);
    if(s != string::npos) {
      cout << s << "\n";
      it = s;
    }
    else {
      return 0;
    }
  }
}