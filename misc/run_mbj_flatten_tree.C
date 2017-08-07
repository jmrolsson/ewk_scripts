#include <iostream>
#include <TTree.h>
#include <TChain.h>
#include <TH1F.h>
#include <TString.h>
#include "mbj_flatten_tree.h"

/****************************************************************
 To compile:
 g++ $(root-config --cflags --libs) mbj_flatten_tree.C run_mbj_flatten_tree.C -o run_mbj_flatten_tree
 to run:
 ./run_mbj_flatten_tree treename input_filename output_filename
*****************************************************************/

using namespace std;

int main(int argc, char* argv[])
{
  // default input arguments
  TString treename = "nominal";
  TString input_filename = "input_filename.root";
  TString output_filename = "output_filename.root";

  // optional input arguments
  if (argc > 1)
    treename = argv[1];
  if (argc > 2)
    input_filename = argv[2];
  if (argc > 3)
    output_filename = argv[3];

  /* cout << "Processing:" << endl; */
  /* cout << "tree: " << treename << endl; */
  /* cout << "input file: " << input_filename << endl; */
  /* cout << "output file: " << output_filename << endl; */
 
  TChain *chain = new TChain(treename.Data());
  chain->Add(input_filename.Data());

  TFile *input_file = new TFile(input_filename);
  TFile *output_file = new TFile(output_filename, "recreate");

  mbj_flatten_tree *mbj_ft = new mbj_flatten_tree(chain);
  mbj_ft->Loop(output_file);

  TH1D *cutflow = (TH1D*)input_file->Get("cut_flow");
  TH1D *xs = (TH1D*)input_file->Get("cross_section");
  output_file->cd();
  cutflow->Write();
  xs->Write();

  return 0;
}

