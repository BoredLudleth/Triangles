#include <iostream>
#include <fstream>
#include <random>

int main() {
    int N = 0;
    std::cin >> N;

    std::mt19937 rng(std::random_device{}()); // Инициализация генератора

    std::uniform_real_distribution<float> dist(-1000.0, 1000.0); 

    std::ofstream out;
    out.open("test.dat");
    if (out.is_open()) {
        out << N << std::endl;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < 3; ++j) {
                out << dist(rng) << " ";
                out << dist(rng) << " ";
                out << dist(rng) << std::endl;
            }
            
            out << std::endl;
        }
    } else {
        std::cout << "File didn't wroten\n";
    }

    out.close();
}