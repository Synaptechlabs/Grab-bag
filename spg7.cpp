#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace SPHG {

struct Node {
  std::string value;
  std::map<std::string, std::shared_ptr<Node>> next;
  std::map<std::string, std::shared_ptr<Node>> prev;
  std::map<std::string, int> forwardFreq;
  std::map<std::string, int> backwardFreq;

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

class Engine {
public:
  void addNode(const std::shared_ptr<Node> &node) {
    allNodes.push_back(node);
    nodeMap[node->value] = node;
  }

  std::shared_ptr<Node> getOrCreateNode(const std::string &word) {
    if (nodeMap.count(word))
      return nodeMap[word];
    auto newNode = std::make_shared<Node>(word);
    addNode(newNode);
    return newNode;
  }

  void tick() {
    for (auto &node : allNodes)
      node->decay();
    for (auto &node : allNodes) {
      if (node->fire()) {
        for (const auto &[path, target] : node->next) {
          float weight = static_cast<float>(node->forwardFreq[path]);
          target->receiveInput(node->activation * weight);
        }
      }
    }
  }

  void printActivations(int tickNumber) const {
    std::cout << "Tick " << tickNumber << ": ";
    for (const auto &node : allNodes) {
      if (node->activation > 0.01f)
        std::cout << node->value << "(" << node->activation << ") ";
    }
    std::cout << std::endl;
  }

  void learnInput(const std::string &input, const std::string &pathID) {
    std::istringstream iss(input);
    std::string word;
    SentenceList path(pathID);
    while (iss >> word) {
      std::transform(word.begin(), word.end(), word.begin(), ::tolower);
      auto node = getOrCreateNode(word);
      path.append(node);
      node->receiveInput(1.0f); // seed activation
      lastInputNode = node;     // track last node seen
    }
  }

  std::string generateResponse() {
    std::string output;
    std::shared_ptr<Node> maxNode = lastInputNode; // prefer recent input

    if (!maxNode || maxNode->activation < 0.01f) {
      float maxActivation = 0.0f;
      for (const auto &node : allNodes) {
        if (!node->next.empty() && node->activation > maxActivation) {
          maxActivation = node->activation;
          maxNode = node;
        }
      }
    }

    std::map<std::string, bool> visited;
    while (maxNode && !visited[maxNode->value]) {
      output += maxNode->value + " ";
      visited[maxNode->value] = true;
      float maxScore = 0.0f;
      std::shared_ptr<Node> nextNode = nullptr;
      for (const auto &[path, target] : maxNode->next) {
        float score = target->activation * maxNode->forwardFreq[path];
        if (score > maxScore) {
          maxScore = score;
          nextNode = target;
        }
      }
      maxNode = nextNode;
    }

    return output;
  }

  void runChatLoop() {
    std::string line;
    int inputCount = 1;
    while (true) {
      std::cout << "you: ";
      std::getline(std::cin, line);
      if (line == "exit")
        break;

      std::string pathID = "u" + std::to_string(inputCount++);
      learnInput(line, pathID);

      for (int i = 0; i < 3; ++i)
        tick();

      std::string response = generateResponse();
      std::cout << "system: " << response << std::endl;
    }
  }

private:
  std::vector<std::shared_ptr<Node>> allNodes;
  std::map<std::string, std::shared_ptr<Node>> nodeMap;
  std::shared_ptr<Node> lastInputNode = nullptr;
};

} // namespace SPHG

int main() {
  SPHG::Engine engine;
  std::cout << "SPHG Interactive Chat (type 'exit' to quit)\n";
  engine.runChatLoop();
  return 0;
}
