#include <iostream>
#include <fstream>
#include <string>
#include "Vector.h"
#include "math.h"
#include <cstring>
using namespace std;
// a constant char array for storing name of the input file
const char filename[] = { "data\\MetData_Mar01-2014-Mar01-2015-ALL.csv" };

// string array for storing
const string Months[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };

// structure for storing data retrieved from file
/** \brief Data Structure
 *  This is the data structure in which all the data will be inputted that is read from the data(.CSV) file. Each and every member of this structure represents
 * the data of each and every sensor which will be used to for calucation such as standard deviation, average speed etc.
 */


struct Data {
	string WAST;
	int dd;
	int mm;
	int yy;
	double DP;
	double Dta;
	double Dts;
	double EV;
	double QFE;
	double QFF;
	double QNH;
	double RF;
	double RH;
	double S;
	double SR;
	double ST1;
	double ST2;
	double ST3;
	double ST4;
	double Sx;
	double T;
};

// vector of structures for storing data
// to be used for performing various calculation
vectorClass<Data> d;
/** \brief
 *  This is the tempelate vector class which is being treated as a array of data structures D giving the advantage of dynamic
 * array.
 * \param Data struct
 * \param
 * \return
 *
 */


// offset of the record entered in the vector of structures
int index;

// Function to tokenize the string s in to substring strs based on the delimiter deltokenize
// After tokenizing, the function return the number of tokens found.
int tokenize(string s, string strs[], string del = " ")
{
	int start = 0;
	int end = s.find(del);
	int index = 0;
	while (end != -1) {
		strs[index++] = s.substr(start, end - start);
		start = end + del.size();
		end = s.find(del, start);
	}
	strs[index++] = s.substr(start, end - start);
	return index;
}
/** \brief
 * Some of the data is inputted as a string and needs to seperated, this function is responsible in doing that.
 *
 * \param string s (orignal string)
 * \param string strs[] (array of string that will store each and every part of the seperated string)
 * \param string del (this will act as a delimitter which means that it will break the string on this specific charector)
 *\return
 *
 */


// Function for computing average wind speed and
// standard deviation for a specif month and year
void AvgWS() {
	int mm, yy;
	double ws = 0.0;
	int count = 0;
	double avgSpeed = 0.0;
	double sdev = 0.0;
	cout << "Enter month and year (mm yyyy) -> ";
	cin >> mm >> yy;
	for (int i = 0; i < index; i++) {
		if (d[i].yy == yy && d[i].mm == mm)
		{
			ws += d[i].S;
			count++;
		}
	}
	///**< find average of wind speeds
	avgSpeed = ws / count;

	///**< calculate variance
	for (int i = 0; i < index; i++) {
		if (d[i].yy == yy && d[i].mm == mm)
		{
			sdev += pow(d[i].S - avgSpeed, 2);
		}
	}
	if (count > 0) {
		///**<  calculate standard deviation of wind speeds
		sdev = sqrt(sdev / avgSpeed);
		cout << Months[mm - 1] << " " << yy << ":" << endl;
		cout << "Average Speed: " << avgSpeed << " km/h" << endl;
		cout << "Sample stdev: " << sdev << endl;
	}
	else
		cout << Months[mm - 1] << " " << yy << ": No Data" << endl;

}
/** \brief Thus function serves the purpose of calculating the wind speed and the standard deviation of month and year.
 * Then it prints out the
 * \param
 * \param
 * \return
 *
 */


// Function for computing average ambient temperature and
// standard deviation for each month a specific year
void AvgAT() {
	int yy;

	///**<Arrays for storing values of each month of an year
	double at[12] = { 0.0 };
	int count[12] = { 0 };
	double avgAT[12] = { 0.0 };
	double sdev[12] = { 0.0 };
	cout << "Enter year (yyyy) -> ";
	cin >> yy;
	for (int i = 0; i < index; i++) {
		if (d[i].yy == yy)
		{
			at[d[i].mm-1] += d[i].T;
			count[d[i].mm-1]++;
		}
	}
	for (int i = 0;i < 12;i++)
		avgAT[i] = at[i] / count[i];

	for (int i = 0; i < index; i++) {
		if (d[i].yy == yy)
		{
			sdev[d[i].mm-1] += pow(d[i].T - avgAT[d[i].mm-1], 2);
		}
	}
	for (int i = 0; i < 12; i++)
	{
		sdev[i] = sqrt(sdev[i] / avgAT[i]);
		cout << yy << endl;
		cout << Months[i] << ": ";
		if (count[i] > 0)
			cout << "average: " << avgAT[i] << " degrees C, stdev: " << sdev[i] << endl;
		else
			cout << "No Data" << endl;
	}
}
/** \brief
 * This function serves the purpose of calculating the ambient temperature and standard deviation for each month of the specified year
 * \param
 * \param
 * \return
 *
 */


// Function for computing total solar radiation
// for each month of a specific year
void TSR() {
	int yy;
	double sr[12] = { 0.0 };
	cout << "Enter year (yyyy) -> ";
	cin >> yy;
	for (int i = 0; i < index; i++) {
		if (d[i].yy == yy)
			sr[d[i].mm - 1] += d[i].SR;
	}
	for (int i = 0; i < 12; i++)
	{
		cout << yy << endl;
		cout << Months[i] << ": ";
		if (sr[i] > 0)
			cout << sr[i] << " kWh/m2" << endl;
		else
			cout << "No Data" << endl;
	}
}
/** \brief
 * The function displays the total solar radiation for each month of the year inputted by the user.
 * If there is no data, then an appropriate message is displayed.
 * \param
 * \param
 * \return
 *
 */


