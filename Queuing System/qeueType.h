#ifndef QEUETYPE_H_INCLUDED
#define QEUETYPE_H_INCLUDED

#include"server.h"
#include"serverList.h"


template <class Type>
class queueADT{
public:
    virtual bool isEmptyQueue() const=0;
    virtual bool isFullQueue() const = 0;
    virtual void initializeQueue() = 0;
    virtual Type front() const = 0;
    virtual Type back() const = 0;
    virtual void addQueue(const Type& queueElement) = 0;
    virtual void deleteQueue() = 0;

};

template <class Type>
class queueType:public queueADT<Type>{
private:
    int maxQueueSize;
    int count;
    int queueFront;
    int queueRear;
    Type *list;

public:
    const queueType<Type>& operator=(const queueType<Type>&);

    bool isEmptyQueue() const{
        return (count == 0);
    }
    bool isFullQueue() const{
        return (count == maxQueueSize);
    }
    void initializeQueue(){
        queueFront = 0;
        queueRear = maxQueueSize - 1;
        count = 0;
    }
    Type front() const{
        assert(!isEmptyQueue());
        return list[queueFront];
    }
    Type back() const{
        assert(!isEmptyQueue());
        return list[queueRear];
    }
    void addQueue(const Type& newElement){
        if (!isFullQueue()){
                queueRear = (queueRear + 1) % maxQueueSize;
                count++;
                list[queueRear] = newElement;
        }
    }
    void deleteQueue(){
        if (!isEmptyQueue()){
                count--;
                queueFront = (queueFront + 1) % maxQueueSize;
        }
    }
    queueType(int queueSize){
        if (queueSize <= 0){
                maxQueueSize = 100;
        }else
            maxQueueSize = queueSize;
            queueFront = 0;
            queueRear = maxQueueSize - 1;
            count = 0;
            list = new Type[maxQueueSize];
    }
   ~queueType(){
       delete [] list;
    }
};

#endif // QEUETYPE_H_INCLUDED
