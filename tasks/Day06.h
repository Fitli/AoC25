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
        std::string line;
        vector<string> lines;
        while (getline(_input, line)) {
            lines.push_back(line);
        }

        long long total = 0;
        vector<long long> nums;
        char operand = ' ';
        for (int i = 0; i < lines[0].size(); ++i) {
            bool is_empty = true;
            long long num = 0;
            for (int j = 0; j < lines.size()-1; ++j) {
                if (lines[j][i] != ' ') {
                    is_empty = false;
                    num *= 10;
                    num += lines[j][i] - '0';
                }
            }
            char op_line_char = lines[lines.size()-1][i];
            if (op_line_char == '+' or op_line_char == '*') {
                operand = op_line_char;
            }
            if (is_empty) {
                long long result = get_result(nums, operand);
                total += result;
                nums.clear();
                operand = ' ';
            } else
                nums.push_back(num);
        }
        long long result = get_result(nums, operand);
        total += result;

        if (print_result)
            cout << total << std::endl;
    }

private:
    static long long get_result(const vector<long long> &numbers, char operand) {
        long long result = 0;
        if (operand == '+') {
            for (auto & number : numbers) {
                result += number;
            }
        }
        if (operand == '*') {
            result = 1;
            for (auto & number : numbers) {
                result *= number;
            }
        }
        return result;
    }
};
#endif //AOC2023_DAY06_H