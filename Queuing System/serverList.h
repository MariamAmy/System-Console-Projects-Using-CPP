#ifndef SERVERLIST_H_INCLUDED
#define SERVERLIST_H_INCLUDED

#include<ostream>

#include"customerType.h"
#include"server.h"

class serverListType{
public:
    // Data Members
    int numOfServers;
    serverType *servers;

    // Function Prototyping
    serverListType(int num = 1); // Constructor
    ~serverListType(); // Destructor
    int getFreeServerID() const;
    int getNumberOfBusyServers() const;
    void setServerBusy(int serverID, customerType cCustomer, int tTime);
    void setServerBusy(int serverID, customerType cCustomer);
    void updateServers(std::ostream& outFile);

};

serverListType::serverListType(int num){
    numOfServers = num;
    servers = new serverType[num];
}
serverListType::~serverListType(){
    delete [] servers;
}
int serverListType::getFreeServerID() const{
    int serverID = -1;
    int i;
    for (i=0; i < numOfServers; i++){
        if (servers[i].isFree()){
            serverID = i;
            break;
        }
    }
    return serverID;
}
int serverListType::getNumberOfBusyServers() const{
    int busyServers = 0;
    int i;
    for (i = 0; i < numOfServers; i++)
        if (!servers[i].isFree())
            busyServers++;
    return busyServers;
}
void serverListType::setServerBusy(int serverID, customerType cCustomer, int tTime){
    servers[serverID].setBusy();
    servers[serverID].setTransactionTime(tTime);
    servers[serverID].setCurrentCustomer(cCustomer);
}
void serverListType::setServerBusy(int serverID, customerType cCustomer){
    int time;
    time = cCustomer.getTransactionTime();
    servers[serverID].setBusy();
    servers[serverID].setTransactionTime(time);
    servers[serverID].setCurrentCustomer(cCustomer);
}
void serverListType::updateServers(std::ostream& outFile){
    int i;
    for (i = 0; i < numOfServers; i++){
        if (!servers[i].isFree()){
            servers[i].decreaseTransactionTime();
            if (servers[i].getRemainingTransactionTime() == 0){
                outFile << "From server number " << (i + 1) << " customer number " << servers[i].getCurrentCustomerNumber() << "\n departed at time unit "
                << servers[i].getCurrentCustomerArrivalTime()
                 + servers[i].getCurrentCustomerWaitingTime()
                 + servers[i].getCurrentCustomerTransactionTime()
                << std::endl;

                servers[i].setFree();
            }
        }
    }
}

#endif // SERVERLIST_H_INCLUDED
