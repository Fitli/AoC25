//
// Created by fitli on 11.01.26.
//

#ifndef AOC2023_DAY05_H
#define AOC2023_DAY05_H

#include <utility>
#include <iostream>

#include "../helper/string_manipulation.h"
#include "../infra/Task.h"
class Day05: public Task
{
public:
    Day05(string name, const string& in_file) : Task(std::move(name), in_file) {};
    void run1(bool print_result) override {
        std::string line;
        vector<Interval> intervals;
        while (getline(_input, line) and !line.empty()) {
            vector<string> tokens = split(line, '-');
            intervals.push_back(Interval(std::stoll(tokens[0]), std::stoll(tokens[1])));
        }
        int count = 0;
        long long id;
        while (_input >> id) {
            for (auto interval : intervals) {
                if (interval.start <= id && id <= interval.end) {
                    count++;
                    break;
                }
            }
        }
        if (print_result)
            cout << count << std::endl;
    }
    void run2(bool print_result) override {
        std::string line;
        vector<Interval> intervals;
        while (getline(_input, line) and !line.empty()) {
            vector<string> tokens = split(line, '-');
            auto interval = Interval(std::stoll(tokens[0]), std::stoll(tokens[1]));
            vector<Interval> new_intervals;
            for (Interval other:intervals) {
                if (not other.overlaps(interval)) {
                    new_intervals.push_back(other);
                }
                else {
                    interval = interval.join(other);
                }
            }
            new_intervals.push_back(interval);
            intervals = new_intervals;
        }
        long long count = 0;
        for (auto interval : intervals) {
            count += interval.length();
        }
        if (print_result)
            cout << count << std::endl;
    }

private:
    struct Interval {
        long long start=0;
        long long end=0;
        public:
            bool overlaps(Interval other) {
                if (start <= other.start and other.start <= end)
                    return true;
                if (start <= other.end and other.end <= end)
                    return true;
                if (other.start <= start and start <= other.end)
                    return true;
                if (other.start <= end and end <= other.end)
                    return true;
                return false;
            }

            Interval join(Interval other) {
                if (not overlaps(other)) {
                    return Interval(0,-1);
                }
                return Interval(min(start, other.start),max(end, other.end));
            }

            long long length() const {
                return end-start + 1;
            }
    };
};

#endif //AOC2023_DAY05_H