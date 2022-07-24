#pragma once
#include <vector>

namespace phys2d{
    struct Body;

    struct SPEntry{
        Body* body = nullptr;
        int axis;

        float min() const;
        float max() const;

        SPEntry(Body* body, int axis);

        float axPos() const;

        bool isPast(const SPEntry& other) const;
        bool isBehind(const SPEntry& other) const;

        bool isIn(const SPEntry& other) const;

        friend bool operator< (const SPEntry& A, const SPEntry& B);
        friend bool operator> (const SPEntry& A, const SPEntry& B);

        friend bool operator== (const SPEntry& A, const SPEntry& B);
        friend bool operator!= (const SPEntry& A, const SPEntry& B);
    };

    void insertInPlace(std::vector<SPEntry>& bodies, SPEntry toInsert);
    void insertionSort(std::vector<SPEntry>& bodies);
}

using namespace phys2d;
template<>
struct std::hash<SPEntry>{
    std::size_t operator()(SPEntry const& c) const noexcept{
        return std::hash<Body*>()(c.body);
    }
};