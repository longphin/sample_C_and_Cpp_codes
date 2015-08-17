// lonnguyen; Nguyen, Longphi
#include <cstdio> 
#include <cstdlib>
#include <set>
#include <stack>
#include <iostream>
#include <set>
#include <iomanip>

using namespace std;

set<char> rows[9];
set<char> cols[9];
set<char> blocks[9];
int solncount=0;

class Puzzle
{
	private:
	char puz[9][9];
	public:
	Puzzle(char mypuz[][9])
	{
		for(int i=0; i<9; i++)
		{
			for(int j=0; j<9; j++)
			{
				puz[i][j]=mypuz[i][j];
			}
		}
	}

	inline int getBlock(int i, int j)//{ return( (j-j%3)/3 + (i-i%3)); }
{
	if(i<3)
	{
		if(j<3) return(0);
		if(j<6) return(1);
		return(2);
	}
	if(i<6)
	{
		if(j<3) return(3);
		if(j<6) return(4);
		return(5);
	}
	if(j<3) return(6);
	if(j<6) return(7);
	return(8);
}

void findSets()
{
	for(int i=0; i<9; i++)
	{
		rows[i].clear();
		cols[i].clear();
		blocks[i].clear();
	}

	// find possibilities
	for(int i=0; i<9; i++)
	{
		for(int j=0; j<9; j++)
		{
			if(puz[i][j]!='0')
			{
				rows[i].insert(puz[i][j]);
				cols[j].insert(puz[i][j]);

				int blocknum=getBlock(i,j);
				blocks[blocknum].insert(puz[i][j]);
			}
		}
	}
}

int simplify(stack<Puzzle> &alternatives, int &r, int &c) // changes cell to be cell with least alternatives
{
	findSets();

	char fullset[]={'1','2','3','4','5','6','7','8','9'};

	int smallest=0;
	int simplified=0;

	for(int i=0; i<9; i++)
	{
		for(int j=0; j<9; j++)
		{
			if(puz[i][j]=='0')
			{
				set<char> choices;

				for(set<char>::iterator itr=rows[i].begin(); itr!=rows[i].end(); itr++)
				{
					choices.insert(*itr);
				}

				for(set<char>::iterator itr=cols[j].begin(); itr!=cols[j].end(); itr++)
				{
					choices.insert(*itr);
				}

				int b=getBlock(i,j);
				for(set<char>::iterator itr=blocks[b].begin(); itr!=blocks[b].end(); itr++)
				{
					choices.insert(*itr);
				}

				int ss=choices.size();
				if(ss==9) return(-1); // 0 = not solvable

				if(ss==8) //hidden singles
				{
					simplified++;
					for(int k=0; k<9; k++)
					{
						set<char>::iterator itr=choices.find(fullset[k]);
						if(itr==choices.end())
						{
							puz[i][j]=fullset[k];
							rows[i].insert(fullset[k]);
							cols[j].insert(fullset[k]);
							blocks[b].insert(fullset[k]);
							break;
						}
					}
				}else{
					if((int)choices.size()>smallest)
					{
						r=i; c=j;
						smallest=choices.size();
					}
				}
			}
		}
	}
	return(simplified);
}

bool solved()
{
	findSets();

	for(int i=0; i<9; i++)
	{
		if(rows[i].size()!=9 || cols[i].size()!=9 || blocks[i].size()!=9) return(false);
	}

	return(true);
}

void print() const
{
	for(int i=0; i<9; i++)
	{
		for(int j=0; j<9; j++)
		{
			cout << puz[i][j];
		}
	}
	cout << endl;
}

void guess(stack<Puzzle> &alternatives, int &r, int &c) // cell = cell with least alternatives (value given from simplify())
{
	char fullset[]={'1','2','3','4','5','6','7','8','9'};

	if(r!=-1 && c!=-1)
	{
		set<char> choices;
		choices.insert(fullset, fullset+9);

		for(set<char>::iterator itr=rows[r].begin(); itr!=rows[r].end(); itr++)
			choices.erase(*itr);

		for(set<char>::iterator itr=cols[c].begin(); itr!=cols[c].end(); itr++)
		{
			set<char>::iterator itr2=choices.find(*itr);
			if(itr2!=choices.end()) choices.erase(itr2);
		}

		int b=getBlock(r,c);
		for(set<char>::iterator itr = blocks[b].begin(); itr!=blocks[b].end(); itr++)
		{
			set<char>::iterator itr2 = choices.find(*itr);
			if(itr2!=choices.end()) choices.erase(itr2);
		}

		for(set<char>::iterator itr=choices.begin(); itr!=choices.end(); itr++)
		{
			puz[r][c]=*itr;
			alternatives.push(* new Puzzle(puz));
		}
	}else{
		if(solved()==true)
		{
			print();
			solncount++;
		}
	}
}
};

