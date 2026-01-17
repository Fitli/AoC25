#include "infra/Task.h"
#include "tasks/Day01.h"
#include "tasks/Day03.h"
#include "tasks/Day04.h"
#include "tasks/Day05.h"
#include "tasks/Day06.h"
#include "tasks/Day07.h"
#include "tasks/Day08.h"
#include "tasks/Day09.h"

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
    Day01 d1 = Day01("01", "../input/input01.txt");
    Day03 d3 = Day03("03", "../input/input03.txt");
    Day04 d4 = Day04("04", "../input/input04.txt");
    Day05 d5 = Day05("05", "../input/input05.txt");
    Day06 d6 = Day06("06", "../input/input06.txt");
    Day07 d7 = Day07("07", "../input/input07.txt");
    Day08 d8 = Day08("08", "../input/input08.txt");
    Day09 d9 = Day09("09", "../input/input09.txt");

    vector<Task *> tasks{
        &d1, &d3, &d4, &d5, &d6, &d7, &d8, &d9
    };

    for (auto task: tasks) {
        task->run_benchmarks();
        task->print_results();
    }

    generate_readme("../readme.md", tasks);
    return 0;
}

