//
//  HT.cpp
//
//  Created by Hina Khalid  on 27/07/2020.
//  Copyright © 2020 Hina Khalid . All rights reserved.
//  main.cpp
//  BST
//  Created by Hina Khalid  on 17/06/2020.
//  Copyright © 2020 Hina Khalid . All rights reserved.
//used by HabibaAtique
//edited by Habiba Atique
// Hashing
//Datastructures and Algorithms

/*/////readme////////

1. Complete the functions so that they call tallyProbes on every successful insertion, with the number of probes required for that insertion
 and return that value as well. And in case of failure in insertion update 'numFailures'.
2. Run some experiments to see how the average number of probes per insertion differs when using the different methods.Try to answer the following questions:
 (a) A critical influence on performance of an open addressing hash table is the load factor; that is, the proportion of the slots in the array that are used.
  As the load factor increases towards 100%, the number of probes that may be required to find or insert a given key rises dramatically. Once the table becomes
  full, probing algorithms may even fail to terminate. Even with good hash functions, load factors are normally limited to 80%. A poor hash function can 
  exhibit poor performance even at very low load factors by generating significant clustering, especially with the simplest linear addressing method.
     Experiment with load factor 50% (engaging the size of hashtable double as compared to the values to be stored), 60% and 70% . 
	 Does changing the load factor effects the number of probes with each method of open addressing. Under what load factors is linear probing just as 
	 good as quadratic probing? When does quadratic begin to win out?
 (b) Experiment with different hashfunctions for both methods, to pick your best(one with less average probing or probing rate).
 (c) Finally, which open addressing scheme would you choose and why?
3. In case of failure to find any value, Is there any way to identify if failure resulted because no try was made to insert the value  or  because the 
try was done but it resulted in failure



//////////////////*/

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class HT
{
private:
    int length;   // will increase with increase in inserted element
    int HTableSize;
    string *key_arr; // Will hold Names in an array of size 10
    int *status_arr; // Will hold (0 for Empty, 1 for there is data, -1 for deleted)
    int totalProbes;           // will count total number of probes for all inserted elements
    int numFailures;           // will update if unable to find any empty slot
    void updateProbes(int probes)
    {
        // Add the number of probes, for one insert operation to the tally.
        totalProbes += probes;
        length += 1;
    }
    
    
    int hFLin1(string key,int pos)
    {
		int ch;
		ch=int(key[0]);

    		int j=	(ch+pos) % HTableSize;
		
        // complete
        return j;
    }
    int hFQuad1(string key,int pos)
    {
		int ch=int(key[0]);
    	int j=	(ch+(pos^2))%HTableSize;
        return j;
    }
    int hFLin2(string key,int pos)
    {
		int z=key.length();
		int ch=0;
		for(int k=0;k<z;k++)
		{
			ch=ch+int(key[k]);
		}
    		int j=	(ch+pos) % HTableSize;
		
        return j;
    }
    int hFQuad2(string key,int pos)
    {
		int z=key.length();
		int ch=0;
		for(int k=0;k<z;k++)
		{
			ch=ch+int(key[k]);
		}
    	int j=	(ch+(pos^2))%HTableSize;
        return j;
    }
public:
    HT(int Size) // bcz the words in wordlist are 85760 something
    {
  
        key_arr = new string[Size];
        status_arr = new int[Size];
        HTableSize = Size;
        for (int i = 0; i < Size; i++)
            {status_arr[i] = 0;}
    }
    void printStats() {
        cout << "Average probes/insert = " <<
        probeRate() << " = " <<
        totalProbes << "/" << length;
        cout <<", size = "<< length;
        cout <<", failures = " << numFailures << endl;
    }
    
    float probeRate() {
        if ( length == 0 ) return 0;
        return (float)totalProbes / (float)length;
    }
    
    void print() {
        // Print the content of the hash table.
        
        for (int i=0; i<length; i++) {
            cout<<"["<<i<<"] ";
            cout << key_arr[i];
            cout << endl;
        }
    }
    
    int getSize() 
	{
        return HTableSize;
    }
    int getInserts()
	{
        return length;
    }
    int getFailures()
	{
        return numFailures;
    }
    int getProbes()
	{
        return totalProbes;
    }
    
    
    int lExists(string key)
    {
        // using linear probing for item searching
        for(int i=0;i<=HTableSize;i++)
        {
        	int j=hFLin2(key,i);
        	if (key_arr[j]==key)
        	{
        		cout<<"word exsts at: "<<j;
        		return 1;
			}
		}

    }
    
    int qExists(string key)
    {
         // using quadratic probing for item searching
        for(int i=0;i<=HTableSize;i++)
        {
        	int j=hFQuad2(key,i);
        	if (key_arr[j]==key)
        	{
        		cout<<"word exsts at: "<<j;
        		return 1;
			}

		}
    }

    int qAdd(string key) {
        // Insert k in the hash table.
        // Use open addressing with quadratic probing and hash(k) = k % _size.
        
        // Tips:
        // - Look at the lecture slides if you don't remember how to implement these.
        // - You need to prevent against infinite loops. You should limit the number
        // of times you probe and print an error message upon exceeding this limit.
        // - You're welcome to add new declarations add to the constructor,
        // include libraries, or anything else you need. Just make it work.
        // - You're also welcome to modify the main() method to automate your testing.
        // In fact, you should!
        
        // ************* ADD YOUR CODE HERE *******************
        int probe=0;
        for(int i=0;i<=HTableSize;i++)
        {
        	
        	int j=hFQuad2(key,i);
        	if (status_arr[j]==0 ||status_arr[j]==-1)
        	{
        		key_arr[j]=key;
        		status_arr[j]=1;
        		return probe;
        		break;
			}
			else
			{
				probe=probe+1;
			}
		}
        updateProbes(probe);
        // Your method should return with no of probes, after it stores the value in an EMPTY slot
        // and calls tallyProbes, so if it gets here, it didn't find an EMPTY slot
        if(probe==HTableSize)
        {
        numFailures += 1;
        cout << "Warning: qinsert(" << key << ") found no EMPTY slot, so no insert was done." << endl;
        return -1;
		}

       
    }
    
    int linsert(string key)
	 {
        // Insert k in the hash table.
        // Use open addressing with linear probing and hf for hash(k) = k % _size.
        
        // ************* ADD YOUR CODE HERE *******************
        int probe=0;
        for(int i=0;i<=HTableSize;i++)
        {
        	
        	int j=hFLin2(key,i);
        	if (status_arr[j]==0 ||status_arr[j]==-1)
        	{
        		key_arr[j]=key;
        		status_arr[j]=1;
        		return probe;
        		
			}
			else
			{
				probe=probe+1;
			}
		}
        updateProbes(probe);
        // Your method should return with no of probes, after it stores the value in an EMPTY slot
        // and calls tallyProbes, so if it gets here, it didn't find an EMPTY slot
        if(probe==HTableSize)
        {
        numFailures += 1;
        cout << "Warning: qinsert(" << key << ") found no EMPTY slot, so no insert was done." << endl;
        return -1;
		}
    }
    
};


