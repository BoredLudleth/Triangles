#pragma once

#include <deque>
#include <list>
#include <map>
#include <utility>

#include "triangle.hpp"

namespace triangle_space {

template <typename T = float>
class cell {
 private:
  using ListIt = typename std::list<triangle<T>>::iterator;

  std::list<std::pair<ListIt, int>> incell;

  T x_min = 0;
  T x_max = 0;

  T y_min = 0;
  T y_max = 0;

  T z_min = 0;
  T z_max = 0;

 public:
  cell(const std::list<std::pair<ListIt, int>>& incell) : incell(incell) {
    x_min = x_max = incell.begin()->first->get_a().x;
    y_min = y_max = incell.begin()->first->get_a().y;
    z_min = z_max = incell.begin()->first->get_a().z;

    for (auto it = incell.begin(); it != incell.end(); ++it) {
      if (x_min > it->first->min_x()) {
        x_min = it->first->min_x();
      }

      if (x_max < it->first->max_x()) {
        x_max = it->first->max_x();
      }

      if (y_min > it->first->min_y()) {
        y_min = it->first->min_y();
      }

      if (y_max < it->first->max_y()) {
        y_max = it->first->max_y();
      }

      if (z_min > it->first->min_z()) {
        z_min = it->first->min_z();
      }

      if (z_max < it->first->max_z()) {
        z_max = it->first->max_z();
      }
    }
  }

  T get_x_average() const { return (x_max + x_min) / 2; }

  T get_y_average() const { return (y_max + y_min) / 2; }

  T get_z_average() const { return (z_max + z_min) / 2; }

  std::list<std::pair<ListIt, int>>& get_incell() { return incell; }

  void print() const {
    for (const auto& it : incell) {
      std::cout << it->second << " ";
    }

    std::cout << std::endl;
  }

  void group_intersections(std::map<size_t, size_t>& result) {
    for (auto one = incell.begin(); one != incell.end(); ++one) {
      auto it = one;

      it++;

      for (auto two = it; two != incell.end(); ++two) {
        if (one->first->intersection(*two->first)) {
          result[(*one).second] = (*one).second;
          result[(*two).second] = (*two).second;
        }
      }
    }
  }
};

template <typename T = float>
class octotree {
 private:
  using ListIt = typename std::list<triangle<T>>::iterator;

  std::list<triangle<T>> input;
  std::deque<cell<T>> groups;

  size_t depth = 0;
  size_t num_of_cells = 0;

 public:
  octotree(const std::list<triangle<T>>& myinput, size_t depth)
      : input(myinput), depth(depth) {
    std::list<std::pair<ListIt, int>> prepare_for_deque;

    for (auto it = input.begin(); it != input.end(); ++it) {
      static int i = 0;

      prepare_for_deque.push_back(std::pair<ListIt, int>(it, i));
      
      ++i;
    }

    groups.push_back(cell<T>(prepare_for_deque));
    ++num_of_cells;
  };

  const std::deque<cell<T>>& get_groups() { return groups; }

  void divide_cell() {
    static int axis = 0;

    std::list<std::pair<ListIt, int>> plus;
    std::list<std::pair<ListIt, int>> minus;

    size_t copy_num_of_cells = num_of_cells;

    for (int i = 0; i < copy_num_of_cells; ++i) {
      auto front_groups = groups.front();

      T average = NAN;
      size_t nod = axis % 3;
      if (nod == 0) {
        average = front_groups.get_x_average();
      } else if (nod == 1) {
        average = front_groups.get_y_average();
      } else {
        average = front_groups.get_z_average();
      }

      for (const auto& it : front_groups.get_incell()) {
        T coordinates[3][3] = {
            it.first->get_a().x, it.first->get_b().x, it.first->get_c().x,
            it.first->get_a().y, it.first->get_b().y, it.first->get_c().y,
            it.first->get_a().z, it.first->get_b().z, it.first->get_c().z};

        if (coordinates[nod][0] >= average || coordinates[nod][1] >= average ||
            coordinates[nod][2] >= average) {
          plus.push_back(it);
        }

        if (coordinates[nod][0] <= average || coordinates[nod][1] <= average ||
            coordinates[nod][2] <= average) {
          minus.push_back(it);
        }
      }

      if (plus.size() + minus.size() < front_groups.get_incell().size() * 2) {
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
      }

      plus.clear();
      minus.clear();
      ++axis;
    }
  }

  void divide_on_eight() {
    for (int i = 0; i < 3; ++i) divide_cell();
  }

  void divide_full_depth() {
    for (int i = 0; i < depth; ++i) {
      divide_on_eight();
    }
  }
};

size_t count_depth(size_t n) {
  if (n < 1000) {
    return 0;
  }

  if (n < 10000) {
    return 1;
  }

  if (n < 100000) {
    return 2;
  }

  return 3;
}
}  // namespace triangle_space
