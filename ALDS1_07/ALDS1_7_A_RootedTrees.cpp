#include <iostream>
#include <vector>
using namespace std;

struct Tree {
  int node;
  int depth;
  int parent;
  vector<int> childs;
  Tree(int id,int depth,int parent,vector<int> childs) {
    this->node = id;
    this->depth = depth;
    this->parent = parent;
    this->childs = childs;
  }
  void fix_tree(int depth,int parent) {
    this->depth = depth;
    this->parent = parent;
  }
};

Tree* serach_parent(vector<Tree*>& trees,int n) {
  int index = 0;
  Tree* current = trees[0];
  while(true) {
    bool is_parent = true;
    // 経路が必ず存在するのでParentまで到達する
    for(int i=0;i<n;i++) {
      vector<int> childs = trees[i]->childs;
      for(int j=0;j<childs.size();j++) {
        if(childs[j] == index) {
          // 発見!
          index = i;
          current = trees[i];
          is_parent = false;
        }
      }
    }
    if(is_parent) {
      return current;
    }
  }
  return NULL;
}

void rec(Tree* tree, vector<Tree*> &trees) {
  if(tree->childs.size() == 0) {
    return;
  }
  int parent = tree->node;
  int depth = tree->depth + 1;
  for(int i=0;i<tree->childs.size();i++) {
    Tree* child = trees[tree->childs[i]];
    child->fix_tree(depth,parent);
    rec(child,trees);
  }
}

int main() {
  int n; cin >> n;
  vector<Tree*> tree_list(n,NULL);

  for(int i=0;i<n;i++) {
    int id,k; cin >> id >> k;
    vector<int> c(k);
    for(int j=0;j<k;j++)
      cin >> c[j];

    // Treeの仮登録
    tree_list[id] = new Tree(id,0,0,c);
  }

  Tree* parent = serach_parent(tree_list,n);
  parent->fix_tree(0,-1);
  rec(parent,tree_list);

  //node 0: parent = -1, depth = 0, root, [1, 4, 10]
  for(int i=0;i<n;i++) {
    cout << "node " << tree_list[i]->node << ": ";
    cout << "parent = " << tree_list[i]->parent << ", ";
    cout << "depth = " << tree_list[i]->depth << ", ";
    if(tree_list[i]->parent == -1) {
      cout << "root" << ", ";
    }
    else if(tree_list[i]->childs.size()==0) {
      cout << "leaf" << ", ";
    }
    else {
      cout << "internal node" << ", ";
    }
    cout << "[";
    int size = tree_list[i]->childs.size();
    if(size != 0) {
      for(int j=0;j<size-1;j++) {
        cout << tree_list[i]->childs[j] << ", ";
      }
      cout << tree_list[i]->childs[size-1];
    }
    cout << "]" << endl;
  }
}