#include "infra/Task.h"
#include "tasks/Day01.h"

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
    //Day01 d1 = Day01("01", "../../test01");
    Day01 d1 = Day01("01", "../input/input01.txt");

    vector<Task *> tasks{
        &d1
    };

    for (auto task: tasks) {
        task->run_benchmarks();
        task->print_results();
    }

    generate_readme("../readme.md", tasks);
    return 0;
}

