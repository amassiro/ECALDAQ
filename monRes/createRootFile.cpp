// 
// c++ -o createRootFile.exe createRootFile.cpp `root-config --cflags --glibs`
// ./createRootFile.exe   dumpMachinesResHistory.txt
// 


#include <map>
#include <vector>

#include <iomanip>      // std::get_time
#include <ctime>        // struct std::tm

#include <fstream>
#include <iostream> 
#include <sstream> 

int main(int argc, char** argv) {
 
 std::cout << " Create ROOT file from history text file " << std::endl;
 
 std::map<std::string, std::pair <std::time_t, std::vector<std::string> > > machine_res;
 
 
 if ( argc != 2 ) {
  // We print argv[0] assuming it is the program name
  std::cout << " usage: " << argv[0] <<" <filename>" << std::endl;
 }
 else {
  std::cout << " Reading : " << argv[1] << std::endl;
  
  std::ifstream readfile;
  readfile.open(argv[1]);
  std::string buffer;
  std::string tempString;
  std::string tempString_value_machineName;
  std::string tempString_value_total;
  
  if (readfile) {
   
   while(!readfile.eof()) {
    getline(readfile,buffer);
    if (buffer != ""){ ///---> save from empty line at the end!
     std::stringstream line( buffer );      
     line >> tempString; 
     //----          Machine..........................................Total(MB) Used(MB)        Free(MB)        cpuIdle         usage5          usage15         time
     //---- example: # ecalod-disk01/ecalod-web01                     3942              3902            40               98.7%id        .02             .01     15:45:31
     if (tempString.at(0) == '#') {
      line >> tempString_value_machineName; 
      std::vector <std::string> vect_values;
      if (line.str().empty()) {
       std::cout << " is empty!" << std::endl;
      }
//       std::cout << " line = <---" << line.str() << "---> " ;
//       std::cout << " " << tempString_value_machineName;
//       std::cout << " -||" << line.rdbuf()->in_avail() << "||-" ;
      line >> tempString_value_total; 
//       std::cout << " -||" << line.rdbuf()->in_avail() << "||-" ;
//       std::cout << " " << tempString_value_total ;
      if (line.rdbuf()->in_avail() != 0) {    
       vect_values.push_back(tempString_value_total);
       line >> tempString_value_total; 
//        std::cout << " -||" << line.rdbuf()->in_avail() << "||-" ;
//        std::cout << std::endl;
       vect_values.push_back(tempString_value_total);
       line >> tempString_value_total; 
       vect_values.push_back(tempString_value_total);
       line >> tempString_value_total; 
       vect_values.push_back(tempString_value_total);
       line >> tempString_value_total; 
       vect_values.push_back(tempString_value_total);
       line >> tempString_value_total; 
       vect_values.push_back(tempString_value_total);
       line >> tempString_value_total; 
       vect_values.push_back(tempString_value_total);
       //---- time
       struct std::tm when;
       strptime(tempString_value_total.c_str(), "%H:%M:%S", &when);
       std::time_t time = mktime(&when);
       machine_res[tempString_value_machineName] = std::pair<std::time_t, std::vector<std::string> > (time, vect_values);       
      }
      
     }
    } 
   }
   
   readfile.close();
   
  }
  
  
  //---- plot ----
  
  
  
  
  
  
  
  
  
  

 
}