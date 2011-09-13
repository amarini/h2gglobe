#include "../interface/HggVertexAnalyzer.h"
#include "../interface/PhotonInfo.h"
#include "../interface/VertexAlgoParameters.h"

#include "stdio.h"
#include "math.h"

#include <algorithm>
#include <numeric>
#include <iterator>

#include <assert.h>

#include "TMatrixDSym.h"
#include "TMatrixDSymEigen.h"
#include "TVectorD.h"
#include "TTree.h"
#include "TBranch.h"

#include "TMVA/Reader.h"

using namespace std;

// -------------------------------------------------------------------------------------------------------------------------------------------------------------
const float HggVertexAnalyzer::spherPwr_(1.5);

// -------------------------------------------------------------------------------------------------------------------------------------------------------------
vector<float> HggVertexAnalyzer::vars_;
vector<HggVertexAnalyzer::getter_t> HggVertexAnalyzer::varmeths_;

// -------------------------------------------------------------------------------------------------------------------------------------------------------------
HggVertexAnalyzer::dict_t & HggVertexAnalyzer::dictionary() 
{
	static HggVertexAnalyzer::dict_t dictionary;
	if( dictionary.empty() ) { fillDictionary(dictionary); }
	return dictionary;
}

// -------------------------------------------------------------------------------------------------------------------------------------------------------------
void HggVertexAnalyzer::fillDictionary(HggVertexAnalyzer::dict_t& dictionary)
{
	//// dictionary_["mva"] =   make_pair(&HggVertexAnalyzer::mva,false);
	
	dictionary["diphopt"]   = make_pair(&HggVertexAnalyzer::diphopt,false);
	dictionary["nch"]   = make_pair(&HggVertexAnalyzer::nch,false);
	dictionary["ptmax"] = make_pair(&HggVertexAnalyzer::ptmax,false);
	dictionary["sumpt"] = make_pair(&HggVertexAnalyzer::sumpt,false);
	dictionary["ptvtx"] = make_pair(&HggVertexAnalyzer::ptvtx,false);
	dictionary["acosA"] = make_pair(&HggVertexAnalyzer::acosA,false);
	dictionary["ptasym"] = make_pair(&HggVertexAnalyzer::ptasym,false);
	dictionary["ptbal"] = make_pair(&HggVertexAnalyzer::ptbal,false);
	
	dictionary["nchthr"] = make_pair(&HggVertexAnalyzer::nchthr,false);
	dictionary["ptmax3"] = make_pair(&HggVertexAnalyzer::ptmax3,false);
	dictionary["thrust"] = make_pair(&HggVertexAnalyzer::thrust,false);
	
	dictionary["sumweight"] = make_pair(&HggVertexAnalyzer::sumweight,false);
	dictionary["logsumpt2"] = make_pair(&HggVertexAnalyzer::logsumpt2,false);
	dictionary["log(sumPt2)"] = make_pair(&HggVertexAnalyzer::logsumpt2,false);
	dictionary["ptratio"] =   make_pair(&HggVertexAnalyzer::ptratio,false);
	dictionary["pzasym"] =    make_pair(&HggVertexAnalyzer::pzasym,false);
	
	dictionary["spher"] = make_pair(&HggVertexAnalyzer::spher,false);
	dictionary["aplan"] = make_pair(&HggVertexAnalyzer::aplan,false);
	dictionary["sumpr"] = make_pair(&HggVertexAnalyzer::sumpr,false);
	
	dictionary["sumawy"] = make_pair(&HggVertexAnalyzer::sumawy,false);
	dictionary["sumtrv"] = make_pair(&HggVertexAnalyzer::sumtrv,false);
	dictionary["sumtwd"] = make_pair(&HggVertexAnalyzer::sumtwd,false);
	dictionary["awytwdasym"] = make_pair( &HggVertexAnalyzer::awytwdasym,false);
}

