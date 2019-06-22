#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "assignments/wl/word_ladder.h"

void PrintWordLadder(const WordLadder& wl);
void SortWordLadders(WordLadders& wls);
void FindConnections(Lexicon& lex, std::string src, Connections& connections);
void CreateEdges(Connections& connections, Graph& graph);
void MakeEdge(Graph& graph, std::string v1, std::string v2);

/**
 * Connect all words that differ by one letter
 *
 * @param lex           lexicon
 * @param src           start word of the word ladder
 * @param connections   map of words in the lexicon with an empty slot and other
 *                      words that can regex match it
 */
void FindConnections(Lexicon& lex, std::string src, Connections& connections) {
  int req_len = src.size(), len = 0;

  for (const auto& word : lex) {
    len = word.size();
    if (req_len != len)
      continue;

    for (int i = 0; i < len; i++) {
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

/**
 * Make an edge between all pair of words that differ by one letter
 *
 * @param connections   map of words that differ by one letter
 * @param graph         graph representing the connections
 */
void CreateEdges(Connections& connections, Graph& graph) {
  for (auto pair = connections.begin(); pair != connections.end(); ++pair) {
    const std::vector<std::string> edges = pair->second;

    for (const auto& v1 : edges) {
      for (const auto& v2 : edges) {
        if (v1.compare(v2) == 0)
          continue;

        MakeEdge(graph, v1, v2);
        MakeEdge(graph, v2, v1);
      }
    }
  }
}

/**
 * Make an between two vertices in the graph
 *
 * @param graph
 * @param v1      vertex A
 * @param v2      vertex B
 */
void MakeEdge(Graph& graph, std::string v1, std::string v2) {
  auto itr = graph.find(v1);
  if (itr != graph.end()) {
    (itr->second).insert(v2);

  } else {
    graph.emplace(v1, std::set<std::string>{v2});
  }
}

/**
 * Create a graph from the lexicon
 *
 * @param lex   lexicon
 * @param src   start word of the word ladder
 * @return      map between words in the lexicon (vertices) and words that
 *              differ from it by one letter (adjacent vertices)
 */
Graph CreateGraph(Lexicon& lex, std::string src) {
  Connections connections;
  Graph graph;

  FindConnections(lex, src, connections);
  CreateEdges(connections, graph);

  return graph;
}

/**
 * Breadth First Search algorithm that finds all shortest word ladders from src
 * to dest
 *
 * @param src     start word
 * @param dest    end word
 * @param graph   map between vertices and it's adjacent vertices
 * @return        vector of all shortest word ladders
 */
WordLadders Bfs(std::string src, std::string dest, Graph& graph) {
  if (src.compare(dest) == 0) {
    return WordLadders{{src, dest}};
  }

  std::queue<WordLadder> wls;
  WordLadders result;
  std::unordered_map<std::string, int> visited;
  int shortest_len = 0, curr_len = 0;

  wls.push({src});
  visited.emplace(src, 1);

  while (!wls.empty()) {
    const WordLadder wl = wls.front();
    wls.pop();

    /*
     * End algorithm when all words ladders of the same length as the shortest
     * found word ladder have been searched
     */
    curr_len = wl.size();
    if (shortest_len && curr_len >= shortest_len)
      break;

    const std::string word = wl.back();

    auto it = graph.find(word);
    if (it != graph.end()) {
      auto edges = it->second;

      for (const auto& v : edges) {
        /* Destination word reached */
        if (v.compare(dest) == 0) {
          WordLadder new_wl = wl;
          new_wl.push_back(v);
          result.push_back(new_wl);
          shortest_len = new_wl.size();
          break;

          /*
           * Prevent extending word ladders that uses words used in shorter word
           * ladders
           */
        } else {
          auto itr = visited.find(v);
          if (itr != visited.end() && itr->second < curr_len) {
            graph.erase(v);
            continue;
          }
        }

        /* Explore the new extended word ladder */
        WordLadder new_wl = wl;
        new_wl.push_back(v);
        visited.emplace(v, new_wl.size());
        wls.push(new_wl);
      }
    }

    if (curr_len == 1)
      graph.erase(src);
  }

  return result;
}

/**
 * Sort word ladders alphabetically
 *
 * @param wls   vector of word ladders
 */
void SortWordLadders(WordLadders& wls) {
  std::sort(wls.begin(), wls.end());
}

/**
 * Shows all word ladders
 *
 * @param wls   vector of word ladders
 */
void PrintWordLadders(const WordLadders& wls) {
  if (wls.empty()) {
    std::cout << "No ladder found.\n";
    return;
  }

  std::cout << "Found ladder: ";
  for (const auto& wl : wls) {
    PrintWordLadder(wl);
    std::cout << "\n";
  }
}

/**
 * Shows the word ladder
 *
 * @param wl    word ladder
 */
void PrintWordLadder(const WordLadder& wl) {
  for (const auto& word : wl) {
    std::cout << word << " ";
  }
}
