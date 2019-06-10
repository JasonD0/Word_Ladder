#include <string>
#include <set>
#include <vector>
#include <queue> 

#include "assignments/wl/word_ladder.h"

std::string bfs(std::string src, std::string dest, std::set<std::string>& lex) {
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

        // goal state
        if (newWord.compare(dest) == 0) {
          wl.push_back(dest);
          for (const auto&  word : wl) {
            std::cout << word << " ";
          }
          std::cout << "\n";
          return "finito";
        }

        // not valid word or visited
        if (lex.find(newWord) == lex.end() || visited.find(newWord) != visited.end()) continue;

        // add new word ladder to queue
        visited.insert(newWord);
        std::vector<std::string> newWl = wl;
        newWl.push_back(newWord);
        wls.push(newWl);
      }
    }
  }
  
  return "No path exists";
}