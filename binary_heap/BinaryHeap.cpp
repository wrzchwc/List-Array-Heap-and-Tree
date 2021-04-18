//
// Created by kubaw on 18.04.2021.
//

#include <iostream>
#include <cmath>
#include "BinaryHeap.h"

using namespace std;

BinaryHeap::BinaryHeap() {
    heap = nullptr;
    size = 0;
}

void BinaryHeap::add(int data) {
    //heap is empty
    if (heap == nullptr || size == 0) {
        size++;
        heap = new int[size];
        heap[0] = data;
    }
        //heap is not empty
    else {
        size++;
        int *tmp = new int[size];
        for (int i = 0; i < size; i++) {
            tmp[i] = heap[i];
        }
        tmp[size] = data;
        delete heap;
        heap = tmp;
    }
    restore();

}

void BinaryHeap::remove() {
    //heap is empty
    if (heap == nullptr || size == 0)
        cout << "Heap is empty!" << endl;
        //heap is not empty
    else {
        swap(heap[0], heap[size - 1]);
        size--;
        int *tmp = new int[size];
        for (int i = 0; i < size; i++)
            tmp[i] = heap[i];
        delete heap;
        heap = tmp;
    }
    restore();
}

bool BinaryHeap::contains(int data) {
    int *tmp = heap;
    for (int i = 0; i < size; i++)
        if (tmp[i] == data)
            return true;
    return false;
}

void BinaryHeap::restore(int range, int offset) const {
    for (int i = (range / 2 - 1); i >= (range - size); i = i - offset) {
        //parent has two children
        if (2 * i + 2 <= size - 1) {
            //parent is smaller than its left child
            if (heap[i] < heap[2 * i + 1]) {
                int left_child = 2 * i + 1;
                swap(heap[left_child], heap[i]);
                restore(size + left_child, ((size + left_child) / 2 - 1));
            }
                //parent is smaller than its right child
            else if (heap[i] < heap[2 * i + 2]) {
                int right_child = 2 * i + 2;
                swap(heap[right_child], heap[i]);
                restore(size + right_child, ((size + right_child) / 2 - 1));
            } else
                return;
        }
            //parent has one child - this child is the last leaf
        else if (2 * i + 1 <= size - 1) {
            if (heap[2 * i + 1] > heap[i]) {
                swap(heap[2 * i + 1], heap[i]);
            }
        }
    }
}

void BinaryHeap::show() {
    int tmp = 0;
    for (int i = 0; i < ceil(log2(size)); i++) {
        tmp += pow(2, i);
        if (size - tmp > 0) {
            for (int j = 0; j < pow(2, i); j++)
                cout << heap[i + j] << " " << endl;
        }else{
            tmp-=pow(2,i);
            for (int j = 0; j < size-tmp; j++) {
                cout<<heap[i+j]<<" "<<endl;
            }
        }
        cout<<endl;
    }
}