// Function for computing average wind speed, average ambient temperature
// and their standard deviations and total solar radiation for each month
// of a specific year and store the results in a file.
void All() {
	ofstream ofile("Data\\WindTempSolar.csv");
	if (ofile) {
		int yy;
		double ws[12] = { 0.0 };
		double avgWS[12] = { 0.0 };
		double sdevWS[12] = { 0.0 };

		double at[12] = { 0.0 };
		double avgAT[12] = { 0.0 };
		double sdevAT[12] = { 0.0 };

		int count[12] = { 0 };

		double sr[12] = { 0.0 };

		cout << "Enter year (yyyy) -> ";
		cin >> yy;
		for (int i = 0; i < index; i++) {
			if (d[i].yy == yy)
			{
				ws[d[i].mm - 1] += d[i].S;
				at[d[i].mm - 1] += d[i].T;
				sr[d[i].mm - 1] += d[i].SR;
				count[d[i].mm - 1]++;
			}
		}
		for (int i = 0; i < 12; i++)
		{
			avgWS[i] = ws[i] / count[i];
			avgAT[i] = at[i] / count[i];
		}

		for (int i = 0; i < index; i++) {
			if (d[i].yy == yy)
			{
				sdevWS[d[i].mm - 1] += pow(d[i].S - avgWS[d[i].mm - 1], 2);
				sdevAT[d[i].mm - 1] += pow(d[i].T - avgAT[d[i].mm - 1], 2);
			}
		}
		ofile << yy << endl;
		for (int i = 0; i < 12; i++)
		{
			sdevWS[i] = sqrt(sdevWS[i] / avgWS[i]);
			sdevAT[i] = sqrt(sdevAT[i] / avgAT[i]);
			ofile << Months[i] << ": ";
			if (count[i] > 0)
				ofile << avgWS[i] << "(" << sdevWS[i] << "), " << avgAT[i] << "(" << sdevAT[i] << "), " << sr[i] << endl;
			else
				ofile << "No Data" << endl;
		}
		ofile.close();
	}
	else
		cout << "Couldn't open file for writing" << endl;
}

/** \brief
 * The function is responsible for computing average wind speed, ambient temperature and their
 * respective standard deviation along with the solar radiation for each month and then writing it
 * into a .CSV file.
 * \param
 * \param
 * \return
 *
 */

// Main program:
// Open an input file stream, read a Registration object,
// including its list of courses. Redisplay all information,
// and calculate the total credits taken. Write the results
// to a file stream.

int main()
{
	ifstream ifile(filename);

	///**<vectorClass<Data> d;

	if (ifile)
	{
		char str[1000];
		string strs[100];
		while (!ifile.eof())
		{
			ifile.getline(str, 1000);
			int count = tokenize(str, strs, ",");
			string ss[10];
			int cc;
			if (strlen(str) <=0 )
				continue;
			for (int i = 0; i < count ; i++)
			{
				d.push(Data());
				switch (i)
				{
					///**<first one is for date
				case 0: d[index].WAST = strs[i];
					///**<split the date into dd mm yyyy
					cc = tokenize(d[index].WAST, ss, "/");
					d[index].dd = stoi(ss[0]);
					d[index].mm = stoi(ss[1]);
					///**< extract year from the last part containing time as well
					cc = tokenize(ss[2], ss, " ");
					d[index].yy = stoi(ss[0]);
					break;

				case 1: d[index].DP = stof(strs[i]); break;
				case 2: d[index].Dta = stof(strs[i]); break;
				case 3: d[index].Dts = stof(strs[i]); break;
				case 4: d[index].EV = stof(strs[i]); break;
				case 5: d[index].QFE = stof(strs[i]); break;
				case 6: d[index].QFF = stof(strs[i]); break;
				case 7: d[index].QNH = stof(strs[i]); break;
				case 8: d[index].RF = stof(strs[i]); break;
				case 9: d[index].RH = stof(strs[i]); break;
				case 10: d[index].S = stof(strs[i]); break;
				case 11: d[index].SR = stof(strs[i]); break;
				case 12: d[index].ST1 = stof(strs[i]); break;
				case 13: d[index].ST2 = stof(strs[i]); break;
				case 14: d[index].ST3 = stof(strs[i]); break;
				case 15: d[index].ST4 = stof(strs[i]); break;
				case 16: d[index].Sx = stof(strs[i]); break;
				case 17: d[index].T = stof(strs[i]); break;
				} ///**< using switch case until the end of line so that all the data is inputted inside the struct.*/
			}
			index++;
		}
	}
	else
		cout << "Couldn't open file for reading\n";

	char choice ; /**< char is used instead of unsigned/int so that the program doesnt crash after entering any type of charector on the keyboard */
	do {
		cout << endl << endl;
		cout << "1. Average Wind Speed and standard deviation for a specific month and year\n";
		cout << "2. Average Ambient Temperature and standard deviation for each month of a year\n";
		cout << "3. Total Solar Radiation for each month of a year\n";
		cout << "4. Average Wind Speed, Average Ambient Temperature and Total Solar Radiation for each month of a year\n";
		cout << "5. Quit\n";
		cout << "Enter your choice (1-5) - > ";
		cin >> choice;
		switch (choice) {
		case '1':
			AvgWS();
			break;
		case '2':
			AvgAT();
			break;
		case '3':
			TSR();
			break;
		case '4':
			All();
			break;
		case '5': cout << "Thank You for using the program" << endl; break;
		default: cout << "Invalid input. Enter a valid value (1-5) only\n";
		}

	} while (choice != '5');
	cout << "Exiting the program ;) :)";
}
