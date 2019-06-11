#ifndef ASSIGNMENTS_WL_WORD_LADDER_H_
#define ASSIGNMENTS_WL_WORD_LADDER_H_

// TODO(students): Add some stuff here
std::queue<std::vector<std::string>> Bfs(std::string src, std::string dest, std::set<std::string>& lex);
void PrintWordLadders(std::queue<std::vector<std::string>>& wls);
void PrintWordLadder(std::vector<std::string>& wl);

#endif  // ASSIGNMENTS_WL_WORD_LADDER_H_
