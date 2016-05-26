// # include <stdio.h>
# include <iostream>
# include <string>
# include <vector>
# include <fstream>
# include <sstream>

# define LINESIZE 100
using namespace std;

class Process {
public:
  int mId;
  int mCpuBurst;
  int mArrivalTime;
  int mPriority;

  Process() {
    mId = 0;
    mCpuBurst = 0;
    mArrivalTime = 0;
    mPriority = 0;
  } // Process()
}; // class Process

typedef vector<Process> ProcessQueue;
ProcessQueue gProcessQueue;
string inputName = "";
string outputName = "";
fstream fin;

void FCFS() {

} // FCFS()

void ReadProcess( int &type ) {
  char line[LINESIZE];
  int indexOfDot = 0;
  vector<int> numVector;

  cout << "請輸入檔案名稱: ";
  cin >> inputName;
  indexOfDot = inputName.find( "." );
  if ( indexOfDot > -1 )
    outputName = inputName.substr( 0, inputName.length() - 4 ) + "_output.txt";
  else
    outputName = "output.txt";

  fin.open( inputName, ios::in );
  if ( !fin )
    cout << "無法開啟檔案" << endl;
  else {
    fin.getline( line, sizeof( line ), '\n' );
    cout << line << endl;
    type = atoi( line );
    fin.getline( line, sizeof( line ), '\n' );
    cout << line << endl;
    while ( fin.getline( line, sizeof( line ), '\n' ) ) {
      Process process;
      sscanf( line, "%d %d %d %d", &process.mId, &process.mCpuBurst, &process.mArrivalTime, &process.mPriority );
      gProcessQueue.push_back( process );
    } // while
  } // else

  fin.close();
} // ReadProcess()

void Run() {
  int type = 0;
  ReadProcess( type );
  for ( int i = 0 ; i < gProcessQueue.size() ; i++ )
    cout << gProcessQueue[i].mId << " " << gProcessQueue[i].mCpuBurst << " "
         << gProcessQueue[i].mArrivalTime << " " << gProcessQueue[i].mPriority << endl;


} // Run()

int main() {
  Run();

  return 0;
} // main()
