#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

struct Node {
  std::string value;
  std::map<std::string, std::shared_ptr<Node>> next;
  std::map<std::string, std::shared_ptr<Node>> prev;
  std::map<std::string, float>
      decisionWeights; // Optional: per-path or per-token score
  std::map<std::string, std::string> tags; // Optional: POS, mood, etc.

  explicit Node(const std::string &val) : value(val) {}
};

class SentenceList {
public:
  SentenceList(const std::string &listId) : id(listId) {}

  void append(const std::shared_ptr<Node> &node) {
    if (!head) {
      head = node;
    } else {
      tail->next[id] = node;
      node->prev[id] = tail;
    }
    tail = node;
  }

  void printForward() const {
    auto curr = head;
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

  void printBackward() const {
    auto curr = tail;
    while (curr) {
      std::cout << curr->value;
      if (curr->prev.count(id)) {
        std::cout << " ← ";
        curr = curr->prev.at(id);
      } else {
        break;
      }
    }
    std::cout << std::endl;
  }

private:
  std::string id;
  std::shared_ptr<Node> head = nullptr;
  std::shared_ptr<Node> tail = nullptr;
};

int main() {
  // Create shared nodes
  auto the = std::make_shared<Node>("The");
  auto a = std::make_shared<Node>("A");
  auto cat = std::make_shared<Node>("cat");
  auto sat = std::make_shared<Node>("sat");
  auto has = std::make_shared<Node>("has");
  auto four = std::make_shared<Node>("four");
  auto legs = std::make_shared<Node>("legs");
  auto on = std::make_shared<Node>("on");
  auto mat = std::make_shared<Node>("mat");
  auto the2 = std::make_shared<Node>("the");

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

  // Print both directions
  std::cout << "Sentence 1 (forward): ";
  s1.printForward();
  std::cout << "Sentence 1 (backward): ";
  s1.printBackward();

  std::cout << "Sentence 2 (forward): ";
  s2.printForward();
  std::cout << "Sentence 2 (backward): ";
  s2.printBackward();

  return 0;
}
