#include <iostream>

#include "insertSort.h"

std::vector<int> insertSort(std::vector<int> list) {
    if (list.empty() || list.size() == 1) {
        return list;
    }

    for (int j = 1; j < list.size(); ++j) {
        int key = list[j];

        int i = j - 1;
        while(i > 0 && list[i] > key) {
            list[i + 1] = list[i];
            list[i] = key;
            --i;
        }
    }

    return list;
}