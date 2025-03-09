#include "ladder.h"

using namespace std;

void error(string word1, string word2, string msg) {
    std::cout << "Error: " << msg << word1 << word2 << std::endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    // Implementation goes here
}

bool is_adjacent(const string& word1, const string& word2) {
    // Implementation goes here
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    // Implementation goes here
}

void load_words(set<string> & word_list, const string& file_name) {
    // Implementation goes here
}

void print_word_ladder(const vector<string>& ladder) {
    // Implementation goes here
}

void verify_word_ladder() {
    // Implementation goes here
}
