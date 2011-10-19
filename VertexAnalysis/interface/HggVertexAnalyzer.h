#ifndef hgg_VertexAnalyzer_h
#define hgg_VertexAnalyzer_h


#include <set>
#include <vector>
#include <map>
#include <string>
#include <assert.h>

#include "TLorentzVector.h"
#include "TVector2.h"
#include "TVector3.h"
#include "TMatrixDSym.h"

namespace TMVA { class Reader; }

class VertexAlgoParameters;
class PhotonInfo;

class VertexInfoAdapter;
class TBranch;
class TTree;

// -------------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * 
 * \class HggVertexAnalyzer
 * Implements vertex analysis for Higgs to gamma gamma. 
 * The class provides vertexes classification through (T)MVA classifiers and ranks combination.
 *
 * Vertexes and tracks informations are read through the VertexInfoAdapter interface and the PhotonInfo class.
 * An implementation of the VertexInfoAdapter interface that can be used with (almost) any NTuple is provided 
 * by the TupleVertexInfo class.
 * 
 * usage example:
 * <code>
 * class MyAnalzer {
 * 
 *     // algo parameters
 *     VertexAlgoParameters vtxAlgoParams_;
 *     vector<string> rankVariables_, tmvaVariables_;
 *
 *     TMVA::Reader tmvaReader_;
 *     string tmvaMethod_;
 *
 *     // branches buffers
 *     inf nvtx_;
 *     float  vtxx_[100], vtxy_[100], vtxz_[100];
 *     
 *     int ntracks_;
 *     float tkpx_[100], tkpy_[100], tkpz_[100], tkPtErr_[100], tkVtxId_[100], tkWeight_[100];
 *     
 *     float phocalox_[30], phocaloy_[30], phocaloz_[30], phoen_[30];
 *     
 *     void init() {
 *           vtxAlgoParams_.rescaleTkPtByError = true;}
 *           // variables order matters to resolve ties
 *           rankVariables_.push_back("ptbal"), rankVariables.push_back("ptasym"), rankVariables.push_back("logsumpt2");
 *                    
 *           mvaMethod_ = "BDTMethod"; 
 *           // tmva has its own order
 *           tmvaVariables_.push_back("ptbal"), tmvaVariables.push_back("ptasym"), tmvaVariables.push_back("logsumpt2");
 *           tmvaReader_ = new TMVA::Reader( "!Color:!Silent" );
 *           HggVertexAnalyzer::bookVariables( *tmvaReader_, tmvaVariables_ );
 *           tmvaReader_->BookMVA( tmvaMethod_, "<path to weights>" ); 
 *     }
 *     
 *     void analyze() {
 *     
 *           TupleVertexInfo vinfo(nvtx_, vtxx_, vtxy_, vtxz_, 
 *     			   ntracks_, tkpx_, tkpy_, tkpz_, tkPtErr_, tkVtxId_, tkWeight_);
 *           
 *           PhotonInfo pho1(TVector3(phocalox_[p1],phocaloy_[p1],phocaloz_[p1]),phoen_[p1]), 
 *                           pho2(TVector3(phocalox_[p2],phocaloy_[p2],phocaloz_[p2]),phoen_[p2]);
 *     
 *          
 *           HggVertexAnalyzer vAna(vtxAlgoParams_,nvtx);
 *     
 *           vAna.analyze(vinfo,pho1,pho2);
 *     
 *           vecto<int> rankprod = vAna.rankprod(rankVariables_);
 *           cout << "\n\nRanks product" << endl;
 *           cout << "best vertex " << rankprod[0] << endl;
 *           for(int ii=0; ii<nvtx_; ++ii) {
 *                 int vtxrank = find(rankprod.begin(), rankprod.end(), ii) - rankprod.begin();
 *                 cout << "vertx " << ii << " rank " << vtxrank << " " << vAna.ptbal(ii) << " " << vAna.ptasym(ii) << " " << vAna.logsumpt2(ii) << endl;
 *     
 *           }
 * 
 *           vecto<int> ranktmva = vAna.rankprod(*tmvaReader_,tmvaMethod_);
 *           cout << "\n\n" << tmvaMethod_ << endl;
 *           cout << "best vertex " << rankprod[0] << endl;
 *           for(int ii=0; ii<nvtx_; ++ii) {
 *                 int vtxrank = find(ranktmva.begin(), ranktmva.end(), ii) - ranktmva.begin();
 *                 cout << "vertx " << ii << " rank " << vtxrank << " " << vAna.ptbal(ii) << " " << vAna.ptasym(ii) << " " << vAna.logsumpt2(ii) << endl;
 *           }
 *     }
 * 
 * };
 * </code>
 */
