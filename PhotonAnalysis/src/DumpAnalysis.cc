#include "../interface/DumpAnalysis.h"

//#include "../../JetAnalysis/interface/JetHandler.h"

#include "Sorters.h"
#include "PhotonReducedInfo.h"
#include <iostream>
#include <algorithm>

//#include "CMGTools/External/interface/PileupJetIdentifier.h"

#define PADEBUG 0 

using namespace std;

// ----------------------------------------------------------------------------------------------------
TreeVariablesDump::TreeVariablesDump() : 
    entry(0),		
    weight(0),		
    sampleweight(0),		
    pho1pt(0),		
    pho2pt(0),		
    diphopt(0),		
    diphoM(0),		
    diphoEta(999),	
   // dijetEta(999),	
   // jet1isMatched(false),	
   // jet2isMatched(false),	
   // jet1genPt(0),	
   // jet2genPt(0),	
   // jet1genDr(0),	
   // jet2genDr(0),	
   // jet1Pt(0),		
   // jet2Pt(0),		
   // jet1Eta(999),		
   // jet2Eta(999),		
  //  zepp(999),		
  //  mj1j2(-999),		
  //  dphi(999),		
  //  dphiJJ(999),		
  //  dphiJJ2(999),		
  //  deltaEta3(999),	
   // jet1PileupID(0),	
   // jet2PileupID(0),	
    isSignal(false),	
    mctype(0),		
    diphomva(-999),	
    pho1Eta(999),		
    pho2Eta(999),		
    pho1Phi(999),		
    pho2Phi(999),		
    pho1scEta(999),		
    pho2scEta(999),		
    pho1r9(999),		
    pho2r9(999),		
    pho1idMva(-999),	
    pho2idMva(-999),	
    pho1sE(999),	
    pho2sE(999),	
    pho1sEsmear(999),	
    pho2sEsmear(999),	
    diphosM(999),	
    diphosMwv(999),	
    diphovtxProb(-1),
   // jet1(-1),
   // jet2(-1),
   // jet3(-1),
    pho1Matched(false), pho2Matched(false),corrVeretx(false),
    pho1CiC(-1),pho2CiC(-1), diphoMVA(-999.),
    //Photon mva informations   
     pho1sieie(999),  pho2sieie(999),
     pho1scetawidth(999),  pho2scetawidth(999),
     pho1scphiwidth(999),  pho2scphiwidth(999),
     pho1sieip(999),  pho2sieip(999),
     pho1s4ratio(999),  pho2s4ratio(999),
     pho1pfphotoniso03(999),  pho2pfphotoniso03(999),
     pho1pfchargedisogood03(999),  pho2pfchargedisogood03(999),
     pho1pfchargedisobad03(999),  pho2pfchargedisobad03(999),
     pho1sceta(999),  pho2sceta(999),
     rho(999),
    //Nikolas variables
     pho1r9_Ethresh(999),  pho2r9_Ethresh(999),
     pho1sieie_Ethresh(999),  pho2sieie_Ethresh(999),
     pho1r9_chi2Thresh(999),  pho2r9_chi2Thresh(999),
     pho1sieie_chi2Thresh(999),  pho2sieie_chi2Thresh(999),
     pho1pfiso_cleanphoton03(999),  pho2pfiso_cleanphoton03(999),
     pho1pfiso_cleanneutral03(999),  pho2pfiso_cleanneutral03(999),
     pho1pfiso_cleancharged03(999),  pho2pfiso_cleancharged03(999),
     pho1pfiso_cleanphoton04(999),  pho2pfiso_cleanphoton04(999),
     pho1pfiso_cleanneutral04(999),  pho2pfiso_cleanneutral04(999),
     pho1pfiso_cleancharged04(999),  pho2pfiso_cleancharged04(999)
{}

// ----------------------------------------------------------------------------------------------------
DumpAnalysis::DumpAnalysis()  
{
    name_ = "DumpAnalysis";

    recomputeJetId = false;
    expoMatching   = false;
    dumpFlatTree   = false;
    requireTwoJets = false;
    
    flatTree_ = 0;
    outputFile_ = 0;
}

// ----------------------------------------------------------------------------------------------------
DumpAnalysis::~DumpAnalysis() 
{
}

// ----------------------------------------------------------------------------------------------------
void DumpAnalysis::Term(LoopAll& l) 
{
    if( dumpFlatTree ) {
	//// if( outputFile_ ) {
	////     outputFile_->cd();
	//// } else {
	////     l.outputFile->cd();
	//// }
	//// flatTree_->Write();
	//// if( outputFile_ ) {
	////     outputFile_->Close();
	//// }
    }
}

