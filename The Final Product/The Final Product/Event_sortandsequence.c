#include "Emulation.h"

void eventlist() {
	/*
	-This file scans an event file containing event records, into a linked lists
	-Sorts each record according to time (Creates a sequential file)
	-And repopulates the event file with the sorted records - for execution.
	*/
	EF = fopen("Events.txt", "r");
	
	if (EF == NULL) {
		printf("Error opening file. Possibly missing");
		return 1;
	}

	List* start; 
	Event eventish;
	list_count = 0;

	char Event_record[LENGTH];
	char* event_token = NULL;
	
	initialize_list(&start);
	
	if (fgets(Event_record, LENGTH, EF) == NULL) {
		perror("Error reading file");
		return 1;
	}

	

	while (fgets(Event_record, LENGTH, EF) != NULL) {
		TRUNCATE(Event_record);

		
		event_token = strtok(Event_record, "\t");
		eventish.time = atol(event_token);

		event_token = strtok(NULL, "\t");
		strcpy(&eventish.event, event_token); // Use strcpy to copy the token to eventish.event
		

		event_token = strtok(NULL, "\t");
		eventish.orig_cust = atol(event_token);

		event_token = strtok(NULL, "\t");
		eventish.dest_cust = atol(event_token);

		event_token = strtok(NULL, "\t");
		eventish.weight = atol(event_token);
		
		
		//buildevent(event_token, &eventish, Event_record);
		add_to_list(&start, &eventish);
		
	}
	bubbleSort(&start, list_count);
	display_list(start);
	free_mem(&start);


	fclose(EF);


}