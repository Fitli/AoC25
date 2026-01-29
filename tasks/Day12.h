//
// Created by fitli on 29.01.26.
//

#ifndef AOC2023_DAY12_H
#define AOC2023_DAY12_H

#include <vector>

#include "../helper/string_manipulation.h"
#include "../infra/Task.h"

class Day12: public Task {
public:
    Day12(std::string name, const string& in_file) : Task(std::move(name), in_file) {};
    void run1(bool print_result) override {
        std::string line;
        int count = 0;
        vector<Shape> shapes;
        pair<int, int> max_tile;
        while (getline(_input, line)) {
            if (line[1] == ':') {
                shapes.push_back(parse_shape());
            }
            else {
                for (auto &shape:shapes) {
                    if (shape.tile_area.first > max_tile.first) {
                        max_tile.first = shape.tile_area.first;
                    }
                    if (shape.tile_area.second > max_tile.second) {
                        max_tile.second = shape.tile_area.second;
                    }
                }
                break;
            }
        }
        do {
            auto tokens = split(line, ' ');
            pair<int, int> area = parse_area(tokens[0]);
            vector<int> amounts;
            transform(tokens.begin()+1, tokens.end(), std::back_inserter(amounts), [](const string& s) { return stoi(s); });
            int sum_amounts = 0;
            int presents_area = 0;
            for (int i = 0; i < amounts.size(); i++) {
                sum_amounts += amounts[i];
                presents_area += amounts[i] * shapes[i].area;
            }
            int num_tiles = (area.first/max_tile.first) * (area.second/max_tile.second);
            int total_area = area.first * area.second;
            if (num_tiles >= sum_amounts) {
                count++;
            } else if (total_area < presents_area) {
                continue;
            } else {
                cout << "oh no, this looks too NP-complete" << endl;
            }

        } while (getline(_input, line));
        if (print_result)
            cout << count << std::endl;
    }

private:
    struct Shape {
        int area = 0;
        pair<int, int> tile_area = make_pair(0, 0);
    };

    Shape parse_shape() {
        Shape s;
        string line;
        while (getline(_input, line)) {
            if (line.empty()) {
                return s;
            }
            s.area += count(line.begin(), line.end(), '#');
            s.tile_area.first = line.size();
            s.tile_area.second++;
        }
        return s;
    }
    static pair<int, int> parse_area(string s) {
        s = s.substr(0, s.length() - 1);
        auto tokens = split(s, 'x');
        return pair(stoi(tokens[0]), stoi(tokens[1]));
    }
};

#endif //AOC2023_DAY12_H