
//  Project4
//  CS 325 - Summer 2016
//  Edwin Grove, Vijay Kumar, Michael Dambacher
//  Greedy TSP
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

#define CPS CLOCKS_PER_SEC

using namespace std;


int measureDistance(int x1, int y1, int x2, int y2);
void printTheGoods(int visted[], int distance, int cities, string arg);
int greedyTSP(int xs[], int ys[], int order[], int points);

int main(int argc, const char * argv[]) {

    
    // read in file and put in x y arrays
    
    int cityCount = 0;              // count for number of cities
    int city;
    string line;
    
    ifstream myfile;
    myfile.open(argv[1]);
    
    if(myfile.is_open())            // count the number of cities
    {
        while (getline(myfile, line))
            cityCount++;
        
    }
    
    myfile.clear();                 // rewind to front of file
    myfile.seekg(0);
    
    int xarray[cityCount];          // holds x coords
    int yarray[cityCount];          // holds y coords
    int index = 0;
    
    if(myfile.is_open())            // read data into arrays
    {
        while (!myfile.eof())
        {
            myfile >> city >> xarray[index] >> yarray[index];
            index++;
        }
    }
    
    myfile.close();                 // close file
    

    int order[cityCount];           // create array to store path
    
    clock_t t2 = clock();
    int length = greedyTSP(xarray, yarray, order, cityCount);       // run the greedy tour
    cout << "The greedy alg completed in : " << ((float) (clock() - t2)) / CPS << " s\n";
    printTheGoods(order, length, cityCount, argv[1]);               // output the solution
    
    
    return 0;
}

/****************************************************
 ** measureDistance measures the distance between
 ** two points on a x/y matrix.
 ** parameters: x/y coordinates for two points
 ** precondition: x and y coords must be valid
 ** postcondition: no change to parameters
 ** returns: distance between x and y
 ****************************************************/


int measureDistance(int x1, int y1, int x2, int y2)
{
    
    int dx = pow((float)(x1 - x2), 2);
    int dy = pow((float)(y1 - y2), 2);
    return (floor((float) (sqrt(dx + dy)) + 0.5));
    
}

/****************************************************
 ** printTheGoods prints to file an and integer and
 ** integer array, one integer per line.
 ** parameters: integer array, int, int, string
 ** precondition: variables must be initialized and 
 ** valid
 ** postcondition: output file named by string arg
 ** appended with ".tour" will be created in main
 ** directory
 ** returns: void
 ****************************************************/

void printTheGoods(int visited[], int distance, int cities, string arg)
{
    string filename = arg;
    filename.append(".tour");
    
    ofstream outfile;
    outfile.open(filename.c_str());
    
    outfile << distance << endl;
    
    for(int i = 0; i< cities; i++)
    {
        outfile << visited[i] << endl;
        
    }
    outfile.close();
}

/******************************************************
 ** greedyTSP uses a greedy method to find the shortest
 ** TSP. Solution will be non-optimal, but operationaly
 ** fast.
 ** parameters: int array for x coords, int array for
 ** y coords, int array to hold final path, int for
 ** number of vertices to cover.
 ** precondition: x array and y array must be intialized
 ** and contain valid data, order array must be intialized
 ** with correct number of vertices, points must be 
 ** correct number of vertices to cover
 ** postcondition: order array will be populated with
 ** the greedy TSP traversal
 ** returns: final length of path
 ****************************************************/

int greedyTSP(int xs[], int ys[], int order[], int points)
{
    int length = 0;                         // measure final length
    int currentCity = 0;                    // mark the current city in the path
    int nearestCity = 0;                    // mark the nearest city to current city
    int bestDist;                           // measures the shortest distance
    int nextDist;                           // measures all distances for comparison
    bool firstCity;                         // loop check: if loop finds that it is our first city checked, we adjust vars.
    int cityVisited[points];                // array to hold visited flags for each city
    for(int i=0; i<points; i++)             // if city index is flagged (==1), we know it exists in the path.
    {                                       // initialize flag array
        cityVisited[i]=0;
        
    }
    
    for (int i = 0; i < points; i++)        // loop through cities and find closest adjacent vertex
    {
        currentCity = nearestCity;
        order[i] = currentCity;
        cityVisited[currentCity] = 1;
        firstCity = true;
        bestDist = 0;
        
        for (int j = 0; j < points; j++) {
            if(cityVisited[j]==1)
                continue;
            
            nextDist = measureDistance(xs[currentCity], ys[currentCity], xs[j], ys[j]);
    
            if (nextDist < bestDist || firstCity)       // if the nextDistance found is lower than then record best distance, adjust..
            {
                bestDist = nextDist;
                nearestCity = j;
                firstCity = false;
            }
        }
        length += bestDist;                             // add bestDist to the accumulating distance
    }
                                                        // Add the connection from the last point to the first
    length += measureDistance(xs[order[points - 1]], ys[order[points - 1]], xs[order[0]], ys[order[0]]);
    return length;
}

