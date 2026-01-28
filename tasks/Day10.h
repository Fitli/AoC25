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

    struct PartialSolution {
        vector<int> num_pushed;
        vector<bool> is_solved;
    };

    class LinearEquation {
    public:
        vector<int> coefficients;
        int result;
        int num_variables;

        LinearEquation(const vector<int> &coeffs, const int &res, const int &n_vars) {
            coefficients = coeffs;
            result = res;
            num_variables = n_vars;
        }
        LinearEquation(int n_vars) {
            num_variables = n_vars;
            coefficients = vector<int>(n_vars);
            result = 0;
        }

        void elliminate(const LinearEquation &other, int pos) {
            if (coefficients[pos] == 0)
                return;
            int c_this = other.coefficients[pos];
            int c_other = coefficients[pos];
            for (int i = 0; i < coefficients.size(); i++) {
                coefficients[i] = coefficients[i] * c_this - other.coefficients[i] * c_other;
            }
            result = result * c_this - other.result * c_other;
        }

        vector<PartialSolution> solve(PartialSolution partial_solution, int &upper_bound) {
            vector<PartialSolution> solutions;
            vector<int> solvable_members;
            int partial_result = 0;
            int sol_sum = 0;
            for (int i = 0; i < num_variables; i++) {
                if (not partial_solution.is_solved[i] and coefficients[i] != 0) {
                    solvable_members.push_back(i);
                }
                else {
                    partial_result += partial_solution.num_pushed[i] * coefficients[i];
                    sol_sum += partial_solution.num_pushed[i];
                }
            }
            if (solvable_members.empty()) {
                if (partial_result == result) {
                    solutions.push_back(partial_solution);
                }
                return solutions;
            }
            if (solvable_members.size() == 1) {
                int member_solution = (result - partial_result) / coefficients[solvable_members[0]];
                if (member_solution < 0 or member_solution > upper_bound - sol_sum) {
                    return solutions;
                }
                partial_solution.num_pushed[solvable_members[0]] = member_solution;
                partial_solution.is_solved[solvable_members[0]] = true;
                return solve(partial_solution, upper_bound);
            }
            int first_solvable = solvable_members[0];
            for (int i = 0; i <= upper_bound-sol_sum; i++) {
                partial_solution.is_solved[first_solvable] = true;
                partial_solution.num_pushed[first_solvable] = i;
                vector<PartialSolution> new_sols = solve(partial_solution, upper_bound);
                solutions.insert(solutions.end(), new_sols.begin(), new_sols.end());
            }
            return solutions;
        }
    };

    static long long solve_task2(string &line) {
        vector<string> tokens = split(line, ' ');
        vector<int> result = parse_joltage_result(tokens[tokens.size()-1]);
        int n_lights = result.size();
        int n_buttons = tokens.size()-2;
        int min_pushes = 0;
        vector<LinearEquation> equations(n_lights, LinearEquation(n_buttons));
        for (int i = 0; i < n_buttons; i++) {
            vector<int> button = parse_buttons(tokens[i+1]);
            for (int l: button) {
                equations[l].coefficients[i] = 1;
            }
        }
        for (int i = 0; i < n_lights; i++) {
            equations[i].result = result[i];
            min_pushes += result[i];
        }
        vector<LinearEquation> diagonalized;
        for (int i = 0; i < n_buttons; i++) {
            for (auto j = equations.begin(); j < equations.end(); ++j) {
                if (j->coefficients[i] != 0) {
                    LinearEquation moved = *j;
                    diagonalized.push_back(moved);
                    equations.erase(j);
                    for (auto k = equations.begin(); k < equations.end(); ++k) {
                        (*k).elliminate(moved, i);
                    }
                    break;
                }
            }
        }

        int upper_bound = 8;
        while (upper_bound < min_pushes) {
            upper_bound = min(upper_bound*2, min_pushes);
            vector<PartialSolution> solutions(1, PartialSolution(vector<int>(n_buttons), vector<bool>(n_buttons)));
            for (int i = diagonalized.size()-1; i >= 0; i--) {
                vector<PartialSolution> new_solutions;
                for (auto &solution: solutions) {
                    vector<PartialSolution> added_solutions = diagonalized[i].solve(solution, upper_bound);
                    new_solutions.insert(new_solutions.end(), added_solutions.begin(), added_solutions.end());
                }
                solutions = new_solutions;
            }

            for (auto &solution: solutions) {
                int num_pushes=0;
                for (int button:solution.num_pushed) {
                    num_pushes += button;
                }
                if (num_pushes < min_pushes)
                    min_pushes = num_pushes;
            }
        }
        return min_pushes;
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

    // parse button in format (1,3) as vector of ints
    static vector<int> parse_buttons (string s) {
        vector<int> lights;
        s = s.substr(1, s.size()-2);
        vector<string> tokens = split(s, ',');
        for (const string& token:tokens) {
            lights.push_back(stoi(token));
        }
        return lights;
    }
};


#endif //AOC2023_DAY10_H