/*
  This is the main driver function that constantly analyzes data from the
  different clients. It checks if cars are within a certain range and if
  there average speed is below the threshold.If it is it creates a flag it 
  then will create a txt file of flags and send it to the clients. It then 
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

#define d2r 0.017453292519943

using namespace std;

struct car{
  double longitude;
  double latitude;
  double speed;
  double time;
  car* next;
};

vector<double> v;

/*function declaration
----------------------
*/
void loadFile(string fileName,car*& root);

double haversine_km(double long1,double long2,double lat1,double lat2);

void averageSpeed(car*& root);

void congestion();

void pause(int dur);

void deleteAll(car*& root);

void printList(car*& root);

/*
  The main program begins by waiting till the files from the clients have 
  been recieved. It then loads the data from the files into a linked list 
  storing them with the regards to there time. Then we walk the list with the 
  average speed function checking for congestion. Then using the congestion 
  function we see how many flags occured in the 11 second window. It writes 
  to a text file that tells if there is congestion or not. Delete all is then 
  called that deletes all the memory that was alocated for the link list and 
  waits for the clients to send more data. 
  ----------------------------------------------------------------
*/ 
int main()
{
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
    
    car *root = NULL;
    pause(2);
    loadFile("text1.txt",root);
    printList(root);
    pause(2);
    cout << endl << endl << endl << endl << endl;
    loadFile("text2.txt",root);
    pause(2);
    printList(root);
    pause(2);
    cout << endl << endl << endl << endl << endl;
    averageSpeed(root);
    congestion();
    system("./fileTransfer.sh");
    system("./fileTransfer1.sh");
    system("rm Congestion.txt");
    system("rm text1.txt");
    system("rm text2.txt");
    v.clear();
    deleteAll(root);
    
  }
}



/*
  This function reads in a text file from a client and adds the data into a
 linked list. The data is stored acorrding to time.
  ------------------------------------------------------------------------
*/

void loadFile(string fileName,car*& root){
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
  car* nodePtr = root;
  car* delPtr = root;
  while(!infile.eof())
    {
      getline(infile,str);
      double lat;
      double lon;
      double s;
      double t;
      istringstream ss(str);
      ss >> lat >> lon >> s >> t;
      car* newNode = new car;
      newNode->time = t;
      newNode->longitude = lon;
      newNode->latitude= lat;
      newNode->speed = s;
      //cout << newNode->time << endl;
      //cout << newNode->longitude << endl;
      //cout << newNode->latitude << endl;
      //cout << newNode->speed << endl;
      //cout << "did i make it here? " << endl;
      nodePtr = root;
      delPtr = root;
      if(root == NULL){
	root = newNode;
	newNode->next = NULL;
	//cout << "case 1" << endl;
      }
      else if(newNode->time <= root->time){
	root = newNode;
	newNode->next = nodePtr;
	//cout << "case 2" << endl;
      }
      else{
	//cout << "case 3" << endl;
	//nodePtr = root;
	//cout <<"nodePtr next " << nodePtr->next << endl;
	//cout << "newNode time " << newNode->time << endl;
	//cout << "nodePtr time " << nodePtr->time << endl;
	while(newNode->time > nodePtr->time && nodePtr->next != NULL){
	  //cout << "while loop" << endl;
	  delPtr = nodePtr;
	  nodePtr = nodePtr->next;
	  
	}
	if(nodePtr->next == NULL){
	  //cout << "case 4" << endl;
	  nodePtr->next = newNode;
	  newNode->next = NULL;
	  
	}else{
	  //cout << "case 5" << endl;
	  delPtr->next = newNode;
	  newNode->next = nodePtr;
	  
	}
      }
    }
  infile.close();
}




/*
  This function is usued to calculate the distance between two devices in km's
  -------------------------------------------------------------------------
*/

double haversine_km(double long1,double long2,double lat1,double lat2){
  
  double dlong = (long2 - long1) * d2r;
  double dlat = (lat2 - lat1) * d2r;
  double a = pow(sin(dlat/2.0), 2) + cos(lat1*d2r) * cos(lat2*d2r) * pow(sin(dlong/2.0), 2);
  double c = 2 * atan2(sqrt(a), sqrt(1-a));
  double d = 6367 * c;
  return d;
}

/*
This function walks the list check to see average speed and if the cars are 
within a raidus to consider themselves close to  another car 
----------------------------------------------------------------------------
*/

void averageSpeed(car*& root){
  int count;
  count = 0;
  car* nodePtr = root;
  car* delPtr = nodePtr->next;
  while(delPtr->next != NULL)
    {
      count++;
      if(nodePtr->time == delPtr->time){
	cout << "SHOULD COME HERE" << endl;
	double distance = haversine_km(nodePtr->longitude,delPtr->longitude,nodePtr->latitude,delPtr->latitude);
	double speed = (nodePtr->speed + delPtr->speed)/2.0;
	cout << "distance " << distance << endl;
	cout << "speed " << speed << endl;
	if(distance < .04){ //minimal distance
	  cout << "Cars are close " << endl;
	  v.push_back(speed);
	}else{
	  v.push_back(-1.0);
	  cout << "Cars are not close " << endl;
	}
	if(delPtr->next == NULL){
	  cout << "case 1 " << endl;
	  nodePtr = delPtr;
	}
	else if(delPtr->next->next == NULL){
	  nodePtr = delPtr->next;
	  cout << "case 2 " << endl;
	}
	else{
	  cout << "case 3" << endl;
	  delPtr = delPtr->next->next;
	  nodePtr = nodePtr->next->next;
	}
      }
      else{
	cout << "SHOULD NOT COME HERE " << endl;
	v.push_back(-1.0);
	if(delPtr->next == NULL){
	  cout << "case 4" << endl;
	  nodePtr= delPtr;
	}
	else{
	  cout << "case 5" <<endl;
	  delPtr = delPtr->next;
	  nodePtr = nodePtr->next;
	}
      }
    }
  cout << endl << endl << endl;
  cout << "count " << count << endl << endl << endl;
}



/*
  Walk through vector v. Keep a count if speed is below threshold increase 
  count. If count is above second threshold write to a txt file that there is 
  congestion. If the count is below the threshold write to the text file that
  there in no congestion on the roadway.
  ----------------------------------------------------------------------------
*/

void congestion(){
  int count = 0;
  for(int j = 0; j < v.size(); j++)
    cout << "v[j] " << v[j] << endl;
  for(int i =0; i < v.size(); i++){
    if(v[i] < 1.0 && v[i] > -1.0) //speed threshold is firts number
      count++;
  }
  if(count < 3){ //threshold for how many flags are necessay for congestion
    ofstream myfile;
    myfile.open("Congestion.txt");
    myfile << "There is no congestion on the roadway.\n";
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
  This function will walk through the linked list and deltete all heap memory
  used. This will efectively act as a destructor.
  ---------------------------------------------------------------------------
*/

void deleteAll(car*& root){
  car* nodePtr = root;
  while(root->next != NULL){
    nodePtr = root->next;
    delete root;
    root = nodePtr;
  }
  delete root;
  
}
/*
  This function will walk the linked list and print all data from the items
  in the list
  --------------------------------------------------------------------------
*/
void printList(car*& root){
  car* nodePtr = root;
  while(nodePtr->next != NULL){
    cout << nodePtr->longitude << endl;
    cout << nodePtr->latitude << endl;
    cout << nodePtr->speed << endl;
    cout << nodePtr->time << endl;
    cout << nodePtr->next << endl;
    nodePtr = nodePtr->next;
  }
}
    
