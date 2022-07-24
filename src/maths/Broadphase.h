#pragma once
#include <vector>
#include <unordered_map>

namespace phys2d{
    struct Body;
    struct Contact;

    struct SPEntry{
        Body* body = nullptr;
        int axis;

        float min() const;
        float max() const;

        SPEntry(Body* body, int axis);

        float axPos() const;
        float axVel() const;

        bool isPast(const SPEntry& other) const;
        bool isBehind(const SPEntry& other) const;

        bool isIn(const SPEntry& other) const;

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

        void run(std::vector<Contact>& contactList);

        std::unordered_map<Body*, std::vector<Contact>> continuousContacts;

        private:

        void insertInPlace(Body* body);

        std::vector<SPEntry> bodiesX;
        std::vector<SPEntry> bodiesY;
        
    };
}

using namespace phys2d;
template<>
struct std::hash<SPEntry>{
    std::size_t operator()(SPEntry const& c) const noexcept{
        return std::hash<Body*>()(c.body);
    }
};