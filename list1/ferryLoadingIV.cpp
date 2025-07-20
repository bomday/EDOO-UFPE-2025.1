#include <iostream>
#include <string>

using namespace std;

/* Thought Process:

- The ferry needs at least one car or any car waiting on either bank to make a trip.
- The ferry unloads, then loads cars until reaching its maximum capacity.
- Cars are loaded in First-In-First-Out (FIFO) order (queue).
- The ferry always starts on the *left* bank.

Input:

c          → number of test cases  
l, m       → for each case:  
   l       → ferry length (in meters)  
   m       → number of cars to process  
t, d       → for each car:  
   t       → car length (in centimeters)  
   d       → bank where the car is waiting ("left" or "right")

Output:

- Number of times the ferry crosses the river.

What to do:

1. Convert ferry length from meters to centimeters.
2. Create two queues: one for the left bank, one for the right.
3. Track the current side of the ferry (starting on the left).
4. Load cars from the current side while the ferry can still take them.
5. After each loading, increment the trip counter.
6. Alternate the ferry side and repeat until both queues are empty.
*/

// Structure representing a single car
struct Car {
    int carLength; // Length of the car in centimeters
    Car* nextCar; // Pointer to the next car in the queue
};

// Class representing a queue of cars waiting on one side of the ferry
class FerryQueue {
    private:
        int ferryLength; // Maximum capacity of the ferry in cm
        Car* firstCar; // Pointer to the first car in the queue
        Car* lastCar; // Pointer to the last car in the queue
    public:
        // Constructor
        FerryQueue(int newferryLength) {
            ferryLength = newferryLength;
            firstCar = lastCar = nullptr;
        }

        // Getters
        int getFirstCarLength() {
            return firstCar->carLength;
        }

        int getLastCarLength() {
            return lastCar->carLength;
        }
        
        // Add a new car to the end of the queue
        void addCar(int length) {
            Car* newCar = new Car{length, nullptr};

            // If the queue is empty, the new car is both the first and last
            if (firstCar == nullptr && lastCar == nullptr) {
                firstCar = lastCar = newCar;
            } else {
                lastCar->nextCar = newCar;
                lastCar = newCar;
            }
        }

        // Remove the first car from the queue
        void deleteCar() {
            if (firstCar != nullptr && lastCar != nullptr) {
                Car* delCar = firstCar;
                firstCar = firstCar->nextCar;
                
                // If the queue becomes empty after removal
                if (!firstCar) {
                    lastCar = nullptr;
                
                // If only one car remains
                } else if (!firstCar->nextCar) {
                    lastCar = firstCar;
                }

                delete delCar;
            }
        }

        // Simulate loading cars onto the ferry for a single trip
        void takeCarsOnTrip() {
            int carsOnTripLength = 0;

            // Load cars while total length is less than ferry capacity
            while (firstCar && carsOnTripLength <= ferryLength) {
                if (carsOnTripLength + firstCar->carLength <= ferryLength) {
                    carsOnTripLength = carsOnTripLength + firstCar->carLength;
                    deleteCar();
                } else {
                    break; // Next car doesn't fit
                }
            }
        }

        // Check if the queue is empty
        bool isQueueEmpty() {
            return firstCar == nullptr;
        }
        
        // Destructor
        ~FerryQueue() {
            while (firstCar != nullptr) {
                deleteCar();
            }
        }
};

int main() {
    int numTestCases;

    cin >> numTestCases;

    for (int i=0; i<numTestCases; i++) {
        int ferryLength; // Length of the ferry in meters
        int numCars; // Number of cars to work with
        int numTrips = 0; // Counter for number of trips
        bool leftSide = true; // Start on the left side

        cin >> ferryLength >> numCars;
        
        ferryLength = ferryLength*100; // Convert ferry length from m to cm

        // Create separate queues for cars on the left and right sides
        FerryQueue* queueLeft = new FerryQueue(ferryLength);
        FerryQueue* queueRight = new FerryQueue(ferryLength);

        // Read car data and add to corresponding queue
        for (int i=0; i<numCars; i++) {
            int carLength;
            string carSide;

            cin >> carLength >> carSide;
            
            if (carSide == "right"){
                queueRight->addCar(carLength);
            } else {
                queueLeft->addCar(carLength);
            }
        }

        // Continue trips until both queues are empty
        while (!queueLeft->isQueueEmpty() || !queueRight->isQueueEmpty()) {
            if (leftSide) {
                queueLeft->takeCarsOnTrip();
            } else {
                queueRight->takeCarsOnTrip();
            }

            leftSide = !leftSide; // Switch sides after each trip
            numTrips++;
        }

        // Output the total number of trips needed
        cout << numTrips << endl;

        delete queueLeft;
        delete queueRight;
    }
}