#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

struct Node {
  std::string value;
  std::map<std::string, Node *> next;

  Node(const std::string &val) : value(val) {}
};

struct SentenceList {
  std::string id;
  Node *head = nullptr;
  Node *tail = nullptr;

  SentenceList(const std::string &listId) : id(listId) {}

  void append(Node *node) {
    if (!head) {
      head = node;
    } else {
      tail->next[id] = node;
    }
    tail = node;
  }

  void print() const {
    Node *curr = head;
    while (curr) {
      std::cout << curr->value;
      if (curr->next.count(id)) {
        std::cout << " → ";
        curr = curr->next.at(id);
      } else {
        break;
      }
    }
    std::cout << std::endl;
  }
};

int main() {
  // Shared nodes
  Node *the = new Node("The");
  Node *a = new Node("A");
  Node *cat = new Node("cat");
  Node *sat = new Node("sat");
  Node *has = new Node("has");
  Node *four = new Node("four");
  Node *legs = new Node("legs");
  Node *on = new Node("on");
  Node *mat = new Node("mat");
  Node *the2 = new Node("the");

  // Sentence 1: The cat sat on the mat
  SentenceList s1("s1");
  s1.append(the);
  s1.append(cat);
  s1.append(sat);
  s1.append(on);
  s1.append(the2);
  s1.append(mat);

  // Sentence 2: A cat has four legs
  SentenceList s2("s2");
  s2.append(a);
  s2.append(cat); // shared node
  s2.append(has);
  s2.append(four);
  s2.append(legs);

  std::cout << "Sentence 1: ";
  s1.print();
  std::cout << "Sentence 2: ";
  s2.print();

  // Cleanup (or use smart pointers in real implementation)
  delete the;
  delete a;
  delete cat;
  delete sat;
  delete has;
  delete four;
  delete legs;
  delete on;
  delete mat;
  delete the2;

  return 0;
}
