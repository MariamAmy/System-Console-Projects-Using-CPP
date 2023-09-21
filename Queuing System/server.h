#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

#include<bits/stdc++.h>
#include<string>

#include"customerType.h"

class serverType{
public:
    // Data Members
    customerType currentCustomer;
    std::string status;
    int transactionTime;

    // Function Prototyping
    serverType(); // Constructor
    bool isFree() const;
    void setBusy();
    void setFree();

    void setTransactionTime(int t);
    void setTransactionTime();
    void decreaseTransactionTime();
    int getRemainingTransactionTime() const;

    void setCurrentCustomer(customerType cCustomer);
    int getCurrentCustomerNumber() const;
    int getCurrentCustomerArrivalTime() const;
    int getCurrentCustomerWaitingTime() const;
    int getCurrentCustomerTransactionTime() const;

};

serverType::serverType(){
    status = "free";
    transactionTime = 0;
}
bool serverType::isFree() const{
    return (status == "free");
}
void serverType::setBusy(){
    status = "busy";
}
void serverType::setFree(){
    status = "free";
}
void serverType::setTransactionTime(int t){
    transactionTime = t;
}
void serverType::setTransactionTime(){
    int time;
    time = currentCustomer.getTransactionTime();
    transactionTime = time;
}
void serverType::decreaseTransactionTime(){
    transactionTime--;
}
int serverType::getRemainingTransactionTime() const{
    return transactionTime;
}
void serverType::setCurrentCustomer(customerType cCustomer){
    currentCustomer = cCustomer;
}
int serverType::getCurrentCustomerNumber() const{
    return currentCustomer.getCustomerNumber();
}
int serverType::getCurrentCustomerArrivalTime() const{
    return currentCustomer.getArrivalTime();
}
int serverType::getCurrentCustomerTransactionTime() const{
    return currentCustomer.getTransactionTime();
}
int serverType::getCurrentCustomerWaitingTime() const{
    return currentCustomer.getWaitingTime();
}

#endif // SERVER_H_INCLUDED
