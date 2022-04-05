#include "assignment/binary_search_tree.hpp"

namespace assignment {

  BinarySearchTree::~BinarySearchTree() {
    BinarySearchTree::Clear();
  }

  void BinarySearchTree::Insert(int key, int value) {
    insert(key, value, root_);
  }

  bool BinarySearchTree::Remove(int key) {
    return remove(key, root_);
  }

  void BinarySearchTree::Clear() {
    clear(root_);
    root_ = nullptr;
  }

  std::optional<int> BinarySearchTree::Find(int key) const {
    Node* found_node = find(key, root_);
    if (found_node != nullptr) {
      return found_node->value;
    }
    return std::nullopt;
  }

  bool BinarySearchTree::Contains(int key) const {
    if (find(key, root_) == nullptr) {
      return false;
    }
    return true;
  }

  bool BinarySearchTree::IsEmpty() const {
    return root_ == nullptr;
  }

  std::optional<int> BinarySearchTree::FindMin() const {
    Node* node = find_min(root_);
    if (node != nullptr){
      return node->key;
    }
    return std::nullopt;
  }

  std::optional<int> BinarySearchTree::FindMax() const {
    Node* node = find_max(root_);
    if (node != nullptr){
      return node->key;
    }
    return std::nullopt;
  }

  Node* BinarySearchTree::root() const {
    return root_;
  }

  // вспомогательные методы

  void BinarySearchTree::insert(int key, int value, Node*& node) {
    if (node == nullptr){
      node = new Node(key, value);
      return;
    }
    if (key > node->key){
      return insert(key, value, node->right);
    }
    if (key < node->key){
      return insert(key, value, node->left);
    }
    node->value = value;
  }

  bool BinarySearchTree::remove(int key, Node*& node) {
    if (node == nullptr){
      return false;
    }

    if (key == node->key){

      if (node->left != nullptr and node->right != nullptr){
        Node* min = find_min(node->right);
        node->key = min->key;
        node->value = min->value;
        return remove(min->key, node->right);
      }

      if (node->left != nullptr or node->right == nullptr){
        Node* left_child = node->left;
        delete node;
        node = left_child;
        return true;
      }

      Node* right_child = node->right;
      delete node;
      node = right_child;
      return true;
    }

    if (key > node->key){
      return remove(key, node->right);
    }

    return remove(key, node->left);
  }

  void BinarySearchTree::clear(Node* node) {
    delete node;
    //node = nullptr;
  }

  Node* BinarySearchTree::find(int key, Node* node) const {
    if (node == nullptr) {
      return nullptr;
    }
    if (key == node->key) {
      return node;
    }
    if (key < node->key) {
      return find(key, node->left);
    }
    if (key > node->key) {
      return find(key, node->right);
    }
    return nullptr;
  }

  Node* BinarySearchTree::find_min(Node* node) const {
    if (node == nullptr) {
      return nullptr;
    }
    Node* curr_node = node;
    while (curr_node->left != nullptr){
      curr_node = curr_node->left;
    }
    return curr_node;
  }

  Node* BinarySearchTree::find_max(Node* node) const {
    if (node == nullptr) {
      return nullptr;
    }
    Node* curr_node = node;
    while (curr_node->right != nullptr){
      curr_node = curr_node->right;
    }
    return curr_node;
  }

}  // namespace assignment