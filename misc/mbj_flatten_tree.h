//////////////////////////////////////////////////////////
// Make flat ntuples from MBJ tree output files 
// (for the 2017 W/h/Z qqbb EWK SUSY analysis)
// Author: Joakim Olsson <joakim.olsson@cern.ch>
//////////////////////////////////////////////////////////

#ifndef mbj_flatten_tree_h
#define mbj_flatten_tree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TLorentzVector.h>
#include <TMath.h>

// Header file for the classes stored in the TTree if any.
#include "vector"

using namespace std;

class mbj_flatten_tree {
  public :
    TTree          *fChain;   //!pointer to the analyzed TTree or TChain
    Int_t           fCurrent; //!current Tree number in a TChain

    // Fixed size dimensions of array or collections stored in the TTree if any.

    // Declaration of leaf types
    ULong64_t       event_number;
    ULong64_t       run_number;
    Int_t           lumiblock_number;
    Float_t         average_interactions_per_crossing;
    Float_t         actual_interactions_per_crossing;
    Int_t           n_vtx;
    Float_t         primary_vertex_z;
    Int_t           process;
    Float_t         gen_filt_ht;
    Float_t         gen_filt_met;
    Int_t           muons_n;
    vector<float>   *muons_pt;
    vector<float>   *muons_phi;
    vector<float>   *muons_eta;
    vector<float>   *muons_e;
    vector<int>     *muons_passOR;
    vector<int>     *muons_isSignal;
    vector<int>     *muons_isCosmic;
    vector<int>     *muons_isBad;
    vector<double>  *muons_d0sig;
    vector<double>  *muons_z0;
    vector<int>     *muons_trgMatch_HLT_mu20_iloose_L1MU15;
    vector<int>     *muons_trgMatch_HLT_mu26_ivarmedium;
    vector<int>     *muons_trgMatch_HLT_mu50;
    Int_t           electrons_n;
    vector<float>   *electrons_pt;
    vector<float>   *electrons_phi;
    vector<float>   *electrons_eta;
    vector<float>   *electrons_e;
    vector<int>     *electrons_passOR;
    vector<int>     *electrons_isSignal;
    vector<int>     *electrons_passId;
    vector<double>  *electrons_d0sig;
    vector<double>  *electrons_z0;
    vector<int>     *electrons_trgMatch_HLT_e120_lhloose;
    vector<int>     *electrons_trgMatch_HLT_e140_lhloose_nod0;
    vector<int>     *electrons_trgMatch_HLT_e24_lhmedium_L1EM20VH;
    vector<int>     *electrons_trgMatch_HLT_e26_lhtight_nod0_ivarloose;
    vector<int>     *electrons_trgMatch_HLT_e60_lhmedium;
    vector<int>     *electrons_trgMatch_HLT_e60_lhmedium_nod0;
    Int_t           jets_n;
    Int_t           bjets_n;
    Int_t           bjets_n_60;
    Int_t           bjets_n_70;
    Int_t           bjets_n_77;
    Int_t           bjets_n_85;
    vector<float>   *jets_pt;
    vector<float>   *jets_phi;
    vector<float>   *jets_eta;
    vector<float>   *jets_e;
    vector<float>   *jets_jvt;
    vector<int>     *jets_nTracks;
    vector<int>     *jets_truthLabel;
    vector<double>  *jets_btag_weight;
    vector<int>     *jets_isb_60;
    vector<int>     *jets_isb_70;
    vector<int>     *jets_isb_77;
    vector<int>     *jets_isb_85;
    vector<double>  *jets_btagEff_weight;
    Float_t         asymmetry;
    Float_t         ht;
    Float_t         ht_jets;
    Float_t         meff_incl;
    Float_t         meff_4j;
    Float_t         minv_4j;
    Float_t         mT_4j;
    Float_t         minv_2j;
    Float_t         mT_2j;
    Float_t         minv_bb;
    Float_t         mT_bb;
    Float_t         mct_bb;
    Float_t         mTb_min;
    Float_t         mTb_max;
    Float_t         minv_non_bb;
    Float_t         mT_non_bb;
    Float_t         mct_non_bb;
    Float_t         minv_bb_60;
    Float_t         mT_bb_60;
    Float_t         mct_bb_60;
    Float_t         mTb_min_60;
    Float_t         mTb_max_60;
    Float_t         minv_non_bb_60;
    Float_t         mT_non_bb_60;
    Float_t         mct_non_bb_60;
    Float_t         minv_bb_70;
    Float_t         mT_bb_70;
    Float_t         mct_bb_70;
    Float_t         mTb_min_70;
    Float_t         mTb_max_70;
    Float_t         minv_non_bb_70;
    Float_t         mT_non_bb_70;
    Float_t         mct_non_bb_70;
    Float_t         minv_bb_77;
    Float_t         mT_bb_77;
    Float_t         mct_bb_77;
    Float_t         mTb_min_77;
    Float_t         mTb_max_77;
    Float_t         minv_non_bb_77;
    Float_t         mT_non_bb_77;
    Float_t         mct_non_bb_77;
    Float_t         minv_bb_85;
    Float_t         mT_bb_85;
    Float_t         mct_bb_85;
    Float_t         mTb_min_85;
    Float_t         mTb_max_85;
    Float_t         minv_non_bb_85;
    Float_t         mT_non_bb_85;
    Float_t         mct_non_bb_85;
    Float_t         metcst;
    Float_t         metcst_phi;
    Float_t         mettst;
    Float_t         mettst_phi;
    Float_t         metsoft;
    Float_t         metsoft_phi;
    Float_t         mettrack;
    Float_t         mettrack_phi;
    Float_t         mettrack_met_dPhi;
    Float_t         dphi_min;
    Float_t         dphi_1jet;
    Float_t         dphi_sum4jet;
    Float_t         dphi_min_alljets;
    Int_t           pass_HLT_e120_lhloose;
    Int_t           pass_HLT_e140_lhloose_nod0;
    Int_t           pass_HLT_e24_lhmedium_L1EM20VH;
    Int_t           pass_HLT_e26_lhtight_nod0_ivarloose;
    Int_t           pass_HLT_e60_lhmedium;
    Int_t           pass_HLT_e60_lhmedium_nod0;
    Int_t           pass_HLT_mu20_iloose_L1MU15;
    Int_t           pass_HLT_mu26_ivarmedium;
    Int_t           pass_HLT_mu50;
    Int_t           pass_MET;
    Double_t        weight_WZ_2_2;
    Double_t        weight_btag;
    Double_t        weight_elec;
    Double_t        weight_elec_trigger;
    Double_t        weight_jvt;
    Double_t        weight_mc;
    Double_t        weight_muon;
    Double_t        weight_muon_trigger;
    Double_t        weight_pu;
    Double_t        weight_ttbar_NNLO;
    Double_t        weight_ttbar_NNLO_1L;

    Float_t         MJSum_ak10;
    Int_t           ak10_jets_n;
    vector<float>   *ak10_jets_pt;
    vector<float>   *ak10_jets_phi;
    vector<float>   *ak10_jets_eta;
    vector<float>   *ak10_jets_e;
    vector<float>   *ak10_jets_m;
    vector<float>   *ak10_jets_SPLIT12;
    vector<float>   *ak10_jets_SPLIT23;
    vector<float>   *ak10_jets_tau21;
    vector<float>   *ak10_jets_tau32;
    vector<float>   *ak10_jets_C2;
    vector<float>   *ak10_jets_D2;
    vector<float>   *ak10_jets_isTopLoose;
    vector<float>   *ak10_jets_isTopTight;
    vector<float>   *ak10_jets_isTopSmoothLoose;
    vector<float>   *ak10_jets_isTopSmoothTight;
    vector<int>     *ak10_jets_ghost_ak2_trk_n;
    vector<int>     *ak10_jets_assoc_ak4_n;
    vector<int>     *ak10_jets_assoc_ak4_btag_n;
    vector<vector<float> > *ak10_jets_assoc_ak4_pt;
    vector<vector<float> > *ak10_jets_assoc_ak4_eta;
    vector<vector<float> > *ak10_jets_assoc_ak4_phi;
    vector<vector<float> > *ak10_jets_assoc_ak4_e;
    vector<vector<int> > *ak10_jets_assoc_ak4_isb_60;
    vector<vector<int> > *ak10_jets_assoc_ak4_isb_70;
    vector<vector<int> > *ak10_jets_assoc_ak4_isb_77;
    vector<vector<int> > *ak10_jets_assoc_ak4_isb_85;
    Float_t         ak10_jets_dR01;
    Float_t         ak10_jets_dEta01;
    Float_t         ak10_jets_dPhi01;

    Float_t         MJSum_R08PT10;
    Int_t           rc_R08PT10_jets_n;
    vector<Int_t>   *rc_R08PT10_jets_nconst;
    vector<Int_t>   *rc_R08PT10_jets_nconst_btag;
    vector<Int_t>   *rc_R08PT10_jets_nconst_btag_60;
    vector<Int_t>   *rc_R08PT10_jets_nconst_btag_70;
    vector<Int_t>   *rc_R08PT10_jets_nconst_btag_77;
    vector<Int_t>   *rc_R08PT10_jets_nconst_btag_85;
    vector<float>   *rc_R08PT10_jets_pt;
    vector<float>   *rc_R08PT10_jets_phi;
    vector<float>   *rc_R08PT10_jets_eta;
    vector<float>   *rc_R08PT10_jets_e;
    vector<float>   *rc_R08PT10_jets_m;
    vector<float>   *rc_R08PT10_jets_SPLIT12;
    vector<float>   *rc_R08PT10_jets_SPLIT23;
    vector<float>   *rc_R08PT10_jets_tau21;
    vector<float>   *rc_R08PT10_jets_tau32;
    vector<float>   *rc_R08PT10_jets_C2;
    vector<float>   *rc_R08PT10_jets_D2;
    Float_t         rc_R08PT10_jets_dR01;
    Float_t         rc_R08PT10_jets_dEta01;
    Float_t         rc_R08PT10_jets_dPhi01;

    Float_t         MJSum_R10PT10;
    Int_t           rc_R10PT10_jets_n;
    vector<Int_t>   *rc_R10PT10_jets_nconst;
    vector<Int_t>   *rc_R10PT10_jets_nconst_btag;
    vector<Int_t>   *rc_R10PT10_jets_nconst_btag_60;
    vector<Int_t>   *rc_R10PT10_jets_nconst_btag_70;
    vector<Int_t>   *rc_R10PT10_jets_nconst_btag_77;
    vector<Int_t>   *rc_R10PT10_jets_nconst_btag_85;
    vector<float>   *rc_R10PT10_jets_pt;
    vector<float>   *rc_R10PT10_jets_phi;
    vector<float>   *rc_R10PT10_jets_eta;
    vector<float>   *rc_R10PT10_jets_e;
    vector<float>   *rc_R10PT10_jets_m;
    vector<float>   *rc_R10PT10_jets_SPLIT12;
    vector<float>   *rc_R10PT10_jets_SPLIT23;
    vector<float>   *rc_R10PT10_jets_tau21;
    vector<float>   *rc_R10PT10_jets_tau32;
    vector<float>   *rc_R10PT10_jets_C2;
    vector<float>   *rc_R10PT10_jets_D2;
    Float_t         rc_R10PT10_jets_dR01;
    Float_t         rc_R10PT10_jets_dEta01;
    Float_t         rc_R10PT10_jets_dPhi01;

    Float_t         MJSum_R12PT10;
    Int_t           rc_R12PT10_jets_n;
    vector<Int_t>   *rc_R12PT10_jets_nconst;
    vector<Int_t>   *rc_R12PT10_jets_nconst_btag;
    vector<Int_t>   *rc_R12PT10_jets_nconst_btag_60;
    vector<Int_t>   *rc_R12PT10_jets_nconst_btag_70;
    vector<Int_t>   *rc_R12PT10_jets_nconst_btag_77;
    vector<Int_t>   *rc_R12PT10_jets_nconst_btag_85;
    vector<float>   *rc_R12PT10_jets_pt;
    vector<float>   *rc_R12PT10_jets_phi;
    vector<float>   *rc_R12PT10_jets_eta;
    vector<float>   *rc_R12PT10_jets_e;
    vector<float>   *rc_R12PT10_jets_m;
    vector<float>   *rc_R12PT10_jets_SPLIT12;
    vector<float>   *rc_R12PT10_jets_SPLIT23;
    vector<float>   *rc_R12PT10_jets_tau21;
    vector<float>   *rc_R12PT10_jets_tau32;
    vector<float>   *rc_R12PT10_jets_C2;
    vector<float>   *rc_R12PT10_jets_D2;
    Float_t         rc_R12PT10_jets_dR01;
    Float_t         rc_R12PT10_jets_dEta01;
    Float_t         rc_R12PT10_jets_dPhi01;

    Float_t         MJSum_R15PT10;
    Int_t           rc_R15PT10_jets_n;
    vector<Int_t>   *rc_R15PT10_jets_nconst;
    vector<Int_t>   *rc_R15PT10_jets_nconst_btag;
    vector<Int_t>   *rc_R15PT10_jets_nconst_btag_60;
    vector<Int_t>   *rc_R15PT10_jets_nconst_btag_70;
    vector<Int_t>   *rc_R15PT10_jets_nconst_btag_77;
    vector<Int_t>   *rc_R15PT10_jets_nconst_btag_85;
    vector<float>   *rc_R15PT10_jets_pt;
    vector<float>   *rc_R15PT10_jets_phi;
    vector<float>   *rc_R15PT10_jets_eta;
    vector<float>   *rc_R15PT10_jets_e;
    vector<float>   *rc_R15PT10_jets_m;
    vector<float>   *rc_R15PT10_jets_SPLIT12;
    vector<float>   *rc_R15PT10_jets_SPLIT23;
    vector<float>   *rc_R15PT10_jets_tau21;
    vector<float>   *rc_R15PT10_jets_tau32;
    vector<float>   *rc_R15PT10_jets_C2;
    vector<float>   *rc_R15PT10_jets_D2;
    Float_t         rc_R15PT10_jets_dR01;
    Float_t         rc_R15PT10_jets_dEta01;
    Float_t         rc_R15PT10_jets_dPhi01;

    // Additional flat output variables
    Float_t         pt_jet_1;
    Float_t         pt_jet_2;
    Float_t         pt_jet_3;
    Float_t         pt_jet_4;

    Float_t         pt_bjet_1_60;
    Float_t         pt_bjet_2_60;
    Float_t         pt_bjet_3_60;
    Float_t         pt_bjet_4_60;
    Float_t         pt_bjet_1_70;
    Float_t         pt_bjet_2_70;
    Float_t         pt_bjet_3_70;
    Float_t         pt_bjet_4_70;
    Float_t         pt_bjet_1_77;
    Float_t         pt_bjet_2_77;
    Float_t         pt_bjet_3_77;
    Float_t         pt_bjet_4_77;
    Float_t         pt_bjet_1_85;
    Float_t         pt_bjet_2_85;
    Float_t         pt_bjet_3_85;
    Float_t         pt_bjet_4_85;

    Float_t         ak10_dphi_min;
    Float_t         ak10_dphi_1jet;
    Float_t         ak10_dphi_sum2jet;
    Float_t         ak10_dphi_min_alljets;
    Float_t         ak10_meff_2j;
    Float_t         ak10_meff_4j;
    Float_t         ak10_meff_nj;
    Float_t         ak10_mT_2j;
    Float_t         ak10_pt_jet_1;
    Float_t         ak10_pt_jet_2;
    Float_t         ak10_pt_jet_3;
    Float_t         ak10_pt_jet_4;
    Float_t         ak10_m_jet_1;
    Float_t         ak10_m_jet_2;
    Float_t         ak10_m_jet_3;
    Float_t         ak10_m_jet_4;
    Float_t         ak10_SPLIT12_jet_1;
    Float_t         ak10_SPLIT12_jet_2;
    Float_t         ak10_SPLIT12_jet_3;
    Float_t         ak10_SPLIT12_jet_4;
    Float_t         ak10_SPLIT23_jet_1;
    Float_t         ak10_SPLIT23_jet_2;
    Float_t         ak10_SPLIT23_jet_3;
    Float_t         ak10_SPLIT23_jet_4;
    Float_t         ak10_tau21_jet_1;
    Float_t         ak10_tau21_jet_2;
    Float_t         ak10_tau21_jet_3;
    Float_t         ak10_tau21_jet_4;
    Float_t         ak10_tau32_jet_1;
    Float_t         ak10_tau32_jet_2;
    Float_t         ak10_tau32_jet_3;
    Float_t         ak10_tau32_jet_4;
    Float_t         ak10_C2_jet_1;
    Float_t         ak10_C2_jet_2;
    Float_t         ak10_C2_jet_3;
    Float_t         ak10_C2_jet_4;
    Float_t         ak10_D2_jet_1;
    Float_t         ak10_D2_jet_2;
    Float_t         ak10_D2_jet_3;
    Float_t         ak10_D2_jet_4;
    Int_t           ak10_assoc_ak4_n_jet_1;
    Int_t           ak10_assoc_ak4_n_jet_2;
    Int_t           ak10_assoc_ak4_n_jet_3;
    Int_t           ak10_assoc_ak4_n_jet_4;
    Int_t           ak10_assoc_ak4_btag_n_jet_1;
    Int_t           ak10_assoc_ak4_btag_n_jet_2;
    Int_t           ak10_assoc_ak4_btag_n_jet_3;
    Int_t           ak10_assoc_ak4_btag_n_jet_4;
    Int_t           ak10_ghost_ak2_trk_n_jet_1;
    Int_t           ak10_ghost_ak2_trk_n_jet_2;
    Int_t           ak10_ghost_ak2_trk_n_jet_3;
    Int_t           ak10_ghost_ak2_trk_n_jet_4;

    Float_t ak10_pt_h;
    Float_t ak10_pt_W;
    Float_t ak10_m_h;
    Float_t ak10_m_W;
    Float_t ak10_SPLIT12_h;
    Float_t ak10_SPLIT12_W;
    Float_t ak10_SPLIT23_h;
    Float_t ak10_SPLIT23_W;
    Float_t ak10_tau21_h;
    Float_t ak10_tau21_W;
    Float_t ak10_tau32_h;
    Float_t ak10_tau32_W;
    Float_t ak10_C2_h;
    Float_t ak10_C2_W;
    Float_t ak10_D2_h;
    Float_t ak10_D2_W;
    Float_t ak10_dR_Wh;
    Float_t ak10_dEta_Wh;
    Float_t ak10_dPhi_Wh;
    Int_t ak10_assoc_ak4_n_h;
    Int_t ak10_assoc_ak4_n_W;
    Int_t ak10_assoc_ak4_btag_n_h;
    Int_t ak10_assoc_ak4_btag_n_W;
    Int_t ak10_ghost_ak2_trk_n_h;
    Int_t ak10_ghost_ak2_trk_n_W;

    Float_t         rc_R08PT10_dphi_min;
    Float_t         rc_R08PT10_dphi_1jet;
    Float_t         rc_R08PT10_dphi_sum2jet;
    Float_t         rc_R08PT10_dphi_min_alljets;
    Float_t         rc_R08PT10_meff_2j;
    Float_t         rc_R08PT10_meff_4j;
    Float_t         rc_R08PT10_meff_nj;
    Float_t         rc_R08PT10_mT_2j;
    Float_t         rc_R08PT10_pt_jet_1;
    Float_t         rc_R08PT10_pt_jet_2;
    Float_t         rc_R08PT10_pt_jet_3;
    Float_t         rc_R08PT10_pt_jet_4;
    Float_t         rc_R08PT10_m_jet_1;
    Float_t         rc_R08PT10_m_jet_2;
    Float_t         rc_R08PT10_m_jet_3;
    Float_t         rc_R08PT10_m_jet_4;
    Float_t         rc_R08PT10_SPLIT12_jet_1;
    Float_t         rc_R08PT10_SPLIT12_jet_2;
    Float_t         rc_R08PT10_SPLIT12_jet_3;
    Float_t         rc_R08PT10_SPLIT12_jet_4;
    Float_t         rc_R08PT10_SPLIT23_jet_1;
    Float_t         rc_R08PT10_SPLIT23_jet_2;
    Float_t         rc_R08PT10_SPLIT23_jet_3;
    Float_t         rc_R08PT10_SPLIT23_jet_4;
    Float_t         rc_R08PT10_tau21_jet_1;
    Float_t         rc_R08PT10_tau21_jet_2;
    Float_t         rc_R08PT10_tau21_jet_3;
    Float_t         rc_R08PT10_tau21_jet_4;
    Float_t         rc_R08PT10_tau32_jet_1;
    Float_t         rc_R08PT10_tau32_jet_2;
    Float_t         rc_R08PT10_tau32_jet_3;
    Float_t         rc_R08PT10_tau32_jet_4;
    Float_t         rc_R08PT10_C2_jet_1;
    Float_t         rc_R08PT10_C2_jet_2;
    Float_t         rc_R08PT10_C2_jet_3;
    Float_t         rc_R08PT10_C2_jet_4;
    Float_t         rc_R08PT10_D2_jet_1;
    Float_t         rc_R08PT10_D2_jet_2;
    Float_t         rc_R08PT10_D2_jet_3;
    Float_t         rc_R08PT10_D2_jet_4;
    Int_t           rc_R08PT10_nconst_jet_1;
    Int_t           rc_R08PT10_nconst_jet_2;
    Int_t           rc_R08PT10_nconst_jet_3;
    Int_t           rc_R08PT10_nconst_jet_4;
    Int_t           rc_R08PT10_nconst_btag_jet_1;
    Int_t           rc_R08PT10_nconst_btag_jet_2;
    Int_t           rc_R08PT10_nconst_btag_jet_3;
    Int_t           rc_R08PT10_nconst_btag_jet_4;
    Int_t           rc_R08PT10_nconst_btag_60_jet_1;
    Int_t           rc_R08PT10_nconst_btag_60_jet_2;
    Int_t           rc_R08PT10_nconst_btag_60_jet_3;
    Int_t           rc_R08PT10_nconst_btag_60_jet_4;
    Int_t           rc_R08PT10_nconst_btag_70_jet_1;
    Int_t           rc_R08PT10_nconst_btag_70_jet_2;
    Int_t           rc_R08PT10_nconst_btag_70_jet_3;
    Int_t           rc_R08PT10_nconst_btag_70_jet_4;
    Int_t           rc_R08PT10_nconst_btag_77_jet_1;
    Int_t           rc_R08PT10_nconst_btag_77_jet_2;
    Int_t           rc_R08PT10_nconst_btag_77_jet_3;
    Int_t           rc_R08PT10_nconst_btag_77_jet_4;
    Int_t           rc_R08PT10_nconst_btag_85_jet_1;
    Int_t           rc_R08PT10_nconst_btag_85_jet_2;
    Int_t           rc_R08PT10_nconst_btag_85_jet_3;
    Int_t           rc_R08PT10_nconst_btag_85_jet_4;

    Float_t rc_R08PT10_pt_h;
    Float_t rc_R08PT10_pt_W;
    Float_t rc_R08PT10_m_h;
    Float_t rc_R08PT10_m_W;
    Float_t rc_R08PT10_SPLIT12_h;
    Float_t rc_R08PT10_SPLIT12_W;
    Float_t rc_R08PT10_SPLIT23_h;
    Float_t rc_R08PT10_SPLIT23_W;
    Float_t rc_R08PT10_tau21_h;
    Float_t rc_R08PT10_tau21_W;
    Float_t rc_R08PT10_tau32_h;
    Float_t rc_R08PT10_tau32_W;
    Float_t rc_R08PT10_C2_h;
    Float_t rc_R08PT10_C2_W;
    Float_t rc_R08PT10_D2_h;
    Float_t rc_R08PT10_D2_W;
    Float_t rc_R08PT10_dR_Wh;
    Float_t rc_R08PT10_dEta_Wh;
    Float_t rc_R08PT10_dPhi_Wh;
    Int_t rc_R08PT10_nconst_h;
    Int_t rc_R08PT10_nconst_W;
    Int_t rc_R08PT10_nconst_btag_h;
    Int_t rc_R08PT10_nconst_btag_W;
    Int_t rc_R08PT10_nconst_btag_60_h;
    Int_t rc_R08PT10_nconst_btag_60_W;
    Int_t rc_R08PT10_nconst_btag_70_h;
    Int_t rc_R08PT10_nconst_btag_70_W;
    Int_t rc_R08PT10_nconst_btag_77_h;
    Int_t rc_R08PT10_nconst_btag_77_W;
    Int_t rc_R08PT10_nconst_btag_85_h;
    Int_t rc_R08PT10_nconst_btag_85_W;

    Float_t         rc_R10PT10_dphi_min;
    Float_t         rc_R10PT10_dphi_1jet;
    Float_t         rc_R10PT10_dphi_sum2jet;
    Float_t         rc_R10PT10_dphi_min_alljets;
    Float_t         rc_R10PT10_meff_2j;
    Float_t         rc_R10PT10_meff_4j;
    Float_t         rc_R10PT10_meff_nj;
    Float_t         rc_R10PT10_mT_2j;
    Float_t         rc_R10PT10_pt_jet_1;
    Float_t         rc_R10PT10_pt_jet_2;
    Float_t         rc_R10PT10_pt_jet_3;
    Float_t         rc_R10PT10_pt_jet_4;
    Float_t         rc_R10PT10_m_jet_1;
    Float_t         rc_R10PT10_m_jet_2;
    Float_t         rc_R10PT10_m_jet_3;
    Float_t         rc_R10PT10_m_jet_4;
    Float_t         rc_R10PT10_SPLIT12_jet_1;
    Float_t         rc_R10PT10_SPLIT12_jet_2;
    Float_t         rc_R10PT10_SPLIT12_jet_3;
    Float_t         rc_R10PT10_SPLIT12_jet_4;
    Float_t         rc_R10PT10_SPLIT23_jet_1;
    Float_t         rc_R10PT10_SPLIT23_jet_2;
    Float_t         rc_R10PT10_SPLIT23_jet_3;
    Float_t         rc_R10PT10_SPLIT23_jet_4;
    Float_t         rc_R10PT10_tau21_jet_1;
    Float_t         rc_R10PT10_tau21_jet_2;
    Float_t         rc_R10PT10_tau21_jet_3;
    Float_t         rc_R10PT10_tau21_jet_4;
    Float_t         rc_R10PT10_tau32_jet_1;
    Float_t         rc_R10PT10_tau32_jet_2;
    Float_t         rc_R10PT10_tau32_jet_3;
    Float_t         rc_R10PT10_tau32_jet_4;
    Float_t         rc_R10PT10_C2_jet_1;
    Float_t         rc_R10PT10_C2_jet_2;
    Float_t         rc_R10PT10_C2_jet_3;
    Float_t         rc_R10PT10_C2_jet_4;
    Float_t         rc_R10PT10_D2_jet_1;
    Float_t         rc_R10PT10_D2_jet_2;
    Float_t         rc_R10PT10_D2_jet_3;
    Float_t         rc_R10PT10_D2_jet_4;
    Int_t           rc_R10PT10_nconst_jet_1;
    Int_t           rc_R10PT10_nconst_jet_2;
    Int_t           rc_R10PT10_nconst_jet_3;
    Int_t           rc_R10PT10_nconst_jet_4;
    Int_t           rc_R10PT10_nconst_btag_jet_1;
    Int_t           rc_R10PT10_nconst_btag_jet_2;
    Int_t           rc_R10PT10_nconst_btag_jet_3;
    Int_t           rc_R10PT10_nconst_btag_jet_4;
    Int_t           rc_R10PT10_nconst_btag_60_jet_1;
    Int_t           rc_R10PT10_nconst_btag_60_jet_2;
    Int_t           rc_R10PT10_nconst_btag_60_jet_3;
    Int_t           rc_R10PT10_nconst_btag_60_jet_4;
    Int_t           rc_R10PT10_nconst_btag_70_jet_1;
    Int_t           rc_R10PT10_nconst_btag_70_jet_2;
    Int_t           rc_R10PT10_nconst_btag_70_jet_3;
    Int_t           rc_R10PT10_nconst_btag_70_jet_4;
    Int_t           rc_R10PT10_nconst_btag_77_jet_1;
    Int_t           rc_R10PT10_nconst_btag_77_jet_2;
    Int_t           rc_R10PT10_nconst_btag_77_jet_3;
    Int_t           rc_R10PT10_nconst_btag_77_jet_4;
    Int_t           rc_R10PT10_nconst_btag_85_jet_1;
    Int_t           rc_R10PT10_nconst_btag_85_jet_2;
    Int_t           rc_R10PT10_nconst_btag_85_jet_3;
    Int_t           rc_R10PT10_nconst_btag_85_jet_4;

