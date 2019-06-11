#include <string>
#include <set>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
#include <utility>
#include <unordered_map>

#include "assignments/wl/word_ladder.h"

//TODO  share  shire  sharn     shire appears before sharn  (but need alphabet)  b/c  i changed before n
// use .sort(start, end, comparator func)  at end

std::vector<std::vector<std::string>> Bfs(std::string src, std::string dest, std::set<std::string>& lex) {
  std::queue<std::vector<std::string>> wls;
  std::vector<std::vector<std::string>> result;
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
          result.push_back(newWl);
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
 * Sort word ladders alphabetically
 * @param wls
 */
void SortWordLadders(std::vector<std::vector<std::string>>& wls) {
  std::sort(wls.begin(), wls.end());
}

/**
 * Shows all word ladders
 * @param wls
 */
void PrintWordLadders(std::vector<std::vector<std::string>>& wls) {
  for (const auto& wl : wls) {
    PrintWordLadder(wl);
  }
}

/**
 * Shows the word ladder
 * @param wl
 */
void PrintWordLadder(const std::vector<std::string>& wl) {
  for (const auto& word : wl) {
    std::cout << word << " ";
  }
  std::cout << "\n";
}
