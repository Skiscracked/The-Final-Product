#pragma once

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BILLS 100
#define MAX_CUSTOMERS 50
#define MAX_VEHICLES 50

typedef struct {
    int billNumber;
    char senderName[50];
    char receiverName[50];
    int timeTaken;
} Bill;

typedef struct {
    int customerNumber;
    char customerName[50];
    int billNumbers[MAX_BILLS];
    int numberOfBills;
} Customer;

typedef struct {
    int vehicleID;
    char vehicleStatus[20];
    int batteryCapacity;
    int rechargeRate;
    int drivingDischargeRate;
    int idlingDischargeRate;
} Vehicle;

Bill bills[MAX_BILLS];
Customer customers[MAX_CUSTOMERS];
Vehicle vehicles[MAX_VEHICLES];



extern int findVehicleIndex(int vehicleID);
extern void queryBillInformation(int billNumber);
extern void queryCustomerBills(int customerNumber);
extern void queryVehicleStatus(int vehicleID);
extern void changeVehicleBattery(int vehicleID, int newBatteryCapacity, int newRechargeRate, int newDrivingDischargeRate, int newIdlingDischargeRate);
extern int findCustomerIndex(int customerNumber);
extern int findBillIndex(int billNumber);




