#include "algs.h"

#include <phys2d/body.h>

#include <functional>
#include <algorithm>

namespace phys2d{
    SPEntry::SPEntry(Body* body_, int axis_) {
        body = body_;
        axis = axis_;
    }

    float SPEntry::min() const {
        return axPos() - body->shape->maxExtent;;
    }

    float SPEntry::max() const {
        return axPos() + body->shape->maxExtent;
    }

    float SPEntry::axPos() const{
        return ((float*)(&body->position))[axis];
    }

    bool SPEntry::isPast(const SPEntry& other) const {
        return min() > other.max();
    }

    bool SPEntry::isBehind(const SPEntry& other) const {
        return max() < other.min();
    }

    bool SPEntry::isIn(const SPEntry& other) const {
        return !isBehind(other) && !isPast(other);
    }

    bool operator< (const SPEntry& A, const SPEntry& B){
        return A.axPos() < B.axPos();
    }

    bool operator> (const SPEntry& A, const SPEntry& B){
        return A.axPos() > B.axPos();
    }

    bool operator== (const SPEntry& A, const SPEntry& B){
        return A.axPos() == B.axPos();
    }

    bool operator!= (const SPEntry& A, const SPEntry& B){
        return A.axPos() != B.axPos();
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
