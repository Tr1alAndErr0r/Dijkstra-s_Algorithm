#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <set>
#include <limits>
#include <time.h>
    
using namespace std;

int main (int argc, char *argv[])
{
	const clock_t startTime = clock();
	if (argc != 3) 
	{
		cout<<"usage: "<< argv[0] <<" <test-input-file> <node i>\n";
	}
	
	else 
	{
		ifstream theFile;
		theFile.open(argv[1], ios::in);
		if (!theFile.is_open())
		{
			cout<<"Could not open file\n";
		}
		
		else 
		{
			string line;
			int numOfNodes = 0;
			long int temp = 0;
			int sourceNode = 0;
			int minNode = 0;
			unsigned int a = 1;
			unsigned int b = 1;
			
			
			getline(theFile, line);
			numOfNodes = atoi(line.c_str());
			sourceNode = atoi(argv[2]);
			unsigned int inputArray[numOfNodes+1][numOfNodes+1];	
			
			while (!theFile.eof())
			{
				theFile>> temp >> temp >> temp;
				inputArray[a][b] = temp;
				
				if(b != numOfNodes)
				{
					b++;
				}
				
				else 
				{
					b = 1;
					a++;
				}
			}  
			theFile.close();
			
			a = sourceNode;
			unsigned int D[numOfNodes+1];
			unsigned int R[numOfNodes+1];
			
			for (b = 1; b < numOfNodes+1; b++)
			{
				if (a!=b)
				{	
					D[b] = inputArray[a][b];
				}
				else
				{
					D[b] = 4294967295;
				}	

				
				if(D[b]!= 4294967295)
				{
					R[b] = b;
				}
				else
				{
					R[b] = 0;
				}
			}	
			
			set<int> S;
			set<int>::iterator it = S.begin();
			for (b = 1; b < numOfNodes + 1; b++)
			{
				it = S.insert(it, b);
			}
			S.erase(sourceNode);
			
			cout << "\nSet contains: \n";
			for (it=S.begin(); it!=S.end(); ++it)
			{
				cout << *it;
				cout << '\n';
			}
	
			b = 0;
			while(!S.empty())
			{
				temp = numeric_limits<long>::max();
				for (it = S.begin(); it!= S.end(); ++it)
				{
					if(D[*it] < temp)
					{
						temp = D[*it];
						minNode = *it;
					}
				}
				
				S.erase(minNode);
				
				cout << "\n\nMinNode is: " << minNode << "\n";
				cout << "Set contains:\n";
				
				for (it=S.begin(); it!=S.end(); ++it)
				{
					cout << *it;
					cout << '\n';
				}
				
				for (a = 1; a < numOfNodes+1; a++)
				{
					if(a != minNode && inputArray[minNode][a] != 4294967295)
					{
						it = S.find(a);
						if(it!=S.end())
						{
							b = D[minNode] + inputArray[minNode][a];
							
							
							if (b < D[a])
							{
								cout << "\nR[" << a << "] before = " << R[a] << "\n";
								
								R[a] = R[minNode];
								
								cout << "R[" << a << "] after = " << R[a] << "\n";	
								cout << "D[" << a << "] before = " << D[a] << "\n";
								
								D[a] = b;
								
								cout << "D[" << a << "] after = " << R[a] << "\n";
								
							}
							
						}
					}
				}
				
			}	
				
			cout << "\n\nForwarding Table: (source node " << sourceNode << ")\n";
			cout << "Destination        |            Link\n";
			for(a = 1; a < numOfNodes+1; a++)
			{
				if(a != sourceNode)
				{	
					if(R[a] != 0)
					{
						cout << a << "        |      ( " << sourceNode << ", " << R[a] << ")\n";
					}	
					
					else
					{
						cout << a << "        |      unconnected\n";
					}
				}
			}
			
		}
	}
	cout << "\nTime: " << 1000*(float( clock () - startTime ) /  CLOCKS_PER_SEC) << "  ms\n";
	return 0;
}