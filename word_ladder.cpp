#include <string>
#include <set>
#include <vector>
#include <queue>
#include <iostream>
#include <unordered_map>

#include "assignments/wl/word_ladder.h"


std::queue<std::vector<std::string>> Bfs(std::string src, std::string dest, std::set<std::string>& lex) {
  std::queue<std::vector<std::string>> wls, result;
  std::unordered_map<std::string, int> visited;
  int min_ladder_len = 0, curr_ladder_len = 0;

  wls.push({src});
  visited.insert_or_assign(src, 1);

  while (!wls.empty()) {
    std::vector<std::string> wl = wls.front();
    wls.pop();

    /* End algorithm when curr ladder is longer than the shortest found ladder */
    curr_ladder_len = wl.size();
    if (curr_ladder_len >= min_ladder_len && min_ladder_len) break;
    
    std::string parentWord = wl.back();

    // generate valid words
    int len = parentWord.length();
    for (int index = 0; index < len; index++) {

      // new function
      for (int letter = 97; letter < 123; letter++)  {
        std::string newWord = parentWord;
        newWord = newWord.replace(index, 1, std::string(1, letter));

        auto search = visited.find(newWord);

        // Check new word is valid and not visited in a shorter path
        if (lex.find(newWord) == lex.end() ||
            (search != visited.end() && search->second < curr_ladder_len)) continue;

        std::vector<std::string> newWl = wl;
        newWl.push_back(newWord);

        // goal state
        if (newWord.compare(dest) == 0) {
          result.push(newWl);
          min_ladder_len = newWl.size();
          break;
        }

        visited.insert_or_assign(newWord, wl.size());
        wls.push(newWl);
      }

    }
  }

  return result;
}

/**
 * Shows all the word ladders
 * @param wls
 */
void PrintWordLadders(std::queue<std::vector<std::string>>& wls) {
  while (!wls.empty()) {
    PrintWordLadder(wls.front());
    wls.pop();
  }
}

/**
 * Shows the word ladder
 * @param wl
 */
void PrintWordLadder(std::vector<std::string>& wl) {
  for (const auto& word : wl) {
    std::cout << word << " ";
  }
  std::cout << "\n";
}
