//
// Created by fitli on 24.01.26.
//

#ifndef AOC2023_DAY10_H
#define AOC2023_DAY10_H

#include <queue>

#include "../helper/string_manipulation.h"
#include "../infra/Task.h"
class Day10: public Task {
public:
    Day10(string name, const string& in_file) : Task(std::move(name), in_file) {};
    void run1(bool print_result) override {
        std::string line;
        int count = 0;
        while (getline(_input, line) and !line.empty()) {
            count += solve_task1(line);
        }
        if (print_result)
            cout << count << std::endl;
    }
    void run2(bool print_result) override {
        return;
        std::string line;
        int count = 0;
        while (getline(_input, line) and !line.empty()) {
            count += solve_task2(line);
        }
        if (print_result)
            cout << count << std::endl;
    }

private:
    struct Binary_State {
        long long lights = 0;
        long long buttons_pushed = 0;
        int count = 0;
    };

    static int solve_task1(string &line) {
        vector<string> tokens = split(line, ' ');
        long long result = parse_binary_result(tokens[0]);
        vector<Binary_State> buttons;
        for (int i = 1; i < tokens.size()-1; i++) {
            buttons.push_back(parse_button_binary(tokens[i], i-1));
        }

        auto state_cmp = [](Binary_State a, Binary_State b) {return a.count > b.count;};
        priority_queue<Binary_State, vector<Binary_State>, decltype(state_cmp)> pq(state_cmp);

        pq.emplace();
        while (!pq.empty()) {
            Binary_State state = pq.top();
            pq.pop();
            for (Binary_State &button : buttons) {
                if ((button.buttons_pushed & state.buttons_pushed) == 0) {
                    auto new_state = Binary_State(
                        state.lights ^ button.lights,
                        state.buttons_pushed ^ button.buttons_pushed,
                        state.count + button.count);
                    if (new_state.lights == result) {
                        return new_state.count;
                    }
                    pq.push(new_state);
                }
            }
        }
    }

    // parse result representation in format [.##.]
    static long long parse_binary_result (string s) {
        long long lights = 0;
        for (int i = 0; i < s.length()-2; i++) {
            if (s[i+1]=='#')
                lights |= 1 << i;
        }
        return lights;
    }

    // parse button mask in format (1,3)
    static Binary_State parse_button_binary (string s, int number) {
        Binary_State button;
        s = s.substr(1, s.size()-2);
        vector<string> tokens = split(s, ',');
        for (const string& token:tokens) {
            button.lights |= 1 << stoi(token);
        }
        button.buttons_pushed = 1 << number;
        button.count = 1;
        return button;
    }

    struct Joltage_State {
        vector<int> joltages;
        long long count = 0;
    };

    static long long solve_task2(string &line) {
        vector<string> tokens = split(line, ' ');
        vector<int> result = parse_joltage_result(tokens[tokens.size()-1]);
        vector<vector<int>> buttons;
        for (int i = 1; i < tokens.size()-1; i++) {
            buttons.push_back(parse_button_vector(tokens[i], result.size()));
        }

        auto state_cmp = [](Joltage_State a, Joltage_State b) {return a.count > b.count;};
        priority_queue<Joltage_State, vector<Joltage_State>, decltype(state_cmp)> pq(state_cmp);
        set<vector<int>> explored;

        pq.push(Joltage_State(vector<int>(result.size(), 0), 0));
        while (!pq.empty()) {
            Joltage_State state = pq.top();
            pq.pop();
            for (auto &button:buttons) {
                bool joltage_too_big = false;
                bool result_met = true;
                auto new_state = state;
                for (int light = 0; light < button.size(); light++) {
                    new_state.joltages[light] += button[light];
                    if (new_state.joltages[light] != result[light]) {
                        result_met = false;
                    }
                    if (new_state.joltages[light] > result[light]) {
                        joltage_too_big = true;
                        break;
                    }
                }
                new_state.count++;
                if (result_met) {
                    cout << new_state.count << endl;
                    return new_state.count;
                }
                if (!joltage_too_big and !explored.contains(new_state.joltages)) {
                    pq.push(new_state);
                    explored.insert(new_state.joltages);
                }
            }
        }
    }

    // parse result representation in format {3,5,4,7}
    static vector<int> parse_joltage_result (string s) {
        vector<int> joltages;
        s = s.substr(1, s.size()-2);
        vector<string> tokens = split(s, ',');
        for (const string& token:tokens) {
            joltages.push_back(stoi(token));
        }
        return joltages;
    }

    // parse button mask in format (1,3) as vector of 0s and 1s
    static vector<int> parse_button_vector (string s, int len) {
        vector<int> lights(len);
        s = s.substr(1, s.size()-2);
        vector<string> tokens = split(s, ',');
        for (const string& token:tokens) {
            lights[stoi(token)] = 1;
        }
        return lights;
    }
};


#endif //AOC2023_DAY10_H