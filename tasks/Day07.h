//
// Created by fitli on 14.01.26.
//

#ifndef AOC2023_DAY07_H
#define AOC2023_DAY07_H
#include <algorithm>
#include <numeric>
#include <set>

#include "../infra/Task.h"

class Day07: public Task
{
public:
    Day07(std::string name, const string& in_file) : Task(std::move(name), in_file) {};
    void run1(bool print_result) override {
        std::string line;
        set<int> beams;
        int count = 0;
        while (getline(_input, line)) {
            set<int> add_beams;
            set<int> remove_beams;
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == 'S') {
                    beams.insert(i);
                }
                else if (line[i] == '^' and beams.contains(i)) {
                    beams.erase(i);
                    beams.insert(i-1);
                    beams.insert(i+1);
                    count++;
                }
            }
        }
        if (print_result)
            cout << count << std::endl;
    }
    void run2(bool print_result) override {
        string line;
        vector<long long> num_timelines;
        while (getline(_input, line)) {
            if (num_timelines.empty()) {
                num_timelines.resize(line.length(), 0);
            }
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == 'S') {
                    num_timelines[i] += 1;
                }
                else if (line[i] == '^') {
                    num_timelines[i-1] += num_timelines[i];
                    num_timelines[i+1] += num_timelines[i];
                    num_timelines[i] = 0;
                }
            }
        }
        long long result = 0;
        for (auto final_beam : num_timelines) {
            result += final_beam;
        }
        if (print_result)
            cout << result << std::endl;
    }

private:

};

#endif //AOC2023_DAY07_H