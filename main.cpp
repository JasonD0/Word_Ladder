#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

#include "assignments/wl/lexicon.h"
#include "assignments/wl/word_ladder.h"

int main() {
  auto lexicon = GetLexicon("assignments/wl/words.txt");

  std::string src, dest;

  std::cout << "Enter start word (RETURN to quit): ";
  std::cin >> src;
  if (src.compare("RETURN") == 0)
    return 0;

  std::cout << "Enter destination word: ";
  std::cin >> dest;

  Graph graph = CreateGraph(lexicon, src);
  WordLadders wls = Bfs(src, dest, graph);

  SortWordLadders(wls);

  PrintWordLadders(wls);

  return 0;
}