class HggVertexAnalyzer
{
public:
	typedef VertexAlgoParameters AlgoParameters;

	HggVertexAnalyzer(AlgoParameters & ap, int nvtx=40);


// CINT doesn't like function pointers
#ifndef __CINT__ 
	typedef float (HggVertexAnalyzer::*getter_t) (int) const;
	typedef std::map<std::string,std::pair<getter_t,bool> > dict_t;
	
	static dict_t & dictionary();
#endif
	static const float spherPwr_;
	
	static void bookVariables(TMVA::Reader & reader, const std::vector<std::string> & vars);
	static void bookSpectators(TMVA::Reader & reader, const std::vector<std::string> & vars);
	void fillVariables(int iv);
	
	// Rank vertexes
	std::vector<int> rank(std::string method);
#ifndef __CINT__	
	std::vector<int> rank(getter_t method, bool sign);
#endif
	std::vector<int> rank(TMVA::Reader &reader, const std::string & method);
	void evaluate(TMVA::Reader &reader, const std::string & method);
	std::vector<int> rankprod(const std::vector<std::string> & vars);

	void analyze(const VertexInfoAdapter &, const PhotonInfo & pho1, const PhotonInfo & pho2);

	void preselection(const std::vector<int> &ps) { preselection_ = ps; }

	// getters
	int pho1() const { return pho1_[ipair_]; };
	int pho2() const { return pho2_[ipair_]; };
	int ninvalid_idxs() const { return ninvalid_idxs_; };

	float mva(int i)    const { return 	mva_[i]; };	
	float rcomb(int i)    const { return 	rcomb_[i]; };	

	void setPullToConv(int ivert, float pull, float lim=10.);
	float pulltoconv(int i)    const { return pulltoconv_[ipair_][i]; };	
	float limpulltoconv(int i)    const { return limpulltoconv_[ipair_][i]; };	

	void setNConv(int n);
	float nconv(int i)            const { return nconv_[ipair_]; };	
	
	float diphopt(int i)    const { return diphopt_[ipair_][i]; };	
	float nch(int i)    const { return 	nch_[ipair_][i]; };	
	float ptmax(int i)  const { return 	ptmax_[ipair_][i]; };	
	float sumpt(int i)  const { return 	sumpt_[ipair_][i]; };	
	float ptvtx(int i)  const { return 	ptvtx_[ipair_][i]; };	
	float acosA(int i)  const { return  	acosA_[ipair_][i]; }; 	
	float ptasym(int i) const { return 	ptasym_[ipair_][i]; };	
	float ptbal(int i)  const { return 	ptbal_[ipair_][i]; };	
	
	float nchthr(int i) const { return 	nchthr_[ipair_][i]; };	
	float ptmax3(int i) const { return 	ptmax3_[ipair_][i]; };	
	float thrust(int i) const { return 	thrust_[ipair_][i]; };	

	float sumweight(int i) const { return sumweight_[ipair_][i]; };	
	float logsumpt2(int i) const { return log(sumpt2_[ipair_][i]); };	
	float ptratio(int i)   const { return ptratio_[ipair_][i]; };	
	float pzasym(int i)    const { return pzasym_[ipair_][i]; };	
	
	float spher(int i) const { return 	spher_[ipair_][i]; };	
	float tspher(int i) const { return 	tspher_[ipair_][i]; };
	float aplan(int i) const { return 	aplan_[ipair_][i]; };	
	float threejetC(int i) const { return 	threejetC_[ipair_][i]; };
	float fourjetD(int i) const { return 	fourjetD_[ipair_][i]; };
	float sumpr(int i) const { return 	sumpr_[ipair_][i]; };	
	
	float sumawy(int i) const { return 	sumawy_[ipair_][i]; };	
	float sumtrv(int i) const { return 	sumtrv_[ipair_][i]; };	
	float sumtwd(int i) const { return 	sumtwd_[ipair_][i]; };	
	float awytwdasym(int i) const { return awytwdasym_[ipair_][i]; };
	
	// read and write info to plain ROOT TTree
	void branches(TTree *, const std::string & );
	void setBranchAdresses(TTree *, const std::string &);
	void getBranches(TTree *, const std::string &, std::set<TBranch *>& );

