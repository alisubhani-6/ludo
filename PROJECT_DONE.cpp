#include <string>
#include <iostream>
using namespace std;

class Flight{
    private:
    int FlightID;
    string airline;
    string status;
    bool emergency;
    int time;
    int runwayID;
    Flight* right;
    Flight* left;
   
    public:
    Flight(int id,string air = " ",string now = "StandBy",bool temp = false,int t = 0,int Rid = 0){
        FlightID = id;
        airline = air;
        status = now;
        emergency = temp;
        time = t;
        runwayID = Rid;
        right = nullptr;
        left = nullptr;
    }
   
    void setFlightID(int id){
        FlightID = id;
    }
    void setAirline(string air = " "){
        airline = air;
    }
    void setStatus(string now = "StandBy"){
        status = now;
    }
    void setEmergency(bool temp = false){
        emergency = temp;
    }
    void setTime(int t = 0){
        time = t;
    }
    void setRunwayID(int Rid = 0){
        runwayID = Rid;
    }
    void setRight(Flight* f){
        right = f;
    }
    void setLeft(Flight* f){
        left = f;
    }
    int getFlightID(){
        return FlightID;
    }
    string getAirline(){
        return airline;
    }
    string getStatus(){
        return status;
    }
    bool getEmergency(){
        return emergency;
    }
    int getTime(){
        return time;
    }
    int getRunwayID(){
        return runwayID;
    }
    Flight* getRight(){
        return right;
    }
    Flight* getLeft(){
        return left;
    }
};

class RecordBST{
  private:
  Flight* root;
 
  public:
  RecordBST(){
      root = nullptr;
  }
 
  void insert(Flight* id){
      if(root == nullptr){
          root = id;
      }
      else{
          Flight* current = root;
          Flight* parent = nullptr;
          while(current != nullptr){
              parent = current;
              if(id->getFlightID() < current->getFlightID()){
                  current = current->getLeft();
              }
              else{
                  current = current->getRight();
              }
          }
          if(id->getFlightID() < parent->getFlightID()){
              parent->setLeft(id);
          }
          else{
              parent->setRight(id);
          }
      }
  }
 
  Flight* getRoot(){
      return root;
  }
  void inOrder(Flight* temp){
      if(root == nullptr){
          cout<<"NO DATA AVAILABLE!"<<endl;
          return;
      }
      if(temp == nullptr){
          return;
      }
      inOrder(temp->getLeft());
      cout<<temp->getFlightID()<<" "<<endl;
      inOrder(temp->getRight());
  }
  void preOrder(Flight* temp){
      if(root == nullptr){
          cout<<"NO DATA AVAILABLE!"<<endl;
          return;
      }
      if(temp == nullptr){
          return;
      }
      cout<<temp->getFlightID()<<" "<<endl;
      preOrder(temp->getLeft());
      preOrder(temp->getRight());
  }
  void postOrder(Flight* temp){
      if(root == nullptr){
          cout<<"NO DATA AVAILABLE!"<<endl;
          return;
      }
      if(temp == nullptr){
          return;
      }
      postOrder(temp->getLeft());
      postOrder(temp->getRight());
      cout<<temp->getFlightID()<<" "<<endl;
  }
  bool isEmpty(){
      if(root == nullptr){
          return true;
         
      }
      else{
          return false;
      }
  }
  bool search(int id){
      if(isEmpty() == true){
          cout<<"the record is empty!!"<<endl;
          return false;
      }
      Flight* temp = root;
      while(temp != nullptr){
          if(temp->getFlightID() == id){
              return true;
          }
          else if(id < temp->getFlightID()){
              temp = temp->getLeft();
          }
          else{
              temp = temp->getRight();
          }
      }
      return false;
  }
  void Delete(int value){
      Flight* parent = nullptr;
      Flight* current = root;
     
     //traversal
    while(current != nullptr && current->getFlightID() != value){
        parent = current;
        if(value < current->getFlightID())
            current = current->getLeft();
        else
            current = current->getRight();
    }
    if(current == nullptr){
        cout << "the value does not exist!!" << endl;
        return;
    }
   //no child
    if(current->getLeft() == nullptr && current->getRight() == nullptr){
        if(current == root){
            root = nullptr;
        }
        else if(parent->getLeft() == current){
            parent->setLeft(nullptr);
        }
        else{
            parent->setRight(nullptr);
        }
        delete current;
    }
   //one child
    else if(current->getLeft() == nullptr || current->getRight() == nullptr){
        Flight* child;

        if(current->getLeft() != nullptr)
            child = current->getLeft();
        else
            child = current->getRight();

        if(current == root){
            root = child;
        }
        else if(parent->getLeft() == current){
            parent->setLeft(child);
        }
        else{
            parent->setRight(child);
        }
        delete current;
    }
//both childs
    else{
        Flight* succParent = current;
        Flight* succ = current->getRight();

        while(succ->getLeft() != nullptr){
            succParent = succ;
            succ = succ->getLeft();
        }

        current->setFlightID(succ->getFlightID());
        current->setAirline(succ->getAirline());
        current->setStatus(succ->getStatus());
        current->setTime(succ->getTime());
        current->setRunwayID(succ->getRunwayID());

        if(succParent->getLeft() == succ)
            succParent->setLeft(succ->getRight());
        else
            succParent->setRight(succ->getRight());

        delete succ;
    }

    cout << "Node deleted successfully" << endl;
}
};


