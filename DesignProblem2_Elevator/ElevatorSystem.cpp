#include <bits/stdc++.h>
using namespace std;

class ElevatorPanel;
class HallButton;
class ElevatorButton;
class HallPanel;
class Display;

enum DirectionStatus {
    UP,
    Down
};

enum ElevatorStatus {
    Move_up,
    Move_Down,
    Idle
};

enum DoorStatus {
    Open,
    Close
};

class Button {
protected:
    bool status;
public:
    Button() : status(false) {}
    virtual void press() = 0;
    bool isPressed() { return status; }
};

class ElevatorButton : public Button {
    int destinationFloor;

public:
    ElevatorButton(int floor) : destinationFloor(floor) {}

    void press() override {
        status = true;
        cout << "Elevator button for floor " << destinationFloor << " pressed." << endl;
    }

    int getDestinationFloor() {
        return destinationFloor;
    }

    void reset() {
        status = false;
    }
};

class HallButton : public Button {
    DirectionStatus directionButton;

public:
    HallButton(DirectionStatus direction) : directionButton(direction) {}

    void press() override {
        status = true;
        cout << "Hall button for direction " << (directionButton == UP ? "UP" : "Down") << " pressed." << endl;
    }

    DirectionStatus getDirection() {
        return directionButton;
    }

    void reset() {
        status = false;
    }
};

class ElevatorPanel {
    vector<ElevatorButton *> floorButtons;
    ElevatorButton *openDoorButton;
    ElevatorButton *closeDoorButton;
public:
    ElevatorPanel(int numFloors) {
        for (int i = 1; i <= numFloors; ++i) {
            floorButtons.push_back(new ElevatorButton(i));
        }
        openDoorButton = new ElevatorButton(-1); // Special value for open door
        closeDoorButton = new ElevatorButton(-2); // Special value for close door
    }

    vector<ElevatorButton *> getFloorButtons() {
        return floorButtons;
    }

    ElevatorButton *getOpenDoorButton() {
        return openDoorButton;
    }

    ElevatorButton *getCloseDoorButton() {
        return closeDoorButton;
    }
};

class HallPanel {
    HallButton *upButton;
    HallButton *downButton;

public:
    HallPanel() {
        upButton = new HallButton(UP);
        downButton = new HallButton(Down);
    }

    HallButton *getUpButton() {
        return upButton;
    }

    HallButton *getDownButton() {
        return downButton;
    }
};

class Display {
    int floorNumber;
    DirectionStatus direction;

public:
    Display() : floorNumber(0), direction(UP) {}

    void setFloorNumber(int floor) {
        floorNumber = floor;
    }

    int getFloorNumber() {
        return floorNumber;
    }

    void setDirection(DirectionStatus dir) {
        direction = dir;
    }

    DirectionStatus getDirection() {
        return direction;
    }

    void show() {
        cout << "Floor: " << floorNumber << ", Direction: " << (direction == UP ? "UP" : "Down") << endl;
    }
};

class Door {
    DoorStatus doorStatus;

public:
    Door() : doorStatus(Close) {}

    void setDoorStatus(DoorStatus status) {
        doorStatus = status;
        cout << "Door is now " << (status == Open ? "Open" : "Closed") << "." << endl;
    }

    DoorStatus getDoorStatus() {
        return doorStatus;
    }
};

class Elevator {
    int id;
    Door *elevatorDoor;
    Display *elevatorDisplay;
    ElevatorStatus elevatorState;
    ElevatorPanel *elevatorPanel;
    int currentFloor;
    queue<int> destinations;
    static const int maxCapacity = 680;

public:
    Elevator(int eid, int numFloors) : id(eid), elevatorState(Idle), currentFloor(0) {
        elevatorDoor = new Door();
        elevatorDisplay = new Display();
        elevatorPanel = new ElevatorPanel(numFloors);
    }

    int getCurrentFloor() {
        return currentFloor;
    }

