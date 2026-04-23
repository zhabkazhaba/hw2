#pragma once
#include <vector>
#include <algorithm>
#include <string>
#include <utility>

/**
* @brief Линейный поиск
*/
template <typename T>
std::vector<T> linear_search(const std::vector<T>& input, const std::string& key) {
    std::vector<T> output;

    for (const auto& item : input) {
        if (item.street == key) {
            output.push_back(item);
        }
    }

    return output;
}
