#include "ladder.h"


// g++ -std=c++17 ladder_main.cpp ladder.cpp -o ladder


using namespace std;

void error(string word1, string word2, string msg) {
    std::cout << "Error: " << msg << word1 << word2 << std::endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int strlen1 = str1.length();
    int strlen2 = str2.length();

    if (abs(strlen1 - strlen2) > d)
        return false;

    int i = 0;
    int j = 0;
    int diff = 0;
    while (i < strlen1 && j < strlen2) {
        if (str1[i] != str2[j]) {
            diff++;
            
            if (diff > d) {
                return false;
            } 

            if (strlen1 > strlen2){
                i++;
            }

            else if (strlen1 < strlen2) {
                j++;
            }

            else {  
                i++;
                j++;
            }
        }

        else{
            i++;
            j++;
        }
    }
    diff += (strlen1 - i);
    diff += (strlen2 - j);

    return diff <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}



vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) {
        error(begin_word, end_word, "Words are the same");
        vector<string> empty;
        return empty;
    }

    queue<vector<string>> ladder_q;
    set<string> visited;

    ladder_q.push({begin_word});
    visited.insert(begin_word);

    while (!ladder_q.empty()) {
        vector<string> ladder = ladder_q.front();
        ladder_q.pop();
        string lastWord = ladder.back();

        
        for (string word : word_list) {
            if (is_adjacent(lastWord, word)){
                if (visited.find(word) == visited.end()) {
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    

                    if (word == end_word) {
                        return new_ladder;
                    }

                ladder_q.push(new_ladder);
                }
            }
        }
    }
    error(begin_word, end_word, "No word found");
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
    int size = ladder.size();

    if (size == 0) {
        std::cout << "No word ladder found." << std::endl;
        return;
    }

    std::cout << "Word ladder found: ";
    for (int i = 0; i < size; i++) {
        std::cout << ladder[i] << " ";
    }
    std::cout << std::endl;
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
