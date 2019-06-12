#include <iostream>
#include <algorithm>
#include <string>
#include <set>
#include <vector>
#include <queue>
#include <unordered_map>

#include "assignments/wl/word_ladder.h"

void InitGraph(std::set<std::string>& lex) {
  std::unordered_map<std::string, std::vector<std::string>> connections;

  for (const auto& word : lex) {
     int len = word.size();
     for (int i = 0; i < len ; i++) {
         std::string reg = word;
         reg = reg.replace(i, 1, ".");

         auto it = connections.find(reg);
         if (it != connections.end()) {
           (*it).push_back(word);
         } else {
           connections.emplace(reg, word);
         }
     }
  }

  for (const auto& reg : connections) {
    it = connections.find(reg);
    std::vector<std::string> edges = *it;
    for (const auto& v1 : edges) {
      for (const auto& v2 : edges) {
        if (v1.compare(v2) == 0) continue;

        auto itr = graph.find(v1);
        if (itr != graph.end()) {
         (*itr).push_back(v2);
        } else {
          graph.emplace(v1, v2);
        }
      }
    }
  }
}

/**
 * Performs breadth first search to obtain all word ladders from src to dest
 * @param src   start word of the word ladder
 * @param dest  final word of the word ladder
 * @param lex   lexicon
 * @return      vector of word ladders
 */
std::vector<std::vector<std::string>> Bfs(std::string src, std::string dest, std::set<std::string>& lex) {
  std::queue<std::vector<std::string>> wls;
  std::vector<std::vector<std::string>> result;
  std::unordered_map<std::string, int> visited;
  int min_ladder_len = 0, curr_ladder_len = 0;

  wls.push({src});
  visited.insert_or_assign(src, 1);

  while (!wls.empty()) {
    const std::vector<std::string> wl = wls.front();
    wls.pop();

    /* End algorithm when curr ladder is longer than the shortest found ladder */
    curr_ladder_len = wl.size();
    if (curr_ladder_len >= min_ladder_len && min_ladder_len) break;

    const std::string parent_word = wl.back();
    std::string newWord = wl.back();
    std::vector<std::string> new_wl = wl;
    const int len = parent_word.length();

    /* Generate all possible valid words to extend the current word ladder */
    for (int index = 0; index < len; index++) {

      for (int letter = 97; letter < 123; letter++)  {
        /* Generate new word from parent word and append to word ladder */
        newWord = parent_word;
        newWord = newWord.replace(index, 1, std::string(1, letter));
        new_wl = wl;
        new_wl.push_back(newWord);

        /* Destination word generated */
        if (newWord.compare(dest) == 0) {
          result.push_back(new_wl);
          min_ladder_len = new_wl.size();
          break;

        /* Check new word is valid and not visited in a shorter path */
        } else {
          auto itr = visited.find(newWord);
          if (lex.find(newWord) == lex.end() ||
              (itr != visited.end() && itr->second < curr_ladder_len)) continue;
        }

        visited.insert_or_assign(newWord, wl.size());
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
void PrintWordLadders(std::vector<std::vector<std::string>>& wls) {
  if (wls.empty()) {
    std::cout << "No ladder found.\n";
    return;
  }

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
