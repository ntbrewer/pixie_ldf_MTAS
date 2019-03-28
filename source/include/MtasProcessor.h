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
        DetectorSummary *refmodSummary; //added by Goetz

	double refmodEnergy;

    
        static double measureOnTime;
        double firstTime;


	//booleans for rings
	bool isCenter;
	bool isInner;
	bool isMiddle;
	bool isOuter;
	bool isCenterOnly;
	bool isInnerOnly;
	bool isMiddleOnly;
	bool isOuterOnly;
	bool isAll;

    public:
        MtasProcessor(); // no virtual c'tors
        virtual void DeclarePlots(void) const;
        virtual bool Process(RawEvent &event);

    private:
        void FillMtasMap();
        void FillSiliMap();
        void FillRefModMapAndEnergy();


        double maxLocation; 
	int nrOfCentralPMTs;
 

        /*
        void FillMtasEnergyVectors();*/
        void SetIfOnlyRingBool();

        struct MtasData //to trzeba przerobic // Needs rewritten?
        {
            MtasData(std::string type="");
	    MtasData(ChanEvent *chan);
            
            std::string detSubtype;
            double energy;
            double calEnergy;
            double time;
            double location;

            bool isTapeMoveOn;
            bool isMeasureOn;
            bool isBkgOn;
            bool isLaserOn;
            bool isBeamOn;
            //std::vector<int> trace; not necessary for MTAS
        };


	std::vector<ChanEvent*> mtasList;
	std::vector<ChanEvent*> siliList;
	std::vector<ChanEvent*> refmodList;

	std::map<std::string, struct MtasData>  mtasMap;
	std::map<std::string, struct MtasData>  siliMap;
	std::map<std::string, struct MtasData>  refmodMap;


        bool isBetaSignal;
        double betaTime;
    	double maxSiliconSignal;
};

#endif // __MTAS_PROCESSOR_H_
