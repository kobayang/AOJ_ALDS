#include <iostream>
#include <vector>
using namespace std;

struct Node {
  int id;
  int left;
  int right;
  Node(int id) {
    this->id = id;
    this->left = -1;
    this->right = -1;
  }
};
void crawl_postorder(vector<Node*> &node_list, vector<int> &order_list, Node* node) {
  if(node->left != -1) {
    crawl_postorder(node_list,order_list,node_list[node->left]);
  }
  if(node->right != -1) {
    crawl_postorder(node_list,order_list,node_list[node->right]);
  }
  order_list.push_back(node->id);
  return;
}

int main() {
  /* input */
  int n; cin >> n;
  vector<int> pre_list(n);
  vector<int> in_list(n);
  for(int i=0;i<n;i++)
    cin >> pre_list[i];
  for(int i=0;i<n;i++)
    cin >> in_list[i];

  /* construct tree */
  vector<Node*> node_list(n+1,NULL);
  int root_id = pre_list[0];
  node_list[root_id] = new Node(root_id);
  for(int i=1;i<n;i++) {
    int pre_id = pre_list[i];
    node_list[pre_id] = new Node(pre_id);

    int pre2in_index;
    for(int j=0;j<n;j++) {
      if(pre_list[i] == in_list[j]) {
        pre2in_index = j;
        break;
      }
    }

    int in_left_index = -1;
    for(int j=pre2in_index-1;j>=0;j--) {
      if(node_list[in_list[j]] != NULL) {
        in_left_index = j;
        break;
      }
    }
    int in_right_index = -1;
    for(int j=pre2in_index+1;j<n;j++) {
      if(node_list[in_list[j]] != NULL) {
        in_right_index = j;
        break;
      }
    }

    int pre_left_index = -1;
    if(in_left_index != -1) {
      for(int j=0;j<n;j++) {
        if(pre_list[j] == in_list[in_left_index]) {
          pre_left_index = j;
          break;
        }
      }
    }
    int pre_right_index = -1;
    if(in_right_index != -1) {
      for(int j=0;j<n;j++) {
        if(pre_list[j] == in_list[in_right_index]) {
          pre_right_index = j;
          break;
        }
      }
    }

    int parent_id;
    if(pre_right_index > pre_left_index)
      parent_id = pre_list[pre_right_index];
    else
      parent_id = pre_list[pre_left_index];

    if(in_list[in_right_index] == parent_id)
      node_list[parent_id]->left = pre_id;
    else
      node_list[parent_id]->right = pre_id;

  }
  vector<int> order_list;
  crawl_postorder(node_list,order_list,node_list[root_id]);
  for(int i=0;i<n-1;i++) {
    cout << order_list[i] << " ";
  }
  cout << order_list[n-1] << endl;
}