//
// Created by kkoltun on 05.02.19.
//

#include <algorithm>
#include <list>

#include "bucketSort.h"
#include "insertSort.h"

void bucketSort(std::vector<float> &array) {
    std::vector<std::list<float>> b = std::vector<std::list<float>>(array.size(), std::list<float>());

    for (float f : array) {
        auto idx = unsigned(array.size() * f);
        b[idx].push_back(f);
    }

    for (auto &list : b) {
        list.sort();
    }

    auto b_itr = b.begin();
    auto elem_itr = (*b_itr).begin();

    array = std::vector<float>();

    for (auto &list : b) {
        for (float f : list) {
            array.push_back(f);
        }
    }
}