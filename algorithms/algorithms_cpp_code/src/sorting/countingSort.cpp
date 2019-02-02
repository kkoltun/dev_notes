//
// Created by kkoltun on 02.02.19.
//

#include "countingSort.h"

std::vector<unsigned> countingSortSimple(std::vector<unsigned> &list, unsigned k) {
    std::vector<unsigned> occurrences = std::vector<unsigned>(k + 1);

    for (unsigned i : list) {
        ++occurrences[i];
    }

    std::vector<unsigned> output = std::vector<unsigned>();

    for (unsigned i = 0; i < occurrences.size(); ++i) {
        for (unsigned n = 0; n < occurrences[i]; ++n) {
            output.push_back(i);
        }
    }

    return output;
}

std::vector<unsigned> countingSort(std::vector<unsigned> &list, unsigned k) {
    std::vector<unsigned> occurrences = std::vector<unsigned>(k + 1);

    for (unsigned i : list) {
        ++occurrences[i]; // contains numbers of occurrences
    }

    for (unsigned i = 1; i < occurrences.size(); ++i) {
        occurrences[i] += occurrences[i - 1]; // contains number of element less than or equal to i
    }

    std::vector<unsigned> output = std::vector<unsigned>(list.size());
    for (int i = list.size() - 1; i >= 0; --i) {
        unsigned value = list[i];
        unsigned numberOfLessOrEqual = occurrences[value];
        output[numberOfLessOrEqual - 1] = value;

        --occurrences[value];
    }

    return output;
}