#!/usr/bin/env python

import json
import sys
from sys import exit
import ROOT
import optparse
import os.path
import string
import logging
import traceback
from array import array
from collections import OrderedDict
import math

import os




if __name__ == '__main__':
    print '''
--------------------------------------------------------------------------------------------------

    Convert ResMon
 
--------------------------------------------------------------------------------------------------
'''    

    usage = 'usage: %prog [options]'
    parser = optparse.OptionParser(usage)

    parser.add_option('--inputFile'      , dest='inputFile'      , help='input file with values'           , default='example.txt')
    parser.add_option('--outputFile'     , dest='outputFile'     , help='output file with values'          , default='out_example.txt')
          
    # read default parsing options as well
    #hwwtools.addOptions(parser)
    #hwwtools.loadOptDefaults(parser)
    (opt, args) = parser.parse_args()

    sys.argv.append( '-b' )
    ROOT.gROOT.SetBatch()


    print " inputFile        = ", opt.inputFile
    print " outputFile       = ", opt.outputFile

    iFile = open (opt.inputFile)

    information = {}
     
    with iFile:
      for line in iFile:
        if '#' in line :
          #print "line = ", line
          if len(line.split()) > 2 :
            ### esod-esm                                       23980          1505            22475            99.2%id                0               0               1471874054
            useless, key, totalMB, usedMB, freeMB, cpuIdle, boh, bah, time = line.rstrip().split()
            #print " useless = " , useless
            #print " totalMB = " , totalMB
            cpuIdle = cpuIdle.replace("%id","")
            
            #information[string(key) + string(time) ] = [ 
            information[ (key, time)  ] = [ totalMB, usedMB, freeMB, cpuIdle ]
          
    #print "information = ", information
      
 

    oFile = open(opt.outputFile, 'w')
    #oFile.write('// to copy\n')

     
     
    oFile.write('  <html>                                                                                        \n')
    oFile.write('  <head>                                                                                        \n')
    oFile.write('  <link rel="stylesheet" type="text/css" href="mystyle.css">                                    \n')
    oFile.write('                                                                                                \n')
    oFile.write('                                                                                                \n')
    oFile.write('  <!--Load the AJAX API-->                                                                      \n')
    oFile.write('  <script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>       \n')
    oFile.write('  <script type="text/javascript">                                                               \n')
    oFile.write('                                                                                                \n')
    oFile.write('                                                                                                \n')
    oFile.write('                                                                                                \n')
    oFile.write('                                                                                                \n')
    oFile.write('                                                                                                \n')
    oFile.write('  google.charts.load(\'current\', {packages: [\'corechart\']});                                 \n')
    oFile.write('  google.charts.setOnLoadCallback(drawCurveTypes);                                              \n')
    oFile.write('                                                                                                \n')
    oFile.write('  function drawCurveTypes() {                                                                   \n')
    oFile.write('    var data = new google.visualization.DataTable();                                            \n')
    oFile.write('    data.addColumn(\'date\', \'X\');                                                            \n')
    oFile.write('                                                                                                \n')
    oFile.write('                                                                                                \n')




     
     

    list_of_machines = []
    for key, value in information.items() :
      if key[0] not in list_of_machines :
        list_of_machines.append(key[0])
        
    for machine in list_of_machines :
      oFile.write( ' data.addColumn(\'number\', \'%s\'); \n' % machine)
    oFile.write( ' \n' )
    oFile.write( ' \n' )
    oFile.write( ' \n' )

    oFile.write('    data.addRows([                                                                              \n')
    oFile.write('                                                                                                \n')
     

   



     
    for key, value in information.items() :
      #print " ",  key[1]

      temp_date = ROOT.TDatime(long(key[1]))
   
      #oFile.write( ' new Date({0:d},  {1:d},  {2:d},  {3:d},  {4:d}) ,  {5:.2f}  \n'.format(
           #temp_date.GetYear() , 
           #temp_date.GetMonth() ,
           #temp_date.GetDay() , 
           #temp_date.GetHour() , 
           #temp_date.GetMinute() , 
           #float(float(value[1]) / float(value[0])) ) 
      #)
    
      oFile.write( ' [ new Date({0:d},  {1:d},  {2:d},  {3:d},  {4:d})  '.format(
           temp_date.GetYear() , 
           temp_date.GetMonth() ,
           temp_date.GetDay() , 
           temp_date.GetHour() , 
           temp_date.GetMinute() ) 
      )          


      for machine in list_of_machines :
        if  key[0] == machine :
          oFile.write( ' , {0:.2f} '.format(float(float(value[1]) / float(value[0])))   )   
        else :
          oFile.write( ' , null '  )   
        
      oFile.write(' ] , \n ')
      
      
      
    oFile.write('        ]);                                                                                     \n')
                                                           
     
    
    
    
    
    oFile.write('               var options = {                                                                                 \n ')
    oFile.write('               width: 900,                                                                                     \n ')
    oFile.write('               height: 500,                                                                                    \n ')
    oFile.write('                                                                                                               \n ')
    oFile.write('               hAxis: {                                                                                        \n ')
    oFile.write('                  title: \'Time\',                                                                             \n ')
    oFile.write('                  format: \'yy/M/d/hh\',                                                                       \n ')
    oFile.write('                  gridlines: {                                                                                 \n ')
    oFile.write('                    count: -1,                                                                                 \n ')
    oFile.write('                    units: {                                                                                   \n ')
    oFile.write('                      days: {format: [\'MMM dd\']},                                                            \n ')
    oFile.write('                      hours: {format: [\'HH:mm\', \'ha\']},                                                    \n ')
    oFile.write('                    }                                                                                          \n ')
    oFile.write('                  },                                                                                           \n ')
    oFile.write('                  minorGridlines: {                                                                            \n ')
    oFile.write('                    units: {                                                                                   \n ')
    oFile.write('                      hours: {format: [\'hh:mm:ss a\', \'ha\']},                                               \n ')
    oFile.write('                      minutes: {format: [\'HH:mm a Z\', \':mm\']}                                              \n ')
    oFile.write('                    }                                                                                          \n ')
    oFile.write('                  }                                                                                            \n ')
    oFile.write('                                                                                                               \n ')
    oFile.write('                },                                                                                             \n ')
    oFile.write('                                                                                                               \n ')
    oFile.write('               vAxis: {                                                                                        \n ')
    oFile.write('                    title : \'CPU\'                                                                            \n ')
    oFile.write('                },                                                                                             \n ')
    oFile.write('               series: {                                                                                       \n ')
    oFile.write('                                                                                                               \n ')


    for imachine in range(len(list_of_machines)) :
      oFile.write('                     %d: {lineWidth: 0.3,    pointSize : 5 , interpolateNulls: true  },                      \n ' % (imachine) )

    oFile.write('                                                                                                               \n ')
    oFile.write('                     },                                                                                        \n ')
    oFile.write('                                                                                                               \n ')
    oFile.write('                                                                                                               \n ')
    oFile.write('               explorer: {                                                                                     \n ')
    oFile.write('                         actions: [\'dragToZoom\', \'rightClickToReset\'],                                     \n ')
    oFile.write('                         maxZoomIn : 0.01                                                                      \n ')
    oFile.write('                         }                                                                                     \n ')
    oFile.write('                                                                                                               \n ')
    oFile.write('              };                                                                                               \n ')
    oFile.write('                                                                                                               \n ')
    oFile.write('                                                                                                               \n ')
    oFile.write('              var chart = new google.visualization.LineChart(document.getElementById(\'chart_div\'));          \n ')
    oFile.write('              chart.draw(data, options);                                                                       \n ')
      
      
      

    oFile.write( 'hideSelected = function () {' )
    for imachine in range(len(list_of_machines)) :
      oFile.write( ' if(Hidden_%d){  new_data.hideColumns([%d]); } \n' % (imachine+1, imachine+1) )
    oFile.write( '}' )
    oFile.write( ' \n' )




  

    for imachine in range(len(list_of_machines)) :
      oFile.write( ' var hide_%d = document.getElementById("hide_%d"); \n' % (imachine+1, imachine+1) )
      oFile.write( ' var Hidden_%d = false; \n' % (imachine+1) )
      oFile.write( ' hide_%d.onclick = function() \n' % (imachine+1) )
      oFile.write( '  {  Hidden_%d = !Hidden_%d;   new_data = new google.visualization.DataView(data);  hideSelected(); chart.draw(new_data, options); }; \n' % (imachine+1, imachine+1) )
   
    oFile.write( ' \n' )

 
    
    oFile.write('        }                                          \n ')
    oFile.write('        </script>                                  \n ')
    oFile.write('                                                   \n ')
    oFile.write('         </head>                                   \n ')
    oFile.write('                                                   \n ')
    oFile.write('         <body>                                    \n ')
    oFile.write('                                                   \n ')
    oFile.write('          <div id="chart_div"></div>               \n ')
    oFile.write('                                                   \n ')
    oFile.write('                                                   \n ')
    oFile.write('        <ul>                                       \n ')


     
    for imachine in range(len(list_of_machines)) :
      oFile.write( ' <li> %s  <label class="switch">  <input type="checkbox" checked> <div class="slider round" id="hide_%d"></div> </label><br></li> \n' %(list_of_machines[imachine], imachine+1))
    oFile.write( ' \n' )
  
    oFile.write('        </ul>                                       \n ')

    oFile.write('       </body>                                    \n ')
    oFile.write('     </html>                                    \n ')
 

    
 


    
   
   


  
    #print " outputFile       = ", opt.outputFile


