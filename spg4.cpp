#include <cmath>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

struct Node {
  std::string value;
  std::map<std::string, std::shared_ptr<Node>> next;
  std::map<std::string, std::shared_ptr<Node>> prev;
  std::map<std::string, int> forwardFreq;
  std::map<std::string, int> backwardFreq;

  // Perceptron-style properties
  float activation = 0.0f;
  float threshold = 0.5f;
  float decayRate = 0.01f;
  float inputSum = 0.0f;

  explicit Node(const std::string &val) : value(val) {}

  void receiveInput(float value) { inputSum += value; }

  void decay() { activation *= (1.0f - decayRate); }

  bool fire() {
    activation = 1.0f / (1.0f + exp(-inputSum));
    inputSum = 0.0f;
    return activation >= threshold;
  }
};

class SentenceList {
public:
  explicit SentenceList(const std::string &listId) : id(listId) {}

  void append(const std::shared_ptr<Node> &node) {
    if (!head) {
      head = node;
    } else {
      tail->next[id] = node;
      node->prev[id] = tail;
      tail->forwardFreq[id]++;
      node->backwardFreq[id]++;
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

private:
  std::string id;
  std::shared_ptr<Node> head = nullptr;
  std::shared_ptr<Node> tail = nullptr;
};

void tick(std::vector<std::shared_ptr<Node>> &allNodes) {
  for (auto &node : allNodes) {
    node->decay();
  }
  for (auto &node : allNodes) {
    if (node->fire()) {
      for (const auto &[path, target] : node->next) {
        float weight = static_cast<float>(node->forwardFreq[path]);
        target->receiveInput(node->activation * weight);
      }
    }
  }
}

int main() {
  auto the = std::make_shared<Node>("The");
  auto a = std::make_shared<Node>("A");
  auto she = std::make_shared<Node>("She");
  auto cat = std::make_shared<Node>("cat");
  auto sat = std::make_shared<Node>("sat");
  auto has = std::make_shared<Node>("has");
  auto four = std::make_shared<Node>("four");
  auto legs = std::make_shared<Node>("legs");
  auto on = std::make_shared<Node>("on");
  auto mat = std::make_shared<Node>("mat");
  auto chair = std::make_shared<Node>("chair");
  auto talked = std::make_shared<Node>("talked");
  auto to = std::make_shared<Node>("to");
  auto her = std::make_shared<Node>("her");

  SentenceList s1("s1");
  s1.append(the);
  s1.append(cat);
  s1.append(sat);
  s1.append(on);
  s1.append(mat);

  SentenceList s2("s2");
  s2.append(a);
  s2.append(cat);
  s2.append(has);
  s2.append(four);
  s2.append(legs);

  SentenceList s3("s3");
  s3.append(she);
  s3.append(sat);
  s3.append(on);
  s3.append(chair);

  SentenceList s4("s4");
  s4.append(she);
  s4.append(talked);
  s4.append(to);
  s4.append(her);
  s4.append(cat);

  std::vector<std::shared_ptr<Node>> allNodes = {
      the, a, she, cat, sat, has, four, legs, on, mat, chair, talked, to, her};

  // Activate the "cat" node manually
  cat->receiveInput(2.0f); // initial stimulation

  std::cout << "\nActivation Ticks:\n";
  for (int i = 0; i < 5; ++i) {
    tick(allNodes);
    std::cout << "Tick " << i << ": ";
    for (const auto &node : allNodes) {
      if (node->activation > 0.01f)
        std::cout << node->value << "(" << node->activation << ") ";
    }
    std::cout << std::endl;
  }

  return 0;
}
