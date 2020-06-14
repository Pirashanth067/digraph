// digraph.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <math.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <regex>
#include <sstream>
#include <iterator>
#include <limits.h> 
#include <limits>       

using namespace std;

//void dijkstra(digraph, vector <vector<int>>, int, string );

//void sample(int);
void dijkstra(digraph digraph, vector <vector<int>> matrix, int src, string outputfile);
class digraph {
private:
	vector <vector<int>> vec2D;
public:
	digraph()
	{}
	string ttloutput;
	void writefile(string str, string filename) {
		ofstream File;
		File.open("../data/" + filename, fstream::app);
		File << str << endl;
		if (!File.is_open() || File.fail())
		{
			File.close();
			printf("\nError : failed to erase file content !");
		}
		File.close();
	}
	void clearfile(string filename) {
		ofstream File;
		File.open("../data/" + filename, fstream::out | fstream::trunc);
		File.close();
	}

	void vectorResize(int vertices, vector<string> matrix,string outputfile,int startingVertex) {
		vec2D.resize(vertices); //constructed vec2d vector has been resized to store inside a 2d vector
		for (int i = 0; i < vertices; i++)
		{
			vec2D[i].resize(vertices);
		}
		for (int i = 0; i < matrix.size(); i++)
		{
			int row = i / vertices;
			int col = i % vertices;
			vec2D[row][col] = stoi(matrix[i]);
		}
		digraph obj;
		writefile("", outputfile);
		cout << "total vertices :" << vertices << endl;
		cout << "Start vertex :" << startingVertex << endl;
		writefile("Start vertex :" + to_string(startingVertex), outputfile);
		writefile("", outputfile);
		//sample(5);
		dijkstra(obj, vec2D, startingVertex, outputfile);  //calling the dijkstra algorithm
	}

	int minDistance(int distance[],
		bool vertex[], int n)
	{

		// Initialize min value 
		int min = INT_MAX, minimum_index;

		for (int i = 0; i < n; i++)
			if (vertex[i] == false && distance[i] <= min)
				min = distance[i], minimum_index = i;

		return minimum_index;
	}

	// this method is to print shortest 
	// whole path of the vertex from source to j 
	// using array of the parent
	void printPath(int parentpath[], int n)
	{
		// Base Case : If j is source 
		if (parentpath[n] == -1)
			return;
		printPath(parentpath, parentpath[n]);
		ttloutput += to_string(n) + " ";
		printf("%d ", n);

	}

	/*void dijkstra(){}*/
	//this function will print the array of the details and path 
	void printSolution(int distance[], int n,
		int parentpath[], int src, string outputfile)
	{
		ttloutput = "Total Dest | Weight | Path\n";
		writefile(ttloutput, outputfile);
		printf("Total Dest | Weight | Path\n");
		ttloutput = "----------------------------------------------------------";
		writefile(ttloutput, outputfile);
		printf("----------------------------------------------------------");
		for (int i = 0; i < n; i++)
		{
			if (distance[i] == INT_MAX || distance[i] == INT_MIN || distance[i] < 0) {
				ttloutput = to_string(src) + "->" + to_string(i) + "      " + "inf" + "\t\t";
				/*ttloutput*/
				printf("\n%d -> %d \t %s ",
					src, i, "inf");
				//printPath(parentpath, i);
			}
			else if (distance[i] == 0) {
				ttloutput = to_string(src) + "->" + to_string(i) + "      " + "0" + "\t\t";
				/*ttloutput*/
				printf("\n%d -> %d \t %s ",
					src, i, "0");
				//printPath(parentpath, i);
			}
			else {
				ttloutput = to_string(src) + "->" + to_string(i) + "      " + to_string(distance[i]) + "\t\t" + to_string(src) + " ";
				/*ttloutput*/
				printf("\n%d -> %d \t %d\t\t%d ",
					src, i, distance[i], src);
				printPath(parentpath, i);
			}

			writefile(ttloutput, outputfile);

		}
	}

};

void sample(int hello){
	cout << "testing"<<hello << endl;
}
	//Dijakstra function doesnt include as a part of the class as requested