int main()
{
	// read puzzle
	char readpuz[9][9];

	int row=0, col=0;

	string puz;

/*
	if(cin.eof()==true)
	{
		cout << "ERROR: expected <value> got <eof>" << endl;
		return(0);
	}
*/

	if(getline(cin,puz))
	{
		if(puz.empty())
		{
			cout << "ERROR: expected <value> got \\n" << endl;
			return(0);
		}
		if(!cin.eof() && puz.empty())
		{
			cout << "ERROR: expected <value> got <eof>" << endl;
			return(0);
		}
	}else{
		cout << "ERROR: expected <value> got <eof>" << endl; // doesn't actually work?
		return(0);
	}

/*
	if(puz.empty())// && cin.eof())
	{
		cout << "ERROR: expected <value> got <eof>" << endl;
		return(1);
	}
	*/

	size_t found = puz.find_first_not_of("123456789.\n");
	if(found!=string::npos)
	{
		cout << "ERROR: expected ";
		if((int)found<81)
		{
			cout << "<value>";
		}else{
			if((int)found==81)
			{
				cout << "\\n";
			}else{
				cout << "<eof>";
			}
		}
		cout << " got ";
		if(isprint(puz[found]) || puz[found]=='.')
			cout << puz[found];
		else
			printf("\\x%02x", puz[found]);
		cout << endl;
		return(0);
	}

	int puzlength=(int)puz.length();

	if(puzlength<81)
	{
		cout << "ERROR: expected <value> got \\n" << endl;
		return(0);
	}
	
	if(puzlength>81)
	{
		cout << "ERROR: expected \\n got ";
		if(isprint(puz[81]) || puz[81]=='.')
			cout << puz[81];
		else
			printf("\\x%02x", puz[81]);
		cout << endl;

		return(0);
	}

	for(int i=0; i<puzlength; i++)
	{
//		if(i<81)
//		{
//			if(puz[i]=='1' || puz[i]=='2' || puz[i]=='3' || puz[i]=='4' || puz[i]=='5' || puz[i]=='6' || puz[i]=='7' || puz[i]=='8' || puz[i]=='9' || puz[i]=='.')
//			{
				if(puz[i]=='.')
				{
					puz[i]='0';
				}
//			}else{
//				cout << "ERROR: expected <value> got ";
//				if(isprint(puz[i])==true)
//				{
					//cout << puz[i] << endl;
//					printf("\\x%02x", puz[i]);
//					cout << endl;
//				}else{
					//printf("\\x%02x", puz[i]);
//					cout << puz[i] << endl;
					//cout << endl;//<< hex << setw(2) << setfill('0') << (int)puz[i] << endl << setfill(' ');
//				}
//				return(0);
//			}
//		}
		/*
		if(i==81)
		{
			cout << "ERROR: expected \\n got ";
			if(isprint(puz[81])==true)
			{
				//cout << puz[81] << endl;
				printf("\\x%02x", puz[81]);
				cout << endl;
			}else{
				//cout << "\\x" << hex << (int)puz[81] << endl;
				cout << puz[81] << endl;
				//printf("\\x%02x", puz[81]);
				//cout << endl; //<< hex << setw(2) << setfill('0') << (int)puz[81] << endl << setfill(' ');
			}
			return(0);
		}
		*/

		readpuz[row][col]=puz[i];
		if(col==8)
		{
			row++;
			col=0;
		}else{
			col++;
		}
	}


//	if(puzlength<81)
//	{
//		cout << "ERROR: expected <value> got \\n" << endl;
//		return(0);
//	}

	if(getline(cin, puz))
	{
		if(puz.empty())
		{
			cout << "ERROR: expected <eof> got \\n" << endl;
		}else{
			cout << "ERROR: expected <eof> got ";
			if(isprint(puz[0])==true || puz[0]=='.')
			{
				cout << puz[0] << endl;
			}else{
				//cout << "\\x" << hex << (int)puz[0] << endl;
				printf("\\x%02x", puz[0]);
				//cout << puz[0]; // TEMPORARY
				cout << endl; //<< hex << setw(2) << setfill('0') << (int)puz[0] << endl << setfill(' ');
			}
		}
		return(0);
	}

/*
	if(cin.eof())
	{
		cout << "ERROR: expected <value> got <eof>" << endl;
		return(0);
	}
*/
	//char tok;

	/*
	while(cin >> tok)
	{
		if(counter==81 && tok!='\n')// && cin.eof())
		{
			cout << "ERROR: expected \\n got " << tok << endl;//<eof>" << endl;
			return(0);
		}else{
			if(counter > 81)
			{
				cout << "ERROR: expected <eof> got " << tok << endl;
				return(0);
			}
		}

		if(counter < 81 && (tok=='.' || tok=='1' || tok=='2' || tok=='3' || tok=='4' || tok=='5' || tok=='6' || tok=='7' || tok=='8' || tok=='9'))
		{
			if(tok=='.')
				readpuz[row][col]='0';
			else
				readpuz[row][col]=tok;
		}else{
			cout << "ERROR: expected <value> got " << tok << endl;
			return(0);
		}

		counter++;
		if(col<8)
		{
			col++;
		}else{
			col=0;
			row++;
		}
	}

	if(counter<81)
	{
		cout << "(4) ERROR expected <value> got ";
		if(tok==EOF) cout << "<eof>" << endl;
		else
			cout << "\\n" << endl;
		return(0);
	}
	*/

	stack<Puzzle> alternatives;
	alternatives.push(* new Puzzle(readpuz));

	while(!alternatives.empty())
	{
		Puzzle puzzle = alternatives.top();
		alternatives.pop();

		// decide all immediately decidable cells
		int r=-1,c=-1;//, value;

		// simplify = hidden singles, returns false if no simplifications needed
		int breaker=puzzle.simplify(alternatives,r,c);

		if(breaker==-1) continue; // not solvable
		puzzle.guess(alternatives,r,c);
	}

	if(solncount==0)
		cout <<"No solution!"<<endl;
	return(0);
}