// -------------------------------------------------------------------------------------------------------------------------------------------------------------
HggVertexAnalyzer::HggVertexAnalyzer(AlgoParameters & ap, int nvtx) :
	params_(ap),
	nvtx_(nvtx) /// ,
	////// 
	////// mva_(nvtx),
	////// 
	////// diPhoton_(nvtx),
	////// diphopt_(nvtx),
	////// 
	////// ptbal_(nvtx,0.),
	////// thrust_(nvtx,0.),
	////// sumpt_(nvtx,0.),
	////// sumpt2_(nvtx,0.),
	////// sumawy_(nvtx,0.),
	////// sumtwd_(nvtx,0.),
	////// sumtrv_(nvtx,0.),
	////// sumweight_(nvtx,0.),
	////// ptmax_(nvtx,0.),
	////// nchthr_(nvtx,0.),
	////// nch_(nvtx,0.),
	////// tksPt_(nvtx, vector<float>(1)),
	////// sphers_(nvtx,TMatrixDSym(3)),
	////// sumpr_(nvtx,0.),
	////// spher_(nvtx,0.),
	////// tspher_(nvtx,0.),
	////// aplan_(nvtx,0.),
	////// threejetC_(nvtx,0.),
	////// fourjetD_(nvtx,0.),
	////// 
	////// vtxP_(nvtx,0.),
	////// vtxPt_(nvtx),
	////// ptvtx_(nvtx),
	////// 
	////// diPhotonPt_(nvtx),
	////// diPhotonPz_(nvtx),
	////// 
	////// acosA_(nvtx),
	////// ptasym_(nvtx),
	////// 
	////// ptmax3_(nvtx),
	////// 
	////// ptratio_(nvtx),
	////// pzasym_(nvtx),
	////// 
	////// awytwdasym_(nvtx),
	////// pho1_(-1),
	////// pho2_(-1),
{

	pdiphopt = &diphopt_;
	pnch = &nch_;
	pptmax = &ptmax_;
	psumpt = &sumpt_;
	pptvtx = &ptvtx_;
	pacosA = &acosA_;
	pptasym = &ptasym_;
	pptbal = &ptbal_;
	
	pnchthr = &nchthr_;
	pptmax3 = &ptmax3_;
	pthrust = &thrust_;
	
	psumweight = &sumweight_;
	psumpt2 = &sumpt2_;
	pptratio = &ptratio_;
	ppzasym = &pzasym_;
	
	pspher = &spher_;
	paplan = &aplan_;
	psumpr = &sumpr_;
	
	psumawy = &sumawy_;
	psumtrv = &sumtrv_;
	psumtwd = &sumtwd_;
	pawytwdasym = &awytwdasym_;

	ppho1_ = &pho1_;
	ppho2_ = &pho2_;
}

// -------------------------------------------------------------------------------------------------------------------------------------------------------------
void HggVertexAnalyzer::branches(TTree * tree, const std::string & pfx)
{
	tree->Branch((pfx+"diphopt").c_str(), &diphopt_ );
	tree->Branch((pfx+"nch").c_str(), &nch_ )  ;
	tree->Branch((pfx+"ptmax").c_str(), &ptmax_ );
	tree->Branch((pfx+"sumpt").c_str(), &sumpt_ );
	tree->Branch((pfx+"ptvtx").c_str(), &ptvtx_ );
	tree->Branch((pfx+"acosA").c_str(), &acosA_ );
	tree->Branch((pfx+"ptasym").c_str(), &ptasym_ );
	tree->Branch((pfx+"ptbal").c_str(), &ptbal_ );
	
	tree->Branch((pfx+"nchthr").c_str(), &nchthr_ );
	tree->Branch((pfx+"ptmax3").c_str(), &ptmax3_ );
	tree->Branch((pfx+"thrust").c_str(), &thrust_ );
	
	tree->Branch((pfx+"sumweight").c_str(), &sumweight_ );
	tree->Branch((pfx+"sumpt2").c_str(), &sumpt2_ );
	tree->Branch((pfx+"ptratio").c_str(), &ptratio_ );
	tree->Branch((pfx+"pzasym").c_str(), &pzasym_ );
	
	tree->Branch((pfx+"spher").c_str(), &spher_ );
	tree->Branch((pfx+"aplan").c_str(), &aplan_ );
	tree->Branch((pfx+"sumpr").c_str(), &sumpr_ );
	
	tree->Branch((pfx+"sumawy").c_str(), &sumawy_ );
	tree->Branch((pfx+"sumtrv").c_str(), &sumtrv_ );
	tree->Branch((pfx+"sumtwd").c_str(), &sumtwd_ );
	tree->Branch((pfx+"awytwdasym").c_str(), &awytwdasym_ );

	/// tree->Branch((pfx+"ninvalid_idxs").c_str(), &ninvalid_idxs_, (pfx+"ninvalid_idxs/I").c_str() );
	tree->Branch((pfx+"pho1").c_str(), &pho1_, (pfx+"pho1/I").c_str() );
	tree->Branch((pfx+"pho2").c_str(), &pho2_, (pfx+"pho2/I").c_str() );
}

