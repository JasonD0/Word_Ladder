/*

  == Explanation and rational of testing ==

  Explain and justify how you approached testing, the degree
   to which you're certain you have covered all possibilities,
   and why you think your tests are that thorough.

   Cover the basic scenarios and ensure the basic functionality
   of the interface provided works as intended. Ensuring no words appearing in
   shorter ladders and other complex scenarios is too difficult to test in
   isolation so it is excluded from testing. This makes test scenarios
   simple and makes checking implementation correctness simpler. Also, it is
   assumed that if the smaller cases work as intended, then the bigger cases
   also will, and only time and space complexity will be the issue.
   These tests definitely dont cover most possibilities due to the simplicity
   of these tests.

*/

#include "assignments/wl/word_ladder.h"
#include "catch.h"

SCENARIO("creating the graph") {
  GIVEN("a lexicon and a source word") {
    std::unordered_set<std::string> lexicon{"word", "rope", "cat", "failure", "hope", "role"};
    std::string src = "rope";

    WHEN("a graph is created") {
      auto graph = CreateGraph(lexicon, src);

      THEN("no words with different length as the source word is a vertex in the graph") {
        REQUIRE(graph.find("failure") == graph.end());
        REQUIRE(graph.find("cat") == graph.end());
      }

      THEN("words differing by one letter from another word is an adjacent vertex") {
        REQUIRE(graph.find("rope")->second == std::set<std::string>{"hope", "role"});
        REQUIRE(graph.find("hope")->second == std::set<std::string>{"rope"});
      }
    }
  }
}

SCENARIO("base cases for bfs") {
  GIVEN("a source word and a graph made from a lexicon") {
    std::unordered_set<std::string> lexicon{"word", "rope", "different"};
    std::string src = "rope";
    auto graph = CreateGraph(lexicon, src);

    GIVEN("a destination word the same as the source word") {
      std::string dest = src;

      WHEN("finding the shortest word ladders using bfs") {
        auto word_ladders = Bfs(src, dest, graph);

        THEN("the word ladder is simply the src and dest word") {
          REQUIRE(word_ladders == std::vector<std::vector<std::string>>{{"rope", "rope"}});
        }
      }
    }

    GIVEN("an unreachable destination from the source word") {
      std::string dest = "word";

      WHEN("finding the shortest word ladders using bfs") {
        auto word_ladders = Bfs(src, dest, graph);

        THEN("no word ladder is returned") { REQUIRE(word_ladders.size() == 0); }
      }
    }
  }
}

SCENARIO("single shortest word ladder") {
  GIVEN("two words and a graph made from a lexicon") {
    std::unordered_set<std::string> lexicon{"word",   "space", "ware", "wore",
                                            "filler", "rare",  "four", "care"};
    std::string src = "word";
    std::string dest = "rare";
    auto graph = CreateGraph(lexicon, src);

    WHEN("finding the shortest word ladders using bfs") {
      auto word_ladders = Bfs(src, dest, graph);

      THEN("the word ladder is of shortest length") { REQUIRE(word_ladders.at(0).size() == 4); }

      THEN("the difference between adjacent words is one letter") {
        REQUIRE(word_ladders ==
                std::vector<std::vector<std::string>>{{"word", "wore", "ware", "rare"}});
      }
    }
  }
}

SCENARIO("multiple shortest word ladders") {
  GIVEN("two words and a graph made from a lexicon") {
    std::unordered_set<std::string> lexicon{"word", "rope", "laid", "lard",
                                            "lain", "lord", "ward", "liar"};
    std::string src = "word";
    std::string dest = "laid";
    auto graph = CreateGraph(lexicon, src);

    WHEN("finding the shortest word ladders using bfs") {
      auto word_ladders = Bfs(src, dest, graph);

      THEN("there is the correct number of word ladders generated") {
        REQUIRE(word_ladders.size() == 2);
      }

      THEN("all ladders is of shortest length") {
        REQUIRE(word_ladders.at(0).size() == 4);
        REQUIRE(word_ladders.at(1).size() == 4);
      }

      THEN("a word can appear at the same position on different word ladders") {
        REQUIRE(word_ladders ==
                std::vector<std::vector<std::string>>{{"word", "lord", "lard", "laid"},
                                                      {"word", "ward", "lard", "laid"}});
      }
    }
  }
}
