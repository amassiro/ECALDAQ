// 
// c++ -o createRootFile.exe createRootFile.cpp `root-config --cflags --glibs`
// ./createRootFile.exe   dumpMachinesResHistory.txt
// 


#include <map>
#include <vector>
#include <string> 

#include <iomanip>      // std::get_time
#include <ctime>        // struct std::tm

#include <algorithm> 

#include <fstream>
#include <iostream> 
#include <sstream> 

#include "TGraph.h"
#include "TMultiGraph.h"
#include "TCanvas.h"
#include "TDatime.h"
#include "TAxis.h"


int main(int argc, char** argv) {
 
 std::cout << " Create ROOT file from history text file " << std::endl;
 
 std::map<std::pair <std::time_t, std::string> , std::vector<std::string> > machine_res;
 std::map<std::pair <std::time_t, std::string> , float > machine_res_memory;
 std::map<std::pair <std::time_t, std::string> , float > machine_res_cpu;
 std::vector<std::string> machines_names;
 
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
       float memory_total = stof(tempString_value_total);
       
       line >> tempString_value_total; 
//        std::cout << " -||" << line.rdbuf()->in_avail() << "||-" ;
//        std::cout << std::endl;
       vect_values.push_back(tempString_value_total);
       float memory_used = stof(tempString_value_total);
       
       line >> tempString_value_total; 
       vect_values.push_back(tempString_value_total);
       float memory_free = stof(tempString_value_total);
       
       line >> tempString_value_total; 
       vect_values.push_back(tempString_value_total);
       std::string::size_type iremove = tempString_value_total.find("\%id");
       if (iremove != std::string::npos) {
        tempString_value_total.erase(iremove, 3);
       }
//        std::cout << tempString_value_total << std::endl;
       float cpu_free = stof(tempString_value_total);
       
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
       machine_res[std::pair <std::time_t, std::string>(time,tempString_value_machineName)] = vect_values;   

       machine_res_memory[std::pair <std::time_t, std::string>(time,tempString_value_machineName)] = memory_free / memory_total;   
       machine_res_cpu   [std::pair <std::time_t, std::string>(time,tempString_value_machineName)] = cpu_free;   
       
       
       bool isPresent = (std::find(machines_names.begin(), machines_names.end(), tempString_value_machineName) != machines_names.end());
       if (!isPresent) {
        machines_names.push_back(tempString_value_machineName);
       }
      }
      
     }
    } 
   }
   
   readfile.close();
   
  }
  
  
  //---- plot ----
  typedef std::map<std::pair <std::time_t, std::string> , float >::iterator it_type;
  for (int iMachine = 0; iMachine < machines_names.size(); iMachine++) {
   std::string plot_name = machines_names.at(iMachine) + ".png";
   
   TGraph*  gr_memory = new TGraph();
   gr_memory->SetLineColor(2);
   gr_memory->SetLineWidth(1);
   gr_memory->SetMarkerColor(2);
   gr_memory->SetMarkerStyle(21);

   int nPoint = 0;
   for(it_type iterator = machine_res_memory.begin(); iterator != machine_res_memory.end(); iterator++) {
    if (iterator->first.second == machines_names.at(iMachine)) {
     std::time_t timer = iterator->first.first;
     gr_memory->SetPoint(nPoint, timer, iterator->second);
     nPoint++;
    }
   }
   
   TGraph*  gr_cpu = new TGraph();
   gr_cpu->SetLineColor(3);
   gr_cpu->SetLineWidth(1);
   gr_cpu->SetMarkerColor(3);
   gr_cpu->SetMarkerStyle(22);
   
   nPoint = 0;
   for(it_type iterator = machine_res_cpu.begin(); iterator != machine_res_cpu.end(); iterator++) {
    if (iterator->first.second == machines_names.at(iMachine)) {
     std::time_t timer = iterator->first.first;
     gr_cpu->SetPoint(nPoint, timer, iterator->second / 100.);
     nPoint++;
    }
   }
   
   TCanvas* cc = new TCanvas(machines_names.at(iMachine).c_str(),"cc",800,500);

   TMultiGraph *mg = new TMultiGraph();
   mg->Add(gr_cpu,   "lp");
   mg->Add(gr_memory,"lp");
   mg->Draw("a");
   mg->GetXaxis()->SetTimeDisplay(1);
   mg->GetXaxis()->SetNdivisions(-503);
   mg->GetXaxis()->SetTimeFormat("%Y-%m-%d %H:%M");
   mg->GetXaxis()->SetTimeOffset(0,"gmt");
   mg->GetYaxis()->SetRangeUser(0.0, 1.0);
   cc->SetGrid();
   cc->Modified();
   
   cc->SaveAs(plot_name.c_str());
   //    gr->GetXaxis()->SetTitle("X title");
//    gr->GetYaxis()->SetTitle("Y title");
//    
//    // TCanvas::Update() draws the frame, after which one can change it
   
  }
  
  
  
  
 }
  
}