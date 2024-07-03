void conversion(TString inputFileName = "data/sim_alpha2.txt")
{
    TString outputFileName = inputFileName;
    outputFileName.ReplaceAll(".txt",".root");
    TFile *file = new TFile(outputFileName,"recreate");

    TTree *tree = new TTree("energy","");
    int eventID, volumeID;
    double x, y, z, energy;
    tree -> Branch("eventID",&eventID);
    tree -> Branch("volumeID",&volumeID);
    tree -> Branch("x",&x);
    tree -> Branch("y",&y);
    tree -> Branch("z",&z);
    tree -> Branch("energy",&energy);

    TTree *tree2 = new TTree("energy","");
    double energySum;
    tree2 -> Branch("energySum",&energySum);

    ifstream data_file("data_cf4_alpha.txt");
    while (data_file >> eventID >> volumeID >> x >> y >> z >> energy) {
        tree -> Fill();
    }

    file -> cd();
    tree -> Write();
    tree2 -> Write();

    cout << outputFileName << endl;
}