// ----------------------------------------------------------------------------------------------------
void DumpAnalysis::Init(LoopAll& l) 
{  
    if( l.runZeeValidation ) {
	leadEtCut = 15;
	subleadEtCut = 15;
	leadEtVBFCut = 15.;
	subleadEtVBFCut = 15.;
	massMin = 60, massMax = 120.;
	applyPtoverM = false;
    }
    

    MassFactorizedMvaAnalysis::Init(l);

    if( dumpFlatTree ) {
	if( flatTree_ == 0 ) { 
	    //// outputFile_ = TFile::Open("DumpAnalysisTree_"+l.histFileName,"recreate");
	    //// flatTree_ = new TTree("flatTree","flatTree");
	    l.InitTrees("DumpAnalysis");
	    tree_.entry = 0;
	}
	
	l.BookExternalTreeBranch( "entry",         &tree_.entry, "DumpAnalysis" );         
	l.BookExternalTreeBranch( "weight",        &tree_.weight, "DumpAnalysis" );         
	l.BookExternalTreeBranch( "sampleweight",  &tree_.sampleweight, "DumpAnalysis" );         
	l.BookExternalTreeBranch( "pho1pt",        &tree_.pho1pt, "DumpAnalysis" );        
	l.BookExternalTreeBranch( "pho2pt",        &tree_.pho2pt, "DumpAnalysis" );        
	l.BookExternalTreeBranch( "diphopt",       &tree_.diphopt, "DumpAnalysis" );       
	l.BookExternalTreeBranch( "diphoM",        &tree_.diphoM, "DumpAnalysis" );        
	l.BookExternalTreeBranch( "diphoEta",      &tree_.diphoEta, "DumpAnalysis" );      
//	l.BookExternalTreeBranch( "dijetEta",      &tree_.dijetEta, "DumpAnalysis" );      
//	l.BookExternalTreeBranch( "jet1",          &tree_.jet1, "DumpAnalysis" ); 
//	l.BookExternalTreeBranch( "jet2",          &tree_.jet2, "DumpAnalysis" ); 
//	l.BookExternalTreeBranch( "jet3",          &tree_.jet3, "DumpAnalysis" ); 
//	l.BookExternalTreeBranch( "jet1isMatched", &tree_.jet1isMatched, "DumpAnalysis" ); 
//	l.BookExternalTreeBranch( "jet2isMatched", &tree_.jet2isMatched, "DumpAnalysis" ); 
//	l.BookExternalTreeBranch( "jet1genPt",     &tree_.jet1genPt, "DumpAnalysis" );     
//	l.BookExternalTreeBranch( "jet2genPt",     &tree_.jet2genPt, "DumpAnalysis" );     
//	l.BookExternalTreeBranch( "jet1genDr",     &tree_.jet1genDr, "DumpAnalysis" );     
//	l.BookExternalTreeBranch( "jet2genDr",     &tree_.jet2genDr, "DumpAnalysis" );     
//	l.BookExternalTreeBranch( "jet1Pt",        &tree_.jet1Pt, "DumpAnalysis" );        
//	l.BookExternalTreeBranch( "jet2Pt",        &tree_.jet2Pt, "DumpAnalysis" );        
//	l.BookExternalTreeBranch( "jet1Eta",       &tree_.jet1Eta, "DumpAnalysis" );       
//	l.BookExternalTreeBranch( "jet2Eta",       &tree_.jet2Eta, "DumpAnalysis" );       
//	l.BookExternalTreeBranch( "zepp",          &tree_.zepp, "DumpAnalysis" );          
//	l.BookExternalTreeBranch( "mj1j2",         &tree_.mj1j2, "DumpAnalysis" );         
//	l.BookExternalTreeBranch( "dphi",          &tree_.dphi, "DumpAnalysis" );          
//	l.BookExternalTreeBranch( "dphiJJ",        &tree_.dphiJJ, "DumpAnalysis" );        
//	l.BookExternalTreeBranch( "dphiJJ2",       &tree_.dphiJJ2, "DumpAnalysis" );       
//	l.BookExternalTreeBranch( "deltaEta3",     &tree_.deltaEta3, "DumpAnalysis" );     
//	l.BookExternalTreeBranch( "jet1PileupID",  &tree_.jet1PileupID, "DumpAnalysis" );  
//	l.BookExternalTreeBranch( "jet2PileupID",  &tree_.jet2PileupID, "DumpAnalysis" );  
	l.BookExternalTreeBranch( "isSignal",      &tree_.isSignal, "DumpAnalysis" );      
	l.BookExternalTreeBranch( "mctype",        &tree_.mctype, "DumpAnalysis" );        
	l.BookExternalTreeBranch( "diphomva",      &tree_.diphomva, "DumpAnalysis" );      
	l.BookExternalTreeBranch( "pho1energy",       &tree_.pho1energy, "DumpAnalysis" );       
	l.BookExternalTreeBranch( "pho2energy",       &tree_.pho2energy, "DumpAnalysis" );       
	l.BookExternalTreeBranch( "pho1Eta",       &tree_.pho1Eta, "DumpAnalysis" );       
	l.BookExternalTreeBranch( "pho2Eta",       &tree_.pho2Eta, "DumpAnalysis" );       
	l.BookExternalTreeBranch( "pho1Phi",       &tree_.pho1Phi, "DumpAnalysis" );       
	l.BookExternalTreeBranch( "pho2Phi",       &tree_.pho2Phi, "DumpAnalysis" );       
	l.BookExternalTreeBranch( "pho1scEta",       &tree_.pho1scEta, "DumpAnalysis" );       
	l.BookExternalTreeBranch( "pho2scEta",       &tree_.pho2scEta, "DumpAnalysis" );       
	l.BookExternalTreeBranch( "pho1r9",        &tree_.pho1r9, "DumpAnalysis" );        
	l.BookExternalTreeBranch( "pho2r9",        &tree_.pho2r9, "DumpAnalysis" );        
	l.BookExternalTreeBranch( "pho1idMva",     &tree_.pho1idMva, "DumpAnalysis" );    
	l.BookExternalTreeBranch( "pho2idMva",     &tree_.pho2idMva, "DumpAnalysis" );    
	l.BookExternalTreeBranch( "pho1sE",   &tree_.pho1sE, "DumpAnalysis" );   
	l.BookExternalTreeBranch( "pho2sE",   &tree_.pho2sE, "DumpAnalysis" );   
	l.BookExternalTreeBranch( "pho1sEsmear",   &tree_.pho1sEsmear, "DumpAnalysis" );   
	l.BookExternalTreeBranch( "pho2sEsmear",   &tree_.pho2sEsmear, "DumpAnalysis" );   
	l.BookExternalTreeBranch( "diphosM",  &tree_.diphosM, "DumpAnalysis" );  
	l.BookExternalTreeBranch( "diphosMwv",&tree_.diphosMwv, "DumpAnalysis" );
	l.BookExternalTreeBranch( "diphovtxProb",  &tree_.diphovtxProb, "DumpAnalysis" );  
	l.BookExternalTreeBranch( "pho1Matched",  &tree_.pho1Matched, "DumpAnalysis" );  
	l.BookExternalTreeBranch( "pho2Matched",  &tree_.pho2Matched, "DumpAnalysis" );  
	l.BookExternalTreeBranch( "corrVeretx",  &tree_.corrVeretx, "DumpAnalysis" );  
	l.BookExternalTreeBranch( "pho1CiC",  &tree_.pho1CiC, "DumpAnalysis" );  
	l.BookExternalTreeBranch( "pho2CiC",  &tree_.pho2CiC, "DumpAnalysis" );  
	l.BookExternalTreeBranch( "diphoMVA",  &tree_.diphoMVA, "DumpAnalysis" );  
    //Photon mva informations   
        l.BookExternalTreeBranch("pho1sieie",&tree_.pho1sieie             ,"DumpAnalysis");
        l.BookExternalTreeBranch("pho2sieie",&tree_.pho2sieie             ,"DumpAnalysis");
        l.BookExternalTreeBranch("pho1scetawidth",&tree_.pho1scetawidth        ,"DumpAnalysis");
        l.BookExternalTreeBranch("pho2scetawidth",&tree_.pho2scetawidth        ,"DumpAnalysis");
        l.BookExternalTreeBranch("pho1scphiwidth",&tree_.pho1scphiwidth        ,"DumpAnalysis");
        l.BookExternalTreeBranch("pho2scphiwidth",&tree_.pho2scphiwidth        ,"DumpAnalysis");
        l.BookExternalTreeBranch("pho1sieip",&tree_.pho1sieip             ,"DumpAnalysis");
        l.BookExternalTreeBranch("pho2sieip",&tree_.pho2sieip             ,"DumpAnalysis");
        l.BookExternalTreeBranch("pho1s4ratio",&tree_.pho1s4ratio           ,"DumpAnalysis");
        l.BookExternalTreeBranch("pho2s4ratio",&tree_.pho2s4ratio           ,"DumpAnalysis");
        l.BookExternalTreeBranch("pho1pfphotoniso03",&tree_.pho1pfphotoniso03     ,"DumpAnalysis");
        l.BookExternalTreeBranch("pho2pfphotoniso03",&tree_.pho2pfphotoniso03     ,"DumpAnalysis");
        l.BookExternalTreeBranch("pho1pfchargedisogood03",&tree_.pho1pfchargedisogood03,"DumpAnalysis");
        l.BookExternalTreeBranch("pho2pfchargedisogood03",&tree_.pho2pfchargedisogood03,"DumpAnalysis");
        l.BookExternalTreeBranch("pho1pfchargedisobad03",&tree_.pho1pfchargedisobad03 ,"DumpAnalysis");
        l.BookExternalTreeBranch("pho2pfchargedisobad03",&tree_.pho2pfchargedisobad03 ,"DumpAnalysis");
        l.BookExternalTreeBranch("pho1sceta",&tree_.pho1sceta             ,"DumpAnalysis");
        l.BookExternalTreeBranch("pho2sceta",&tree_.pho2sceta             ,"DumpAnalysis");
        l.BookExternalTreeBranch("rho",&tree_.rho                   ,"DumpAnalysis");
		//Nikolas variables
        l.BookExternalTreeBranch("pho1r9_Ethresh",&tree_.pho1r9_Ethresh          ,"DumpAnalysis");
        l.BookExternalTreeBranch("pho2r9_Ethresh",&tree_.pho2r9_Ethresh          ,"DumpAnalysis");
        l.BookExternalTreeBranch("pho1sieie_Ethresh",&tree_.pho1sieie_Ethresh       ,"DumpAnalysis");
        l.BookExternalTreeBranch("pho2sieie_Ethresh",&tree_.pho2sieie_Ethresh       ,"DumpAnalysis");
        l.BookExternalTreeBranch("pho1r9_chi2Thresh",&tree_.pho1r9_chi2Thresh       ,"DumpAnalysis");
        l.BookExternalTreeBranch("pho2r9_chi2Thresh",&tree_.pho2r9_chi2Thresh       ,"DumpAnalysis");
        l.BookExternalTreeBranch("pho1sieie_chi2Thresh",&tree_.pho1sieie_chi2Thresh    ,"DumpAnalysis");
        l.BookExternalTreeBranch("pho2sieie_chi2Thresh",&tree_.pho2sieie_chi2Thresh    ,"DumpAnalysis");
        l.BookExternalTreeBranch("pho1pfiso_cleanphoton03",&tree_.pho1pfiso_cleanphoton03 ,"DumpAnalysis");
        l.BookExternalTreeBranch("pho2pfiso_cleanphoton03",&tree_.pho2pfiso_cleanphoton03 ,"DumpAnalysis");
        l.BookExternalTreeBranch("pho1pfiso_cleanneutral03",&tree_.pho1pfiso_cleanneutral03,"DumpAnalysis");
        l.BookExternalTreeBranch("pho2pfiso_cleanneutral03",&tree_.pho2pfiso_cleanneutral03,"DumpAnalysis");
        l.BookExternalTreeBranch("pho1pfiso_cleancharged03",&tree_.pho1pfiso_cleancharged03,"DumpAnalysis");
        l.BookExternalTreeBranch("pho2pfiso_cleancharged03",&tree_.pho2pfiso_cleancharged03,"DumpAnalysis");
        l.BookExternalTreeBranch("pho1pfiso_cleanphoton04",&tree_.pho1pfiso_cleanphoton04 ,"DumpAnalysis");
        l.BookExternalTreeBranch("pho2pfiso_cleanphoton04",&tree_.pho2pfiso_cleanphoton04 ,"DumpAnalysis");
        l.BookExternalTreeBranch("pho1pfiso_cleanneutral04",&tree_.pho1pfiso_cleanneutral04,"DumpAnalysis");
        l.BookExternalTreeBranch("pho2pfiso_cleanneutral04",&tree_.pho2pfiso_cleanneutral04,"DumpAnalysis");
        l.BookExternalTreeBranch("pho1pfiso_cleancharged04",&tree_.pho1pfiso_cleancharged04,"DumpAnalysis");
        l.BookExternalTreeBranch("pho2pfiso_cleancharged04",&tree_.pho2pfiso_cleancharged04,"DumpAnalysis");
   }
}