class Queue {
private:
    int size;
    int current;
    Flight** arr;

    int parent(int i) {
        return (i - 1) / 2;
    }
   
    int left(int i) {
        return 2 * i + 1;
    }
   
    int right(int i) {
        return 2 * i + 2;
    }

    void swap(int i, int j) {
        Flight* temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    bool higherPriority(Flight* a, Flight* b) {
        if (a->getTime() < b->getTime()) {
            return true;
        } else {
            return false;
        }
    }

    void heapifyUp(int index) {
        while (index > 0 && higherPriority(arr[index], arr[parent(index)])) {
            swap(index, parent(index));
            index = parent(index);
        }
    }

    void heapifyDown(int index) {
        int smallest = index;
        int l = left(index);
        int r = right(index);

        if (l < current && higherPriority(arr[l], arr[smallest]))
            smallest = l;

        if (r < current && higherPriority(arr[r], arr[smallest]))
            smallest = r;

        if (smallest != index) {
            swap(index, smallest);
            heapifyDown(smallest);
        }
    }

public:
    Queue(int cap = 100) {
        size = cap;
        current = 0;
        arr = new Flight*[size];
    }

    bool isEmpty() {
        return current == 0;
    }

    bool isFull() {
        return current == size;
    }

    void resize() {
        int newSize = size * 2;
        Flight** temp = new Flight*[newSize];

        for (int i = 0; i < current; i++)
            temp[i] = arr[i];

        delete[] arr;
        arr = temp;
        size = newSize;
    }

    void enqueue(Flight* f) {
        if (isFull())
            resize();

        arr[current] = f;
        heapifyUp(current);
        current++;

        cout << "Flight " << f->getFlightID()
             << " added to heap queue\n";
    }

    Flight* dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            return nullptr;
        }

        Flight* top = arr[0];
        arr[0] = arr[current - 1];
        current--;
        heapifyDown(0);

        return top;
    }

    void display() {
        if (isEmpty()) {
            cout << "Queue is empty!\n";
            return;
        }

        cout << "Queue contents:\n";
        for (int i = 0; i < current; i++) {
            cout << i + 1 << ") FlightID: " << arr[i]->getFlightID()
                 << ", Airline: " << arr[i]->getAirline()
                 << ", Status: " << arr[i]->getStatus()
                 << ", Time: " << arr[i]->getTime()
                 << endl;
        }
    }
};

