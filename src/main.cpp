#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <fstream>
#include "resident.hpp"
#include "sort.hpp"
#include "util.hpp"

#ifdef _WIN32
#include <windows.h>
#endif

template <typename Func>
long long measure_time(Func f, std::vector<Resident>& data) {
    auto start = std::chrono::high_resolution_clock::now();
    f(data);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

int main() {
    #ifdef _WIN32
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    #endif

    std::string in_file = "../data/in_data.csv";
    std::string times_file = "../data/out_times.csv";

    std::cout << "Читаем данные из " << in_file << "\n";
    std::vector<Resident> original_data = read_csv(in_file);
    std::cout << "Успешно прочитано\n";

    if (original_data.empty()) {
        std::cerr << "Датасет пуст\n";
        return 1;
    }

    std::vector<int> sizes = {100, 500, 1000, 2500, 5000, 10000, 25000, 50000, 75000, 100000};

    std::ofstream t_file(times_file);
    if (!t_file.is_open()) {
        std::cerr << "Не удалось открыть файл для записи времени\n";
        return 1;
    }

    // std::cout << "Записываем данные в " << out_file << "\n";
    // write_csv(out_file, final_data);
    // std::cout << "Успешно записано\n";

    return 0;
}