int main()
{

    char ch;
    cout<<"L for Linear Addressing & Q for quadratic Probing: ";
    cin >>ch; // L=for experimentation with linear probing  Q=for experimentation with quadratic probing
    switch(ch)
    {
        case ('L'):
            {
			
            // declare hashtable
            HT htL(84096*2);   //adjust size acording to load factor
            // read data from file
            ofstream fout;
            ifstream fin;
            string line;
            fin.open("engmix.txt");
            fout.open("statusL.txt");
            string x;
            // Execute a loop If file successfully opened
            if(fin)
			{
				
            while (!fin.eof()) 
				{
                   /// read wordlist
                // insert each word in hashtable
                /* report the number of collisions for each word by writting it in another file (so you need two files one in reading mode i.e 
				wordlist and other in write mode i.e status file, telling the collision per word containing <word, probe count> pairs)*/
                
				fin>>x;
				int val=htL.linsert(x);
				fout<<x<<" "<<val<<endl;
				cout<<x<<endl;
            	}
                fin.close();
                fout.close();
                
            }
            string y;
            cout<<"***Enter word to see if exists***";
            cin>>y;
            if(htL.lExists(y)==true)
            {
            	cout<<"Word exists..."<<endl;
			}

            // report total stats of the process
            
            /* ask the user to find any particular word and report number of collisions to find that number is it the same as number of probes occured 
			at the time of insertion (you can check from the status file)*/
            
            break;
		}
        case ('Q'):
            {
			
            // declare hashtable
            HT htQ(84096);   //adjust size acording to load factor
            // read data from file
            ifstream fin;
            ofstream fout;
            string line;
            fin.open("engmix.txt");
            fout.open("statusQ.txt");
            string x;
            // Execute a loop If file successfully opened
            if(fin)
			{
				
            while (!fin.eof()) 
				{
                   /// read wordlist
                // insert each word in hashtable
                /* report the number of collisions for each word by writting it in another file (so you need two files one in reading mode i.e 
				wordlist and other in write mode i.e status file, telling the collision per word containing <word, probe count> pairs)*/
                
				fin>>x;
				
				int val=htQ.qAdd(x);
				fout<<x<<" "<<val<<endl;
				cout<<x<<endl;
            	}
                fin.close();
                fout.close();
            }
            cout<<"**********************************************************************"<<endl;
            cout<<"                              FILE STORED"<<endl;
            cout<<"**********************************************************************"<<endl;
            string y;
            cout<<"***Enter word to see if exists***";
            cin>>y;
            if(htQ.qExists(y)==1)
            {
            	cout<<"Word exists..."<<endl;
			}
			else
			{
				cout<<"Word does not exist"<<endl;
			}
            // report total stats of the process
            
            /* ask the user to find any particular word and report number of collisions to find that number is it the same as number of probes occured 
			at the time of insertion (you can check from the status file)*/
            
            break;
		}
    }
}
