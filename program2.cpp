#include <sys/time.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>

using namespace std;

char** readFile(char* fname, int& m, int& n);
int** bottomUpDynamic(char** seq, int m, int n);
int** tdmDriver(char** seq, int m, int n);
int topDownMemoized(char** seq, int** C, int m, int n);
char* backtrack(char** seq, int** C, int m, int n);


int main(int argc, char* argv[]) {
  cout << endl << "\e[4mLongest Common Subsequence Calculator\e[0m" << endl << endl;
  struct timeval start, end;
  long mtime, seconds, useconds;

  int m,n,length;

  char** sequence;

  // Check to see if the appropriate number of arguments were passed.
  if(argc != 3 || strlen(argv[2]) != 2) {
    cout << "\033[31mERROR:\033[0m Please execute this function using the form:\nprogram2 <inputfilename> <-b|-t>\n";
    cout << endl << endl;
    return 1;
  }

  // Read the file into an array.
  sequence = readFile(argv[1], m, n);
  if(n == -1) {
    cout << "\033[31mERROR:\033[0m The file \033[33m" << argv[1] << "\033[0m not found." << endl;
    cout << endl << endl;
    return 1;
  }

  // Print initial output.
  cout << "Input File: \033[32m" << argv[1] << "\033[0m\n";
  cout << "n = \033[32m" << n << "\033[0m, m = \033[32m" << m << "\033[0m\n";

  int** C;
  gettimeofday(&start, NULL);
  mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
  if(argv[2][1] == 'b' || argv[2][1] == 'B') {
    C = bottomUpDynamic(sequence, m, n);
    cout << "Algorithm used: \033[33mBottom Up\033[0m\n";
  } else if(argv[2][1] == 't' || argv[2][1] == 'T') {
    C = tdmDriver(sequence, m, n);
    cout << "Algorithm used: \033[33mTop Down\033[0m\n";
  } else {
    cout << "\033[31mERROR:\033[0m Please execute this function using the form:\nprogram2 <inputfilename> <-b|-t>\n";
    cout << endl << endl;
    return 1;
  }

  // Do the backtracking for either algorithm.
  char* ret = backtrack(sequence, C, m, n);
  length = C[m][n];


  gettimeofday(&end, NULL);
  seconds  = end.tv_sec  - start.tv_sec;
  useconds = end.tv_usec - start.tv_usec;
  mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;

  for(int seqId = 0; seqId < 2; seqId++) {
    cout << "Sequence "<< seqId+1 << ":" << endl;
    int lcsIndex = 0;
    for(int i = 1; i <= m; i++) {
      if(sequence[seqId][i] == ret[lcsIndex]) {
        cout << "\033[32m" << sequence[seqId][i] << "\033[0m";
        lcsIndex++;
      } else {
        cout << "\033[33m" << sequence[seqId][i] << "\033[0m";
      }
    }
    cout << endl << endl;
  }

  cout << "LCS: \n\033[32m" << ret << "\033[0m\nThe LCS has length \033[32m" << length << "\033[0m." << endl;

  cout << "Algorithm took \033[32m~" << mtime << "ms\033[0m.\n";

  cout << endl << endl;
}

char* backtrack(char** seq, int** C, int m, int n) {

  char* ret = new char[C[m][n]+1];

  int i = m;
  int j = n;
  int count = C[i][j]-1;

  while(i > 0 && j > 0) {
    if(seq[0][i] == seq[1][j]) {
      ret[count] = seq[0][i];
      i--;
      j--;
      count--;
    } else {
      if(C[i-1][j] > C[i][j-1]) {
        i--;
      } else {
        j--;
      }
    }
  }
  ret[C[m][n]] = '\0';
  return ret;
}

int** tdmDriver(char** seq, int m, int n) {

  int** C = new int*[m+1];
  for(int i = 0; i <= m; i++) {
    C[i] = new int[n+1];
  }
  for(int i = 0; i <= m; i++) {
    for(int j = 0; j <= n; j++) {
      C[i][j] = -1;
    }
  }
  C[m][n] = topDownMemoized(seq, C, m, n);
  return C;


}

int topDownMemoized(char** seq, int** C, int m, int n) {
  /*

  C(i,j) = | 0                          if i = 0 or j = 0
           | C(i-1, j-1) + 1            if i > 0 and j > 0 and X[i]  = Y[j]
           | Max(C(i, j-1), C(i-1, j))  if i > 0 and j > 0 and X[i] != Y[j]

  */
  if(C[m][n] < 0) {
    if(m == 0 || n == 0) {
      C[m][n] = 0;
    } else if(seq[0][m] == seq[1][n]) {
      C[m][n] = topDownMemoized(seq, C, m-1, n-1) + 1;
    } else {
      C[m][n] = max(topDownMemoized(seq, C, m, n-1), topDownMemoized(seq, C, m-1, n));
    }
  }

  return C[m][n];
}



int** bottomUpDynamic(char** seq, int m, int n) {

  int** C = new int*[m+1];
  for(int i = 0; i <= m; i++) {
    C[i] = new int[n+1];
  }

  for(int i = 0; i <= m; i++) {
    C[i][0] = 0;
  }

  for(int j = 0; j <= n; j++) {
    C[0][j] = 0;
  }

  /*

  C(i,j) = | 0                          if i = 0 or j = 0
           | C(i-1, j-1) + 1            if i > 0 and j > 0 and X[i]  = Y[j]
           | Max(C(i, j-1), C(i-1, j))  if i > 0 and j > 0 and X[i] != Y[j]

  */

  for(int i = 1; i <= m; i++) {
    for(int j = 1; j <= n; j++) {
      if(seq[0][i] == seq[1][j]) {
        C[i][j] = C[i-1][j-1] + 1;
      } else {
        C[i][j] = max(C[i][j-1], C[i-1][j]);
      }
    }
  }

  return C;
}


char** readFile(char* fname, int& m, int& n) {
  char** sequence;
  m = -1;
  n = -1;
  ifstream in;
  in.open(fname);
  if(in) {
    in >> m;
    in >> n;
    if(m == -1 || n == -1) {
      in.close();
      return sequence;
    }
    sequence = new char*[2];
    sequence[0] = new char[m+2];
    while (in.peek()!='\n') {
      in.get();
    }
    sequence[1] = new char[n+2];
    in.get();
    in.get(sequence[0] + 1, m+1);
    in.get();
    in.get(sequence[1] + 1, n+1);
  }

  in.close();
  return sequence;
}
