

/*
//Program Requirements:
a.Ask the user for the name of the input file.Give the user 5 trials to enter the correct name; otherwise exit the program with a message.
b.Ask the user to enter the output file name where you need to save the sorted data in.
c.Read the data from the file into two arrays(or vectors).
d.Write a function to sort the read data in ascending order based on the price of the plants with the corresponding plant names.
e.The sorted data should be saved in the output file.
f.Write a function to find the plant that has the maximum price and print it to the user.
g.Write a function to find the plant that has the minimum price and print it to the user.
h.Write a function to read two prices from the user in any order.
i.Write a function to print all plants that their prices fall between the two prices that been read in the previous function.
j.Display a menu to the user to select a task such as :
To find the highest price enter : H To find the lowest price enter : L To list plants within a range enter : R To exit enter : E
k.Your program should continue running until the user enter ‘E’.
l.All your outputs should be formatted using the appropriate manipulators.
*/

//including the required files and namespaces for algorithms, I/O, string operations, vector operations, mapping, manipulation and File streaming as well as the C++ Standard Library
#include <algorithm> 
#include<iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <fstream>
using namespace std;

//Save sorted items using the prices to a file.
void saveSorted(vector<string> &items, vector<float_t> &prices)
{
	//sorting the items
	//fill in the map 
	multimap<float_t, string> map;

	for (size_t p = 0; p < items.size(); ++p)
		map.insert(make_pair(prices[p], items[p]));

	// copy back out into the vectors 
	size_t p = 0;

	for (auto i = map.begin(); i != map.end(); ++i)
	{
		items[p] = i->second;
		prices[p] = i->first;
		++p;
	}

	//Save to another file
	string outFileName; //output file name
	ofstream outfile; //output file stream.

	cout << "Please enter output file name:";
	cin >> outFileName;
	outfile.open(outFileName);
	// output  
	for (size_t p = 0; p < items.size(); ++p)
		outfile << left << std::setw(25) << items[p] << "$" << left << std::setw(15) << prices[p] << endl;
	outfile.close();
}
//get range values between min and max for items price
void getRange(vector<string> &items, vector<float_t> &prices, float min, float max)
{
	//get the upper(max) and the lower(min) bounds for the range in the prices array and outputing the items. 
	auto first = lower_bound(prices.begin(), prices.end(), min);
	auto last = upper_bound(prices.begin(), prices.end(), max);
	for (auto it = first; it != last; ++it) cout << left << std::setw(25) << items[it - prices.begin()] << "$" << left << std::setw(15) << prices[it - prices.begin()] << endl;
}
//prints items in-between a Min-Max range.
void Range(vector<string> &items, vector<float_t> &prices)
{
	float min, max; //to hold the min and max prices values
	string MinMax;// to hold the input from the user

	//asking user to input Min-Max value.
	cout << "Please enter the range Min-Max values: ";
	cin >> MinMax;
	// get the Min and Max values from user and assiging them to the min and max values after conversion to float. 
	min = stof(MinMax.substr(0, MinMax.find('-', 0)).c_str());
	max = stof(MinMax.substr(MinMax.find('-', 0) + 1).c_str());
	//switch min and max if the user inputed Max-Min value in the begining.
	if (min > max)
	{
		float temp = min;
		min = max;
		max = temp;
	}
	//get the range values and print them;
	getRange(items, prices, min, max);
}

//prints the the item with lowest price.
void getMin(vector<string> &items, vector<float_t>& prices)
{
	//get index of the lowset item using prices begin location - the min price location in memory
	int index = min_element(prices.begin(), prices.end()) - prices.begin();
	cout << "The lowest item in price: " << left << std::setw(25) << items[index] << "$" << left << std::setw(15) << prices[index] << endl;
}
//prints the the item with highest price.
void getMax(vector<string> &items, vector<float_t> &prices)
{
	//get index of the highest item using prices begin location - the max price location in memory
	int index = max_element(prices.begin(), prices.end()) - prices.begin();
	cout << "The highest item in price: " << left << std::setw(25) << items[index] << "$" << left << std::setw(15) << prices[index] << endl;
}

//Main Function of program
int main()
{
	string inFileName; //to store the input file path
	char option;// to store the command option of the user

	vector<string> items; vector<float_t> prices; //vector lists of items and prices in the file
	cout << "Please enter the file name: ";
	for (int i = 0; i < 5; i++)
	{
		cin >> inFileName;
		fstream file;

		//open file for input or output without creating a file.
		file.open(inFileName, ios_base::out | ios_base::in);  // will not create file
		if (file.is_open())
		{
			//If file exists, input the values to the items and prices arrays.
			string file_line;
			while (getline(file, file_line))
			{
				items.push_back(string(file_line.substr(0, file_line.find('\t'))));
				prices.push_back(float_t(stof(file_line.substr(file_line.find_last_of('\t') + 1).c_str())));
			}
			file.close();
			//sort the array and save to a file
			saveSorted(items, prices);
			break;
		}
		//In the last try, exit the program.
		if (i == 4)
		{
			cout << "You ran out of tries. Exiting...";
			return 0;
		}
	}
	while (true)
	{
		//show user option menu for the user for acions to preform
		cout << "To find the highest price enter : H\n"
			<< "To find the lowest price enter : L\n"
			<< "To list plants within a range enter : R\n"
			<< "To exit enter : E\n";
		cin >> option;

		switch (option)
		{
		case 'H': case'h':
			//get item with max price.
			getMax(items, prices);
			break;
		case 'L': case'l':
			//get item with min price.
			getMin(items, prices);
			break;
		case 'R':case'r':
			//get item between min-max price.
			Range(items, prices);
			break;
		case 'E':case'e':default:
			//exit
			return 0;
		}
	}
}
