//
// Created by fitli on 16.01.26.
//

#ifndef AOC2023_DAY09_H
#define AOC2023_DAY09_H
#include <string>
#include <vector>

#include "../helper/string_manipulation.h"
#include "../infra/Task.h"

class Day09: public Task
{
typedef pair<int, int> Coordinates;
typedef pair<int, int> Interval;
public:
    Day09(string name, const string& in_file) : Task(std::move(name), in_file) {};
    void run1(bool print_result) override {
        vector<Coordinates> reds = parse_reds();
        long long max_area = 0;
        for (int i = 0; i < reds.size(); i++) {
            for (int j = i + 1; j < reds.size(); j++) {
                long long area = get_area(reds[i], reds[j]);
                if (area > max_area) {
                    max_area = area;
                }
            }
        }
        if (print_result)
            cout << max_area << std::endl;
    }
    void run2(bool print_result) override {
        vector<Coordinates> reds = parse_reds();
        int max_x = 0;
        int max_y = 0;
        for (auto &r : reds) {
            if (r.first+1 > max_x) {
                max_x = r.first+1;
            }
            if (r.second+1 > max_y) {
                max_y = r.second+1;
            }
        }

        vector<set<int>> walls_vertical(max_y+1);
        vector<set<int>> walls_horizontal(max_x+1);
        make_walls(reds, max_x, max_y, walls_horizontal, walls_vertical);

        if (not is_inside_walls(reds[0], walls_vertical)) {
            reverse(reds.begin(), reds.end());
            make_walls(reds, max_x, max_y, walls_horizontal, walls_vertical);
        }

        long long max_area = 0;
        for (int i = 0; i < reds.size(); i++) {
            for (int j = i + 1; j < reds.size(); j++) {
                long long area = get_area(reds[i], reds[j]);
                if (area > max_area) {
                    if (not wall_between(reds[i].first, reds[j].first, walls_vertical[reds[i].second]) and
                        not wall_between(reds[i].first, reds[j].first, walls_vertical[reds[j].second]) and
                        not wall_between(reds[i].second, reds[j].second, walls_horizontal[reds[i].first]) and
                        not wall_between(reds[i].second, reds[j].second, walls_horizontal[reds[j].first])
                        )
                            max_area = area;
                }
            }
        }


        if (print_result)
            cout << max_area << std::endl;
    }

private:
    vector<Coordinates> parse_reds() {
        vector<Coordinates> reds;
        string line;
        while (getline(_input, line)) {
            vector<string> tokens = split(line, ',');
            reds.push_back(Coordinates(stoll(tokens[0]), stoll(tokens[1])));
        }
        return reds;
    }
    long long get_area(const Coordinates &start, const Coordinates &end) {
        long long width = start.first - end.first;
        if (width < 0)
            width *= -1;
        width++;
        long long height = start.second - end.second;
        if (height < 0)
            height *= -1;
        height++;
        return width*height;
    }

    void connect(Coordinates start, Coordinates end, vector<set<int>> &walls_horizontal, vector<set<int>> &walls_vertical) {
        if (start.second == end.second) {
            if (start.first < end.first) { //left to right
                for (int i = start.first; i <= end.first; i++) {
                    walls_horizontal[i].insert(start.second);
                }
            } else {
                for (int i = start.first; i >= end.first; i--) { //rigth to left
                    walls_horizontal[i].insert(start.second+1);
                }
            }
        }
        else if (start.first == end.first) {
            if (start.second < end.second) { //top to bottom
                for (int i = start.second; i <= end.second; i++) {
                    walls_vertical[i].insert(start.first+1);
                }
            } else {
                for (int i = start.second; i >= end.second; i--) { //bottom to top
                    walls_vertical[i].insert(start.first);
                }
            }
        }
    }

    void break_walls(Coordinates start, Coordinates end, vector<set<int>> &walls_horizontal, vector<set<int>> &walls_vertical) {
        if (start.first == end.first) {
            int smaller = min(start.second, end.second);
            int bigger = max(start.second, end.second);
            vector<int> to_remove;
            for (auto w: walls_horizontal[start.first]) {
                if (smaller < w and w <= bigger) {
                    to_remove.push_back(w);
                }
            }
            for (auto w: to_remove) {
                walls_horizontal[start.first].erase(w);
            }
        }
        else if (start.second == end.second) {
            int smaller = min(start.first, end.first);
            int bigger = max(start.first, end.first);
            vector<int> to_remove;
            for (auto &w: walls_vertical[start.second]) {
                if (smaller < w and w <= bigger) {
                    to_remove.push_back(w);
                }
            }
            for (auto w: to_remove) {
                walls_vertical[start.second].erase(w);
            }
        }
    }

    void make_walls(vector<Coordinates> &reds, int max_x, int max_y, vector<set<int>> &walls_horizontal, vector<set<int>> &walls_vertical) {
        for (auto &w: walls_vertical)
            w.clear();
        for (auto &w: walls_horizontal)
            w.clear();
        for (int i = 0; i<reds.size(); i++) {
            connect(reds[i], reds[(i+1)%reds.size()], walls_horizontal, walls_vertical);
        }
        for (int i = 0; i<reds.size(); i++) {
            break_walls(reds[i], reds[(i+1)%reds.size()], walls_horizontal, walls_vertical);
        }
    }

    bool is_inside_walls(Coordinates point, vector<set<int>> &walls_vertical) {
        int count_walls = 0;
        for (auto w: walls_vertical[point.second]) {
            if (w <= point.first)
                count_walls++;
        }
        return count_walls % 2 == 1;
    }

    bool wall_between(int c1, int c2, set<int> &walls) {
        int first = min(c1, c2);
        int second = max(c1, c2);
        if (walls.empty()) {
            return false;
        }
        for (auto w: walls) {
            if (w > first and w <= second)
                return true;
        }
        return false;
    }
};
#endif //AOC2023_DAY09_H