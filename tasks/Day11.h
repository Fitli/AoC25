//
// Created by fitli on 29.01.26.
//

#ifndef AOC2023_DAY11_H
#define AOC2023_DAY11_H

#include <vector>
#include <map>
#include <set>

#include "../helper/string_manipulation.h"
#include "../infra/Task.h"

class Day11: public Task
{
public:
    Day11(std::string name, const string& in_file) : Task(std::move(name), in_file) {};

    void run1(bool print_result) override {
        map<string, Node> nodes = parse_nodes();
        if (print_result)
            cout << num_paths("you", "out", nodes) << endl;
    }

    void run2(bool print_result) override {
        map<string, Node> nodes = parse_nodes();
        long long result = num_paths("svr", "dac", nodes) * num_paths("dac", "fft", nodes) * num_paths("fft", "out", nodes);
        result += num_paths("svr", "fft", nodes) * num_paths("fft", "dac", nodes) * num_paths("dac", "out", nodes);
        if (print_result)
            cout << result << endl;
    }

private:
    struct Node {
        string name;
        vector<string> edges;
    };

    map<string, Node> parse_nodes() {
        map<string, Node> nodes;
        string line;
        while (getline(_input, line)) {
            vector<string> tokens = split(line, ' ');
            Node n;
            n.name = tokens[0].substr(0, tokens[0].length() - 1);
            n.edges = vector(tokens.begin() + 1, tokens.end());
            nodes[n.name] = n;
        }
        return nodes;
    }

    long long num_paths(const string &start, const string &end, map<string, Node> &nodes) {
        auto paths_to_end = map<string, long long>();
        paths_to_end[end] = 1;
        return num_paths_recursive(start, end, nodes, paths_to_end);
    }
    long long num_paths_recursive(const string &start, const string &end, map<string, Node> &nodes, map<string, long long> &paths_to_end) {
        if (paths_to_end.contains(start)) {
            return paths_to_end[start];
        }

        paths_to_end[start] = 0;
        for (auto &next:nodes[start].edges) {
            paths_to_end[start] += num_paths_recursive(next, end, nodes, paths_to_end);
        }
        return paths_to_end[start];

    }


};

#endif //AOC2023_DAY11_H