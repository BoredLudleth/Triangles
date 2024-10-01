#pragma once

#include "triangle.hpp"

#include <list>
#include <deque>
#include <map>

template<typename T = float>
class cell {
private:
    using ListIt = typename std::list<triangle<T>>::iterator;

    std::list<ListIt> incell;

    T x_min = 0;
    T x_max = 0;

    T y_min = 0;
    T y_max = 0;

    T z_min = 0;
    T z_max = 0;
public:
    cell(const std::list<ListIt>& incell) : incell(incell) {

        x_min = x_max = (*incell.begin())->get_a().get_x();
        y_min = y_max = (*incell.begin())->get_a().get_y();
        z_min = z_max = (*incell.begin())->get_a().get_z();

        for (auto it = incell.begin(); it != incell.end(); ++it) {
            if (x_min > (*it)->min_x()) {
                x_min = (*it)->min_x();
            }

            if (x_max < (*it)->max_x()) {
                x_max = (*it)->max_x();
            }

            if (y_min > (*it)->min_y()) {
                y_min = (*it)->min_y();
            }

            if (y_max < (*it)->max_y()) {
                y_max = (*it)->max_y();
            }

            if (z_min > (*it)->min_z()) {
                z_min = (*it)->min_z();
            }

            if (z_max < (*it)->max_z()) {
                z_max = (*it)->max_z();
            }
        }
    }

    T get_x_average() const {
        return (x_max + x_min)/2;
    }

    T get_y_average() const {
        return (y_max + y_min)/2;
    }

    T get_z_average() const {
        return (z_max + z_min)/2;
    }

    std::list<ListIt>& get_incell() {
        return incell;
    }

    void print() const {
        for (const auto& it : incell) {
            it->print();
        }
    }
};

template<typename T = float>
class octotree {
private:
    using ListIt = typename std::list<triangle<T>>::iterator;

    std::list<triangle<T>> input;
    std::deque<cell<T>> groups;   // ячейки R^3 содержат в себе list, в котором лежат итераторы, на треугольники 

    size_t depth = 0;                       // глубина разбора R^3
    size_t num_of_cells = 0;
public:
    octotree(const std::list<triangle<T>>& myinput, size_t depth) : input(myinput), depth(depth) {
        std::list<ListIt> prepare_for_deque;

        for (auto it = input.begin(); it !=input.end(); ++it) {
            prepare_for_deque.push_back(it);
        }
        
        groups.push_back(cell<T>(prepare_for_deque));
        ++num_of_cells;
    };

    const std::deque<cell<T>>& get_groups() {
        return groups;
    }

    void divide_cell_x() {
        std::list<ListIt> plus;
        std::list<ListIt> minus;

        size_t copy_num_of_cells = num_of_cells;

        for (int i = 0; i < copy_num_of_cells; ++i) {
            auto front_groups = groups.front();
            float x_average = front_groups.get_x_average();

            for (const auto& it : front_groups.get_incell()) {
                if(it->get_a().get_x() >= x_average ||
                   it->get_b().get_x() >= x_average ||
                   it->get_c().get_x() >= x_average) {
                    plus.push_back(it);
                   }

                if(it->get_a().get_x() <= x_average ||
                   it->get_b().get_x() <= x_average ||
                   it->get_c().get_x() <= x_average) {
                    minus.push_back(it);
                   }
            }

            if (!plus.empty()) {
                groups.push_back(cell<T>(plus));
                num_of_cells++;
            }
            if (!minus.empty()) {
                groups.push_back(cell<T>(minus));
                num_of_cells++;
            }

            groups.pop_front();
            num_of_cells--;

            plus.clear();
            minus.clear();
        }
    }

    void divide_cell_y() {
        std::list<ListIt> plus;
        std::list<ListIt> minus;

        size_t copy_num_of_cells = num_of_cells;

        for (int i = 0; i < copy_num_of_cells; ++i) {
            auto front_groups = groups.front();
            float y_average = front_groups.get_y_average();

            for (const auto& it : front_groups.get_incell()) {
                if(it->get_a().get_y() >= y_average ||
                   it->get_b().get_y() >= y_average ||
                   it->get_c().get_y() >= y_average) {
                    plus.push_back(it);
                   }

                if(it->get_a().get_y() <= y_average ||
                   it->get_b().get_y() <= y_average ||
                   it->get_c().get_y() <= y_average) {
                    minus.push_back(it);
                   }
            }

            if (!plus.empty()) {
                groups.push_back(cell<T>(plus));
                num_of_cells++;
            }
            if (!minus.empty()) {
                groups.push_back(cell<T>(minus));
                num_of_cells++;
            }

            groups.pop_front();
            num_of_cells--;

            plus.clear();
            minus.clear();
        }
    }

    void divide_cell_z() {
        std::list<ListIt> plus;
        std::list<ListIt> minus;

        size_t copy_num_of_cells = num_of_cells;

        for (int i = 0; i < copy_num_of_cells; ++i) {
            auto front_groups = groups.front();
            float z_average = front_groups.get_z_average();

            for (const auto& it : front_groups.get_incell()) {
                if(it->get_a().get_z() >= z_average ||
                   it->get_b().get_z() >= z_average ||
                   it->get_c().get_z() >= z_average) {
                    plus.push_back(it);
                   }

                if(it->get_a().get_z() <= z_average ||
                   it->get_b().get_z() <= z_average ||
                   it->get_c().get_z() <= z_average) {
                    minus.push_back(it);
                   }
            }

            if (!plus.empty()) {
                groups.push_back(cell<T>(plus));
                num_of_cells++;
            }
            if (!minus.empty()) {
                groups.push_back(cell<T>(minus));
                num_of_cells++;
            }
            groups.pop_front();
            num_of_cells--;

            plus.clear();
            minus.clear();
        }
    }

    void divide_on_eight() {
        divide_cell_x();
        divide_cell_y();
        divide_cell_z();
    }

    void divide_full_depth() {
        for (int i = 0;i < depth; ++i) {
            divide_on_eight();
        }
    }

};

template <typename T = float>
void group_intersections(std::list<std::list<triangle<float>>::iterator>& cur_group, std::map<size_t, size_t>& result) {
    for (auto first = cur_group.begin(); first != cur_group.end(); ++first) {
        auto it = first;
        it++;

        for (auto second = it; second != cur_group.end(); ++second) {
            if(intersection(**first, **second)) {
                // std::cout << (*first)->num << " " << (*second)->num << " "<< intersection(**first, **second) << std::endl;
                // (*first)->print();
                // (*second)->print();
                
                result[(*first)->num] = (*first)->num;
                result[(*second)->num] = (*second)->num;
            }
        }
    }
}