// This program will do 
// k-NN clasification.
// Usage: knn <filename> <delimitor> <classifier position> <debug>
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <assert.h>
using namespace std;
vector<vector<float> > train_data;
vector<vector<float> > test_data;
int classifier_i;
char delimitor;
int k_number = 1;
int debug = 0;
int hasid = 0;

struct distance_result{
	float distance;
	int class_type;
};

void print(vector<vector<float> > &a)
{
	for (vector<vector<float> >::size_type i = 0; i<a.size(); i++)
	{
		for (vector<float>::size_type j = 0; j< a[i].size()-1; j++)
			cout<<a[i][j]<<delimitor;
		cout<<a[i][a[i].size()-1] << "\n";
	}
}

void print(vector<float> &a)
{
	for (vector<float>::size_type i = 0; i<a.size()-1; i++)
		cout << a[i] << delimitor;
	cout<<a[a.size()-1]<<"\n";
}

void split(const std::string &s, char delim, vector<float> &elems) {
	stringstream ss;
	ss.str(s);
	string item;
	while (std::getline(ss, item, delim)) 
		elems.push_back(stof(item));
}

vector<float> split(const std::string &s, char delim) {
	vector<float> elems;
	split(s, delim, elems);
	return elems;
}

float distance (vector <float> &a, vector <float> &b){
	float sum = 0;
	for (vector<float>::size_type i = 0; i!=a.size();i++) {
		if (hasid && i==0)
			continue;
		if (i != classifier_i)
		       sum += pow(b[i] - a[i],2);
	}
	return sqrt(sum);
}

int knn (vector < vector <float> > &train, vector<float> &test, int classifier, int k)
{
	vector <distance_result> ranks;
	float temp;
	distance_result temp_dr;
	for (vector<vector<float> >::size_type i = 0; i< train.size(); i++)
	{
		temp = distance(train[i],test);
		temp_dr.distance = temp;
		temp_dr.class_type = train[i][classifier];
		if (ranks.size() == 0)
			ranks.push_back(temp_dr);
		else
		{
			bool check = false;
			for (vector<float>::size_type j = 0; j < ranks.size(); j++)
				if (temp < ranks[j].distance)
				{
					ranks.insert(ranks.begin()+j, temp_dr);
					check = true;
					break;
				}
			if (!check && ranks.size()<k)
				ranks.push_back(temp_dr);
			if(ranks.size() > k)
				ranks.erase(ranks.end()-1);
		}
	}
	float sum = 0;
	for (vector<distance_result>::size_type i = 0; i< ranks.size(); i++)
	{
		sum += ranks[i].class_type;
	}
	float average = sum/ranks.size();
	float min = numeric_limits<float>::max();
	float min_rank = round(average);
	float min_temp;
	for (vector<distance_result>::size_type i = 0; i< ranks.size(); i++)
	{
		min_temp = abs(ranks[i].class_type-average);
		if (min_temp < min)
		{
			min = min_temp;
			min_rank = ranks[i].class_type;
		}
	}
	return min_rank;
}

int main (int argc, char* argv[]) {
	if (argc == 1)
	{
		cout << "Usage: knn <train_filename> <test_filename> <delimiter> <classifier position> <k number> <debug=0> <hasid>\n";
		cout << "Option : \n";
		cout << "\t train_filename - path to train dataset file\n";
		cout << "\t test_filename - path to test dataset file\n";
		cout << "\t delimiter - use " " if it is a space\n";
		cout << "\t classifier position - the position of the class value, counting from 0 and from left to right\n";
		cout << "\t k_number - k number in knn algorithm\n";
		cout << "\t debug - default is 0, set to 1 to print debug\n";
		return 1;
	}
	if (argc != 8)
	{
		cout << "Wrong number of argument\n";
		return 1;
	}
	debug = stoi(argv[6]);
	classifier_i = stoi(argv[4]);
	delimitor = argv[3][0];
	k_number = stoi(argv[5]);
	hasid = stoi(argv[7]);
	if (debug)
		cout << "k number : "<< k_number << "\n";
	string line;
	ifstream myfile (argv[1]);
	if (myfile.is_open())
	{
		if (debug)
			cout << "Delimiter:" << delimitor << "\n";
		while (getline(myfile, line))
			train_data.push_back(split(line, delimitor));
		myfile.close();
		if (debug)
			cout << "Train data is loaded\n";
	}
	ifstream myfile2 (argv[2]);
	if (myfile2.is_open())
	{
		if (debug)
			cout << "Delimiter:" << delimitor << "\n";
		while (getline(myfile2, line))
			test_data.push_back(split(line, delimitor));
		myfile2.close();
		if (debug)
			cout << "Test Data is loaded\n";
	}
	else cout << "Unable to open file\n";
	float right = 0;
	float result;
	for (vector<vector<float> >::size_type i = 0; i<test_data.size(); i++)
	{
		result = knn(train_data, test_data[i], classifier_i, k_number);
		cout<< result << "\n";
		if (result == test_data[i][classifier_i])
			right++;
	}
	cout << "Right percent: \n";
        cout << right/test_data.size()*100 <<"%\n";	
	return 0;
}