	void clear();
	int  pairID(int pho1, int pho2);
	void setPairID(int x) { ipair_ = x; };
	void setPairID(int pho1, int pho2) { setPairID( pairID(pho1,pho2) ); };

private:
#ifndef __CINT__	
	static void fillDictionary(dict_t & dictionary);

	// TMVA interface
	static std::vector<getter_t> varmeths_;
	static std::vector<float> vars_;
#endif
	std::vector<int> preselection();
	void newpair(int ipair);

	AlgoParameters & params_;
	int nvtx_;
	int ipair_;
	
	std::vector<int> preselection_;

	std::vector<float> mva_, rcomb_;
	
	// buffers
	std::vector<std::vector<TLorentzVector> > diPhoton_;
	std::vector<std::vector<float> > diphopt_;
	
	std::vector<float> nconv_;
	std::vector<std::vector<float> > pulltoconv_;
	std::vector<std::vector<float> > limpulltoconv_;
	std::vector<std::vector<float> > ptbal_;
	std::vector<std::vector<float> > thrust_;
	std::vector<std::vector<float> > sumpt_;
	std::vector<std::vector<float> > sumpt2_;
	std::vector<std::vector<float> > sumawy_;
	std::vector<std::vector<float> > sumtwd_;
	std::vector<std::vector<float> > sumtrv_;
	std::vector<std::vector<float> > sumweight_;
	std::vector<std::vector<float> > ptmax_;
	std::vector<std::vector<float> > nchthr_;
	std::vector<std::vector<float> > nch_;
	std::vector<std::vector<std::vector<float> > > tksPt_;
	std::vector<std::vector<TMatrixDSym> > sphers_;
	std::vector<std::vector<float> > sumpr_;
	std::vector<std::vector<float> > spher_;
	std::vector<std::vector<float> > tspher_;
	std::vector<std::vector<float> > aplan_;
	std::vector<std::vector<float> > threejetC_;
	std::vector<std::vector<float> > fourjetD_;

	std::vector<std::vector<TVector3> > vtxP_;
	std::vector<std::vector<TVector2> > vtxPt_;
	std::vector<std::vector<float> > ptvtx_;

	std::vector<std::vector<TVector2> > diPhotonPt_;
	std::vector<std::vector<float> > diPhotonPz_;
	
	std::vector<std::vector<float> > acosA_;
	std::vector<std::vector<float> > ptasym_;

	std::vector<std::vector<float> > ptmax3_;

	std::vector<std::vector<float> > ptratio_;
	std::vector<std::vector<float> > pzasym_;

	std::vector<std::vector<float> > awytwdasym_;

	std::vector<int> pho1_, pho2_;
	std::vector<int> * ppho1_, * ppho2_;
	int ninvalid_idxs_;

	std::vector<std::vector<float> > * pdiphopt ;
	std::vector<std::vector<float> > * pnch ;
	std::vector<std::vector<float> > * pptmax ;
	std::vector<std::vector<float> > * psumpt ;
	std::vector<std::vector<float> > * pptvtx ;
	std::vector<std::vector<float> > * pacosA ;
	std::vector<std::vector<float> > * pptasym ;
	std::vector<std::vector<float> > * pptbal ;
	
	std::vector<std::vector<float> > * pnchthr ;
	std::vector<std::vector<float> > * pptmax3 ;
	std::vector<std::vector<float> > * pthrust ;

	std::vector<std::vector<float> > * psumweight ;
	std::vector<std::vector<float> > * psumpt2 ;
	std::vector<std::vector<float> > * pptratio ;
	std::vector<std::vector<float> > * ppzasym ;

	std::vector<std::vector<float> > * pspher ;
	std::vector<std::vector<float> > * paplan ;
	std::vector<std::vector<float> > * psumpr ;

	std::vector<std::vector<float> > * psumawy ;
	std::vector<std::vector<float> > * psumtrv ;
	std::vector<std::vector<float> > * psumtwd ;
	std::vector<std::vector<float> > * pawytwdasym ;

};

// -------------------------------------------------------------------------------------------------------------------------------------------------------------
class VertexInfoAdapter 
{
public:

	virtual int nvtx() const = 0;

	virtual float vtxx(int) const = 0;
	virtual float vtxy(int) const = 0;
	virtual float vtxz(int) const = 0;

	virtual int ntracks() const = 0;

