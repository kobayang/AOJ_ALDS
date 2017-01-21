#include <iostream>
#include <vector>
using namespace std;

struct Node {
  int id;
  int depth;
  int height;
  int parent;
  int left;
  int right;
  Node(int id,int left,int right) {
    this->id = id;
    this->left = left;
    this->right = right;
    this->height = -1;
    this->depth = -1;
    this->parent = -1;
  }
  void regist_parent(int parent) {
    this->parent = parent;
  }
  void regist_height(int height) {
    this->height = height;
  }
  void regist_depth(int depth) {
    this->depth = depth;
  }
};

Node* return_parent(vector<Node*>& node_list,int n) {
  Node* current = node_list[0];
  while(true) {
    bool is_parent = true;
    // 経路が必ず存在するのでParentまで到達する
    for(int i=0;i<n;i++) {
      int left = node_list[i]->left;
      int right = node_list[i]->right;
      if(left == current->id || right == current->id) {
        current = node_list[i];
        is_parent = false;
      }
    }
    if(is_parent) {
      current->regist_parent(-1);
      current->regist_depth(0);
      return current;
    }
  }
  return NULL;
}

void search_depth_from_parent(Node* node, vector<Node*> &node_list) {
  if(node->left == -1 && node->right == -1) {
    return;
  }
  int parent = node->id;
  int depth = node->depth + 1;
  if(node->left != -1) {
    node_list[node->left]->regist_parent(parent);
    node_list[node->left]->regist_depth(depth);
    search_depth_from_parent(node_list[node->left],node_list);
  }
  if(node->right != -1) {
    node_list[node->right]->regist_parent(parent);
    node_list[node->right]->regist_depth(depth);
    search_depth_from_parent(node_list[node->right],node_list);
  }
}

void search_height_from_leaf(Node* leaf,vector<Node*> &node_list,int n) {
  int height = 0;
  leaf->regist_height(0);
  Node* current = leaf;
  while(true) {
    if(current->height < height) {
      current->regist_height(height);
    }

    if(current->parent != -1) {
      current = node_list[current->parent];
      height++;
    }
    else {
      return;
    }
  }
  return;
}

int main() {
  int n; cin >> n;
  vector<Node*> node_list(n,NULL);

  for(int i=0;i<n;i++) {
    int id; cin >> id;
    int left,right; cin >> left >> right;

    // Nodeの仮登録
    node_list[id] = new Node(id,left,right);
  }

  Node* parent = return_parent(node_list,n);
  search_depth_from_parent(parent,node_list);
  for(int i=0;i<n;i++) {
    if(node_list[i]->left == -1 && node_list[i]->right == -1)
      search_height_from_leaf(node_list[i],node_list,n);
  }

  for(int i=0;i<n;i++) {
    cout << "node " << node_list[i]->id << ": ";

    cout << "parent = " << node_list[i]->parent << ", ";

    bool has_sibling = false;
    if(node_list[i]->parent != -1) {
      Node* parent = node_list[node_list[i]->parent];
      if(parent->left != -1 && parent->left != i) {
        cout << "sibling = " << parent->left << ", ";
        has_sibling = true;
      }
      else if(parent->right != -1 && parent->right != i) {
        cout << "sibling = " << parent->right << ", ";
        has_sibling = true;
      }
    }
    if(!has_sibling)
      cout << "sibling = " << -1 << ", ";

    int degree = 0;
    if(node_list[i]->left != -1) degree++;
    if(node_list[i]->right != -1) degree++;
    cout << "degree = " << degree << ", ";

    cout << "depth = " << node_list[i]->depth << ", ";

    cout << "height = " << node_list[i]->height << ", ";

    if(node_list[i]->parent == -1) {
      cout << "root";
    }
    else if(degree == 0) {
      cout << "leaf";
    }
    else {
      cout << "internal node";
    }
    cout << endl;
  }
}