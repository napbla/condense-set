// Author : Lam Tuan Anh         1570202
// 	    Quach Dinh Hoang     157
// This program will condense the set of sample for using in 
// k-NN clasification.
// Usage: condense <filename> <delimiter> <classifier position> <debug>
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>

using namespace std;

vector<vector<float> > data;
vector<vector<float> > result;

int classifier_i;
char delimiter;
static int debug = 0;
static int hasid = 0;
string filename;

void print(vector<vector<float> > &a, int* b, int is_condense = 1)
{
	for (vector<vector<float> >::size_type i = 0; i<a.size(); i++)
	{
		if (b[i]==is_condense)
		{
			for (vector<float>::size_type j = 0; j< a[i].size()-1; j++)
				cout<<a[i][j]<<delimiter;
			cout<<a[i][a[i].size()-1] << "\n";
		}
	}
}

void print(vector<float> &a)
{
	for (vector<float>::size_type i = 0; i<a.size()-1; i++)
		cout << a[i] << delimiter;
	cout<<a[a.size()-1]<<"\n";
}

void split(const std::string &s, char delim, vector<float> &elems) {
	stringstream ss;
	ss.str(s);
	string item;
	while (std::getline(ss, item, delim)) 
	{
		if(debug)
			cout<< "Read item: "<< item <<"\n";
		elems.push_back(stof(item));
	}
}

vector<float> split(const std::string &s, char delim) {
	vector<float> elems;
	split(s, delim, elems);
	return elems;
}

float distance (vector <float> &a, vector <float> &b){
	assert (a.size() == b.size());
	float sum = 0;
	for (vector<float>::size_type i = 0; i!=a.size(); i++) {
		if (i==0 && hasid>0)
			continue;
		if (i != classifier_i)
		       sum += pow(b[i] - a[i],2);
	}
	return sqrt(sum);
}

void condens (vector < vector <float> > &train, int classifier)
{
	int condense_set [train.size()];
	memset(condense_set, 0, sizeof(condense_set));
	int condense_max_pos = 1;
	int condense_sum = 1;
	float condense_hash = 1;
	float old_condense_hash;
	float smallest_distance;
	condense_set[0] = 1;
	if (debug)
		cout << "Step 1 finished\n";
	do {
		old_condense_hash = condense_hash;
		//step 2
		int reduce_position = 0;
		do{
			if (condense_set[reduce_position])
			{
				reduce_position++;
				continue;
			}
			smallest_distance = numeric_limits<float>::max();
			float temp = 0;
			int position = -1;
			for (vector<float>::size_type i=0; i<condense_max_pos; i++)
			{
				if (condense_set[i]&& i!=reduce_position)
				{
					if (debug) 
						cout << "i:=" << i << "\n";
					temp = distance(train[i],train[reduce_position]);
					if (debug)
						cout << "Dist = " << temp << "\n";
					if (temp < smallest_distance)
					{
						smallest_distance = temp;
						position = i;
					}
					else
						if (temp == smallest_distance && 
							train[i][classifier]!=train[reduce_position][classifier])
							position = i;
				}
			}
			if (debug)
			{
				cout << "Position :" << position << "\n";
				cout << "reduce position" << reduce_position << "\n";
				cout << "Condense max pos"<< condense_max_pos << "\n";
				cout << "reduce pos classifier" << train[reduce_position][classifier] <<"\n";

				cout << "condense pos classifier" << train[position][classifier] <<"\n";
			}
			if (position!= -1 && 
				train[reduce_position][classifier]!=train[position][classifier])
			{	
					condense_set[reduce_position] = 1;
					condense_hash += (reduce_position + 1);
					condense_sum++;
					if (condense_max_pos <= reduce_position)
						condense_max_pos = reduce_position + 1;
			}
			reduce_position++;
			if (debug)
			{
				cout << "Step 2 is done, reduce position is " << reduce_position << "\n";
				cout << "Condense size is " << condense_sum  << "\n";
			}
		}
		//step 3	
		while(reduce_position < train.size());
		if (debug)
			cout << "Step 3 is done\n";	
		//step 4
		if (debug)
		{
			cout << "Step 4 is done! reduced size is" << train.size() - condense_sum  <<" \n";
			cout << "Reduced set : \n";
			print(train, condense_set, 0);
			cout << "Condensed set : \n";
			print(train, condense_set, 1);
		}	
	}
	//step 5
	while (old_condense_hash != condense_hash && 
		train.size()!=condense_sum);
	if (debug)
		cout << "Step 5 is done\n";
	print(train, condense_set, 1);
}

void help()
{
	cout << "Usage: condense [-f --file filename] [-p --classifier-position position] [-d --delimiter delimiter_char] (--debug --hasid) \n";
	cout << "Option : \n";
	cout << "\t filename - path to file\n";
	cout << "\t delimiter - use \" \" if it is a space\n";
	cout << "\t classifier position - the position of the class value, counting from 0 and from left to right\n";
	cout << "\t debug - default is 0, set to 1 to print debug\n";
	cout << "\t hasid - default is 0, set to 1 if dataset has the first collumn works as an id number for the data\n";
}

int main (int argc, char* argv[]) {
	//-f : file in
	//-d : delimiter
	//-c : classifier position
	//-degub
	//
	
	int c;
	delimiter = ',';
	filename = "";
	if (argc == 1)
	{
		help();
		return 1;
	}
	while (1)
	{
		static struct option long_options[] =
		{
			{"debug", no_argument, &debug, 1},
			{"hasid", no_argument, &hasid, 1},
			{"classifier-position", required_argument, 0, 'c'},
			{"delimiter", required_argument, 0, 'd'},
			{"file", required_argument, 0, 'f'},
			{0, 0, 0, 0}
		};
		int option_index = 0;
		c = getopt_long (argc, argv, "p:d:f:", long_options, &option_index);
		if (c==-1)
			break;

		switch(c)
		{
			case 0: //for long option
				//for long option flag
				if (long_options[option_index].flag != 0)
					break;
				break;
			case 'p':
				classifier_i = stoi(optarg);
				//cout << "option c = " << classifier_i << "\n";
				break;
			case 'd':
				delimiter = optarg[0];
				//cout << "option d = " << delimiter << "\n";
				break;
			case 'f':
				filename = optarg;
				//cout << "option f = " << filename  << "\n";
				break;
			case '?':
				break;
			default:
				abort();
				break;
		}

	}	
	if (optind < argc)
	{
		cout << "nonopt argv\n";
		return 1;
	}
	//cout << "Debug : " << debug << "\n";
	string line;
	if (filename == "")
	{
		if (debug)
			cout << "Delimiter:" << delimiter << "\n";
		while (getline(cin, line))
			data.push_back(split(line, delimiter));
		if (debug)
			cout << "Data is loaded\n";
		condens(data, classifier_i);
	}
	else
	{
		ifstream myfile(filename);
		if (myfile.is_open())
		{
			if (debug)
				cout << "Delimiter:" << delimiter << "\n";
			while (getline(myfile, line))
				data.push_back(split(line, delimiter));
			myfile.close();
			if (debug)
				cout << "Data is loaded\n";
			condens(data, classifier_i);
		}
		else cout << "Unable to open file\n";
	}
	return 0;
}
