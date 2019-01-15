/** \file MtasProcessor.h
 *
 * Header file for MTAS analysis
 */

#ifndef __MTAS_PROCESSOR_H_
#define __MTAS_PROCESSOR_H_

#include "EventProcessor.h"
#include <vector>
#include <map>

class DetectorSummary;
class RawEvent;
class ChanEvent;
/**
 * \brief Handles detectors of type Mtas
 */
class MtasProcessor : public EventProcessor 
{
    private:
        DetectorSummary *mtasSummary; ///< all detectors of type Mtas
        DetectorSummary *siliSummary; 
        DetectorSummary *logiSummary;
        DetectorSummary *refmodSummary; //added by Goetz

        bool isTapeMoveOn;
        bool isMeasureOn;
        bool isBkgOn;
        bool isLightPulserOn;
        bool isIrradOn;
        unsigned cycleNumber;
    
        double measureOnTime;
        double firstTime;

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

        static const double logicTreshold = 1;
	int logicSignalsValue;

        void FillLogicMap();
        /*double maxLocation; 
	double nrOfCentralPMTs; 

        void FillMtasMap();
        void FillSiliMap();
        void FillRefModMap();
        
        void SetCycleState();
        void FillMtasEnergyVectors();
        void FillRefModEnergyVector();
        void SetIfOnlyRingBool();*/

        struct MtasData //to trzeba przerobic // Needs rewritten?
        {
            MtasData(ChanEvent *chan);
            
            std::string detSubtype;
            double energy;
            double calEnergy;
            double time;
            double location;

            //std::vector<int> trace; not necessary for MTAS
        };

        std::vector<ChanEvent*> logiList;
        std::map<std::string, struct MtasData>  logiMap;

    public:
        MtasProcessor(); // no virtual c'tors
        virtual void DeclarePlots(void) const;
        virtual bool Process(RawEvent &event);


};

#endif // __MTAS_PROCESSOR_H_
