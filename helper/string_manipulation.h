//
// Created by fitli on 11.01.26.
//

#ifndef AOC2023_STRING_MANIPULATION_H
#define AOC2023_STRING_MANIPULATION_H
#include <string>
#include <vector>

inline std::vector<std::string> split(std::string s, char delimiter) {
    int delimiter_pos;
    std::vector<std::string> tokens;
    while ((delimiter_pos = s.find(delimiter)) != std::string::npos) {
        if (delimiter_pos != 0)
            tokens.push_back(s.substr(0, delimiter_pos));
        s = s.substr(delimiter_pos + 1);
    }
    if (!s.empty()) {
        tokens.push_back(s);
    }
    return tokens;
}

#endif //AOC2023_STRING_MANIPULATION_H