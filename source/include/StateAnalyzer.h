/**   \file TraceAnalyzer.h
 *    \Header file for the StateAnalyzer class
 *    \Intended to function much like a Trace Analyzer
 *    NT Brewer - 3-26-2019
 */

#ifndef __STATEANALYZER_H_
#define __STATEANALYZER_H_

#include <string>
#include <vector>
#include <sys/times.h>

#include "EventProcessor.h"

class DetectorSummary;
class RawEvent;
class ChanEvent;

using std::string;
using std::vector;

/** \logic and cycle state analysis
 *
 *  \Analyzer for Logical signals, sets the state and makes it available 
 */

class StateAnalyzer: public EventProcessor {
  
  private:
    static bool isTapeMoveOn;
    static bool isMeasureOn;
    static bool isBkgOn;
    static bool isLightPulserOn;
    static bool isIrradOn;
    static double previousCycleTime;
    static double measureOnTime;
    static unsigned cycleNumber;

    bool isTriggerOnSignal;
    bool isTapeMoveOnSignal;
    bool isTapeMoveOffSignal;
    bool isMeasureOnSignal;
    bool isMeasureOffSignal;	
    bool isBkgOnSignal;
    bool isBkgOffSignal;
    bool isLightPulserOnSignal;
    bool isLightPulserOffSignal;	
    bool isIrradOnSignal;
    bool isIrradOffSignal;
    int logicSignalsValue;

    struct LogicData 
    {
        LogicData(std::string type="");
        LogicData(ChanEvent *chan);
            
        std::string detSubtype;
        double energy;
        double calEnergy;
        double time;
        double location;
    };

    // things associated with timing
    double userTime;          ///< user time used by this class
    double systemTime;        ///< system time used by this class
    double clocksPerSecond;   ///< frequency of system clock

    void FillLogicMap();
    void SetCycleState();

    DetectorSummary *logiSummary;
    std::vector<ChanEvent*> logiList;
    std::map<std::string, struct LogicData>  logiMap;

 public:
    virtual bool Init(void);
    virtual void DeclarePlots() const;
    virtual bool Analyze(RawEvent &event);

    StateAnalyzer();
    ~StateAnalyzer();

    bool HasCycle(void) const {return true;}
    bool GetLogicSignal(void) const {return logicSignalsValue;}
    bool GetTapeOn(void) const {return isTapeMoveOn;}
    bool GetMeasureOn(void) const {return isTapeMoveOn;}
    bool GetBkgOn(void) const {return isBkgOn;}
    bool GetLaserOn(void) const {return isLightPulserOn;}
    bool GetBeamOn(void) const {return isIrradOn;}
    unsigned GetCycleNumber(void) const {return cycleNumber;}
    double GetMeasureTime(void) const {return measureOnTime;}
    double GetPreviousTime(void) const {return previousCycleTime;}
};

#endif // __STATEANALYZER_H_