// -------------------------------------------------------------------------------------------------------------------------------------------------------------
void HggVertexAnalyzer::setBranchAdresses(TTree * tree, const std::string & pfx)
{
	tree->SetBranchAddress((pfx+"diphopt").c_str(), &pdiphopt );
	tree->SetBranchAddress((pfx+"nch").c_str(), &pnch )  ;
	tree->SetBranchAddress((pfx+"ptmax").c_str(), &pptmax );
	tree->SetBranchAddress((pfx+"sumpt").c_str(), &psumpt );
	tree->SetBranchAddress((pfx+"ptvtx").c_str(), &pptvtx );
	tree->SetBranchAddress((pfx+"acosA").c_str(), &pacosA );
	tree->SetBranchAddress((pfx+"ptasym").c_str(), &pptasym );
	tree->SetBranchAddress((pfx+"ptbal").c_str(), &pptbal );
								   		  
	tree->SetBranchAddress((pfx+"nchthr").c_str(), &pnchthr );
	tree->SetBranchAddress((pfx+"ptmax3").c_str(), &pptmax3 );
	tree->SetBranchAddress((pfx+"thrust").c_str(), &pthrust );

	tree->SetBranchAddress((pfx+"sumweight").c_str(), &psumweight );
	tree->SetBranchAddress((pfx+"sumpt2").c_str(), &psumpt2 );
	tree->SetBranchAddress((pfx+"ptratio").c_str(), &pptratio );
	tree->SetBranchAddress((pfx+"pzasym").c_str(), &ppzasym );

	tree->SetBranchAddress((pfx+"spher").c_str(), &pspher );
	tree->SetBranchAddress((pfx+"aplan").c_str(), &paplan );
	tree->SetBranchAddress((pfx+"sumpr").c_str(), &psumpr );

	tree->SetBranchAddress((pfx+"sumawy").c_str(), &psumawy );
	tree->SetBranchAddress((pfx+"sumtrv").c_str(), &psumtrv );
	tree->SetBranchAddress((pfx+"sumtwd").c_str(), &psumtwd );
	tree->SetBranchAddress((pfx+"awytwdasym").c_str(), &pawytwdasym );

	/// tree->SetBranchAddress((pfx+"ninvalid_idxs").c_str(), &ninvalid_idxs_ );
	tree->SetBranchAddress((pfx+"pho1").c_str(), &ppho1_ );
	tree->SetBranchAddress((pfx+"pho2").c_str(), &ppho2_ );
}

// -------------------------------------------------------------------------------------------------------------------------------------------------------------
void HggVertexAnalyzer::getBranches(TTree * tree, const std::string & pfx, std::set<TBranch *> &ret)
{
	ret.insert(tree->GetBranch((pfx+"diphopt").c_str()));
	ret.insert(tree->GetBranch((pfx+"nch").c_str()));
	ret.insert(tree->GetBranch((pfx+"ptmax").c_str()));
	ret.insert(tree->GetBranch((pfx+"sumpt").c_str()));
	ret.insert(tree->GetBranch((pfx+"ptvtx").c_str()));
	ret.insert(tree->GetBranch((pfx+"acosA").c_str()));
	ret.insert(tree->GetBranch((pfx+"ptasym").c_str()));
	ret.insert(tree->GetBranch((pfx+"ptbal").c_str()));
	
	ret.insert(tree->GetBranch((pfx+"nchthr").c_str()));
	ret.insert(tree->GetBranch((pfx+"ptmax3").c_str()));
	ret.insert(tree->GetBranch((pfx+"thrust").c_str()));
	
	ret.insert(tree->GetBranch((pfx+"sumweight").c_str()));
	ret.insert(tree->GetBranch((pfx+"sumpt2").c_str()));
	ret.insert(tree->GetBranch((pfx+"ptratio").c_str()));
	ret.insert(tree->GetBranch((pfx+"pzasym").c_str()));
	
	ret.insert(tree->GetBranch((pfx+"spher").c_str()));
	ret.insert(tree->GetBranch((pfx+"aplan").c_str()));
	ret.insert(tree->GetBranch((pfx+"sumpr").c_str()));
	
	ret.insert(tree->GetBranch((pfx+"sumawy").c_str()));
	ret.insert(tree->GetBranch((pfx+"sumtrv").c_str()));
	ret.insert(tree->GetBranch((pfx+"sumtwd").c_str()));
	ret.insert(tree->GetBranch((pfx+"awytwdasym").c_str()));

	/// ret.insert(tree->GetBranch((pfx+"ninvalid_idxs").c_str()));
	ret.insert(tree->GetBranch((pfx+"pho1").c_str()));
	ret.insert(tree->GetBranch((pfx+"pho2").c_str()));
}

// -------------------------------------------------------------------------------------------------------------------------------------------------------------
void HggVertexAnalyzer::bookVariables(TMVA::Reader & reader,const std::vector<std::string> & order)
{
	vars_.resize(order.size(),0.);
	varmeths_.resize(order.size(),0);
	for(size_t ivar=0; ivar<order.size(); ++ivar) {
		reader.AddVariable( order[ivar], &vars_[ivar] );
		varmeths_[ivar] = dictionary()[order[ivar]].first;
	}
}

// -------------------------------------------------------------------------------------------------------------------------------------------------------------
void HggVertexAnalyzer::bookSpectators(TMVA::Reader & reader,const std::vector<std::string> & order)
{
	for(size_t ivar=0; ivar<order.size(); ++ivar) {
		vars_.push_back(0.); 
		reader.AddSpectator( order[ivar], &*vars_.rbegin() );
		varmeths_.push_back( dictionary()[order[ivar]].first );
	}
}


// -------------------------------------------------------------------------------------------------------------------------------------------------------------
void HggVertexAnalyzer::fillVariables(int iv)
{
	for(size_t ivar=0; ivar<varmeths_.size(); ++ivar) {
		vars_[ivar] = ((*this).*(varmeths_[ivar]))(iv);
	}
}

// -------------------------------------------------------------------------------------------------------------------------------------------------------------
class RankHelper
{
public:
	RankHelper( HggVertexAnalyzer & vAna, vector<pair< HggVertexAnalyzer::getter_t, bool> > m) :
		vAna_(vAna), method_(m) {};
	RankHelper( HggVertexAnalyzer & vAna, HggVertexAnalyzer::getter_t m, bool sign) :
		vAna_(vAna), method_(vector<pair<HggVertexAnalyzer::getter_t,bool> >(1,make_pair(m,sign))) {};

