/*------------------------------------------------------------------------------
-- SOURCE FILE: gps-utils.cpp - reads GPS data
--
-- PROGRAM: 	GPS receiver
--
-- FUNCTIONS:
-- 				int readGPS(gpsmm&)
				string getAddress(const string&, const string&)
				string getAddress(const string&, const string&)
--
-- DATE: 		Oct. 18, 2016
--
-- REVISIONS: 

-- DESIGNER: 	Terry Kang, Tim Makimov 
--
-- PROGRAMMER: 	Terry Kang
--
-- NOTES: The program reads and outputs GPS location data on the screen by 
-- using Open Source GPSD utility. The environment is Linux on Raspberry Pi board.    

------------------------------------------------------------------------------*/
#include "headers/gps-utils.h"

/*--------------------------------------------------------------------------
-- FUNCTION: 	readGPS - reads data from GPS into gps_data_t structure
--
-- DATE: 		Oct. 18, 2016
--
-- REVISIONS: 
--
-- DESIGNER: 	Terry Kang, Tim Makimov 
--
-- PROGRAMMER: 	Terry Kang
--
-- INTERFACE: 	int readGPS(gpsmm&)
--
-- RETURNS: 	int: returns 1 if read from GPS is not successful

--------------------------------------------------------------------------*/
int readGPS(gpsmm &gps_rec)
{
    for (;;)
    {
	struct gps_data_t *newdata;
	if (!gps_rec.waiting(50000000))
	    continue;
	if ((newdata = gps_rec.read()) == NULL)
	{
	    cerr << "Read error.\n";
	    return 1;
	}
	else
	{
	    printGPSReport(newdata);
	}
    }
}

/*--------------------------------------------------------------------------
-- FUNCTION: 	write_data - utility function that is used by getAddress 
				function
--
-- DATE: 		Oct. 18, 2016
--
-- REVISIONS: 
--
-- DESIGNER: 	Terry Kang
--
-- PROGRAMMER: 	Terry Kang
--
-- INTERFACE: 	size_t write_data(void*, size_t, size_t, void*)
--
-- RETURNS: 	size_t: 

-- NOTE: stores the response from curl request in the global variable to 
be parsed later in getAdress function.
--------------------------------------------------------------------------*/
size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp)
{
    int byteNum = size * nmemb;
    *resultString += string((char *)buffer, byteNum);
    return size * nmemb;
}

/*--------------------------------------------------------------------------
-- FUNCTION: 	getAddress
--
-- DATE: 		Oct. 18, 2016
--
-- REVISIONS: 
--
-- DESIGNER: 	Terry Kang
--
-- PROGRAMMER: 	Terry Kang
--
-- INTERFACE: 	string getAddress(const string&, const string&)
--
-- RETURNS: 	string: Postal address of the location
-- NOTE: send a request to google maps api with the latitude and longitude retrieved from GPS,
-- and get the response with the locaion's info as json.
-- after getting response, parse the response and return the formatted address.'
--------------------------------------------------------------------------*/
string getAddress(const string &lat, const string &lng)
{
    CURL *curl;
    CURLcode res;
    string address = "n/a";

    curl = curl_easy_init();
    if (curl)
    {
	try
	{
	    string url = "https://maps.googleapis.com/maps/api/geocode/json?latlng=";
	    url += lat + "," + lng;
		url += "&key=AIzaSyC9utt1WykD9z2RE8FxgwD94uFhSJ3nAuo";
	    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

	    string json;
	    resultString = &json;

		/* get response and process */
	    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);

	    /* Perform the request, res will get the return code */
	    res = curl_easy_perform(curl);
	    /* Check for errors */
	    if (res != CURLE_OK)
		curl_easy_strerror(res);

	    /* always cleanup */
	    curl_easy_cleanup(curl);

	    Document document;
		
	    if (!document.Parse<0>(json.c_str()).HasParseError()){
			if(document["results"].Size()>1)
				address = document["results"][0]["formatted_address"].GetString();
		}
	}
	catch (int e)
	{
	}
    }
    return address;
}
