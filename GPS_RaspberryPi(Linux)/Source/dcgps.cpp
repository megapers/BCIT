#include "headers/dcgps.h" 
/*------------------------------------------------------------------------------
-- SOURCE FILE: dcgps.cpp - GPS Program Entrance
--
-- PROGRAM: 	GPS receiver
--
-- FUNCTIONS:
-- 				int main (int argc, char **argv)
-- DATE: 		Oct. 18, 2016
--
-- REVISIONS: 

-- DESIGNER: 	Terry Kang, Tim Makimov 
--
-- PROGRAMMER: 	Terry Kang, Tim Makimov 
--
-- NOTES: The program reads and outputs GPS location data on the screen by 
using Open Source GPSD utility. The environment is Linux on Raspberry Pi board.    

------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------
-- FUNCTION: 	main - program entrance
--
-- DATE: 		Oct. 18, 2016
--
-- REVISIONS: 
--
-- DESIGNER: 	Terry Kang, Tim Makimov 
--
-- PROGRAMMER: 	Terry Kang, Tim Makimov 
--
-- INTERFACE: 	int main(int, char**)
--
-- RETURNS: 
-- 				int signifying state at exit 
--
-- NOTES: Help is available if user passes no argument or '-h'.
-- '-c' argument for version 1 of dcgps that has basic functions and prints data line by line.
-- '-g' argument for version 2 of dcgps thas has more functions and console graphics using ncurses.
--------------------------------------------------------------------------*/
int main(int argc, char **argv)
{
	if(argc != 2 || !strcmp(argv[1], "-h") || (strcmp(argv[1], "-c") && strcmp(argv[1], "-g")))
	{
			cout << "Usage: "<< argv[0] <<" [-h | -c | -g]"<<endl;
			cout << "  -h      Show this help, then exit"<<endl;
			cout << "  -c      version 1 without user interface"<<endl;
			cout << "  -g      version 2 with user interface"<<endl;
			return 1;

	}
	
	gpsmm gps_rec("localhost", DEFAULT_GPSD_PORT);
    if (gps_rec.stream(WATCH_ENABLE|WATCH_JSON) == NULL) {
        cerr << "No GPSD running.\n";
        return 2;
    }

	if(!strcmp(argv[1], "-c"))
	{
		if(readGPS(gps_rec)==1){
			cerr << "Faild to read GPS.\n";
			gps_rec.~gpsmm();
			return 3;
		}
	}else if(!strcmp(argv[1], "-g")){
		initializeWindows(gps_rec);
	}
	return 0;
}