	bool operator() (int lh,int rh) {

		if (lh == rh){
			return true;
		}

		vector<pair< HggVertexAnalyzer::getter_t, bool> >::iterator imeth;
		for(imeth = method_.begin(); imeth != method_.end(); ++imeth){
			float lhv = (vAna_.*imeth->first)(lh);
			float rhv = (vAna_.*imeth->first)(rh);
			if( lhv != rhv ){
				return imeth->second ? lhv < rhv : lhv > rhv;
			}
		}
		
		return lh < rh;
	}
	
private:
	HggVertexAnalyzer & vAna_;
	vector<pair< HggVertexAnalyzer::getter_t,bool> > method_;
};

// -------------------------------------------------------------------------------------------------------------------------------------------------------------
std::vector<int> HggVertexAnalyzer::rank(HggVertexAnalyzer::getter_t method, bool sign)
{
	std::vector<int> vtxs = preselection_;
	assert( ! vtxs.empty() );
	assert( (size_t)ipair_ < pho1_.size() );
	RankHelper helper(*this, method, sign );
	sort(vtxs.begin(),vtxs.end(),helper);

	return vtxs;
}

// -------------------------------------------------------------------------------------------------------------------------------------------------------------
std::vector<int> HggVertexAnalyzer::rank(std::string method)
{
	dict_t::value_type::second_type m = dictionary()[method];
	return rank(m.first,m.second);
}

// -------------------------------------------------------------------------------------------------------------------------------------------------------------
std::vector<int> HggVertexAnalyzer::rank(TMVA::Reader &reader, const std::string & method)
{
	std::vector<int> vtxs = preselection_;
	assert( ! vtxs.empty() );
	assert( (size_t)ipair_ < pho1_.size() );
	mva_.clear(); mva_.resize(sumpt2_.size(),0.);
	for(int ii=0; ii<nvtx_; ++ii) { 
		fillVariables(ii);
		mva_[ii] = reader.EvaluateMVA(method);
	}
	RankHelper helper(*this,&HggVertexAnalyzer::mva,false);
	sort(vtxs.begin(),vtxs.end(),helper);

	return vtxs;	
}

// -------------------------------------------------------------------------------------------------------------------------------------------------------------
void HggVertexAnalyzer::evaluate(TMVA::Reader &reader, const std::string & method)
{
	std::vector<int> vtxs = preselection_;
	assert( ! vtxs.empty() );
	assert( (size_t)ipair_ < pho1_.size() );
	mva_.clear(); mva_.resize(sumpt2_.size(),0.);
	for(int ii=0; ii<nvtx_; ++ii) {
		fillVariables(ii);
		mva_[ii] = reader.EvaluateMVA(method);
	}
}

// -------------------------------------------------------------------------------------------------------------------------------------------------------------
std::vector<int> HggVertexAnalyzer::ranksum(const vector<string> & vars)
{
	std::vector<int> vtxs = preselection_;
	assert( ! vtxs.empty() );
	assert( (size_t)ipair_ < pho1_.size() );
	mva_.clear(); mva_.resize(nvtx_,0.);
	// fill the rank sum
	std::vector<int> vrank(nvtx_);
	std::vector<pair<HggVertexAnalyzer::getter_t, bool> > meths(1,make_pair(&HggVertexAnalyzer::mva,true));
	for( vector<string>::const_iterator ivar=vars.begin(); ivar!=vars.end(); ++ivar) {
		meths.push_back(dictionary()[*ivar]);
		vrank = rank( *ivar );
		for(size_t ii=0; ii<vtxs.size(); ++ii) {
			int ivert = vtxs[ii];
			mva_[ivert] += (float)(find( vrank.begin(), vrank.end(), ivert) - vrank.begin());
		}
	}
	RankHelper helper(*this,meths);
	sort(vtxs.begin(),vtxs.end(),helper);

	return vtxs;
}

// -------------------------------------------------------------------------------------------------------------------------------------------------------------
std::vector<int> HggVertexAnalyzer::rankprod(const vector<string> & vars)
{
	std::vector<int> vtxs = preselection_;
	assert( ! vtxs.empty() );
	assert( (size_t)ipair_ < pho1_.size() );
	mva_.clear(); mva_.resize(nvtx_,1.);
	// fill the rank sum
	std::vector<int> vrank(nvtx_);
	std::vector<pair<HggVertexAnalyzer::getter_t, bool> > meths(1,make_pair(&HggVertexAnalyzer::mva,true));
	for( vector<string>::const_iterator ivar=vars.begin(); ivar!=vars.end(); ++ivar) {
		meths.push_back(dictionary()[*ivar]);
		vrank = rank( *ivar );
		for(size_t ii=0; ii<vtxs.size(); ++ii) {
			int ivert = vtxs[ii];
			int rank = find( vrank.begin(), vrank.end(), ivert) - vrank.begin(); 
			mva_[ivert] *= 1. + (float)(rank);
			/// if( mva_[ivert] < 0. ) {
			/// 	cerr << "HggVertexAn  : negative rankprod " << ivert << " " << rank << " " << vrank.size() << " " << mva_[ivert] << endl;
			/// }
		}
	}
	for(int ii=0; ii<nvtx_; ++ii) {
		mva_[ii] = pow( mva_[ii], 1./(float)vars.size() );
	}
	RankHelper helper(*this,meths);
	sort(vtxs.begin(),vtxs.end(),helper);

	return vtxs;
}

