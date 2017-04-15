#include <sys/time.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>

using namespace std;

char** readFile(char* fname, int& m, int& n);

int main(int argc, char* argv[]) {

  struct timeval start, end;
  long mtime, seconds, useconds;

  int m,n;

  char** sequence;

  // Check to see if the appropriate number of arguments were passed.
  if(argc != 3 || strlen(argv[2]) != 2) {
    cout << "\033[31mERROR:\033[0m Please execute this function using the form:\nprogram2 <inputfilename> <-b|-d>\n";
    return 1;
  } else if(){
    cout << "\033[31mERROR:\033[0m Please execute this function using the form:\nprogram2 <inputfilename> <-b|-d>\n";
    return 1;
  }

  // Read the file into an array.
  sequence = readFile(argv[1], m, n);
  if(n == -1) {
    cout << "\033[31mERROR:\033[0m The file \033[33m" << argv[1] << "\033[0m not found." << endl;
    return 1;
  }

  // Print initial output.
  cout << "Input File: \033[32m" << argv[1] << "\033[0m\n";
  cout << "n = \033[32m" << n << "\033[0m, m = \033[32m" << m << "\033[0m\n";

  int ret;
  gettimeofday(&start, NULL);
  mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
  if(argv[2][1] == 'b' || argv[2][1] == 'B') {
    //ret = bottomUpDynamic();
    cout << "Algorithm used: \033[33mBottom Up\033[0m\n";
  } else if(argv[2][1] == 't' || argv[2][1] == 'T') {
    //ret = topDownMemoized();
    cout << "Algorithm used: \033[33mTop Down\033[0m\n";
  }
  gettimeofday(&end, NULL);
  seconds  = end.tv_sec  - start.tv_sec;
  useconds = end.tv_usec - start.tv_usec;
  mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;

  cout << "Algorithm took \033[32m~" << mtime << "ms\033[0m.\n";

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
    sequence[0] = new char[m+1];
    sequence[1] = new char[n+1];
    in.get();
    in.get(sequence[0], m+1);
    in.get();
    in.get(sequence[1], n+1);
  }
  in.close();
  return sequence;
}
