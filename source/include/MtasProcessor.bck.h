/** \file MtasProcessor.h
 *
 * Header file for MTAS analysis
 */

#ifndef __MTAS_PROCESSOR_H_
#define __MTAS_PROCESSOR_H_

#include "EventProcessor.h"
#include <vector>

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

	

        static bool isTapeMoveOn;
        static bool isMeasureOn;
        static bool isBkgOn;
        static bool isLightPulserOn;
        static bool isIrradOn;
        static unsigned cycleNumber;
    
        static double measureOnTime;
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

    public:
        MtasProcessor(); // no virtual c'tors
        virtual void DeclarePlots(void) const;
        virtual bool Process(RawEvent &event);

    private:
        //void FillLogicMap();
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
};

#endif // __MTAS_PROCESSOR_H_
