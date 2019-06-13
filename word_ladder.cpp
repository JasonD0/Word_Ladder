#include <iostream>
#include <algorithm>
#include <string>
#include <set>
#include <vector>
#include <queue>
#include <unordered_map>

#include "assignments/wl/word_ladder.h"


void CreateConnections(std::set<std::string>& lex,
                     std::unordered_map<std::string, std::vector<std::string>>& connections) {

  for (const auto& word : lex) {
    const int len = word.size();
    for (int i = 0; i < len ; i++) {
      std::string reg = word;
      reg = reg.replace(i, 1, ".");

      auto it = connections.find(reg);
      if (it != connections.end()) {
        (it->second).push_back(word);

      } else {
        connections.emplace(reg, std::vector<std::string>{word});
      }
    }
  }
}


void CreateEdges(std::unordered_map<std::string, std::vector<std::string>>& connections,
               std::unordered_map<std::string, std::vector<std::string>>& graph) {

  for (auto pair = connections.begin(); pair != connections.end(); ++pair) {
    const std::vector<std::string> edges = pair->second;

    for (const auto& v1 : edges) {
      auto itr = graph.find(v1);

      for (const auto& v2 : edges) {
        if (v1.compare(v2) == 0) continue;

        if (itr != graph.end()) {
          (itr->second).push_back(v2);

        } else {
          graph.emplace(v1, std::vector<std::string>{v2});
        }
      }
    }
  }
}

std::unordered_map<std::string, std::vector<std::string>> CreateGraph(std::set<std::string>& lex) {

  std::unordered_map<std::string, std::vector<std::string>> connections;
  std::unordered_map<std::string, std::vector<std::string>> graph;

  CreateConnections(lex, connections);
  CreateEdges(connections, graph);

  return graph;
}

std::vector<std::vector<std::string>> Bfs(std::string src, std::string dest,
                                          std::unordered_map<std::string, std::vector<std::string>>& graph) {
  std::queue<std::vector<std::string>> wls;
  std::vector<std::vector<std::string>> result;
  std::unordered_map<std::string, int> visited;
  int shortest_len = 0, curr_len = 0;

  wls.push({src});
  visited.emplace(src, 1);

  while (!wls.empty()) {
    const std::vector<std::string> wl = wls.front();
    wls.pop();

    curr_len = wl.size();
    if (curr_len >= shortest_len && shortest_len) break;

    const std::string word = wl.back();


    auto it = graph.find(word);
    if (it != graph.end()) {
      auto edges = it->second;

      for (const auto& v : edges) {
        std::vector<std::string> new_wl = wl;
        new_wl.push_back(v);

        if (v.compare(dest) == 0) {
          result.push_back(new_wl);
          shortest_len = new_wl.size();
          break;

        } else {
          auto itr = visited.find(v);
          if (itr != visited.end() && itr->second < curr_len) {
            continue;
          }
        }

        visited.emplace(v, new_wl.size());
        wls.push(new_wl);
      }
    }

  }

  return result;
}

/**
 * Sort word ladders alphabetically
 * @param wls   vector of word ladders
 */
void SortWordLadders(std::vector<std::vector<std::string>>& wls) {

  std::sort(wls.begin(), wls.end());
}

/**
 * Shows all word ladders
 * @param wls   vector of word ladders
 */
void PrintWordLadders(const std::vector<std::vector<std::string>>& wls) {

  if (wls.empty()) {
    std::cout << "No ladder found.\n";
    return;
  }

  std::cout << "Found ladder: ";
  for (const auto& wl : wls) {
    PrintWordLadder(wl);
  }
}

/**
 * Shows the word ladder
 * @param wl    word ladder
 */
void PrintWordLadder(const std::vector<std::string>& wl) {

  for (const auto& word : wl) {
    std::cout << word << " ";
  }
  std::cout << "\n";
}
