/* Akshay Aravindan
* Galil Motion Controller Code (C)
* This is a very basic program that allows you to connect to the
* Galil controller and send a few simple commands to move it.
* This was built for exclusive use by Bluescape.
*/

// List of imports
#include <time.h>
#include <stdio.h>
#include <gclibo.h> // This allows the Galil API's to be pulled in

/*
* Set up variables to use
*/
GReturn rc; // Main variable used; if rc!=0, then there is an error.
char buf[1024]; // This is used as a traffic buffer.
GCon g; // This is used to refer to a unique connection

/*
* Print out simple information about the controller
*/
int bluescape_getInfo(int getInfo) {
	rc = GVersion(buf, sizeof(buf));
	printf("rc: %d\n", (int) rc); // rc should be 0
	printf("Version: %s\n", buf); //Print the library version

	return rc;
}

/*
* Connect to the controller
*/
int bluescape_connect(int connect) {
	// Open up error log
	FILE *f = fopen("error.log", "a+");
	if (f == NULL)
	{
	    printf("Error opening file.\n");
	    exit(1);
	}

	// Get date and time
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	rc = GOpen("10.1.3.17 -d", &g); // Open a connection and store it as g
	if (rc != 0) { // If the controller fails to connect
		// Print in console
		printf("==========[%d-%d-%d %d:%d:%d]==========\n", tm.tm_mon + 1, tm.tm_mday, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
		printf("Connection Failed.\n");
		// Print in error file
		fprintf(f, "==========[%d-%d-%d %d:%d:%d]==========\n", tm.tm_mon + 1, tm.tm_mday, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
		fprintf(f, "Connection Failed.\n");
		return rc; // Stop the program
	} else { // If the controller connects
		printf("rc: %d\n", (int) rc);
	}

	return rc;
	fclose(f);
}

/*
* Print out the status of the controller
*/
int bluescape_status(int status) {
	// Open up error log
	FILE *f = fopen("error.log", "a+");
	if (f == NULL)
	{
	    printf("Error opening file.\n");
	    exit(1);
	}

	// Get date and time
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	rc = GInfo(g, buf, sizeof(buf)); // Check the status of the controller
	if (rc != 0) { // If the controller is not working properly
		// Print in console
		printf("==========[%d-%d-%d %d:%d:%d]==========\n", tm.tm_mon + 1, tm.tm_mday, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
		printf("The information is not being displayed.\n");
		// Print in error file
		fprintf(f, "==========[%d-%d-%d %d:%d:%d]==========\n", tm.tm_mon + 1, tm.tm_mday, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
		fprintf(f, "The information is not being displayed.\n");
		exit(-1); // Stop the program
	} else { // If the controller is working properly
		printf("rc: %d\n", (int) rc);
		printf("Info: %s\n", buf); // Print the connection info
	}
	
	return rc;
	fclose(f);
}

/*
* Send commands to the controller
*/
int bluescape_command(int command) {
	// Open up error log
	FILE *f = fopen("error.log", "a+");
	if (f == NULL)
	{
	    printf("Error opening file.\n");
	    exit(1);
	}

	// Get date and time
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	rc = GCommand(g, "MG TIME", buf, sizeof(buf), 0); // Send MG TIME command. Because the response is ASCII, it don't care about bytes read.
	if (rc != 0) { // If the commands were not received
		// Print in console
		printf("==========[%d-%d-%d %d:%d:%d]==========\n", tm.tm_mon + 1, tm.tm_mday, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
		printf("The commands did not go through properly.\n");
		// Print in error file
		fprintf(f, "==========[%d-%d-%d %d:%d:%d]==========\n", tm.tm_mon + 1, tm.tm_mday, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
		fprintf(f, "The commands did not go through properly.\n");
		exit(-1); // Stop the program
	} else { // If the commands were received
		printf("rc: %d\n", (int) rc);	
		printf("Response: %s\n", buf); // Print the response
	}
	
	return rc;
	fclose(f);
}

/*
* Make the controller move right
*/
int bluescape_moveRight(int moveRight) {
	// Open up error log
	FILE *f = fopen("error.log", "a+");
	if (f == NULL)
	{
	    printf("Error opening file.\n");
	    exit(1);
	}

	// Get date and time
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	rc = GCommand(g, "DPA= 0", buf, sizeof(buf), 0);
	rc = GCommand(g, "PRA= 100", buf, sizeof(buf), 0);
	rc = GCommand(g, "BG A", buf, sizeof(buf), 0);
	rc = GCommand(g, "AM A", buf, sizeof(buf), 0);
	rc = GCommand(g, "WT 1000", buf, sizeof(buf), 0);
	if (rc != 0) { // If the commands were not received
		// Print in console
		printf("==========[%d-%d-%d %d:%d:%d]==========\n", tm.tm_mon + 1, tm.tm_mday, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
		printf("The controller did not move right when told.\n");
		// Print in error file
		fprintf(f, "==========[%d-%d-%d %d:%d:%d]==========\n", tm.tm_mon + 1, tm.tm_mday, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
		fprintf(f, "The controller did not move right when told.\n");
		exit(-1); // Stop the program
	} else { // If the commands were received
		printf("rc: %d\n", (int) rc);	
		printf("Response: %s\n", buf); // Print the response
		printf("Moved Right!\n");
	}
	
	return rc;
	fclose(f);
}

/*
* Make the controller move left
*/
int bluescape_moveLeft(int moveLeft) {
	// Open up error log
	FILE *f = fopen("error.log", "a+");
	if (f == NULL)
	{
	    printf("Error opening file.\n");
	    exit(1);
	}

	// Get date and time
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	rc = GCommand(g, "DPA= 0", buf, sizeof(buf), 0);
	rc = GCommand(g, "PRA= -100", buf, sizeof(buf), 0);
	rc = GCommand(g, "BG A", buf, sizeof(buf), 0);
	rc = GCommand(g, "AM A", buf, sizeof(buf), 0);
	rc = GCommand(g, "WT 1000", buf, sizeof(buf), 0);
	if (rc != 0) { // If the commands were not received
		// Print in console
		printf("==========[%d-%d-%d %d:%d:%d]==========\n", tm.tm_mon + 1, tm.tm_mday, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
		printf("The controller did not move left when told.\n");
		// Print in error file
		fprintf(f, "==========[%d-%d-%d %d:%d:%d]==========\n", tm.tm_mon + 1, tm.tm_mday, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
		fprintf(f, "The controller did not move left when told.\n");
		exit(-1); // Stop the program
	} else { // If the commands were received
		printf("rc: %d\n", (int) rc);	
		printf("Response: %s\n", buf); // Print the response
		printf("Moved Left!\n");
	}
	
	return rc;
	fclose(f);
}

/*
* Close connection
*/
int bluescape_close(int close) {
	rc = GClose(g); // Close the connection
	
	return rc;
}

/* Akshay Aravindan
* Galil Motion Controller Code (C)
* This is a very basic program that allows you to connect to the
* Galil controller and send a few simple commands to move it.
* This was built for exclusive use by Bluescape.
*/