    Float_t rc_R10PT10_pt_h;
    Float_t rc_R10PT10_pt_W;
    Float_t rc_R10PT10_m_h;
    Float_t rc_R10PT10_m_W;
    Float_t rc_R10PT10_SPLIT12_h;
    Float_t rc_R10PT10_SPLIT12_W;
    Float_t rc_R10PT10_SPLIT23_h;
    Float_t rc_R10PT10_SPLIT23_W;
    Float_t rc_R10PT10_tau21_h;
    Float_t rc_R10PT10_tau21_W;
    Float_t rc_R10PT10_tau32_h;
    Float_t rc_R10PT10_tau32_W;
    Float_t rc_R10PT10_C2_h;
    Float_t rc_R10PT10_C2_W;
    Float_t rc_R10PT10_D2_h;
    Float_t rc_R10PT10_D2_W;
    Float_t rc_R10PT10_dR_Wh;
    Float_t rc_R10PT10_dEta_Wh;
    Float_t rc_R10PT10_dPhi_Wh;
    Int_t rc_R10PT10_nconst_h;
    Int_t rc_R10PT10_nconst_W;
    Int_t rc_R10PT10_nconst_btag_h;
    Int_t rc_R10PT10_nconst_btag_W;
    Int_t rc_R10PT10_nconst_btag_60_h;
    Int_t rc_R10PT10_nconst_btag_60_W;
    Int_t rc_R10PT10_nconst_btag_70_h;
    Int_t rc_R10PT10_nconst_btag_70_W;
    Int_t rc_R10PT10_nconst_btag_77_h;
    Int_t rc_R10PT10_nconst_btag_77_W;
    Int_t rc_R10PT10_nconst_btag_85_h;
    Int_t rc_R10PT10_nconst_btag_85_W;

    Float_t         rc_R12PT10_dphi_min;
    Float_t         rc_R12PT10_dphi_1jet;
    Float_t         rc_R12PT10_dphi_sum2jet;
    Float_t         rc_R12PT10_dphi_min_alljets;
    Float_t         rc_R12PT10_meff_2j;
    Float_t         rc_R12PT10_meff_4j;
    Float_t         rc_R12PT10_meff_nj;
    Float_t         rc_R12PT10_mT_2j;
    Float_t         rc_R12PT10_pt_jet_1;
    Float_t         rc_R12PT10_pt_jet_2;
    Float_t         rc_R12PT10_pt_jet_3;
    Float_t         rc_R12PT10_pt_jet_4;
    Float_t         rc_R12PT10_m_jet_1;
    Float_t         rc_R12PT10_m_jet_2;
    Float_t         rc_R12PT10_m_jet_3;
    Float_t         rc_R12PT10_m_jet_4;
    Float_t         rc_R12PT10_SPLIT12_jet_1;
    Float_t         rc_R12PT10_SPLIT12_jet_2;
    Float_t         rc_R12PT10_SPLIT12_jet_3;
    Float_t         rc_R12PT10_SPLIT12_jet_4;
    Float_t         rc_R12PT10_SPLIT23_jet_1;
    Float_t         rc_R12PT10_SPLIT23_jet_2;
    Float_t         rc_R12PT10_SPLIT23_jet_3;
    Float_t         rc_R12PT10_SPLIT23_jet_4;
    Float_t         rc_R12PT10_tau21_jet_1;
    Float_t         rc_R12PT10_tau21_jet_2;
    Float_t         rc_R12PT10_tau21_jet_3;
    Float_t         rc_R12PT10_tau21_jet_4;
    Float_t         rc_R12PT10_tau32_jet_1;
    Float_t         rc_R12PT10_tau32_jet_2;
    Float_t         rc_R12PT10_tau32_jet_3;
    Float_t         rc_R12PT10_tau32_jet_4;
    Float_t         rc_R12PT10_C2_jet_1;
    Float_t         rc_R12PT10_C2_jet_2;
    Float_t         rc_R12PT10_C2_jet_3;
    Float_t         rc_R12PT10_C2_jet_4;
    Float_t         rc_R12PT10_D2_jet_1;
    Float_t         rc_R12PT10_D2_jet_2;
    Float_t         rc_R12PT10_D2_jet_3;
    Float_t         rc_R12PT10_D2_jet_4;
    Int_t           rc_R12PT10_nconst_jet_1;
    Int_t           rc_R12PT10_nconst_jet_2;
    Int_t           rc_R12PT10_nconst_jet_3;
    Int_t           rc_R12PT10_nconst_jet_4;
    Int_t           rc_R12PT10_nconst_btag_jet_1;
    Int_t           rc_R12PT10_nconst_btag_jet_2;
    Int_t           rc_R12PT10_nconst_btag_jet_3;
    Int_t           rc_R12PT10_nconst_btag_jet_4;
    Int_t           rc_R12PT10_nconst_btag_60_jet_1;
    Int_t           rc_R12PT10_nconst_btag_60_jet_2;
    Int_t           rc_R12PT10_nconst_btag_60_jet_3;
    Int_t           rc_R12PT10_nconst_btag_60_jet_4;
    Int_t           rc_R12PT10_nconst_btag_70_jet_1;
    Int_t           rc_R12PT10_nconst_btag_70_jet_2;
    Int_t           rc_R12PT10_nconst_btag_70_jet_3;
    Int_t           rc_R12PT10_nconst_btag_70_jet_4;
    Int_t           rc_R12PT10_nconst_btag_77_jet_1;
    Int_t           rc_R12PT10_nconst_btag_77_jet_2;
    Int_t           rc_R12PT10_nconst_btag_77_jet_3;
    Int_t           rc_R12PT10_nconst_btag_77_jet_4;
    Int_t           rc_R12PT10_nconst_btag_85_jet_1;
    Int_t           rc_R12PT10_nconst_btag_85_jet_2;
    Int_t           rc_R12PT10_nconst_btag_85_jet_3;
    Int_t           rc_R12PT10_nconst_btag_85_jet_4;

    Float_t rc_R12PT10_pt_h;
    Float_t rc_R12PT10_pt_W;
    Float_t rc_R12PT10_m_h;
    Float_t rc_R12PT10_m_W;
    Float_t rc_R12PT10_SPLIT12_h;
    Float_t rc_R12PT10_SPLIT12_W;
    Float_t rc_R12PT10_SPLIT23_h;
    Float_t rc_R12PT10_SPLIT23_W;
    Float_t rc_R12PT10_tau21_h;
    Float_t rc_R12PT10_tau21_W;
    Float_t rc_R12PT10_tau32_h;
    Float_t rc_R12PT10_tau32_W;
    Float_t rc_R12PT10_C2_h;
    Float_t rc_R12PT10_C2_W;
    Float_t rc_R12PT10_D2_h;
    Float_t rc_R12PT10_D2_W;
    Float_t rc_R12PT10_dR_Wh;
    Float_t rc_R12PT10_dEta_Wh;
    Float_t rc_R12PT10_dPhi_Wh;
    Int_t rc_R12PT10_nconst_h;
    Int_t rc_R12PT10_nconst_W;
    Int_t rc_R12PT10_nconst_btag_h;
    Int_t rc_R12PT10_nconst_btag_W;
    Int_t rc_R12PT10_nconst_btag_60_h;
    Int_t rc_R12PT10_nconst_btag_60_W;
    Int_t rc_R12PT10_nconst_btag_70_h;
    Int_t rc_R12PT10_nconst_btag_70_W;
    Int_t rc_R12PT10_nconst_btag_77_h;
    Int_t rc_R12PT10_nconst_btag_77_W;
    Int_t rc_R12PT10_nconst_btag_85_h;
    Int_t rc_R12PT10_nconst_btag_85_W;

    Float_t         rc_R15PT10_dphi_min;
    Float_t         rc_R15PT10_dphi_1jet;
    Float_t         rc_R15PT10_dphi_sum2jet;
    Float_t         rc_R15PT10_dphi_min_alljets;
    Float_t         rc_R15PT10_meff_2j;
    Float_t         rc_R15PT10_meff_4j;
    Float_t         rc_R15PT10_meff_nj;
    Float_t         rc_R15PT10_mT_2j;
    Float_t         rc_R15PT10_pt_jet_1;
    Float_t         rc_R15PT10_pt_jet_2;
    Float_t         rc_R15PT10_pt_jet_3;
    Float_t         rc_R15PT10_pt_jet_4;
    Float_t         rc_R15PT10_m_jet_1;
    Float_t         rc_R15PT10_m_jet_2;
    Float_t         rc_R15PT10_m_jet_3;
    Float_t         rc_R15PT10_m_jet_4;
    Float_t         rc_R15PT10_SPLIT12_jet_1;
    Float_t         rc_R15PT10_SPLIT12_jet_2;
    Float_t         rc_R15PT10_SPLIT12_jet_3;
    Float_t         rc_R15PT10_SPLIT12_jet_4;
    Float_t         rc_R15PT10_SPLIT23_jet_1;
    Float_t         rc_R15PT10_SPLIT23_jet_2;
    Float_t         rc_R15PT10_SPLIT23_jet_3;
    Float_t         rc_R15PT10_SPLIT23_jet_4;
    Float_t         rc_R15PT10_tau21_jet_1;
    Float_t         rc_R15PT10_tau21_jet_2;
    Float_t         rc_R15PT10_tau21_jet_3;
    Float_t         rc_R15PT10_tau21_jet_4;
    Float_t         rc_R15PT10_tau32_jet_1;
    Float_t         rc_R15PT10_tau32_jet_2;
    Float_t         rc_R15PT10_tau32_jet_3;
    Float_t         rc_R15PT10_tau32_jet_4;
    Float_t         rc_R15PT10_C2_jet_1;
    Float_t         rc_R15PT10_C2_jet_2;
    Float_t         rc_R15PT10_C2_jet_3;
    Float_t         rc_R15PT10_C2_jet_4;
    Float_t         rc_R15PT10_D2_jet_1;
    Float_t         rc_R15PT10_D2_jet_2;
    Float_t         rc_R15PT10_D2_jet_3;
    Float_t         rc_R15PT10_D2_jet_4;
    Int_t           rc_R15PT10_nconst_jet_1;
    Int_t           rc_R15PT10_nconst_jet_2;
    Int_t           rc_R15PT10_nconst_jet_3;
    Int_t           rc_R15PT10_nconst_jet_4;
    Int_t           rc_R15PT10_nconst_btag_jet_1;
    Int_t           rc_R15PT10_nconst_btag_jet_2;
    Int_t           rc_R15PT10_nconst_btag_jet_3;
    Int_t           rc_R15PT10_nconst_btag_jet_4;
    Int_t           rc_R15PT10_nconst_btag_60_jet_1;
    Int_t           rc_R15PT10_nconst_btag_60_jet_2;
    Int_t           rc_R15PT10_nconst_btag_60_jet_3;
    Int_t           rc_R15PT10_nconst_btag_60_jet_4;
    Int_t           rc_R15PT10_nconst_btag_70_jet_1;
    Int_t           rc_R15PT10_nconst_btag_70_jet_2;
    Int_t           rc_R15PT10_nconst_btag_70_jet_3;
    Int_t           rc_R15PT10_nconst_btag_70_jet_4;
    Int_t           rc_R15PT10_nconst_btag_77_jet_1;
    Int_t           rc_R15PT10_nconst_btag_77_jet_2;
    Int_t           rc_R15PT10_nconst_btag_77_jet_3;
    Int_t           rc_R15PT10_nconst_btag_77_jet_4;
    Int_t           rc_R15PT10_nconst_btag_85_jet_1;
    Int_t           rc_R15PT10_nconst_btag_85_jet_2;
    Int_t           rc_R15PT10_nconst_btag_85_jet_3;
    Int_t           rc_R15PT10_nconst_btag_85_jet_4;

    Float_t rc_R15PT10_pt_h;
    Float_t rc_R15PT10_pt_W;
    Float_t rc_R15PT10_m_h;
    Float_t rc_R15PT10_m_W;
    Float_t rc_R15PT10_SPLIT12_h;
    Float_t rc_R15PT10_SPLIT12_W;
    Float_t rc_R15PT10_SPLIT23_h;
    Float_t rc_R15PT10_SPLIT23_W;
    Float_t rc_R15PT10_tau21_h;
    Float_t rc_R15PT10_tau21_W;
    Float_t rc_R15PT10_tau32_h;
    Float_t rc_R15PT10_tau32_W;
    Float_t rc_R15PT10_C2_h;
    Float_t rc_R15PT10_C2_W;
    Float_t rc_R15PT10_D2_h;
    Float_t rc_R15PT10_D2_W;
    Float_t rc_R15PT10_dR_Wh;
    Float_t rc_R15PT10_dEta_Wh;
    Float_t rc_R15PT10_dPhi_Wh;
    Int_t rc_R15PT10_nconst_h;
    Int_t rc_R15PT10_nconst_W;
    Int_t rc_R15PT10_nconst_btag_h;
    Int_t rc_R15PT10_nconst_btag_W;
    Int_t rc_R15PT10_nconst_btag_60_h;
    Int_t rc_R15PT10_nconst_btag_60_W;
    Int_t rc_R15PT10_nconst_btag_70_h;
    Int_t rc_R15PT10_nconst_btag_70_W;
    Int_t rc_R15PT10_nconst_btag_77_h;
    Int_t rc_R15PT10_nconst_btag_77_W;
    Int_t rc_R15PT10_nconst_btag_85_h;
    Int_t rc_R15PT10_nconst_btag_85_W;

    // List of branches
    TBranch        *b_event_number;   //!
    TBranch        *b_run_number;   //!
    TBranch        *b_lumiblock_number;   //!
    TBranch        *b_average_interactions_per_crossing;   //!
    TBranch        *b_actual_interactions_per_crossing;   //!
    TBranch        *b_n_vtx;   //!
    TBranch        *b_primary_vertex_z;   //!
    TBranch        *b_process;   //!
    TBranch        *b_gen_filt_ht;   //!
    TBranch        *b_gen_filt_met;   //!
    TBranch        *b_muons_n;   //!
    TBranch        *b_muons_pt;   //!
    TBranch        *b_muons_phi;   //!
    TBranch        *b_muons_eta;   //!
    TBranch        *b_muons_e;   //!
    TBranch        *b_muons_passOR;   //!
    TBranch        *b_muons_isSignal;   //!
    TBranch        *b_muons_isCosmic;   //!
    TBranch        *b_muons_isBad;   //!
    TBranch        *b_muons_d0sig;   //!
    TBranch        *b_muons_z0;   //!
    TBranch        *b_muons_trgMatch_HLT_mu20_iloose_L1MU15;   //!
    TBranch        *b_muons_trgMatch_HLT_mu26_ivarmedium;   //!
    TBranch        *b_muons_trgMatch_HLT_mu50;   //!
    TBranch        *b_electrons_n;   //!
    TBranch        *b_electrons_pt;   //!
    TBranch        *b_electrons_phi;   //!
    TBranch        *b_electrons_eta;   //!
    TBranch        *b_electrons_e;   //!
    TBranch        *b_electrons_passOR;   //!
    TBranch        *b_electrons_isSignal;   //!
    TBranch        *b_electrons_passId;   //!
    TBranch        *b_electrons_d0sig;   //!
    TBranch        *b_electrons_z0;   //!
    TBranch        *b_electrons_trgMatch_HLT_e120_lhloose;   //!
    TBranch        *b_electrons_trgMatch_HLT_e140_lhloose_nod0;   //!
    TBranch        *b_electrons_trgMatch_HLT_e24_lhmedium_L1EM20VH;   //!
    TBranch        *b_electrons_trgMatch_HLT_e26_lhtight_nod0_ivarloose;   //!
    TBranch        *b_electrons_trgMatch_HLT_e60_lhmedium;   //!
    TBranch        *b_electrons_trgMatch_HLT_e60_lhmedium_nod0;   //!
    TBranch        *b_jets_n;   //!
    TBranch        *b_bjets_n;   //!
    TBranch        *b_bjets_n_60;   //!
    TBranch        *b_bjets_n_70;   //!
    TBranch        *b_bjets_n_77;   //!
    TBranch        *b_bjets_n_85;   //!
    TBranch        *b_jets_pt;   //!
    TBranch        *b_jets_phi;   //!
    TBranch        *b_jets_eta;   //!
    TBranch        *b_jets_e;   //!
    TBranch        *b_jets_jvt;   //!
    TBranch        *b_jets_nTracks;   //!
    TBranch        *b_jets_truthLabel;   //!
    TBranch        *b_jets_btag_weight;   //!
    TBranch        *b_jets_isb_60;   //!
    TBranch        *b_jets_isb_70;   //!
    TBranch        *b_jets_isb_77;   //!
    TBranch        *b_jets_isb_85;   //!
    TBranch        *b_jets_btagEff_weight;   //!
    TBranch        *b_asymmetry;   //!
    TBranch        *b_ht;   //!
    TBranch        *b_ht_jets;   //!
    TBranch        *b_meff_incl;   //!
    TBranch        *b_meff_4j;   //!
    TBranch        *b_minv_4j;   //!
    TBranch        *b_mT_4j;   //!
    TBranch        *b_minv_2j;   //!
    TBranch        *b_mT_2j;   //!
    TBranch        *b_minv_bb;   //!
    TBranch        *b_mT_bb;   //!
    TBranch        *b_mct_bb;   //!
    TBranch        *b_mTb_min;   //!
    TBranch        *b_mTb_max;   //!
    TBranch        *b_minv_non_bb;   //!
    TBranch        *b_mT_non_bb;   //!
    TBranch        *b_mct_non_bb;   //!
    TBranch        *b_minv_bb_60;   //!
    TBranch        *b_mT_bb_60;   //!
    TBranch        *b_mct_bb_60;   //!
    TBranch        *b_mTb_min_60;   //!
    TBranch        *b_mTb_max_60;   //!
    TBranch        *b_minv_non_bb_60;   //!
    TBranch        *b_mT_non_bb_60;   //!
    TBranch        *b_mct_non_bb_60;   //!
    TBranch        *b_minv_bb_70;   //!
    TBranch        *b_mT_bb_70;   //!
    TBranch        *b_mct_bb_70;   //!
    TBranch        *b_mTb_min_70;   //!
    TBranch        *b_mTb_max_70;   //!
    TBranch        *b_minv_non_bb_70;   //!
    TBranch        *b_mT_non_bb_70;   //!
    TBranch        *b_mct_non_bb_70;   //!
    TBranch        *b_minv_bb_77;   //!
    TBranch        *b_mT_bb_77;   //!
    TBranch        *b_mct_bb_77;   //!
    TBranch        *b_mTb_min_77;   //!
    TBranch        *b_mTb_max_77;   //!
    TBranch        *b_minv_non_bb_77;   //!
    TBranch        *b_mT_non_bb_77;   //!
    TBranch        *b_mct_non_bb_77;   //!
    TBranch        *b_minv_bb_85;   //!
    TBranch        *b_mT_bb_85;   //!
    TBranch        *b_mct_bb_85;   //!
    TBranch        *b_mTb_min_85;   //!
    TBranch        *b_mTb_max_85;   //!
    TBranch        *b_minv_non_bb_85;   //!
    TBranch        *b_mT_non_bb_85;   //!
    TBranch        *b_mct_non_bb_85;   //!
    TBranch        *b_metcst;   //!
    TBranch        *b_metcst_phi;   //!
    TBranch        *b_mettst;   //!
    TBranch        *b_mettst_phi;   //!
    TBranch        *b_metsoft;   //!
    TBranch        *b_metsoft_phi;   //!
    TBranch        *b_mettrack;   //!
    TBranch        *b_mettrack_phi;   //!
    TBranch        *b_mettrack_met_dPhi;   //!
    TBranch        *b_dphi_min;   //!
    TBranch        *b_dphi_1jet;   //!
    TBranch        *b_dphi_sum4jet;   //!
    TBranch        *b_dphi_min_alljets;   //!
    TBranch        *b_pass_HLT_e120_lhloose;   //!
    TBranch        *b_pass_HLT_e140_lhloose_nod0;   //!
    TBranch        *b_pass_HLT_e24_lhmedium_L1EM20VH;   //!
    TBranch        *b_pass_HLT_e26_lhtight_nod0_ivarloose;   //!
    TBranch        *b_pass_HLT_e60_lhmedium;   //!
    TBranch        *b_pass_HLT_e60_lhmedium_nod0;   //!
    TBranch        *b_pass_HLT_mu20_iloose_L1MU15;   //!
    TBranch        *b_pass_HLT_mu26_ivarmedium;   //!
    TBranch        *b_pass_HLT_mu50;   //!
    TBranch        *b_pass_MET;   //!
    TBranch        *b_weight_WZ_2_2;   //!
    TBranch        *b_weight_btag;   //!
    TBranch        *b_weight_elec;   //!
    TBranch        *b_weight_elec_trigger;   //!
    TBranch        *b_weight_jvt;   //!
    TBranch        *b_weight_mc;   //!
    TBranch        *b_weight_muon;   //!
    TBranch        *b_weight_muon_trigger;   //!
    TBranch        *b_weight_pu;   //!
    TBranch        *b_weight_ttbar_NNLO;   //!
    TBranch        *b_weight_ttbar_NNLO_1L;   //!
    TBranch        *b_MJSum_ak10;   //!
    TBranch        *b_ak10_jets_n;   //!
    TBranch        *b_ak10_jets_pt;   //!
    TBranch        *b_ak10_jets_phi;   //!
    TBranch        *b_ak10_jets_eta;   //!
    TBranch        *b_ak10_jets_e;   //!
    TBranch        *b_ak10_jets_m;   //!
    TBranch        *b_ak10_jets_SPLIT12;   //!
    TBranch        *b_ak10_jets_SPLIT23;   //!
    TBranch        *b_ak10_jets_tau21;   //!
    TBranch        *b_ak10_jets_tau32;   //!
    TBranch        *b_ak10_jets_C2;   //!
    TBranch        *b_ak10_jets_D2;   //!
    TBranch        *b_ak10_jets_isTopLoose;   //!
    TBranch        *b_ak10_jets_isTopTight;   //!
    TBranch        *b_ak10_jets_isTopSmoothLoose;   //!
    TBranch        *b_ak10_jets_isTopSmoothTight;   //!
    TBranch        *b_ak10_jets_ghost_ak2_trk_n;   //!
    TBranch        *b_ak10_jets_assoc_ak4_n;   //!
    TBranch        *b_ak10_jets_assoc_ak4_btag_n;   //!
    TBranch        *b_ak10_jets_assoc_ak4_pt;   //!
    TBranch        *b_ak10_jets_assoc_ak4_eta;   //!
    TBranch        *b_ak10_jets_assoc_ak4_phi;   //!
    TBranch        *b_ak10_jets_assoc_ak4_e;   //!
    TBranch        *b_ak10_jets_assoc_ak4_isb_60;   //!
    TBranch        *b_ak10_jets_assoc_ak4_isb_70;   //!
    TBranch        *b_ak10_jets_assoc_ak4_isb_77;   //!
    TBranch        *b_ak10_jets_assoc_ak4_isb_85;   //!
    TBranch        *b_ak10_jets_dR01;   //!
    TBranch        *b_ak10_jets_dEta01;   //!
    TBranch        *b_ak10_jets_dPhi01;   //!

    TBranch        *b_MJSum_R08PT10;   //!
    TBranch        *b_rc_R08PT10_jets_n;   //!
    TBranch        *b_rc_R08PT10_jets_nconst;   //!
    TBranch        *b_rc_R08PT10_jets_nconst_btag;   //!
    TBranch        *b_rc_R08PT10_jets_nconst_btag_60;   //!
    TBranch        *b_rc_R08PT10_jets_nconst_btag_70;   //!
    TBranch        *b_rc_R08PT10_jets_nconst_btag_77;   //!
    TBranch        *b_rc_R08PT10_jets_nconst_btag_85;   //!
    TBranch        *b_rc_R08PT10_jets_pt;   //!
    TBranch        *b_rc_R08PT10_jets_phi;   //!
    TBranch        *b_rc_R08PT10_jets_eta;   //!
    TBranch        *b_rc_R08PT10_jets_e;   //!
    TBranch        *b_rc_R08PT10_jets_m;   //!
    TBranch        *b_rc_R08PT10_jets_SPLIT12;   //!
    TBranch        *b_rc_R08PT10_jets_SPLIT23;   //!
    TBranch        *b_rc_R08PT10_jets_tau21;   //!
    TBranch        *b_rc_R08PT10_jets_tau32;   //!
    TBranch        *b_rc_R08PT10_jets_C2;   //!
    TBranch        *b_rc_R08PT10_jets_D2;   //!
    TBranch        *b_rc_R08PT10_jets_dR01;   //!
    TBranch        *b_rc_R08PT10_jets_dEta01;   //!
    TBranch        *b_rc_R08PT10_jets_dPhi01;   //!

    TBranch        *b_MJSum_R10PT10;   //!
    TBranch        *b_rc_R10PT10_jets_n;   //!
    TBranch        *b_rc_R10PT10_jets_nconst;   //!
    TBranch        *b_rc_R10PT10_jets_nconst_btag;   //!
    TBranch        *b_rc_R10PT10_jets_nconst_btag_60;   //!
    TBranch        *b_rc_R10PT10_jets_nconst_btag_70;   //!
    TBranch        *b_rc_R10PT10_jets_nconst_btag_77;   //!
    TBranch        *b_rc_R10PT10_jets_nconst_btag_85;   //!
    TBranch        *b_rc_R10PT10_jets_pt;   //!
    TBranch        *b_rc_R10PT10_jets_phi;   //!
    TBranch        *b_rc_R10PT10_jets_eta;   //!
    TBranch        *b_rc_R10PT10_jets_e;   //!
    TBranch        *b_rc_R10PT10_jets_m;   //!
    TBranch        *b_rc_R10PT10_jets_SPLIT12;   //!
    TBranch        *b_rc_R10PT10_jets_SPLIT23;   //!
    TBranch        *b_rc_R10PT10_jets_tau21;   //!
    TBranch        *b_rc_R10PT10_jets_tau32;   //!
    TBranch        *b_rc_R10PT10_jets_C2;   //!
    TBranch        *b_rc_R10PT10_jets_D2;   //!
    TBranch        *b_rc_R10PT10_jets_dR01;   //!
    TBranch        *b_rc_R10PT10_jets_dEta01;   //!
    TBranch        *b_rc_R10PT10_jets_dPhi01;   //!

