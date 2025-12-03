//
// Created by ivana.krumlova on 2.12.2025.
//

#ifndef AOC2025_DAY01_H
#define AOC2025_DAY01_H


#include <map>
#include <regex>
#include <utility>
#include <iostream>
#include "../infra/Task.h"
class Day01: public Task
{
public:
    Day01(string name, const string& in_file) : Task(std::move(name), in_file) {};
    void run1(bool print_result) override {
        std::string line;
        int count = 0;
        int dial = 50;
        while (_input >> line) {
            int n = parse_number(line);
            dial += n;
            dial %= 100;
            if (dial == 0) {
                count++;
            }
        }
        if (print_result)
            cout << count << std::endl;
    }
    void run2(bool print_result) override {
        std::string line;
        int count = 0;
        int dial = 50;
        while (_input >> line) {
            int n = parse_number(line);
            if (dial == 0 and n < 0)
                dial = 100;
            dial += n;
            count += abs(dial / 100);
            if (dial <= 0) {
                count++;
            }
            dial %= 100;
            if (dial < 0)
                dial += 100;
        }
        if (print_result)
            cout << count << std::endl;
    }

private:
    int parse_number(string &line) {
        if (line[0] == 'L') {
            return -1 * std::stoi(line.substr(1));
        }
        else {
            return std::stoi(line.substr(1));
        }
    }
};


#endif //AOC2025_DAY01_H
