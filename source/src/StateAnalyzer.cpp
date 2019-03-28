/**   \file TraceAnalyzer.cpp
 *    \Defines the State Analyzer class
 *    \Intended to function much like a Trace Analyzer 
 *    \i.e. it contains an Init, DeclarePlots and , Analyze (as opposed to Process)
 *    NT Brewer - 3-26-2019
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>

#include <cstdlib>
#include <unistd.h>

#include "damm_plotids.h"
#include "RandomPool.h"
#include "RawEvent.h"
#include "DetectorDriver.h"
#include "StatsAccumulator.h"
#include "StateAnalyzer.h"

using namespace std;

bool StateAnalyzer::isTapeMoveOn;
bool StateAnalyzer::isMeasureOn;
bool StateAnalyzer::isBkgOn;
bool StateAnalyzer::isLightPulserOn;
bool StateAnalyzer::isIrradOn;
double StateAnalyzer::previousCycleTime;
double StateAnalyzer::measureOnTime;
unsigned StateAnalyzer::cycleNumber;

/**
 *  Declare plots for cycle state diagnostics
 *
**/
void StateAnalyzer::DeclarePlots() const
{
	using namespace dammIds::state;
}

StateAnalyzer::StateAnalyzer():logiSummary(NULL)
{
    associatedTypes.insert("logi");//logic sygnals
}

/** Output time processing traces */
StateAnalyzer::~StateAnalyzer() 
{
    cout << "Using Cycle Analyzer"  << endl;
}


/**
 * Initialize the state analysis class.  
 * read and Loop through the map
 * perform minimal diagnostic plotting
 * i.e. figure out a good way to see all state changes vs time
 * set state and time of change.
 */
bool StateAnalyzer::Init(void)
{

    isTapeMoveOn = false;
    isMeasureOn = true;
    isBkgOn = false;
    isLightPulserOn = false;
    isIrradOn = false;
    measureOnTime = -1; 
    cycleNumber = 0;
    return(true);
}

bool StateAnalyzer::Analyze(RawEvent &event)
{
    
    using namespace dammIds::state;
    
    if (!EventProcessor::Process(event))
	return false;


    if (logiSummary == NULL)
	logiSummary = event.GetSummary("logi");

    logiList= logiSummary->GetList();
    logiMap.clear();

    FillLogicMap();

    double actualLogiTime = -1.0;
    double cycleLogiTime = -1.0;

    if(logiSummary->GetMult() > 0)//I have at leat one element in mtasList
    {
		vector<ChanEvent*>::const_iterator logiListIt = logiList.begin();
		actualLogiTime = (*logiListIt)->GetTime() * pixie::clockInSeconds;
		cycleLogiTime = actualLogiTime - measureOnTime;
    }

    SetCycleState();

    return(true);
}


void StateAnalyzer::SetCycleState()
{

//Check flags and set main (static) flags

	//tape		
	if(isTapeMoveOffSignal && isTapeMoveOnSignal)
		cout<<"Error: tape movement signal and end of tape movement signal in the same event"<<endl;
		
	if(isTapeMoveOnSignal && isTapeMoveOn) 
		cout<<"Error: No end of tape movement signal in the last tape cicle"<<endl;
		
	if(isTapeMoveOnSignal)
		isTapeMoveOn = true;
	if(isTapeMoveOffSignal)
		isTapeMoveOn = false;

	//measurement  
	if(isMeasureOffSignal && isMeasureOnSignal)
		cout<<"Error: measurement signal and no measurement signal in the same event"<<endl;
		
	if(isMeasureOnSignal && isMeasureOn) 
		cout<<"Error: No end of measurement signal in the last tape cicle"<<endl;
		
	if(isMeasureOnSignal)
		isMeasureOn = true;
	if(isMeasureOffSignal)
		isMeasureOn = false; 

	//background		
	if(isBkgOffSignal && isBkgOnSignal)
		cout<<"Error: background signal and no background signal in the same event"<<endl;
		
	if(isBkgOnSignal && isBkgOn) 
		cout<<"Error: No end of background signal in the last tape cicle"<<endl;
		
	if(isBkgOnSignal)
		isBkgOn = true;
	if(isBkgOffSignal)
		isBkgOn = false; 
		
	//light pulser	
	if(isLightPulserOffSignal && isLightPulserOnSignal)
		cout<<"Error: light pulser signal and no light pulser signal in the same event"<<endl;
		
	if(isLightPulserOnSignal && isLightPulserOn) 
		cout<<"Error: No end of light pulser signal in the last tape cicle"<<endl;
		
	if(isLightPulserOnSignal)
		isLightPulserOn = true;
	if(isLightPulserOffSignal)
		isLightPulserOn = false;		
		
	//irradiation		
	if(isIrradOffSignal && isIrradOnSignal)
		cout<<"Error: irradiation signal and no irradiation signal in the same event"<<endl;
		
	if(isIrradOnSignal && isIrradOn) 
		cout<<"Error: No end of irradiation signal in the last tape cicle"<<endl;
		
	if(isIrradOnSignal)
		isIrradOn = true;
	if(isIrradOffSignal)
		isIrradOn = false;
 
}


