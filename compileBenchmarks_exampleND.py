#!/usr/bin/python

import sys
import os
import commands
import shlex

###########################################################################
###########################################################################
###########################################################################
###########################################################################
###########################################################################
###########################################################################

#LIST OF FLAGS TO TEST.
configurationCommands = ['./goas ../tst/oas_queries/0scan/1_scan',
                         './goas ../tst/oas_queries/0scan/100_scan',
                         './goas ../tst/oas_queries/0scan/1k_scan',
                         './goas ../tst/oas_queries/0scan/10k_scan',
                         './goas ../tst/oas_queries/0scan/50k_scan',
                         './goas ../tst/oas_queries/0scan/100k_scan',
                         './goas ../tst/oas_queries/0scan/200k_scan',
                         './goas ../tst/oas_queries/0scan/300k_scan',
                         './goas ../tst/oas_queries/0scan/400k_scan']

def changeDirectoryToBin():
    os.chdir('bin')

def comeBackToTheRootPathFromExecutionPath():
    os.chdir('../')

def calculateTime(output):
    outputArray = []
    outputArray = shlex.split(output) 
    time = outputArray[1]
    print 'time [%s]' % time
    minutes = float(time[0])
    #seconds = float(time[2:8])
    seconds=float(time[time.find("m")+1:time.find("s")])
    timePrinted = str(int(minutes*60*1000 + seconds*1000))
    print 'timePrinted [%s]' % timePrinted
    return timePrinted

def write(FILE, output):
    FILE.write(output)

def executingBenchmarkNTimes(n, FILE, configurationCommand):
    print 'Executing times: %s' % n
    list = ''
    for i in range(n):
        output = executingExampleND(FILE)
        #output = executingExampleC(FILE)
        list = list+' '+str(calculateTime(output))
    lineToPrint = ' \"'+configurationCommand+'\" '+list+'\n'
    write(FILE, lineToPrint)

def executingExampleND(FILE):
    print 'Executing Example ND: ' 
    os.system('purge')
    output = commands.getoutput("time ./temp > /dev/null")
    print 'output [%s]' % output 
    return output

def configuring(configurationCommand):
    print 'configuring: [%s]' % configurationCommand
    os.system('purge')
    output = commands.getoutput(configurationCommand)
    print '%s' % output
    
def transverseRootFolders():
    FILE = open("report.dat", "w")
    for configurationCommand in configurationCommands:
        changeDirectoryToBin();
        configuring(configurationCommand)
        executingBenchmarkNTimes(10, FILE, configurationCommand)
        comeBackToTheRootPathFromExecutionPath()

    FILE.close()

def main():
    transverseRootFolders()			
			
if __name__ == '__main__':
	main()
	
