#include <iostream>

#include "insertSort.h"

std::vector<int> insertSort(std::vector<int> list) {
    if (list.empty() || list.size() == 1) {
        return list;
    }

    for (int i = 1; i < list.size(); ++i) {
        int key = list[i];
        int j = i - 1;

        while (j > 0 && list[j] > key) {
            list[j + 1] = list[j];
            j -= 1;
        }
        list[j + 1] = key;
    }

    return list;
}