void StateAnalyzer::FillLogicMap()
{
        isTriggerOnSignal = false;
	isTapeMoveOnSignal = false;
	isTapeMoveOffSignal = false;
	isMeasureOnSignal = false;
	isMeasureOffSignal = false;	
 	isBkgOnSignal = false;
	isBkgOffSignal = false;
 	isLightPulserOnSignal = false;
	isLightPulserOffSignal = false;	
 	isIrradOnSignal = false;
	isIrradOffSignal = false;
	
	double logicTreshold = 1;	
	logicSignalsValue = 0;

	for(vector<ChanEvent*>::const_iterator logiListIt = logiList.begin(); logiListIt != logiList.end(); logiListIt++)
	{
		string subtype = (*logiListIt)->GetChanID().GetSubtype();
		if (logiMap.count(subtype)>0)
			cout<<"Error: Detector "<<subtype<<" has "<< logiMap.count(subtype)+1<<" signals in one event"<<endl;
		logiMap.insert(make_pair(subtype,LogicData(((*logiListIt)))));
		
		//set logic flags
		if((*logiListIt)->GetEnergy() > logicTreshold)
		{
			if(subtype == "TRU") {
				isTriggerOnSignal = true;
				measureOnTime = (*logiListIt)->GetTime() * pixie::clockInSeconds;
				cycleNumber ++;
				logicSignalsValue +=1;
			}
			
			if(subtype == "IRU")
			{
				isIrradOnSignal = true;
				logicSignalsValue +=2;
			}
			if(subtype == "IRD")
			{
				isIrradOffSignal = true;
				logicSignalsValue +=4;
			}	
			if(subtype == "LPU")
			{
				isLightPulserOnSignal = true;
				logicSignalsValue +=8;
			}
			if(subtype == "LPD")
			{
				isLightPulserOffSignal = true;
				logicSignalsValue +=16;
			}
			if(subtype == "TMU")
			{
				isTapeMoveOnSignal = true;
				logicSignalsValue +=32;
			}
			if(subtype == "TMD")
			{
				isTapeMoveOffSignal = true;
				logicSignalsValue +=64;
			}
			
			if(subtype == "BGU")
			{
				isBkgOnSignal = true;
				logicSignalsValue +=128;
			}
			if(subtype == "BGD")
			{
				isBkgOffSignal = true;
				logicSignalsValue +=256;
			}
			if(subtype == "MSU")
			{
				isMeasureOnSignal = true;
				logicSignalsValue +=512;
			}
			if(subtype == "MSD")
			{
				isMeasureOffSignal = true;
				logicSignalsValue +=1024;
			}		

		}
		
	}    
}

StateAnalyzer::LogicData::LogicData(string type)
{
    detSubtype     = type;
    energy         = -1.;
    calEnergy      = -1.;
    time           = -1.;
    location       = -1.;
}

StateAnalyzer::LogicData::LogicData(ChanEvent *chan)
{
    detSubtype	= chan->GetChanID().GetSubtype();
    energy	= chan->GetEnergy();
    calEnergy = chan->GetCalEnergy();
    time = chan->GetTime();
    location = chan->GetChanID().GetLocation();
}
