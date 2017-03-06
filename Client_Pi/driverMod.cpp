/*
  ------------------------------------------------------------------------
  driver.cpp
  written by Noah Weller
  created October 26, 2016
  -------------------------------------------------------------------------
  This program will be the main program for the raspberry pi clients.
  It will run the python script send GPS data to the server pi and recieve
  traffic updates. It will display the updates on the LCD sceen connecedted
  to the raspberry pi.
  ---------------------------------------------------------------------------
  
*/

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <cctype>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <vector>
using namespace std;

int LCDAddr = 0x27;
int BLEN = 1;
int fd;

/*
  --------------------------------------------------------------
  Function decleration
  
  ---------------------------------------------------------------
*/
void write_word(int data);

void send_command(int comm);

void send_data(int data);

void init();

void clear();

void write(int x, int y, char data[]);

void printFile();

void pause(int dur);

void sortFile(string text);
/*
  --------------------------------------------------------------
  This is the main program that calls all the function. It runs
   the python script and sends the data to the server pi. It then 
   waits to print out a message from the server after the server 
   computes data from all of the clients.
   
   ---------------------------------------------------------------
*/

int main()
{
  
    fd = wiringPiI2CSetup(LCDAddr);
    init();

    system("python pyandc.py"); //gather sensor data 
    system("./fileTransfer.sh"); // send GPS data
    pause(1);
    system("rm text1.txt");   //remove text file after it has been sent
    pause(2);
	
    //wait till we have a message from the server
    int a  =0;
    while(a < 1){
      struct stat st;
      if(stat("./Congestion.txt",&st) == 0)
    	a = 2;
    }
	
    pause(2);
    cout << "file recieved " << endl;

    printFile();
    pause(3);
    clear();
    sortFile("Congestion.txt");

    system("rm Congestion.txt");
    pause(1);

    return 0;
}


/*
--------------------------------------------------------------
   Function implementation

---------------------------------------------------------------

*/
/*These functions were already created
-------------------------------------
*/
void write_word(int data){
  int temp = data;
  if ( BLEN == 1 )
	temp |= 0x08;
  else
	temp &= 0xF7;
  wiringPiI2CWrite(fd, temp);
}
void send_command(int comm){
  int buf;
  // Send bit7-4 firstly
  buf = comm & 0xF0;
  buf |= 0x04; // RS = 0, RW = 0, EN = 1
  write_word(buf);
  delay(2);
  buf &= 0xFB; // Make EN = 0
  write_word(buf);
  // Send bit3-0 secondly
  buf = (comm & 0x0F) << 4;
  buf |= 0x04; // RS = 0, RW = 0, EN = 1
  write_word(buf);
  delay(2);
  buf &= 0xFB; // Make EN = 0
  write_word(buf);
}
void send_data(int data){
  int buf;
  // Send bit7-4 firstly
  buf = data & 0xF0;
  buf |= 0x05; // RS = 1, RW = 0, EN = 1
  write_word(buf);
  delay(2);
  buf &= 0xFB; // Make EN = 0
  write_word(buf);
  // Send bit3-0 secondly
  buf = (data & 0x0F) << 4;
  buf |= 0x05; // RS = 1, RW = 0, EN = 1
  write_word(buf);
  delay(2);
  buf &= 0xFB; // Make EN = 0
  write_word(buf);
}
void init(){
  send_command(0x33); // Must initialize to 8-line mode at first
  delay(5);
  send_command(0x32); // Then initialize to 4-line mode
  delay(5);
  send_command(0x28); // 2 Lines & 5*7 dots
  delay(5);
  send_command(0x0C); // Enable display without cursor
  delay(5);
  send_command(0x01); // Clear Screen
  wiringPiI2CWrite(fd, 0x08);
}
void clear(){
  send_command(0x01); //clear Screen
}
void write(int x, int y, string data){
  //cout << "Did I come here?" << endl;	
  int addr, i;
  int tmp;
  if (x < 0) x = 0;
  if (x > 15) x = 15;
  if (y < 0) y = 0;
  if (y > 1) y = 1;
  // Move cursor
  addr = 0x80 + 0x40 * y + x;
  send_command(addr);
  
  tmp = data.size();
  for (i = 0; i < tmp; i++){
	send_data(data[i]);
  }
}
/*
Till here
------------------------------------------------
*/


