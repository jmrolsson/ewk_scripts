#define mbj_flatten_tree_cxx
#include "mbj_flatten_tree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>

using namespace std;

void mbj_flatten_tree::Loop(TFile* outFile)
{
//   In a ROOT session, you can do:
//      root> .L mbj_flatten_tree.C
//      root> mbj_flatten_tree t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   if (outFile == 0) {
     outFile = new TFile("output_file.root", "recreate");
   }
   TTree *outTree = new TTree(fChain->GetName(), fChain->GetName());
   InitOutTree(outTree);

   Long64_t nentries = fChain->GetEntries();
   /* std::cout << "fChain->GetEntries() " << fChain->GetEntries() << std::endl; */

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      ResetOutTreeBranches();

      // fill small-R jet variables
      int ibjet_60 = 0;
      int ibjet_70 = 0;
      int ibjet_77 = 0;
      int ibjet_85 = 0;
      for(int i=0; i < jets_n; ++i) {

        if (i==0) pt_jet_1 = jets_pt->at(i);
        if (i==1) pt_jet_2 = jets_pt->at(i);
        if (i==2) pt_jet_3 = jets_pt->at(i);
        if (i==3) pt_jet_4 = jets_pt->at(i);

        if(jets_isb_60->at(i) && ibjet_60 < 4) {
          if (ibjet_60 == 0) pt_bjet_1_60 = jets_pt->at(i);
          if (ibjet_60 == 1) pt_bjet_2_60 = jets_pt->at(i);
          if (ibjet_60 == 2) pt_bjet_3_60 = jets_pt->at(i);
          if (ibjet_60 == 3) pt_bjet_4_60 = jets_pt->at(i);
          ibjet_60++;
        }
        if(jets_isb_70->at(i) && ibjet_70 < 4) {
          if (ibjet_70 == 0) pt_bjet_1_70 = jets_pt->at(i);
          if (ibjet_70 == 1) pt_bjet_2_70 = jets_pt->at(i);
          if (ibjet_70 == 2) pt_bjet_3_70 = jets_pt->at(i);
          if (ibjet_70 == 3) pt_bjet_4_70 = jets_pt->at(i);
          ibjet_70++;
        }
        if(jets_isb_77->at(i) && ibjet_77 < 4) {
          if (ibjet_77 == 0) pt_bjet_1_77 = jets_pt->at(i);
          if (ibjet_77 == 1) pt_bjet_2_77 = jets_pt->at(i);
          if (ibjet_77 == 2) pt_bjet_3_77 = jets_pt->at(i);
          if (ibjet_77 == 3) pt_bjet_4_77 = jets_pt->at(i);
          ibjet_77++;
        }
        if(jets_isb_85->at(i) && ibjet_85 < 4) {
          if (ibjet_85 == 0) pt_bjet_1_85 = jets_pt->at(i);
          if (ibjet_85 == 1) pt_bjet_2_85 = jets_pt->at(i);
          if (ibjet_85 == 2) pt_bjet_3_85 = jets_pt->at(i);
          if (ibjet_85 == 3) pt_bjet_4_85 = jets_pt->at(i);
          ibjet_85++;
        }
      }

      // fill AK10 large-R jet variables
      TLorentzVector ak10_jet_1_vec;
      TLorentzVector ak10_jet_2_vec;

      for(int i=0; i < ak10_jets_n; ++i) {

        ak10_meff_nj += ak10_jets_pt->at(i);

        float dphi_ak10_jet_mettst = fabs(ak10_jets_phi->at(i) - mettst_phi);
        if (dphi_ak10_jet_mettst > TMath::Pi()) 
          dphi_ak10_jet_mettst = 2*TMath::Pi() - dphi_ak10_jet_mettst;

        // calculate ak10_dphi_1jet using the leading fat-jet
        if (i==0)
          ak10_dphi_1jet = dphi_ak10_jet_mettst;

        // calculate ak10_dphi_min using the two leading fat-jets
        if (i < 3 && dphi_ak10_jet_mettst < ak10_dphi_min)
          ak10_dphi_min = dphi_ak10_jet_mettst;

        // calculate ak10_dphi_min_alljets using all fat-jets
        if (dphi_ak10_jet_mettst < ak10_dphi_min_alljets)
          ak10_dphi_min_alljets = dphi_ak10_jet_mettst;

        // fill lar-R jet variables
        if (i==0) {
          ak10_jet_1_vec.SetPtEtaPhiE(ak10_jets_pt->at(i), ak10_jets_eta->at(i), ak10_jets_phi->at(i), ak10_jets_e->at(i));
          ak10_meff_2j += ak10_jets_pt->at(i);
          ak10_meff_4j += ak10_jets_pt->at(i);

          ak10_pt_jet_1 = ak10_jets_pt->at(i);
          ak10_m_jet_1 = ak10_jets_m->at(i);
          ak10_SPLIT12_jet_1 = ak10_jets_SPLIT12->at(i);
          ak10_SPLIT23_jet_1 = ak10_jets_SPLIT23->at(i);
          ak10_tau21_jet_1 = ak10_jets_tau21->at(i);
          ak10_tau32_jet_1 = ak10_jets_tau32->at(i);
          ak10_C2_jet_1 = ak10_jets_C2->at(i);
          ak10_D2_jet_1 = ak10_jets_D2->at(i);

          ak10_assoc_ak4_n_jet_1 = ak10_jets_assoc_ak4_n->at(i);
          ak10_assoc_ak4_btag_n_jet_1 = ak10_jets_assoc_ak4_btag_n->at(i);
          ak10_ghost_ak2_trk_n_jet_1= ak10_jets_ghost_ak2_trk_n->at(i);
        }
        if (i==1) {
          ak10_jet_2_vec.SetPtEtaPhiE(ak10_jets_pt->at(i), ak10_jets_eta->at(i), ak10_jets_phi->at(i), ak10_jets_e->at(i));
          ak10_meff_2j += ak10_jets_pt->at(i);
          ak10_meff_4j += ak10_jets_pt->at(i);

          ak10_pt_jet_2 = ak10_jets_pt->at(i);
          ak10_m_jet_2 = ak10_jets_m->at(i);
          ak10_SPLIT12_jet_2 = ak10_jets_SPLIT12->at(i);
          ak10_SPLIT23_jet_2 = ak10_jets_SPLIT23->at(i);
          ak10_tau21_jet_2 = ak10_jets_tau21->at(i);
          ak10_tau32_jet_2 = ak10_jets_tau32->at(i);
          ak10_C2_jet_2 = ak10_jets_C2->at(i);
          ak10_D2_jet_2 = ak10_jets_D2->at(i);

          ak10_assoc_ak4_n_jet_2 = ak10_jets_assoc_ak4_n->at(i);
          ak10_assoc_ak4_btag_n_jet_2 = ak10_jets_assoc_ak4_btag_n->at(i);
          ak10_ghost_ak2_trk_n_jet_2= ak10_jets_ghost_ak2_trk_n->at(i);
        }
        if (i==2) {
          ak10_meff_4j += ak10_jets_pt->at(i);
          ak10_pt_jet_3 = ak10_jets_pt->at(i);
          ak10_m_jet_3 = ak10_jets_m->at(i);
          ak10_SPLIT12_jet_3 = ak10_jets_SPLIT12->at(i);
          ak10_SPLIT23_jet_3 = ak10_jets_SPLIT23->at(i);
          ak10_tau21_jet_3 = ak10_jets_tau21->at(i);
          ak10_tau32_jet_3 = ak10_jets_tau32->at(i);
          ak10_C2_jet_3 = ak10_jets_C2->at(i);
          ak10_D2_jet_3 = ak10_jets_D2->at(i);

          ak10_assoc_ak4_n_jet_3 = ak10_jets_assoc_ak4_n->at(i);
          ak10_assoc_ak4_btag_n_jet_3 = ak10_jets_assoc_ak4_btag_n->at(i);
          ak10_ghost_ak2_trk_n_jet_3= ak10_jets_ghost_ak2_trk_n->at(i);
        }
        if (i==3) {
          ak10_meff_4j += ak10_jets_pt->at(i);
          ak10_pt_jet_4 = ak10_jets_pt->at(i);
          ak10_m_jet_4 = ak10_jets_m->at(i);
          ak10_SPLIT12_jet_4 = ak10_jets_SPLIT12->at(i);
          ak10_SPLIT23_jet_4 = ak10_jets_SPLIT23->at(i);
          ak10_tau21_jet_4 = ak10_jets_tau21->at(i);
          ak10_tau32_jet_4 = ak10_jets_tau32->at(i);
          ak10_C2_jet_4 = ak10_jets_C2->at(i);
          ak10_D2_jet_4 = ak10_jets_D2->at(i);

          ak10_assoc_ak4_n_jet_4 = ak10_jets_assoc_ak4_n->at(i);
          ak10_assoc_ak4_btag_n_jet_4 = ak10_jets_assoc_ak4_btag_n->at(i);
          ak10_ghost_ak2_trk_n_jet_4= ak10_jets_ghost_ak2_trk_n->at(i);
        }
      }

      TLorentzVector sum2jet_vec = ak10_jet_1_vec + ak10_jet_2_vec;

      ak10_dphi_sum2jet = fabs(sum2jet_vec.Phi() - mettst_phi);
      if (ak10_dphi_sum2jet > TMath::Pi()) 
        ak10_dphi_sum2jet = 2*TMath::Pi() - ak10_dphi_sum2jet;

      ak10_meff_nj += mettst;
      ak10_meff_2j += mettst;
      ak10_meff_4j += mettst;
      ak10_mT_2j = sum2jet_vec.Mt();

      //if (ak10_jets_n > 1 && mettst > 150 && ak10_jets_pt->at(0) > 200. && ak10_jets_pt->at(1) > 200.) {
      if (ak10_jets_n > 1) {

        // Effective mass of two leading fat-jets and MET

        // Take our Higgs candidate to be the fat-jet with the largest mass 
        // (among the 2 leading fat-jets)
        int iHiggs = 0; 
        int iW = 1; 
        if (ak10_jets_m->at(0) < ak10_jets_m->at(1)) {
          iHiggs = 1; iW = 0;
        }

        ak10_pt_h = ak10_jets_pt->at(iHiggs);
        ak10_pt_W = ak10_jets_pt->at(iW);

        ak10_m_h = ak10_jets_m->at(iHiggs);
        ak10_m_W = ak10_jets_m->at(iW);

        ak10_SPLIT12_h = ak10_jets_SPLIT12->at(iHiggs);
        ak10_SPLIT12_W = ak10_jets_SPLIT12->at(iW);

        ak10_SPLIT23_h = ak10_jets_SPLIT23->at(iHiggs);
        ak10_SPLIT23_W = ak10_jets_SPLIT23->at(iW);

        ak10_tau21_h = ak10_jets_tau21->at(iHiggs);
        ak10_tau21_W = ak10_jets_tau21->at(iW);

        ak10_tau32_h = ak10_jets_tau32->at(iHiggs);
        ak10_tau32_W = ak10_jets_tau32->at(iW);

        ak10_C2_h = ak10_jets_C2->at(iHiggs);
        ak10_C2_W = ak10_jets_C2->at(iW);

        ak10_D2_h = ak10_jets_D2->at(iHiggs);
        ak10_D2_W = ak10_jets_D2->at(iW);

        ak10_assoc_ak4_n_h = ak10_jets_assoc_ak4_n->at(iHiggs);
        ak10_assoc_ak4_n_W = ak10_jets_assoc_ak4_n->at(iW);

        ak10_assoc_ak4_btag_n_h = ak10_jets_assoc_ak4_btag_n->at(iHiggs);
        ak10_assoc_ak4_btag_n_W = ak10_jets_assoc_ak4_btag_n->at(iW);

        ak10_ghost_ak2_trk_n_h = ak10_jets_ghost_ak2_trk_n->at(iHiggs);
        ak10_ghost_ak2_trk_n_W = ak10_jets_ghost_ak2_trk_n->at(iW);

        float dEta = fabs( ak10_jets_eta->at(iHiggs) - ak10_jets_eta->at(iW) );
        float dPhi = fabs( ak10_jets_phi->at(iHiggs) - ak10_jets_phi->at(iW) );
        if (dPhi > TMath::Pi()) dPhi = 2*TMath::Pi()-dPhi;
        ak10_dR_Wh = sqrt(dEta*dEta + dPhi*dPhi); 
        ak10_dEta_Wh = dEta; 
        ak10_dPhi_Wh = dPhi; 

      }

      // fill 'rc_R08PT10' reclustered jet variables
      TLorentzVector rc_R08PT10_jet_1_vec;
      TLorentzVector rc_R08PT10_jet_2_vec;

      for(int i=0; i < rc_R08PT10_jets_n; ++i) {

        rc_R08PT10_meff_nj += rc_R08PT10_jets_pt->at(i);

        float dphi_rc_R08PT10_jet_mettst = fabs(rc_R08PT10_jets_phi->at(i) - mettst_phi);
        if (dphi_rc_R08PT10_jet_mettst > TMath::Pi()) 
          dphi_rc_R08PT10_jet_mettst = 2*TMath::Pi() - dphi_rc_R08PT10_jet_mettst;

        // calculate rc_R08PT10_dphi_1jet using the leading fat-jet
        if (i==0)
          rc_R08PT10_dphi_1jet = dphi_rc_R08PT10_jet_mettst;

        // calculate rc_R08PT10_dphi_min using the two leading fat-jets
        if (i < 3 && dphi_rc_R08PT10_jet_mettst < rc_R08PT10_dphi_min)
          rc_R08PT10_dphi_min = dphi_rc_R08PT10_jet_mettst;

        // calculate rc_R08PT10_dphi_min_alljets using all fat-jets
        if (dphi_rc_R08PT10_jet_mettst < rc_R08PT10_dphi_min_alljets)
          rc_R08PT10_dphi_min_alljets = dphi_rc_R08PT10_jet_mettst;

        // fill lar-R jet variables
        if (i==0) {
          rc_R08PT10_jet_1_vec.SetPtEtaPhiE(rc_R08PT10_jets_pt->at(i), rc_R08PT10_jets_eta->at(i), rc_R08PT10_jets_phi->at(i), rc_R08PT10_jets_e->at(i));
          rc_R08PT10_meff_2j += rc_R08PT10_jets_pt->at(i);
          rc_R08PT10_meff_4j += rc_R08PT10_jets_pt->at(i);

          rc_R08PT10_pt_jet_1 = rc_R08PT10_jets_pt->at(i);
          rc_R08PT10_m_jet_1 = rc_R08PT10_jets_m->at(i);
          rc_R08PT10_SPLIT12_jet_1 = rc_R08PT10_jets_SPLIT12->at(i);
          rc_R08PT10_SPLIT23_jet_1 = rc_R08PT10_jets_SPLIT23->at(i);
          rc_R08PT10_tau21_jet_1 = rc_R08PT10_jets_tau21->at(i);
          rc_R08PT10_tau32_jet_1 = rc_R08PT10_jets_tau32->at(i);
          rc_R08PT10_C2_jet_1 = rc_R08PT10_jets_C2->at(i);
          rc_R08PT10_D2_jet_1 = rc_R08PT10_jets_D2->at(i);

          rc_R08PT10_nconst_jet_1 = rc_R08PT10_jets_nconst->at(i);
          rc_R08PT10_nconst_btag_jet_1 = rc_R08PT10_jets_nconst_btag->at(i);
          rc_R08PT10_nconst_btag_60_jet_1 = rc_R08PT10_jets_nconst_btag_60->at(i);
          rc_R08PT10_nconst_btag_70_jet_1 = rc_R08PT10_jets_nconst_btag_70->at(i);
          rc_R08PT10_nconst_btag_77_jet_1 = rc_R08PT10_jets_nconst_btag_77->at(i);
          rc_R08PT10_nconst_btag_85_jet_1 = rc_R08PT10_jets_nconst_btag_85->at(i);
        }
        if (i==1) {
          rc_R08PT10_jet_2_vec.SetPtEtaPhiE(rc_R08PT10_jets_pt->at(i), rc_R08PT10_jets_eta->at(i), rc_R08PT10_jets_phi->at(i), rc_R08PT10_jets_e->at(i));
          rc_R08PT10_meff_2j += rc_R08PT10_jets_pt->at(i);
          rc_R08PT10_meff_4j += rc_R08PT10_jets_pt->at(i);

          rc_R08PT10_pt_jet_2 = rc_R08PT10_jets_pt->at(i);
          rc_R08PT10_m_jet_2 = rc_R08PT10_jets_m->at(i);
          rc_R08PT10_SPLIT12_jet_2 = rc_R08PT10_jets_SPLIT12->at(i);
          rc_R08PT10_SPLIT23_jet_2 = rc_R08PT10_jets_SPLIT23->at(i);
          rc_R08PT10_tau21_jet_2 = rc_R08PT10_jets_tau21->at(i);
          rc_R08PT10_tau32_jet_2 = rc_R08PT10_jets_tau32->at(i);
          rc_R08PT10_C2_jet_2 = rc_R08PT10_jets_C2->at(i);
          rc_R08PT10_D2_jet_2 = rc_R08PT10_jets_D2->at(i);

          rc_R08PT10_nconst_jet_2 = rc_R08PT10_jets_nconst->at(i);
          rc_R08PT10_nconst_btag_jet_2 = rc_R08PT10_jets_nconst_btag->at(i);
          rc_R08PT10_nconst_btag_60_jet_2 = rc_R08PT10_jets_nconst_btag_60->at(i);
          rc_R08PT10_nconst_btag_70_jet_2 = rc_R08PT10_jets_nconst_btag_70->at(i);
          rc_R08PT10_nconst_btag_77_jet_2 = rc_R08PT10_jets_nconst_btag_77->at(i);
          rc_R08PT10_nconst_btag_85_jet_2 = rc_R08PT10_jets_nconst_btag_85->at(i);
        }
        if (i==2) {
          rc_R08PT10_meff_4j += rc_R08PT10_jets_pt->at(i);
          rc_R08PT10_pt_jet_3 = rc_R08PT10_jets_pt->at(i);
          rc_R08PT10_m_jet_3 = rc_R08PT10_jets_m->at(i);
          rc_R08PT10_SPLIT12_jet_3 = rc_R08PT10_jets_SPLIT12->at(i);
          rc_R08PT10_SPLIT23_jet_3 = rc_R08PT10_jets_SPLIT23->at(i);
          rc_R08PT10_tau21_jet_3 = rc_R08PT10_jets_tau21->at(i);
          rc_R08PT10_tau32_jet_3 = rc_R08PT10_jets_tau32->at(i);
          rc_R08PT10_C2_jet_3 = rc_R08PT10_jets_C2->at(i);
          rc_R08PT10_D2_jet_3 = rc_R08PT10_jets_D2->at(i);

          rc_R08PT10_nconst_jet_3 = rc_R08PT10_jets_nconst->at(i);
          rc_R08PT10_nconst_btag_jet_3 = rc_R08PT10_jets_nconst_btag->at(i);
          rc_R08PT10_nconst_btag_60_jet_3 = rc_R08PT10_jets_nconst_btag_60->at(i);
          rc_R08PT10_nconst_btag_70_jet_3 = rc_R08PT10_jets_nconst_btag_70->at(i);
          rc_R08PT10_nconst_btag_77_jet_3 = rc_R08PT10_jets_nconst_btag_77->at(i);
          rc_R08PT10_nconst_btag_85_jet_3 = rc_R08PT10_jets_nconst_btag_85->at(i);
        }
        if (i==3) {
          rc_R08PT10_meff_4j += rc_R08PT10_jets_pt->at(i);
          rc_R08PT10_pt_jet_4 = rc_R08PT10_jets_pt->at(i);
          rc_R08PT10_m_jet_4 = rc_R08PT10_jets_m->at(i);
          rc_R08PT10_SPLIT12_jet_4 = rc_R08PT10_jets_SPLIT12->at(i);
          rc_R08PT10_SPLIT23_jet_4 = rc_R08PT10_jets_SPLIT23->at(i);
          rc_R08PT10_tau21_jet_4 = rc_R08PT10_jets_tau21->at(i);
          rc_R08PT10_tau32_jet_4 = rc_R08PT10_jets_tau32->at(i);
          rc_R08PT10_C2_jet_4 = rc_R08PT10_jets_C2->at(i);
          rc_R08PT10_D2_jet_4 = rc_R08PT10_jets_D2->at(i);

          rc_R08PT10_nconst_jet_4 = rc_R08PT10_jets_nconst->at(i);
          rc_R08PT10_nconst_btag_jet_4 = rc_R08PT10_jets_nconst_btag->at(i);
          rc_R08PT10_nconst_btag_60_jet_4 = rc_R08PT10_jets_nconst_btag_60->at(i);
          rc_R08PT10_nconst_btag_70_jet_4 = rc_R08PT10_jets_nconst_btag_70->at(i);
          rc_R08PT10_nconst_btag_77_jet_4 = rc_R08PT10_jets_nconst_btag_77->at(i);
          rc_R08PT10_nconst_btag_85_jet_4 = rc_R08PT10_jets_nconst_btag_85->at(i);
        }
      }

      sum2jet_vec = rc_R08PT10_jet_1_vec + rc_R08PT10_jet_2_vec;

      rc_R08PT10_dphi_sum2jet = fabs(sum2jet_vec.Phi() - mettst_phi);
      if (rc_R08PT10_dphi_sum2jet > TMath::Pi()) 
        rc_R08PT10_dphi_sum2jet = 2*TMath::Pi() - rc_R08PT10_dphi_sum2jet;

      rc_R08PT10_meff_nj += mettst;
      rc_R08PT10_meff_2j += mettst;
      rc_R08PT10_meff_4j += mettst;
      rc_R08PT10_mT_2j = sum2jet_vec.Mt();

      if (rc_R08PT10_jets_n > 1) {

        // Effective mass of two leading fat-jets and MET

        // Take our Higgs candidate to be the fat-jet with the largest mass 
        // (among the 2 leading fat-jets)
        int iHiggs = 0; 
        int iW = 1; 
        if (rc_R08PT10_jets_m->at(0) < rc_R08PT10_jets_m->at(1)) {
          iHiggs = 1; iW = 0;
        }

        rc_R08PT10_pt_h = rc_R08PT10_jets_pt->at(iHiggs);
        rc_R08PT10_pt_W = rc_R08PT10_jets_pt->at(iW);

        rc_R08PT10_m_h = rc_R08PT10_jets_m->at(iHiggs);
        rc_R08PT10_m_W = rc_R08PT10_jets_m->at(iW);

        rc_R08PT10_SPLIT12_h = rc_R08PT10_jets_SPLIT12->at(iHiggs);
        rc_R08PT10_SPLIT12_W = rc_R08PT10_jets_SPLIT12->at(iW);

        rc_R08PT10_SPLIT23_h = rc_R08PT10_jets_SPLIT23->at(iHiggs);
        rc_R08PT10_SPLIT23_W = rc_R08PT10_jets_SPLIT23->at(iW);

        rc_R08PT10_tau21_h = rc_R08PT10_jets_tau21->at(iHiggs);
        rc_R08PT10_tau21_W = rc_R08PT10_jets_tau21->at(iW);

        rc_R08PT10_tau32_h = rc_R08PT10_jets_tau32->at(iHiggs);
        rc_R08PT10_tau32_W = rc_R08PT10_jets_tau32->at(iW);

        rc_R08PT10_C2_h = rc_R08PT10_jets_C2->at(iHiggs);
        rc_R08PT10_C2_W = rc_R08PT10_jets_C2->at(iW);

        rc_R08PT10_D2_h = rc_R08PT10_jets_D2->at(iHiggs);
        rc_R08PT10_D2_W = rc_R08PT10_jets_D2->at(iW);

        rc_R08PT10_nconst_h = rc_R08PT10_jets_nconst->at(iHiggs);
        rc_R08PT10_nconst_W = rc_R08PT10_jets_nconst->at(iW);
        rc_R08PT10_nconst_btag_h = rc_R08PT10_jets_nconst_btag->at(iHiggs);
        rc_R08PT10_nconst_btag_W = rc_R08PT10_jets_nconst_btag->at(iW);
        rc_R08PT10_nconst_btag_60_h = rc_R08PT10_jets_nconst_btag_60->at(iHiggs);
        rc_R08PT10_nconst_btag_60_W = rc_R08PT10_jets_nconst_btag_60->at(iW);
        rc_R08PT10_nconst_btag_70_h = rc_R08PT10_jets_nconst_btag_70->at(iHiggs);
        rc_R08PT10_nconst_btag_70_W = rc_R08PT10_jets_nconst_btag_70->at(iW);
        rc_R08PT10_nconst_btag_77_h = rc_R08PT10_jets_nconst_btag_77->at(iHiggs);
        rc_R08PT10_nconst_btag_77_W = rc_R08PT10_jets_nconst_btag_77->at(iW);
        rc_R08PT10_nconst_btag_85_h = rc_R08PT10_jets_nconst_btag_85->at(iHiggs);
        rc_R08PT10_nconst_btag_85_W = rc_R08PT10_jets_nconst_btag_85->at(iW);

        float dEta = fabs( rc_R08PT10_jets_eta->at(iHiggs) - rc_R08PT10_jets_eta->at(iW) );
        float dPhi = fabs( rc_R08PT10_jets_phi->at(iHiggs) - rc_R08PT10_jets_phi->at(iW) );
        if (dPhi > TMath::Pi()) dPhi = 2*TMath::Pi()-dPhi;
        rc_R08PT10_dR_Wh = sqrt(dEta*dEta + dPhi*dPhi); 
        rc_R08PT10_dEta_Wh = dEta; 
        rc_R08PT10_dPhi_Wh = dPhi; 

      }

      // fill 'rc_R10PT10' reclustered jet variables
      TLorentzVector rc_R10PT10_jet_1_vec;
      TLorentzVector rc_R10PT10_jet_2_vec;

      for(int i=0; i < rc_R10PT10_jets_n; ++i) {

        rc_R10PT10_meff_nj += rc_R10PT10_jets_pt->at(i);

        float dphi_rc_R10PT10_jet_mettst = fabs(rc_R10PT10_jets_phi->at(i) - mettst_phi);
        if (dphi_rc_R10PT10_jet_mettst > TMath::Pi()) 
          dphi_rc_R10PT10_jet_mettst = 2*TMath::Pi() - dphi_rc_R10PT10_jet_mettst;

        // calculate rc_R10PT10_dphi_1jet using the leading fat-jet
        if (i==0)
          rc_R10PT10_dphi_1jet = dphi_rc_R10PT10_jet_mettst;

        // calculate rc_R10PT10_dphi_min using the two leading fat-jets
        if (i < 3 && dphi_rc_R10PT10_jet_mettst < rc_R10PT10_dphi_min)
          rc_R10PT10_dphi_min = dphi_rc_R10PT10_jet_mettst;

        // calculate rc_R10PT10_dphi_min_alljets using all fat-jets
        if (dphi_rc_R10PT10_jet_mettst < rc_R10PT10_dphi_min_alljets)
          rc_R10PT10_dphi_min_alljets = dphi_rc_R10PT10_jet_mettst;

        // fill lar-R jet variables
        if (i==0) {
          rc_R10PT10_jet_1_vec.SetPtEtaPhiE(rc_R10PT10_jets_pt->at(i), rc_R10PT10_jets_eta->at(i), rc_R10PT10_jets_phi->at(i), rc_R10PT10_jets_e->at(i));
          rc_R10PT10_meff_2j += rc_R10PT10_jets_pt->at(i);
          rc_R10PT10_meff_4j += rc_R10PT10_jets_pt->at(i);

          rc_R10PT10_pt_jet_1 = rc_R10PT10_jets_pt->at(i);
          rc_R10PT10_m_jet_1 = rc_R10PT10_jets_m->at(i);
          rc_R10PT10_SPLIT12_jet_1 = rc_R10PT10_jets_SPLIT12->at(i);
          rc_R10PT10_SPLIT23_jet_1 = rc_R10PT10_jets_SPLIT23->at(i);
          rc_R10PT10_tau21_jet_1 = rc_R10PT10_jets_tau21->at(i);
          rc_R10PT10_tau32_jet_1 = rc_R10PT10_jets_tau32->at(i);
          rc_R10PT10_C2_jet_1 = rc_R10PT10_jets_C2->at(i);
          rc_R10PT10_D2_jet_1 = rc_R10PT10_jets_D2->at(i);

          rc_R10PT10_nconst_jet_1 = rc_R10PT10_jets_nconst->at(i);
          rc_R10PT10_nconst_btag_jet_1 = rc_R10PT10_jets_nconst_btag->at(i);
          rc_R10PT10_nconst_btag_60_jet_1 = rc_R10PT10_jets_nconst_btag_60->at(i);
          rc_R10PT10_nconst_btag_70_jet_1 = rc_R10PT10_jets_nconst_btag_70->at(i);
          rc_R10PT10_nconst_btag_77_jet_1 = rc_R10PT10_jets_nconst_btag_77->at(i);
          rc_R10PT10_nconst_btag_85_jet_1 = rc_R10PT10_jets_nconst_btag_85->at(i);
        }
        if (i==1) {
          rc_R10PT10_jet_2_vec.SetPtEtaPhiE(rc_R10PT10_jets_pt->at(i), rc_R10PT10_jets_eta->at(i), rc_R10PT10_jets_phi->at(i), rc_R10PT10_jets_e->at(i));
          rc_R10PT10_meff_2j += rc_R10PT10_jets_pt->at(i);
          rc_R10PT10_meff_4j += rc_R10PT10_jets_pt->at(i);

          rc_R10PT10_pt_jet_2 = rc_R10PT10_jets_pt->at(i);
          rc_R10PT10_m_jet_2 = rc_R10PT10_jets_m->at(i);
          rc_R10PT10_SPLIT12_jet_2 = rc_R10PT10_jets_SPLIT12->at(i);
          rc_R10PT10_SPLIT23_jet_2 = rc_R10PT10_jets_SPLIT23->at(i);
          rc_R10PT10_tau21_jet_2 = rc_R10PT10_jets_tau21->at(i);
          rc_R10PT10_tau32_jet_2 = rc_R10PT10_jets_tau32->at(i);
          rc_R10PT10_C2_jet_2 = rc_R10PT10_jets_C2->at(i);
          rc_R10PT10_D2_jet_2 = rc_R10PT10_jets_D2->at(i);

          rc_R10PT10_nconst_jet_2 = rc_R10PT10_jets_nconst->at(i);
          rc_R10PT10_nconst_btag_jet_2 = rc_R10PT10_jets_nconst_btag->at(i);
          rc_R10PT10_nconst_btag_60_jet_2 = rc_R10PT10_jets_nconst_btag_60->at(i);
          rc_R10PT10_nconst_btag_70_jet_2 = rc_R10PT10_jets_nconst_btag_70->at(i);
          rc_R10PT10_nconst_btag_77_jet_2 = rc_R10PT10_jets_nconst_btag_77->at(i);
          rc_R10PT10_nconst_btag_85_jet_2 = rc_R10PT10_jets_nconst_btag_85->at(i);
        }
        if (i==2) {
          rc_R10PT10_meff_4j += rc_R10PT10_jets_pt->at(i);
          rc_R10PT10_pt_jet_3 = rc_R10PT10_jets_pt->at(i);
          rc_R10PT10_m_jet_3 = rc_R10PT10_jets_m->at(i);
          rc_R10PT10_SPLIT12_jet_3 = rc_R10PT10_jets_SPLIT12->at(i);
          rc_R10PT10_SPLIT23_jet_3 = rc_R10PT10_jets_SPLIT23->at(i);
          rc_R10PT10_tau21_jet_3 = rc_R10PT10_jets_tau21->at(i);
          rc_R10PT10_tau32_jet_3 = rc_R10PT10_jets_tau32->at(i);
          rc_R10PT10_C2_jet_3 = rc_R10PT10_jets_C2->at(i);
          rc_R10PT10_D2_jet_3 = rc_R10PT10_jets_D2->at(i);

          rc_R10PT10_nconst_jet_3 = rc_R10PT10_jets_nconst->at(i);
          rc_R10PT10_nconst_btag_jet_3 = rc_R10PT10_jets_nconst_btag->at(i);
          rc_R10PT10_nconst_btag_60_jet_3 = rc_R10PT10_jets_nconst_btag_60->at(i);
          rc_R10PT10_nconst_btag_70_jet_3 = rc_R10PT10_jets_nconst_btag_70->at(i);
          rc_R10PT10_nconst_btag_77_jet_3 = rc_R10PT10_jets_nconst_btag_77->at(i);
          rc_R10PT10_nconst_btag_85_jet_3 = rc_R10PT10_jets_nconst_btag_85->at(i);
        }
        if (i==3) {
          rc_R10PT10_meff_4j += rc_R10PT10_jets_pt->at(i);
          rc_R10PT10_pt_jet_4 = rc_R10PT10_jets_pt->at(i);
          rc_R10PT10_m_jet_4 = rc_R10PT10_jets_m->at(i);
          rc_R10PT10_SPLIT12_jet_4 = rc_R10PT10_jets_SPLIT12->at(i);
          rc_R10PT10_SPLIT23_jet_4 = rc_R10PT10_jets_SPLIT23->at(i);
          rc_R10PT10_tau21_jet_4 = rc_R10PT10_jets_tau21->at(i);
          rc_R10PT10_tau32_jet_4 = rc_R10PT10_jets_tau32->at(i);
          rc_R10PT10_C2_jet_4 = rc_R10PT10_jets_C2->at(i);
          rc_R10PT10_D2_jet_4 = rc_R10PT10_jets_D2->at(i);

          rc_R10PT10_nconst_jet_4 = rc_R10PT10_jets_nconst->at(i);
          rc_R10PT10_nconst_btag_jet_4 = rc_R10PT10_jets_nconst_btag->at(i);
          rc_R10PT10_nconst_btag_60_jet_4 = rc_R10PT10_jets_nconst_btag_60->at(i);
          rc_R10PT10_nconst_btag_70_jet_4 = rc_R10PT10_jets_nconst_btag_70->at(i);
          rc_R10PT10_nconst_btag_77_jet_4 = rc_R10PT10_jets_nconst_btag_77->at(i);
          rc_R10PT10_nconst_btag_85_jet_4 = rc_R10PT10_jets_nconst_btag_85->at(i);
        }
      }

      sum2jet_vec = rc_R10PT10_jet_1_vec + rc_R10PT10_jet_2_vec;

      rc_R10PT10_dphi_sum2jet = fabs(sum2jet_vec.Phi() - mettst_phi);
      if (rc_R10PT10_dphi_sum2jet > TMath::Pi()) 
        rc_R10PT10_dphi_sum2jet = 2*TMath::Pi() - rc_R10PT10_dphi_sum2jet;

      rc_R10PT10_meff_nj += mettst;
      rc_R10PT10_meff_2j += mettst;
      rc_R10PT10_meff_4j += mettst;
      rc_R10PT10_mT_2j = sum2jet_vec.Mt();

      if (rc_R10PT10_jets_n > 1) {

        // Effective mass of two leading fat-jets and MET

        // Take our Higgs candidate to be the fat-jet with the largest mass 
        // (among the 2 leading fat-jets)
        int iHiggs = 0; 
        int iW = 1; 
        if (rc_R10PT10_jets_m->at(0) < rc_R10PT10_jets_m->at(1)) {
          iHiggs = 1; iW = 0;
        }

        rc_R10PT10_pt_h = rc_R10PT10_jets_pt->at(iHiggs);
        rc_R10PT10_pt_W = rc_R10PT10_jets_pt->at(iW);

        rc_R10PT10_m_h = rc_R10PT10_jets_m->at(iHiggs);
        rc_R10PT10_m_W = rc_R10PT10_jets_m->at(iW);

        rc_R10PT10_SPLIT12_h = rc_R10PT10_jets_SPLIT12->at(iHiggs);
        rc_R10PT10_SPLIT12_W = rc_R10PT10_jets_SPLIT12->at(iW);

        rc_R10PT10_SPLIT23_h = rc_R10PT10_jets_SPLIT23->at(iHiggs);
        rc_R10PT10_SPLIT23_W = rc_R10PT10_jets_SPLIT23->at(iW);

        rc_R10PT10_tau21_h = rc_R10PT10_jets_tau21->at(iHiggs);
        rc_R10PT10_tau21_W = rc_R10PT10_jets_tau21->at(iW);

        rc_R10PT10_tau32_h = rc_R10PT10_jets_tau32->at(iHiggs);
        rc_R10PT10_tau32_W = rc_R10PT10_jets_tau32->at(iW);

        rc_R10PT10_C2_h = rc_R10PT10_jets_C2->at(iHiggs);
        rc_R10PT10_C2_W = rc_R10PT10_jets_C2->at(iW);

        rc_R10PT10_D2_h = rc_R10PT10_jets_D2->at(iHiggs);
        rc_R10PT10_D2_W = rc_R10PT10_jets_D2->at(iW);

        rc_R10PT10_nconst_h = rc_R10PT10_jets_nconst->at(iHiggs);
        rc_R10PT10_nconst_W = rc_R10PT10_jets_nconst->at(iW);
        rc_R10PT10_nconst_btag_h = rc_R10PT10_jets_nconst_btag->at(iHiggs);
        rc_R10PT10_nconst_btag_W = rc_R10PT10_jets_nconst_btag->at(iW);
        rc_R10PT10_nconst_btag_60_h = rc_R10PT10_jets_nconst_btag_60->at(iHiggs);
        rc_R10PT10_nconst_btag_60_W = rc_R10PT10_jets_nconst_btag_60->at(iW);
        rc_R10PT10_nconst_btag_70_h = rc_R10PT10_jets_nconst_btag_70->at(iHiggs);
        rc_R10PT10_nconst_btag_70_W = rc_R10PT10_jets_nconst_btag_70->at(iW);
        rc_R10PT10_nconst_btag_77_h = rc_R10PT10_jets_nconst_btag_77->at(iHiggs);
        rc_R10PT10_nconst_btag_77_W = rc_R10PT10_jets_nconst_btag_77->at(iW);
        rc_R10PT10_nconst_btag_85_h = rc_R10PT10_jets_nconst_btag_85->at(iHiggs);
        rc_R10PT10_nconst_btag_85_W = rc_R10PT10_jets_nconst_btag_85->at(iW);

        float dEta = fabs( rc_R10PT10_jets_eta->at(iHiggs) - rc_R10PT10_jets_eta->at(iW) );
        float dPhi = fabs( rc_R10PT10_jets_phi->at(iHiggs) - rc_R10PT10_jets_phi->at(iW) );
        if (dPhi > TMath::Pi()) dPhi = 2*TMath::Pi()-dPhi;
        rc_R10PT10_dR_Wh = sqrt(dEta*dEta + dPhi*dPhi); 
        rc_R10PT10_dEta_Wh = dEta; 
        rc_R10PT10_dPhi_Wh = dPhi; 

      }

      // fill 'rc_R12PT10' reclustered jet variables
      TLorentzVector rc_R12PT10_jet_1_vec;
      TLorentzVector rc_R12PT10_jet_2_vec;

      for(int i=0; i < rc_R12PT10_jets_n; ++i) {

        rc_R12PT10_meff_nj += rc_R12PT10_jets_pt->at(i);

        float dphi_rc_R12PT10_jet_mettst = fabs(rc_R12PT10_jets_phi->at(i) - mettst_phi);
        if (dphi_rc_R12PT10_jet_mettst > TMath::Pi()) 
          dphi_rc_R12PT10_jet_mettst = 2*TMath::Pi() - dphi_rc_R12PT10_jet_mettst;

        // calculate rc_R12PT10_dphi_1jet using the leading fat-jet
        if (i==0)
          rc_R12PT10_dphi_1jet = dphi_rc_R12PT10_jet_mettst;

        // calculate rc_R12PT10_dphi_min using the two leading fat-jets
        if (i < 3 && dphi_rc_R12PT10_jet_mettst < rc_R12PT10_dphi_min)
          rc_R12PT10_dphi_min = dphi_rc_R12PT10_jet_mettst;

        // calculate rc_R12PT10_dphi_min_alljets using all fat-jets
        if (dphi_rc_R12PT10_jet_mettst < rc_R12PT10_dphi_min_alljets)
          rc_R12PT10_dphi_min_alljets = dphi_rc_R12PT10_jet_mettst;

        // fill lar-R jet variables
        if (i==0) {
          rc_R12PT10_jet_1_vec.SetPtEtaPhiE(rc_R12PT10_jets_pt->at(i), rc_R12PT10_jets_eta->at(i), rc_R12PT10_jets_phi->at(i), rc_R12PT10_jets_e->at(i));
          rc_R12PT10_meff_2j += rc_R12PT10_jets_pt->at(i);
          rc_R12PT10_meff_2j += rc_R12PT10_jets_pt->at(i);

          rc_R12PT10_pt_jet_1 = rc_R12PT10_jets_pt->at(i);
          rc_R12PT10_m_jet_1 = rc_R12PT10_jets_m->at(i);
          rc_R12PT10_SPLIT12_jet_1 = rc_R12PT10_jets_SPLIT12->at(i);
          rc_R12PT10_SPLIT23_jet_1 = rc_R12PT10_jets_SPLIT23->at(i);
          rc_R12PT10_tau21_jet_1 = rc_R12PT10_jets_tau21->at(i);
          rc_R12PT10_tau32_jet_1 = rc_R12PT10_jets_tau32->at(i);
          rc_R12PT10_C2_jet_1 = rc_R12PT10_jets_C2->at(i);
          rc_R12PT10_D2_jet_1 = rc_R12PT10_jets_D2->at(i);

          rc_R12PT10_nconst_jet_1 = rc_R12PT10_jets_nconst->at(i);
          rc_R12PT10_nconst_btag_jet_1 = rc_R12PT10_jets_nconst_btag->at(i);
          rc_R12PT10_nconst_btag_60_jet_1 = rc_R12PT10_jets_nconst_btag_60->at(i);
          rc_R12PT10_nconst_btag_70_jet_1 = rc_R12PT10_jets_nconst_btag_70->at(i);
          rc_R12PT10_nconst_btag_77_jet_1 = rc_R12PT10_jets_nconst_btag_77->at(i);
          rc_R12PT10_nconst_btag_85_jet_1 = rc_R12PT10_jets_nconst_btag_85->at(i);
        }
        if (i==1) {
          rc_R12PT10_jet_2_vec.SetPtEtaPhiE(rc_R12PT10_jets_pt->at(i), rc_R12PT10_jets_eta->at(i), rc_R12PT10_jets_phi->at(i), rc_R12PT10_jets_e->at(i));
          rc_R12PT10_meff_2j += rc_R12PT10_jets_pt->at(i);
          rc_R12PT10_meff_4j += rc_R12PT10_jets_pt->at(i);

          rc_R12PT10_pt_jet_2 = rc_R12PT10_jets_pt->at(i);
          rc_R12PT10_m_jet_2 = rc_R12PT10_jets_m->at(i);
          rc_R12PT10_SPLIT12_jet_2 = rc_R12PT10_jets_SPLIT12->at(i);
          rc_R12PT10_SPLIT23_jet_2 = rc_R12PT10_jets_SPLIT23->at(i);
          rc_R12PT10_tau21_jet_2 = rc_R12PT10_jets_tau21->at(i);
          rc_R12PT10_tau32_jet_2 = rc_R12PT10_jets_tau32->at(i);
          rc_R12PT10_C2_jet_2 = rc_R12PT10_jets_C2->at(i);
          rc_R12PT10_D2_jet_2 = rc_R12PT10_jets_D2->at(i);

          rc_R12PT10_nconst_jet_2 = rc_R12PT10_jets_nconst->at(i);
          rc_R12PT10_nconst_btag_jet_2 = rc_R12PT10_jets_nconst_btag->at(i);
          rc_R12PT10_nconst_btag_60_jet_2 = rc_R12PT10_jets_nconst_btag_60->at(i);
          rc_R12PT10_nconst_btag_70_jet_2 = rc_R12PT10_jets_nconst_btag_70->at(i);
          rc_R12PT10_nconst_btag_77_jet_2 = rc_R12PT10_jets_nconst_btag_77->at(i);
          rc_R12PT10_nconst_btag_85_jet_2 = rc_R12PT10_jets_nconst_btag_85->at(i);
        }
        if (i==2) {
          rc_R12PT10_meff_4j += rc_R12PT10_jets_pt->at(i);
          rc_R12PT10_pt_jet_3 = rc_R12PT10_jets_pt->at(i);
          rc_R12PT10_m_jet_3 = rc_R12PT10_jets_m->at(i);
          rc_R12PT10_SPLIT12_jet_3 = rc_R12PT10_jets_SPLIT12->at(i);
          rc_R12PT10_SPLIT23_jet_3 = rc_R12PT10_jets_SPLIT23->at(i);
          rc_R12PT10_tau21_jet_3 = rc_R12PT10_jets_tau21->at(i);
          rc_R12PT10_tau32_jet_3 = rc_R12PT10_jets_tau32->at(i);
          rc_R12PT10_C2_jet_3 = rc_R12PT10_jets_C2->at(i);
          rc_R12PT10_D2_jet_3 = rc_R12PT10_jets_D2->at(i);

          rc_R12PT10_nconst_jet_3 = rc_R12PT10_jets_nconst->at(i);
          rc_R12PT10_nconst_btag_jet_3 = rc_R12PT10_jets_nconst_btag->at(i);
          rc_R12PT10_nconst_btag_60_jet_3 = rc_R12PT10_jets_nconst_btag_60->at(i);
          rc_R12PT10_nconst_btag_70_jet_3 = rc_R12PT10_jets_nconst_btag_70->at(i);
          rc_R12PT10_nconst_btag_77_jet_3 = rc_R12PT10_jets_nconst_btag_77->at(i);
          rc_R12PT10_nconst_btag_85_jet_3 = rc_R12PT10_jets_nconst_btag_85->at(i);
        }
        if (i==3) {
          rc_R12PT10_meff_4j += rc_R12PT10_jets_pt->at(i);
          rc_R12PT10_pt_jet_4 = rc_R12PT10_jets_pt->at(i);
          rc_R12PT10_m_jet_4 = rc_R12PT10_jets_m->at(i);
          rc_R12PT10_SPLIT12_jet_4 = rc_R12PT10_jets_SPLIT12->at(i);
          rc_R12PT10_SPLIT23_jet_4 = rc_R12PT10_jets_SPLIT23->at(i);
          rc_R12PT10_tau21_jet_4 = rc_R12PT10_jets_tau21->at(i);
          rc_R12PT10_tau32_jet_4 = rc_R12PT10_jets_tau32->at(i);
          rc_R12PT10_C2_jet_4 = rc_R12PT10_jets_C2->at(i);
          rc_R12PT10_D2_jet_4 = rc_R12PT10_jets_D2->at(i);

          rc_R12PT10_nconst_jet_4 = rc_R12PT10_jets_nconst->at(i);
          rc_R12PT10_nconst_btag_jet_4 = rc_R12PT10_jets_nconst_btag->at(i);
          rc_R12PT10_nconst_btag_60_jet_4 = rc_R12PT10_jets_nconst_btag_60->at(i);
          rc_R12PT10_nconst_btag_70_jet_4 = rc_R12PT10_jets_nconst_btag_70->at(i);
          rc_R12PT10_nconst_btag_77_jet_4 = rc_R12PT10_jets_nconst_btag_77->at(i);
          rc_R12PT10_nconst_btag_85_jet_4 = rc_R12PT10_jets_nconst_btag_85->at(i);
        }
      }

      sum2jet_vec = rc_R12PT10_jet_1_vec + rc_R12PT10_jet_2_vec;

      rc_R12PT10_dphi_sum2jet = fabs(sum2jet_vec.Phi() - mettst_phi);
      if (rc_R12PT10_dphi_sum2jet > TMath::Pi()) 
        rc_R12PT10_dphi_sum2jet = 2*TMath::Pi() - rc_R12PT10_dphi_sum2jet;

      rc_R12PT10_meff_nj += mettst;
      rc_R12PT10_meff_2j += mettst;
      rc_R12PT10_meff_4j += mettst;
      rc_R12PT10_mT_2j = sum2jet_vec.Mt();

      if (rc_R12PT10_jets_n > 1) {

        // Effective mass of two leading fat-jets and MET

        // Take our Higgs candidate to be the fat-jet with the largest mass 
        // (among the 2 leading fat-jets)
        int iHiggs = 0; 
        int iW = 1; 
        if (rc_R12PT10_jets_m->at(0) < rc_R12PT10_jets_m->at(1)) {
          iHiggs = 1; iW = 0;
        }

        rc_R12PT10_pt_h = rc_R12PT10_jets_pt->at(iHiggs);
        rc_R12PT10_pt_W = rc_R12PT10_jets_pt->at(iW);

        rc_R12PT10_m_h = rc_R12PT10_jets_m->at(iHiggs);
        rc_R12PT10_m_W = rc_R12PT10_jets_m->at(iW);

        rc_R12PT10_SPLIT12_h = rc_R12PT10_jets_SPLIT12->at(iHiggs);
        rc_R12PT10_SPLIT12_W = rc_R12PT10_jets_SPLIT12->at(iW);

        rc_R12PT10_SPLIT23_h = rc_R12PT10_jets_SPLIT23->at(iHiggs);
        rc_R12PT10_SPLIT23_W = rc_R12PT10_jets_SPLIT23->at(iW);

        rc_R12PT10_tau21_h = rc_R12PT10_jets_tau21->at(iHiggs);
        rc_R12PT10_tau21_W = rc_R12PT10_jets_tau21->at(iW);

        rc_R12PT10_tau32_h = rc_R12PT10_jets_tau32->at(iHiggs);
        rc_R12PT10_tau32_W = rc_R12PT10_jets_tau32->at(iW);

        rc_R12PT10_C2_h = rc_R12PT10_jets_C2->at(iHiggs);
        rc_R12PT10_C2_W = rc_R12PT10_jets_C2->at(iW);

        rc_R12PT10_D2_h = rc_R12PT10_jets_D2->at(iHiggs);
        rc_R12PT10_D2_W = rc_R12PT10_jets_D2->at(iW);

        rc_R12PT10_nconst_h = rc_R12PT10_jets_nconst->at(iHiggs);
        rc_R12PT10_nconst_W = rc_R12PT10_jets_nconst->at(iW);
        rc_R12PT10_nconst_btag_h = rc_R12PT10_jets_nconst_btag->at(iHiggs);
        rc_R12PT10_nconst_btag_W = rc_R12PT10_jets_nconst_btag->at(iW);
        rc_R12PT10_nconst_btag_60_h = rc_R12PT10_jets_nconst_btag_60->at(iHiggs);
        rc_R12PT10_nconst_btag_60_W = rc_R12PT10_jets_nconst_btag_60->at(iW);
        rc_R12PT10_nconst_btag_70_h = rc_R12PT10_jets_nconst_btag_70->at(iHiggs);
        rc_R12PT10_nconst_btag_70_W = rc_R12PT10_jets_nconst_btag_70->at(iW);
        rc_R12PT10_nconst_btag_77_h = rc_R12PT10_jets_nconst_btag_77->at(iHiggs);
        rc_R12PT10_nconst_btag_77_W = rc_R12PT10_jets_nconst_btag_77->at(iW);
        rc_R12PT10_nconst_btag_85_h = rc_R12PT10_jets_nconst_btag_85->at(iHiggs);
        rc_R12PT10_nconst_btag_85_W = rc_R12PT10_jets_nconst_btag_85->at(iW);

        float dEta = fabs( rc_R12PT10_jets_eta->at(iHiggs) - rc_R12PT10_jets_eta->at(iW) );
        float dPhi = fabs( rc_R12PT10_jets_phi->at(iHiggs) - rc_R12PT10_jets_phi->at(iW) );
        if (dPhi > TMath::Pi()) dPhi = 2*TMath::Pi()-dPhi;
        rc_R12PT10_dR_Wh = sqrt(dEta*dEta + dPhi*dPhi); 
        rc_R12PT10_dEta_Wh = dEta; 
        rc_R12PT10_dPhi_Wh = dPhi; 

      }

      // fill 'rc_R15PT10' reclustered jet variables
      TLorentzVector rc_R15PT10_jet_1_vec;
      TLorentzVector rc_R15PT10_jet_2_vec;

      for(int i=0; i < rc_R15PT10_jets_n; ++i) {

        rc_R15PT10_meff_nj += rc_R15PT10_jets_pt->at(i);

        float dphi_rc_R15PT10_jet_mettst = fabs(rc_R15PT10_jets_phi->at(i) - mettst_phi);
        if (dphi_rc_R15PT10_jet_mettst > TMath::Pi()) 
          dphi_rc_R15PT10_jet_mettst = 2*TMath::Pi() - dphi_rc_R15PT10_jet_mettst;

        // calculate rc_R15PT10_dphi_1jet using the leading fat-jet
        if (i==0)
          rc_R15PT10_dphi_1jet = dphi_rc_R15PT10_jet_mettst;

        // calculate rc_R15PT10_dphi_min using the two leading fat-jets
        if (i < 3 && dphi_rc_R15PT10_jet_mettst < rc_R15PT10_dphi_min)
          rc_R15PT10_dphi_min = dphi_rc_R15PT10_jet_mettst;

        // calculate rc_R15PT10_dphi_min_alljets using all fat-jets
        if (dphi_rc_R15PT10_jet_mettst < rc_R15PT10_dphi_min_alljets)
          rc_R15PT10_dphi_min_alljets = dphi_rc_R15PT10_jet_mettst;

        // fill lar-R jet variables
        if (i==0) {
          rc_R15PT10_jet_1_vec.SetPtEtaPhiE(rc_R15PT10_jets_pt->at(i), rc_R15PT10_jets_eta->at(i), rc_R15PT10_jets_phi->at(i), rc_R15PT10_jets_e->at(i));
          rc_R15PT10_meff_2j += rc_R15PT10_jets_pt->at(i);
          rc_R15PT10_meff_4j += rc_R15PT10_jets_pt->at(i);

          rc_R15PT10_pt_jet_1 = rc_R15PT10_jets_pt->at(i);
          rc_R15PT10_m_jet_1 = rc_R15PT10_jets_m->at(i);
          rc_R15PT10_SPLIT12_jet_1 = rc_R15PT10_jets_SPLIT12->at(i);
          rc_R15PT10_SPLIT23_jet_1 = rc_R15PT10_jets_SPLIT23->at(i);
          rc_R15PT10_tau21_jet_1 = rc_R15PT10_jets_tau21->at(i);
          rc_R15PT10_tau32_jet_1 = rc_R15PT10_jets_tau32->at(i);
          rc_R15PT10_C2_jet_1 = rc_R15PT10_jets_C2->at(i);
          rc_R15PT10_D2_jet_1 = rc_R15PT10_jets_D2->at(i);

          rc_R15PT10_nconst_jet_1 = rc_R15PT10_jets_nconst->at(i);
          rc_R15PT10_nconst_btag_jet_1 = rc_R15PT10_jets_nconst_btag->at(i);
          rc_R15PT10_nconst_btag_60_jet_1 = rc_R15PT10_jets_nconst_btag_60->at(i);
          rc_R15PT10_nconst_btag_70_jet_1 = rc_R15PT10_jets_nconst_btag_70->at(i);
          rc_R15PT10_nconst_btag_77_jet_1 = rc_R15PT10_jets_nconst_btag_77->at(i);
          rc_R15PT10_nconst_btag_85_jet_1 = rc_R15PT10_jets_nconst_btag_85->at(i);
        }
        if (i==1) {
          rc_R15PT10_jet_2_vec.SetPtEtaPhiE(rc_R15PT10_jets_pt->at(i), rc_R15PT10_jets_eta->at(i), rc_R15PT10_jets_phi->at(i), rc_R15PT10_jets_e->at(i));
          rc_R15PT10_meff_2j += rc_R15PT10_jets_pt->at(i);
          rc_R15PT10_meff_4j += rc_R15PT10_jets_pt->at(i);

          rc_R15PT10_pt_jet_2 = rc_R15PT10_jets_pt->at(i);
          rc_R15PT10_m_jet_2 = rc_R15PT10_jets_m->at(i);
          rc_R15PT10_SPLIT12_jet_2 = rc_R15PT10_jets_SPLIT12->at(i);
          rc_R15PT10_SPLIT23_jet_2 = rc_R15PT10_jets_SPLIT23->at(i);
          rc_R15PT10_tau21_jet_2 = rc_R15PT10_jets_tau21->at(i);
          rc_R15PT10_tau32_jet_2 = rc_R15PT10_jets_tau32->at(i);
          rc_R15PT10_C2_jet_2 = rc_R15PT10_jets_C2->at(i);
          rc_R15PT10_D2_jet_2 = rc_R15PT10_jets_D2->at(i);

          rc_R15PT10_nconst_jet_2 = rc_R15PT10_jets_nconst->at(i);
          rc_R15PT10_nconst_btag_jet_2 = rc_R15PT10_jets_nconst_btag->at(i);
          rc_R15PT10_nconst_btag_60_jet_2 = rc_R15PT10_jets_nconst_btag_60->at(i);
          rc_R15PT10_nconst_btag_70_jet_2 = rc_R15PT10_jets_nconst_btag_70->at(i);
          rc_R15PT10_nconst_btag_77_jet_2 = rc_R15PT10_jets_nconst_btag_77->at(i);
          rc_R15PT10_nconst_btag_85_jet_2 = rc_R15PT10_jets_nconst_btag_85->at(i);
        }
        if (i==2) {
          rc_R15PT10_meff_4j += rc_R15PT10_jets_pt->at(i);
          rc_R15PT10_pt_jet_3 = rc_R15PT10_jets_pt->at(i);
          rc_R15PT10_m_jet_3 = rc_R15PT10_jets_m->at(i);
          rc_R15PT10_SPLIT12_jet_3 = rc_R15PT10_jets_SPLIT12->at(i);
          rc_R15PT10_SPLIT23_jet_3 = rc_R15PT10_jets_SPLIT23->at(i);
          rc_R15PT10_tau21_jet_3 = rc_R15PT10_jets_tau21->at(i);
          rc_R15PT10_tau32_jet_3 = rc_R15PT10_jets_tau32->at(i);
          rc_R15PT10_C2_jet_3 = rc_R15PT10_jets_C2->at(i);
          rc_R15PT10_D2_jet_3 = rc_R15PT10_jets_D2->at(i);

          rc_R15PT10_nconst_jet_3 = rc_R15PT10_jets_nconst->at(i);
          rc_R15PT10_nconst_btag_jet_3 = rc_R15PT10_jets_nconst_btag->at(i);
          rc_R15PT10_nconst_btag_60_jet_3 = rc_R15PT10_jets_nconst_btag_60->at(i);
          rc_R15PT10_nconst_btag_70_jet_3 = rc_R15PT10_jets_nconst_btag_70->at(i);
          rc_R15PT10_nconst_btag_77_jet_3 = rc_R15PT10_jets_nconst_btag_77->at(i);
          rc_R15PT10_nconst_btag_85_jet_3 = rc_R15PT10_jets_nconst_btag_85->at(i);
        }
        if (i==3) {
          rc_R15PT10_meff_4j += rc_R15PT10_jets_pt->at(i);
          rc_R15PT10_pt_jet_4 = rc_R15PT10_jets_pt->at(i);
          rc_R15PT10_m_jet_4 = rc_R15PT10_jets_m->at(i);
          rc_R15PT10_SPLIT12_jet_4 = rc_R15PT10_jets_SPLIT12->at(i);
          rc_R15PT10_SPLIT23_jet_4 = rc_R15PT10_jets_SPLIT23->at(i);
          rc_R15PT10_tau21_jet_4 = rc_R15PT10_jets_tau21->at(i);
          rc_R15PT10_tau32_jet_4 = rc_R15PT10_jets_tau32->at(i);
          rc_R15PT10_C2_jet_4 = rc_R15PT10_jets_C2->at(i);
          rc_R15PT10_D2_jet_4 = rc_R15PT10_jets_D2->at(i);

          rc_R15PT10_nconst_jet_4 = rc_R15PT10_jets_nconst->at(i);
          rc_R15PT10_nconst_btag_jet_4 = rc_R15PT10_jets_nconst_btag->at(i);
          rc_R15PT10_nconst_btag_60_jet_4 = rc_R15PT10_jets_nconst_btag_60->at(i);
          rc_R15PT10_nconst_btag_70_jet_4 = rc_R15PT10_jets_nconst_btag_70->at(i);
          rc_R15PT10_nconst_btag_77_jet_4 = rc_R15PT10_jets_nconst_btag_77->at(i);
          rc_R15PT10_nconst_btag_85_jet_4 = rc_R15PT10_jets_nconst_btag_85->at(i);
        }
      }

      sum2jet_vec = rc_R15PT10_jet_1_vec + rc_R15PT10_jet_2_vec;

      rc_R15PT10_dphi_sum2jet = fabs(sum2jet_vec.Phi() - mettst_phi);
      if (rc_R15PT10_dphi_sum2jet > TMath::Pi()) 
        rc_R15PT10_dphi_sum2jet = 2*TMath::Pi() - rc_R15PT10_dphi_sum2jet;

      rc_R15PT10_meff_nj += mettst;
      rc_R15PT10_meff_2j += mettst;
      rc_R15PT10_meff_4j += mettst;
      rc_R15PT10_mT_2j = sum2jet_vec.Mt();

      if (rc_R15PT10_jets_n > 1) {

        // Effective mass of two leading fat-jets and MET

        // Take our Higgs candidate to be the fat-jet with the largest mass 
        // (among the 2 leading fat-jets)
        int iHiggs = 0; 
        int iW = 1; 
        if (rc_R15PT10_jets_m->at(0) < rc_R15PT10_jets_m->at(1)) {
          iHiggs = 1; iW = 0;
        }

        rc_R15PT10_pt_h = rc_R15PT10_jets_pt->at(iHiggs);
        rc_R15PT10_pt_W = rc_R15PT10_jets_pt->at(iW);

        rc_R15PT10_m_h = rc_R15PT10_jets_m->at(iHiggs);
        rc_R15PT10_m_W = rc_R15PT10_jets_m->at(iW);

        rc_R15PT10_SPLIT12_h = rc_R15PT10_jets_SPLIT12->at(iHiggs);
        rc_R15PT10_SPLIT12_W = rc_R15PT10_jets_SPLIT12->at(iW);

        rc_R15PT10_SPLIT23_h = rc_R15PT10_jets_SPLIT23->at(iHiggs);
        rc_R15PT10_SPLIT23_W = rc_R15PT10_jets_SPLIT23->at(iW);

        rc_R15PT10_tau21_h = rc_R15PT10_jets_tau21->at(iHiggs);
        rc_R15PT10_tau21_W = rc_R15PT10_jets_tau21->at(iW);

        rc_R15PT10_tau32_h = rc_R15PT10_jets_tau32->at(iHiggs);
        rc_R15PT10_tau32_W = rc_R15PT10_jets_tau32->at(iW);

        rc_R15PT10_C2_h = rc_R15PT10_jets_C2->at(iHiggs);
        rc_R15PT10_C2_W = rc_R15PT10_jets_C2->at(iW);

        rc_R15PT10_D2_h = rc_R15PT10_jets_D2->at(iHiggs);
        rc_R15PT10_D2_W = rc_R15PT10_jets_D2->at(iW);

        rc_R15PT10_nconst_h = rc_R15PT10_jets_nconst->at(iHiggs);
        rc_R15PT10_nconst_W = rc_R15PT10_jets_nconst->at(iW);
        rc_R15PT10_nconst_btag_h = rc_R15PT10_jets_nconst_btag->at(iHiggs);
        rc_R15PT10_nconst_btag_W = rc_R15PT10_jets_nconst_btag->at(iW);
        rc_R15PT10_nconst_btag_60_h = rc_R15PT10_jets_nconst_btag_60->at(iHiggs);
        rc_R15PT10_nconst_btag_60_W = rc_R15PT10_jets_nconst_btag_60->at(iW);
        rc_R15PT10_nconst_btag_70_h = rc_R15PT10_jets_nconst_btag_70->at(iHiggs);
        rc_R15PT10_nconst_btag_70_W = rc_R15PT10_jets_nconst_btag_70->at(iW);
        rc_R15PT10_nconst_btag_77_h = rc_R15PT10_jets_nconst_btag_77->at(iHiggs);
        rc_R15PT10_nconst_btag_77_W = rc_R15PT10_jets_nconst_btag_77->at(iW);
        rc_R15PT10_nconst_btag_85_h = rc_R15PT10_jets_nconst_btag_85->at(iHiggs);
        rc_R15PT10_nconst_btag_85_W = rc_R15PT10_jets_nconst_btag_85->at(iW);

        float dEta = fabs( rc_R15PT10_jets_eta->at(iHiggs) - rc_R15PT10_jets_eta->at(iW) );
        float dPhi = fabs( rc_R15PT10_jets_phi->at(iHiggs) - rc_R15PT10_jets_phi->at(iW) );
        if (dPhi > TMath::Pi()) dPhi = 2*TMath::Pi()-dPhi;
        rc_R15PT10_dR_Wh = sqrt(dEta*dEta + dPhi*dPhi); 
        rc_R15PT10_dEta_Wh = dEta; 
        rc_R15PT10_dPhi_Wh = dPhi; 

      }

      outTree->Fill(); 
   }
   outFile->cd();
   outTree->Write();
   delete outTree;
}
