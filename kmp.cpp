#include <iostream>
#include <vector>
using namespace std;

void GetNext(const string& pattern, vector<int>& next) {
    next[0] = -1;
    int cur_index = 0;
    int jump_index = -1;
    while(cur_index < next.size() - 1) {
        if(jump_index == -1 || pattern[cur_index] == pattern[jump_index]) {
            ++jump_index;
            next[++cur_index] = jump_index;
        } else {
            jump_index = next[jump_index];
        }
    }
}

void Kmp(const string& text, const string& pattern, vector<int>& pos) {
    int pattern_len = pattern.size();
    int text_len = text.size();
    vector<int> next(pattern_len);
    GetNext(pattern, next);
    int text_index = 0, pattern_index = 0;
    while(text_index < text_len) {
        if(pattern_index == -1 || text[text_index] == pattern[pattern_index]) {
            if(pattern_index == pattern_len-1) {
                pos.push_back(text_index - pattern_len + 1);
                pattern_index = next[pattern_index];
                continue;
            }
            ++text_index;
            ++pattern_index;
        } else {
            pattern_index = next[pattern_index];
        }
    }
}
int main() {
    string text = "abaababccabce";
    string pattern = "abc";
    vector<int> pos;
    Kmp(text, pattern, pos);
    for(int i = 0; i < pos.size(); ++i) {
        cout << pos[i] << endl;
    }
}