    TBranch        *b_MJSum_R12PT10;   //!
    TBranch        *b_rc_R12PT10_jets_n;   //!
    TBranch        *b_rc_R12PT10_jets_nconst;   //!
    TBranch        *b_rc_R12PT10_jets_nconst_btag;   //!
    TBranch        *b_rc_R12PT10_jets_nconst_btag_60;   //!
    TBranch        *b_rc_R12PT10_jets_nconst_btag_70;   //!
    TBranch        *b_rc_R12PT10_jets_nconst_btag_77;   //!
    TBranch        *b_rc_R12PT10_jets_nconst_btag_85;   //!
    TBranch        *b_rc_R12PT10_jets_pt;   //!
    TBranch        *b_rc_R12PT10_jets_phi;   //!
    TBranch        *b_rc_R12PT10_jets_eta;   //!
    TBranch        *b_rc_R12PT10_jets_e;   //!
    TBranch        *b_rc_R12PT10_jets_m;   //!
    TBranch        *b_rc_R12PT10_jets_SPLIT12;   //!
    TBranch        *b_rc_R12PT10_jets_SPLIT23;   //!
    TBranch        *b_rc_R12PT10_jets_tau21;   //!
    TBranch        *b_rc_R12PT10_jets_tau32;   //!
    TBranch        *b_rc_R12PT10_jets_C2;   //!
    TBranch        *b_rc_R12PT10_jets_D2;   //!
    TBranch        *b_rc_R12PT10_jets_dR01;   //!
    TBranch        *b_rc_R12PT10_jets_dEta01;   //!
    TBranch        *b_rc_R12PT10_jets_dPhi01;   //!

    TBranch        *b_MJSum_R15PT10;   //!
    TBranch        *b_rc_R15PT10_jets_n;   //!
    TBranch        *b_rc_R15PT10_jets_nconst;   //!
    TBranch        *b_rc_R15PT10_jets_nconst_btag;   //!
    TBranch        *b_rc_R15PT10_jets_nconst_btag_60;   //!
    TBranch        *b_rc_R15PT10_jets_nconst_btag_70;   //!
    TBranch        *b_rc_R15PT10_jets_nconst_btag_77;   //!
    TBranch        *b_rc_R15PT10_jets_nconst_btag_85;   //!
    TBranch        *b_rc_R15PT10_jets_pt;   //!
    TBranch        *b_rc_R15PT10_jets_phi;   //!
    TBranch        *b_rc_R15PT10_jets_eta;   //!
    TBranch        *b_rc_R15PT10_jets_e;   //!
    TBranch        *b_rc_R15PT10_jets_m;   //!
    TBranch        *b_rc_R15PT10_jets_SPLIT12;   //!
    TBranch        *b_rc_R15PT10_jets_SPLIT23;   //!
    TBranch        *b_rc_R15PT10_jets_tau21;   //!
    TBranch        *b_rc_R15PT10_jets_tau32;   //!
    TBranch        *b_rc_R15PT10_jets_C2;   //!
    TBranch        *b_rc_R15PT10_jets_D2;   //!
    TBranch        *b_rc_R15PT10_jets_dR01;   //!
    TBranch        *b_rc_R15PT10_jets_dEta01;   //!
    TBranch        *b_rc_R15PT10_jets_dPhi01;   //!

    mbj_flatten_tree(TTree *tree=0);
    virtual ~mbj_flatten_tree();
    // virtual Int_t    Cut(Long64_t entry);
    virtual Int_t    GetEntry(Long64_t entry);
    virtual Long64_t LoadTree(Long64_t entry);
    virtual void     Init(TTree *tree);
    virtual void     Loop(TFile *outFile=0);
    virtual Bool_t   Notify();
    virtual void     Show(Long64_t entry = -1);

    void InitOutTree(TTree *tree);
    void ResetOutTreeBranches();
};

#endif

#ifdef mbj_flatten_tree_cxx
mbj_flatten_tree::mbj_flatten_tree(TTree *tree) : fChain(0)
{
  // if parameter tree is not specified (or zero), connect the file
  // used to generate this class and read the Tree.
  if (tree == 0) {
    TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("user.jolsson.mc15_13TeV.000006.MGPy8EG_A14N23LO_C1N2_Wh_500p0_100p0_bbqq_J10.DAOD_SUSY10.20170322_2.3.4.4_EXT0.merged");
    if (!f || !f->IsOpen()) {
      f = new TFile("user.jolsson.mc15_13TeV.000006.MGPy8EG_A14N23LO_C1N2_Wh_500p0_100p0_bbqq_J10.DAOD_SUSY10.20170322_2.3.4.4_EXT0.merged");
    }
    f->GetObject("nominal",tree);

  }
  Init(tree);

}

mbj_flatten_tree::~mbj_flatten_tree()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t mbj_flatten_tree::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}
Long64_t mbj_flatten_tree::LoadTree(Long64_t entry)
{
  // Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (fChain->GetTreeNumber() != fCurrent) {
    fCurrent = fChain->GetTreeNumber();
    Notify();
  }
  return centry;
}

void mbj_flatten_tree::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  // Set object pointer
  muons_pt = 0;
  muons_phi = 0;
  muons_eta = 0;
  muons_e = 0;
  muons_passOR = 0;
  muons_isSignal = 0;
  muons_isCosmic = 0;
  muons_isBad = 0;
  muons_d0sig = 0;
  muons_z0 = 0;
  muons_trgMatch_HLT_mu20_iloose_L1MU15 = 0;
  muons_trgMatch_HLT_mu26_ivarmedium = 0;
  muons_trgMatch_HLT_mu50 = 0;
  electrons_pt = 0;
  electrons_phi = 0;
  electrons_eta = 0;
  electrons_e = 0;
  electrons_passOR = 0;
  electrons_isSignal = 0;
  electrons_passId = 0;
  electrons_d0sig = 0;
  electrons_z0 = 0;
  electrons_trgMatch_HLT_e120_lhloose = 0;
  electrons_trgMatch_HLT_e140_lhloose_nod0 = 0;
  electrons_trgMatch_HLT_e24_lhmedium_L1EM20VH = 0;
  electrons_trgMatch_HLT_e26_lhtight_nod0_ivarloose = 0;
  electrons_trgMatch_HLT_e60_lhmedium = 0;
  electrons_trgMatch_HLT_e60_lhmedium_nod0 = 0;
  jets_pt = 0;
  jets_phi = 0;
  jets_eta = 0;
  jets_e = 0;
  jets_jvt = 0;
  jets_nTracks = 0;
  jets_truthLabel = 0;
  jets_btag_weight = 0;
  jets_isb_60 = 0;
  jets_isb_70 = 0;
  jets_isb_77 = 0;
  jets_isb_85 = 0;
  jets_btagEff_weight = 0;
  ak10_jets_pt = 0;
  ak10_jets_phi = 0;
  ak10_jets_eta = 0;
  ak10_jets_e = 0;
  ak10_jets_m = 0;
  ak10_jets_SPLIT12 = 0;
  ak10_jets_SPLIT23 = 0;
  ak10_jets_tau21 = 0;
  ak10_jets_tau32 = 0;
  ak10_jets_C2 = 0;
  ak10_jets_D2 = 0;
  ak10_jets_isTopLoose = 0;
  ak10_jets_isTopTight = 0;
  ak10_jets_isTopSmoothLoose = 0;
  ak10_jets_isTopSmoothTight = 0;
  ak10_jets_ghost_ak2_trk_n = 0;
  ak10_jets_assoc_ak4_n = 0;
  ak10_jets_assoc_ak4_btag_n = 0;
  ak10_jets_assoc_ak4_pt = 0;
  ak10_jets_assoc_ak4_eta = 0;
  ak10_jets_assoc_ak4_phi = 0;
  ak10_jets_assoc_ak4_e = 0;
  ak10_jets_assoc_ak4_isb_60 = 0;
  ak10_jets_assoc_ak4_isb_70 = 0;
  ak10_jets_assoc_ak4_isb_77 = 0;
  ak10_jets_assoc_ak4_isb_85 = 0;
  rc_R08PT10_jets_nconst = 0;
  rc_R08PT10_jets_nconst_btag = 0;
  rc_R08PT10_jets_nconst_btag_60 = 0;
  rc_R08PT10_jets_nconst_btag_70 = 0;
  rc_R08PT10_jets_nconst_btag_77 = 0;
  rc_R08PT10_jets_nconst_btag_85 = 0;
  rc_R08PT10_jets_pt = 0;
  rc_R08PT10_jets_phi = 0;
  rc_R08PT10_jets_eta = 0;
  rc_R08PT10_jets_e = 0;
  rc_R08PT10_jets_m = 0;
  rc_R08PT10_jets_SPLIT12 = 0;
  rc_R08PT10_jets_SPLIT23 = 0;
  rc_R08PT10_jets_tau21 = 0;
  rc_R08PT10_jets_tau32 = 0;
  rc_R08PT10_jets_C2 = 0;
  rc_R08PT10_jets_D2 = 0;
  rc_R10PT10_jets_nconst = 0;
  rc_R10PT10_jets_nconst_btag = 0;
  rc_R10PT10_jets_nconst_btag_60 = 0;
  rc_R10PT10_jets_nconst_btag_70 = 0;
  rc_R10PT10_jets_nconst_btag_77 = 0;
  rc_R10PT10_jets_nconst_btag_85 = 0;
  rc_R10PT10_jets_pt = 0;
  rc_R10PT10_jets_phi = 0;
  rc_R10PT10_jets_eta = 0;
  rc_R10PT10_jets_e = 0;
  rc_R10PT10_jets_m = 0;
  rc_R10PT10_jets_SPLIT12 = 0;
  rc_R10PT10_jets_SPLIT23 = 0;
  rc_R10PT10_jets_tau21 = 0;
  rc_R10PT10_jets_tau32 = 0;
  rc_R10PT10_jets_C2 = 0;
  rc_R10PT10_jets_D2 = 0;
  rc_R12PT10_jets_nconst = 0;
  rc_R12PT10_jets_nconst_btag = 0;
  rc_R12PT10_jets_nconst_btag_60 = 0;
  rc_R12PT10_jets_nconst_btag_70 = 0;
  rc_R12PT10_jets_nconst_btag_77 = 0;
  rc_R12PT10_jets_nconst_btag_85 = 0;
  rc_R12PT10_jets_pt = 0;
  rc_R12PT10_jets_phi = 0;
  rc_R12PT10_jets_eta = 0;
  rc_R12PT10_jets_e = 0;
  rc_R12PT10_jets_m = 0;
  rc_R12PT10_jets_SPLIT12 = 0;
  rc_R12PT10_jets_SPLIT23 = 0;
  rc_R12PT10_jets_tau21 = 0;
  rc_R12PT10_jets_tau32 = 0;
  rc_R12PT10_jets_C2 = 0;
  rc_R12PT10_jets_D2 = 0;
  rc_R15PT10_jets_nconst = 0;
  rc_R15PT10_jets_nconst_btag = 0;
  rc_R15PT10_jets_nconst_btag_60 = 0;
  rc_R15PT10_jets_nconst_btag_70 = 0;
  rc_R15PT10_jets_nconst_btag_77 = 0;
  rc_R15PT10_jets_nconst_btag_85 = 0;
  rc_R15PT10_jets_pt = 0;
  rc_R15PT10_jets_phi = 0;
  rc_R15PT10_jets_eta = 0;
  rc_R15PT10_jets_e = 0;
  rc_R15PT10_jets_m = 0;
  rc_R15PT10_jets_SPLIT12 = 0;
  rc_R15PT10_jets_SPLIT23 = 0;
  rc_R15PT10_jets_tau21 = 0;
  rc_R15PT10_jets_tau32 = 0;
  rc_R15PT10_jets_C2 = 0;
  rc_R15PT10_jets_D2 = 0;
  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);

  fChain->SetBranchAddress("event_number", &event_number, &b_event_number);
  fChain->SetBranchAddress("run_number", &run_number, &b_run_number);
  fChain->SetBranchAddress("lumiblock_number", &lumiblock_number, &b_lumiblock_number);
  fChain->SetBranchAddress("average_interactions_per_crossing", &average_interactions_per_crossing, &b_average_interactions_per_crossing);
  fChain->SetBranchAddress("actual_interactions_per_crossing", &actual_interactions_per_crossing, &b_actual_interactions_per_crossing);
  fChain->SetBranchAddress("n_vtx", &n_vtx, &b_n_vtx);
  fChain->SetBranchAddress("primary_vertex_z", &primary_vertex_z, &b_primary_vertex_z);
  fChain->SetBranchAddress("process", &process, &b_process);
  fChain->SetBranchAddress("gen_filt_ht", &gen_filt_ht, &b_gen_filt_ht);
  fChain->SetBranchAddress("gen_filt_met", &gen_filt_met, &b_gen_filt_met);
  fChain->SetBranchAddress("muons_n", &muons_n, &b_muons_n);
  fChain->SetBranchAddress("muons_pt", &muons_pt, &b_muons_pt);
  fChain->SetBranchAddress("muons_phi", &muons_phi, &b_muons_phi);
  fChain->SetBranchAddress("muons_eta", &muons_eta, &b_muons_eta);
  fChain->SetBranchAddress("muons_e", &muons_e, &b_muons_e);
  fChain->SetBranchAddress("muons_passOR", &muons_passOR, &b_muons_passOR);
  fChain->SetBranchAddress("muons_isSignal", &muons_isSignal, &b_muons_isSignal);
  fChain->SetBranchAddress("muons_isCosmic", &muons_isCosmic, &b_muons_isCosmic);
  fChain->SetBranchAddress("muons_isBad", &muons_isBad, &b_muons_isBad);
  fChain->SetBranchAddress("muons_d0sig", &muons_d0sig, &b_muons_d0sig);
  fChain->SetBranchAddress("muons_z0", &muons_z0, &b_muons_z0);
  fChain->SetBranchAddress("muons_trgMatch_HLT_mu20_iloose_L1MU15", &muons_trgMatch_HLT_mu20_iloose_L1MU15, &b_muons_trgMatch_HLT_mu20_iloose_L1MU15);
  fChain->SetBranchAddress("muons_trgMatch_HLT_mu26_ivarmedium", &muons_trgMatch_HLT_mu26_ivarmedium, &b_muons_trgMatch_HLT_mu26_ivarmedium);
  fChain->SetBranchAddress("muons_trgMatch_HLT_mu50", &muons_trgMatch_HLT_mu50, &b_muons_trgMatch_HLT_mu50);
  fChain->SetBranchAddress("electrons_n", &electrons_n, &b_electrons_n);
  fChain->SetBranchAddress("electrons_pt", &electrons_pt, &b_electrons_pt);
  fChain->SetBranchAddress("electrons_phi", &electrons_phi, &b_electrons_phi);
  fChain->SetBranchAddress("electrons_eta", &electrons_eta, &b_electrons_eta);
  fChain->SetBranchAddress("electrons_e", &electrons_e, &b_electrons_e);
  fChain->SetBranchAddress("electrons_passOR", &electrons_passOR, &b_electrons_passOR);
  fChain->SetBranchAddress("electrons_isSignal", &electrons_isSignal, &b_electrons_isSignal);
  fChain->SetBranchAddress("electrons_passId", &electrons_passId, &b_electrons_passId);
  fChain->SetBranchAddress("electrons_d0sig", &electrons_d0sig, &b_electrons_d0sig);
  fChain->SetBranchAddress("electrons_z0", &electrons_z0, &b_electrons_z0);
  fChain->SetBranchAddress("electrons_trgMatch_HLT_e120_lhloose", &electrons_trgMatch_HLT_e120_lhloose, &b_electrons_trgMatch_HLT_e120_lhloose);
  fChain->SetBranchAddress("electrons_trgMatch_HLT_e140_lhloose_nod0", &electrons_trgMatch_HLT_e140_lhloose_nod0, &b_electrons_trgMatch_HLT_e140_lhloose_nod0);
  fChain->SetBranchAddress("electrons_trgMatch_HLT_e24_lhmedium_L1EM20VH", &electrons_trgMatch_HLT_e24_lhmedium_L1EM20VH, &b_electrons_trgMatch_HLT_e24_lhmedium_L1EM20VH);
  fChain->SetBranchAddress("electrons_trgMatch_HLT_e26_lhtight_nod0_ivarloose", &electrons_trgMatch_HLT_e26_lhtight_nod0_ivarloose, &b_electrons_trgMatch_HLT_e26_lhtight_nod0_ivarloose);
  fChain->SetBranchAddress("electrons_trgMatch_HLT_e60_lhmedium", &electrons_trgMatch_HLT_e60_lhmedium, &b_electrons_trgMatch_HLT_e60_lhmedium);
  fChain->SetBranchAddress("electrons_trgMatch_HLT_e60_lhmedium_nod0", &electrons_trgMatch_HLT_e60_lhmedium_nod0, &b_electrons_trgMatch_HLT_e60_lhmedium_nod0);
  fChain->SetBranchAddress("jets_n", &jets_n, &b_jets_n);
  fChain->SetBranchAddress("bjets_n", &bjets_n, &b_bjets_n);
  fChain->SetBranchAddress("bjets_n_60", &bjets_n_60, &b_bjets_n_60);
  fChain->SetBranchAddress("bjets_n_70", &bjets_n_70, &b_bjets_n_70);
  fChain->SetBranchAddress("bjets_n_77", &bjets_n_77, &b_bjets_n_77);
  fChain->SetBranchAddress("bjets_n_85", &bjets_n_85, &b_bjets_n_85);
  fChain->SetBranchAddress("jets_pt", &jets_pt, &b_jets_pt);
  fChain->SetBranchAddress("jets_phi", &jets_phi, &b_jets_phi);
  fChain->SetBranchAddress("jets_eta", &jets_eta, &b_jets_eta);
  fChain->SetBranchAddress("jets_e", &jets_e, &b_jets_e);
  fChain->SetBranchAddress("jets_jvt", &jets_jvt, &b_jets_jvt);
  fChain->SetBranchAddress("jets_nTracks", &jets_nTracks, &b_jets_nTracks);
  fChain->SetBranchAddress("jets_truthLabel", &jets_truthLabel, &b_jets_truthLabel);
  fChain->SetBranchAddress("jets_btag_weight", &jets_btag_weight, &b_jets_btag_weight);
  fChain->SetBranchAddress("jets_isb_60", &jets_isb_60, &b_jets_isb_60);
  fChain->SetBranchAddress("jets_isb_70", &jets_isb_70, &b_jets_isb_70);
  fChain->SetBranchAddress("jets_isb_77", &jets_isb_77, &b_jets_isb_77);
  fChain->SetBranchAddress("jets_isb_85", &jets_isb_85, &b_jets_isb_85);
  fChain->SetBranchAddress("jets_btagEff_weight", &jets_btagEff_weight, &b_jets_btagEff_weight);
  fChain->SetBranchAddress("asymmetry", &asymmetry, &b_asymmetry);
  fChain->SetBranchAddress("ht", &ht, &b_ht);
  fChain->SetBranchAddress("ht_jets", &ht_jets, &b_ht_jets);
  fChain->SetBranchAddress("meff_incl", &meff_incl, &b_meff_incl);
  fChain->SetBranchAddress("meff_4j", &meff_4j, &b_meff_4j);
  fChain->SetBranchAddress("minv_4j", &minv_4j, &b_minv_4j);
  fChain->SetBranchAddress("mT_4j", &mT_4j, &b_mT_4j);
  fChain->SetBranchAddress("minv_2j", &minv_2j, &b_minv_2j);
  fChain->SetBranchAddress("mT_2j", &mT_2j, &b_mT_2j);
  fChain->SetBranchAddress("minv_bb", &minv_bb, &b_minv_bb);
  fChain->SetBranchAddress("mT_bb", &mT_bb, &b_mT_bb);
  fChain->SetBranchAddress("mct_bb", &mct_bb, &b_mct_bb);
  fChain->SetBranchAddress("mTb_min", &mTb_min, &b_mTb_min);
  fChain->SetBranchAddress("mTb_max", &mTb_max, &b_mTb_max);
  fChain->SetBranchAddress("minv_non_bb", &minv_non_bb, &b_minv_non_bb);
  fChain->SetBranchAddress("mT_non_bb", &mT_non_bb, &b_mT_non_bb);
  fChain->SetBranchAddress("mct_non_bb", &mct_non_bb, &b_mct_non_bb);
  fChain->SetBranchAddress("minv_bb_60", &minv_bb_60, &b_minv_bb_60);
  fChain->SetBranchAddress("mT_bb_60", &mT_bb_60, &b_mT_bb_60);
  fChain->SetBranchAddress("mct_bb_60", &mct_bb_60, &b_mct_bb_60);
  fChain->SetBranchAddress("mTb_min_60", &mTb_min_60, &b_mTb_min_60);
  fChain->SetBranchAddress("mTb_max_60", &mTb_max_60, &b_mTb_max_60);
  fChain->SetBranchAddress("minv_non_bb_60", &minv_non_bb_60, &b_minv_non_bb_60);
  fChain->SetBranchAddress("mT_non_bb_60", &mT_non_bb_60, &b_mT_non_bb_60);
  fChain->SetBranchAddress("mct_non_bb_60", &mct_non_bb_60, &b_mct_non_bb_60);
  fChain->SetBranchAddress("minv_bb_70", &minv_bb_70, &b_minv_bb_70);
  fChain->SetBranchAddress("mT_bb_70", &mT_bb_70, &b_mT_bb_70);
  fChain->SetBranchAddress("mct_bb_70", &mct_bb_70, &b_mct_bb_70);
  fChain->SetBranchAddress("mTb_min_70", &mTb_min_70, &b_mTb_min_70);
  fChain->SetBranchAddress("mTb_max_70", &mTb_max_70, &b_mTb_max_70);
  fChain->SetBranchAddress("minv_non_bb_70", &minv_non_bb_70, &b_minv_non_bb_70);
  fChain->SetBranchAddress("mT_non_bb_70", &mT_non_bb_70, &b_mT_non_bb_70);
  fChain->SetBranchAddress("mct_non_bb_70", &mct_non_bb_70, &b_mct_non_bb_70);
  fChain->SetBranchAddress("minv_bb_77", &minv_bb_77, &b_minv_bb_77);
  fChain->SetBranchAddress("mT_bb_77", &mT_bb_77, &b_mT_bb_77);
  fChain->SetBranchAddress("mct_bb_77", &mct_bb_77, &b_mct_bb_77);
  fChain->SetBranchAddress("mTb_min_77", &mTb_min_77, &b_mTb_min_77);
  fChain->SetBranchAddress("mTb_max_77", &mTb_max_77, &b_mTb_max_77);
  fChain->SetBranchAddress("minv_non_bb_77", &minv_non_bb_77, &b_minv_non_bb_77);
  fChain->SetBranchAddress("mT_non_bb_77", &mT_non_bb_77, &b_mT_non_bb_77);
  fChain->SetBranchAddress("mct_non_bb_77", &mct_non_bb_77, &b_mct_non_bb_77);
  fChain->SetBranchAddress("minv_bb_85", &minv_bb_85, &b_minv_bb_85);
  fChain->SetBranchAddress("mT_bb_85", &mT_bb_85, &b_mT_bb_85);
  fChain->SetBranchAddress("mct_bb_85", &mct_bb_85, &b_mct_bb_85);
  fChain->SetBranchAddress("mTb_min_85", &mTb_min_85, &b_mTb_min_85);
  fChain->SetBranchAddress("mTb_max_85", &mTb_max_85, &b_mTb_max_85);
  fChain->SetBranchAddress("minv_non_bb_85", &minv_non_bb_85, &b_minv_non_bb_85);
  fChain->SetBranchAddress("mT_non_bb_85", &mT_non_bb_85, &b_mT_non_bb_85);
  fChain->SetBranchAddress("mct_non_bb_85", &mct_non_bb_85, &b_mct_non_bb_85);
  fChain->SetBranchAddress("metcst", &metcst, &b_metcst);
  fChain->SetBranchAddress("metcst_phi", &metcst_phi, &b_metcst_phi);
  fChain->SetBranchAddress("mettst", &mettst, &b_mettst);
  fChain->SetBranchAddress("mettst_phi", &mettst_phi, &b_mettst_phi);
  fChain->SetBranchAddress("metsoft", &metsoft, &b_metsoft);
  fChain->SetBranchAddress("metsoft_phi", &metsoft_phi, &b_metsoft_phi);
  fChain->SetBranchAddress("mettrack", &mettrack, &b_mettrack);
  fChain->SetBranchAddress("mettrack_phi", &mettrack_phi, &b_mettrack_phi);
  fChain->SetBranchAddress("mettrack_met_dPhi", &mettrack_met_dPhi, &b_mettrack_met_dPhi);
  fChain->SetBranchAddress("dphi_min", &dphi_min, &b_dphi_min);
  fChain->SetBranchAddress("dphi_1jet", &dphi_1jet, &b_dphi_1jet);
  fChain->SetBranchAddress("dphi_sum4jet", &dphi_sum4jet, &b_dphi_sum4jet);
  fChain->SetBranchAddress("dphi_min_alljets", &dphi_min_alljets, &b_dphi_min_alljets);
  fChain->SetBranchAddress("pass_HLT_e120_lhloose", &pass_HLT_e120_lhloose, &b_pass_HLT_e120_lhloose);
  fChain->SetBranchAddress("pass_HLT_e140_lhloose_nod0", &pass_HLT_e140_lhloose_nod0, &b_pass_HLT_e140_lhloose_nod0);
  fChain->SetBranchAddress("pass_HLT_e24_lhmedium_L1EM20VH", &pass_HLT_e24_lhmedium_L1EM20VH, &b_pass_HLT_e24_lhmedium_L1EM20VH);
  fChain->SetBranchAddress("pass_HLT_e26_lhtight_nod0_ivarloose", &pass_HLT_e26_lhtight_nod0_ivarloose, &b_pass_HLT_e26_lhtight_nod0_ivarloose);
  fChain->SetBranchAddress("pass_HLT_e60_lhmedium", &pass_HLT_e60_lhmedium, &b_pass_HLT_e60_lhmedium);
  fChain->SetBranchAddress("pass_HLT_e60_lhmedium_nod0", &pass_HLT_e60_lhmedium_nod0, &b_pass_HLT_e60_lhmedium_nod0);
  fChain->SetBranchAddress("pass_HLT_mu20_iloose_L1MU15", &pass_HLT_mu20_iloose_L1MU15, &b_pass_HLT_mu20_iloose_L1MU15);
  fChain->SetBranchAddress("pass_HLT_mu26_ivarmedium", &pass_HLT_mu26_ivarmedium, &b_pass_HLT_mu26_ivarmedium);
  fChain->SetBranchAddress("pass_HLT_mu50", &pass_HLT_mu50, &b_pass_HLT_mu50);
  fChain->SetBranchAddress("pass_MET", &pass_MET, &b_pass_MET);
  fChain->SetBranchAddress("weight_WZ_2_2", &weight_WZ_2_2, &b_weight_WZ_2_2);
  fChain->SetBranchAddress("weight_btag", &weight_btag, &b_weight_btag);
  fChain->SetBranchAddress("weight_elec", &weight_elec, &b_weight_elec);
  fChain->SetBranchAddress("weight_elec_trigger", &weight_elec_trigger, &b_weight_elec_trigger);
  fChain->SetBranchAddress("weight_jvt", &weight_jvt, &b_weight_jvt);
  fChain->SetBranchAddress("weight_mc", &weight_mc, &b_weight_mc);
  fChain->SetBranchAddress("weight_muon", &weight_muon, &b_weight_muon);
  fChain->SetBranchAddress("weight_muon_trigger", &weight_muon_trigger, &b_weight_muon_trigger);
  fChain->SetBranchAddress("weight_pu", &weight_pu, &b_weight_pu);
  fChain->SetBranchAddress("weight_ttbar_NNLO", &weight_ttbar_NNLO, &b_weight_ttbar_NNLO);
  fChain->SetBranchAddress("weight_ttbar_NNLO_1L", &weight_ttbar_NNLO_1L, &b_weight_ttbar_NNLO_1L);

  fChain->SetBranchAddress("MJSum_ak10", &MJSum_ak10, &b_MJSum_ak10);
  fChain->SetBranchAddress("ak10_jets_n", &ak10_jets_n, &b_ak10_jets_n);
  fChain->SetBranchAddress("ak10_jets_pt", &ak10_jets_pt, &b_ak10_jets_pt);
  fChain->SetBranchAddress("ak10_jets_phi", &ak10_jets_phi, &b_ak10_jets_phi);
  fChain->SetBranchAddress("ak10_jets_eta", &ak10_jets_eta, &b_ak10_jets_eta);
  fChain->SetBranchAddress("ak10_jets_e", &ak10_jets_e, &b_ak10_jets_e);
  fChain->SetBranchAddress("ak10_jets_m", &ak10_jets_m, &b_ak10_jets_m);
  fChain->SetBranchAddress("ak10_jets_SPLIT12", &ak10_jets_SPLIT12, &b_ak10_jets_SPLIT12);
  fChain->SetBranchAddress("ak10_jets_SPLIT23", &ak10_jets_SPLIT23, &b_ak10_jets_SPLIT23);
  fChain->SetBranchAddress("ak10_jets_tau21", &ak10_jets_tau21, &b_ak10_jets_tau21);
  fChain->SetBranchAddress("ak10_jets_tau32", &ak10_jets_tau32, &b_ak10_jets_tau32);
  fChain->SetBranchAddress("ak10_jets_C2", &ak10_jets_C2, &b_ak10_jets_C2);
  fChain->SetBranchAddress("ak10_jets_D2", &ak10_jets_D2, &b_ak10_jets_D2);
  fChain->SetBranchAddress("ak10_jets_isTopLoose", &ak10_jets_isTopLoose, &b_ak10_jets_isTopLoose);
  fChain->SetBranchAddress("ak10_jets_isTopTight", &ak10_jets_isTopTight, &b_ak10_jets_isTopTight);
  fChain->SetBranchAddress("ak10_jets_isTopSmoothLoose", &ak10_jets_isTopSmoothLoose, &b_ak10_jets_isTopSmoothLoose);
  fChain->SetBranchAddress("ak10_jets_isTopSmoothTight", &ak10_jets_isTopSmoothTight, &b_ak10_jets_isTopSmoothTight);
  fChain->SetBranchAddress("ak10_jets_ghost_ak2_trk_n", &ak10_jets_ghost_ak2_trk_n, &b_ak10_jets_ghost_ak2_trk_n);
  fChain->SetBranchAddress("ak10_jets_assoc_ak4_n", &ak10_jets_assoc_ak4_n, &b_ak10_jets_assoc_ak4_n);
  fChain->SetBranchAddress("ak10_jets_assoc_ak4_btag_n", &ak10_jets_assoc_ak4_btag_n, &b_ak10_jets_assoc_ak4_btag_n);
  fChain->SetBranchAddress("ak10_jets_assoc_ak4_pt", &ak10_jets_assoc_ak4_pt, &b_ak10_jets_assoc_ak4_pt);
  fChain->SetBranchAddress("ak10_jets_assoc_ak4_eta", &ak10_jets_assoc_ak4_eta, &b_ak10_jets_assoc_ak4_eta);
  fChain->SetBranchAddress("ak10_jets_assoc_ak4_phi", &ak10_jets_assoc_ak4_phi, &b_ak10_jets_assoc_ak4_phi);
  fChain->SetBranchAddress("ak10_jets_assoc_ak4_e", &ak10_jets_assoc_ak4_e, &b_ak10_jets_assoc_ak4_e);
  fChain->SetBranchAddress("ak10_jets_assoc_ak4_isb_60", &ak10_jets_assoc_ak4_isb_60, &b_ak10_jets_assoc_ak4_isb_60);
  fChain->SetBranchAddress("ak10_jets_assoc_ak4_isb_70", &ak10_jets_assoc_ak4_isb_70, &b_ak10_jets_assoc_ak4_isb_70);
  fChain->SetBranchAddress("ak10_jets_assoc_ak4_isb_77", &ak10_jets_assoc_ak4_isb_77, &b_ak10_jets_assoc_ak4_isb_77);
  fChain->SetBranchAddress("ak10_jets_assoc_ak4_isb_85", &ak10_jets_assoc_ak4_isb_85, &b_ak10_jets_assoc_ak4_isb_85);
  fChain->SetBranchAddress("ak10_jets_dR01", &ak10_jets_dR01, &b_ak10_jets_dR01);
  fChain->SetBranchAddress("ak10_jets_dEta01", &ak10_jets_dEta01, &b_ak10_jets_dEta01);
  fChain->SetBranchAddress("ak10_jets_dPhi01", &ak10_jets_dPhi01, &b_ak10_jets_dPhi01);

  fChain->SetBranchAddress("MJSum_R08PT10", &MJSum_R08PT10, &b_MJSum_R08PT10);
  fChain->SetBranchAddress("rc_R08PT10_jets_n", &rc_R08PT10_jets_n, &b_rc_R08PT10_jets_n);
  fChain->SetBranchAddress("rc_R08PT10_jets_nconst", &rc_R08PT10_jets_nconst, &b_rc_R08PT10_jets_nconst);
  fChain->SetBranchAddress("rc_R08PT10_jets_nconst_btag", &rc_R08PT10_jets_nconst_btag, &b_rc_R08PT10_jets_nconst_btag);
  fChain->SetBranchAddress("rc_R08PT10_jets_nconst_btag_60", &rc_R08PT10_jets_nconst_btag_60, &b_rc_R08PT10_jets_nconst_btag_60);
  fChain->SetBranchAddress("rc_R08PT10_jets_nconst_btag_70", &rc_R08PT10_jets_nconst_btag_70, &b_rc_R08PT10_jets_nconst_btag_70);
  fChain->SetBranchAddress("rc_R08PT10_jets_nconst_btag_77", &rc_R08PT10_jets_nconst_btag_77, &b_rc_R08PT10_jets_nconst_btag_77);
  fChain->SetBranchAddress("rc_R08PT10_jets_nconst_btag_85", &rc_R08PT10_jets_nconst_btag_85, &b_rc_R08PT10_jets_nconst_btag_85);
  fChain->SetBranchAddress("rc_R08PT10_jets_pt", &rc_R08PT10_jets_pt, &b_rc_R08PT10_jets_pt);
  fChain->SetBranchAddress("rc_R08PT10_jets_phi", &rc_R08PT10_jets_phi, &b_rc_R08PT10_jets_phi);
  fChain->SetBranchAddress("rc_R08PT10_jets_eta", &rc_R08PT10_jets_eta, &b_rc_R08PT10_jets_eta);
  fChain->SetBranchAddress("rc_R08PT10_jets_e", &rc_R08PT10_jets_e, &b_rc_R08PT10_jets_e);
  fChain->SetBranchAddress("rc_R08PT10_jets_m", &rc_R08PT10_jets_m, &b_rc_R08PT10_jets_m);
  fChain->SetBranchAddress("rc_R08PT10_jets_SPLIT12", &rc_R08PT10_jets_SPLIT12, &b_rc_R08PT10_jets_SPLIT12);
  fChain->SetBranchAddress("rc_R08PT10_jets_SPLIT23", &rc_R08PT10_jets_SPLIT23, &b_rc_R08PT10_jets_SPLIT23);
  fChain->SetBranchAddress("rc_R08PT10_jets_tau21", &rc_R08PT10_jets_tau21, &b_rc_R08PT10_jets_tau21);
  fChain->SetBranchAddress("rc_R08PT10_jets_tau32", &rc_R08PT10_jets_tau32, &b_rc_R08PT10_jets_tau32);
  fChain->SetBranchAddress("rc_R08PT10_jets_C2", &rc_R08PT10_jets_C2, &b_rc_R08PT10_jets_C2);
  fChain->SetBranchAddress("rc_R08PT10_jets_D2", &rc_R08PT10_jets_D2, &b_rc_R08PT10_jets_D2);
  fChain->SetBranchAddress("rc_R08PT10_jets_dR01", &rc_R08PT10_jets_dR01, &b_rc_R08PT10_jets_dR01);
  fChain->SetBranchAddress("rc_R08PT10_jets_dEta01", &rc_R08PT10_jets_dEta01, &b_rc_R08PT10_jets_dEta01);
  fChain->SetBranchAddress("rc_R08PT10_jets_dPhi01", &rc_R08PT10_jets_dPhi01, &b_rc_R08PT10_jets_dPhi01);
  fChain->SetBranchAddress("MJSum_R10PT10", &MJSum_R10PT10, &b_MJSum_R10PT10);
  fChain->SetBranchAddress("rc_R10PT10_jets_n", &rc_R10PT10_jets_n, &b_rc_R10PT10_jets_n);
  fChain->SetBranchAddress("rc_R10PT10_jets_nconst", &rc_R10PT10_jets_nconst, &b_rc_R10PT10_jets_nconst);
  fChain->SetBranchAddress("rc_R10PT10_jets_nconst_btag", &rc_R10PT10_jets_nconst_btag, &b_rc_R10PT10_jets_nconst_btag);
  fChain->SetBranchAddress("rc_R10PT10_jets_nconst_btag_60", &rc_R10PT10_jets_nconst_btag_60, &b_rc_R10PT10_jets_nconst_btag_60);
  fChain->SetBranchAddress("rc_R10PT10_jets_nconst_btag_70", &rc_R10PT10_jets_nconst_btag_70, &b_rc_R10PT10_jets_nconst_btag_70);
  fChain->SetBranchAddress("rc_R10PT10_jets_nconst_btag_77", &rc_R10PT10_jets_nconst_btag_77, &b_rc_R10PT10_jets_nconst_btag_77);
  fChain->SetBranchAddress("rc_R10PT10_jets_nconst_btag_85", &rc_R10PT10_jets_nconst_btag_85, &b_rc_R10PT10_jets_nconst_btag_85);
  fChain->SetBranchAddress("rc_R10PT10_jets_pt", &rc_R10PT10_jets_pt, &b_rc_R10PT10_jets_pt);
  fChain->SetBranchAddress("rc_R10PT10_jets_phi", &rc_R10PT10_jets_phi, &b_rc_R10PT10_jets_phi);
  fChain->SetBranchAddress("rc_R10PT10_jets_eta", &rc_R10PT10_jets_eta, &b_rc_R10PT10_jets_eta);
  fChain->SetBranchAddress("rc_R10PT10_jets_e", &rc_R10PT10_jets_e, &b_rc_R10PT10_jets_e);
  fChain->SetBranchAddress("rc_R10PT10_jets_m", &rc_R10PT10_jets_m, &b_rc_R10PT10_jets_m);
  fChain->SetBranchAddress("rc_R10PT10_jets_SPLIT12", &rc_R10PT10_jets_SPLIT12, &b_rc_R10PT10_jets_SPLIT12);
  fChain->SetBranchAddress("rc_R10PT10_jets_SPLIT23", &rc_R10PT10_jets_SPLIT23, &b_rc_R10PT10_jets_SPLIT23);
  fChain->SetBranchAddress("rc_R10PT10_jets_tau21", &rc_R10PT10_jets_tau21, &b_rc_R10PT10_jets_tau21);
  fChain->SetBranchAddress("rc_R10PT10_jets_tau32", &rc_R10PT10_jets_tau32, &b_rc_R10PT10_jets_tau32);
  fChain->SetBranchAddress("rc_R10PT10_jets_C2", &rc_R10PT10_jets_C2, &b_rc_R10PT10_jets_C2);
  fChain->SetBranchAddress("rc_R10PT10_jets_D2", &rc_R10PT10_jets_D2, &b_rc_R10PT10_jets_D2);
  fChain->SetBranchAddress("rc_R10PT10_jets_dR01", &rc_R10PT10_jets_dR01, &b_rc_R10PT10_jets_dR01);
  fChain->SetBranchAddress("rc_R10PT10_jets_dEta01", &rc_R10PT10_jets_dEta01, &b_rc_R10PT10_jets_dEta01);
  fChain->SetBranchAddress("rc_R10PT10_jets_dPhi01", &rc_R10PT10_jets_dPhi01, &b_rc_R10PT10_jets_dPhi01);
  fChain->SetBranchAddress("MJSum_R12PT10", &MJSum_R12PT10, &b_MJSum_R12PT10);
  fChain->SetBranchAddress("rc_R12PT10_jets_n", &rc_R12PT10_jets_n, &b_rc_R12PT10_jets_n);
  fChain->SetBranchAddress("rc_R12PT10_jets_nconst", &rc_R12PT10_jets_nconst, &b_rc_R12PT10_jets_nconst);
  fChain->SetBranchAddress("rc_R12PT10_jets_nconst_btag", &rc_R12PT10_jets_nconst_btag, &b_rc_R12PT10_jets_nconst_btag);
  fChain->SetBranchAddress("rc_R12PT10_jets_nconst_btag_60", &rc_R12PT10_jets_nconst_btag_60, &b_rc_R12PT10_jets_nconst_btag_60);
  fChain->SetBranchAddress("rc_R12PT10_jets_nconst_btag_70", &rc_R12PT10_jets_nconst_btag_70, &b_rc_R12PT10_jets_nconst_btag_70);
  fChain->SetBranchAddress("rc_R12PT10_jets_nconst_btag_77", &rc_R12PT10_jets_nconst_btag_77, &b_rc_R12PT10_jets_nconst_btag_77);
  fChain->SetBranchAddress("rc_R12PT10_jets_nconst_btag_85", &rc_R12PT10_jets_nconst_btag_85, &b_rc_R12PT10_jets_nconst_btag_85);
  fChain->SetBranchAddress("rc_R12PT10_jets_pt", &rc_R12PT10_jets_pt, &b_rc_R12PT10_jets_pt);
  fChain->SetBranchAddress("rc_R12PT10_jets_phi", &rc_R12PT10_jets_phi, &b_rc_R12PT10_jets_phi);
  fChain->SetBranchAddress("rc_R12PT10_jets_eta", &rc_R12PT10_jets_eta, &b_rc_R12PT10_jets_eta);
  fChain->SetBranchAddress("rc_R12PT10_jets_e", &rc_R12PT10_jets_e, &b_rc_R12PT10_jets_e);
  fChain->SetBranchAddress("rc_R12PT10_jets_m", &rc_R12PT10_jets_m, &b_rc_R12PT10_jets_m);
  fChain->SetBranchAddress("rc_R12PT10_jets_SPLIT12", &rc_R12PT10_jets_SPLIT12, &b_rc_R12PT10_jets_SPLIT12);
  fChain->SetBranchAddress("rc_R12PT10_jets_SPLIT23", &rc_R12PT10_jets_SPLIT23, &b_rc_R12PT10_jets_SPLIT23);
  fChain->SetBranchAddress("rc_R12PT10_jets_tau21", &rc_R12PT10_jets_tau21, &b_rc_R12PT10_jets_tau21);
  fChain->SetBranchAddress("rc_R12PT10_jets_tau32", &rc_R12PT10_jets_tau32, &b_rc_R12PT10_jets_tau32);
  fChain->SetBranchAddress("rc_R12PT10_jets_C2", &rc_R12PT10_jets_C2, &b_rc_R12PT10_jets_C2);
  fChain->SetBranchAddress("rc_R12PT10_jets_D2", &rc_R12PT10_jets_D2, &b_rc_R12PT10_jets_D2);
  fChain->SetBranchAddress("rc_R12PT10_jets_dR01", &rc_R12PT10_jets_dR01, &b_rc_R12PT10_jets_dR01);
  fChain->SetBranchAddress("rc_R12PT10_jets_dEta01", &rc_R12PT10_jets_dEta01, &b_rc_R12PT10_jets_dEta01);
  fChain->SetBranchAddress("rc_R12PT10_jets_dPhi01", &rc_R12PT10_jets_dPhi01, &b_rc_R12PT10_jets_dPhi01);
  fChain->SetBranchAddress("MJSum_R15PT10", &MJSum_R15PT10, &b_MJSum_R15PT10);
  fChain->SetBranchAddress("rc_R15PT10_jets_n", &rc_R15PT10_jets_n, &b_rc_R15PT10_jets_n);
  fChain->SetBranchAddress("rc_R15PT10_jets_nconst", &rc_R15PT10_jets_nconst, &b_rc_R15PT10_jets_nconst);
  fChain->SetBranchAddress("rc_R15PT10_jets_nconst_btag", &rc_R15PT10_jets_nconst_btag, &b_rc_R15PT10_jets_nconst_btag);
  fChain->SetBranchAddress("rc_R15PT10_jets_nconst_btag_60", &rc_R15PT10_jets_nconst_btag_60, &b_rc_R15PT10_jets_nconst_btag_60);
  fChain->SetBranchAddress("rc_R15PT10_jets_nconst_btag_70", &rc_R15PT10_jets_nconst_btag_70, &b_rc_R15PT10_jets_nconst_btag_70);
  fChain->SetBranchAddress("rc_R15PT10_jets_nconst_btag_77", &rc_R15PT10_jets_nconst_btag_77, &b_rc_R15PT10_jets_nconst_btag_77);
  fChain->SetBranchAddress("rc_R15PT10_jets_nconst_btag_85", &rc_R15PT10_jets_nconst_btag_85, &b_rc_R15PT10_jets_nconst_btag_85);
  fChain->SetBranchAddress("rc_R15PT10_jets_pt", &rc_R15PT10_jets_pt, &b_rc_R15PT10_jets_pt);
  fChain->SetBranchAddress("rc_R15PT10_jets_phi", &rc_R15PT10_jets_phi, &b_rc_R15PT10_jets_phi);
  fChain->SetBranchAddress("rc_R15PT10_jets_eta", &rc_R15PT10_jets_eta, &b_rc_R15PT10_jets_eta);
  fChain->SetBranchAddress("rc_R15PT10_jets_e", &rc_R15PT10_jets_e, &b_rc_R15PT10_jets_e);
  fChain->SetBranchAddress("rc_R15PT10_jets_m", &rc_R15PT10_jets_m, &b_rc_R15PT10_jets_m);
  fChain->SetBranchAddress("rc_R15PT10_jets_SPLIT12", &rc_R15PT10_jets_SPLIT12, &b_rc_R15PT10_jets_SPLIT12);
  fChain->SetBranchAddress("rc_R15PT10_jets_SPLIT23", &rc_R15PT10_jets_SPLIT23, &b_rc_R15PT10_jets_SPLIT23);
  fChain->SetBranchAddress("rc_R15PT10_jets_tau21", &rc_R15PT10_jets_tau21, &b_rc_R15PT10_jets_tau21);
  fChain->SetBranchAddress("rc_R15PT10_jets_tau32", &rc_R15PT10_jets_tau32, &b_rc_R15PT10_jets_tau32);
  fChain->SetBranchAddress("rc_R15PT10_jets_C2", &rc_R15PT10_jets_C2, &b_rc_R15PT10_jets_C2);
  fChain->SetBranchAddress("rc_R15PT10_jets_D2", &rc_R15PT10_jets_D2, &b_rc_R15PT10_jets_D2);
  fChain->SetBranchAddress("rc_R15PT10_jets_dR01", &rc_R15PT10_jets_dR01, &b_rc_R15PT10_jets_dR01);
  fChain->SetBranchAddress("rc_R15PT10_jets_dEta01", &rc_R15PT10_jets_dEta01, &b_rc_R15PT10_jets_dEta01);
  fChain->SetBranchAddress("rc_R15PT10_jets_dPhi01", &rc_R15PT10_jets_dPhi01, &b_rc_R15PT10_jets_dPhi01);
  Notify();
}

