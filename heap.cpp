#include "heap.h"

size_t Heap::Size() const {
    return heap_.size();
}

void Heap::ShiftDown(size_t i) {
    if (heap_.empty()) {
        return;
    }
    while (i * 2 + 1 < heap_.size()) {
        size_t left = i * 2 + 1;
        size_t right = i * 2 + 2;
        size_t candidate_to_swap = left;
        if (right < heap_.size() && heap_[left] > heap_[right]) {
            candidate_to_swap = right;
        }
        if (heap_[i] > heap_[candidate_to_swap]) {
            std::swap(heap_[i], heap_[candidate_to_swap]);
            i = candidate_to_swap;
        } else {
            break;
        }
    }
}

void Heap::ShiftUp(size_t i) {
    if (i >= heap_.size()) {
        return;
    }
    while (i != 0) {
        size_t ancestor = (i - 1) / 2;
        if (heap_[i] < heap_[ancestor]) {
            std::swap(heap_[i], heap_[ancestor]);
            i = ancestor;
        } else {
            break;
        }
    }
}

Vertex Heap::GetMin() const {
    if (heap_.empty()) {
        return {0, 0};
    }
    return heap_[0];
}

void Heap::Pop() {
    if (heap_.empty()) {
        return;
    }
    std::swap(heap_[0], heap_.back());
    heap_.pop_back();
    ShiftDown(0);
}

void Heap::Add(Vertex x) {
    heap_.push_back(x);
    ShiftUp(heap_.size() - 1);
}

Heap::Heap() {
    heap_ = {};
}
