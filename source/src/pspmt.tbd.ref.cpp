/*    //read in anode & dynode signals
    hiDynode = event.GetSummary("pspmt:dynode_high")->GetList();
    lowDynode = event.GetSummary("pspmt:dynode_low")->GetList();
    hiAnode = event.GetSummary("pspmt:anode_high")->GetList();
    lowAnode = event.GetSummary("pspmt:anode_low")->GetList();
    //read in other signals
    veto = event.GetSummary("pspmt:veto")->GetList();
    ionTrig = event.GetSummary("pspmt:ion")->GetList();
    desi = event.GetSummary("pspmt:desi")->GetList();
    separatorScint = event.GetSummary("pspmt:f11")->GetList(); 

   //Plot Dynode QDCs
    for (auto it = lowDynode.begin(); it != lowDynode.end(); it++) {
        if (DetectorDriver::get()->GetSysRootOutput()) {
            PSstruct.energy = (*it)->GetCalibratedEnergy();
            PSstruct.time = (*it)->GetTimeSansCfd();
            PSstruct.subtype = (*it)->GetChanID().GetSubtype();
            PSstruct.tag = (*it)->GetChanID().GetGroup();
            pixie_tree_event_->pspmt_vec_.emplace_back(PSstruct);
            PSstruct = processor_struct::PSPMT_DEFAULT_STRUCT;
        }
        plot(DD_DYNODE_QDC, (*it)->GetTrace().GetQdc(), 0);
    }
    for (auto it = hiDynode.begin(); it != hiDynode.end(); it++) {
        if (DetectorDriver::get()->GetSysRootOutput()) {
            PSstruct.energy = (*it)->GetCalibratedEnergy();
            PSstruct.time = (*it)->GetTimeSansCfd();
            PSstruct.subtype = (*it)->GetChanID().GetSubtype();
            PSstruct.tag = (*it)->GetChanID().GetGroup();
            pixie_tree_event_->pspmt_vec_.emplace_back(PSstruct);
            PSstruct = processor_struct::PSPMT_DEFAULT_STRUCT;
        }
        plot(DD_DYNODE_QDC, (*it)->GetTrace().GetQdc(), 1);
    }

    //set up position calculation for low / high gain yso signals and ion scint
    position_low.first = 0, position_low.second = 0;
    position_high.first = 0, position_high.second = 0;
//initalized all the things
    double energy = 0;
    double xa_l = 0, ya_l = 0, xb_l = 0, yb_l = 0;
    double xa_h = 0, ya_h = 0, xb_h = 0, yb_h = 0;
    double top_l = 0, top_r = 0, bottom_l = 0, bottom_r = 0;
    bool hasPosition_low = false, hasPosition_high = false, hasPosition_ion = false, hasUpstream = false,
    hasDeSi = false, hasVeto = false;

    plot(DD_MULTI, lowDynode.size(), 0);
    plot(DD_MULTI, hiDynode.size(), 1);

    plot(DD_MULTI, lowAnode.size(), 2);
    plot(DD_MULTI, hiAnode.size(), 3);


    double lowAnodeSum = 0;
    for (auto it = lowAnode.begin(); it != lowAnode.end(); it++) {
        //check signals energy vs threshold
        energy = (*it)->GetCalibratedEnergy();

        if (DetectorDriver::get()->GetSysRootOutput()) {
            PSstruct.energy = (*it)->GetCalibratedEnergy();
            PSstruct.time = (*it)->GetTimeSansCfd();
            PSstruct.subtype = (*it)->GetChanID().GetSubtype();
            PSstruct.tag = (*it)->GetChanID().GetGroup();
            pixie_tree_event_->pspmt_vec_.emplace_back(PSstruct);
            PSstruct = processor_struct::PSPMT_DEFAULT_STRUCT;
        }

        if (energy < threshold_)
            continue;
        //parcel out position signals by tag
        if ((*it)->GetChanID().GetGroup() == "xa" && xa_l == 0) {
            xa_l = energy;
            lowAnodeSum += energy;
        }
        if ((*it)->GetChanID().GetGroup() == "xb" && xb_l == 0) {
            xb_l = energy;
            lowAnodeSum += energy;
        }
        if ((*it)->GetChanID().GetGroup() == "ya" && ya_l == 0) {
            ya_l = energy;
            lowAnodeSum += energy;
        }
        if ((*it)->GetChanID().GetGroup() == "yb" && yb_l == 0) {
            yb_l = energy;
            lowAnodeSum += energy;
        }
    }


    double highAnodeSum = 0;
    for (auto it = hiAnode.begin(); it != hiAnode.end(); it++) {

        if (DetectorDriver::get()->GetSysRootOutput()) {
            PSstruct.energy = (*it)->GetCalibratedEnergy();
            PSstruct.time = (*it)->GetTimeSansCfd();
            PSstruct.subtype = (*it)->GetChanID().GetSubtype();
            PSstruct.tag = (*it)->GetChanID().GetGroup();
            pixie_tree_event_->pspmt_vec_.emplace_back(PSstruct);
            PSstruct = processor_struct::PSPMT_DEFAULT_STRUCT;
        }

        //check signals energy vs threshold
        energy = (*it)->GetCalibratedEnergy();
        if (energy < threshold_ || energy > 63000)
            continue;
        //parcel out position signals by tag
        if ((*it)->GetChanID().GetGroup() == "xa" && xa_h == 0){
            xa_h = energy;
            highAnodeSum += energy;
        }
        if ((*it)->GetChanID().GetGroup() == "xb" && xb_h == 0){
            xb_h = energy;
            highAnodeSum += energy;
        }
        if ((*it)->GetChanID().GetGroup() == "ya" && ya_h == 0){
            ya_h = energy;
            highAnodeSum += energy;
        }
        if ((*it)->GetChanID().GetGroup() == "yb" && yb_h == 0){
            yb_h = energy;
            highAnodeSum += energy;
        }
    }
*/
    //compute position only if all 4 signals are present
    if (xa_l > 0 && xb_l > 0 && ya_l > 0 && yb_l > 0){
        hasPosition_low = true;
        position_low.first = CalculatePosition(xa_l, xb_l, ya_l, yb_l, vdtype_, rotation_).first;
        position_low.second  = CalculatePosition(xa_l, xb_l, ya_l, yb_l, vdtype_, rotation_).second;
        plot(DD_POS_LOW, position_low.first * positionScale_ + positionOffset_,
             position_low.second * positionScale_ + positionOffset_);
    }

    if (xa_h > 0 && xb_h > 0 && ya_h > 0 && yb_h > 0){
        hasPosition_high = true;
        position_high.first = CalculatePosition(xa_h, xb_h, ya_h, yb_h, vdtype_, rotation_).first;
        position_high.second = CalculatePosition(xa_h, xb_h, ya_h, yb_h, vdtype_, rotation_).second;
        plot(DD_POS_HIGH, position_high.first * positionScale_ + positionOffset_,
             position_high.second * positionScale_ + positionOffset_ );
    }

    //---------------VETO LOOP------------------------------------------------
    int numOfVetoChans = (int) (DetectorLibrary::get()->GetLocations("pspmt", "veto")).size();

    for(auto it = veto.begin(); it != veto.end(); it++){
        int loc = (*it)->GetChanID().GetLocation();
        plot(DD_PLASTIC_EN, (*it)->GetCalibratedEnergy(), loc);
        if ((*it)->GetCalibratedEnergy() > 1 && (*it)->GetCalibratedEnergy() < 10000){
            hasVeto = true;
        }

        if (DetectorDriver::get()->GetSysRootOutput()) {
            PSstruct.energy = (*it)->GetCalibratedEnergy();
            PSstruct.time = (*it)->GetTimeSansCfd();
            PSstruct.subtype = (*it)->GetChanID().GetSubtype();
            PSstruct.tag = (*it)->GetChanID().GetGroup();
            pixie_tree_event_->pspmt_vec_.emplace_back(PSstruct);
            PSstruct = processor_struct::PSPMT_DEFAULT_STRUCT;
        }
    }

    //------------Positions from ion scintillator---------------------------------
        //using top - bottom and left - right computation scheme

    for(auto it = ionTrig.begin(); it != ionTrig.end(); it++){
        //check signals energy vs threshold

        if (DetectorDriver::get()->GetSysRootOutput()) {
            PSstruct.energy = (*it)->GetCalibratedEnergy();
            PSstruct.time = (*it)->GetTimeSansCfd();
            PSstruct.subtype = (*it)->GetChanID().GetSubtype();
            PSstruct.tag = (*it)->GetChanID().GetGroup();
            pixie_tree_event_->pspmt_vec_.emplace_back(PSstruct);
            PSstruct = processor_struct::PSPMT_DEFAULT_STRUCT;
        }
        energy = (*it)->GetCalibratedEnergy();
        if (energy < 10)
            continue;

        // damm plotting of energies
        int loc = (*it)->GetChanID().GetLocation();
        plot(DD_PLASTIC_EN, (*it)->GetCalibratedEnergy(), loc + numOfVetoChans + 1); //max veto chan +1 for readablility

        //parcel out position signals by tag
        if ((*it)->GetChanID().GetGroup() == "black" && top_l == 0 )
            top_l = energy;
        if ((*it)->GetChanID().GetGroup() == "blue" && top_r == 0 )
            top_r = energy;
        if ((*it)->GetChanID().GetGroup() == "white" && bottom_l == 0 )
            bottom_l = energy;
        if ((*it)->GetChanID().GetGroup() == "green" && bottom_r == 0 )
            bottom_r = energy;


    }

    if (top_l > 0 && top_r > 0 && bottom_l > 0 && bottom_r > 0){
        hasPosition_ion = true;
        position_ion.first = (top_l + bottom_l - top_r - bottom_r) / (top_l + top_r + bottom_l + bottom_r);
        position_ion.second  = (top_l + top_r - bottom_l - bottom_r) / (top_l + top_r + bottom_l + bottom_r);
        plot(DD_POS_ION, position_ion.first * front_positionScale_ + front_positionOffset_,
             position_ion.second * front_positionScale_ + front_positionOffset_);
    }

    //----------------------------------------------------------------------------
    //------------Check Transmission efficiencies---------------------------------

        //check for valid upstream events, dE silicon events, and vetos for gating
    for(auto it = separatorScint.begin(); it != separatorScint.end(); it++){
        if (DetectorDriver::get()->GetSysRootOutput()) {
            PSstruct.energy = (*it)->GetCalibratedEnergy();
            PSstruct.time = (*it)->GetTimeSansCfd();
            PSstruct.subtype = (*it)->GetChanID().GetSubtype();
            PSstruct.tag = (*it)->GetChanID().GetGroup();
            pixie_tree_event_->pspmt_vec_.emplace_back(PSstruct);
            PSstruct = processor_struct::PSPMT_DEFAULT_STRUCT;
        }
        if ((*it)->GetCalibratedEnergy() > 1 && (*it)->GetCalibratedEnergy() < 10000){
            hasUpstream = true;
        }
    }

    for (auto it = desi.begin(); it != desi.end(); it++){
        if (DetectorDriver::get()->GetSysRootOutput()) {
            PSstruct.energy = (*it)->GetCalibratedEnergy();
            PSstruct.time = (*it)->GetTimeSansCfd();
            PSstruct.subtype = (*it)->GetChanID().GetSubtype();
            PSstruct.tag = (*it)->GetChanID().GetGroup();
            pixie_tree_event_->pspmt_vec_.emplace_back(PSstruct);
            PSstruct = processor_struct::PSPMT_DEFAULT_STRUCT;
        }
        if((*it)->GetCalibratedEnergy() > 1 && (*it)->GetCalibratedEnergy() < 10000){
            hasDeSi = true;
        }
    }


    //Begin plotting

        //plot valid YSO positions and dE silicon events gated on upstream events
        //plot upstream events gated on dE silicon
        //plot transmission efficiency from upstream to YSO and veto

    if(hasUpstream) {
        for(auto de_it = desi.begin(); de_it != desi.end(); de_it++) {
            plot(D_DESI_ENERGY,(*de_it)->GetCalibratedEnergy());
        }
        if(hasPosition_low){
            plot(DD_SEPAR_GATED_LOW, position_low.first * positionScale_ + positionOffset_,
                    position_low.second * positionScale_ + positionOffset_);
        }
        if(hasPosition_ion){
            plot(DD_SEPAR_GATED_ION, position_ion.first * positionScale_ + positionOffset_,
                    position_ion.second * positionScale_ + positionOffset_);
        }
    }

    if(hasDeSi) {
        for (auto it_sep = separatorScint.begin(); it_sep != separatorScint.end(); it_sep++) {
            if ((*it_sep)->GetChanID().GetGroup() =="left") {
                plot(DD_SEPAR_ENERGY, (*it_sep)->GetCalibratedEnergy(), 0);
            } else if ((*it_sep)->GetChanID().GetGroup() == "right") {
                plot(DD_SEPAR_ENERGY, (*it_sep)->GetCalibratedEnergy(), 1);
            }
        }

        if (hasPosition_low) {
            plot(DD_DESI_GATED_LOW, position_low.first * positionScale_ + positionOffset_,
                 position_low.second * positionScale_ + positionOffset_);
        }
        if (hasPosition_ion) {
            plot(DD_DESI_GATED_ION, position_ion.first * positionScale_ + positionOffset_,
                 position_ion.second * positionScale_ + positionOffset_);
        }
    }

    if(hasPosition_low) {
        for (auto de_it = desi.begin(); de_it != desi.end(); de_it++) {
            plot(D_DESI_YSO_GATED, (*de_it)->GetCalibratedEnergy());
        }
        for (auto it_sep = separatorScint.begin(); it_sep != separatorScint.end(); it_sep++) {
            if ((*it_sep)->GetChanID().GetGroup() =="left") {
                plot(DD_SEPAR_YSO_GATED, (*it_sep)->GetCalibratedEnergy(), 0);
            } else if ((*it_sep)->GetChanID().GetGroup() =="right") {
                plot(DD_SEPAR_YSO_GATED, (*it_sep)->GetCalibratedEnergy(), 1);
            }
        }
    }

    if(hasUpstream)
        plot(D_TRANS_EFF_YSO, 0);
    if(hasUpstream && hasPosition_ion)
        plot(D_TRANS_EFF_YSO, 1);
    if(hasUpstream && hasPosition_low)
        plot(D_TRANS_EFF_YSO, 2);
    if (hasUpstream && hasVeto)
        plot(D_TRANS_EFF_YSO, 3);



    if (!lowDynode.empty())
        plot(DD_DY_SUM_LG,lowDynode.front()->GetCalibratedEnergy(),lowAnodeSum);

    if (!hiDynode.empty())
        plot(DD_DY_SUM_HG,hiDynode.front()->GetCalibratedEnergy(),highAnodeSum);

         plot(DD_DYNODE_QDC, (*it)->GetTrace().GetQdc(), 0);
           plot(DD_DYNODE_QDC, (*it)->GetTrace().GetQdc(), 1);


    EndProcess();
    return true;

}

