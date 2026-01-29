#include "infra/Task.h"
#include "tasks/Day01.h"
#include "tasks/Day03.h"
#include "tasks/Day04.h"
#include "tasks/Day05.h"
#include "tasks/Day06.h"
#include "tasks/Day07.h"
#include "tasks/Day08.h"
#include "tasks/Day09.h"
#include "tasks/Day10.h"
#include "tasks/Day11.h"
#include "tasks/Day12.h"

void generate_readme(string filename, vector<Task *> tasks) {
    ofstream readme(filename);
    readme << "|\t| Solution \t| Execution time part 1\t | Execution time part 2\t|" << endl;
    readme <<"|---------|---|---|---|" << endl;
    for(Task *task:tasks) {
        task->write_readme_line(readme);
    }
}

int main()
{
    auto d1 = Day01("01", "../input/input01.txt");
    auto d3 = Day03("03", "../input/input03.txt");
    auto d4 = Day04("04", "../input/input04.txt");
    auto d5 = Day05("05", "../input/input05.txt");
    auto d6 = Day06("06", "../input/input06.txt");
    auto d7 = Day07("07", "../input/input07.txt");
    auto d8 = Day08("08", "../input/input08.txt");
    auto d9 = Day09("09", "../input/input09.txt");
    auto d10 = Day10("10", "../input/input10.txt");
    auto d11 = Day11("11", "../input/input11.txt");
    auto d12 = Day12("12", "../input/input12.txt");

    vector<Task *> tasks{
        &d1, &d3, &d4, &d5, &d6, &d7, &d8, &d9,
        &d10, &d11, &d12
    };

    for (auto task: tasks) {
        task->run_benchmarks();
        task->print_results();
    }

    generate_readme("../readme.md", tasks);
    return 0;
}