void mbj_flatten_tree::InitOutTree(TTree *tree)
{
  // Initialize the output tree

  // Initialize branches for the flat output tree
  // Branches that are just copied over from the input tree
  tree->Branch("event_number", &event_number, "event_number/l");
  tree->Branch("run_number", &run_number, "run_number/l");
  tree->Branch("lumiblock_number", &lumiblock_number, "lumiblock_number/I");
  tree->Branch("average_interactions_per_crossing", &average_interactions_per_crossing, "average_interactions_per_crossing/F");
  tree->Branch("actual_interactions_per_crossing", &actual_interactions_per_crossing, "actual_interactions_per_crossing/F");
  tree->Branch("n_vtx", &n_vtx, "n_vtx/I");
  tree->Branch("primary_vertex_z", &primary_vertex_z, "primary_vertex_z/F");
  tree->Branch("process", &process, "process/I");
  tree->Branch("gen_filt_ht", &gen_filt_ht, "gen_filt_ht/F");
  tree->Branch("gen_filt_met", &gen_filt_met, "gen_filt_met/F");
  tree->Branch("muons_n", &muons_n, "muons_n/I");
  tree->Branch("electrons_n", &electrons_n, "electrons/I");
  tree->Branch("jets_n", &jets_n, "jets_n/I");
  tree->Branch("bjets_n", &bjets_n, "bjets_n/I");
  tree->Branch("bjets_n_60", &bjets_n_60, "bjets_n_60/I");
  tree->Branch("bjets_n_70", &bjets_n_70, "bjets_n_70/I");
  tree->Branch("bjets_n_77", &bjets_n_77, "bjets_n_77/I");
  tree->Branch("bjets_n_85", &bjets_n_85, "bjets_n_85/I");
  tree->Branch("asymmetry", &asymmetry, "asymmetry/F");
  tree->Branch("ht", &ht, "ht/F");
  tree->Branch("ht_jets", &ht_jets, "ht_jets/F");
  tree->Branch("meff_incl", &meff_incl, "meff_incl/F");
  tree->Branch("meff_4j", &meff_4j, "meff_4j/F");
  tree->Branch("minv_4j", &minv_4j, "minv_4j/F");
  tree->Branch("mT_4j", &mT_4j, "mT_4j/F");
  tree->Branch("minv_2j", &minv_2j, "minv_2j/F");
  tree->Branch("mT_2j", &mT_2j, "mT_2j/F");
  tree->Branch("minv_bb", &minv_bb, "minv_bb/F");
  tree->Branch("mT_bb", &mT_bb, "mT_bb/F");
  tree->Branch("mct_bb", &mct_bb, "mct_bb/F");
  tree->Branch("mTb_min", &mTb_min, "mTb_min/F");
  tree->Branch("mTb_max", &mTb_max, "mTb_max/F");
  tree->Branch("minv_non_bb", &minv_non_bb, "minv_non_bb/F");
  tree->Branch("mT_non_bb", &mT_non_bb, "mT_non_bb/F");
  tree->Branch("mct_non_bb", &mct_non_bb, "mct_non_bb/F");
  tree->Branch("minv_bb_60", &minv_bb_60, "minv_bb_60/F");
  tree->Branch("mT_bb_60", &mT_bb_60, "mT_bb_60/F");
  tree->Branch("mct_bb_60", &mct_bb_60, "mct_bb_60/F");
  tree->Branch("mTb_min_60", &mTb_min_60, "mTb_min_60/F");
  tree->Branch("mTb_max_60", &mTb_max_60, "mTb_max_60/F");
  tree->Branch("minv_non_bb_60", &minv_non_bb_60, "minv_non_bb_60/F");
  tree->Branch("mT_non_bb_60", &mT_non_bb_60, "mT_non_bb_60/F");
  tree->Branch("mct_non_bb_60", &mct_non_bb_60, "mct_non_bb_60/F");
  tree->Branch("minv_bb_70", &minv_bb_70, "minv_bb_70/F");
  tree->Branch("mT_bb_70", &mT_bb_70, "mT_bb_70/F");
  tree->Branch("mct_bb_70", &mct_bb_70, "mct_bb_70/F");
  tree->Branch("mTb_min_70", &mTb_min_70, "mTb_min_70/F");
  tree->Branch("mTb_max_70", &mTb_max_70, "mTb_max_70/F");
  tree->Branch("minv_non_bb_70", &minv_non_bb_70, "minv_non_bb_70/F");
  tree->Branch("mT_non_bb_70", &mT_non_bb_70, "mT_non_bb_70/F");
  tree->Branch("mct_non_bb_70", &mct_non_bb_70, "mct_non_bb_70/F");
  tree->Branch("minv_bb_77", &minv_bb_77, "minv_bb_77/F");
  tree->Branch("mT_bb_77", &mT_bb_77, "mT_bb_77/F");
  tree->Branch("mct_bb_77", &mct_bb_77, "mct_bb_77/F");
  tree->Branch("mTb_min_77", &mTb_min_77, "mTb_min_77/F");
  tree->Branch("mTb_max_77", &mTb_max_77, "mTb_max_77/F");
  tree->Branch("minv_non_bb_77", &minv_non_bb_77, "minv_non_bb_77/F");
  tree->Branch("mT_non_bb_77", &mT_non_bb_77, "mT_non_bb_77/F");
  tree->Branch("mct_non_bb_77", &mct_non_bb_77, "mct_non_bb_77/F");
  tree->Branch("minv_bb_85", &minv_bb_85, "minv_bb_85/F");
  tree->Branch("mT_bb_85", &mT_bb_85, "mT_bb_85/F");
  tree->Branch("mct_bb_85", &mct_bb_85, "mct_bb_85/F");
  tree->Branch("mTb_min_85", &mTb_min_85, "mTb_min_85/F");
  tree->Branch("mTb_max_85", &mTb_max_85, "mTb_max_85/F");
  tree->Branch("minv_non_bb_85", &minv_non_bb_85, "minv_non_bb_85/F");
  tree->Branch("mT_non_bb_85", &mT_non_bb_85, "mT_non_bb_85/F");
  tree->Branch("mct_non_bb_85", &mct_non_bb_85, "mct_non_bb_85/F");
  tree->Branch("metcst", &metcst, "metcst/F");
  tree->Branch("metcst_phi", &metcst_phi, "metcst_phi/F");
  tree->Branch("mettst", &mettst, "mettst/F");
  tree->Branch("mettst_phi", &mettst_phi, "mettst_phi/F");
  tree->Branch("metsoft", &metsoft, "metsoft/F");
  tree->Branch("metsoft_phi", &metsoft_phi, "metsoft_phi/F");
  tree->Branch("mettrack", &mettrack, "mettrack/F");
  tree->Branch("mettrack_phi", &mettrack_phi, "mettrack_phi/F");
  tree->Branch("mettrack_met_dPhi", &mettrack_met_dPhi, "mettrack_met_dPhi/F");
  tree->Branch("dphi_min", &dphi_min, "dphi_min/F");
  tree->Branch("dphi_1jet", &dphi_1jet, "dphi_1jet/F");
  tree->Branch("dphi_sum4jet", &dphi_sum4jet, "dphi_sum4jet/F");
  tree->Branch("dphi_min_alljets", &dphi_min_alljets, "dphi_min_alljets/F");
  tree->Branch("pass_HLT_e120_lhloose", &pass_HLT_e120_lhloose, "pass_HLT_e120_lhloose/I");
  tree->Branch("pass_HLT_e140_lhloose_nod0", &pass_HLT_e140_lhloose_nod0, "pass_HLT_e140_lhloose_nod0/I");
  tree->Branch("pass_HLT_e24_lhmedium_L1EM20VH", &pass_HLT_e24_lhmedium_L1EM20VH, "pass_HLT_e24_lhmedium_L1EM20VH/I");
  tree->Branch("pass_HLT_e26_lhtight_nod0_ivarloose", &pass_HLT_e26_lhtight_nod0_ivarloose, "pass_HLT_e26_lhtight_nod0_ivarloose/I");
  tree->Branch("pass_HLT_e60_lhmedium", &pass_HLT_e60_lhmedium, "pass_HLT_e60_lhmedium/I");
  tree->Branch("pass_HLT_e60_lhmedium_nod0", &pass_HLT_e60_lhmedium_nod0, "pass_HLT_e60_lhmedium_nod0/I");
  tree->Branch("pass_HLT_mu20_iloose_L1MU15", &pass_HLT_mu20_iloose_L1MU15, "pass_HLT_mu20_iloose_L1MU15/I");
  tree->Branch("pass_HLT_mu26_ivarmedium", &pass_HLT_mu26_ivarmedium, "pass_HLT_mu26_ivarmedium/I");
  tree->Branch("pass_HLT_mu50", &pass_HLT_mu50, "pass_HLT_mu50/I");
  tree->Branch("pass_MET", &pass_MET, "pass_MET/I");
  tree->Branch("weight_WZ_2_2", &weight_WZ_2_2, "weight_WZ_2_2/D");
  tree->Branch("weight_btag", &weight_btag, "weight_btag/D");
  tree->Branch("weight_elec", &weight_elec, "weight_elec/D");
  tree->Branch("weight_elec_trigger", &weight_elec_trigger, "weight_elec_trigger/D");
  tree->Branch("weight_jvt", &weight_jvt, "weight_jvt/D");
  tree->Branch("weight_mc", &weight_mc, "weight_mc/D");
  tree->Branch("weight_muon", &weight_muon, "weight_muon/D");
  tree->Branch("weight_muon_trigger", &weight_muon_trigger, "weight_muon_trigger/D");
  tree->Branch("weight_pu", &weight_pu, "weight_pu/D");
  tree->Branch("weight_ttbar_NNLO", &weight_ttbar_NNLO, "weight_ttbar_NNLO/D");
  tree->Branch("weight_ttbar_NNLO_1L", &weight_ttbar_NNLO_1L, "weight_ttbar_NNLO_1L/D");

  tree->Branch("MJSum_ak10", &MJSum_ak10, "MJSum_ak10/F");
  tree->Branch("ak10_jets_n", &ak10_jets_n, "ak10_jets_n/I");
  tree->Branch("ak10_jets_dR01", &ak10_jets_dR01, "ak10_jets_dR01/F");
  tree->Branch("ak10_jets_dEta01", &ak10_jets_dEta01, "ak10_jets_dEta01/F");
  tree->Branch("ak10_jets_dPhi01", &ak10_jets_dPhi01, "ak10_jets_dPhi01/F");

  tree->Branch("MJSum_R08PT10", &MJSum_R08PT10, "MJSum_R08PT10/F");
  tree->Branch("rc_R08PT10_jets_n", &rc_R08PT10_jets_n, "rc_R08PT10_jets_n/I");
  tree->Branch("rc_R08PT10_jets_dR01", &rc_R08PT10_jets_dR01, "rc_R08PT10_jets_dR01/F");
  tree->Branch("rc_R08PT10_jets_dEta01", &rc_R08PT10_jets_dEta01, "rc_R08PT10_jets_dEta01/F");
  tree->Branch("rc_R08PT10_jets_dPhi01", &rc_R08PT10_jets_dPhi01, "rc_R08PT10_jets_dPhi01/F");

  tree->Branch("MJSum_R10PT10", &MJSum_R10PT10, "MJSum_R10PT10/F");
  tree->Branch("rc_R10PT10_jets_n", &rc_R10PT10_jets_n, "rc_R10PT10_jets_n/I");
  tree->Branch("rc_R10PT10_jets_dR01", &rc_R10PT10_jets_dR01, "rc_R10PT10_jets_dR01/F");
  tree->Branch("rc_R10PT10_jets_dEta01", &rc_R10PT10_jets_dEta01, "rc_R10PT10_jets_dEta01/F");
  tree->Branch("rc_R10PT10_jets_dPhi01", &rc_R10PT10_jets_dPhi01, "rc_R10PT10_jets_dPhi01/F");

  tree->Branch("MJSum_R12PT10", &MJSum_R12PT10, "MJSum_R12PT10/F");
  tree->Branch("rc_R12PT10_jets_n", &rc_R12PT10_jets_n, "rc_R12PT10_jets_n/I");
  tree->Branch("rc_R12PT10_jets_dR01", &rc_R12PT10_jets_dR01, "rc_R12PT10_jets_dR01/F");
  tree->Branch("rc_R12PT10_jets_dEta01", &rc_R12PT10_jets_dEta01, "rc_R12PT10_jets_dEta01/F");
  tree->Branch("rc_R12PT10_jets_dPhi01", &rc_R12PT10_jets_dPhi01, "rc_R12PT10_jets_dPhi01/F");

  tree->Branch("MJSum_R15PT10", &MJSum_R15PT10, "MJSum_R15PT10/F");
  tree->Branch("rc_R15PT10_jets_n", &rc_R15PT10_jets_n, "rc_R15PT10_jets_n/I");
  tree->Branch("rc_R15PT10_jets_dR01", &rc_R15PT10_jets_dR01, "rc_R15PT10_jets_dR01/F");
  tree->Branch("rc_R15PT10_jets_dEta01", &rc_R15PT10_jets_dEta01, "rc_R15PT10_jets_dEta01/F");
  tree->Branch("rc_R15PT10_jets_dPhi01", &rc_R15PT10_jets_dPhi01, "rc_R15PT10_jets_dPhi01/F");

  // New brances added in the flat tree
  
  // AKT4 jets
  tree->Branch("pt_jet_1", &pt_jet_1, "pt_jet_1/F");
  tree->Branch("pt_jet_2", &pt_jet_2, "pt_jet_2/F");
  tree->Branch("pt_jet_3", &pt_jet_3, "pt_jet_3/F");
  tree->Branch("pt_jet_4", &pt_jet_4, "pt_jet_4/F");

  tree->Branch("pt_bjet_1_60", &pt_bjet_1_60, "pt_bjet_1_60/F");
  tree->Branch("pt_bjet_2_60", &pt_bjet_2_60, "pt_bjet_2_60/F");
  tree->Branch("pt_bjet_3_60", &pt_bjet_3_60, "pt_bjet_3_60/F");
  tree->Branch("pt_bjet_4_60", &pt_bjet_4_60, "pt_bjet_4_60/F");

  tree->Branch("pt_bjet_1_70", &pt_bjet_1_70, "pt_bjet_1_70/F");
  tree->Branch("pt_bjet_2_70", &pt_bjet_2_70, "pt_bjet_2_70/F");
  tree->Branch("pt_bjet_3_70", &pt_bjet_3_70, "pt_bjet_3_70/F");
  tree->Branch("pt_bjet_4_70", &pt_bjet_4_70, "pt_bjet_4_70/F");

  tree->Branch("pt_bjet_1_77", &pt_bjet_1_77, "pt_bjet_1_77/F");
  tree->Branch("pt_bjet_2_77", &pt_bjet_2_77, "pt_bjet_2_77/F");
  tree->Branch("pt_bjet_3_77", &pt_bjet_3_77, "pt_bjet_3_77/F");
  tree->Branch("pt_bjet_4_77", &pt_bjet_4_77, "pt_bjet_4_77/F");

  tree->Branch("pt_bjet_1_85", &pt_bjet_1_85, "pt_bjet_1_85/F");
  tree->Branch("pt_bjet_2_85", &pt_bjet_2_85, "pt_bjet_2_85/F");
  tree->Branch("pt_bjet_3_85", &pt_bjet_3_85, "pt_bjet_3_85/F");
  tree->Branch("pt_bjet_4_85", &pt_bjet_4_85, "pt_bjet_4_85/F");

  // AKT10 trimmed fat-jets
  tree->Branch("ak10_dphi_min", &ak10_dphi_min, "ak10_dphi_min/F");
  tree->Branch("ak10_dphi_1jet", &ak10_dphi_1jet, "ak10_dphi_1jet/F");
  tree->Branch("ak10_dphi_sum2jet", &ak10_dphi_sum2jet, "ak10_dphi_sum2jet/F");
  tree->Branch("ak10_dphi_min_alljets", &ak10_dphi_min_alljets, "ak10_dphi_min_alljets/F");
  tree->Branch("ak10_meff_2j", &ak10_meff_2j, "ak10_meff_2j/F");
  tree->Branch("ak10_meff_4j", &ak10_meff_4j, "ak10_meff_4j/F");
  tree->Branch("ak10_meff_nj", &ak10_meff_nj, "ak10_meff_nj/F");
  tree->Branch("ak10_mT_2j", &ak10_mT_2j, "ak10_mT_2j/F");
  tree->Branch("ak10_pt_jet_1", &ak10_pt_jet_1, "ak10_pt_jet_1/F");
  tree->Branch("ak10_pt_jet_2", &ak10_pt_jet_2, "ak10_pt_jet_2/F");
  tree->Branch("ak10_pt_jet_3", &ak10_pt_jet_3, "ak10_pt_jet_3/F");
  tree->Branch("ak10_pt_jet_4", &ak10_pt_jet_4, "ak10_pt_jet_4/F");
  tree->Branch("ak10_m_jet_1", &ak10_m_jet_1, "ak10_m_jet_1/F");
  tree->Branch("ak10_m_jet_2", &ak10_m_jet_2, "ak10_m_jet_2/F");
  tree->Branch("ak10_m_jet_3", &ak10_m_jet_3, "ak10_m_jet_3/F");
  tree->Branch("ak10_m_jet_4", &ak10_m_jet_4, "ak10_m_jet_4/F");
  tree->Branch("ak10_SPLIT12_jet_1", &ak10_SPLIT12_jet_1, "ak10_SPLIT12_jet_1/F");
  tree->Branch("ak10_SPLIT12_jet_2", &ak10_SPLIT12_jet_2, "ak10_SPLIT12_jet_2/F");
  tree->Branch("ak10_SPLIT12_jet_3", &ak10_SPLIT12_jet_3, "ak10_SPLIT12_jet_3/F");
  tree->Branch("ak10_SPLIT12_jet_4", &ak10_SPLIT12_jet_4, "ak10_SPLIT12_jet_4/F");
  tree->Branch("ak10_SPLIT23_jet_1", &ak10_SPLIT23_jet_1, "ak10_SPLIT23_jet_1/F");
  tree->Branch("ak10_SPLIT23_jet_2", &ak10_SPLIT23_jet_2, "ak10_SPLIT23_jet_2/F");
  tree->Branch("ak10_SPLIT23_jet_3", &ak10_SPLIT23_jet_3, "ak10_SPLIT23_jet_3/F");
  tree->Branch("ak10_SPLIT23_jet_4", &ak10_SPLIT23_jet_4, "ak10_SPLIT23_jet_4/F");
  tree->Branch("ak10_tau21_jet_1", &ak10_tau21_jet_1, "ak10_tau21_jet_1/F");
  tree->Branch("ak10_tau21_jet_2", &ak10_tau21_jet_2, "ak10_tau21_jet_2/F");
  tree->Branch("ak10_tau21_jet_3", &ak10_tau21_jet_3, "ak10_tau21_jet_3/F");
  tree->Branch("ak10_tau21_jet_4", &ak10_tau21_jet_4, "ak10_tau21_jet_4/F");
  tree->Branch("ak10_tau32_jet_1", &ak10_tau32_jet_1, "ak10_tau32_jet_1/F");
  tree->Branch("ak10_tau32_jet_2", &ak10_tau32_jet_2, "ak10_tau32_jet_2/F");
  tree->Branch("ak10_tau32_jet_3", &ak10_tau32_jet_3, "ak10_tau32_jet_3/F");
  tree->Branch("ak10_tau32_jet_4", &ak10_tau32_jet_4, "ak10_tau32_jet_4/F");
  tree->Branch("ak10_C2_jet_1", &ak10_C2_jet_1, "ak10_C2_jet_1/F");
  tree->Branch("ak10_C2_jet_2", &ak10_C2_jet_2, "ak10_C2_jet_2/F");
  tree->Branch("ak10_C2_jet_3", &ak10_C2_jet_3, "ak10_C2_jet_3/F");
  tree->Branch("ak10_C2_jet_4", &ak10_C2_jet_4, "ak10_C2_jet_4/F");
  tree->Branch("ak10_D2_jet_1", &ak10_D2_jet_1, "ak10_D2_jet_1/F");
  tree->Branch("ak10_D2_jet_2", &ak10_D2_jet_2, "ak10_D2_jet_2/F");
  tree->Branch("ak10_D2_jet_3", &ak10_D2_jet_3, "ak10_D2_jet_3/F");
  tree->Branch("ak10_D2_jet_4", &ak10_D2_jet_4, "ak10_D2_jet_4/F");
  tree->Branch("ak10_assoc_ak4_n_jet_1", &ak10_assoc_ak4_n_jet_1, "ak10_assoc_ak4_n_jet_1/I");
  tree->Branch("ak10_assoc_ak4_n_jet_2", &ak10_assoc_ak4_n_jet_2, "ak10_assoc_ak4_n_jet_2/I");
  tree->Branch("ak10_assoc_ak4_n_jet_3", &ak10_assoc_ak4_n_jet_3, "ak10_assoc_ak4_n_jet_3/I");
  tree->Branch("ak10_assoc_ak4_n_jet_4", &ak10_assoc_ak4_n_jet_4, "ak10_assoc_ak4_n_jet_4/I");
  tree->Branch("ak10_assoc_ak4_btag_n_jet_1", &ak10_assoc_ak4_btag_n_jet_1, "ak10_assoc_ak4_btag_n_jet_1/I");
  tree->Branch("ak10_assoc_ak4_btag_n_jet_2", &ak10_assoc_ak4_btag_n_jet_2, "ak10_assoc_ak4_btag_n_jet_2/I");
  tree->Branch("ak10_assoc_ak4_btag_n_jet_3", &ak10_assoc_ak4_btag_n_jet_3, "ak10_assoc_ak4_btag_n_jet_3/I");
  tree->Branch("ak10_assoc_ak4_btag_n_jet_4", &ak10_assoc_ak4_btag_n_jet_4, "ak10_assoc_ak4_btag_n_jet_4/I");
  tree->Branch("ak10_ghost_ak2_trk_n_jet_1", &ak10_ghost_ak2_trk_n_jet_1, "ak10_ghost_ak2_trk_n_jet_1/I");
  tree->Branch("ak10_ghost_ak2_trk_n_jet_2", &ak10_ghost_ak2_trk_n_jet_2, "ak10_ghost_ak2_trk_n_jet_2/I");
  tree->Branch("ak10_ghost_ak2_trk_n_jet_3", &ak10_ghost_ak2_trk_n_jet_3, "ak10_ghost_ak2_trk_n_jet_3/I");
  tree->Branch("ak10_ghost_ak2_trk_n_jet_4", &ak10_ghost_ak2_trk_n_jet_4, "ak10_ghost_ak2_trk_n_jet_4/I");

  tree->Branch("ak10_pt_h", &ak10_pt_h, "ak10_pt_h/F");
  tree->Branch("ak10_pt_W", &ak10_pt_W, "ak10_pt_W/F");
  tree->Branch("ak10_m_h", &ak10_m_h, "ak10_m_h/F");
  tree->Branch("ak10_m_W", &ak10_m_W, "ak10_m_W/F");
  tree->Branch("ak10_SPLIT12_h", &ak10_SPLIT12_h, "ak10_SPLIT12_h/F");
  tree->Branch("ak10_SPLIT12_W", &ak10_SPLIT12_W, "ak10_SPLIT12_W/F");
  tree->Branch("ak10_SPLIT23_h", &ak10_SPLIT23_h, "ak10_SPLIT23_h/F");
  tree->Branch("ak10_SPLIT23_W", &ak10_SPLIT23_W, "ak10_SPLIT23_W/F");
  tree->Branch("ak10_tau21_h", &ak10_tau21_h, "ak10_tau21_h/F");
  tree->Branch("ak10_tau21_W", &ak10_tau21_W, "ak10_tau21_W/F");
  tree->Branch("ak10_tau32_h", &ak10_tau32_h, "ak10_tau32_h/F");
  tree->Branch("ak10_tau32_W", &ak10_tau32_W, "ak10_tau32_W/F");
  tree->Branch("ak10_C2_h", &ak10_C2_h, "ak10_C2_h/F");
  tree->Branch("ak10_C2_W", &ak10_C2_W, "ak10_C2_W/F");
  tree->Branch("ak10_D2_h", &ak10_D2_h, "ak10_D2_h/F");
  tree->Branch("ak10_D2_W", &ak10_D2_W, "ak10_D2_W/F");
  tree->Branch("ak10_dR_Wh", &ak10_dR_Wh, "ak10_dR_Wh/F");
  tree->Branch("ak10_dEta_Wh", &ak10_dEta_Wh, "ak10_dEta_Wh/F");
  tree->Branch("ak10_dPhi_Wh", &ak10_dPhi_Wh, "ak10_dPhi_Wh/F");
  tree->Branch("ak10_assoc_ak4_n_h", &ak10_assoc_ak4_n_h, "ak10_assoc_ak4_n_h/I");
  tree->Branch("ak10_assoc_ak4_n_W", &ak10_assoc_ak4_n_W, "ak10_assoc_ak4_n_W/I");
  tree->Branch("ak10_assoc_ak4_btag_n_h", &ak10_assoc_ak4_btag_n_h, "ak10_assoc_ak4_btag_n_h/I");
  tree->Branch("ak10_assoc_ak4_btag_n_W", &ak10_assoc_ak4_btag_n_W, "ak10_assoc_ak4_btag_n_W/I");
  tree->Branch("ak10_ghost_ak2_trk_n_h", &ak10_ghost_ak2_trk_n_h, "ak10_ghost_ak2_trk_n_h/I");
  tree->Branch("ak10_ghost_ak2_trk_n_W", &ak10_ghost_ak2_trk_n_W, "ak10_ghost_ak2_trk_n_W/I");

  // R08PT10 reclustered fat-jets
  tree->Branch("rc_R08PT10_dphi_min", &rc_R08PT10_dphi_min, "rc_R08PT10_dphi_min/F");
  tree->Branch("rc_R08PT10_dphi_1jet", &rc_R08PT10_dphi_1jet, "rc_R08PT10_dphi_1jet/F");
  tree->Branch("rc_R08PT10_dphi_sum2jet", &rc_R08PT10_dphi_sum2jet, "rc_R08PT10_dphi_sum2jet/F");
  tree->Branch("rc_R08PT10_dphi_min_alljets", &rc_R08PT10_dphi_min_alljets, "rc_R08PT10_dphi_min_alljets/F");
  tree->Branch("rc_R08PT10_meff_2j", &rc_R08PT10_meff_2j, "rc_R08PT10_meff_2j/F");
  tree->Branch("rc_R08PT10_meff_4j", &rc_R08PT10_meff_4j, "rc_R08PT10_meff_4j/F");
  tree->Branch("rc_R08PT10_meff_nj", &rc_R08PT10_meff_nj, "rc_R08PT10_meff_nj/F");
  tree->Branch("rc_R08PT10_mT_2j", &rc_R08PT10_mT_2j, "rc_R08PT10_mT_2j/F");
  tree->Branch("rc_R08PT10_pt_jet_1", &rc_R08PT10_pt_jet_1, "rc_R08PT10_pt_jet_1/F");
  tree->Branch("rc_R08PT10_pt_jet_2", &rc_R08PT10_pt_jet_2, "rc_R08PT10_pt_jet_2/F");
  tree->Branch("rc_R08PT10_pt_jet_3", &rc_R08PT10_pt_jet_3, "rc_R08PT10_pt_jet_3/F");
  tree->Branch("rc_R08PT10_pt_jet_4", &rc_R08PT10_pt_jet_4, "rc_R08PT10_pt_jet_4/F");
  tree->Branch("rc_R08PT10_m_jet_1", &rc_R08PT10_m_jet_1, "rc_R08PT10_m_jet_1/F");
  tree->Branch("rc_R08PT10_m_jet_2", &rc_R08PT10_m_jet_2, "rc_R08PT10_m_jet_2/F");
  tree->Branch("rc_R08PT10_m_jet_3", &rc_R08PT10_m_jet_3, "rc_R08PT10_m_jet_3/F");
  tree->Branch("rc_R08PT10_m_jet_4", &rc_R08PT10_m_jet_4, "rc_R08PT10_m_jet_4/F");
  tree->Branch("rc_R08PT10_SPLIT12_jet_1", &rc_R08PT10_SPLIT12_jet_1, "rc_R08PT10_SPLIT12_jet_1/F");
  tree->Branch("rc_R08PT10_SPLIT12_jet_2", &rc_R08PT10_SPLIT12_jet_2, "rc_R08PT10_SPLIT12_jet_2/F");
  tree->Branch("rc_R08PT10_SPLIT12_jet_3", &rc_R08PT10_SPLIT12_jet_3, "rc_R08PT10_SPLIT12_jet_3/F");
  tree->Branch("rc_R08PT10_SPLIT12_jet_4", &rc_R08PT10_SPLIT12_jet_4, "rc_R08PT10_SPLIT12_jet_4/F");
  tree->Branch("rc_R08PT10_SPLIT23_jet_1", &rc_R08PT10_SPLIT23_jet_1, "rc_R08PT10_SPLIT23_jet_1/F");
  tree->Branch("rc_R08PT10_SPLIT23_jet_2", &rc_R08PT10_SPLIT23_jet_2, "rc_R08PT10_SPLIT23_jet_2/F");
  tree->Branch("rc_R08PT10_SPLIT23_jet_3", &rc_R08PT10_SPLIT23_jet_3, "rc_R08PT10_SPLIT23_jet_3/F");
  tree->Branch("rc_R08PT10_SPLIT23_jet_4", &rc_R08PT10_SPLIT23_jet_4, "rc_R08PT10_SPLIT23_jet_4/F");
  tree->Branch("rc_R08PT10_tau21_jet_1", &rc_R08PT10_tau21_jet_1, "rc_R08PT10_tau21_jet_1/F");
  tree->Branch("rc_R08PT10_tau21_jet_2", &rc_R08PT10_tau21_jet_2, "rc_R08PT10_tau21_jet_2/F");
  tree->Branch("rc_R08PT10_tau21_jet_3", &rc_R08PT10_tau21_jet_3, "rc_R08PT10_tau21_jet_3/F");
  tree->Branch("rc_R08PT10_tau21_jet_4", &rc_R08PT10_tau21_jet_4, "rc_R08PT10_tau21_jet_4/F");
  tree->Branch("rc_R08PT10_tau32_jet_1", &rc_R08PT10_tau32_jet_1, "rc_R08PT10_tau32_jet_1/F");
  tree->Branch("rc_R08PT10_tau32_jet_2", &rc_R08PT10_tau32_jet_2, "rc_R08PT10_tau32_jet_2/F");
  tree->Branch("rc_R08PT10_tau32_jet_3", &rc_R08PT10_tau32_jet_3, "rc_R08PT10_tau32_jet_3/F");
  tree->Branch("rc_R08PT10_tau32_jet_4", &rc_R08PT10_tau32_jet_4, "rc_R08PT10_tau32_jet_4/F");
  tree->Branch("rc_R08PT10_C2_jet_1", &rc_R08PT10_C2_jet_1, "rc_R08PT10_C2_jet_1/F");
  tree->Branch("rc_R08PT10_C2_jet_2", &rc_R08PT10_C2_jet_2, "rc_R08PT10_C2_jet_2/F");
  tree->Branch("rc_R08PT10_C2_jet_3", &rc_R08PT10_C2_jet_3, "rc_R08PT10_C2_jet_3/F");
  tree->Branch("rc_R08PT10_C2_jet_4", &rc_R08PT10_C2_jet_4, "rc_R08PT10_C2_jet_4/F");
  tree->Branch("rc_R08PT10_D2_jet_1", &rc_R08PT10_D2_jet_1, "rc_R08PT10_D2_jet_1/F");
  tree->Branch("rc_R08PT10_D2_jet_2", &rc_R08PT10_D2_jet_2, "rc_R08PT10_D2_jet_2/F");
  tree->Branch("rc_R08PT10_D2_jet_3", &rc_R08PT10_D2_jet_3, "rc_R08PT10_D2_jet_3/F");
  tree->Branch("rc_R08PT10_D2_jet_4", &rc_R08PT10_D2_jet_4, "rc_R08PT10_D2_jet_4/F");
  tree->Branch("rc_R08PT10_nconst_jet_1", &rc_R08PT10_nconst_jet_1, "rc_R08PT10_nconst_jet_1/I");
  tree->Branch("rc_R08PT10_nconst_jet_2", &rc_R08PT10_nconst_jet_2, "rc_R08PT10_nconst_jet_2/I");
  tree->Branch("rc_R08PT10_nconst_jet_3", &rc_R08PT10_nconst_jet_3, "rc_R08PT10_nconst_jet_3/I");
  tree->Branch("rc_R08PT10_nconst_jet_4", &rc_R08PT10_nconst_jet_4, "rc_R08PT10_nconst_jet_4/I");
  tree->Branch("rc_R08PT10_nconst_btag_jet_1", &rc_R08PT10_nconst_btag_jet_1, "rc_R08PT10_nconst_btag_jet_1/I");
  tree->Branch("rc_R08PT10_nconst_btag_jet_2", &rc_R08PT10_nconst_btag_jet_2, "rc_R08PT10_nconst_btag_jet_2/I");
  tree->Branch("rc_R08PT10_nconst_btag_jet_3", &rc_R08PT10_nconst_btag_jet_3, "rc_R08PT10_nconst_btag_jet_3/I");
  tree->Branch("rc_R08PT10_nconst_btag_jet_4", &rc_R08PT10_nconst_btag_jet_4, "rc_R08PT10_nconst_btag_jet_4/I");
  tree->Branch("rc_R08PT10_nconst_btag_60_jet_1", &rc_R08PT10_nconst_btag_60_jet_1, "rc_R08PT10_nconst_btag_60_jet_1/I");
  tree->Branch("rc_R08PT10_nconst_btag_60_jet_2", &rc_R08PT10_nconst_btag_60_jet_2, "rc_R08PT10_nconst_btag_60_jet_2/I");
  tree->Branch("rc_R08PT10_nconst_btag_60_jet_3", &rc_R08PT10_nconst_btag_60_jet_3, "rc_R08PT10_nconst_btag_60_jet_3/I");
  tree->Branch("rc_R08PT10_nconst_btag_60_jet_4", &rc_R08PT10_nconst_btag_60_jet_4, "rc_R08PT10_nconst_btag_60_jet_4/I");
  tree->Branch("rc_R08PT10_nconst_btag_70_jet_1", &rc_R08PT10_nconst_btag_70_jet_1, "rc_R08PT10_nconst_btag_70_jet_1/I");
  tree->Branch("rc_R08PT10_nconst_btag_70_jet_2", &rc_R08PT10_nconst_btag_70_jet_2, "rc_R08PT10_nconst_btag_70_jet_2/I");
  tree->Branch("rc_R08PT10_nconst_btag_70_jet_3", &rc_R08PT10_nconst_btag_70_jet_3, "rc_R08PT10_nconst_btag_70_jet_3/I");
  tree->Branch("rc_R08PT10_nconst_btag_70_jet_4", &rc_R08PT10_nconst_btag_70_jet_4, "rc_R08PT10_nconst_btag_70_jet_4/I");
  tree->Branch("rc_R08PT10_nconst_btag_77_jet_1", &rc_R08PT10_nconst_btag_77_jet_1, "rc_R08PT10_nconst_btag_77_jet_1/I");
  tree->Branch("rc_R08PT10_nconst_btag_77_jet_2", &rc_R08PT10_nconst_btag_77_jet_2, "rc_R08PT10_nconst_btag_77_jet_2/I");
  tree->Branch("rc_R08PT10_nconst_btag_77_jet_3", &rc_R08PT10_nconst_btag_77_jet_3, "rc_R08PT10_nconst_btag_77_jet_3/I");
  tree->Branch("rc_R08PT10_nconst_btag_77_jet_4", &rc_R08PT10_nconst_btag_77_jet_4, "rc_R08PT10_nconst_btag_77_jet_4/I");
  tree->Branch("rc_R08PT10_nconst_btag_85_jet_1", &rc_R08PT10_nconst_btag_85_jet_1, "rc_R08PT10_nconst_btag_85_jet_1/I");
  tree->Branch("rc_R08PT10_nconst_btag_85_jet_2", &rc_R08PT10_nconst_btag_85_jet_2, "rc_R08PT10_nconst_btag_85_jet_2/I");
  tree->Branch("rc_R08PT10_nconst_btag_85_jet_3", &rc_R08PT10_nconst_btag_85_jet_3, "rc_R08PT10_nconst_btag_85_jet_3/I");
  tree->Branch("rc_R08PT10_nconst_btag_85_jet_4", &rc_R08PT10_nconst_btag_85_jet_4, "rc_R08PT10_nconst_btag_85_jet_4/I");

  tree->Branch("rc_R08PT10_pt_h", &rc_R08PT10_pt_h, "rc_R08PT10_pt_h/F");
  tree->Branch("rc_R08PT10_pt_W", &rc_R08PT10_pt_W, "rc_R08PT10_pt_W/F");
  tree->Branch("rc_R08PT10_m_h", &rc_R08PT10_m_h, "rc_R08PT10_m_h/F");
  tree->Branch("rc_R08PT10_m_W", &rc_R08PT10_m_W, "rc_R08PT10_m_W/F");
  tree->Branch("rc_R08PT10_SPLIT12_h", &rc_R08PT10_SPLIT12_h, "rc_R08PT10_SPLIT12_h/F");
  tree->Branch("rc_R08PT10_SPLIT12_W", &rc_R08PT10_SPLIT12_W, "rc_R08PT10_SPLIT12_W/F");
  tree->Branch("rc_R08PT10_SPLIT23_h", &rc_R08PT10_SPLIT23_h, "rc_R08PT10_SPLIT23_h/F");
  tree->Branch("rc_R08PT10_SPLIT23_W", &rc_R08PT10_SPLIT23_W, "rc_R08PT10_SPLIT23_W/F");
  tree->Branch("rc_R08PT10_tau21_h", &rc_R08PT10_tau21_h, "rc_R08PT10_tau21_h/F");
  tree->Branch("rc_R08PT10_tau21_W", &rc_R08PT10_tau21_W, "rc_R08PT10_tau21_W/F");
  tree->Branch("rc_R08PT10_tau32_h", &rc_R08PT10_tau32_h, "rc_R08PT10_tau32_h/F");
  tree->Branch("rc_R08PT10_tau32_W", &rc_R08PT10_tau32_W, "rc_R08PT10_tau32_W/F");
  tree->Branch("rc_R08PT10_C2_h", &rc_R08PT10_C2_h, "rc_R08PT10_C2_h/F");
  tree->Branch("rc_R08PT10_C2_W", &rc_R08PT10_C2_W, "rc_R08PT10_C2_W/F");
  tree->Branch("rc_R08PT10_D2_h", &rc_R08PT10_D2_h, "rc_R08PT10_D2_h/F");
  tree->Branch("rc_R08PT10_D2_W", &rc_R08PT10_D2_W, "rc_R08PT10_D2_W/F");
  tree->Branch("rc_R08PT10_dR_Wh", &rc_R08PT10_dR_Wh, "rc_R08PT10_dR_Wh/F");
  tree->Branch("rc_R08PT10_dEta_Wh", &rc_R08PT10_dEta_Wh, "rc_R08PT10_dEta_Wh/F");
  tree->Branch("rc_R08PT10_dPhi_Wh", &rc_R08PT10_dPhi_Wh, "rc_R08PT10_dPhi_Wh/F");
  tree->Branch("rc_R08PT10_nconst_h", &rc_R08PT10_nconst_h, "rc_R08PT10_nconst_h/I");
  tree->Branch("rc_R08PT10_nconst_W", &rc_R08PT10_nconst_W, "rc_R08PT10_nconst_W/I");
  tree->Branch("rc_R08PT10_nconst_btag_h", &rc_R08PT10_nconst_btag_h, "rc_R08PT10_nconst_btag_h/I");
  tree->Branch("rc_R08PT10_nconst_btag_W", &rc_R08PT10_nconst_btag_W, "rc_R08PT10_nconst_btag_W/I");
  tree->Branch("rc_R08PT10_nconst_btag_60_h", &rc_R08PT10_nconst_btag_60_h, "rc_R08PT10_nconst_btag_60_h/I");
  tree->Branch("rc_R08PT10_nconst_btag_60_W", &rc_R08PT10_nconst_btag_60_W, "rc_R08PT10_nconst_btag_60_W/I");
  tree->Branch("rc_R08PT10_nconst_btag_70_h", &rc_R08PT10_nconst_btag_70_h, "rc_R08PT10_nconst_btag_70_h/I");
  tree->Branch("rc_R08PT10_nconst_btag_70_W", &rc_R08PT10_nconst_btag_70_W, "rc_R08PT10_nconst_btag_70_W/I");
  tree->Branch("rc_R08PT10_nconst_btag_77_h", &rc_R08PT10_nconst_btag_77_h, "rc_R08PT10_nconst_btag_77_h/I");
  tree->Branch("rc_R08PT10_nconst_btag_77_W", &rc_R08PT10_nconst_btag_77_W, "rc_R08PT10_nconst_btag_77_W/I");
  tree->Branch("rc_R08PT10_nconst_btag_85_h", &rc_R08PT10_nconst_btag_85_h, "rc_R08PT10_nconst_btag_85_h/I");
  tree->Branch("rc_R08PT10_nconst_btag_85_W", &rc_R08PT10_nconst_btag_85_W, "rc_R08PT10_nconst_btag_85_W/I");

  // R10PT10 reclustered fat-jets
  tree->Branch("rc_R10PT10_dphi_min", &rc_R10PT10_dphi_min, "rc_R10PT10_dphi_min/F");
  tree->Branch("rc_R10PT10_dphi_1jet", &rc_R10PT10_dphi_1jet, "rc_R10PT10_dphi_1jet/F");
  tree->Branch("rc_R10PT10_dphi_sum2jet", &rc_R10PT10_dphi_sum2jet, "rc_R10PT10_dphi_sum2jet/F");
  tree->Branch("rc_R10PT10_dphi_min_alljets", &rc_R10PT10_dphi_min_alljets, "rc_R10PT10_dphi_min_alljets/F");
  tree->Branch("rc_R10PT10_meff_2j", &rc_R10PT10_meff_2j, "rc_R10PT10_meff_2j/F");
  tree->Branch("rc_R10PT10_meff_4j", &rc_R10PT10_meff_4j, "rc_R10PT10_meff_4j/F");
  tree->Branch("rc_R10PT10_meff_nj", &rc_R10PT10_meff_nj, "rc_R10PT10_meff_nj/F");
  tree->Branch("rc_R10PT10_mT_2j", &rc_R10PT10_mT_2j, "rc_R10PT10_mT_2j/F");
  tree->Branch("rc_R10PT10_pt_jet_1", &rc_R10PT10_pt_jet_1, "rc_R10PT10_pt_jet_1/F");
  tree->Branch("rc_R10PT10_pt_jet_2", &rc_R10PT10_pt_jet_2, "rc_R10PT10_pt_jet_2/F");
  tree->Branch("rc_R10PT10_pt_jet_3", &rc_R10PT10_pt_jet_3, "rc_R10PT10_pt_jet_3/F");
  tree->Branch("rc_R10PT10_pt_jet_4", &rc_R10PT10_pt_jet_4, "rc_R10PT10_pt_jet_4/F");
  tree->Branch("rc_R10PT10_m_jet_1", &rc_R10PT10_m_jet_1, "rc_R10PT10_m_jet_1/F");
  tree->Branch("rc_R10PT10_m_jet_2", &rc_R10PT10_m_jet_2, "rc_R10PT10_m_jet_2/F");
  tree->Branch("rc_R10PT10_m_jet_3", &rc_R10PT10_m_jet_3, "rc_R10PT10_m_jet_3/F");
  tree->Branch("rc_R10PT10_m_jet_4", &rc_R10PT10_m_jet_4, "rc_R10PT10_m_jet_4/F");
  tree->Branch("rc_R10PT10_SPLIT12_jet_1", &rc_R10PT10_SPLIT12_jet_1, "rc_R10PT10_SPLIT12_jet_1/F");
  tree->Branch("rc_R10PT10_SPLIT12_jet_2", &rc_R10PT10_SPLIT12_jet_2, "rc_R10PT10_SPLIT12_jet_2/F");
  tree->Branch("rc_R10PT10_SPLIT12_jet_3", &rc_R10PT10_SPLIT12_jet_3, "rc_R10PT10_SPLIT12_jet_3/F");
  tree->Branch("rc_R10PT10_SPLIT12_jet_4", &rc_R10PT10_SPLIT12_jet_4, "rc_R10PT10_SPLIT12_jet_4/F");
  tree->Branch("rc_R10PT10_SPLIT23_jet_1", &rc_R10PT10_SPLIT23_jet_1, "rc_R10PT10_SPLIT23_jet_1/F");
  tree->Branch("rc_R10PT10_SPLIT23_jet_2", &rc_R10PT10_SPLIT23_jet_2, "rc_R10PT10_SPLIT23_jet_2/F");
  tree->Branch("rc_R10PT10_SPLIT23_jet_3", &rc_R10PT10_SPLIT23_jet_3, "rc_R10PT10_SPLIT23_jet_3/F");
  tree->Branch("rc_R10PT10_SPLIT23_jet_4", &rc_R10PT10_SPLIT23_jet_4, "rc_R10PT10_SPLIT23_jet_4/F");
  tree->Branch("rc_R10PT10_tau21_jet_1", &rc_R10PT10_tau21_jet_1, "rc_R10PT10_tau21_jet_1/F");
  tree->Branch("rc_R10PT10_tau21_jet_2", &rc_R10PT10_tau21_jet_2, "rc_R10PT10_tau21_jet_2/F");
  tree->Branch("rc_R10PT10_tau21_jet_3", &rc_R10PT10_tau21_jet_3, "rc_R10PT10_tau21_jet_3/F");
  tree->Branch("rc_R10PT10_tau21_jet_4", &rc_R10PT10_tau21_jet_4, "rc_R10PT10_tau21_jet_4/F");
  tree->Branch("rc_R10PT10_tau32_jet_1", &rc_R10PT10_tau32_jet_1, "rc_R10PT10_tau32_jet_1/F");
  tree->Branch("rc_R10PT10_tau32_jet_2", &rc_R10PT10_tau32_jet_2, "rc_R10PT10_tau32_jet_2/F");
  tree->Branch("rc_R10PT10_tau32_jet_3", &rc_R10PT10_tau32_jet_3, "rc_R10PT10_tau32_jet_3/F");
  tree->Branch("rc_R10PT10_tau32_jet_4", &rc_R10PT10_tau32_jet_4, "rc_R10PT10_tau32_jet_4/F");
  tree->Branch("rc_R10PT10_C2_jet_1", &rc_R10PT10_C2_jet_1, "rc_R10PT10_C2_jet_1/F");
  tree->Branch("rc_R10PT10_C2_jet_2", &rc_R10PT10_C2_jet_2, "rc_R10PT10_C2_jet_2/F");
  tree->Branch("rc_R10PT10_C2_jet_3", &rc_R10PT10_C2_jet_3, "rc_R10PT10_C2_jet_3/F");
  tree->Branch("rc_R10PT10_C2_jet_4", &rc_R10PT10_C2_jet_4, "rc_R10PT10_C2_jet_4/F");
  tree->Branch("rc_R10PT10_D2_jet_1", &rc_R10PT10_D2_jet_1, "rc_R10PT10_D2_jet_1/F");
  tree->Branch("rc_R10PT10_D2_jet_2", &rc_R10PT10_D2_jet_2, "rc_R10PT10_D2_jet_2/F");
  tree->Branch("rc_R10PT10_D2_jet_3", &rc_R10PT10_D2_jet_3, "rc_R10PT10_D2_jet_3/F");
  tree->Branch("rc_R10PT10_D2_jet_4", &rc_R10PT10_D2_jet_4, "rc_R10PT10_D2_jet_4/F");
  tree->Branch("rc_R10PT10_nconst_jet_1", &rc_R10PT10_nconst_jet_1, "rc_R10PT10_nconst_jet_1/I");
  tree->Branch("rc_R10PT10_nconst_jet_2", &rc_R10PT10_nconst_jet_2, "rc_R10PT10_nconst_jet_2/I");
  tree->Branch("rc_R10PT10_nconst_jet_3", &rc_R10PT10_nconst_jet_3, "rc_R10PT10_nconst_jet_3/I");
  tree->Branch("rc_R10PT10_nconst_jet_4", &rc_R10PT10_nconst_jet_4, "rc_R10PT10_nconst_jet_4/I");
  tree->Branch("rc_R10PT10_nconst_btag_jet_1", &rc_R10PT10_nconst_btag_jet_1, "rc_R10PT10_nconst_btag_jet_1/I");
  tree->Branch("rc_R10PT10_nconst_btag_jet_2", &rc_R10PT10_nconst_btag_jet_2, "rc_R10PT10_nconst_btag_jet_2/I");
  tree->Branch("rc_R10PT10_nconst_btag_jet_3", &rc_R10PT10_nconst_btag_jet_3, "rc_R10PT10_nconst_btag_jet_3/I");
  tree->Branch("rc_R10PT10_nconst_btag_jet_4", &rc_R10PT10_nconst_btag_jet_4, "rc_R10PT10_nconst_btag_jet_4/I");
  tree->Branch("rc_R10PT10_nconst_btag_60_jet_1", &rc_R10PT10_nconst_btag_60_jet_1, "rc_R10PT10_nconst_btag_60_jet_1/I");
  tree->Branch("rc_R10PT10_nconst_btag_60_jet_2", &rc_R10PT10_nconst_btag_60_jet_2, "rc_R10PT10_nconst_btag_60_jet_2/I");
  tree->Branch("rc_R10PT10_nconst_btag_60_jet_3", &rc_R10PT10_nconst_btag_60_jet_3, "rc_R10PT10_nconst_btag_60_jet_3/I");
  tree->Branch("rc_R10PT10_nconst_btag_60_jet_4", &rc_R10PT10_nconst_btag_60_jet_4, "rc_R10PT10_nconst_btag_60_jet_4/I");
  tree->Branch("rc_R10PT10_nconst_btag_70_jet_1", &rc_R10PT10_nconst_btag_70_jet_1, "rc_R10PT10_nconst_btag_70_jet_1/I");
  tree->Branch("rc_R10PT10_nconst_btag_70_jet_2", &rc_R10PT10_nconst_btag_70_jet_2, "rc_R10PT10_nconst_btag_70_jet_2/I");
  tree->Branch("rc_R10PT10_nconst_btag_70_jet_3", &rc_R10PT10_nconst_btag_70_jet_3, "rc_R10PT10_nconst_btag_70_jet_3/I");
  tree->Branch("rc_R10PT10_nconst_btag_70_jet_4", &rc_R10PT10_nconst_btag_70_jet_4, "rc_R10PT10_nconst_btag_70_jet_4/I");
  tree->Branch("rc_R10PT10_nconst_btag_77_jet_1", &rc_R10PT10_nconst_btag_77_jet_1, "rc_R10PT10_nconst_btag_77_jet_1/I");
  tree->Branch("rc_R10PT10_nconst_btag_77_jet_2", &rc_R10PT10_nconst_btag_77_jet_2, "rc_R10PT10_nconst_btag_77_jet_2/I");
  tree->Branch("rc_R10PT10_nconst_btag_77_jet_3", &rc_R10PT10_nconst_btag_77_jet_3, "rc_R10PT10_nconst_btag_77_jet_3/I");
  tree->Branch("rc_R10PT10_nconst_btag_77_jet_4", &rc_R10PT10_nconst_btag_77_jet_4, "rc_R10PT10_nconst_btag_77_jet_4/I");
  tree->Branch("rc_R10PT10_nconst_btag_85_jet_1", &rc_R10PT10_nconst_btag_85_jet_1, "rc_R10PT10_nconst_btag_85_jet_1/I");
  tree->Branch("rc_R10PT10_nconst_btag_85_jet_2", &rc_R10PT10_nconst_btag_85_jet_2, "rc_R10PT10_nconst_btag_85_jet_2/I");
  tree->Branch("rc_R10PT10_nconst_btag_85_jet_3", &rc_R10PT10_nconst_btag_85_jet_3, "rc_R10PT10_nconst_btag_85_jet_3/I");
  tree->Branch("rc_R10PT10_nconst_btag_85_jet_4", &rc_R10PT10_nconst_btag_85_jet_4, "rc_R10PT10_nconst_btag_85_jet_4/I");

  tree->Branch("rc_R10PT10_pt_h", &rc_R10PT10_pt_h, "rc_R10PT10_pt_h/F");
  tree->Branch("rc_R10PT10_pt_W", &rc_R10PT10_pt_W, "rc_R10PT10_pt_W/F");
  tree->Branch("rc_R10PT10_m_h", &rc_R10PT10_m_h, "rc_R10PT10_m_h/F");
  tree->Branch("rc_R10PT10_m_W", &rc_R10PT10_m_W, "rc_R10PT10_m_W/F");
  tree->Branch("rc_R10PT10_SPLIT12_h", &rc_R10PT10_SPLIT12_h, "rc_R10PT10_SPLIT12_h/F");
  tree->Branch("rc_R10PT10_SPLIT12_W", &rc_R10PT10_SPLIT12_W, "rc_R10PT10_SPLIT12_W/F");
  tree->Branch("rc_R10PT10_SPLIT23_h", &rc_R10PT10_SPLIT23_h, "rc_R10PT10_SPLIT23_h/F");
  tree->Branch("rc_R10PT10_SPLIT23_W", &rc_R10PT10_SPLIT23_W, "rc_R10PT10_SPLIT23_W/F");
  tree->Branch("rc_R10PT10_tau21_h", &rc_R10PT10_tau21_h, "rc_R10PT10_tau21_h/F");
  tree->Branch("rc_R10PT10_tau21_W", &rc_R10PT10_tau21_W, "rc_R10PT10_tau21_W/F");
  tree->Branch("rc_R10PT10_tau32_h", &rc_R10PT10_tau32_h, "rc_R10PT10_tau32_h/F");
  tree->Branch("rc_R10PT10_tau32_W", &rc_R10PT10_tau32_W, "rc_R10PT10_tau32_W/F");
  tree->Branch("rc_R10PT10_C2_h", &rc_R10PT10_C2_h, "rc_R10PT10_C2_h/F");
  tree->Branch("rc_R10PT10_C2_W", &rc_R10PT10_C2_W, "rc_R10PT10_C2_W/F");
  tree->Branch("rc_R10PT10_D2_h", &rc_R10PT10_D2_h, "rc_R10PT10_D2_h/F");
  tree->Branch("rc_R10PT10_D2_W", &rc_R10PT10_D2_W, "rc_R10PT10_D2_W/F");
  tree->Branch("rc_R10PT10_dR_Wh", &rc_R10PT10_dR_Wh, "rc_R10PT10_dR_Wh/F");
  tree->Branch("rc_R10PT10_dEta_Wh", &rc_R10PT10_dEta_Wh, "rc_R10PT10_dEta_Wh/F");
  tree->Branch("rc_R10PT10_dPhi_Wh", &rc_R10PT10_dPhi_Wh, "rc_R10PT10_dPhi_Wh/F");
  tree->Branch("rc_R10PT10_nconst_h", &rc_R10PT10_nconst_h, "rc_R10PT10_nconst_h/I");
  tree->Branch("rc_R10PT10_nconst_W", &rc_R10PT10_nconst_W, "rc_R10PT10_nconst_W/I");
  tree->Branch("rc_R10PT10_nconst_btag_h", &rc_R10PT10_nconst_btag_h, "rc_R10PT10_nconst_btag_h/I");
  tree->Branch("rc_R10PT10_nconst_btag_W", &rc_R10PT10_nconst_btag_W, "rc_R10PT10_nconst_btag_W/I");
  tree->Branch("rc_R10PT10_nconst_btag_60_h", &rc_R10PT10_nconst_btag_60_h, "rc_R10PT10_nconst_btag_60_h/I");
  tree->Branch("rc_R10PT10_nconst_btag_60_W", &rc_R10PT10_nconst_btag_60_W, "rc_R10PT10_nconst_btag_60_W/I");
  tree->Branch("rc_R10PT10_nconst_btag_70_h", &rc_R10PT10_nconst_btag_70_h, "rc_R10PT10_nconst_btag_70_h/I");
  tree->Branch("rc_R10PT10_nconst_btag_70_W", &rc_R10PT10_nconst_btag_70_W, "rc_R10PT10_nconst_btag_70_W/I");
  tree->Branch("rc_R10PT10_nconst_btag_77_h", &rc_R10PT10_nconst_btag_77_h, "rc_R10PT10_nconst_btag_77_h/I");
  tree->Branch("rc_R10PT10_nconst_btag_77_W", &rc_R10PT10_nconst_btag_77_W, "rc_R10PT10_nconst_btag_77_W/I");
  tree->Branch("rc_R10PT10_nconst_btag_85_h", &rc_R10PT10_nconst_btag_85_h, "rc_R10PT10_nconst_btag_85_h/I");
  tree->Branch("rc_R10PT10_nconst_btag_85_W", &rc_R10PT10_nconst_btag_85_W, "rc_R10PT10_nconst_btag_85_W/I");

  // R12PT10 reclustered fat-jets
  tree->Branch("rc_R12PT10_dphi_min", &rc_R12PT10_dphi_min, "rc_R12PT10_dphi_min/F");
  tree->Branch("rc_R12PT10_dphi_1jet", &rc_R12PT10_dphi_1jet, "rc_R12PT10_dphi_1jet/F");
  tree->Branch("rc_R12PT10_dphi_sum2jet", &rc_R12PT10_dphi_sum2jet, "rc_R12PT10_dphi_sum2jet/F");
  tree->Branch("rc_R12PT10_dphi_min_alljets", &rc_R12PT10_dphi_min_alljets, "rc_R12PT10_dphi_min_alljets/F");
  tree->Branch("rc_R12PT10_meff_2j", &rc_R12PT10_meff_2j, "rc_R12PT10_meff_2j/F");
  tree->Branch("rc_R12PT10_meff_4j", &rc_R12PT10_meff_4j, "rc_R12PT10_meff_4j/F");
  tree->Branch("rc_R12PT10_meff_nj", &rc_R12PT10_meff_nj, "rc_R12PT10_meff_nj/F");
  tree->Branch("rc_R12PT10_mT_2j", &rc_R12PT10_mT_2j, "rc_R12PT10_mT_2j/F");
  tree->Branch("rc_R12PT10_pt_jet_1", &rc_R12PT10_pt_jet_1, "rc_R12PT10_pt_jet_1/F");
  tree->Branch("rc_R12PT10_pt_jet_2", &rc_R12PT10_pt_jet_2, "rc_R12PT10_pt_jet_2/F");
  tree->Branch("rc_R12PT10_pt_jet_3", &rc_R12PT10_pt_jet_3, "rc_R12PT10_pt_jet_3/F");
  tree->Branch("rc_R12PT10_pt_jet_4", &rc_R12PT10_pt_jet_4, "rc_R12PT10_pt_jet_4/F");
  tree->Branch("rc_R12PT10_m_jet_1", &rc_R12PT10_m_jet_1, "rc_R12PT10_m_jet_1/F");
  tree->Branch("rc_R12PT10_m_jet_2", &rc_R12PT10_m_jet_2, "rc_R12PT10_m_jet_2/F");
  tree->Branch("rc_R12PT10_m_jet_3", &rc_R12PT10_m_jet_3, "rc_R12PT10_m_jet_3/F");
  tree->Branch("rc_R12PT10_m_jet_4", &rc_R12PT10_m_jet_4, "rc_R12PT10_m_jet_4/F");
  tree->Branch("rc_R12PT10_SPLIT12_jet_1", &rc_R12PT10_SPLIT12_jet_1, "rc_R12PT10_SPLIT12_jet_1/F");
  tree->Branch("rc_R12PT10_SPLIT12_jet_2", &rc_R12PT10_SPLIT12_jet_2, "rc_R12PT10_SPLIT12_jet_2/F");
  tree->Branch("rc_R12PT10_SPLIT12_jet_3", &rc_R12PT10_SPLIT12_jet_3, "rc_R12PT10_SPLIT12_jet_3/F");
  tree->Branch("rc_R12PT10_SPLIT12_jet_4", &rc_R12PT10_SPLIT12_jet_4, "rc_R12PT10_SPLIT12_jet_4/F");
  tree->Branch("rc_R12PT10_SPLIT23_jet_1", &rc_R12PT10_SPLIT23_jet_1, "rc_R12PT10_SPLIT23_jet_1/F");
  tree->Branch("rc_R12PT10_SPLIT23_jet_2", &rc_R12PT10_SPLIT23_jet_2, "rc_R12PT10_SPLIT23_jet_2/F");
  tree->Branch("rc_R12PT10_SPLIT23_jet_3", &rc_R12PT10_SPLIT23_jet_3, "rc_R12PT10_SPLIT23_jet_3/F");
  tree->Branch("rc_R12PT10_SPLIT23_jet_4", &rc_R12PT10_SPLIT23_jet_4, "rc_R12PT10_SPLIT23_jet_4/F");
  tree->Branch("rc_R12PT10_tau21_jet_1", &rc_R12PT10_tau21_jet_1, "rc_R12PT10_tau21_jet_1/F");
  tree->Branch("rc_R12PT10_tau21_jet_2", &rc_R12PT10_tau21_jet_2, "rc_R12PT10_tau21_jet_2/F");
  tree->Branch("rc_R12PT10_tau21_jet_3", &rc_R12PT10_tau21_jet_3, "rc_R12PT10_tau21_jet_3/F");
  tree->Branch("rc_R12PT10_tau21_jet_4", &rc_R12PT10_tau21_jet_4, "rc_R12PT10_tau21_jet_4/F");
  tree->Branch("rc_R12PT10_tau32_jet_1", &rc_R12PT10_tau32_jet_1, "rc_R12PT10_tau32_jet_1/F");
  tree->Branch("rc_R12PT10_tau32_jet_2", &rc_R12PT10_tau32_jet_2, "rc_R12PT10_tau32_jet_2/F");
  tree->Branch("rc_R12PT10_tau32_jet_3", &rc_R12PT10_tau32_jet_3, "rc_R12PT10_tau32_jet_3/F");
  tree->Branch("rc_R12PT10_tau32_jet_4", &rc_R12PT10_tau32_jet_4, "rc_R12PT10_tau32_jet_4/F");
  tree->Branch("rc_R12PT10_C2_jet_1", &rc_R12PT10_C2_jet_1, "rc_R12PT10_C2_jet_1/F");
  tree->Branch("rc_R12PT10_C2_jet_2", &rc_R12PT10_C2_jet_2, "rc_R12PT10_C2_jet_2/F");
  tree->Branch("rc_R12PT10_C2_jet_3", &rc_R12PT10_C2_jet_3, "rc_R12PT10_C2_jet_3/F");
  tree->Branch("rc_R12PT10_C2_jet_4", &rc_R12PT10_C2_jet_4, "rc_R12PT10_C2_jet_4/F");
  tree->Branch("rc_R12PT10_D2_jet_1", &rc_R12PT10_D2_jet_1, "rc_R12PT10_D2_jet_1/F");
  tree->Branch("rc_R12PT10_D2_jet_2", &rc_R12PT10_D2_jet_2, "rc_R12PT10_D2_jet_2/F");
  tree->Branch("rc_R12PT10_D2_jet_3", &rc_R12PT10_D2_jet_3, "rc_R12PT10_D2_jet_3/F");
  tree->Branch("rc_R12PT10_D2_jet_4", &rc_R12PT10_D2_jet_4, "rc_R12PT10_D2_jet_4/F");
  tree->Branch("rc_R12PT10_nconst_jet_1", &rc_R12PT10_nconst_jet_1, "rc_R12PT10_nconst_jet_1/I");
  tree->Branch("rc_R12PT10_nconst_jet_2", &rc_R12PT10_nconst_jet_2, "rc_R12PT10_nconst_jet_2/I");
  tree->Branch("rc_R12PT10_nconst_jet_3", &rc_R12PT10_nconst_jet_3, "rc_R12PT10_nconst_jet_3/I");
  tree->Branch("rc_R12PT10_nconst_jet_4", &rc_R12PT10_nconst_jet_4, "rc_R12PT10_nconst_jet_4/I");
  tree->Branch("rc_R12PT10_nconst_btag_jet_1", &rc_R12PT10_nconst_btag_jet_1, "rc_R12PT10_nconst_btag_jet_1/I");
  tree->Branch("rc_R12PT10_nconst_btag_jet_2", &rc_R12PT10_nconst_btag_jet_2, "rc_R12PT10_nconst_btag_jet_2/I");
  tree->Branch("rc_R12PT10_nconst_btag_jet_3", &rc_R12PT10_nconst_btag_jet_3, "rc_R12PT10_nconst_btag_jet_3/I");
  tree->Branch("rc_R12PT10_nconst_btag_jet_4", &rc_R12PT10_nconst_btag_jet_4, "rc_R12PT10_nconst_btag_jet_4/I");
  tree->Branch("rc_R12PT10_nconst_btag_60_jet_1", &rc_R12PT10_nconst_btag_60_jet_1, "rc_R12PT10_nconst_btag_60_jet_1/I");
  tree->Branch("rc_R12PT10_nconst_btag_60_jet_2", &rc_R12PT10_nconst_btag_60_jet_2, "rc_R12PT10_nconst_btag_60_jet_2/I");
  tree->Branch("rc_R12PT10_nconst_btag_60_jet_3", &rc_R12PT10_nconst_btag_60_jet_3, "rc_R12PT10_nconst_btag_60_jet_3/I");
  tree->Branch("rc_R12PT10_nconst_btag_60_jet_4", &rc_R12PT10_nconst_btag_60_jet_4, "rc_R12PT10_nconst_btag_60_jet_4/I");
  tree->Branch("rc_R12PT10_nconst_btag_70_jet_1", &rc_R12PT10_nconst_btag_70_jet_1, "rc_R12PT10_nconst_btag_70_jet_1/I");
  tree->Branch("rc_R12PT10_nconst_btag_70_jet_2", &rc_R12PT10_nconst_btag_70_jet_2, "rc_R12PT10_nconst_btag_70_jet_2/I");
  tree->Branch("rc_R12PT10_nconst_btag_70_jet_3", &rc_R12PT10_nconst_btag_70_jet_3, "rc_R12PT10_nconst_btag_70_jet_3/I");
  tree->Branch("rc_R12PT10_nconst_btag_70_jet_4", &rc_R12PT10_nconst_btag_70_jet_4, "rc_R12PT10_nconst_btag_70_jet_4/I");
  tree->Branch("rc_R12PT10_nconst_btag_77_jet_1", &rc_R12PT10_nconst_btag_77_jet_1, "rc_R12PT10_nconst_btag_77_jet_1/I");
  tree->Branch("rc_R12PT10_nconst_btag_77_jet_2", &rc_R12PT10_nconst_btag_77_jet_2, "rc_R12PT10_nconst_btag_77_jet_2/I");
  tree->Branch("rc_R12PT10_nconst_btag_77_jet_3", &rc_R12PT10_nconst_btag_77_jet_3, "rc_R12PT10_nconst_btag_77_jet_3/I");
  tree->Branch("rc_R12PT10_nconst_btag_77_jet_4", &rc_R12PT10_nconst_btag_77_jet_4, "rc_R12PT10_nconst_btag_77_jet_4/I");
  tree->Branch("rc_R12PT10_nconst_btag_85_jet_1", &rc_R12PT10_nconst_btag_85_jet_1, "rc_R12PT10_nconst_btag_85_jet_1/I");
  tree->Branch("rc_R12PT10_nconst_btag_85_jet_2", &rc_R12PT10_nconst_btag_85_jet_2, "rc_R12PT10_nconst_btag_85_jet_2/I");
  tree->Branch("rc_R12PT10_nconst_btag_85_jet_3", &rc_R12PT10_nconst_btag_85_jet_3, "rc_R12PT10_nconst_btag_85_jet_3/I");
  tree->Branch("rc_R12PT10_nconst_btag_85_jet_4", &rc_R12PT10_nconst_btag_85_jet_4, "rc_R12PT10_nconst_btag_85_jet_4/I");

  tree->Branch("rc_R12PT10_pt_h", &rc_R12PT10_pt_h, "rc_R12PT10_pt_h/F");
  tree->Branch("rc_R12PT10_pt_W", &rc_R12PT10_pt_W, "rc_R12PT10_pt_W/F");
  tree->Branch("rc_R12PT10_m_h", &rc_R12PT10_m_h, "rc_R12PT10_m_h/F");
  tree->Branch("rc_R12PT10_m_W", &rc_R12PT10_m_W, "rc_R12PT10_m_W/F");
  tree->Branch("rc_R12PT10_SPLIT12_h", &rc_R12PT10_SPLIT12_h, "rc_R12PT10_SPLIT12_h/F");
  tree->Branch("rc_R12PT10_SPLIT12_W", &rc_R12PT10_SPLIT12_W, "rc_R12PT10_SPLIT12_W/F");
  tree->Branch("rc_R12PT10_SPLIT23_h", &rc_R12PT10_SPLIT23_h, "rc_R12PT10_SPLIT23_h/F");
  tree->Branch("rc_R12PT10_SPLIT23_W", &rc_R12PT10_SPLIT23_W, "rc_R12PT10_SPLIT23_W/F");
  tree->Branch("rc_R12PT10_tau21_h", &rc_R12PT10_tau21_h, "rc_R12PT10_tau21_h/F");
  tree->Branch("rc_R12PT10_tau21_W", &rc_R12PT10_tau21_W, "rc_R12PT10_tau21_W/F");
  tree->Branch("rc_R12PT10_tau32_h", &rc_R12PT10_tau32_h, "rc_R12PT10_tau32_h/F");
  tree->Branch("rc_R12PT10_tau32_W", &rc_R12PT10_tau32_W, "rc_R12PT10_tau32_W/F");
  tree->Branch("rc_R12PT10_C2_h", &rc_R12PT10_C2_h, "rc_R12PT10_C2_h/F");
  tree->Branch("rc_R12PT10_C2_W", &rc_R12PT10_C2_W, "rc_R12PT10_C2_W/F");
  tree->Branch("rc_R12PT10_D2_h", &rc_R12PT10_D2_h, "rc_R12PT10_D2_h/F");
  tree->Branch("rc_R12PT10_D2_W", &rc_R12PT10_D2_W, "rc_R12PT10_D2_W/F");
  tree->Branch("rc_R12PT10_dR_Wh", &rc_R12PT10_dR_Wh, "rc_R12PT10_dR_Wh/F");
  tree->Branch("rc_R12PT10_dEta_Wh", &rc_R12PT10_dEta_Wh, "rc_R12PT10_dEta_Wh/F");
  tree->Branch("rc_R12PT10_dPhi_Wh", &rc_R12PT10_dPhi_Wh, "rc_R12PT10_dPhi_Wh/F");
  tree->Branch("rc_R12PT10_nconst_h", &rc_R12PT10_nconst_h, "rc_R12PT10_nconst_h/I");
  tree->Branch("rc_R12PT10_nconst_W", &rc_R12PT10_nconst_W, "rc_R12PT10_nconst_W/I");
  tree->Branch("rc_R12PT10_nconst_btag_h", &rc_R12PT10_nconst_btag_h, "rc_R12PT10_nconst_btag_h/I");
  tree->Branch("rc_R12PT10_nconst_btag_W", &rc_R12PT10_nconst_btag_W, "rc_R12PT10_nconst_btag_W/I");
  tree->Branch("rc_R12PT10_nconst_btag_60_h", &rc_R12PT10_nconst_btag_60_h, "rc_R12PT10_nconst_btag_60_h/I");
  tree->Branch("rc_R12PT10_nconst_btag_60_W", &rc_R12PT10_nconst_btag_60_W, "rc_R12PT10_nconst_btag_60_W/I");
  tree->Branch("rc_R12PT10_nconst_btag_70_h", &rc_R12PT10_nconst_btag_70_h, "rc_R12PT10_nconst_btag_70_h/I");
  tree->Branch("rc_R12PT10_nconst_btag_70_W", &rc_R12PT10_nconst_btag_70_W, "rc_R12PT10_nconst_btag_70_W/I");
  tree->Branch("rc_R12PT10_nconst_btag_77_h", &rc_R12PT10_nconst_btag_77_h, "rc_R12PT10_nconst_btag_77_h/I");
  tree->Branch("rc_R12PT10_nconst_btag_77_W", &rc_R12PT10_nconst_btag_77_W, "rc_R12PT10_nconst_btag_77_W/I");
  tree->Branch("rc_R12PT10_nconst_btag_85_h", &rc_R12PT10_nconst_btag_85_h, "rc_R12PT10_nconst_btag_85_h/I");
  tree->Branch("rc_R12PT10_nconst_btag_85_W", &rc_R12PT10_nconst_btag_85_W, "rc_R12PT10_nconst_btag_85_W/I");

  // R15PT10 reclustered fat-jets
  tree->Branch("rc_R15PT10_dphi_min", &rc_R15PT10_dphi_min, "rc_R15PT10_dphi_min/F");
  tree->Branch("rc_R15PT10_dphi_1jet", &rc_R15PT10_dphi_1jet, "rc_R15PT10_dphi_1jet/F");
  tree->Branch("rc_R15PT10_dphi_sum2jet", &rc_R15PT10_dphi_sum2jet, "rc_R15PT10_dphi_sum2jet/F");
  tree->Branch("rc_R15PT10_dphi_min_alljets", &rc_R15PT10_dphi_min_alljets, "rc_R15PT10_dphi_min_alljets/F");
  tree->Branch("rc_R15PT10_meff_2j", &rc_R15PT10_meff_2j, "rc_R15PT10_meff_2j/F");
  tree->Branch("rc_R15PT10_meff_4j", &rc_R15PT10_meff_4j, "rc_R15PT10_meff_4j/F");
  tree->Branch("rc_R15PT10_meff_nj", &rc_R15PT10_meff_nj, "rc_R15PT10_meff_nj/F");
  tree->Branch("rc_R15PT10_mT_2j", &rc_R15PT10_mT_2j, "rc_R15PT10_mT_2j/F");
  tree->Branch("rc_R15PT10_pt_jet_1", &rc_R15PT10_pt_jet_1, "rc_R15PT10_pt_jet_1/F");
  tree->Branch("rc_R15PT10_pt_jet_2", &rc_R15PT10_pt_jet_2, "rc_R15PT10_pt_jet_2/F");
  tree->Branch("rc_R15PT10_pt_jet_3", &rc_R15PT10_pt_jet_3, "rc_R15PT10_pt_jet_3/F");
  tree->Branch("rc_R15PT10_pt_jet_4", &rc_R15PT10_pt_jet_4, "rc_R15PT10_pt_jet_4/F");
  tree->Branch("rc_R15PT10_m_jet_1", &rc_R15PT10_m_jet_1, "rc_R15PT10_m_jet_1/F");
  tree->Branch("rc_R15PT10_m_jet_2", &rc_R15PT10_m_jet_2, "rc_R15PT10_m_jet_2/F");
  tree->Branch("rc_R15PT10_m_jet_3", &rc_R15PT10_m_jet_3, "rc_R15PT10_m_jet_3/F");
  tree->Branch("rc_R15PT10_m_jet_4", &rc_R15PT10_m_jet_4, "rc_R15PT10_m_jet_4/F");
  tree->Branch("rc_R15PT10_SPLIT12_jet_1", &rc_R15PT10_SPLIT12_jet_1, "rc_R15PT10_SPLIT12_jet_1/F");
  tree->Branch("rc_R15PT10_SPLIT12_jet_2", &rc_R15PT10_SPLIT12_jet_2, "rc_R15PT10_SPLIT12_jet_2/F");
  tree->Branch("rc_R15PT10_SPLIT12_jet_3", &rc_R15PT10_SPLIT12_jet_3, "rc_R15PT10_SPLIT12_jet_3/F");
  tree->Branch("rc_R15PT10_SPLIT12_jet_4", &rc_R15PT10_SPLIT12_jet_4, "rc_R15PT10_SPLIT12_jet_4/F");
  tree->Branch("rc_R15PT10_SPLIT23_jet_1", &rc_R15PT10_SPLIT23_jet_1, "rc_R15PT10_SPLIT23_jet_1/F");
  tree->Branch("rc_R15PT10_SPLIT23_jet_2", &rc_R15PT10_SPLIT23_jet_2, "rc_R15PT10_SPLIT23_jet_2/F");
  tree->Branch("rc_R15PT10_SPLIT23_jet_3", &rc_R15PT10_SPLIT23_jet_3, "rc_R15PT10_SPLIT23_jet_3/F");
  tree->Branch("rc_R15PT10_SPLIT23_jet_4", &rc_R15PT10_SPLIT23_jet_4, "rc_R15PT10_SPLIT23_jet_4/F");
  tree->Branch("rc_R15PT10_tau21_jet_1", &rc_R15PT10_tau21_jet_1, "rc_R15PT10_tau21_jet_1/F");
  tree->Branch("rc_R15PT10_tau21_jet_2", &rc_R15PT10_tau21_jet_2, "rc_R15PT10_tau21_jet_2/F");
  tree->Branch("rc_R15PT10_tau21_jet_3", &rc_R15PT10_tau21_jet_3, "rc_R15PT10_tau21_jet_3/F");
  tree->Branch("rc_R15PT10_tau21_jet_4", &rc_R15PT10_tau21_jet_4, "rc_R15PT10_tau21_jet_4/F");
  tree->Branch("rc_R15PT10_tau32_jet_1", &rc_R15PT10_tau32_jet_1, "rc_R15PT10_tau32_jet_1/F");
  tree->Branch("rc_R15PT10_tau32_jet_2", &rc_R15PT10_tau32_jet_2, "rc_R15PT10_tau32_jet_2/F");
  tree->Branch("rc_R15PT10_tau32_jet_3", &rc_R15PT10_tau32_jet_3, "rc_R15PT10_tau32_jet_3/F");
  tree->Branch("rc_R15PT10_tau32_jet_4", &rc_R15PT10_tau32_jet_4, "rc_R15PT10_tau32_jet_4/F");
  tree->Branch("rc_R15PT10_C2_jet_1", &rc_R15PT10_C2_jet_1, "rc_R15PT10_C2_jet_1/F");
  tree->Branch("rc_R15PT10_C2_jet_2", &rc_R15PT10_C2_jet_2, "rc_R15PT10_C2_jet_2/F");
  tree->Branch("rc_R15PT10_C2_jet_3", &rc_R15PT10_C2_jet_3, "rc_R15PT10_C2_jet_3/F");
  tree->Branch("rc_R15PT10_C2_jet_4", &rc_R15PT10_C2_jet_4, "rc_R15PT10_C2_jet_4/F");
  tree->Branch("rc_R15PT10_D2_jet_1", &rc_R15PT10_D2_jet_1, "rc_R15PT10_D2_jet_1/F");
  tree->Branch("rc_R15PT10_D2_jet_2", &rc_R15PT10_D2_jet_2, "rc_R15PT10_D2_jet_2/F");
  tree->Branch("rc_R15PT10_D2_jet_3", &rc_R15PT10_D2_jet_3, "rc_R15PT10_D2_jet_3/F");
  tree->Branch("rc_R15PT10_D2_jet_4", &rc_R15PT10_D2_jet_4, "rc_R15PT10_D2_jet_4/F");
  tree->Branch("rc_R15PT10_nconst_jet_1", &rc_R15PT10_nconst_jet_1, "rc_R15PT10_nconst_jet_1/I");
  tree->Branch("rc_R15PT10_nconst_jet_2", &rc_R15PT10_nconst_jet_2, "rc_R15PT10_nconst_jet_2/I");
  tree->Branch("rc_R15PT10_nconst_jet_3", &rc_R15PT10_nconst_jet_3, "rc_R15PT10_nconst_jet_3/I");
  tree->Branch("rc_R15PT10_nconst_jet_4", &rc_R15PT10_nconst_jet_4, "rc_R15PT10_nconst_jet_4/I");
  tree->Branch("rc_R15PT10_nconst_btag_jet_1", &rc_R15PT10_nconst_btag_jet_1, "rc_R15PT10_nconst_btag_jet_1/I");
  tree->Branch("rc_R15PT10_nconst_btag_jet_2", &rc_R15PT10_nconst_btag_jet_2, "rc_R15PT10_nconst_btag_jet_2/I");
  tree->Branch("rc_R15PT10_nconst_btag_jet_3", &rc_R15PT10_nconst_btag_jet_3, "rc_R15PT10_nconst_btag_jet_3/I");
  tree->Branch("rc_R15PT10_nconst_btag_jet_4", &rc_R15PT10_nconst_btag_jet_4, "rc_R15PT10_nconst_btag_jet_4/I");
  tree->Branch("rc_R15PT10_nconst_btag_60_jet_1", &rc_R15PT10_nconst_btag_60_jet_1, "rc_R15PT10_nconst_btag_60_jet_1/I");
  tree->Branch("rc_R15PT10_nconst_btag_60_jet_2", &rc_R15PT10_nconst_btag_60_jet_2, "rc_R15PT10_nconst_btag_60_jet_2/I");
  tree->Branch("rc_R15PT10_nconst_btag_60_jet_3", &rc_R15PT10_nconst_btag_60_jet_3, "rc_R15PT10_nconst_btag_60_jet_3/I");
  tree->Branch("rc_R15PT10_nconst_btag_60_jet_4", &rc_R15PT10_nconst_btag_60_jet_4, "rc_R15PT10_nconst_btag_60_jet_4/I");
  tree->Branch("rc_R15PT10_nconst_btag_70_jet_1", &rc_R15PT10_nconst_btag_70_jet_1, "rc_R15PT10_nconst_btag_70_jet_1/I");
  tree->Branch("rc_R15PT10_nconst_btag_70_jet_2", &rc_R15PT10_nconst_btag_70_jet_2, "rc_R15PT10_nconst_btag_70_jet_2/I");
  tree->Branch("rc_R15PT10_nconst_btag_70_jet_3", &rc_R15PT10_nconst_btag_70_jet_3, "rc_R15PT10_nconst_btag_70_jet_3/I");
  tree->Branch("rc_R15PT10_nconst_btag_70_jet_4", &rc_R15PT10_nconst_btag_70_jet_4, "rc_R15PT10_nconst_btag_70_jet_4/I");
  tree->Branch("rc_R15PT10_nconst_btag_77_jet_1", &rc_R15PT10_nconst_btag_77_jet_1, "rc_R15PT10_nconst_btag_77_jet_1/I");
  tree->Branch("rc_R15PT10_nconst_btag_77_jet_2", &rc_R15PT10_nconst_btag_77_jet_2, "rc_R15PT10_nconst_btag_77_jet_2/I");
  tree->Branch("rc_R15PT10_nconst_btag_77_jet_3", &rc_R15PT10_nconst_btag_77_jet_3, "rc_R15PT10_nconst_btag_77_jet_3/I");
  tree->Branch("rc_R15PT10_nconst_btag_77_jet_4", &rc_R15PT10_nconst_btag_77_jet_4, "rc_R15PT10_nconst_btag_77_jet_4/I");
  tree->Branch("rc_R15PT10_nconst_btag_85_jet_1", &rc_R15PT10_nconst_btag_85_jet_1, "rc_R15PT10_nconst_btag_85_jet_1/I");
  tree->Branch("rc_R15PT10_nconst_btag_85_jet_2", &rc_R15PT10_nconst_btag_85_jet_2, "rc_R15PT10_nconst_btag_85_jet_2/I");
  tree->Branch("rc_R15PT10_nconst_btag_85_jet_3", &rc_R15PT10_nconst_btag_85_jet_3, "rc_R15PT10_nconst_btag_85_jet_3/I");
  tree->Branch("rc_R15PT10_nconst_btag_85_jet_4", &rc_R15PT10_nconst_btag_85_jet_4, "rc_R15PT10_nconst_btag_85_jet_4/I");

  tree->Branch("rc_R15PT10_pt_h", &rc_R15PT10_pt_h, "rc_R15PT10_pt_h/F");
  tree->Branch("rc_R15PT10_pt_W", &rc_R15PT10_pt_W, "rc_R15PT10_pt_W/F");
  tree->Branch("rc_R15PT10_m_h", &rc_R15PT10_m_h, "rc_R15PT10_m_h/F");
  tree->Branch("rc_R15PT10_m_W", &rc_R15PT10_m_W, "rc_R15PT10_m_W/F");
  tree->Branch("rc_R15PT10_SPLIT12_h", &rc_R15PT10_SPLIT12_h, "rc_R15PT10_SPLIT12_h/F");
  tree->Branch("rc_R15PT10_SPLIT12_W", &rc_R15PT10_SPLIT12_W, "rc_R15PT10_SPLIT12_W/F");
  tree->Branch("rc_R15PT10_SPLIT23_h", &rc_R15PT10_SPLIT23_h, "rc_R15PT10_SPLIT23_h/F");
  tree->Branch("rc_R15PT10_SPLIT23_W", &rc_R15PT10_SPLIT23_W, "rc_R15PT10_SPLIT23_W/F");
  tree->Branch("rc_R15PT10_tau21_h", &rc_R15PT10_tau21_h, "rc_R15PT10_tau21_h/F");
  tree->Branch("rc_R15PT10_tau21_W", &rc_R15PT10_tau21_W, "rc_R15PT10_tau21_W/F");
  tree->Branch("rc_R15PT10_tau32_h", &rc_R15PT10_tau32_h, "rc_R15PT10_tau32_h/F");
  tree->Branch("rc_R15PT10_tau32_W", &rc_R15PT10_tau32_W, "rc_R15PT10_tau32_W/F");
  tree->Branch("rc_R15PT10_C2_h", &rc_R15PT10_C2_h, "rc_R15PT10_C2_h/F");
  tree->Branch("rc_R15PT10_C2_W", &rc_R15PT10_C2_W, "rc_R15PT10_C2_W/F");
  tree->Branch("rc_R15PT10_D2_h", &rc_R15PT10_D2_h, "rc_R15PT10_D2_h/F");
  tree->Branch("rc_R15PT10_D2_W", &rc_R15PT10_D2_W, "rc_R15PT10_D2_W/F");
  tree->Branch("rc_R15PT10_dR_Wh", &rc_R15PT10_dR_Wh, "rc_R15PT10_dR_Wh/F");
  tree->Branch("rc_R15PT10_dEta_Wh", &rc_R15PT10_dEta_Wh, "rc_R15PT10_dEta_Wh/F");
  tree->Branch("rc_R15PT10_dPhi_Wh", &rc_R15PT10_dPhi_Wh, "rc_R15PT10_dPhi_Wh/F");
  tree->Branch("rc_R15PT10_nconst_h", &rc_R15PT10_nconst_h, "rc_R15PT10_nconst_h/I");
  tree->Branch("rc_R15PT10_nconst_W", &rc_R15PT10_nconst_W, "rc_R15PT10_nconst_W/I");
  tree->Branch("rc_R15PT10_nconst_btag_h", &rc_R15PT10_nconst_btag_h, "rc_R15PT10_nconst_btag_h/I");
  tree->Branch("rc_R15PT10_nconst_btag_W", &rc_R15PT10_nconst_btag_W, "rc_R15PT10_nconst_btag_W/I");
  tree->Branch("rc_R15PT10_nconst_btag_60_h", &rc_R15PT10_nconst_btag_60_h, "rc_R15PT10_nconst_btag_60_h/I");
  tree->Branch("rc_R15PT10_nconst_btag_60_W", &rc_R15PT10_nconst_btag_60_W, "rc_R15PT10_nconst_btag_60_W/I");
  tree->Branch("rc_R15PT10_nconst_btag_70_h", &rc_R15PT10_nconst_btag_70_h, "rc_R15PT10_nconst_btag_70_h/I");
  tree->Branch("rc_R15PT10_nconst_btag_70_W", &rc_R15PT10_nconst_btag_70_W, "rc_R15PT10_nconst_btag_70_W/I");
  tree->Branch("rc_R15PT10_nconst_btag_77_h", &rc_R15PT10_nconst_btag_77_h, "rc_R15PT10_nconst_btag_77_h/I");
  tree->Branch("rc_R15PT10_nconst_btag_77_W", &rc_R15PT10_nconst_btag_77_W, "rc_R15PT10_nconst_btag_77_W/I");
  tree->Branch("rc_R15PT10_nconst_btag_85_h", &rc_R15PT10_nconst_btag_85_h, "rc_R15PT10_nconst_btag_85_h/I");
  tree->Branch("rc_R15PT10_nconst_btag_85_W", &rc_R15PT10_nconst_btag_85_W, "rc_R15PT10_nconst_btag_85_W/I");

}