//This function will print the contents of a text file sent form the server
//that tells us if there is congestion on the roadway

void printFile()
{	
  //cout << "Entered printFile" << endl;
  string getcontent;
  int count1 = 0;
  int temp;
  string content = "";
  ifstream openfile ("Congestion.txt");
 
  if(openfile.is_open())
    {

      while(! openfile.eof())
	{
	  getline(openfile, getcontent);

	  content += getcontent;
	}
      vector<string> words;
      int count = 0;
      string word="";
      cout << endl << endl<< "Here is the contents of the file:" << endl;
      cout << content << endl << endl <<endl;
 
      for(int i = 0; i < content.size(); i++)
	{
	  if(count < 15){
	    temp = i;  
	    while(content[temp] != ' ' && temp < content.size()){
	      cout<< content[temp] <<endl;
	      count1++;
	      temp++;
	    }
	    cout << "out of loop" << endl;

	    count1++;
	    if(temp >content.size()){
	      temp--;
	    }
	    cout << "content[temp]: " << content[temp] << endl << "temp :";
	    cout << temp <<endl << "count1 :" <<count1 <<endl << "count :" << count << endl;

	    
	    if(count+count1 > 15){
	      cout << "case 1: " << endl;
	      words.push_back(word);
	      count = 0;
	      count1 = 0;
	      temp = 0;
	      word ="";
	      i--;
	      
	    }
	    else{
	      cout << "case 2 :" << endl;
	      while(i <= temp){
		word += content[i];
		i++;
		count++;;
		//if(i+1 == content.size())
		//words.push_back(word);
	      }
	      count1=0;
	      temp = 0;
	      i--;
	    }
	  }
	  else{
	    cout << "case 3 :" << endl;
	    words.push_back(word);
	    //cout << word << endl;
	    count = 0;
	    count1= 0;
	    word = "";
	    //word += content[i];
	  }
	  cout << "word :" << word << "|"<< endl;
	}
      cout << "case 4 :" <<endl;
      words.push_back(word);
      cout << "Here is Words: " << endl;
      for(int j= 0; j < words.size(); j++)
	cout << words[j] << endl;
      cout << "----------------" ;
      cout << endl << endl << endl;
      //cout << "Problem is here" << endl;
      string word1;
      string word2;
      
      for(int k = 0; k < words.size(); k += 2){
	if(k+2 <= words.size()){
	  //strcpy(firstWord,words[k].c+str());
	  //strcpy(secondWord,words[k].c+str());		  
	  word1 = words[k];
	  word2 = words[k+1];
	  write(0, 0, word1);
	  write(1,1,word2);
	  delay(3000);
	  clear();
	}
	else
	  {
	    //strcpy(firstWord,words[k].c+str());
	    word1 = words[k];
	    write(0, 0, word1);
	    delay(1000);
	    clear();
	  }
	
      }
      
    }
  else
    cout << "ERROR!";
}

//This function is used to pause system in order to make sure process is
//finished before passing handle to next part of the program


//instead we could just use delay that is a built in function of wiringPi
void pause(int dur){
  int temp = time(NULL) + dur;
  while(temp > time(NULL));
}


void sortFile(string text)
{
  string getcontent;
  string direction;
  ifstream openfile(text.c_str());
  //ifstream openfile ("text3.txt");
  cout << "printing....." << endl;
  if(openfile.is_open())
    {
      while(! openfile.eof())
        {
            getline(openfile, getcontent);
            direction += getcontent;
            cout << getcontent << endl;
        }
    }
  else
    cout << "ERROR!";
 if(direction == "right"){
    /// GPIO Right
    cout << "CASE 1" << endl;
    system("./pin1.sh");
    //digitalWrite(rightTurn, HIGH);
    //delay(10000);
    //digitalWrite(rightTurn, LOW);
 }
 else if(direction == "left"){
  cout << "CASE 2" << endl; 	/// GPIO left
  system("./pin2.sh"); 
 //digitalWrite(leftTurn,HIGH);
  //delay(10000);
  //digitalWrite(leftTurn,LOW);
 }
 else if(direction == "back"){
  cout << "CASE 3" << endl;
  system("./pin3.sh");
  //digitalWrite(stop, HIGH);
  //delay(10000);
  //digitalWrite(stop, LOW);
	/// GPIO Else
 }else{
   system("./pin4.sh");
}
}