	virtual bool hasVtxTracks() const = 0;
	virtual const unsigned short * vtxTracks(int) const = 0;
	virtual int vtxNTracks(int) const = 0;
	virtual const float * vtxTkWeights(int) const = 0;
		
	virtual float tkpx(int) const = 0;
	virtual float tkpy(int) const = 0;
	virtual float tkpz(int) const = 0;
	
	virtual float tkPtErr(int) const = 0;
	virtual int   tkVtxId(int) const = 0;

	virtual float tkWeight(int ii, int jj) const  = 0;

	virtual float tkd0(int ii, int jj) const  = 0;
	virtual float tkd0Err(int ii, int jj) const  = 0;

	virtual float tkdz(int ii, int jj) const  = 0;
	virtual float tkdzErr(int ii, int jj) const  = 0;
	
	virtual bool tkIsHighPurity(int) const = 0;

	virtual ~VertexInfoAdapter();
};

// -------------------------------------------------------------------------------------------------------------------------------------------------------------
class TupleVertexInfo : public VertexInfoAdapter
{
public:

	TupleVertexInfo(int nvtx, float * vtxx, float * vtxy, float * vtxz, 
			   int ntracks, float * tkpx, float * tkpy, float * tkpz,
			   float * tkPtErr, int * tkVtxId, float * tkWeight,
			   float * tkd0, float * tkd0Err, float * tkdz, float * tkdzErr,
			   bool * tkIsHighPurity
		);
	
	virtual int nvtx() const    { return nvtx_; };
	virtual int ntracks() const { return ntracks_; };

	virtual bool hasVtxTracks()  const { return false; };
	virtual const unsigned short * vtxTracks(int) const { return 0; };
	virtual int vtxNTracks(int)  const { return 0; };
	virtual const float * vtxTkWeights(int) const { return 0; };

	virtual float tkpx(int ii) const { return tkpx_ != 0 ? tkpx_[ii] : 0.; };
	virtual float tkpy(int ii) const { return tkpx_ != 0 ? tkpy_[ii] : 0.; };
	virtual float tkpz(int ii) const { return tkpx_ != 0 ? tkpz_[ii] : 0.; };
	
	virtual float tkPtErr(int ii) const { return tkPtErr_  != 0 ? tkPtErr_[ii] : 999.; };
	virtual int   tkVtxId(int ii) const { return tkVtxId_  != 0 ? tkVtxId_[ii] : 999; };

	virtual float tkWeight(int ii, int jj) const { return tkWeight_ != 0 ? tkWeight_[ii]*(float)( tkVtxId(ii) == jj) : 0.; };
	
	virtual float vtxx(int ii) const { return vtxx_ != 0 ? vtxx_[ii] : 0.; };
	virtual float vtxy(int ii) const { return vtxy_ != 0 ? vtxy_[ii] : 0.; };
	virtual float vtxz(int ii) const { return vtxz_ != 0 ? vtxz_[ii] : 0.; };

	virtual float tkd0(int ii, int jj) const { assert(tkVtxId(ii) == jj); return tkd0_ != 0 ? tkd0_[ii] : 0.; };
	virtual float tkd0Err(int ii, int jj) const { assert(tkVtxId(ii) == jj); return tkd0Err_ != 0 ? tkd0Err_[ii] : 0.; };

	virtual float tkdz(int ii, int jj) const { assert(tkVtxId(ii) == jj); return tkdz_ != 0 ? tkdz_[ii] : 0.; };
	virtual float tkdzErr(int ii, int jj) const { assert(tkVtxId(ii) == jj); return tkdzErr_ != 0 ? tkdzErr_[ii] : 0.; };

	virtual bool tkIsHighPurity(int ii) const { return tkIsHighPurity_ != 0 ? tkIsHighPurity_[ii] : 0.; };

	virtual ~TupleVertexInfo();
	
private:
	int nvtx_;
	float * vtxx_;
	float * vtxy_;
	float * vtxz_;

	int ntracks_;
	float * tkpx_;
	float * tkpy_;
	float * tkpz_;
	float * tkPtErr_;
	int * tkVtxId_;	
	float * tkWeight_;
	float * tkd0_;
	float * tkd0Err_;
	float * tkdz_;
	float * tkdzErr_;

	bool * tkIsHighPurity_;
};

#endif

// Local Variables:
// mode: c++       
// mode: sensitive 
// c-basic-offset: 8
// End:             
