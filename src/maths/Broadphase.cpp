#include "Broadphase.h"

#include <phys2d/Body.h>
#include "common/Contact.h"

#include <functional>
#include <algorithm>
#include <unordered_set>
#include <vector>

namespace phys2d{
    void insertionSort(std::vector<SPEntry>& bodies){
        if(!bodies.size()) return;

        for (auto it = bodies.begin(); it != bodies.end(); ++it){
            if(it->body->doDestroy){
                it = bodies.erase(it);
                it--;
            }
        }

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
    
    SPEntry::SPEntry(Body* body_, int axis_) {
        body = body_;
        axis = axis_;
    }

    float SPEntry::min() const {
        return axPos() - body->shape->maxExtent - std::abs((axVel() * body->isContinuous()));
    }

    float SPEntry::max() const {
        return axPos() + body->shape->maxExtent + std::abs((axVel() * body->isContinuous()));
    }

    float SPEntry::axPos() const{
        return ((float*)(&body->position))[axis];
    }

    float SPEntry::axVel() const{
        return ((float*)(&body->velocity))[axis];
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
        return A.min() < B.min();
    }

    bool operator> (const SPEntry& A, const SPEntry& B){
        return A.min() > B.min();
    }

    bool operator== (const SPEntry& A, const SPEntry& B){
        return A.min() == B.min();
    }

    bool operator!= (const SPEntry& A, const SPEntry& B){
        return A.min() != B.min();
    }

    void Broadphase::addBody(Body* body){
        insertInPlace(body);
    }

    void Broadphase::clear(){
        bodiesX.clear();
    }

    void Broadphase::insertInPlace(Body* body){
        bodiesX.insert(
            std::upper_bound(bodiesX.begin(), bodiesX.end(), SPEntry(body, 0)), 
            SPEntry(body, 0));
    }

    void Broadphase::run(){
        contacts.clear();
        continuousContacts.clear();

        insertionSort(bodiesX);

        std::vector<SPEntry> current;
        current.reserve(bodiesX.size());

        std::unordered_set<Contact> possibleX;

        possibleX.reserve(bodiesX.size()/2);

        for(SPEntry& entry : bodiesX){
            // Remove all entries out of bounds
            current.erase(std::remove_if(
                current.begin(), current.end(), [&](const SPEntry& e){
                    return e.isBehind(entry);
                }), current.end());

            for(auto it = current.begin(); it != current.end(); it++){
                // Skip for layers
                if(!(it->body->layer & entry.body->collideWith && it->body->collideWith & entry.body->layer)) continue;
                
                // Flag body
                contacts.emplace_back(entry.body, it->body);

                // Add to continuous collision list
                if(entry.body->isContinuous()) continuousContacts[entry.body].push_back(contacts.back());
                if(it->body->isContinuous()) continuousContacts[it->body].push_back(contacts.back());
            }

            current.push_back(entry);

        }
        return;
    }    
}
