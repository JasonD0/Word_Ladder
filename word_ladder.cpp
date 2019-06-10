#include <string>
#include <set>
#include <vector>
#include <queue>
#include <iostream>

#include "assignments/wl/word_ladder.h"

void PrintWordLadder(std::vector<std::string>& wl);
void AddWordLadder(std::string nextWord, std::vector<std::string>& wl,
                   std::queue<std::vector<std::string>>& wls,
                   std::set<std::string>& visited);


std::string Bfs(std::string src, std::string dest, std::set<std::string>& lex) {
  std::queue<std::vector<std::string>> wls;
  std::set<std::string> visited;

  wls.push({src});
  visited.insert(src);

  while (!wls.empty()) {
    std::vector<std::string> wl = wls.front();
    wls.pop();

    std::string parentWord = wl.back();

    // generate valid words
    int len = parentWord.length();
    for (int index = 0; index < len; index++) {

      for (int letter = 97; letter < 123; letter++)  {
        std::string newWord = parentWord;
        newWord = newWord.replace(index, 1, std::string(1, letter));

        // Check new word is valid and not visited in a shorter path
        if (lex.find(newWord) == lex.end() ||
            visited.find(newWord) != visited.end()) continue;

        // goal state
        if (newWord.compare(dest) == 0) {
          wl.push_back(dest);
          PrintWordLadder(wl);
          return dest;
        }

        AddWordLadder(newWord, wl, wls, visited);
      }

    }
  }

  return src;
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

/**
 * Append next word in the word ladder to the queue
 * @param nextWord
 * @param wl
 * @param wls
 * @param visited
 */
void AddWordLadder(std::string nextWord, std::vector<std::string>& wl,
                   std::queue<std::vector<std::string>>& wls,
                   std::set<std::string>& visited) {
  visited.insert(nextWord);
  std::vector<std::string> newWl = wl;
  newWl.push_back(nextWord);
  wls.push(newWl);

}