void dijkstra(digraph digraph, vector <vector<int>> matrix, int src, string outputfile)
{
		int n = matrix.size();
		int* distance = new int(n);     // The output array  distance[i] is holding the minimum distance from src to i 
		int* parentpath = new int(n);
		bool* vertex = new bool[n];

		// Initialize all distances as INFINITE and vertex[] as false 
		for (int i = 0; i < n; i++)
		{
			parentpath[i] = -1;
			distance[i] = INT_MAX;
			vertex[i] = false;
		}

		// Distance from same vertex is always 0
		distance[src] = 0;

		// Find shortest path  for all vertices 
		for (int count = 0; count < n - 1; count++)
		{
			// getting the  minimum distance vertex 
			int u = digraph.minDistance(distance, vertex, n);

			// Mark the selected vertex as true in order to proceed
			vertex[u] = true;

			// Update distance value of the 
			// adjacent vertices of the 
			// selected vertex. 
			for (int v = 0; v < n; v++)

				// Update distance[i] only if is 
				// not in vertex, there is  an edge from u to i, and total 
				//weight of path from  src to i through u is smaller  than current value of  distance[i] 

				if (!vertex[v] && matrix[u][v] &&
					distance[u] + matrix[u][v] < distance[v])
				{
					parentpath[v] = u;
					distance[v] = distance[u] + matrix[u][v];
				}
		}
		// print the array
		digraph.printSolution(distance, n, parentpath, src, outputfile);
}


int main()
{
	string inputfile, joinedchar, outputfile;
	char letter, lastletter = ' ';
	int vertices, startingVertex;
	string str, output, startingvertexoutput, ttloutput;
	vector<string> tokens, matrix;
	vector <vector<int> > vec2D;
	int n = 0, i = 0, lines = 0;
	//int **inputarray;
	cout << "Welcome to digraph by pirashanth!" << endl;                //user display
	cout << "There are input file names given below and type one of them!" << endl;                //user display
	cout << "File1.txt" << endl;
	cout << "File2.txt" << endl;
	cout << "File3.txt" << endl;
	cout << "File4.txt" << endl;
	cout << "Enter the file name : (Example :- File1.txt)" << endl;
	cin >> inputfile;													 // user input
	string inputName("../data/" + inputfile);
	ifstream file(inputName);

	if (inputfile == "File1.txt" || inputfile == "file1.txt") {
		outputfile = "Result1.txt";
	}
	else if ((inputfile == "File2.txt" || inputfile == "file2.txt")) {
		outputfile = "Result2.txt";
	}
	else if ((inputfile == "File3.txt" || inputfile == "file3.txt")) {
		outputfile = "Result3.txt";
	}
	else if ((inputfile == "File4.txt" || inputfile == "file4.txt")) {
		outputfile = "Result4.txt";
	}
	cout << inputfile << endl;
	cout << outputfile << endl;
	ttloutput = "Node | Out-neighbors ";
	std::cout << ttloutput << endl;
	//call the digraph class inorder to proceed
	digraph digraph;
	digraph.clearfile(outputfile); //call the clear file function to clear the file
	digraph.writefile(ttloutput, outputfile); //write inside the file
	while (getline(file, str)) {//proceed each line of the selected open file
		if (n == 0) {
			//cout << str << endl;
			for (int number = 0; number < str.length(); number++) {

				if (isdigit(str[number])) {
					output = output + str[number];
				}
			}
			vertices = stoi(output);
			//n = n + 1;
		}
		if (inputfile == "File1.txt" || inputfile == "file1.txt") {
			if (n == 1) {
				//cout << str << endl;
				for (int number = 0; number < str.length(); number++) {

					if (isdigit(str[number])) {
						startingvertexoutput = startingvertexoutput + str[number];
					}
				}
				startingVertex = stoi(startingvertexoutput);

			}
		}
		else {
			if (n == 2) {
				//cout << str << endl;
				for (int number = 0; number < str.length(); number++) {

					if (isdigit(str[number])) {
						startingvertexoutput = startingvertexoutput + str[number];
					}
				}
				startingVertex = stoi(startingvertexoutput);
				cout << str << endl;
				digraph.writefile(str, outputfile);
			}
		}
		if (n > 2) {
			istringstream iss(str);//store the array from file to tokens[]
			copy(istream_iterator<string>(iss),
				istream_iterator<string>(),
				back_inserter(tokens));

			ttloutput = to_string(n - 3) + "    | " + ' '; //store the specific format of the string for saving inside a file
			for (int i = 0; i < tokens.size(); i++) {
				if (tokens[i] != "0") {
					ttloutput += to_string(i) + ":" + tokens.at(i) + ' ';
				}
			}
			if (!tokens.empty()) {
				digraph.writefile(ttloutput, outputfile);//stored format of string is writing inside the result file
				std::cout << ttloutput;
				i = 0;
			}
			else {
				i = 1;
			}
			cout << endl;
			ttloutput.clear();
		}
		if (i == 0) {
			n++;
		}
		matrix.insert(matrix.end(), tokens.begin(), tokens.end()); //insert all the token[] inside a bigger matrix
		tokens.clear();
	}
	digraph.vectorResize(vertices,matrix,outputfile,startingVertex);

	
}
