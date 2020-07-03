//Conway's "Game of life"

#include <iostream>
#include <fstream>

using namespace std;

#define MAX_ARRAY_SIZE 40

int m;
int n;
int genTotal;
int Coor[] = {-1,0,1};

void PrintGen(char lifeBoard[ ][MAX_ARRAY_SIZE], ostream& outStream, int numRowsInBoard,int numColsInBoard, int generationNum);

void NextGen(char lifeBoard[ ][MAX_ARRAY_SIZE], int numRowsInBoard, int numColsInBoard);

int main()
{
	char inputfile[100];
	char outputfile[100];
	char ch;
	ifstream in;
	ofstream out;
	bool flag = false;
	int count = 0;
	char lifeboard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];
	int i;
	int	j;
	bool flagEdgeError = false;
	int tmpX;
	int tmpY;
	
	cout << "Enter the name of the input file: ";
	cin>> inputfile;
	in.open(inputfile,ios::in);
	if(!in)
	{
		cerr <<"ERROR: input file not opened correctly";
		return 0;
	}
	cout<<"Enter the name of the output file: ";
	cin>>outputfile;
	out.open(outputfile,ios::out);
	if(!out)
	{
		cerr <<"ERROR: output file not opened correctly";
		return 0;
	}
	if(!(in >> m))
	{
		out <<"ERROR: Cannot read number of rows";
		cerr <<"ERROR: Cannot read number of rows";
		return 0;
	}
	if(!(in >> n))
	{
		cerr <<"ERROR: Cannot read number of columns";
		return 0;
	}
	if(!(in >> genTotal))
	{
		cerr <<"ERROR: Cannot read the number of generations";
		return 0;
	}
	if(m < 0 || m > MAX_ARRAY_SIZE)
	{
		cerr <<"ERROR: Read an illegal number of rows for the board";
		flag = true;
	}
	if(n < 0 || n > MAX_ARRAY_SIZE)
	{
		cerr <<"ERROR: Read an illegal number of columns for the board";
		flag = true;
	}
	if(genTotal < 1)
	{
		cerr <<"ERROR: Read an illegal number of generations";
		flag = true;
	}
	if(flag)
	{
		return 0;
	}
	while(in>>ch)// read organism data
	{
		if(ch == '.' || ch == 'X')
		{
			tmpX = count/n;
			tmpY = count%n;
			
			lifeboard[tmpX][tmpY] = ch;
			
			if((tmpX == m-1 || tmpX == 0) || (tmpY == 0 || tmpY == n-1))
			{
				if(lifeboard[tmpX][tmpY] == 'X')
				{
					flagEdgeError = true;
				}
			}
			count++;// record the count of  organism data 
		}
		else
		if(ch!='\n' && ch != char(9) && ch != ' ')
		{
			cerr << "ERROR: Input data for initial board is incorrect"<<endl;
			cerr <<"Location ("<< (count/n)+1<<", "<< (count%n) +1 <<") is not valid";
			return 0;
		}
	}
	if(count < m*n)
	{
		cerr <<"ERROR: Not enough data in the input file";
		return 0;
	}
	if(flagEdgeError)
	{
		cerr <<"ERROR: organisms are present in the border of the board, please correct your input file";
		return 0;
	}
	for(i = 0;i <= genTotal;i++)
	{
		if(i == 0 || i==1 || i == genTotal )
		{
			PrintGen(lifeboard,cout,m,n,i);
			PrintGen(lifeboard,out,m,n,i);
		}
		else
		{
			PrintGen(lifeboard,out,m,n,i);
		}	
		NextGen(lifeboard,m,n);
	}
	return 0;
}

void PrintGen(char lifeBoard[ ][MAX_ARRAY_SIZE], ostream& outStream, int numRowsInBoard,int numColsInBoard, int generationNum)
{
    int i,j;
	if(generationNum == 0)
	{
		outStream<<"LIFE initial game board\n\n";
	}
	else
	{
		outStream<<"LIFE gameboard: generation "<<generationNum<<endl;
	}	
	for(i = 0; i < numRowsInBoard; i++)
	{
		for(j = 0; j < numColsInBoard-1; j++)
		{
			outStream<<lifeBoard[i][j] <<" ";
		}
		outStream<<lifeBoard[i][j]<<endl;
	}
	outStream<<"\n\n\n";
}

void NextGen(char lifeBoard[ ][MAX_ARRAY_SIZE], int numRowsInBoard, int numColsInBoard)
{
	int i,j;
	int k,l;
	int neighbors = 0;
	char temp[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];
	
	for(i = 1;i < numRowsInBoard-1; i++ )
	{
		for(j = 1; j < numColsInBoard -1; j++)
		{
			neighbors = 0;// the count of neighbors
			
			for(k = 0; k < 3; k++)
			{
				for(l=0; l  < 3; l++)
				{
					if(lifeBoard[i+Coor[k]][j+Coor[l]] == 'X')
					{
						neighbors ++;
					}
				}
			}			
			if(lifeBoard[i][j] == 'X')
			{
				neighbors--;
			}	
			//next generation at this Point 		
			if(neighbors == 3)
			{
				temp[i][j] = 'X';
			}
			else
			{
				if(lifeBoard[i][j] == 'X' && neighbors == 2)
				{
					temp[i][j] = 'X';
				}
				else
				{
					temp[i][j] = '.';
				}
			}
		}
	}
	//copy data from temp array to lifeboard
	for(i = 1;i < numRowsInBoard-1; i++ )
	{
		for(j = 1; j < numColsInBoard -1; j++)
		{
			lifeBoard[i][j] = temp[i][j];
		}
	}
}
