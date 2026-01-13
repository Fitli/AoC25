//
// Created by fitli on 10.01.26.
//

#ifndef AOC2023_DAY04_H
#define AOC2023_DAY04_H

#include <iostream>
#include <vector>
#include "../infra/Task.h"

class Day04: public Task
{
public:
    Day04(std::string name, const string& in_file) : Task(std::move(name), in_file) {};
    void run1(bool print_result) override {
        vector<vector<int>> roll_map = parse_roll_map();
        int height = roll_map.size();
        int width = roll_map[0].size();
        vector<vector<int>> num_adj = get_num_adj(roll_map, height, width);
        int count = 0;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (num_adj[i][j] < 5 and roll_map[i][j] == 1) {
                    count++;
                }
            }
        }
        if (print_result)
            cout << count << endl;
    }
    void run2(bool print_result) override {
        vector<vector<int>> roll_map = parse_roll_map();
        int height = roll_map.size();
        int width = roll_map[0].size();
        vector<vector<int>> num_adj = get_num_adj(roll_map, height, width);
        int count = 0;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (num_adj[i][j] < 5 and roll_map[i][j] == 1) {
                    remove_roll(roll_map, num_adj, count,  i, j, height, width);
                }
            }
        }
        if (print_result)
            cout << count << endl;
    }

private:
    static std::vector<int> parse_line(std::string str) {
        std::vector<int> line;
        std::transform(str.begin(), str.end(), std::back_inserter(line),
                       [](char c) { return (c=='@') ? 1 : 0; });
        return line;
    }

    vector<vector<int>> parse_roll_map() {
        vector<vector<int>> roll_map;
        string line;
        while (_input >> line) {
            roll_map.push_back(parse_line(line));
        }
        return roll_map;
    }

    static vector<vector<int>> get_num_adj(vector<vector<int>> roll_map, int height, int width) {
        vector<vector<int>> num_adj(height, std::vector<int>(width));
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                for (int k = i-1; k <= i+1; k++) {
                    for (int l = j-1; l <= j+1; l++) {
                        if (k >= 0 and l >= 0 and k < height and l < width) {
                            num_adj[i][j] += roll_map[k][l];
                        }
                    }
                }
            }
        }
        return num_adj;
    }

    void remove_roll(vector<vector<int>>& roll_map, vector<vector<int>>& num_adj, int & count,
                     int y, int x, int height, int width) {

        roll_map[y][x] = 0;
        count++;
        for (int i = y-1; i <= y+1; i++) {
            for (int j = x-1; j <= x+1; j++) {
                if (i < 0 or j < 0 or i >= height or j >= width) {
                    continue;
                }
                num_adj[i][j]--;
                if (roll_map[i][j] == 1 and num_adj[i][j] < 5) {
                    remove_roll(roll_map, num_adj, count, i, j, height, width);
                }
            }
        }
    }
};

#endif //AOC2023_DAY04_H