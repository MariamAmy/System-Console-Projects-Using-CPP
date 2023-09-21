#ifndef CUSTOMERTYPE_H_INCLUDED
#define CUSTOMERTYPE_H_INCLUDED

class customerType{
public:
    // Data Members
    int customerNumber;
    int arrivalTime;
    int waitingTime;
    int transactionTime;

    // Function Prototyping
    customerType(int cN = 0, int arrvTime = 0, int wTime = 0, int tTime = 0); // Constructor
    void setCustomerInfo(int customerN = 0, int inTime = 0, int wTime = 0, int tTime = 0);
    void setWaitingTime(int time);
    void incrementWaitingTime();
    int getWaitingTime() const;
    int getArrivalTime() const;
    int getTransactionTime() const;
    int getCustomerNumber() const;

};

void customerType::setCustomerInfo(int customerN, int arrvTime, int wTime, int tTime){
    customerNumber = customerN;
    arrivalTime = arrvTime;
    waitingTime = wTime;
    transactionTime = tTime;
}
customerType::customerType(int customerN, int arrvTime, int wTime, int tTime){
    setCustomerInfo(customerN, arrvTime, wTime, tTime);
}
int customerType::getWaitingTime() const{
    return waitingTime;
}
int customerType::getArrivalTime() const{
    return arrivalTime;
}
int customerType::getTransactionTime() const{
    return transactionTime;
}
int customerType::getCustomerNumber() const{
    return customerNumber;
}
void customerType::incrementWaitingTime(){
    waitingTime++;
}
void customerType::setWaitingTime(int time){
    waitingTime = time;
}

#endif // CUSTOMERTYPE_H_INCLUDED
