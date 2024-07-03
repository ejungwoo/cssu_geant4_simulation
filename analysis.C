void analysis()
{
    auto file = new TFile("data_cf4_alpha.root","read");
    auto tree = (TTree*) file -> Get("energy");

    int eventID, volumeID;
    double x, y, z, energy;
    tree -> SetBranchAddress("eventID",&eventID);
    tree -> SetBranchAddress("volumeID",&volumeID);
    tree -> SetBranchAddress("x",&x);
    tree -> SetBranchAddress("y",&y);
    tree -> SetBranchAddress("z",&z);
    tree -> SetBranchAddress("energy",&energy);

    auto hist_z_energy_1d = new TH1D("hist_z_energy_1d",";z;energy sum", 200,0,200);
    auto hist_z_energy_2d = new TH2D("hist_z_energy_2d",";z;energy", 200,0,200, 200,0,0.05);
    auto numEntries = tree -> GetEntries();
    for (auto iEntry=0; iEntry<numEntries; ++iEntry)
    {
        tree -> GetEntry(iEntry);
        //////////////////////////////////////////////////////////////////////

        hist_z_energy_2d -> Fill(z,energy);

        //double energySum = 0;
        //hist_z_energy_1d -> Fill(z,energySum);

        //////////////////////////////////////////////////////////////////////
    }
    new TCanvas("cvs1","",1200,800);
    hist_z_energy_1d -> Draw("colz");

    new TCanvas("cvs2","",1200,800);
    hist_z_energy_2d -> Draw("colz");
}
