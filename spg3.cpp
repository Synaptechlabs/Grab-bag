#include <iostream>
#include <map>
#include <memory>
#include <string>

struct Node {
  std::string value;

  std::map<std::string, std::shared_ptr<Node>> next;
  std::map<std::string, std::shared_ptr<Node>> prev;

  std::map<std::string, int> forwardFreq;  // path ID → count
  std::map<std::string, int> backwardFreq; // path ID → count

  explicit Node(const std::string &val) : value(val) {}

  // Choose next node in this path using max frequency * context bias
  std::shared_ptr<Node> chooseNext(const std::map<std::string, float> &bias) {
    int maxScore = -1;
    std::shared_ptr<Node> chosen = nullptr;

    for (const auto &[path, nextNode] : next) {
      int freq = forwardFreq.count(path) ? forwardFreq.at(path) : 0;
      float weight = bias.count(path) ? bias.at(path) : 1.0f;
      int score = static_cast<int>(freq * weight);
      if (score > maxScore) {
        maxScore = score;
        chosen = nextNode;
      }
    }
    return chosen;
  }
};

class SentenceList {
public:
  explicit SentenceList(const std::string &listId) : id(listId) {}

  void append(const std::shared_ptr<Node> &node) {
    if (!head) {
      head = node;
    } else {
      // Link and reinforce
      tail->next[id] = node;
      node->prev[id] = tail;

      // Frequency update
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
  // Shared nodes
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

  // Sentence 1: The cat sat on the mat
  SentenceList s1("s1");
  s1.append(the);
  s1.append(cat);
  s1.append(sat);
  s1.append(on);
  s1.append(mat);

  // Sentence 2: A cat has four legs
  SentenceList s2("s2");
  s2.append(a);
  s2.append(cat);
  s2.append(has);
  s2.append(four);
  s2.append(legs);

  // Sentence 3: She sat on the chair
  SentenceList s3("s3");
  s3.append(she);
  s3.append(sat);
  s3.append(on);
  s3.append(chair);

  // Sentence 4: She talked to her cat
  SentenceList s4("s4");
  s4.append(she);
  s4.append(talked);
  s4.append(to);
  s4.append(her);
  s4.append(cat); // shared node

  // Print each sentence
  std::cout << "Sentence 1: ";
  s1.printForward();
  std::cout << "Sentence 2: ";
  s2.printForward();
  std::cout << "Sentence 3: ";
  s3.printForward();
  std::cout << "Sentence 4: ";
  s4.printForward();

  // Bias test at node "cat"
  std::cout << "\nDecision at 'cat':\n";
  std::map<std::string, float> bias = {
      {"s1", 1.0f}, {"s2", 0.5f}, {"s4", 1.2f}};
  auto nextFromCat = cat->chooseNext(bias);
  if (nextFromCat) {
    std::cout << "Best next token: " << nextFromCat->value << "\n";
  } else {
    std::cout << "No available next node.\n";
  }

  return 0;
}