    void moveToFloor(int floor) {
        // Simple simulation of moving to a floor
        cout << "Elevator " << id << " moving from floor " << currentFloor << " to floor " << floor << "." << endl;
        currentFloor = floor;
        elevatorDisplay->setFloorNumber(floor);
        elevatorState = Idle;
    }

    void addDestination(int floor) {
        destinations.push(floor);
    }

    void processDestinations() {
        while (!destinations.empty()) {
            int nextFloor = destinations.front();
            destinations.pop();
            moveToFloor(nextFloor);
            // Open and close doors at each floor
            openDoor();
            closeDoor();
        }
    }

    void openDoor() {
        elevatorDoor->setDoorStatus(Open);
    }

    void closeDoor() {
        elevatorDoor->setDoorStatus(Close);
    }

    ElevatorPanel *getElevatorPanel() {
        return elevatorPanel;
    }
};

class Floor {
    int id;
    HallPanel *floorPanel;
    Display *floorDisplay;

public:
    Floor(int fid) : id(fid) {
        floorPanel = new HallPanel();
        floorDisplay = new Display();
    }

    HallPanel *getHallPanel() {
        return floorPanel;
    }

    Display *getFloorDisplay() {
        return floorDisplay;
    }
};

class Building {
private:
    vector<Floor*> floorList;
    vector<Elevator*> elevatorList;
    static Building *buildingInstance;
    Building(int numFloors, int numElevators) {
        for (int i = 0; i < numFloors; ++i) {
            floorList.push_back(new Floor(i));
        }
        for (int i = 0; i < numElevators; ++i) {
            elevatorList.push_back(new Elevator(i, numFloors));
        }
    }

public:
    static Building* getInstance(int numFloors, int numElevators) {
        if (buildingInstance == nullptr) {
            buildingInstance = new Building(numFloors, numElevators);
        }
        return buildingInstance;
    }

    vector<Floor*> getFloors() {
        return floorList;
    }

    vector<Elevator*> getElevators() {
        return elevatorList;
    }
};

Building *Building::buildingInstance = nullptr;

class ElevatorSystem {
    Building *building;
    static ElevatorSystem *elevatorSystemInstance;

    ElevatorSystem(int numFloors, int numElevators) {
        building = Building::getInstance(numFloors, numElevators);
    }

public:
    static ElevatorSystem* getInstance(int numFloors, int numElevators) {
        if (elevatorSystemInstance == nullptr) {
            elevatorSystemInstance = new ElevatorSystem(numFloors, numElevators);
        }
        return elevatorSystemInstance;
    }

    void monitoring() {
        // Logic to monitor the elevator system
        cout << "Monitoring the elevator system..." << endl;
    }

    void dispatcherAlgo() {
        // Simple round-robin dispatcher algorithm
        auto elevators = building->getElevators();
        for (auto elevator : elevators) {
            elevator->processDestinations();
        }
    }
};

ElevatorSystem *ElevatorSystem::elevatorSystemInstance = nullptr;

int main() {
    int numFloors = 10;
    int numElevators = 2;

    ElevatorSystem *system = ElevatorSystem::getInstance(numFloors, numElevators);
    system->monitoring();
    system->dispatcherAlgo();

    // Simulate button presses
    Building *building = Building::getInstance(numFloors, numElevators);

    // Press hall button to go up on floor 0
    building->getFloors()[0]->getHallPanel()->getUpButton()->press();
    // Elevator button to go to floor 5
    building->getElevators()[0]->getElevatorPanel()->getFloorButtons()[5]->press();
    building->getElevators()[0]->addDestination(5);

    // Press hall button to go down on floor 9
    building->getFloors()[9]->getHallPanel()->getDownButton()->press();
    // Elevator button to go to floor 0
    building->getElevators()[1]->getElevatorPanel()->getFloorButtons()[0]->press();
    building->getElevators()[1]->addDestination(0);

    // Run the dispatcher again to process new requests
    system->dispatcherAlgo();

    return 0;
}
