#ifndef ASSIGNMENTS_WL_WORD_LADDER_H_
#define ASSIGNMENTS_WL_WORD_LADDER_H_

#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using Graph = std::unordered_map<std::string, std::set<std::string>>;
using Connections = std::unordered_map<std::string, std::vector<std::string>>;
using WordLadders = std::vector<std::vector<std::string>>;
using WordLadder = std::vector<std::string>;
using Lexicon = std::unordered_set<std::string>;

void PrintWordLadders(const WordLadders& wls);
void SortWordLadders(WordLadders& wls);
Graph CreateGraph(Lexicon& lex, std::string src);
WordLadders Bfs(std::string src, std::string dest, Graph& graph);

#endif  // ASSIGNMENTS_WL_WORD_LADDER_H_
