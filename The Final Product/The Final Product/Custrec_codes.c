#include "Emulation.h"
/*
-This file contains the function used to initialize the header file and initialize the customer record

-This file also creates a relative file for the customer records ("Customer_out.bin")
*/


void init_custheader_and_makerelative() {

	_set_fmode(_O_BINARY);

	FILE* ctfi;//Customer input file pointer - Text file
	FILE* ctfo;//Customer output file pointer - Binary File

	const char* customer_textfile = "Customers.txt";
	const char* customer_outfile = "Customer_out.bin";
	ctfi = fopen(customer_textfile, "r"); //customer input file pointer to open the customer file to be scanned
	if (ctfi == NULL) {
		perror("Error opening file");
		return EXIT_FAILURE;
	}
	ctfo = fopen(customer_outfile, "wb+"); //customer binary output file

	Customer customer_record;
	Header customer_header;

	char customer_rec[LENGTH];
	char* cust_tok;  // returns the address of the token


	//Setting the first customer id to be 1000
	customer_header.first_id = 1000;

	//Using a temporary id to increment through the IDs in the list
	long cust_id = customer_header.first_id;

	if (fgets(customer_rec, LENGTH, ctfi) == NULL) {
		fclose(ctfi);
		return EXIT_FAILURE	;
	}//This is to skip the first line of the input file - the record title

	/*Using fgets to scan each line and populate the data elements of the structure*/
	while (fgets(customer_rec, LENGTH, (FILE*)ctfi) > 0) {
		TRUNCATE(customer_rec);// Removing the line feed character that fgets adds
		customer_record.Customer_ID = cust_id;

		cust_tok = strtok(customer_rec, "\t");
		/*We used the strtok function to obtain characters, utilizing their delimiters*/
		cust_tok = strtok(NULL, "\t");
		strcpy(&customer_record.fname, cust_tok);

		cust_tok = strtok(NULL, "\t");
		strcpy(&customer_record.lname, cust_tok);
		
		cust_tok = strtok(NULL, "\t");
		strcpy(&customer_record.building, cust_tok);
		customer_record.building[2] = '\0';

		cust_tok = strtok(NULL, "\t");
		strcpy(&customer_record.entrance, cust_tok); 

		cust_tok = strtok(NULL, "\n");
		customer_record.floor = atoi(cust_tok);
		//The atol function takes an string and returns it's integer equivalent

		fseek(ctfo, ((customer_record.Customer_ID - START) * sizeof(Customer) + sizeof(Header)), SEEK_SET);
		fwrite(&customer_record, sizeof(Customer), 1, ctfo);//Writing out each record from the .txt file to the .bin file

		cust_id++;
	}

	customer_header.first_id = cust_id; //the header now has the id of the next available spot on the customer file


	fseek(ctfo, 0, SEEK_SET);
	fwrite(&customer_header, sizeof(Header), 1, ctfo);

	fclose(ctfi);
	fclose(ctfo);

	return 0;
}