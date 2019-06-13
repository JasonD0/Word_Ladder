#ifndef ASSIGNMENTS_WL_WORD_LADDER_H_
#define ASSIGNMENTS_WL_WORD_LADDER_H_

#include <unordered_map>
//std::vector<std::vector<std::string>> Bfs(std::string src, std::string dest, std::set<std::string>& lex);

void PrintWordLadders(const std::vector<std::vector<std::string>>& wls);
void PrintWordLadder(const std::vector<std::string>& wl);
void SortWordLadders(std::vector<std::vector<std::string>>& wls);
void CreateConnections(std::set<std::string>& lex, std::unordered_map<std::string, std::vector<std::string>>& connections);
void CreateEdges(std::unordered_map<std::string, std::vector<std::string>>& connections, std::unordered_map<std::string, std::vector<std::string>>& graph);
std::unordered_map<std::string, std::vector<std::string>> CreateGraph(std::set<std::string>& lex);
std::vector<std::vector<std::string>> Bfs(std::string src, std::string dest, std::unordered_map<std::string, std::vector<std::string>>& graph);

#endif  // ASSIGNMENTS_WL_WORD_LADDER_H_
