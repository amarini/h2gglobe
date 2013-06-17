#ifndef __DumpAnalysis__
#define __DumpAnalysis__

#include "BaseAnalysis.h"
#include "BaseSmearer.h"
#include "PhotonAnalysis/interface/MassFactorizedMvaAnalysis.h"
#include "RooContainer.h"
#include "VertexAnalysis/interface/HggVertexAnalyzer.h"

#include "EnergySmearer.h"
#include "EfficiencySmearer.h"
#include "DiPhoEfficiencySmearer.h"
#include "KFactorSmearer.h"
#include <iostream>
#include <fstream>
#include "math.h"

class TreeVariablesDump {

public:
    
    TreeVariablesDump();

    int entry;
    int   nPU;
    float weight;
    float sampleweight;
    
    //int   jet1, jet2, jet3;
    float diphomva;
    float pho1pt;
    float pho2pt;
    float diphopt;
    float diphoM;
    float diphoEta;
   // float dijetEta;
   // float jet1isMatched,jet2isMatched;
   // float jet1genPt,jet2genPt;
   // float jet1genDr,jet2genDr;
   // //float jet1Pt, jet2Pt, jet1Eta, jet2Eta, zepp, mj1j2, dphi, dphiJJ, dphiJJ2, deltaEta3;
   // bool  jet1PileupID,jet2PileupID ;
    bool  isSignal;
    int   mctype;

    float pho1energy;
    float pho2energy;
    float pho1Phi;
    float pho2Phi;
    float pho1Eta;
    float pho2Eta;
    float pho1scEta;
    float pho2scEta;
    float pho1r9;
    float pho2r9;
    float pho1idMva;
    float pho2idMva;
    float pho1sE;
    float pho2sE;
    float pho1sEsmear;
    float pho2sEsmear;
    float diphosM;
    float diphosMwv;
    float diphovtxProb;
    bool pho1Matched, pho2Matched, corrVeretx;
    int pho1CiC, pho2CiC;
    float diphoMVA;
    
    //Photon mva informations   
   // float pho1r9; float pho2r9;
    float pho1sieie; float pho2sieie;
    float pho1scetawidth; float pho2scetawidth;
    float pho1scphiwidth; float pho2scphiwidth;
    float pho1sieip; float pho2sieip;
    float pho1s4ratio; float pho2s4ratio;
    float pho1pfphotoniso03; float pho2pfphotoniso03;
    float pho1pfchargedisogood03; float pho2pfchargedisogood03;
    float pho1pfchargedisobad03; float pho2pfchargedisobad03;
    float pho1sceta; float pho2sceta;
    float pho1hoe; float pho2hoe;
    float rho;
    //Nikolas variables
    float pho1r9_Ethresh; float pho2r9_Ethresh;
    float pho1sieie_Ethresh; float pho2sieie_Ethresh;
    float pho1r9_chi2Thresh; float pho2r9_chi2Thresh;
    float pho1sieie_chi2Thresh; float pho2sieie_chi2Thresh;
    float pho1pfiso_cleanphoton03; float pho2pfiso_cleanphoton03;
    float pho1pfiso_cleanneutral03; float pho2pfiso_cleanneutral03;
    float pho1pfiso_cleancharged03; float pho2pfiso_cleancharged03;
    float pho1pfiso_cleanphoton04; float pho2pfiso_cleanphoton04;
    float pho1pfiso_cleanneutral04; float pho2pfiso_cleanneutral04;
    float pho1pfiso_cleancharged04; float pho2pfiso_cleancharged04;
    
};

// ------------------------------------------------------------------------------------
class DumpAnalysis : public MassFactorizedMvaAnalysis 
{
 public:
    
    DumpAnalysis();
    virtual ~DumpAnalysis();
    
    virtual const std::string & name() const { return name_; };
    
    // LoopAll analysis interface implementation
    void Init(LoopAll&);
    void Term(LoopAll&);
    
    void FillReductionVariables(LoopAll& l, int jentry);   
    void ReducedOutputTree(LoopAll &l, TTree * outputTree);
    bool SelectEventsReduction(LoopAll&, int);

    bool AnalyseEvent(LoopAll& l, Int_t jentry, float weight, TLorentzVector & gP4, float & mass, float & evweight, int & category, 
		      int & diphoton_id,
		      bool & isCorrectVertex,
		      float &kinematic_bdtout,
		      bool isSyst=false, 
		      float syst_shift=0., bool skipSelection=false,
		      BaseGenLevelSmearer *genSys=0, BaseSmearer *phoSys=0, BaseDiPhotonSmearer * diPhoSys=0); 

    
    bool recomputeJetId, expoMatching, dumpFlatTree, requireTwoJets;
    
    
private:
    TFile * outputFile_;
    TTree * flatTree_;
    int _nVertices;
    TreeVariablesDump tree_, default_;

};

#endif


// Local Variables:
// mode: c++
// c-basic-offset: 4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
