#include "algs.h"

#include <phys2d/body.h>

#include <functional>
#include <algorithm>

namespace phys2d{
    SPEntry::SPEntry(Body* body_, int axis) {
        body = body_;
        const float axPos = ((float*)(&body->position))[axis];
        min = axPos - body->shape->maxExtent;
        max = axPos - body->shape->maxExtent;
    }

    bool operator< (const SPEntry& A, const SPEntry& B){
        return A.max < B.min;
    }

    bool operator> (const SPEntry& A, const SPEntry& B){
        return A.min > B.max;
    }

    bool operator== (const SPEntry& A, const SPEntry& B){
        return B.min < A.min && A.min < B.max;
    }

    bool operator!= (const SPEntry& A, const SPEntry& B){
        return A < B || A > B;
    }


    void insertInPlace(std::vector<SPEntry>& bodies, SPEntry entry){
        bodies.insert(
            std::upper_bound(bodies.begin(), bodies.end(), entry), 
            entry);
    }

    // TODO: Rewrite
    void insertionSort(std::vector<SPEntry>& bodies){
        if(!bodies.size()) return;

        for (auto it = bodies.begin() + 1; it != bodies.end(); ++it) {
            auto key = it;

            for (auto i = it - 1; i >= bodies.begin(); --i) {
                if (*i > *key) {
                    std::swap(*i, *key);
                    key--;
                } else {
                    break;
                }
            }
        }
    }
}