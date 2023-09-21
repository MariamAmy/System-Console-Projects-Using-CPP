#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED

#include"wCustomerQueue.h"
#include"qeueType.h"
#include"server.h"
#include"customerType.h"
#include"serverList.h"

using namespace std;

void setSimulationParameters(int& sTime, int& numOfServers, int& transTime, int& tBetweenCArrival);
bool isCustomerArrived(double arvTimeDiff);
void generateStatistics(serverListType& serverList,waitingCustomerQueueType<customerType>& CQueue, int numOfCustArrived, int waitTimeServedCustomers);
void runSimulation();


void setSimulationParameters(int& sTime, int& numOfServers, int& transTime, int& tBetweenCArrival){
    cout << "Enter the simulation time: ";
    cin >> sTime;
    cout << endl;

    cout << "Enter the number of servers: ";
    cin >> numOfServers;
    cout << endl;

    cout << "Enter the transaction time: ";
    cin >> transTime;
    cout << endl;

    cout << "Enter the time between customer arrivals: ";
    cin >> tBetweenCArrival;
    cout << endl;
}

bool isCustomerArrived(double timeDiff){
    double value;
    value = static_cast<double> (rand()) / static_cast<double>(RAND_MAX);
    return (value > exp(-1.0 / timeDiff));
}

void runSimulation(){
    int simulationTime;
    int numberOfServers;
    int transactionTime;
    int timeBetweenCustomerArrival;
    waitingCustomerQueueType<customerType> customerQueue;
    customerType customer;
    int custNumber = 0;
    int totalWaitTimeServedCustomers = 0;
    int totalWaitTime = 0;
    int numberOfCustomersServed = 0;
    int customersLeftInServers = 0;
    int clock = 0;
    int serverID;

    setSimulationParameters(simulationTime, numberOfServers, transactionTime, timeBetweenCustomerArrival);

    serverListType serverList(numberOfServers);

    for (clock = 1; clock <= simulationTime; clock++){
        serverList.updateServers(cout);
        if (!customerQueue.isEmptyQueue()){
            customerQueue.updateWaitingQueue();
        }
        if (isCustomerArrived(timeBetweenCustomerArrival)){
            custNumber++;
            customer.setCustomerInfo(custNumber, clock, 0, transactionTime);
            customerQueue.addQueue(customer);
            cout << "The customer number " << custNumber << " arrived at time unit " << clock << endl;
        }

    serverID = serverList.getFreeServerID();

    if (serverID != -1 && !customerQueue.isEmptyQueue()){
            customer = customerQueue.front();
            customerQueue.deleteQueue();
            totalWaitTimeServedCustomers = totalWaitTimeServedCustomers + customer.getWaitingTime();
            serverList.setServerBusy(serverID, customer);
        }
    }

    cout << endl;

    cout << "The simulation ran for " << simulationTime << " time units" << endl;
    cout << "The number of servers: " << numberOfServers << endl;
    cout << "The average transaction time: " << transactionTime << endl;
    cout << "The average arrival time difference between customers: " << timeBetweenCustomerArrival << endl;

    generateStatistics(serverList, customerQueue, custNumber, totalWaitTimeServedCustomers);
}

    void generateStatistics(serverListType& serverList, waitingCustomerQueueType<customerType>& CQueue, int numOfCustArrived, int waitTimeServedCustomers){
        int customersLeftInQueue = 0;
        int totalWaitTime = waitTimeServedCustomers;
        customerType customer;
        while (!CQueue.isEmptyQueue()){
            customer = CQueue.front();
            CQueue.deleteQueue();
            totalWaitTime = totalWaitTime + customer.getWaitingTime();
            customersLeftInQueue++;
    }

    int customersLeftInServers = serverList.getNumberOfBusyServers();
    int numberOfCustomersServed = numOfCustArrived - customersLeftInServers - customersLeftInQueue;
    double averageWaitTime = 0;

    cout << "The total waiting time: " << totalWaitTime << endl;
    cout << "The number of customers that completed a transaction: "<< numberOfCustomersServed << endl;
    cout << "The number of customers left in the servers: "<< customersLeftInServers << endl;
    cout << "The number of customers left in queue: " << customersLeftInQueue<< endl;

    if (numOfCustArrived > 0){
            averageWaitTime = (static_cast<double>(totalWaitTime)) / numOfCustArrived;
            cout << fixed << showpoint << setprecision(2);
            cout << "The average waiting time: " << averageWaitTime << endl;
            cout << "///////////// END OF SIMULATION \\\\\\\\\\\\\\\\\\\\" << endl;
    }
}

#endif // FILE_H_INCLUDED
