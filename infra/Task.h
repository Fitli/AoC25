//
// Created by ivana.krumlova on 2.12.2023.
//

#ifndef AOC2023_TASK_H
#define AOC2023_TASK_H


#include <string>
#include <fstream>
#include <iostream>
#include <chrono>

using namespace std;

class Task
{
public:
    Task(string number, const string& in_file) {
        _name = std::move(number);
        _input = ifstream(in_file);
    }

    virtual void run1(bool print_result) {
        if (print_result) {
            cout << "not implemented" << endl;
        }
    }
    virtual void run2(bool print_result) {
        if (print_result) {
            cout << "not implemented" << endl;
        }
    }
    void print_results() {
        cout << _name << " - Task 1: ";
        run1(true);
        _input.clear();
        _input.seekg(0);
        cout << "\t(" << time_run1 << " ms)" << endl;

        cout << _name << " - Task 2: ";
        run2(true);
        _input.clear();
        _input.seekg(0);
        cout << "\t(" << time_run2 << " ms)" << endl;
    }

    void run_benchmarks() {
        time_run1 = measure_time_run([this](){run1(false);}, 100);
        time_run2 = measure_time_run([this](){run2(false);}, 100);
    }

    double measure_time_run(auto func, int repeats) {
        chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        for (size_t i = 0; i < repeats; i++)
        {
            func();
            _input.clear();
            _input.seekg(0);
        }
        chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(
                end - begin).count()/(1000.0*repeats);
    }

    void write_readme_line(ofstream &readme) const {
        string filename = "Day" + _name + ".h";
        readme << "| Day " << _name <<"\t|[" << filename << "](tasks/" << filename << ")\t| ";
        readme << time_run1 <<" ms\t | " << time_run2 <<" ms\t |" << endl;
    }

    string _name;
    ifstream _input;
    double time_run1{};
    double time_run2{};
};


#endif //AOC2023_TASK_H
