#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

#include "assignments/wl/lexicon.h"
#include "assignments/wl/word_ladder.h"

int main() {
  auto lexicon = GetLexicon("assignments/wl/words.txt");

  std::string src, dest;

  std::cout << "Enter start word (RETURN to quit): ";
  std::cin >> src;
  if (src.compare("RETURN") == 0) return 0;

  std::cout << "Enter destination word: ";
  std::cin >> dest;

  /* filter words of the same length as src */
  std::set<std::string> new_lexicon;
  std::copy_if(lexicon.begin(), lexicon.end(),
               std::inserter(new_lexicon, new_lexicon.end()),
               [=](std::string s){return s.size() == src.size();});

  auto graph = CreateGraph(new_lexicon);
//  std::vector<std::vector<std::string>> wls = Bfs(src, dest, new_lexicon);

  std::vector<std::vector<std::string>> wls = Bfs(src, dest, graph);
  SortWordLadders(wls);

  PrintWordLadders(wls);

  return 0;
}
