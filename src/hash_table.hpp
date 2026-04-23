#pragma once
#include <vector>
#include <string>
#include "resident.hpp"
#include <list>

namespace htable {
    class HashTable {
        private:
        std::vector<std::list<Resident>> table;
        int capacity;
        int coll_count;

        unsigned int RSHash(const std::string& key) {
            unsigned int b = 378551;
	        unsigned int a = 63689;
	        unsigned int hash = 0;

	        for (unsigned int i = 0; i < key.length(); ++i) {
		        hash = hash * a + key[i];
		        a = a * b;
            }

	        return hash;
        }

        // ------------------------------
        public:
        HashTable(long size) : capacity(size), coll_count(0) {
            table.resize(size);
        }

        void insert (const Resident& input) {
            unsigned int index = RSHash(input.street) % capacity;

            if (!table[index].empty()) {
                coll_count++;
            }

            table[index].push_back(input);
        }

        std::vector<Resident> search(const std::string& key) {
            std::vector<Resident> result;
            unsigned int index = RSHash(key) % capacity;

            for (const auto& elem : table[index]) {
                if (elem.street == key) {
                    result.push_back(elem);
                }
            }

            return result;
        }

        int getCollisions() {
            return coll_count;
        }
    };
}
