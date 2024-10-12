#include "octotree.hpp"
#include "triangle.hpp"

#ifndef NDEBUG
#include <chrono>
#endif

int main() {
  size_t n = 0;
  std::cin >> n;

  if (!std::cin.good()) {
    std::cout << "Invalid input!\n";
    return 0;
  }

  std::list<triangle<float>> input;

#ifndef NDEBUG
  auto begin = std::chrono::steady_clock::now();
#endif

  for (size_t i = 0; i < n; ++i) {
    float x1 = 0, y1 = 0, z1 = 0;
    float x2 = 0, y2 = 0, z2 = 0;
    float x3 = 0, y3 = 0, z3 = 0;

    std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3;

    if (!std::cin.good()) {
      std::cout << "Invalid input!\n";
      return 0;
    }

    triangle<float> trg(point<float>(x1, y1, z1), point<float>(x2, y2, z2),
                        point<float>(x3, y3, z3));
    trg.num = i;
    input.push_back(trg);
  }

  octotree<float> octo(input, count_depth(n));
  octo.divide_full_depth();
  std::deque<cell<float>> groups = octo.get_groups();

  std::map<size_t, size_t> result;

  int i = 0;
  for (auto it : groups) {
    std::list<std::list<triangle<float>>::iterator> cur_group = it.get_incell();
    it.group_intersections(result);
  }

  for (auto it = result.begin(); it != result.end(); ++it) {
    std::cout << it->second << std::endl;
  }

#ifndef NDEBUG
  auto end = std::chrono::steady_clock::now();
  auto elapsed_ms =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
  std::cout << "Time: " << static_cast<float>(elapsed_ms.count()) / 1000
            << " s\n";
#endif

  return 0;
}
