#include "triangle.hpp"
#include "octotree.hpp"

// #define DEBUG

#ifdef DEBUG
    #include <chrono>
#endif

int main() {
    size_t n = 0;
    std::cin >> n;

    std::list<triangle<float>> input;

    #ifdef DEBUG
        auto begin = std::chrono::steady_clock::now();
    #endif

    for (size_t i = 0; i < n; ++i) {
        float x1=0, y1=0, z1=0;
        float x2=0, y2=0, z2=0;
        float x3=0, y3=0, z3=0;

        std::cin >> x1 >> y1 >> z1;
        std::cin >> x2 >> y2 >> z2;
        std::cin >> x3 >> y3 >> z3;

        triangle<float> trg(point<float>(x1,y1,z1), point<float>(x2,y2,z2), point<float>(x3,y3,z3));
        trg.num = i;
        input.push_back(trg);
    }

    octotree<float> octo(input, 0);
    std::deque<cell<float>> groups = octo.get_groups();
    octo.divide_full_depth();

    std::map<size_t, size_t> result;

    for (auto it : groups) {
        std::list<std::list<triangle<float>>::iterator> cur_group = it.get_incell();
        group_intersections(cur_group, result);
    }

    for (auto it = result.begin(); it != result.end(); ++it) {
        std::cout << it->first << std::endl;
    }

    #ifdef DEBUG
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        std::cout << "Time: " << elapsed_ms.count() << " ms\n";
    #endif

    return 0;
}