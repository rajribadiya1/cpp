#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <thread>
using namespace std;

// Escalator Direction Enum
enum Direction { UP, DOWN, STOPPED };

// Person/Passenger Class
class Passenger {
private:
    int id;
    int weight; // in kg (affects load)
    
public:
    Passenger(int id, int weight = 70) : id(id), weight(weight) {}
    
    int getId() const { return id; }
    int getWeight() const { return weight; }
};

// Main Escalator Class
class Escalator {
private:
    int totalSteps;
    int currentLoad;      // Total weight on escalator
    int maxCapacity;      // Maximum weight capacity
    int speed;            // Steps per second
    Direction direction;
    bool isRunning;
    queue<Passenger> passengers;
    vector<Passenger> onEscalator;
    
public:
    Escalator(int steps = 20, int maxCap = 2000, int spd = 1) 
        : totalSteps(steps), maxCapacity(maxCap), speed(spd), 
          currentLoad(0), direction(STOPPED), isRunning(false) {}
    
    // Add passenger to queue
    void addPassenger(const Passenger& p) {
        passengers.push(p);
        cout << "Passenger " << p.getId() << " joins queue\n";
    }
    
    // Board passengers from queue
    void boardPassengers() {
        while (!passengers.empty() && currentLoad + passengers.front().getWeight() <= maxCapacity) {
            Passenger p = passengers.front();
            passengers.pop();
            onEscalator.push_back(p);
            currentLoad += p.getWeight();
            cout << "✓ Passenger " << p.getId() << " boarded (Load: " << currentLoad << "kg)\n";
        }
    }
    
    // Start escalator
    void start(Direction dir) {
        if (isRunning) {
            cout << "⚠ Escalator already running!\n";
            return;
        }
        direction = dir;
        isRunning = true;
        cout << "🟢 Escalator started - Moving " << (dir == UP ? "UP" : "DOWN") << "\n";
    }
    
    // Stop escalator
    void stop() {
        isRunning = false;
        direction = STOPPED;
        cout << "🛑 Escalator stopped\n";
    }
    
    // Move escalator (simulate one step)
    void move() {
        if (!isRunning || onEscalator.empty()) return;
        
        // Simulate passengers exiting at top/bottom
        if (onEscalator.size() > 0) {
            Passenger exiting = onEscalator.back();
            currentLoad -= exiting.getWeight();
            onEscalator.pop_back();
            cout << "✓ Passenger " << exiting.getId() << " exited (Load: " << currentLoad << "kg)\n";
        }
    }
    
    // Check if overloaded
    bool isOverloaded() const {
        return currentLoad > maxCapacity;
    }
    
    // Get escalator status
    void displayStatus() {
        cout << "\n╔════════ ESCALATOR STATUS ════════╗\n";
        cout << "║ Direction:    " << (direction == UP ? "UP" : direction == DOWN ? "DOWN" : "STOPPED") << "\n";
        cout << "║ Running:      " << (isRunning ? "YES" : "NO") << "\n";
        cout << "║ Current Load: " << currentLoad << "kg / " << maxCapacity << "kg\n";
        cout << "║ Passengers:   " << onEscalator.size() << " on escalator, " 
             << passengers.size() << " waiting\n";
        cout << "║ Status:       " << (isOverloaded() ? "⚠️  OVERLOADED" : "✓ Safe") << "\n";
        cout << "╚════════════════════════════════╝\n";
    }
    
    int getPassengerCount() const { return onEscalator.size(); }
    int getCurrentLoad() const { return currentLoad; }
};

// Demo/Test Function
int main() {
    cout << "╔══════════════════════════════════════╗\n";
    cout << "║   C++ ESCALATOR SIMULATION SYSTEM    ║\n";
    cout << "╚══════════════════════════════════════╝\n\n";
    
    Escalator esc(20, 2000, 1);
    
    // Simulate passengers
    for (int i = 1; i <= 5; i++) {
        esc.addPassenger(Passenger(i, 60 + (i * 5)));
    }
    
    esc.displayStatus();
    
    cout << "\n--- Boarding Passengers ---\n";
    esc.boardPassengers();
    
    esc.displayStatus();
    
    cout << "\n--- Starting Escalator (UP) ---\n";
    esc.start(UP);
    esc.displayStatus();
    
    cout << "\n--- Moving Escalator ---\n";
    for (int i = 0; i < 3; i++) {
        esc.move();
    }
    
    esc.displayStatus();
    
    cout << "\n--- Stopping Escalator ---\n";
    esc.stop();
    esc.displayStatus();
    
    return 0;
}