int main() {
    RecordBST flightRecords;

    Queue landingQueue;
    Queue takeoffQueue;
    Queue standbyQueue;

    int choice;

    do {
        cout << "\n========== Airport Management System ==========\n";
        cout << "1. Insert New Flight\n";
        cout << "2. Process Next Landing Flight\n";
        cout << "3. Process Next Takeoff Flight\n";
        cout << "4. Search Flight Record\n";
        cout << "5. Display Pending Flights\n";
        cout << "6. Display All Flight Records\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1: {
            int id, time, runway;
            int emergencyInt;
            string airline, status;
            bool emergency;

            cout << "\n--- Insert New Flight ---\n";
            cout << "Enter Flight ID: ";
            cin >> id;

            if (flightRecords.search(id)) {
                cout << "Flight with this ID already exists!\n";
                break;
            }

            cout << "Enter Airline: ";
            cin >> airline;

            do {
                cout << "Enter Status (landing / takeoff / StandBy): ";
                cin >> status;
            } while (status != "landing" && status != "takeoff" && status != "StandBy");

            do {
                cout << "Emergency? (0 = No, 1 = Yes): ";
                cin >> emergencyInt;
            } while (emergencyInt != 0 && emergencyInt != 1);

            emergency = (emergencyInt == 1);

            cout << "Enter Scheduled Time(in minutes past mid-night): ";
            cin >> time;

            cout << "Enter Runway ID: ";
            cin >> runway;

            Flight* newFlight = new Flight(id, airline, status, emergency, time, runway);

            flightRecords.insert(newFlight);

            if (status == "landing")
                landingQueue.enqueue(newFlight);
            else if (status == "takeoff")
                takeoffQueue.enqueue(newFlight);
            else
                standbyQueue.enqueue(newFlight);

            cout << "Flight successfully added to system.\n";
            break;
        }

        case 2: {
            cout << "\n--- Processing Landing Flight ---\n";
            Flight* flight = landingQueue.dequeue();
            if (flight != nullptr) {
                flight->setStatus("Landed");
                cout << "Flight NO." << flight->getFlightID() << " of "<< flight->getAirline() << " has landed on the Runway No."<<flight->getRunwayID()<<endl;
            }
            break;
        }

        case 3: {
            cout << "\n--- Processing Takeoff Flight ---\n";
            Flight* flight = takeoffQueue.dequeue();
            if (flight != nullptr) {
                flight->setStatus("Departed");
                cout << "Flight NO." << flight->getFlightID() << " of "<< flight->getAirline() << " has Taken off from the Runway No."<<flight->getRunwayID()<<endl;
            }
            break;
        }

        case 4: {
            int searchID;
            cout << "\nEnter Flight ID to search: ";
            cin >> searchID;

            if (flightRecords.search(searchID))
                cout << "Flight found in records.\n";
            else
                cout << "Flight not found.\n";
            break;
        }

        case 5: {
            cout << "\n--- Pending Landing Flights ---\n";
            landingQueue.display();

            cout << "\n--- Pending Takeoff Flights ---\n";
            takeoffQueue.display();

            cout << "\n--- Pending StandBy Flights ---\n";
            standbyQueue.display();
            break;
        }

        case 6: {
            int sub;
            do {
                cout << "\n--- Flight Records Traversal ---\n";
                cout << "1. Inorder\n";
                cout << "2. Preorder\n";
                cout << "3. Postorder\n";
                cout << "0. Back\n";
                cout << "Enter choice: ";
                cin >> sub;

                if (sub == 1)
                    flightRecords.inOrder(flightRecords.getRoot());
                else if (sub == 2)
                    flightRecords.preOrder(flightRecords.getRoot());
                else if (sub == 3)
                    flightRecords.postOrder(flightRecords.getRoot());

            } while (sub != 0);
            break;
        }

        case 0:
            cout << "Exiting system...\n";
            break;

        default:
            cout << "Invalid option. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}