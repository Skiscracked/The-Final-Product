#include "offlinesoftware.h"



int main() 
{
    int choice;

    do {
        // Display menu
        printf("**************** MAIN MENU: ****************\n");
        printf("1. Query Bill Information\n");
        printf("2. Query Customer's Bills\n");
        printf("3. Query Vehicle Status\n");
        printf("4. Change Vehicle Battery\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");

        // Get user input
        scanf_s("%d", &choice);

        // Process user choice
        switch (choice) {
        case 1: {
            int billNumber;
            printf("Enter Bill Number: ");
            scanf_s("%d", &billNumber);
            queryBillInformation(billNumber);
            break;
        }
        case 2: {
            int customerNumber;
            printf("Enter Customer Number: ");
            scanf_s("%d", &customerNumber);
            queryCustomerBills(customerNumber);
            break;
        }
        case 3: {
            int vehicleID;
            printf("Enter Vehicle ID: ");
            scanf_s("%d", &vehicleID);
            queryVehicleStatus(vehicleID);
            break;
        }
        case 4: {
            int vehicleID, newBatteryCapacity, newRechargeRate, newDrivingDischargeRate, newIdlingDischargeRate;
            printf("Enter Vehicle ID: ");
            scanf_s("%d", &vehicleID);
            if(findVehicleIndex)
            {
                printf("Enter New Battery Capacity: ");
                scanf_s("%d", &newBatteryCapacity);
                printf("Enter New Recharge Rate: ");
                scanf_s("%d", &newRechargeRate);
                printf("Enter New Driving Discharge Rate: ");
                scanf_s("%d", &newDrivingDischargeRate);
                printf("Enter New Idling Discharge Rate: ");
                scanf_s("%d", &newIdlingDischargeRate);
                printf("\n");
                (void)getchar();
                changeVehicleBattery(vehicleID, newBatteryCapacity, newRechargeRate, newDrivingDischargeRate, newIdlingDischargeRate);
                break;
            }
            else {
                printf("Vehicle ID %d not found.\n", vehicleID);
            }
        }
        case 0:
            printf("Exiting the program. Goodbye!\n");
            break;
        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }

        // Clear the input buffer
        while (getchar() != '\n');

    } while (choice != 0);

    return 0;
}
