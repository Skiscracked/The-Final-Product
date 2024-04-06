#include "offlinesoftware.h"




void queryBillInformation(int billNumber) {
    // Implementation of querying bill information
    // ...

    int billIndex = findBillIndex(billNumber);

    // Check if the bill exists
    if (billIndex != -1) {
        // Bill found, display detailed information
        printf("Querying information for Bill %d:\n", billNumber);
        printf("Sender: %s\n", bills[billIndex].senderName);
        printf("Receiver: %s\n", bills[billIndex].receiverName);
        printf("Time Taken: %d hours\n", bills[billIndex].timeTaken);
        //printf("Status: %s\n", bills[billIndex].status);
        printf("\n");
    }
    else {
        // Bill not found, print error message
        printf("Bill %d not found.\n", billNumber);
    }
}

    /*printf("Querying information for Bill %d:\n", billNumber);
    // Implement the logic to search for the bill information in the bills array
    // Print the results
    // Example:
    printf("Sender: John Doe\n");
    printf("Receiver: Jane Doe\n");
    printf("Time Taken: 2 hours\n");
    printf("\n");*/

void queryCustomerBills(int customerNumber) {
    // Implementation of querying customer's bills
    // ...

    int customerIndex = findCustomerIndex(customerNumber);

    if (customerIndex != -1) 
    {
        printf("Querying bills for Customer %d:\n", customerNumber);

        // Iterate through the bills associated with the customer
        for (int i = 0; i < customers[customerIndex].numberOfBills; ++i) {
            int billNumber = customers[customerIndex].billNumbers[i];
            // Find the index of the bill in the array
            int billIndex = findBillIndex(billNumber);

            // Check if the bill exists
            if (billIndex != -1) {
                // Bill found, display bill information
                printf("Bill %d: Sender - %s, Receiver - %s, Time Taken - %d hours\n",
                    billNumber,
                    bills[billIndex].senderName,
                    bills[billIndex].receiverName,
                    bills[billIndex].timeTaken);
            }
            else 
            {
                // Bill not found, print error message
                printf("Bill %d not found.\n", billNumber);
            }
        }

        printf("\n");
    }
    else 
    {
        // Customer not found, print error message
        printf("Customer %d not found.\n", customerNumber);
    }
}


void queryVehicleStatus(int vehicleID) {
    // Implementation of querying vehicle status
    // ...

    int vehicleIndex = findVehicleIndex(vehicleID);

    if (vehicleIndex = -1) 
    {
        printf("Vehicle ID %d not found.\n", vehicleID);

    }
    else 
    {
        printf("Querying status for Vehicle %d:\n", vehicleID);
        printf("Status: %s\n", vehicles[vehicleIndex].vehicleStatus);
        printf("Battery Capacity: %d\n", vehicles[vehicleIndex].batteryCapacity);
        printf("Recharge Rate: %d\n", vehicles[vehicleIndex].rechargeRate);
        printf("Driving Discharge Rate: %d\n", vehicles[vehicleIndex].drivingDischargeRate);
        printf("Idling Discharge Rate: %d\n", vehicles[vehicleIndex].idlingDischargeRate);
        printf("\n");

    }

   /* printf("Querying status for Vehicle %d:\n", vehicleID);
    // Implement the logic to search for the vehicle status in the vehicles array
    // Print the results
    // Example:
    printf("Status: Running\n");
    printf("Battery Capacity: 100\n");
    printf("Recharge Rate: 10\n");
    printf("Driving Discharge Rate: 3\n");
    printf("Idling Discharge Rate: 1\n");
    printf("\n");
    */
}

void changeVehicleBattery(int vehicleID, int newBatteryCapacity, int newRechargeRate, int newDrivingDischargeRate, int newIdlingDischargeRate) {
    // Implementation of changing vehicle battery
    // ...
    int vehicleIndex = findVehicleIndex(vehicleID);

    if (vehicleIndex != -1) 
    {
        printf("Vehicle ID %d not found.\n", vehicleID);
    }
    else 
    {
        vehicles[vehicleIndex].batteryCapacity = newBatteryCapacity;
        vehicles[vehicleIndex].rechargeRate = newRechargeRate;
        vehicles[vehicleIndex].drivingDischargeRate = newDrivingDischargeRate;
        vehicles[vehicleIndex].idlingDischargeRate = newIdlingDischargeRate;

        printf("Changing battery for Vehicle %d:\n", vehicleID);
        // Implement the logic to update the vehicle's battery information in the vehicles array
        // Example:
        printf("Battery Capacity changed to: %d\n", newBatteryCapacity);
        printf("Recharge Rate changed to: %d\n", newRechargeRate);
        printf("Driving Discharge Rate changed to: %d\n", newDrivingDischargeRate);
        printf("Idling Discharge Rate changed to: %d\n", newIdlingDischargeRate);
        printf("\n");
    } 
}


int findVehicleIndex(int vehicleID) {
    for (int i = 0; i < MAX_VEHICLES; ++i) {
        if (vehicles[i].vehicleID == vehicleID) {
            return i;  // Return the index of the vehicle if found
        }
        else {
            return -1;  // Return -1 if the vehicle is not found
        }
    }
   
}


int findCustomerIndex(int customerNumber) {
    for (int i = 0; i < MAX_CUSTOMERS; i++) {
        if (customers[i].customerNumber == customerNumber) {
            return i;  // Return the index of the customer if found
        }
        else 
        {
            return -1;  // Return -1 if the customer is not found

        }
    }
    
}

int findBillIndex(int billNumber) {
    for (int i = 0; i < MAX_BILLS; i++) {
        if (bills[i].billNumber == billNumber) {
            return i;  // Return the index of the bill if found
        }
        else 
        {
            return -1;  // Return -1 if the bill is not found
        }
    }
    
}
