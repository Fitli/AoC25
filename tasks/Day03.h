//
// Created by fitli on 9.1.26.
//

#ifndef AOC25_DAY03_H
#define AOC25_DAY03_H

#include <iostream>
#include <vector>
#include "../infra/Task.h"

class Day03: public Task
{
public:
    Day03(std::string name, const string& in_file) : Task(std::move(name), in_file) {};
    void run1(bool print_result) override {
        std::string line;
        long long sum = 0;
        while (_input >> line) {
            vector<int> bank = parse_bank(line);
            sum += get_joltage(bank,2);
        }
        if (print_result)
            cout << sum << std::endl;
    }
    void run2(bool print_result) override {
        std::string line;
        long long sum = 0;
        while (_input >> line) {
            vector<int> bank = parse_bank(line);
            sum += get_joltage(bank,12);
        }
        if (print_result)
            cout << sum << std::endl;
    }

private:
    std::vector<int> parse_bank(std::string str) {
        std::vector<int> bank;
        std::transform(str.begin(), str.end(), std::back_inserter(bank),
                       [](char c) { return c - '0'; });
        return bank;
    }

    long long get_joltage(std::vector<int> bank, int num_on) {
        vector<long long> max_joltages(num_on, 0);
        for (int i = 0; i < bank.size(); i++) {
            for (int j = num_on-1; j > 0; j--) {
                if (max_joltages[j - 1] == 0) {
                    continue;
                }
                long long jolt = 10*max_joltages[j-1] + bank[i];
                if (jolt > max_joltages[j]) {
                    max_joltages[j] = jolt;
                }
            }
            if (bank[i] > max_joltages[0]) {
                max_joltages[0] = bank[i];
            }
        }
        return max_joltages[num_on-1];
    }

    int get_joltage2(std::vector<int> bank) {
        int max_first = bank[0];
        int max_joltage = 0;
        for (int i = 1; i < bank.size(); i++) {
            int j = 10*max_first + bank[i];
            if (j > max_joltage) {
                max_joltage = j;
            }
            if (bank[i] > max_first) {
                max_first = bank[i];
            }
        }
        return max_joltage;
    }
};


#endif //AOC25_DAY03_H
