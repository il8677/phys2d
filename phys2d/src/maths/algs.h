#pragma once
#include <vector>

namespace phys2d{
    struct Body;

    struct SPEntry{
        Body* body = nullptr;

        float min;
        float max;

        SPEntry(Body* body, int axis);

        friend bool operator< (const SPEntry& A, const SPEntry& B);
        friend bool operator> (const SPEntry& A, const SPEntry& B);

        friend bool operator== (const SPEntry& A, const SPEntry& B);
        friend bool operator!= (const SPEntry& A, const SPEntry& B);
    };

    void insertInPlace(std::vector<SPEntry>& bodies, SPEntry toInsert);
    void insertionSort(std::vector<SPEntry>& bodies);
}