////// // -------------------------------------------------------------------------------------------------------------------------------------------------------------
////// std::vector<int> HggVertexAnalyzer::rankreciprocal(const vector<string> & vars)
////// {
////// 	std::vector<int> vtxs = preselection_;
////// 	assert( ! vtxs.empty() );
////// 	assert( (size_t)ipair_ < pho1_.size() );	
////// 	mva_.clear(); mva_.resize(sumpt2_.size(),0.);
////// 	// fill the rank sum
////// 	std::vector<int> vrank(nvtx_);
////// 	std::vector<pair<HggVertexAnalyzer::getter_t, bool> > meths(1,make_pair(&HggVertexAnalyzer::mva,false));
////// 	for( vector<string>::const_iterator ivar=vars.begin(); ivar!=vars.end(); ++ivar) {
////// 		meths.push_back(dictionary()[*ivar]);
////// 		vrank = rank( *ivar );
////// 		for(size_t ii=0; ii<vtxs.size(); ++ii) {
////// 			int ivert = vtxs[ii];
////// 			mva_[ivert] += pow((float)(1 + (find( vrank.begin(), vrank.end(), ivert) - vrank.begin())),-2);
////// 		}
////// 	}
////// 	RankHelper helper(*this,meths);
////// 	sort(vtxs.begin(),vtxs.end(),helper);
////// 
////// 	return vtxs;
////// }
////// 
////// // -------------------------------------------------------------------------------------------------------------------------------------------------------------
////// vector<int> HggVertexAnalyzer::rankPairwise(const vector<string> & vars)
////// {
////// 	vector<int> vtxs = preselection_;
////// 	assert( ! vtxs.empty() );
////// 	mva_.clear(); mva_.resize(sumpt2_.size(),0.);
////// 	// fill the rank sum
////// 	vector<int> vrank(nvtx_);
////// 	vector<vector<int> > comp(nvtx_,vector<int>(nvtx_,0));
////// 	vector<pair<HggVertexAnalyzer::getter_t, bool> > meths(1,make_pair(&HggVertexAnalyzer::mva,false));
////// 	for( vector<string>::const_iterator ivar=vars.begin(); ivar!=vars.end(); ++ivar) {
////// 		meths.push_back(dictionary()[*ivar]);
////// 		vrank = rank( *ivar );
////// 		for(size_t i=0; i<vtxs.size(); ++i) {
////// 			int v1 = vtxs[i];
////// 			for(size_t j=0; j<i; ++j) {
////// 				int v2 = vtxs[j];
////// 				int rankv1 = (int)(find( vrank.begin(), vrank.end(), v1) - vrank.begin());
////// 				int rankv2 = (int)(find( vrank.begin(), vrank.end(), v2) - vrank.begin());
////// 				if(rankv1 < rankv2){
////// 					comp[v1][v2]++;
////// 				}else{
////// 					comp[v2][v1]++;
////// 				}
////// 			}
////// 		}
////// 	}
////// 
////// 	for(size_t i=0; i<vtxs.size(); ++i) {
////// 		int v1 = vtxs[i];
////// 		for(size_t j=0; j<i; ++j) {
////// 			int v2 = vtxs[j];
////// 			if( comp[v1][v2] > comp[v2][v1] ){
////// 				mva_[v1] += 1.0;
////// 			}else if ( comp[v1][v2] < comp[v2][v1] ) {
////// 				mva_[v2] += 1.0;
////// 			}else{
////// 				mva_[v1] += 0.5;
////// 				mva_[v2] += 0.5;
////// 			}
////// 		}
////// 	}
////// 
////// 	RankHelper helper(*this,meths);
////// 	sort(vtxs.begin(),vtxs.end(),helper);
////// 
////// 	return vtxs;
////// }
////// 
////// 
// -------------------------------------------------------------------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------------------------------------------------------------------
int HggVertexAnalyzer::pairID(int pho1, int pho2)
{
	assert( pho1_.size() == pho2_.size() );
	int ipair = 0;
	for( ; (size_t)ipair<pho1_.size(); ++ipair ) {
		if( pho1_[ipair] == pho1 && pho2_[ipair] == pho2 ) { break; }
	}
	return ipair;
}

