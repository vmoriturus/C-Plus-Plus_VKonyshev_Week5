#include <iostream>
#include "ringbuff.hpp"

int main() {
    RingBuffer<int> RB(5);
    bool a=RB.isEmpty();
    size_t b=RB.getSize();
    bool c=RB.isEmpty();
    RB.push(1);
    RB.push(2);
    RB.push(3);
    RB.push(4);
    RB.push(5);
    int d=RB.front();
    int e=RB.back();
    std:: cout << RB.isFull() << std::endl;
//    RB.push(6);
    RB.pop();
    RB.push(6);
    int l = RB.pop();
    e=RB.back();
    d=RB.front();
//    RB.pop();
    std:: cout << RB.isFull() << std::endl;
    size_t f=RB.getCount();
    int g=RB.back();
    int k=RB.getFree();
    RingBuffer RB2=RB;
    RingBuffer<int> RB3(4);
    RB3 = RB2;
    std::cout << "Execution finished" << std::endl;



    return 0;
}
