//
// Created by fitli on 11.01.26.
//

#ifndef AOC2023_DAY06_H
#define AOC2023_DAY06_H
#include <regex>
#include <utility>
#include <iostream>
#include "../infra/Task.h"
class Day06: public Task
{
public:
    Day06(string name, const string& in_file) : Task(std::move(name), in_file) {};
    void run1(bool print_result) override {
        std::string line;
        vector<vector<int>> numbers;
        vector<string> operands;
        while (getline(_input, line)) {
            vector<string> tokens = split(line, ' ');
            if (tokens[0] == "+" or tokens[0] == "*") {
                operands = tokens;
                break;
            }
            vector<int> line_nums;
            ranges::transform(tokens, std::back_inserter(line_nums),
                              [](const string &s) { return stoi(s); });
            numbers.push_back(line_nums);
        }
        long long total = 0;
        for (int i = 0; i < operands.size(); ++i) {
            long long result;
            if (operands[i] == "+") {
                result = 0;
                for (auto & number : numbers) {
                    result += number[i];
                }
            } else {
                result = 1;
                for (auto & number : numbers) {
                    result *= number[i];
                }
            }
            total += result;
        }
        if (print_result)
            cout << total << std::endl;
    }
    void run2(bool print_result) override {

        if (print_result)
            cout << "todo" << std::endl;
    }

private:
};
#endif //AOC2023_DAY06_H