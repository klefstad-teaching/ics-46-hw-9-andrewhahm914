#include "ladder.h"


// g++ -std=c++17 ladder_main.cpp ladder.cpp -o ladder


using namespace std;

void error(string word1, string word2, string msg) {
    std::cout << "Error: " << msg << word1 << word2 << std::endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    if (d < 0) {
        return false;
    }

    if (abs(int(str1.size()) - abs(int(str2.size()))) > d){
        return false;
    }

    if (str1.empty() || str2.empty()) {
        return (str1.size() + str2.size()) <= d;
    }

    if (str1[0] == str2[0]) {
        return edit_distance_within(str1.substr(1), str2.substr(1), d);
    }

    else {
        return edit_distance_within(str1, str2.substr(1), d - 1) || edit_distance_within(str1.substr(1), str2, d - 1) || edit_distance_within(str1.substr(1), str2.substr(1), d - 1); 
    }
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}



vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) {
        return vector<string> empty;
        return empty;
    }

    queue<vector<string>> ladder_q;
    unordered_set<string> visited;

    ladder_q.push({begin_word});
    visited.insert(begin_word);

    while (!ladder_q.empty()) {
        vector<string> ladder = ladder_q.front();
        ladder_q.pop();
        string lastWord = ladder.back();

        
        for (string word : word_list) {
            if (is_adjacent(lastWord, word) && visited.find(word) == visited.end()) {
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                visited.insert(word);

                if (word == end_word) {
                    return new_ladder;
                }

                ladder_q.push(new_ladder);
            }
        }
    }

    vector<string> empty;
    return empty;
}


void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);

    if (!file.is_open()) {
        cerr << "Unable to open the file." << file_name << endl;
        return;
    }

    std::string word;
    while (file >> word) {
        word_list.insert(word);
    }

    file.close();
}


void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
    } 
    
    else {
        cout << "Word ladder found: ";
        for (const auto& word : ladder) {
            cout << word << " ";
        }
        cout << endl;
    }
}


    

void verify_word_ladder() {

    set<string> word_list;

    load_words(word_list, "words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);

}
