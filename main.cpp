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
  int mWaitingTime;
  int mTurnaround;
  int mStartTime;
  bool mHasUsed;

  Process() {
    mId = 0;
    mCpuBurst = 0;
    mArrivalTime = 0;
    mPriority = 0;
    mWaitingTime = 0;
    mTurnaround = 0;
    mHasUsed = false;
  } // Process()
}; // class Process

typedef vector<Process> ProcessQueue;
ProcessQueue gProcessQueue, gAllProcess;
string inputName = "";
string outputName = "";
fstream fin;

void ReadProcess( int &type, int &timeSlice ) {
  char line[LINESIZE];
  int indexOfDot = 0;
  vector<int> numVector;
  string outputNum = "";

  cout << "請輸入檔案名稱: ";
  cin >> inputName;
  indexOfDot = inputName.find( "." );
  if ( inputName[indexOfDot-1] <= '9' && inputName[indexOfDot-1] >= '0' )
    outputNum += inputName[indexOfDot-1];

  if ( indexOfDot > -1 )
    outputName = "output" + outputNum + ".txt";
  else
    outputName = "output.txt";

  fin.open( inputName, ios::in );
  if ( !fin )
    cout << "無法開啟檔案" << endl;
  else {
    fin.getline( line, sizeof( line ), '\n' );
    cout << line << endl;
    sscanf( line, "%d %d", &type, &timeSlice );
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

char GetProcessId( int num ) {
  if ( num - 10 >= 0 )
    return ( char )( 'A' + ( num - 10 ) );
  return ( char )( 48 + num );
} // PrintProcessId()

void PrintQueue( ProcessQueue processQueue ) {
  for ( int i = 0 ; i < processQueue.size() ; i++ )
    cout << processQueue[i].mId << " " << processQueue[i].mCpuBurst << " "
         << processQueue[i].mArrivalTime << " " << processQueue[i].mPriority << endl;
} // PrintQueue()

void PrintWaitingAndTurnaround( ProcessQueue processQueue ) {
  for ( int i = 0 ; i < processQueue.size() ; i++ )
    cout << dec << processQueue[i].mId << " " << processQueue[i].mWaitingTime << " "
         << processQueue[i].mTurnaround << endl;
} // PrintWaitingAndTurnaround()

void PrintAll( vector<ProcessQueue> allProcessVector ) {
  int idNum = 0;
  if ( allProcessVector.size() > 0 )
    idNum = allProcessVector[0].size();
  cout << "===========================================================" << endl
       << endl
       << "Waiting Time" << endl
       << "ID      FCFS    RR      PSJF    NPSJF   Priority" << endl
       << "===========================================================" << endl;
  fin  << "===========================================================" << endl
       << endl
       << "Waiting Time" << endl
       << "ID      FCFS    RR      PSJF    NPSJF   Priority" << endl
       << "===========================================================" << endl;
  for ( int i = 0 ; i < idNum ; i++ ) {
    cout << dec << allProcessVector[0][i].mId;
    fin << dec << allProcessVector[0][i].mId;
    for ( int j = 0 ; j < allProcessVector.size() ; j++ ) {
      cout << "\t" << dec << allProcessVector[j][i].mWaitingTime;
      fin << "\t" << dec << allProcessVector[j][i].mWaitingTime;
    } // for

    cout << endl;
    fin << endl;
  } // for
  cout << "===========================================================" << endl;
  fin << "===========================================================" << endl;

  cout << endl;
  fin << endl;

  cout << "Turnaround Time" << endl
       << "ID      FCFS    RR      PSJF    NPSJF   Priority" << endl
       << "===========================================================" << endl;
  fin << "Turnaround Time" << endl
       << "ID      FCFS    RR      PSJF    NPSJF   Priority" << endl
       << "===========================================================" << endl;
  for ( int i = 0 ; i < idNum ; i++ ) {
    cout << dec << allProcessVector[0][i].mId;
    fin << dec << allProcessVector[0][i].mId;
    for ( int j = 0 ; j < allProcessVector.size() ; j++ ) {
      cout << "\t" << dec << allProcessVector[j][i].mTurnaround;
      fin << "\t" << dec << allProcessVector[j][i].mTurnaround;
    } // for

    cout << endl;
    fin << endl;
  } // for

  cout << "===========================================================" << endl;
  fin << "===========================================================" << endl;
} // PrintAll()

void PrintOne( vector<ProcessQueue> allProcessVector, string schedule ) {
  int idNum = 0;
  if ( allProcessVector.size() > 0 )
    idNum = allProcessVector[0].size();
  cout << "===========================================================" << endl
       << endl
       << "Waiting Time" << endl
       << "ID      " + schedule << endl
       << "===========================================================" << endl;
  fin  << "===========================================================" << endl
       << endl
       << "Waiting Time" << endl
       << "ID      " + schedule << endl
       << "===========================================================" << endl;
  for ( int i = 0 ; i < idNum ; i++ ) {
    cout << dec << allProcessVector[0][i].mId;
    fin << dec << allProcessVector[0][i].mId;
    for ( int j = 0 ; j < allProcessVector.size() ; j++ ) {
      cout << "\t" << dec << allProcessVector[j][i].mWaitingTime;
      fin << "\t" << dec << allProcessVector[j][i].mWaitingTime;
    } // for

    cout << endl;
    fin << endl;
  } // for
  cout << "===========================================================" << endl;
  fin << "===========================================================" << endl;

  cout << endl;
  fin << endl;

  cout << "Turnaround Time" << endl
       << "ID      " + schedule << endl
       << "===========================================================" << endl;
  fin << "Turnaround Time" << endl
       << "ID      " + schedule << endl
       << "===========================================================" << endl;
  for ( int i = 0 ; i < idNum ; i++ ) {
    cout << dec << allProcessVector[0][i].mId;
    fin << dec << allProcessVector[0][i].mId;
    for ( int j = 0 ; j < allProcessVector.size() ; j++ ) {
      cout << "\t" << dec << allProcessVector[j][i].mTurnaround;
      fin << "\t" << dec << allProcessVector[j][i].mTurnaround;
    } // for

    cout << endl;
    fin << endl;
  } // for

  cout << "===========================================================" << endl;
  fin << "===========================================================" << endl;
} // PrintOne()

void SortByID( ProcessQueue &processQueue ) {
  for ( int i = 0 ; i < processQueue.size() ; i++ )
    for ( int j = i + 1 ; j < processQueue.size() ; j++ )
      if ( processQueue[i].mId < processQueue[j].mId ) {
        Process tempProcess = processQueue[i];
        processQueue[i] = processQueue[j];
        processQueue[j] = tempProcess;
      } // if
} // SortByID()

void SortByID_Revers( ProcessQueue &processQueue ) {
  for ( int i = 0 ; i < processQueue.size() ; i++ )
    for ( int j = i + 1 ; j < processQueue.size() ; j++ )
      if ( processQueue[i].mId > processQueue[j].mId ) {
        Process tempProcess = processQueue[i];
        processQueue[i] = processQueue[j];
        processQueue[j] = tempProcess;
      } // if
} // SortByID_Revers()

void SortByArrvialTime( ProcessQueue &processQueue ) {
  for ( int i = 0 ; i < processQueue.size() ; i++ )
    for ( int j = i + 1 ; j < processQueue.size() ; j++ )
      if ( processQueue[i].mArrivalTime < processQueue[j].mArrivalTime ) {
        Process tempProcess = processQueue[i];
        processQueue[i] = processQueue[j];
        processQueue[j] = tempProcess;
      } // if
} // SortByArrvialTime()

void SortByCpuBurst( ProcessQueue &processQueue ) {
  for ( int i = 0 ; i < processQueue.size() ; i++ )
    for ( int j = i + 1 ; j < processQueue.size() ; j++ )
      if ( processQueue[i].mCpuBurst < processQueue[j].mCpuBurst ) {
        Process tempProcess = processQueue[i];
        processQueue[i] = processQueue[j];
        processQueue[j] = tempProcess;
      } // if
} // SortByCpuBurst()


void SortByPriority( ProcessQueue &processQueue ) {
  for ( int i = 0 ; i < processQueue.size() ; i++ )
    for ( int j = i + 1 ; j < processQueue.size() ; j++ )
      if ( processQueue[i].mPriority < processQueue[j].mPriority ) {
        Process tempProcess = processQueue[i];
        processQueue[i] = processQueue[j];
        processQueue[j] = tempProcess;
      } // if
} // SortByPriority()

void SortByPP( ProcessQueue &processQueue, Process process ) {
  int size = processQueue.size();
  int indexOfSamePriority = -1;
  int indexOfDiffPriority = -1;
  for ( int i = 0 ; i < processQueue.size() && indexOfSamePriority == -1 && size == processQueue.size() ; i++ ) {
    if ( process.mPriority > processQueue[i].mPriority )
      processQueue.insert( processQueue.begin() + i, process );
    else if ( process.mPriority == processQueue[i].mPriority )
      indexOfSamePriority = i;
  } // for

  if ( size == processQueue.size() ) {
    for ( int i = indexOfSamePriority ; i < processQueue.size() && size == processQueue.size() ; i++ )
      if ( !processQueue[i].mHasUsed && process.mPriority == processQueue[i].mPriority )
        processQueue.insert( processQueue.begin() + i, process );
      else if ( process.mPriority != processQueue[i].mPriority )
        if ( indexOfDiffPriority == -1 )
          indexOfDiffPriority = i;
  } // if

  if ( size == processQueue.size() ) {
    for ( int i = indexOfSamePriority ; i < processQueue.size() && size == processQueue.size() ; i++ )
      if ( process.mArrivalTime > processQueue[i].mArrivalTime && process.mPriority == processQueue[i].mPriority )
        processQueue.insert( processQueue.begin() + i, process );
      else if ( process.mPriority != processQueue[i].mPriority )
        if ( indexOfDiffPriority == -1 )
          indexOfDiffPriority = i;
  } // if

  if ( size == processQueue.size() ) {
    for ( int i = indexOfSamePriority ; i < processQueue.size() && size == processQueue.size() ; i++ )
      if ( process.mId > processQueue[i].mId && process.mPriority == processQueue[i].mPriority )
        processQueue.insert( processQueue.begin() + i, process );
      else if ( process.mPriority != processQueue[i].mPriority )
        if ( indexOfDiffPriority == -1 )
          indexOfDiffPriority = i;
  } // if

  if ( size == processQueue.size() )
    if ( indexOfDiffPriority != -1 )
      processQueue.insert( processQueue.begin() + indexOfDiffPriority, process );
    else
      processQueue.insert( processQueue.end(), process );

} // SortByPP()

void ComparePP( ProcessQueue &processQueue, Process &runningProcess ) {
  // compare priority
  if ( processQueue.size() > 0 ) {
    if ( runningProcess.mPriority == processQueue.back().mPriority ) {
      if ( !processQueue.back().mHasUsed ) {
        // insert
        SortByPP( processQueue, runningProcess );
        // dispatch
        runningProcess = processQueue.back();
        processQueue.pop_back();
      } // if
      else {
        if ( runningProcess.mArrivalTime > processQueue.back().mArrivalTime ) {
          // insert
          SortByPP( processQueue, runningProcess );
          // dispatch
          runningProcess = processQueue.back();
          processQueue.pop_back();
        } // if
        else if ( runningProcess.mArrivalTime == processQueue.back().mArrivalTime ) {
          if ( runningProcess.mId > processQueue.back().mId ) {
            // insert
            SortByPP( processQueue, runningProcess );
            // dispatch
            runningProcess = processQueue.back();
            processQueue.pop_back();
          } // if
        } // else if
      } // else
    } // if
  } // if
} // ComparePP()

void SortByPSJF( ProcessQueue &processQueue, Process process ) {
  int size = processQueue.size();
  int indexOfSamePriority = -1;
  int indexOfDiffPriority = -1;
  for ( int i = 0 ; i < processQueue.size() && indexOfSamePriority == -1 && size == processQueue.size() ; i++ ) {
    if ( process.mCpuBurst > processQueue[i].mCpuBurst )
      processQueue.insert( processQueue.begin() + i, process );
    else if ( process.mCpuBurst == processQueue[i].mCpuBurst )
      indexOfSamePriority = i;
  } // for

  if ( size == processQueue.size() ) {
    for ( int i = indexOfSamePriority ; i < processQueue.size() && size == processQueue.size() ; i++ )
      if ( !processQueue[i].mHasUsed )
        processQueue.insert( processQueue.begin() + i, process );
      else if ( process.mCpuBurst != processQueue[i].mCpuBurst )
        if ( indexOfDiffPriority == -1 )
          indexOfDiffPriority = i;
  } // if

  if ( size == processQueue.size() ) {
    for ( int i = indexOfSamePriority ; i < processQueue.size() && size == processQueue.size() ; i++ )
      if ( process.mArrivalTime > processQueue[i].mArrivalTime )
        processQueue.insert( processQueue.begin() + i, process );
      else if ( process.mCpuBurst != processQueue[i].mCpuBurst )
        if ( indexOfDiffPriority == -1 )
          indexOfDiffPriority = i;
  } // if

  if ( size == processQueue.size() ) {
    for ( int i = indexOfSamePriority ; i < processQueue.size() && size == processQueue.size() ; i++ )
      if ( process.mId > processQueue[i].mId )
        processQueue.insert( processQueue.begin() + i, process );
      else if ( process.mCpuBurst != processQueue[i].mCpuBurst )
        if ( indexOfDiffPriority == -1 )
          indexOfDiffPriority = i;
  } // if

  if ( size == processQueue.size() )
    if ( indexOfDiffPriority != -1 )
      processQueue.insert( processQueue.begin() + indexOfDiffPriority, process );
    else
      processQueue.insert( processQueue.end(), process );
} // SortByPSJF()

void ComparePSJF( ProcessQueue &processQueue, Process &runningProcess ) {
  // compare priority
  if ( processQueue.size() > 0 ) {
    if ( runningProcess.mCpuBurst == processQueue.back().mCpuBurst ) {
      if ( !processQueue.back().mHasUsed ) {
        // insert
        SortByPSJF( processQueue, runningProcess );
        // dispatch
        runningProcess = processQueue.back();
        processQueue.pop_back();
      } // if
      else {
        if ( runningProcess.mArrivalTime > processQueue.back().mArrivalTime ) {
          // insert
          SortByPSJF( processQueue, runningProcess );
          // dispatch
          runningProcess = processQueue.back();
          processQueue.pop_back();
        } // if
        else if ( runningProcess.mArrivalTime == processQueue.back().mArrivalTime ) {
          if ( runningProcess.mId > processQueue.back().mId ) {
            // insert
            SortByPSJF( processQueue, runningProcess );
            // dispatch
            runningProcess = processQueue.back();
            processQueue.pop_back();
          } // if
        } // else if
      } // else
    } // if
  } // if
} // ComparePSJF()

void PP() {
  int cpuTime = 0;
  ProcessQueue processQueue;
  Process runningProcess;
  runningProcess.mTurnaround = -1;
  while ( gProcessQueue.size() > 0 || processQueue.size() > 0 || runningProcess.mCpuBurst > 0 ) {
    while ( gProcessQueue.back().mArrivalTime == cpuTime ) {
      SortByPP( processQueue, gProcessQueue.back() );
      ComparePP( processQueue, runningProcess );
      gProcessQueue.pop_back();
    } // while

    if ( runningProcess.mCpuBurst > 0 ) {
      if ( runningProcess.mPriority > processQueue.back().mPriority ) {
        // insert
        SortByPP( processQueue, runningProcess );
        // dispatch
        runningProcess = processQueue.back();
        processQueue.pop_back();
      } // if

      cout << GetProcessId( runningProcess.mId );
      fin << GetProcessId( runningProcess.mId );
      runningProcess.mHasUsed = true;
      runningProcess.mCpuBurst--;
      for ( int i = 0 ; i < processQueue.size() ; i++ )
        processQueue[i].mWaitingTime++;
    } // if
    else if ( processQueue.size() > 0 ) {
      // terminal
      if ( runningProcess.mTurnaround == 0 ) {
        runningProcess.mTurnaround = cpuTime - runningProcess.mArrivalTime;
        gAllProcess.push_back( runningProcess );
      } // else if
      // dispatch
      runningProcess = processQueue.back();
      processQueue.pop_back();

      if ( runningProcess.mCpuBurst > 0 ) {
        cout << GetProcessId( runningProcess.mId );
        fin << GetProcessId( runningProcess.mId );
        runningProcess.mHasUsed = true;
        runningProcess.mCpuBurst--;
        for ( int i = 0 ; i < processQueue.size() ; i++ )
          processQueue[i].mWaitingTime++;
      } // if
      else if ( gProcessQueue.size() > 0 ) {
        cout << "-";
        fin << "-";
      } // else if
    } // else if
    else {
      cout << "-";
      fin << "-";
    } // else

    cpuTime++;
  } // while

  runningProcess.mTurnaround = cpuTime - runningProcess.mArrivalTime;
  gAllProcess.push_back( runningProcess );
} // PP()

void RR( int timeSlice ) {
  int cpuTime = 0, nowTimeSlice = timeSlice;
  ProcessQueue processQueue;
  Process runningProcess;
  runningProcess.mTurnaround = -1;
  while ( gProcessQueue.size() > 0 || processQueue.size() > 0 || runningProcess.mCpuBurst > 0 ) {
    while ( gProcessQueue.back().mArrivalTime == cpuTime ) {
      processQueue.insert( processQueue.begin(), gProcessQueue.back() );
      gProcessQueue.pop_back();
    } // while

    if ( runningProcess.mCpuBurst > 0 && nowTimeSlice > 0 ) {
      cout << GetProcessId( runningProcess.mId );
      fin << GetProcessId( runningProcess.mId );
      runningProcess.mCpuBurst--;
      nowTimeSlice--;
      for ( int i = 0 ; i < processQueue.size() ; i++ )
        processQueue[i].mWaitingTime++;
      if ( runningProcess.mCpuBurst == 0 )
        nowTimeSlice = timeSlice;
    } // if
    else if ( processQueue.size() > 0 || runningProcess.mCpuBurst > 0 ) {
      // insert time out process
      if ( runningProcess.mCpuBurst > 0 )
        processQueue.insert( processQueue.begin(), runningProcess );
      else if ( runningProcess.mTurnaround == 0 ) {
        runningProcess.mTurnaround = cpuTime - runningProcess.mArrivalTime;
        gAllProcess.push_back( runningProcess );
      } // else if

      // dispatch process
      nowTimeSlice = timeSlice;
      runningProcess = processQueue.back();
      processQueue.pop_back();

      if ( runningProcess.mCpuBurst > 0 && nowTimeSlice > 0 ) {
        cout << GetProcessId( runningProcess.mId );
        fin << GetProcessId( runningProcess.mId );
        runningProcess.mCpuBurst--;
        nowTimeSlice--;
        for ( int i = 0 ; i < processQueue.size() ; i++ )
          processQueue[i].mWaitingTime++;
        if ( runningProcess.mCpuBurst == 0 )
          nowTimeSlice = timeSlice;
      } // if
      else if ( gProcessQueue.size() > 0 ) {
        cout << "-";
        fin << "-";
      } // else if
    } // else if
    else {
      cout << "-";
      fin << "-";
    } // else

    cpuTime++;
  } // while

  runningProcess.mTurnaround = cpuTime - runningProcess.mArrivalTime;
  gAllProcess.push_back( runningProcess );
} // RR()

void PSJF() {
  int cpuTime = 0;
  ProcessQueue processQueue;
  Process runningProcess;
  runningProcess.mTurnaround = -1;
  while ( gProcessQueue.size() > 0 || processQueue.size() > 0 || runningProcess.mCpuBurst > 0 ) {
    while ( gProcessQueue.back().mArrivalTime == cpuTime ) {
      SortByPSJF( processQueue, gProcessQueue.back() );
      ComparePSJF( processQueue, runningProcess );
      gProcessQueue.pop_back();
    } // while

    if ( runningProcess.mCpuBurst > 0 ) {
      if ( runningProcess.mCpuBurst > processQueue.back().mCpuBurst ) {
        // insert
        SortByPSJF( processQueue, runningProcess );
        // dispatch
        runningProcess = processQueue.back();
        processQueue.pop_back();
      } // if

      cout << GetProcessId( runningProcess.mId );
      fin << GetProcessId( runningProcess.mId );
      runningProcess.mHasUsed = true;
      runningProcess.mCpuBurst--;
      for ( int i = 0 ; i < processQueue.size() ; i++ ) {
        processQueue[i].mWaitingTime++;
        cout << "###" << processQueue[i].mId << " " << processQueue[i].mWaitingTime << "###" << endl;
      } // for
    } // if
    else if ( processQueue.size() > 0 ) {
      // terminal
      if ( runningProcess.mTurnaround == 0 ) {
        runningProcess.mTurnaround = cpuTime - runningProcess.mArrivalTime;
        gAllProcess.push_back( runningProcess );
      } // else if
      // dispatch
      runningProcess = processQueue.back();
      processQueue.pop_back();

      if ( runningProcess.mCpuBurst > 0 ) {
        cout << GetProcessId( runningProcess.mId );
        fin << GetProcessId( runningProcess.mId );
        runningProcess.mHasUsed = true;
        runningProcess.mCpuBurst--;
        for ( int i = 0 ; i < processQueue.size() ; i++ ) {
          processQueue[i].mWaitingTime++;
          cout << "###" << processQueue[i].mId << " " << processQueue[i].mWaitingTime << "###" << endl;
        } // for
      } // if
      else if ( gProcessQueue.size() > 0 ) {
        cout << "-";
        fin << "-";
      } // else if
    } // else if
    else {
      cout << "-";
      fin << "-";
    } // else

    cpuTime++;
  } // while

  runningProcess.mTurnaround = cpuTime - runningProcess.mArrivalTime;
  gAllProcess.push_back( runningProcess );
} // PSJF

void NSJF() {
  int cpuTime = 0;
  ProcessQueue processQueue;
  Process runningProcess;
  while ( gProcessQueue.size() > 0 || processQueue.size() > 0 || runningProcess.mCpuBurst > 0 ) {
    while ( gProcessQueue.back().mArrivalTime == cpuTime ) {
      processQueue.insert( processQueue.begin(), gProcessQueue.back() );
      gProcessQueue.pop_back();
      SortByCpuBurst( processQueue );
    } // while

    if ( runningProcess.mCpuBurst > 0 ) {
      cout << GetProcessId( runningProcess.mId );
      fin << GetProcessId( runningProcess.mId );
      runningProcess.mCpuBurst--;
    } // if
    else if ( processQueue.size() > 0 ) {
      if ( runningProcess.mId != 0 || runningProcess.mCpuBurst != 0 || runningProcess.mArrivalTime != 0 )
        gAllProcess.push_back( runningProcess );
      runningProcess = processQueue.back();
      runningProcess.mWaitingTime = cpuTime - runningProcess.mArrivalTime;
      runningProcess.mTurnaround = runningProcess.mWaitingTime + runningProcess.mCpuBurst;
      processQueue.pop_back();
      if ( runningProcess.mCpuBurst > 0 ) {
        cout << GetProcessId( runningProcess.mId );
        fin << GetProcessId( runningProcess.mId );
        runningProcess.mCpuBurst--;
      } // if
      else if ( gProcessQueue.size() > 0 ) {
        cout << "-";
        fin << "-";
      } // else if
    } // else if
    else {
      cout << "-";
      fin << "-";
    } // else

    cpuTime++;
  } // while

  gAllProcess.push_back( runningProcess );
} // NSJF()

void FCFS() {
  int cpuTime = 0;
  ProcessQueue processQueue;
  Process runningProcess;
  while ( gProcessQueue.size() > 0 || processQueue.size() > 0 || runningProcess.mCpuBurst > 0 ) {
    while ( gProcessQueue.back().mArrivalTime == cpuTime ) {
      processQueue.insert( processQueue.begin(), gProcessQueue.back() );
      gProcessQueue.pop_back();
    } // while

    if ( runningProcess.mCpuBurst > 0 ) {
      cout << GetProcessId( runningProcess.mId );
      fin << GetProcessId( runningProcess.mId );
      runningProcess.mCpuBurst--;
    } // if
    else if ( processQueue.size() > 0 ) {
      if ( runningProcess.mId != 0 || runningProcess.mCpuBurst != 0 || runningProcess.mArrivalTime != 0 )
        gAllProcess.push_back( runningProcess );
      runningProcess = processQueue.back();
      runningProcess.mWaitingTime = cpuTime - runningProcess.mArrivalTime;
      runningProcess.mTurnaround = runningProcess.mWaitingTime + runningProcess.mCpuBurst;
      processQueue.pop_back();
      if ( runningProcess.mCpuBurst > 0 ) {
        cout << GetProcessId( runningProcess.mId );
        fin << GetProcessId( runningProcess.mId );
        runningProcess.mCpuBurst--;
      } // if
      else if ( gProcessQueue.size() > 0 ) {
        cout << "-";
        fin << "-";
      } // else if
    } // else if
    else {
      cout << "-";
      fin << "-";
    } // else

    cpuTime++;
  } // while

  gAllProcess.push_back( runningProcess );
} // FCFS()

void All( int timeSlice ) {
  ProcessQueue processQueue = gProcessQueue;
  vector<ProcessQueue> allProcessVector;
  cout << "==    FCFS==" << endl;
  fin << "==    FCFS==" << endl;
  FCFS();
  cout << endl;
  fin << endl;
  SortByID_Revers( gAllProcess );
  // PrintWaitingAndTurnaround( gAllProcess );
  allProcessVector.push_back( gAllProcess );
  gAllProcess = ProcessQueue();

  cout << "==      RR==" << endl;
  fin << "==      RR==" << endl;
  gProcessQueue = processQueue;
  RR( timeSlice );
  cout << endl;
  fin << endl;
  SortByID_Revers( gAllProcess );
  // PrintWaitingAndTurnaround( gAllProcess );
  allProcessVector.push_back( gAllProcess );
  gAllProcess = ProcessQueue();

  cout << "==    PSJF==" << endl;
  fin << "==    PSJF==" << endl;
  gProcessQueue = processQueue;
  PSJF();
  cout << endl;
  fin << endl;
  SortByID_Revers( gAllProcess );
  // PrintWaitingAndTurnaround( gAllProcess );
  allProcessVector.push_back( gAllProcess );
  gAllProcess = ProcessQueue();

  cout << "==Non-PSJF==" << endl;
  fin << "==Non-PSJF==" << endl;
  gProcessQueue = processQueue;
  NSJF();
  cout << endl;
  fin << endl;
  SortByID_Revers( gAllProcess );
  // PrintWaitingAndTurnaround( gAllProcess );
  allProcessVector.push_back( gAllProcess );
  gAllProcess = ProcessQueue();

  cout << "== Priority==" << endl;
  fin << "== Priority==" << endl;
  gProcessQueue = processQueue;
  PP();
  cout << endl;
  fin << endl;
  SortByID_Revers( gAllProcess );
  // PrintWaitingAndTurnaround( gAllProcess );
  allProcessVector.push_back( gAllProcess );
  gAllProcess = ProcessQueue();

  PrintAll( allProcessVector );
} // All()

void Run() {
  int type = 0, timeSlice = 0;
  vector<ProcessQueue> allProcessVector;
  ReadProcess( type, timeSlice );
  cout << timeSlice << " " << type << endl;
  SortByID( gProcessQueue );
  SortByArrvialTime( gProcessQueue );
  PrintQueue( gProcessQueue );

  fin.open( outputName, ios::out | ios::trunc );

  switch( type ) {
    case 1:
      FCFS();
      cout << endl;
      fin << endl;
      SortByID_Revers( gAllProcess );
      // PrintWaitingAndTurnaround( gAllProcess );
      allProcessVector.push_back( gAllProcess );
      PrintOne( allProcessVector, "FCFS" );
      break;
    case 2:
      NSJF();
      cout << endl;
      fin << endl;
      SortByID_Revers( gAllProcess );
      // PrintWaitingAndTurnaround( gAllProcess );
      allProcessVector.push_back( gAllProcess );
      PrintOne( allProcessVector, "NPSJF" );
      break;
    case 3:
      PSJF();
      cout << endl;
      fin << endl;
      SortByID_Revers( gAllProcess );
      // PrintWaitingAndTurnaround( gAllProcess );
      allProcessVector.push_back( gAllProcess );
      PrintOne( allProcessVector, "PSJF" );
      break;
    case 4:
      RR( timeSlice );
      cout << endl;
      fin << endl;
      SortByID_Revers( gAllProcess );
      // PrintWaitingAndTurnaround( gAllProcess );
      allProcessVector.push_back( gAllProcess );
      PrintOne( allProcessVector, "RR" );
      break;
    case 5:
      PP();
      cout << endl;
      fin << endl;
      SortByID_Revers( gAllProcess );
      // PrintWaitingAndTurnaround( gAllProcess );
      allProcessVector.push_back( gAllProcess );
      PrintOne( allProcessVector, "Priority" );
      break;
    case 6:
      All( timeSlice );
  } // switch

  fin.close();
} // Run()

int main() {
  Run();
  return 0;
} // main()
