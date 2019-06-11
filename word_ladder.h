#ifndef ASSIGNMENTS_WL_WORD_LADDER_H_
#define ASSIGNMENTS_WL_WORD_LADDER_H_

std::vector<std::vector<std::string>> Bfs(std::string src, std::string dest, std::set<std::string>& lex);
void PrintWordLadders(std::vector<std::vector<std::string>>& wls);
void PrintWordLadder(const std::vector<std::string>& wl);
void SortWordLadders(std::vector<std::vector<std::string>>& wls);

#endif  // ASSIGNMENTS_WL_WORD_LADDER_H_