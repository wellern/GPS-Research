/*
  This is the main driver function that constantly analyzes data from 
  the
  different clients. It checks if cars are within a certain range and if
  there average speed is below the threshold.If it is it creates a flag 
  it
  then will create a txt file of flags and send it to the clients. It 
  then
  waits for the files to be sent again.
*/

#include <iostream> 
#include <string> 
#include <fstream>
#include <sstream> 
#include <ctime>
#include <cctype> 
#include <cmath>
#include <vector> 
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 


using namespace std;

vector<double> lane1;
vector<double> lane1T;
vector<double> lane2;
vector<double> lane2T;
vector<double> lane3;
vector<double> lane3T;
vector<double> lane1AVG;
vector<double> lane2AVG;
vector<double> lane3AVG;
float lane1X[4] = {}; //put cordinates here
float lane2X[4] = {};
float lane3X[4] = {};
float lane1Y[4] = {}; 
float lane2Y[4] = {};
float lane3Y[4] = {};


/*function declaration
  ---------------------- 
*/

void loadFile(string fileName);
void averageSpeed(vector<double> speed, vector<double> time, vector<double> avg);
void congestion(vector<double> v); 
void pause(int dur); 
void printList(); 
bool pointInPolygon(float x, float y, float polyX[], float polyY[]);
void clearScreen();

/*
  The main program begins by waiting till the files from the clients 
  have been recieved. It then loads the calulates each entry to see 
  what lane to store the data in. It uses vectors for storage. It 
  stores there speed and time of each event. Then we find the average
  speed of each item making sure there is more than one car. If not we
  dont record the data. Then using the congestion function we see how many 
  flags occured in the 11 second window. It writes to a text file 
  that tells if there is congestion or not. Delete all is then called
  that deletes all the memory that was alocated for the link list 
  and waits for the clients to send more data.
  ---------------------------------------------------------------- 
*/

  
int main() {
  
  int a;
  while(1){
    a = 0;
    while(a < 2){
      struct stat st;
      if(stat("./text1.txt",&st) == 0)
	a = 2;
    }
    a = 0;
    while(a < 2){
      struct stat st;
      if(stat("./text2.txt",&st) == 0)
	a = 2;
    }
    pause(2);
    loadFile("text1.txt");
    pause(2);
    clearScreen();
    loadFile("text2.txt");
    pause(2);
    clearScreen();
    //averageSpeed();
    //congestion();
    system("./fileTransfer.sh");
    system("./fileTransfer1.sh");
    system("rm Congestion.txt");
    system("rm text1.txt");
    system("rm text2.txt");
    lane1.clear();
    lane1T.clear();
    lane2.clear();
    lane2T.clear();
    lane3.clear();
    lane3T.clear();
    lane1AVG.clear();
    lane2AVG.clear();
    lane3AVG.clear();
    
  }
  return 0;
}
/*
  This function reads in a text file from a client and adds the data 
  into a
  linked list. The data is stored acorrding to time.
  
  ------------------------------------------------------------------------ 
*/ 
void loadFile(string fileName){
  cout << "loading file " << endl;
  string str;
  ifstream infile;
  infile.open(fileName.c_str());
  if(!infile.is_open())
    {
      cout << "ERROR loading file \n";
      cout << endl << endl << endl;
      return;
    }
  while(!infile.eof())
    {
      getline(infile,str);
      float lat;
      float lon;
      double s;
      double t;
      istringstream ss(str);
      ss >> lat >> lon >> s >> t;
      if(pointInPolygon(lat, lon, lane1X, lane1Y) == true){
	lane1.push_back(s);
	lane1T.push_back(t);
      }
      if(pointInPolygon(lat, lon, lane2X, lane2Y) == true){
	lane2.push_back(s);
	lane2T.push_back(t);
      }
	  if(pointInPolygon(lat, lon, lane3X, lane3Y) == true){
	    lane3.push_back(s);
	    lane3T.push_back(t);
	  }
    }
  infile.close();
}

/*
  This file will walk through vectors and calculate average speed 
  and make sure there is more than one car in a lane befores storing
  average speed
  
  --------------------------------------------------------------
*/
void averageSpeed(vector<double> speed, vector<double> time, vector<double> avg){
  int count;
  double Time;
  double average;
  for(int k=1; k < 11; k++)
    {
      count = 0;
      average = 0;
      for(int j =0; j < time.size(); j++)
	{
	  if(time[j] == k){
	    count++;
	    average += speed[j];
	  }
	}
      if(count > 1)
	avg.push_back(average/count);
    }
  
}
/*
  Walk through lane vectors Keep a count if speed is below threshold 
  increase count. If count is above second threshold write to a txt 
  file that there is congestion. If the count is below the threshold 
  write to the text file that there in no congestion on the roadway.
  
  ---------------------------------------------------------------------------- 
*/
void congestion(vector<double> v){
  int count = 0;
  for(int j = 0; j < v.size(); j++)
    cout << "v[j] " << v[j] << endl;
   for(int i =0; i < v.size(); i++){
     if(v[i] < 1.0) //speed threshold is firts number
       count++;
   }
   if(count < 3){ //threshold for how many flags are necessay for congestion
     ofstream myfile;
     myfile.open("Congestion.txt");
     myfile << "There is no congestion on the roadway.\n";                                 //Need to change messages so if lane 1 is busy or lane 2 or both. Tell robots what direction to go.
     myfile.close();
     
   }
   if(count >= 3){
     ofstream myfile;
     myfile.open("Congestion.txt");
     myfile << "There is congestion on the roadway.\n";
     myfile.close();
   }
}
/*
  This function is used to pause system in order to make sure process is
  finished before passing handle to next part of the program
  
  ------------------------------------------------------------------------- 
*/
void pause(int dur){
  
  int temp = time(NULL) + dur;
  
  while(temp > time(NULL));
}



/*
  This function takes in a point and boundries of a polygon.
  It then determines if the point is in the polygon returning a boolean.
  ------------------------------------------------------------------
*/
bool pointInPolygon(float x, float y, float polyX[], float polyY[])
{
  cout << "came here" << endl;
  int polyCorners = 4;
  int   i, j=polyCorners-1 ;
  bool  oddNodes= false;
  
  for (i=0; i<polyCorners; i++) {
    if ((polyY[i]<y && polyY[j]>=y) || (polyY[j]<y && polyY[i]>=y))
      {
	cout << "should come here" << endl;
	if (polyX[i]+(y-polyY[i])/(polyY[j]-polyY[i])*(polyX[j]-polyX[i]) < x)
	  {
	    oddNodes=!oddNodes;
	    cout << "came here1 "<< endl;
	  }
      }
    j=i; 
  }
  return oddNodes;
}

/*
  This function will clear the screen with 5 blank lines
  -------------------------------------------------
*/
void clearScreen(){
  
  for(int k=0; k < 5;k++)
    cout << endl;
}
