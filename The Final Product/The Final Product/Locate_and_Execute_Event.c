#include "Emulation.h"

Event Execute;
Customer Temp_origcust, Temp_destcust;/*Temp_origcust represents our temporary customer origin that we're working with, 
										same thing for Temp_destcust - the temporary customer destination. 
										Using those two values, we can call the move function once those values are determined.
										*/

void execute_event() 
{
	const char* Out_binfile = "Customer_out.bin";
	FILE*Custbin = fopen(Out_binfile, "rb"); //opening the binary file for reading in binary mode(to be able to seek to a specific record
	EF = fopen("Events.txt", "r"); //Opening the event file for reading
	if (Custbin == NULL) {
		perror("Error opening binary file");
		return -1;
		// Handle the error, return or exit the function
	}

	while (fgets(Event_Execute, LENGTH, EF) != NULL) 
	{
		TRUNCATE(Event_Execute);
		execute_tok = strtok(Event_Execute, "\t");
		Execute.time = atol(execute_tok);

		execute_tok = strtok(NULL, "\t");
		strcpy(&Execute.event, execute_tok);

		//if (Execute.event == 'D' && Execute.time <= time_elapsed) //if the event is a delivery and the time of the deliver is less than the emulation time
		//{
			execute_tok = strtok(NULL, "\t");
			Execute.orig_cust = atol(execute_tok);

			execute_tok = strtok(NULL, "\t");
			Execute.dest_cust = atol(execute_tok);

			fseek(Custbin, (((Execute.orig_cust - START) * sizeof(Customer)) + sizeof(Header)), SEEK_SET);//put the file pointer in the customer file of the position you wish to scan
			fread(&Temp_origcust, sizeof(Customer), 1, Custbin);//scan the customer in the temporary customer origin variable stores

			fseek(Custbin, ((Execute.dest_cust - START) * sizeof(Customer) + sizeof(Header)), SEEK_SET);
			fread(&Temp_destcust, sizeof(Customer), 1, Custbin);//Scan the destination of the customer into the temporary customer destination variable stores
		//}
		//else
		//{
			//printf("Event could not be executed");
		//}
		
			/*
			* This was a debug statement to check the functionality of the relative files
			printf("Custno: %d, Fname: %s, Lname:%s, Building:%s, Entrance: %c, Floor:%d\n",
			Temp_origcust.Customer_ID, Temp_origcust.fname, Temp_origcust.lname, Temp_origcust.building, Temp_origcust.entrance, Temp_origcust.floor);
			*/
	}

	
}
/*
int returnindex(int i)
{
	for (int i = 0; i < index; i++) {
		if (bills[i].billNumber == billNumber) {
			return i;  // Return the index of the bill if found
		}
}*/