// -------------------------------------------------------------------------------------------------------------------------------------------------------------
void HggVertexAnalyzer::clear()
{
	pho1_.clear();
	pho2_.clear();

	ptbal_.clear();
	thrust_.clear();
	sumpt_.clear();
	sumpt2_.clear();
	sumawy_.clear();
	sumtwd_.clear();
	sumtrv_.clear();
	sumweight_.clear();
	ptmax_.clear();
	nchthr_.clear();
	nch_.clear();
	vtxP_.clear();
	tksPt_.clear();
	sphers_.clear();
	sumpr_.clear();
	spher_.clear();
	tspher_.clear();
	aplan_.clear();
	threejetC_.clear();
	fourjetD_.clear();
	
	diphopt_.clear();
	diPhotonPt_.clear();
	vtxPt_.clear();
	ptvtx_.clear();
	diPhotonPz_.clear();
	
	acosA_.clear();
	ptasym_.clear();
	
	ptmax3_.clear();
	thrust_.clear();
	
	ptratio_.clear();
	pzasym_.clear();
	
	awytwdasym_.clear();
	
	diPhoton_.clear();
}

// -------------------------------------------------------------------------------------------------------------------------------------------------------------
void HggVertexAnalyzer::analyze(const VertexInfoAdapter & e, const PhotonInfo & p1, const PhotonInfo & p2)
{
	int const nvtx = e.nvtx();
	nvtx_ = nvtx;
	mva_.clear(); mva_.resize(nvtx,0.);
	/// std::cerr << "HggVertexAnalyzer::analyze " << nvtx_ << std::endl;
	int pho1 = p1.id();
	int pho2 = p2.id();
	ipair_ = pairID(pho1,pho2);
	if( ipair_ >= pho1_.size() ) {
		pho1_.push_back(pho1);
		pho2_.push_back(pho2);

		ninvalid_idxs_=0;

		// initilise
		ptbal_.resize(ipair_+1); ptbal_[ipair_].resize(nvtx,0.);
		thrust_.resize(ipair_+1); thrust_[ipair_].resize(nvtx,0.);
		sumpt_.resize(ipair_+1); sumpt_[ipair_].resize(nvtx,0.);
		sumpt2_.resize(ipair_+1); sumpt2_[ipair_].resize(nvtx,0.);
		sumawy_.resize(ipair_+1); sumawy_[ipair_].resize(nvtx,0.);
		sumtwd_.resize(ipair_+1); sumtwd_[ipair_].resize(nvtx,0.);
		sumtrv_.resize(ipair_+1); sumtrv_[ipair_].resize(nvtx,0.);
		sumweight_.resize(ipair_+1); sumweight_[ipair_].resize(nvtx,0.);
		ptmax_.resize(ipair_+1); ptmax_[ipair_].resize(nvtx,0.);
		nchthr_.resize(ipair_+1); nchthr_[ipair_].resize(nvtx,0.);
		nch_.resize(ipair_+1); nch_[ipair_].resize(nvtx,0.);
		vtxP_.resize(ipair_+1); vtxP_[ipair_].resize(nvtx,0.);
		tksPt_.resize(ipair_+1); tksPt_[ipair_].resize(nvtx, vector<float>(1));
		sphers_.resize(ipair_+1); sphers_[ipair_].resize(nvtx,TMatrixDSym(3));
		sumpr_.resize(ipair_+1); sumpr_[ipair_].resize(nvtx,0.);
		spher_.resize(ipair_+1); spher_[ipair_].resize(nvtx,0.);
		tspher_.resize(ipair_+1); tspher_[ipair_].resize(nvtx,0.);
		aplan_.resize(ipair_+1); aplan_[ipair_].resize(nvtx,0.);
		threejetC_.resize(ipair_+1); threejetC_[ipair_].resize(nvtx,0.);
		fourjetD_.resize(ipair_+1); fourjetD_[ipair_].resize(nvtx,0.);
		
		diphopt_.resize(ipair_+1); diphopt_[ipair_].resize(nvtx);
		diPhotonPt_.resize(ipair_+1); diPhotonPt_[ipair_].resize(nvtx);
		vtxPt_.resize(ipair_+1); vtxPt_[ipair_].resize(nvtx);
		ptvtx_.resize(ipair_+1); ptvtx_[ipair_].resize(nvtx);
		diPhotonPz_.resize(ipair_+1); diPhotonPz_[ipair_].resize(nvtx);
		
		acosA_.resize(ipair_+1); acosA_[ipair_].resize(nvtx);
		ptasym_.resize(ipair_+1); ptasym_[ipair_].resize(nvtx);
		
		ptmax3_.resize(ipair_+1); ptmax3_[ipair_].resize(nvtx);
		thrust_.resize(ipair_+1); thrust_[ipair_].resize(nvtx);
	
		ptratio_.resize(ipair_+1); ptratio_[ipair_].resize(nvtx);
		pzasym_.resize(ipair_+1); pzasym_[ipair_].resize(nvtx);
		
		awytwdasym_.resize(ipair_+1); awytwdasym_[ipair_].resize(nvtx);
	
		diPhoton_.resize(ipair_+1); diPhoton_[ipair_].resize(nvtx);
		for(int i=0; i<nvtx; ++i) {
			diPhoton_[ipair_][i] = 
				p1.p4(e.vtxx(i),e.vtxy(i),e.vtxz(i)) +
				p2.p4(e.vtxx(i),e.vtxy(i),e.vtxz(i));
		}
	}

	std::vector<unsigned short> vtxTracksBuf;
	std::vector<int> vtxTracksSizeBuf;
	if( ! e.hasVtxTracks() ) {
		vtxTracksBuf.resize(nvtx*e.ntracks());
		vtxTracksSizeBuf.resize(nvtx,0);
		for(int it=0; it<e.ntracks(); ++it) {
			int vid = e.tkVtxId(it);
			int & ntks = vtxTracksSizeBuf[vid];
			vtxTracksBuf[ vid*e.ntracks() + ntks ] = it;
			++ntks;
		}
	}
	
	preselection_.clear();
	// filling loop over vertexes
	for(int vid=0; vid<e.nvtx(); ++vid) {
		
		const unsigned short * vtxTracks = e.hasVtxTracks() ? e.vtxTracks(vid) : &vtxTracksBuf[ vid*e.ntracks() ];
		int ntracks = e.hasVtxTracks() ? e.vtxNTracks(vid) : vtxTracksSizeBuf[ vid ];
		//// std::cerr << "vertexAnalysis  vid " << vid << " ntracks " <<  ntracks << " : ";

		//calculating loop over tracks
		for(int it=0; it<ntracks; ++it) {
			
			unsigned short tid = vtxTracks[it];
			if( params_.fixTkIndex ) {
				if( tid == (unsigned short) -1 ) { tid=0; } 
				else { ++tid; }
			}
			if( tid >= e.ntracks() ) {
				++ninvalid_idxs_;
				//// std::cerr << "skipping [line" << __LINE__ << "] ";
				continue;
			}
			float tkWeight = e.tkWeight(tid,vid);			
			//// std::cerr << tid << ", "; 
			
			if( ( params_.highPurityOnly && !e.tkIsHighPurity(tid)  ) 
			    /// || fabs(e.tkd0(tid,vid)/e.tkd0Err(tid,vid)) > params_.maxD0Signif 
			    /// || fabs(e.tkdz(tid,vid)/e.tkdzErr(tid,vid)) > params_.maxDzSignif ) 
				) {
				//// std::cerr << "skipping [line" << __LINE__ << "] ";
				//// std::cerr << (params_.highPurityOnly && !e.tkIsHighPurity(tid)  )
				//// 	  << " " 
				//// 	  << (fabs(e.tkd0(tid,vid)/e.tkd0Err(tid,vid)) > params_.maxD0Signif )
				//// 	  << " " 
				//// 	  << (fabs(e.tkdz(tid,vid)/e.tkdzErr(tid,vid)) > params_.maxDzSignif) << std::endl;
				continue; 
			}
			

			const TVector3 tkPVec(e.tkpx(tid),e.tkpy(tid),e.tkpz(tid));
			assert(vid >= 0 && vid < nvtx);

			//// std::cerr << "( " << e.tkpx(tid) << " " << e.tkpy(tid) << " " << e.tkpz(tid) << ")";

			TVector2 tkPtVec = tkPVec.XYvector();
			float tkPt = tkPtVec.Mod();
			const float modpt = tkPt > e.tkPtErr(tid) ? tkPt - e.tkPtErr(tid)  : 0.;

			// correct track pt a la POG
			if( params_.rescaleTkPtByError ) {
				if( modpt == 0. ) { 
					/// std::cerr << "skipping [line" << __LINE__ << "] ";
					continue; 
				}
				const float ptcorr = modpt/tkPt;
				tkPtVec *= ptcorr;
				tkPt = modpt;
			}
			
			// vertex properties
			sumpt2_[ipair_][vid] += tkPtVec.Mod2();
			sumpt_[ipair_][vid] += tkPt;
			if(tkPt > params_.trackCountThr) nchthr_[ipair_][vid] += 1;
			nch_[ipair_][vid] += 1;
						
			// remove tracks in a cone around the photon direction to compute kinematic propeties
			if ( params_.removeTracksInCone ) {
			  float dr1 = tkPVec.DeltaR(p1.p4(e.vtxx(vid),e.vtxy(vid),e.vtxz(vid)).Vect()); 
			  float dr2 = tkPVec.DeltaR(p2.p4(e.vtxx(vid),e.vtxy(vid),e.vtxz(vid)).Vect()); 
			  if ( dr1 < params_.coneSize  || dr2 < params_.coneSize) {
				  //// std::cerr << "skipping [line" << __LINE__ << "] ";
				  continue;
			  }
			}
		

			ptbal_[ipair_][vid] -= tkPtVec * diPhoton_[ipair_][vid].Vect().XYvector().Unit();
			float cosTk = tkPVec.Unit() * diPhoton_[ipair_][vid].Vect().Unit();
			float val = tkPtVec.Mod();
			if ( cosTk < -0.5 )	{
				sumawy_[ipair_][vid] += val;
			} else if ( cosTk > 0.5 ){
				sumtwd_[ipair_][vid] += val;
			} else {
				sumtrv_[ipair_][vid] += val;
			}
			sumweight_[ipair_][vid] += tkWeight;
			vtxP_[ipair_][vid] += tkPVec;
			tksPt_[ipair_][vid].push_back(tkPt);
			
			Float_t p[3] = {0.,0.,0.};
			tkPVec.GetXYZ(p);
			for(int j=3; j--;){
				for(int k=j+1; k--;){
					(sphers_[ipair_][vid])[j][k] += pow(tkPVec.Mag(),spherPwr_-2.) * p[j]*p[k];
				}
			}
			sumpr_[ipair_][vid] += pow(tkPVec.Mag(),spherPwr_);
		}
		//// std::cerr << " nch_[ipair_][vid] " << nch_[ipair_][vid] << " sumpt2_[ipair_][vid] " << sumpt2_[ipair_][vid] << std::endl;
		
		sphers_[ipair_][vid] *= 1./sumpr_[ipair_][vid];
		
		TVectorD eigVals(3);
		eigVals = TMatrixDSymEigen(sphers_[ipair_][vid]).GetEigenValues();

		spher_[ipair_][vid] = 1.5 * (eigVals[1]+eigVals[2]);
		tspher_[ipair_][vid] = 2. * eigVals[1] / (eigVals[0]+eigVals[1]);
		aplan_[ipair_][vid] = 1.5 * eigVals[2];

		threejetC_[ipair_][vid] = 3. * (eigVals[0]*eigVals[1] + eigVals[0]*eigVals[2] + eigVals[1]*eigVals[2]);
		fourjetD_[ipair_][vid] = 27. * eigVals[0]*eigVals[1]*eigVals[2];


		diPhotonPt_[ipair_][vid] = diPhoton_[ipair_][vid].Vect().XYvector();
		diphopt_[ipair_][vid]    = diPhotonPt_[ipair_][vid].Mod();
		vtxPt_[ipair_][vid]      = vtxP_[ipair_][vid].XYvector();
		ptvtx_[ipair_][vid]      = vtxPt_[ipair_][vid].Mod();
		diPhotonPz_[ipair_][vid]   = diPhoton_[ipair_][vid].Vect().Pz();
		
 		sort(tksPt_[ipair_][vid].begin(), tksPt_[ipair_][vid].end(), greater<float>());
		
		acosA_[ipair_][vid] =  	acos(vtxPt_[ipair_][vid].Unit() * diPhotonPt_[ipair_][vid].Unit());
		ptasym_[ipair_][vid] = 	(vtxPt_[ipair_][vid].Mod() - diPhotonPt_[ipair_][vid].Mod())/(vtxPt_[ipair_][vid].Mod() + diPhotonPt_[ipair_][vid].Mod());

		ptmax_ [ipair_][vid] = 	tksPt_[ipair_][vid][0];
		ptmax3_[ipair_][vid] = 	accumulate(tksPt_[ipair_][vid].begin(),tksPt_[ipair_][vid].begin() + min(tksPt_[ipair_][vid].size(),(size_t)3), 0.0) ;
		thrust_[ipair_][vid] = 	ptbal_[ipair_][vid]/sumpt_[ipair_][vid];
		
		ptratio_[ipair_][vid] = 	vtxPt_[ipair_][vid].Mod()/diPhotonPt_[ipair_][vid].Mod();
		pzasym_[ipair_][vid] = 	fabs( (vtxP_[ipair_][vid].Pz() - diPhotonPz_[ipair_][vid])/(vtxP_[ipair_][vid].Pz() + diPhotonPz_[ipair_][vid]) );
		
		awytwdasym_[ipair_][vid] = (sumawy_[ipair_][vid]-sumtwd_[ipair_][vid])/(sumawy_[ipair_][vid]+sumtwd_[ipair_][vid]);
		
		preselection_.push_back(vid);
	}
}


