#pragma once
#include <vector>
#include <unordered_map>

namespace phys2d{
    struct Body;
    struct Contact;

    // Entry used to keep track of body bounds
    struct SPEntry{
        Body* body = nullptr;
        int axis;

        // Minimum and maximum bound of the body
        float min() const;
        float max() const;

        SPEntry(Body* body, int axis);

        // Get body position along axis
        float axPos() const;
        // Get body velocity along axis
        float axVel() const;

        // Check if this bodies min is past the others max
        bool isPast(const SPEntry& other) const;

        // Check if this bodies max is behind the others min
        bool isBehind(const SPEntry& other) const;

        // Check if this body is subsumed by another
        bool isIn(const SPEntry& other) const;

        // Comparison of mins (used for sorting)
        friend bool operator< (const SPEntry& A, const SPEntry& B);
        friend bool operator> (const SPEntry& A, const SPEntry& B);

        friend bool operator== (const SPEntry& A, const SPEntry& B);
        friend bool operator!= (const SPEntry& A, const SPEntry& B);
    };

    class Broadphase{
        public:
        void addBody(Body* body);
        void removeBody(Body* body);

        void clear();

        void run();

        std::unordered_map<Body*, std::vector<Contact>> continuousContacts;
        std::vector<Contact> contacts; 

        private:

        void insertInPlace(Body* body);

        std::vector<SPEntry> bodiesX;
    };
}

using namespace phys2d;
template<>
struct std::hash<SPEntry>{
    std::size_t operator()(SPEntry const& c) const noexcept{
        return std::hash<Body*>()(c.body);
    }
};