void mbj_flatten_tree::ResetOutTreeBranches() {

  // Additional flat output variables
  pt_jet_1 = 0.;
  pt_jet_2 = 0.;
  pt_jet_3 = 0.;
  pt_jet_4 = 0.;
  pt_bjet_1_60 = 0.;
  pt_bjet_2_60 = 0.;
  pt_bjet_3_60 = 0.;
  pt_bjet_4_60 = 0.;
  pt_bjet_1_70 = 0.;
  pt_bjet_2_70 = 0.;
  pt_bjet_3_70 = 0.;
  pt_bjet_4_70 = 0.;
  pt_bjet_1_77 = 0.;
  pt_bjet_2_77 = 0.;
  pt_bjet_3_77 = 0.;
  pt_bjet_4_77 = 0.;
  pt_bjet_1_85 = 0.;
  pt_bjet_2_85 = 0.;
  pt_bjet_3_85 = 0.;
  pt_bjet_4_85 = 0.;

  ak10_dphi_min = 1000.;
  ak10_dphi_1jet = 1000.;
  ak10_dphi_sum2jet = 1000.;
  ak10_dphi_min_alljets = 1000.;
  ak10_meff_2j = 0.;
  ak10_meff_4j = 0.;
  ak10_meff_nj = 0.;
  ak10_mT_2j = 0.;
  ak10_pt_jet_1 = 0.;
  ak10_pt_jet_2 = 0.;
  ak10_pt_jet_3 = 0.;
  ak10_pt_jet_4 = 0.;
  ak10_m_jet_1 = 0.;
  ak10_m_jet_2 = 0.;
  ak10_m_jet_3 = 0.;
  ak10_m_jet_4 = 0.;
  ak10_SPLIT12_jet_1 = -1.;
  ak10_SPLIT12_jet_2 = -1.;
  ak10_SPLIT12_jet_3 = -1.;
  ak10_SPLIT12_jet_4 = -1.;
  ak10_SPLIT23_jet_1 = -1.;
  ak10_SPLIT23_jet_2 = -1.;
  ak10_SPLIT23_jet_3 = -1.;
  ak10_SPLIT23_jet_4 = -1.;
  ak10_tau21_jet_1 = -1.;
  ak10_tau21_jet_2 = -1.;
  ak10_tau21_jet_3 = -1.;
  ak10_tau21_jet_4 = -1.;
  ak10_tau32_jet_1 = -1.;
  ak10_tau32_jet_2 = -1.;
  ak10_tau32_jet_3 = -1.;
  ak10_tau32_jet_4 = -1.;
  ak10_C2_jet_1 = -1.;
  ak10_C2_jet_2 = -1.;
  ak10_C2_jet_3 = -1.;
  ak10_C2_jet_4 = -1.;
  ak10_D2_jet_1 = -1.;
  ak10_D2_jet_2 = -1.;
  ak10_D2_jet_3 = -1.;
  ak10_D2_jet_4 = -1.;
  ak10_assoc_ak4_n_jet_1 = -1;
  ak10_assoc_ak4_n_jet_2 = -1;
  ak10_assoc_ak4_n_jet_3 = -1;
  ak10_assoc_ak4_n_jet_4 = -1;
  ak10_assoc_ak4_btag_n_jet_1 = -1;
  ak10_assoc_ak4_btag_n_jet_2 = -1;
  ak10_assoc_ak4_btag_n_jet_3 = -1;
  ak10_assoc_ak4_btag_n_jet_4 = -1;
  ak10_ghost_ak2_trk_n_jet_1 = -1;
  ak10_ghost_ak2_trk_n_jet_2 = -1;
  ak10_ghost_ak2_trk_n_jet_3 = -1;
  ak10_ghost_ak2_trk_n_jet_4 = -1;

  ak10_pt_h = 0.;
  ak10_pt_W = 0.;
  ak10_m_h = 0.;
  ak10_m_W = 0.;
  ak10_SPLIT12_h = -1.;
  ak10_SPLIT12_W = -1.;
  ak10_SPLIT23_h = -1.;
  ak10_SPLIT23_W = -1.;
  ak10_tau21_h = -1.;
  ak10_tau21_W = -1.;
  ak10_tau32_h = -1.;
  ak10_tau32_W = -1.;
  ak10_C2_h = -1.;
  ak10_C2_W = -1.;
  ak10_D2_h = -1.;
  ak10_D2_W = -1.;
  ak10_dR_Wh = -1.;
  ak10_dEta_Wh = -1.;
  ak10_dPhi_Wh = -1.;
  ak10_assoc_ak4_n_h = -1;
  ak10_assoc_ak4_n_W = -1;
  ak10_assoc_ak4_btag_n_h = -1;
  ak10_assoc_ak4_btag_n_W = -1;
  ak10_ghost_ak2_trk_n_h = -1;
  ak10_ghost_ak2_trk_n_W = -1;

  rc_R08PT10_dphi_min = 1000.;
  rc_R08PT10_dphi_1jet = 1000.;
  rc_R08PT10_dphi_sum2jet = 1000.;
  rc_R08PT10_dphi_min_alljets = 1000.;
  rc_R08PT10_meff_2j = 0.;
  rc_R08PT10_meff_4j = 0.;
  rc_R08PT10_meff_nj = 0.;
  rc_R08PT10_mT_2j = 0.;
  rc_R08PT10_pt_jet_1 = 0.;
  rc_R08PT10_pt_jet_2 = 0.;
  rc_R08PT10_pt_jet_3 = 0.;
  rc_R08PT10_pt_jet_4 = 0.;
  rc_R08PT10_m_jet_1 = 0.;
  rc_R08PT10_m_jet_2 = 0.;
  rc_R08PT10_m_jet_3 = 0.;
  rc_R08PT10_m_jet_4 = 0.;
  rc_R08PT10_SPLIT12_jet_1 = -1.;
  rc_R08PT10_SPLIT12_jet_2 = -1.;
  rc_R08PT10_SPLIT12_jet_3 = -1.;
  rc_R08PT10_SPLIT12_jet_4 = -1.;
  rc_R08PT10_SPLIT23_jet_1 = -1.;
  rc_R08PT10_SPLIT23_jet_2 = -1.;
  rc_R08PT10_SPLIT23_jet_3 = -1.;
  rc_R08PT10_SPLIT23_jet_4 = -1.;
  rc_R08PT10_tau21_jet_1 = -1.;
  rc_R08PT10_tau21_jet_2 = -1.;
  rc_R08PT10_tau21_jet_3 = -1.;
  rc_R08PT10_tau21_jet_4 = -1.;
  rc_R08PT10_tau32_jet_1 = -1.;
  rc_R08PT10_tau32_jet_2 = -1.;
  rc_R08PT10_tau32_jet_3 = -1.;
  rc_R08PT10_tau32_jet_4 = -1.;
  rc_R08PT10_C2_jet_1 = -1.;
  rc_R08PT10_C2_jet_2 = -1.;
  rc_R08PT10_C2_jet_3 = -1.;
  rc_R08PT10_C2_jet_4 = -1.;
  rc_R08PT10_D2_jet_1 = -1.;
  rc_R08PT10_D2_jet_2 = -1.;
  rc_R08PT10_D2_jet_3 = -1.;
  rc_R08PT10_D2_jet_4 = -1.;
  rc_R08PT10_nconst_jet_1 = -1;
  rc_R08PT10_nconst_jet_2 = -1;
  rc_R08PT10_nconst_jet_3 = -1;
  rc_R08PT10_nconst_jet_4 = -1;
  rc_R08PT10_nconst_btag_jet_1 = -1;
  rc_R08PT10_nconst_btag_jet_2 = -1;
  rc_R08PT10_nconst_btag_jet_3 = -1;
  rc_R08PT10_nconst_btag_jet_4 = -1;
  rc_R08PT10_nconst_btag_60_jet_1 = -1;
  rc_R08PT10_nconst_btag_60_jet_2 = -1;
  rc_R08PT10_nconst_btag_60_jet_3 = -1;
  rc_R08PT10_nconst_btag_60_jet_4 = -1;
  rc_R08PT10_nconst_btag_70_jet_1 = -1;
  rc_R08PT10_nconst_btag_70_jet_2 = -1;
  rc_R08PT10_nconst_btag_70_jet_3 = -1;
  rc_R08PT10_nconst_btag_70_jet_4 = -1;
  rc_R08PT10_nconst_btag_77_jet_1 = -1;
  rc_R08PT10_nconst_btag_77_jet_2 = -1;
  rc_R08PT10_nconst_btag_77_jet_3 = -1;
  rc_R08PT10_nconst_btag_77_jet_4 = -1;
  rc_R08PT10_nconst_btag_85_jet_1 = -1;
  rc_R08PT10_nconst_btag_85_jet_2 = -1;
  rc_R08PT10_nconst_btag_85_jet_3 = -1;
  rc_R08PT10_nconst_btag_85_jet_4 = -1;

  rc_R08PT10_pt_h = 0.;
  rc_R08PT10_pt_W = 0.;
  rc_R08PT10_m_h = 0.;
  rc_R08PT10_m_W = 0.;
  rc_R08PT10_SPLIT12_h = -1.;
  rc_R08PT10_SPLIT12_W = -1.;
  rc_R08PT10_SPLIT23_h = -1.;
  rc_R08PT10_SPLIT23_W = -1.;
  rc_R08PT10_tau21_h = -1.;
  rc_R08PT10_tau21_W = -1.;
  rc_R08PT10_tau32_h = -1.;
  rc_R08PT10_tau32_W = -1.;
  rc_R08PT10_C2_h = -1.;
  rc_R08PT10_C2_W = -1.;
  rc_R08PT10_D2_h = -1.;
  rc_R08PT10_D2_W = -1.;
  rc_R08PT10_dR_Wh = -1.;
  rc_R08PT10_dEta_Wh = -1.;
  rc_R08PT10_dPhi_Wh = -1.;
  rc_R08PT10_nconst_h = -1;
  rc_R08PT10_nconst_W = -1;
  rc_R08PT10_nconst_btag_h = -1;
  rc_R08PT10_nconst_btag_W = -1;
  rc_R08PT10_nconst_btag_60_h = -1;
  rc_R08PT10_nconst_btag_60_W = -1;
  rc_R08PT10_nconst_btag_70_h = -1;
  rc_R08PT10_nconst_btag_70_W = -1;
  rc_R08PT10_nconst_btag_77_h = -1;
  rc_R08PT10_nconst_btag_77_W = -1;
  rc_R08PT10_nconst_btag_85_h = -1;
  rc_R08PT10_nconst_btag_85_W = -1;

  rc_R10PT10_dphi_min = 1000.;
  rc_R10PT10_dphi_1jet = 1000.;
  rc_R10PT10_dphi_sum2jet = 1000.;
  rc_R10PT10_dphi_min_alljets = 1000.;
  rc_R10PT10_meff_2j = 0.;
  rc_R10PT10_meff_4j = 0.;
  rc_R10PT10_meff_nj = 0.;
  rc_R10PT10_mT_2j = 0.;
  rc_R10PT10_pt_jet_1 = 0.;
  rc_R10PT10_pt_jet_2 = 0.;
  rc_R10PT10_pt_jet_3 = 0.;
  rc_R10PT10_pt_jet_4 = 0.;
  rc_R10PT10_m_jet_1 = 0.;
  rc_R10PT10_m_jet_2 = 0.;
  rc_R10PT10_m_jet_3 = 0.;
  rc_R10PT10_m_jet_4 = 0.;
  rc_R10PT10_SPLIT12_jet_1 = -1.;
  rc_R10PT10_SPLIT12_jet_2 = -1.;
  rc_R10PT10_SPLIT12_jet_3 = -1.;
  rc_R10PT10_SPLIT12_jet_4 = -1.;
  rc_R10PT10_SPLIT23_jet_1 = -1.;
  rc_R10PT10_SPLIT23_jet_2 = -1.;
  rc_R10PT10_SPLIT23_jet_3 = -1.;
  rc_R10PT10_SPLIT23_jet_4 = -1.;
  rc_R10PT10_tau21_jet_1 = -1.;
  rc_R10PT10_tau21_jet_2 = -1.;
  rc_R10PT10_tau21_jet_3 = -1.;
  rc_R10PT10_tau21_jet_4 = -1.;
  rc_R10PT10_tau32_jet_1 = -1.;
  rc_R10PT10_tau32_jet_2 = -1.;
  rc_R10PT10_tau32_jet_3 = -1.;
  rc_R10PT10_tau32_jet_4 = -1.;
  rc_R10PT10_C2_jet_1 = -1.;
  rc_R10PT10_C2_jet_2 = -1.;
  rc_R10PT10_C2_jet_3 = -1.;
  rc_R10PT10_C2_jet_4 = -1.;
  rc_R10PT10_D2_jet_1 = -1.;
  rc_R10PT10_D2_jet_2 = -1.;
  rc_R10PT10_D2_jet_3 = -1.;
  rc_R10PT10_D2_jet_4 = -1.;
  rc_R10PT10_nconst_jet_1 = -1;
  rc_R10PT10_nconst_jet_2 = -1;
  rc_R10PT10_nconst_jet_3 = -1;
  rc_R10PT10_nconst_jet_4 = -1;
  rc_R10PT10_nconst_btag_jet_1 = -1;
  rc_R10PT10_nconst_btag_jet_2 = -1;
  rc_R10PT10_nconst_btag_jet_3 = -1;
  rc_R10PT10_nconst_btag_jet_4 = -1;
  rc_R10PT10_nconst_btag_60_jet_1 = -1;
  rc_R10PT10_nconst_btag_60_jet_2 = -1;
  rc_R10PT10_nconst_btag_60_jet_3 = -1;
  rc_R10PT10_nconst_btag_60_jet_4 = -1;
  rc_R10PT10_nconst_btag_70_jet_1 = -1;
  rc_R10PT10_nconst_btag_70_jet_2 = -1;
  rc_R10PT10_nconst_btag_70_jet_3 = -1;
  rc_R10PT10_nconst_btag_70_jet_4 = -1;
  rc_R10PT10_nconst_btag_77_jet_1 = -1;
  rc_R10PT10_nconst_btag_77_jet_2 = -1;
  rc_R10PT10_nconst_btag_77_jet_3 = -1;
  rc_R10PT10_nconst_btag_77_jet_4 = -1;
  rc_R10PT10_nconst_btag_85_jet_1 = -1;
  rc_R10PT10_nconst_btag_85_jet_2 = -1;
  rc_R10PT10_nconst_btag_85_jet_3 = -1;
  rc_R10PT10_nconst_btag_85_jet_4 = -1;

  rc_R10PT10_pt_h = 0.;
  rc_R10PT10_pt_W = 0.;
  rc_R10PT10_m_h = 0.;
  rc_R10PT10_m_W = 0.;
  rc_R10PT10_SPLIT12_h = -1.;
  rc_R10PT10_SPLIT12_W = -1.;
  rc_R10PT10_SPLIT23_h = -1.;
  rc_R10PT10_SPLIT23_W = -1.;
  rc_R10PT10_tau21_h = -1.;
  rc_R10PT10_tau21_W = -1.;
  rc_R10PT10_tau32_h = -1.;
  rc_R10PT10_tau32_W = -1.;
  rc_R10PT10_C2_h = -1.;
  rc_R10PT10_C2_W = -1.;
  rc_R10PT10_D2_h = -1.;
  rc_R10PT10_D2_W = -1.;
  rc_R10PT10_dR_Wh = -1.;
  rc_R10PT10_dEta_Wh = -1.;
  rc_R10PT10_dPhi_Wh = -1.;
  rc_R10PT10_nconst_h = -1;
  rc_R10PT10_nconst_W = -1;
  rc_R10PT10_nconst_btag_h = -1;
  rc_R10PT10_nconst_btag_W = -1;
  rc_R10PT10_nconst_btag_60_h = -1;
  rc_R10PT10_nconst_btag_60_W = -1;
  rc_R10PT10_nconst_btag_70_h = -1;
  rc_R10PT10_nconst_btag_70_W = -1;
  rc_R10PT10_nconst_btag_77_h = -1;
  rc_R10PT10_nconst_btag_77_W = -1;
  rc_R10PT10_nconst_btag_85_h = -1;
  rc_R10PT10_nconst_btag_85_W = -1;

  rc_R12PT10_dphi_min = 1000.;
  rc_R12PT10_dphi_1jet = 1000.;
  rc_R12PT10_dphi_sum2jet = 1000.;
  rc_R12PT10_dphi_min_alljets = 1000.;
  rc_R12PT10_meff_2j = 0.;
  rc_R12PT10_meff_4j = 0.;
  rc_R12PT10_meff_nj = 0.;
  rc_R12PT10_mT_2j = 0.;
  rc_R12PT10_pt_jet_1 = 0.;
  rc_R12PT10_pt_jet_2 = 0.;
  rc_R12PT10_pt_jet_3 = 0.;
  rc_R12PT10_pt_jet_4 = 0.;
  rc_R12PT10_m_jet_1 = 0.;
  rc_R12PT10_m_jet_2 = 0.;
  rc_R12PT10_m_jet_3 = 0.;
  rc_R12PT10_m_jet_4 = 0.;
  rc_R12PT10_SPLIT12_jet_1 = -1.;
  rc_R12PT10_SPLIT12_jet_2 = -1.;
  rc_R12PT10_SPLIT12_jet_3 = -1.;
  rc_R12PT10_SPLIT12_jet_4 = -1.;
  rc_R12PT10_SPLIT23_jet_1 = -1.;
  rc_R12PT10_SPLIT23_jet_2 = -1.;
  rc_R12PT10_SPLIT23_jet_3 = -1.;
  rc_R12PT10_SPLIT23_jet_4 = -1.;
  rc_R12PT10_tau21_jet_1 = -1.;
  rc_R12PT10_tau21_jet_2 = -1.;
  rc_R12PT10_tau21_jet_3 = -1.;
  rc_R12PT10_tau21_jet_4 = -1.;
  rc_R12PT10_tau32_jet_1 = -1.;
  rc_R12PT10_tau32_jet_2 = -1.;
  rc_R12PT10_tau32_jet_3 = -1.;
  rc_R12PT10_tau32_jet_4 = -1.;
  rc_R12PT10_C2_jet_1 = -1.;
  rc_R12PT10_C2_jet_2 = -1.;
  rc_R12PT10_C2_jet_3 = -1.;
  rc_R12PT10_C2_jet_4 = -1.;
  rc_R12PT10_D2_jet_1 = -1.;
  rc_R12PT10_D2_jet_2 = -1.;
  rc_R12PT10_D2_jet_3 = -1.;
  rc_R12PT10_D2_jet_4 = -1.;
  rc_R12PT10_nconst_jet_1 = -1;
  rc_R12PT10_nconst_jet_2 = -1;
  rc_R12PT10_nconst_jet_3 = -1;
  rc_R12PT10_nconst_jet_4 = -1;
  rc_R12PT10_nconst_btag_jet_1 = -1;
  rc_R12PT10_nconst_btag_jet_2 = -1;
  rc_R12PT10_nconst_btag_jet_3 = -1;
  rc_R12PT10_nconst_btag_jet_4 = -1;
  rc_R12PT10_nconst_btag_60_jet_1 = -1;
  rc_R12PT10_nconst_btag_60_jet_2 = -1;
  rc_R12PT10_nconst_btag_60_jet_3 = -1;
  rc_R12PT10_nconst_btag_60_jet_4 = -1;
  rc_R12PT10_nconst_btag_70_jet_1 = -1;
  rc_R12PT10_nconst_btag_70_jet_2 = -1;
  rc_R12PT10_nconst_btag_70_jet_3 = -1;
  rc_R12PT10_nconst_btag_70_jet_4 = -1;
  rc_R12PT10_nconst_btag_77_jet_1 = -1;
  rc_R12PT10_nconst_btag_77_jet_2 = -1;
  rc_R12PT10_nconst_btag_77_jet_3 = -1;
  rc_R12PT10_nconst_btag_77_jet_4 = -1;
  rc_R12PT10_nconst_btag_85_jet_1 = -1;
  rc_R12PT10_nconst_btag_85_jet_2 = -1;
  rc_R12PT10_nconst_btag_85_jet_3 = -1;
  rc_R12PT10_nconst_btag_85_jet_4 = -1;

  rc_R12PT10_pt_h = 0.;
  rc_R12PT10_pt_W = 0.;
  rc_R12PT10_m_h = 0.;
  rc_R12PT10_m_W = 0.;
  rc_R12PT10_SPLIT12_h = -1.;
  rc_R12PT10_SPLIT12_W = -1.;
  rc_R12PT10_SPLIT23_h = -1.;
  rc_R12PT10_SPLIT23_W = -1.;
  rc_R12PT10_tau21_h = -1.;
  rc_R12PT10_tau21_W = -1.;
  rc_R12PT10_tau32_h = -1.;
  rc_R12PT10_tau32_W = -1.;
  rc_R12PT10_C2_h = -1.;
  rc_R12PT10_C2_W = -1.;
  rc_R12PT10_D2_h = -1.;
  rc_R12PT10_D2_W = -1.;
  rc_R12PT10_dR_Wh = -1.;
  rc_R12PT10_dEta_Wh = -1.;
  rc_R12PT10_dPhi_Wh = -1.;
  rc_R12PT10_nconst_h = -1;
  rc_R12PT10_nconst_W = -1;
  rc_R12PT10_nconst_btag_h = -1;
  rc_R12PT10_nconst_btag_W = -1;
  rc_R12PT10_nconst_btag_60_h = -1;
  rc_R12PT10_nconst_btag_60_W = -1;
  rc_R12PT10_nconst_btag_70_h = -1;
  rc_R12PT10_nconst_btag_70_W = -1;
  rc_R12PT10_nconst_btag_77_h = -1;
  rc_R12PT10_nconst_btag_77_W = -1;
  rc_R12PT10_nconst_btag_85_h = -1;
  rc_R12PT10_nconst_btag_85_W = -1;

  rc_R15PT10_dphi_min = 1000.;
  rc_R15PT10_dphi_1jet = 1000.;
  rc_R15PT10_dphi_sum2jet = 1000.;
  rc_R15PT10_dphi_min_alljets = 1000.;
  rc_R15PT10_meff_2j = 0.;
  rc_R15PT10_meff_4j = 0.;
  rc_R15PT10_meff_nj = 0.;
  rc_R15PT10_mT_2j = 0.;
  rc_R15PT10_pt_jet_1 = 0.;
  rc_R15PT10_pt_jet_2 = 0.;
  rc_R15PT10_pt_jet_3 = 0.;
  rc_R15PT10_pt_jet_4 = 0.;
  rc_R15PT10_m_jet_1 = 0.;
  rc_R15PT10_m_jet_2 = 0.;
  rc_R15PT10_m_jet_3 = 0.;
  rc_R15PT10_m_jet_4 = 0.;
  rc_R15PT10_SPLIT12_jet_1 = -1.;
  rc_R15PT10_SPLIT12_jet_2 = -1.;
  rc_R15PT10_SPLIT12_jet_3 = -1.;
  rc_R15PT10_SPLIT12_jet_4 = -1.;
  rc_R15PT10_SPLIT23_jet_1 = -1.;
  rc_R15PT10_SPLIT23_jet_2 = -1.;
  rc_R15PT10_SPLIT23_jet_3 = -1.;
  rc_R15PT10_SPLIT23_jet_4 = -1.;
  rc_R15PT10_tau21_jet_1 = -1.;
  rc_R15PT10_tau21_jet_2 = -1.;
  rc_R15PT10_tau21_jet_3 = -1.;
  rc_R15PT10_tau21_jet_4 = -1.;
  rc_R15PT10_tau32_jet_1 = -1.;
  rc_R15PT10_tau32_jet_2 = -1.;
  rc_R15PT10_tau32_jet_3 = -1.;
  rc_R15PT10_tau32_jet_4 = -1.;
  rc_R15PT10_C2_jet_1 = -1.;
  rc_R15PT10_C2_jet_2 = -1.;
  rc_R15PT10_C2_jet_3 = -1.;
  rc_R15PT10_C2_jet_4 = -1.;
  rc_R15PT10_D2_jet_1 = -1.;
  rc_R15PT10_D2_jet_2 = -1.;
  rc_R15PT10_D2_jet_3 = -1.;
  rc_R15PT10_D2_jet_4 = -1.;
  rc_R15PT10_nconst_jet_1 = -1;
  rc_R15PT10_nconst_jet_2 = -1;
  rc_R15PT10_nconst_jet_3 = -1;
  rc_R15PT10_nconst_jet_4 = -1;
  rc_R15PT10_nconst_btag_jet_1 = -1;
  rc_R15PT10_nconst_btag_jet_2 = -1;
  rc_R15PT10_nconst_btag_jet_3 = -1;
  rc_R15PT10_nconst_btag_jet_4 = -1;
  rc_R15PT10_nconst_btag_60_jet_1 = -1;
  rc_R15PT10_nconst_btag_60_jet_2 = -1;
  rc_R15PT10_nconst_btag_60_jet_3 = -1;
  rc_R15PT10_nconst_btag_60_jet_4 = -1;
  rc_R15PT10_nconst_btag_70_jet_1 = -1;
  rc_R15PT10_nconst_btag_70_jet_2 = -1;
  rc_R15PT10_nconst_btag_70_jet_3 = -1;
  rc_R15PT10_nconst_btag_70_jet_4 = -1;
  rc_R15PT10_nconst_btag_77_jet_1 = -1;
  rc_R15PT10_nconst_btag_77_jet_2 = -1;
  rc_R15PT10_nconst_btag_77_jet_3 = -1;
  rc_R15PT10_nconst_btag_77_jet_4 = -1;
  rc_R15PT10_nconst_btag_85_jet_1 = -1;
  rc_R15PT10_nconst_btag_85_jet_2 = -1;
  rc_R15PT10_nconst_btag_85_jet_3 = -1;
  rc_R15PT10_nconst_btag_85_jet_4 = -1;

  rc_R15PT10_pt_h = 0.;
  rc_R15PT10_pt_W = 0.;
  rc_R15PT10_m_h = 0.;
  rc_R15PT10_m_W = 0.;
  rc_R15PT10_SPLIT12_h = -1.;
  rc_R15PT10_SPLIT12_W = -1.;
  rc_R15PT10_SPLIT23_h = -1.;
  rc_R15PT10_SPLIT23_W = -1.;
  rc_R15PT10_tau21_h = -1.;
  rc_R15PT10_tau21_W = -1.;
  rc_R15PT10_tau32_h = -1.;
  rc_R15PT10_tau32_W = -1.;
  rc_R15PT10_C2_h = -1.;
  rc_R15PT10_C2_W = -1.;
  rc_R15PT10_D2_h = -1.;
  rc_R15PT10_D2_W = -1.;
  rc_R15PT10_dR_Wh = -1.;
  rc_R15PT10_dEta_Wh = -1.;
  rc_R15PT10_dPhi_Wh = -1.;
  rc_R15PT10_nconst_h = -1;
  rc_R15PT10_nconst_W = -1;
  rc_R15PT10_nconst_btag_h = -1;
  rc_R15PT10_nconst_btag_W = -1;
  rc_R15PT10_nconst_btag_60_h = -1;
  rc_R15PT10_nconst_btag_60_W = -1;
  rc_R15PT10_nconst_btag_70_h = -1;
  rc_R15PT10_nconst_btag_70_W = -1;
  rc_R15PT10_nconst_btag_77_h = -1;
  rc_R15PT10_nconst_btag_77_W = -1;
  rc_R15PT10_nconst_btag_85_h = -1;
  rc_R15PT10_nconst_btag_85_W = -1;

}

Bool_t mbj_flatten_tree::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

void mbj_flatten_tree::Show(Long64_t entry)
{
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}
// Int_t mbj_flatten_tree::Cut(Long64_t entry)
// {
//   // This function may be called from Loop.
//   // returns  1 if entry is accepted.
//   // returns -1 otherwise.
//   return 1;
// }
#endif // #ifdef mbj_flatten_tree_cxx