// ----------------------------------------------------------------------------------------------------
void DumpAnalysis::ReducedOutputTree(LoopAll &l, TTree * outputTree) 
{
    /// dumpFlatTree=true;
    /// flatTree_ = new TTree("flatTree","flatTree");
}

// ----------------------------------------------------------------------------------------------------
void DumpAnalysis::FillReductionVariables(LoopAll& l, int jentry)
{
}
   
// ----------------------------------------------------------------------------------------------------
bool DumpAnalysis::SelectEventsReduction(LoopAll&, int)
{
    return true;
}

//void switchJetIdVertex(LoopAll &l, int ivtx) ;

// ----------------------------------------------------------------------------------------------------
bool DumpAnalysis::AnalyseEvent(LoopAll& l, Int_t jentry, float weight, TLorentzVector & gP4, float & mass, float & evweight, 
				 int & category, int & diphoton_id,
				 bool & isCorrectVertex,
				 float &kinematic_bdtout,
				 bool isSyst, 
				 float syst_shift, bool skipSelection,
				 BaseGenLevelSmearer *genSys, BaseSmearer *phoSys, BaseDiPhotonSmearer * diPhoSys)
{
    assert( isSyst || ! skipSelection );
    
    int cur_type = l.itype[l.current];
    /// diphoton_id = -1;
    
    std::pair<int,int> diphoton_index;
   
    // do gen-level dependent first (e.g. k-factor); only for signal
    genLevWeight=1.;
    if(cur_type!=0 ) {
	applyGenLevelSmearings(genLevWeight,gP4,l.pu_n,cur_type,genSys,syst_shift);
    }

    // event selection
    if( ! skipSelection ) {
	
	// first apply corrections and smearing on the single photons 
	smeared_pho_energy.clear(); smeared_pho_energy.resize(l.pho_n,0.); 
	smeared_pho_r9.clear();     smeared_pho_r9.resize(l.pho_n,0.); 
	smeared_pho_weight.clear(); smeared_pho_weight.resize(l.pho_n,1.);
	applySinglePhotonSmearings(smeared_pho_energy, smeared_pho_r9, smeared_pho_weight, cur_type, l, energyCorrected, energyCorrectedError,
				   phoSys, syst_shift);

	// inclusive category di-photon selection
	// FIXME pass smeared R9
	diphoton_id = l.DiphotonMITPreSelection(leadEtCut,subleadEtCut,phoidMvaCut,applyPtoverM, &smeared_pho_energy[0] ); ///??? serve ???
    	
	// Exclusive Modes
	int diphotonVBF_id = -1;
	int diphotonVHhad_id = -1;
	int diphotonVHlep_id = -1;
	VHmuevent = false;
	VHelevent = false;
	VBFevent = false;
	VHhadevent = false;
	
	//// // preselection 
	//// diphotonVBF_id = l.DiphotonMITPreSelection(leadEtVBFCut,subleadEtVBFCut,phoidMvaCut,applyPtoverM, &smeared_pho_energy[0] );
	//// diphoton_id = diphotonVBF_id; 
	
	//if( diphoton_id == -1 ) { return false; }
	
	/// l.RescaleJetEnergy();
	/// postProcessJets(l,l.dipho_vtxind[diphoton_id]);
		
	TLorentzVector lead_p4, sublead_p4, Higgs;
	float lead_r9, sublead_r9;
	TVector3 * vtx;
	category = 0;
	fillDiphoton(lead_p4, sublead_p4, Higgs, lead_r9, sublead_r9, vtx, &smeared_pho_energy[0], l, diphoton_id);  
	if( Higgs.M() < massMin || Higgs.M() > massMax )  { return false; }
	
	
	// ---- evaluate dipho MVA
	diphoton_index = std::make_pair( l.dipho_leadind[diphoton_id],  l.dipho_subleadind[diphoton_id] );
	evweight = weight * smeared_pho_weight[diphoton_index.first] * smeared_pho_weight[diphoton_index.second] * genLevWeight;
	
        // Mass Resolution of the Event
        massResolutionCalculator->Setup(l,&photonInfoCollection[diphoton_index.first],&photonInfoCollection[diphoton_index.second],diphoton_id,eSmearPars,nR9Categories,nEtaCategories,beamspotSigma);
        float vtx_mva  = l.vtx_std_evt_mva->at(diphoton_id);
        sigmaMrv = massResolutionCalculator->massResolutionEonly();
        sigmaMwv = massResolutionCalculator->massResolutionWrongVtx();
        float sigmaMeonly = massResolutionCalculator->massResolutionEonly();
        // easy to calculate vertex probability from vtx mva output
        float vtxProb   = 1.-0.49*(vtx_mva+1.0); 

        float phoid_mvaout_lead = ( dataIs2011 ? 
				    l.photonIDMVA(diphoton_index.first,l.dipho_vtxind[diphoton_id],
						  lead_p4,bdtTrainingPhilosophy.c_str()) :
				    l.photonIDMVANew(diphoton_index.first,l.dipho_vtxind[diphoton_id],
						     lead_p4,bdtTrainingPhilosophy.c_str()) );
        float phoid_mvaout_sublead = ( dataIs2011 ? 
				       l.photonIDMVA(diphoton_index.second,l.dipho_vtxind[diphoton_id],
						     sublead_p4,bdtTrainingPhilosophy.c_str()) : 
				       l.photonIDMVANew(diphoton_index.second,l.dipho_vtxind[diphoton_id],
							sublead_p4,bdtTrainingPhilosophy.c_str()) );
	// apply di-photon level smearings and corrections
        int selectioncategory = l.DiphotonCategory(diphoton_index.first,diphoton_index.second,Higgs.Pt(),nEtaCategories,nR9Categories,0);
        if( cur_type != 0 && doMCSmearing ) {
	    applyDiPhotonSmearings(Higgs, *vtx, selectioncategory, cur_type, *((TVector3*)l.gv_pos->At(0)), evweight, 
				   phoid_mvaout_lead,phoid_mvaout_sublead,
				   diPhoSys, syst_shift);
            isCorrectVertex=(*vtx- *((TVector3*)l.gv_pos->At(0))).Mag() < 1.;
        }

	float diphobdt_output = l.diphotonMVA(diphoton_index.first,diphoton_index.second,l.dipho_vtxind[diphoton_id] ,
					      vtxProb,lead_p4,sublead_p4,sigmaMrv,sigmaMwv,sigmaMeonly,
					      bdtTrainingPhilosophy.c_str(),
					      phoid_mvaout_lead,phoid_mvaout_sublead);
	
	TLorentzVector diphoton = lead_p4+sublead_p4;
		

	// now dump variables in a flat tree
	if( dumpFlatTree ) {
	    tree_ = default_;
	    
	    tree_.entry         = l.event;
	    tree_.weight        = evweight;
	    tree_.sampleweight  = l.weight;
	    tree_.pho1pt        = lead_p4.Pt();
	    tree_.pho2pt        = sublead_p4.Pt();
	    tree_.diphopt       = diphoton.Pt();
	    tree_.diphoM        = diphoton.M();
	    tree_.diphoEta      = diphoton.Eta();
	    tree_.diphomva      = diphobdt_output;
	    
//	    tree_.jet1 = ijet1;
//	    tree_.jet2 = ijet2;
//	    tree_.jet3 = ijet3;
//	    
//	    if( ijet1 >= 0 ) {
//		tree_.jet1isMatched = l.jet_algoPF1_genMatched[ijet1];
//		tree_.jet1genPt     = l.jet_algoPF1_genPt[ijet1];
//		tree_.jet1genDr     = l.jet_algoPF1_genDr[ijet1];
//		tree_.jet1PileupID  = PileupJetIdentifier::passJetId(l.jet_algoPF1_simple_wp_level[ijet1], PileupJetIdentifier::kLoose);
//		tree_.jet1Pt        = jet1->Pt();
//		tree_.jet1Eta       = jet1->Eta();
//	    }
//	    if( ijet2 >= 0 ) {
//		tree_.jet2isMatched = l.jet_algoPF1_genMatched[ijet2];
//		tree_.jet2genPt     = l.jet_algoPF1_genPt[ijet2];
//		tree_.jet2genDr     = l.jet_algoPF1_genDr[ijet2];
//		tree_.jet2PileupID  = PileupJetIdentifier::passJetId(l.jet_algoPF1_simple_wp_level[ijet2], PileupJetIdentifier::kLoose);
//		tree_.jet2Pt        = jet2->Pt();
//		tree_.jet2Eta       = jet2->Eta();
//	    }
//	    
//	    if( ijet1 >= 0 && ijet2 >= 0 ) {
//		tree_.zepp          = fabs(diphoton.Eta() - 0.5*(jet1->Eta() + jet2->Eta())); 
//		tree_.mj1j2         = dijet.M();
//		tree_.dphi          = fabs(diphoton.DeltaPhi(dijet));
//		tree_.dijetEta      = dijet.Eta();
//		tree_.dphiJJ        = fabs(jet1->DeltaPhi(*jet2));
//		tree_.dphiJJ2       = fabs(sumj1.DeltaPhi(sumj2));
//	    }
	    
	    tree_.pho1energy      = lead_p4.E();
	    tree_.pho2energy      = sublead_p4.E();
	    tree_.pho1Eta         = lead_p4.Eta();
	    tree_.pho2Eta         = sublead_p4.Eta();
	    tree_.pho1Phi         = lead_p4.Phi();
	    tree_.pho2Phi         = sublead_p4.Phi();
	    tree_.pho1scEta         = (float)((TVector3*)l.sc_xyz->At(l.pho_scind[diphoton_index.first]))->Eta();
	    tree_.pho2scEta         = (float)((TVector3*)l.sc_xyz->At(l.pho_scind[diphoton_index.second]))->Eta();
	    tree_.pho1r9          = lead_r9;
	    tree_.pho2r9          = sublead_r9;
	    tree_.pho1idMva       = phoid_mvaout_lead;
	    tree_.pho2idMva       = phoid_mvaout_sublead;
	    tree_.pho1sE     = massResolutionCalculator->leadPhotonResolutionNoSmear();
	    tree_.pho2sE     = massResolutionCalculator->subleadPhotonResolutionNoSmear();
	    tree_.pho1sEsmear= massResolutionCalculator->leadPhotonResolution();   
	    tree_.pho2sEsmear= massResolutionCalculator->subleadPhotonResolution();
	    tree_.diphosM         = sigmaMrv;
	    tree_.diphosMwv       = sigmaMwv;
	    tree_.diphovtxProb    = vtxProb;
	    tree_.pho1Matched         = l.pho_genmatched[diphoton_index.first];
	    tree_.pho2Matched         = l.pho_genmatched[diphoton_index.second];
	    std::vector<std::vector<bool> > ph_passcut;
	    tree_.pho1CiC             = l.PhotonCiCSelectionLevel(diphoton_index.first,  l.dipho_vtxind[diphoton_id], ph_passcut, 4, 0, &smeared_pho_energy[0] );
	    tree_.pho2CiC             = l.PhotonCiCSelectionLevel(diphoton_index.second, l.dipho_vtxind[diphoton_id], ph_passcut, 4, 0, &smeared_pho_energy[0] );

	    tree_.isSignal  = (cur_type < 0);
	    tree_.mctype    = cur_type;
	    tree_.diphoMVA  = diphobdt_output;
	    tree_.corrVeretx = isCorrectVertex;
    //photon id
	   // tree_.pho1r9          = lead_r9;
	   // tree_.pho2r9          = sublead_r9;
	tree_.pho1sieie = (float)l.pho_sieie[diphoton_index.first];
	tree_.pho2sieie = (float)l.pho_sieie[diphoton_index.second];
	tree_.pho1scetawidth = (float)l.sc_seta[diphoton_index.first];
	tree_.pho2scetawidth = (float)l.sc_seta[diphoton_index.second];
	tree_.pho1scphiwidth = (float)l.sc_sphi[diphoton_index.first];
	tree_.pho2scphiwidth = (float)l.sc_sphi[diphoton_index.second];
	tree_.pho1sieip = (float)l.pho_sieip[diphoton_index.first];
	tree_.pho2sieip = (float)l.pho_sieip[diphoton_index.second];
    float s4ratio1 = l.pho_e2x2[diphoton_index.first]/l.pho_e5x5[diphoton_index.first];
    float s4ratio2 = l.pho_e2x2[diphoton_index.second]/l.pho_e5x5[diphoton_index.second];
	tree_.pho1s4ratio = (float) s4ratio1;
	tree_.pho2s4ratio = (float) s4ratio2;
	tree_.pho1pfphotoniso03 = l.pho_pfiso_myphoton03[diphoton_index.first];
	tree_.pho2pfphotoniso03 = l.pho_pfiso_myphoton03[diphoton_index.second];
	tree_.pho1pfchargedisogood03 = (float)((*l.pho_pfiso_mycharged03)[diphoton_index.first][l.dipho_vtxind[diphoton_id]]);
	tree_.pho2pfchargedisogood03 = (float)((*l.pho_pfiso_mycharged03)[diphoton_index.second][l.dipho_vtxind[diphoton_id]]);
    float pfchargedisobad03=0.;
            for(int ivtx=0; ivtx<l.vtx_std_n; ivtx++) {
                pfchargedisobad03 = l.pho_pfiso_mycharged03->at(diphoton_index.first).at(ivtx) > pfchargedisobad03 ? l.pho_pfiso_mycharged03->at(diphoton_index.first).at(ivtx) : pfchargedisobad03;
            }
	tree_.pho1pfchargedisobad03 = pfchargedisobad03;
    pfchargedisobad03=0.;
            for(int ivtx=0; ivtx<l.vtx_std_n; ivtx++) {
                pfchargedisobad03 = l.pho_pfiso_mycharged03->at(diphoton_index.second).at(ivtx) > pfchargedisobad03 ? l.pho_pfiso_mycharged03->at(diphoton_index.second).at(ivtx) : pfchargedisobad03;
            }
	tree_.pho2pfchargedisobad03 = pfchargedisobad03;
	tree_.pho1sceta = (float)((TVector3*)l.sc_xyz->At(l.pho_scind[diphoton_index.first]))->Eta();
	tree_.pho2sceta = (float)((TVector3*)l.sc_xyz->At(l.pho_scind[diphoton_index.second]))->Eta();
	tree_.rho = (float)l.rho_algo1;
    tree_.pho1hoe = (float) l.pho_hoe[diphoton_index.first];
    tree_.pho1hoe = (float) l.pho_hoe[diphoton_index.second];
    //Nikolas variables = ;
	tree_.pho1r9_Ethresh = (float)l.pho_r9_Ethresh[diphoton_index.first] ;
	tree_.pho2r9_Ethresh = (float)l.pho_r9_Ethresh[diphoton_index.second] ;
	tree_.pho1sieie_Ethresh = (float)l.pho_sieie_Ethresh[diphoton_index.first] ;
	tree_.pho2sieie_Ethresh = (float)l.pho_sieie_Ethresh[diphoton_index.second] ;
	tree_.pho1r9_chi2Thresh = (float)l.pho_r9_chi2Thresh[diphoton_index.first] ;
	tree_.pho2r9_chi2Thresh = (float)l.pho_r9_chi2Thresh[diphoton_index.second] ;
	tree_.pho1sieie_chi2Thresh = (float)l.pho_sieie_chi2Thresh[diphoton_index.first] ;
	tree_.pho2sieie_chi2Thresh = (float)l.pho_sieie_chi2Thresh[diphoton_index.second] ;
	tree_.pho1pfiso_cleanphoton03 = (float)l.pho_pfiso_cleanphoton03[diphoton_index.first] ;
	tree_.pho2pfiso_cleanphoton03 = (float)l.pho_pfiso_cleanphoton03[diphoton_index.second] ;
	tree_.pho1pfiso_cleanneutral03 = (float)l.pho_pfiso_cleanneutral03[diphoton_index.first] ;
	tree_.pho2pfiso_cleanneutral03 = (float)l.pho_pfiso_cleanneutral03[diphoton_index.second] ;
	tree_.pho1pfiso_cleancharged03 = (float)l.pho_pfiso_cleancharged03[diphoton_index.first] ;
	tree_.pho2pfiso_cleancharged03 = (float)l.pho_pfiso_cleancharged03[diphoton_index.second] ;
	tree_.pho1pfiso_cleanphoton04 = (float)l.pho_pfiso_cleanphoton04[diphoton_index.first] ;
	tree_.pho2pfiso_cleanphoton04 = (float)l.pho_pfiso_cleanphoton04[diphoton_index.second] ;
	tree_.pho1pfiso_cleanneutral04 = (float)l.pho_pfiso_cleanneutral04[diphoton_index.first] ;
	tree_.pho2pfiso_cleanneutral04 = (float)l.pho_pfiso_cleanneutral04[diphoton_index.second] ;
	tree_.pho1pfiso_cleancharged04 = (float)l.pho_pfiso_cleancharged04[diphoton_index.first] ;
	tree_.pho2pfiso_cleancharged04 = (float)l.pho_pfiso_cleancharged04[diphoton_index.second] ;

	    l.FillTreeContainer();

	    fillControlPlots(lead_p4, sublead_p4, Higgs, lead_r9, sublead_r9, diphoton_id,
			     category, isCorrectVertex, evweight, vtx, l, 0, -1, 0, -1 );
	}
	return false;
    }
    
    return false;
}

// Local Variables:
// mode: c++
// c-basic-offset: 4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
