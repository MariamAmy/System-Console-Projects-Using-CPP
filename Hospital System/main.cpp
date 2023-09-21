#include <iostream>
#include <fstream>

using namespace std;

const string DATA_FILE = "patients_data.txt";
fstream dataFile;

const int MAX_SPECIALIZATIONS = 30;
const int MAX_QUEUE = 10;

string patient_names[MAX_SPECIALIZATIONS][MAX_QUEUE];
int status[MAX_SPECIALIZATIONS][MAX_QUEUE];
int queue_length[MAX_SPECIALIZATIONS];


void loadPatientDataFromFile() {
    ifstream inputFile("patients_data.txt");
    if (!inputFile.is_open()) {
        cerr << "Error opening data file for reading." << endl;
        return;
    }

    int specialization, status;
    string name;

    while (inputFile >> specialization >> name >> status) {
        if (specialization >= 0 && specialization < MAX_SPECIALIZATIONS) {
            int index = queue_length[specialization];
            if (index < MAX_QUEUE) {
                patient_names[specialization][index] = name;
                ::status[specialization][index] = status; // :: -> for accessing the global variable
                queue_length[specialization]++;
            }
        }
    }

    inputFile.close();
}
void savePatientDataToFile() {
    ofstream outputFile("patients_data.txt");
    if (!outputFile.is_open()) {
        cerr << "Error opening data file for writing!" << endl;
        return;
    }

    for (int spec = 0; spec < MAX_SPECIALIZATIONS; spec++) {
        for (int i = 0; i < queue_length[spec]; i++) {
            outputFile << spec << " " << patient_names[spec][i] << " " << status[spec][i] << endl;
        }
    }

    outputFile.close();
}



void shift_right(int spectiality, string names[], int states[]){

    int qlen = queue_length[spectiality];

    for(int i = qlen-1; i >= 0; --i){
        names[i+1] = names[i];
        states[i+1] = states[i];
    }
    queue_length[spectiality]++;
}


bool add_patient(){
    string name;
    int specialization;
    int state;

    cout << "Enter Specialization, Name, Status" << endl;
    cin >> specialization >> name >> state;

    // Need to check if the queue is full for the selected specialization!
    int ndx = queue_length[specialization];
    if(ndx >= MAX_QUEUE){
        cout << "Sorry, there is no available slots for this specialization!" << endl;
        return false;
    }

    // Otherwise we proceed normally!

    if(state == 0){                                    // Normal Case --> add to end of queue
        patient_names[specialization][ndx] = name;
        status[specialization][ndx] = state;
        queue_length[specialization]++;
    }
    else{                                              // Urgent Case --> add to start of queue
        shift_right(specialization, patient_names[specialization], status[specialization]);
        patient_names[specialization][0] = name;
        status[specialization][0] = state;
    }

}


void print_patients(){
    int sp;
    cout << "Enter Specialization!" << endl;
    cin >> sp;

    int len = queue_length[sp];
    if (len == 0){
        cout << "No Patients in the queue!\n";
        return;
    }
    else{
        cout << "There are " << len << " patients in specialization " << sp << ":" <<endl;
        for(int i = 0; i < len; i++){
            cout << patient_names[sp][i] << " ";
            if(status[sp][i])
                cout << "(Urgent)" << endl;
            else
                cout << "(Normal)\n";
        }
    }

}


void shift_left(int spectiality, string names[], int states[]){

    int len = queue_length[spectiality];

    for(int i = 1; i < len; i++){
        patient_names[spectiality][i-1] = patient_names[spectiality][i];
        status[spectiality][i-1] = status[spectiality][i];
    }
    queue_length[spectiality]--;
}

void get_next_patient(){
    int sp;
    cout << "Enter Specialization!\n";
    cin >> sp;

    int len = queue_length[sp];
    if(len == 0){
        cout << "No Waiting Patients! \n";
        return;
    }

    cout << patient_names[sp][0] << "Your Turn! Please go to the doctor!\n";
    shift_left(sp, patient_names[sp], status[sp]);
}

int menu(){
    int choice = 0;
	while(choice == 0){
        cout << "*******************************************" << endl;
		cout << "Select what you need from the following:\n\n";
		cout << "1) Add new patient\n";
		cout << "2) Print all patients for a specific specialization\n";
		cout << "3) Get next patient\n";
		cout << "4) Exit\n";
        cout << "*******************************************" << endl;

		cin >> choice;

		if (choice > 4 || choice < 1) {
			cout << "Invalid! Please try again!\n";
			choice = 0;
		}
    }
    return choice;
}


void run_system(){
    while (true){
        int selection = menu();

        if(selection == 1)
            add_patient();
        else if(selection == 2)
            print_patients();
        else if(selection == 3)
            get_next_patient();
        else{
            cout << "Goodbye!" << endl;
            break;
        }

    }
}


int main()
{
    loadPatientDataFromFile();

    run_system();

    savePatientDataToFile();

    return 0;
}
