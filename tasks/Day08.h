//
// Created by fitli on 14.01.26.
//

#ifndef AOC2023_DAY08_H
#define AOC2023_DAY08_H
#include <map>
#include <queue>
#include <vector>

#include "../helper/string_manipulation.h"
#include "../infra/Task.h"

class Day08: public Task {
public:
    Day08(std::string name, const string& in_file) : Task(std::move(name), in_file) {};
    void run1(bool print_result) override {
        vector<Juncbox> juncboxes = parse_juncboxes();
        vector<Connection> connections = make_connections(juncboxes);

        auto connection_cmp = [](Connection a, Connection b) {return a.length < b.length;};
        priority_queue<Connection, vector<Connection>, decltype(connection_cmp)> smallest(connection_cmp);
        for (auto &c:connections) {
            smallest.push(c);
            if (smallest.size() > 1000) {
                smallest.pop();
            }
        }
        while (!smallest.empty()) {
            Connection c = smallest.top();
            smallest.pop();
            c.a->update_component_id(juncboxes);
            c.b->set_component_id(c.a->component_id, juncboxes);
        }

        map<int, int> component_sizes;
        for (Juncbox& j : juncboxes) {
            int component = j.update_component_id(juncboxes);
            if (component_sizes.contains(component)) {
                component_sizes[component]++;
            }
            else {
                component_sizes[component] = 1;
            }
        }

        priority_queue<int, vector<int>, std::greater<int>> top3;
        for (auto c: component_sizes) {
            top3.push(c.second);
            if (top3.size() > 3) {
                top3.pop();
            }
        }

        int result = 1;
        for (int i = 0; i < 3; ++i) {
            result *= top3.top();
            top3.pop();
        }

        if (print_result)
            cout << result << std::endl;
    }

    void run2(bool print_result) override {
        vector<Juncbox> juncboxes = parse_juncboxes();
        vector<Connection> connections = make_connections(juncboxes);

        sort(connections.begin(), connections.end(), [](Connection a, Connection b) {return a.length < b.length;});
        int neccessary_cables = juncboxes.size() - 1;
        auto it = connections.begin();
        long long last_x;
        while (neccessary_cables > 0) {
            Connection& c = *it;
            if (c.a->update_component_id(juncboxes) != c.b->update_component_id(juncboxes)) {
                neccessary_cables--;
                c.b->set_component_id(c.a->component_id, juncboxes);
                last_x = c.a->x * c.b->x;
            }
            ++it;
        }

        if (print_result)
            cout << last_x << std::endl;
    }

private:
    struct Juncbox {
        long long x;
        long long y;
        long long z;
        int id;
        int component_id;

        int update_component_id(vector<Juncbox>& juncboxes) {
            if (component_id != id) {
                component_id = juncboxes[component_id].update_component_id(juncboxes);
            }
            return component_id;
        }

        void set_component_id(int new_component_id, vector<Juncbox>& juncboxes) {
            if (component_id != id) {
                juncboxes[component_id].set_component_id(new_component_id, juncboxes);
            }
            component_id = new_component_id;
        }
    };
    struct Connection {
        Juncbox* a;
        Juncbox* b;
        long long length;
    };

    vector<Juncbox> parse_juncboxes() {
        vector<Juncbox> juncboxes;
        string line;
        int id = 0;
        while (getline(_input, line)) {
            vector<string> tokens = split(line, ',');
            juncboxes.push_back(Juncbox(stoi(tokens[0]), stoi(tokens[1]), stoi(tokens[2]), id, id));
            id++;
        }
        return juncboxes;
    }

    static vector<Connection> make_connections(vector<Juncbox> &juncboxes) {
        vector<Connection> connections;
        for (int i = 0; i < juncboxes.size(); i++) {
            for (int j = i+1; j < juncboxes.size(); j++) {
                Juncbox& a = juncboxes[i];
                Juncbox& b = juncboxes[j];
                long long len = (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) + (a.z-b.z)*(a.z-b.z);
                connections.push_back(Connection(&a, &b, len));
            }
        }
        return connections;
    }
};
#endif //AOC2023_DAY08_H