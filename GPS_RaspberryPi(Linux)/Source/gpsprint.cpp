/*------------------------------------------------------------------------------
-- SOURCE FILE: gpsprint.cpp
--
-- PROGRAM: 	GPS receiver
--
-- FUNCTIONS:
-- 				int printGPSReport(struct gps_data_t*)
--
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
#include "headers/gpsprint.h"


/*--------------------------------------------------------------------------
-- FUNCTION: 	printGPSReport - outputs the data contained in gps_data_t stuct
--
-- DATE: 		Oct. 18, 2016
--
-- REVISIONS: 
--
-- DESIGNER: 	Terry Kang, Tim Makimov 
--
-- PROGRAMMER: 	Terry Kang, Tim Makimov 
--
-- INTERFACE: 	int printGPSReport(struct gps_data_t*)
--
-- RETURNS: 	int: returns 1 if no sattelites are visible
-- NOTE: print out the basic information of the statelite retrieved from GPS, defined in gps_data_t stuct
-- This function is for version 1 of dcgps.
--------------------------------------------------------------------------*/
int printGPSReport(struct gps_data_t *newdata)
{
    bool usedflags[MAXCHANNELS];

    if (newdata->satellites_visible < 1)
	return 1;

    for (int i = 0; i < MAXCHANNELS; i++)
    {
	usedflags[i] = false;
	for (int j = 0; j < newdata->satellites_used; j++)
	    if (newdata->used[j] == newdata->PRN[i])
		usedflags[i] = true;
    }
    for (int i = 0; i < MAX_POSSIBLE_SATS; i++)
    {
	if (i < newdata->satellites_visible)
	{
	    cout << "PRN:\t" << setw(3) << newdata->PRN[i] << "\t";
	    cout << "Elevation:\t" << setfill('0') << setw(2) << newdata->elevation[i] << "\t";
	    cout << "Azimuth:\t" << setfill('0') << setw(3) << newdata->azimuth[i] << "\t";
	    cout << "SNR:\t" << setfill('0') << setw(2) << newdata->ss[i] << "\t";
	    cout << "Used:\t" << ((usedflags[i]) ? 'Y' : 'N') << endl;
	}
    }

    char buf[256];
    if (isnan(newdata->fix.time) == 0)
    {
	(void)unix_to_iso8601(newdata->fix.time, buf, sizeof(buf));
    }
    else
	(void)snprintf(buf, sizeof(buf), "n/a");
    cout << buf << ": ";
    string lat = "n/a";
    string lng = "n/a";
    string address = "n/a";
	
    if (newdata->fix.mode >= MODE_2D && isnan(newdata->fix.latitude) == 0 && isnan(newdata->fix.longitude) == 0)
	{
	    lat = to_string(fabs(newdata->fix.latitude));
	    lng = to_string(fabs(newdata->fix.longitude));
        address = getAddress(to_string(newdata->fix.latitude), to_string(newdata->fix.longitude));
	    lat += "  " + (newdata->fix.latitude < 0) ? 'S' : 'N';
	    lng += "  " + (newdata->fix.longitude < 0) ? 'W' : 'E';
	}
    cout << "Latitude: " << lat << " " << "Longitude: " << lng << endl;
    cout << "Address: " << address << endl << endl;

    return 0;
}