// -------------------------------------------------------------------------------------------------------------------------------------------------------------
VertexInfoAdapter::~VertexInfoAdapter()
{}

// -------------------------------------------------------------------------------------------------------------------------------------------------------------
TupleVertexInfo::~TupleVertexInfo()
{}

// -------------------------------------------------------------------------------------------------------------------------------------------------------------
TupleVertexInfo::TupleVertexInfo(int nvtx, float * vtxx, float * vtxy, float * vtxz, 
				 int ntracks, float * tkpx, float * tkpy, float * tkpz,
				 float * tkPtErr, int * tkVtxId, float * tkWeight,
				 float * tkd0, float * tkd0Err, float * tkdz, float * tkdzErr,
				 bool * tkIsHighPurity
) :
	nvtx_(nvtx),
	vtxx_(vtxx),
	vtxy_(vtxy),
	vtxz_(vtxz),
	
	ntracks_(ntracks),
	tkpx_(tkpx),
	tkpy_(tkpy),
	tkpz_(tkpz),
	tkPtErr_(tkPtErr),
	tkVtxId_(tkVtxId),
	tkWeight_(tkWeight),
	tkd0_(tkd0),
	tkd0Err_(tkd0Err),
	tkdz_(tkdz),
	tkdzErr_(tkdzErr),

	tkIsHighPurity_(tkIsHighPurity)
{
}

// Local Variables:
// mode: c++       
// mode: sensitive 
// c-basic-offset: 8
// End:             
