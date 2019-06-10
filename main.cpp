#include <iostream>

#include "assignments/wl/lexicon.h"
#include "assignments/wl/word_ladder.h"

int main() {
  auto lexicon = GetLexicon("assignments/wl/words.txt");

  std::string src, dest, wl;

  std::cout << "Enter start word (RETURN to quit): ";
  std::cin >> src;
  if (src.compare("RETURN") == 0) return 0;

  std::cout << "Enter destination: ";
  std::cin >> dest;

  wl = bfs(src, dest, lexicon);
  /*for (const auto& word : lexicon) {
    std::cout << word << '\n';
  }*/

  std::cout << "Found ladder: " << wl << "\n";

  return 0;
}
