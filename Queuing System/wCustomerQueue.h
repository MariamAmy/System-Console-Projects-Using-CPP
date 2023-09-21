#ifndef WCUSTOMERQUEUE_H_INCLUDED
#define WCUSTOMERQUEUE_H_INCLUDED

#include"qeueType.h"
#include"server.h"
#include"customerType.h"
#include"serverList.h"

template<class Type>
class waitingCustomerQueueType: public queueType<Type>{
public:
    waitingCustomerQueueType(int num = 100):queueType<Type>(num){};
    void updateWaitingQueue(){
        customerType cust;
        cust.setWaitingTime(-1);
        int wTime = 0;
        queueType<Type>::addQueue(cust);
        while (wTime != -1){
            cust = queueType<Type>::front();
            queueType<Type>::deleteQueue();
            wTime = cust.getWaitingTime();
            if (wTime == -1)
                break;
            cust.incrementWaitingTime();
            queueType<Type>::addQueue(cust);
        }
    }
};

//waitingCustomerQueueType::waitingCustomerQueueType(int num): public queueType<Type>(num){
//    ;
//}

//void waitingCustomerQueueType::updateWaitingQueue(){
//    customerType cust;
//    cust.setWaitingTime(-1);
//    int wTime = 0;
//    queueType<Type>::addQueue(cust);
//    while (wTime != -1){
//        cust = queueType<Type>::front();
//        queueType<Type>::deleteQueue();
//        wTime = cust.getWaitingTime();
//        if (wTime == -1)
//            break;
//        cust.incrementWaitingTime();
//        queueType<Type>::addQueue(cust);
//    }
//}

//template <class Type>
//class waitingCustomerQueueType: public queueType<Type>{
//public:
//    waitingCustomerQueueType(int size=100);
//    void updateWaitingQueue(){
//        customerType cust;
//        cust.setWaitingTime(-1);
//        int wTime = 0;
//        queueType<Type>::addQueue(cust);
//        while (wTime != -1){
//               cust = queueType<Type>::front();
//               queueType<Type>::deleteQueue();
//               wTime = cust.getWaitingTime();
//               if (wTime == -1)
//                   break;
//               cust.incrementWaitingTime();
//               queueType<Type>::addQueue(cust);
//            }
//    }
//};

#endif // WCUSTOMERQUEUE_H_INCLUDED
