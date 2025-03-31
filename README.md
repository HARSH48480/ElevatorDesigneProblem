# DesignProblem2_ElevatorSystem
# ElevatorSystem

## Overview

The ElevatorSystem is a simulation of a basic elevator control system. This project demonstrates object-oriented design principles including inheritance, composition, aggregation, and the singleton pattern.

## Class Diagram

![Class Diagram](ElevatorSystem_ClassDiagram.png)

### Relationships

1. **Inheritance**
   - `ElevatorButton` and `HallButton` inherit from `Button`.

2. **Composition**
   - `Building` contains `Floor` objects.
   - `Floor` contains `HallPanel` and `Display` objects.
   - `Elevator` contains `Door`, `Display`, and `ElevatorPanel` objects.

3. **Aggregation**
   - `Building` aggregates `Elevator` objects.
   - `ElevatorPanel` aggregates `ElevatorButton` objects.

4. **Singleton Pattern**
   - `Building` and `ElevatorSystem` use the singleton pattern to ensure only one instance exists.

## How It Works

The system consists of several interconnected classes that simulate the behavior of an elevator system in a building:

- **Building**: Singleton class that manages multiple floors and elevators.
- **Floor**: Represents a floor in the building, containing hall panels and displays.
- **HallPanel**: Contains up and down buttons to call the elevator.
- **Elevator**: Manages the state and behavior of an individual elevator, including doors, displays, and buttons.
- **ElevatorPanel**: Contains buttons inside the elevator to select destination floors and open/close doors.
- **Display**: Shows the current floor and direction of the elevator.
- **Button**: Abstract base class for all buttons in the system.
- **ElevatorButton**: Button inside the elevator for selecting floors.
- **HallButton**: Button on the floor to call the elevator in a specific direction.
- **ElevatorSystem**: Singleton class that monitors and controls the elevator system.

## Sample Output

Here is a sample output demonstrating how the system operates:

```plaintext
Monitoring the elevator system...
Elevator 0 moving from floor 0 to floor 5.
Door is now Open.
Door is now Closed.
Elevator 1 moving from floor 0 to floor 9.
Door is now Open.
Door is now Closed.
Hall button for direction UP pressed.
Elevator button for floor 5 pressed.
Elevator 0 moving from floor 0 to floor 5.
Door is now Open.
Door is now Closed.
Hall button for direction Down pressed.
Elevator button for floor 0 pressed.
Elevator 1 moving from floor 9 to floor 0.
Door is now Open.
Door is now Closed.
