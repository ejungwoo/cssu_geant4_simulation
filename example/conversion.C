void conversion(TString input = "data/sim_alpha1.txt")
{
    double electronEfficiency = 0.98;
    double z1 = 20;
    double z2 = 70;

    TString output = input;
    output.ReplaceAll(".txt",".root");
    TFile *file = new TFile(output,"recreate");

    TTree *treePoint = new TTree("point","");
    int eventID, volumeID;
    double x, y, z, energy;
    treePoint -> Branch("eventID",&eventID);
    treePoint -> Branch("volumeID",&volumeID);
    treePoint -> Branch("x",&x);
    treePoint -> Branch("y",&y);
    treePoint -> Branch("z",&z);
    treePoint -> Branch("energy",&energy);

    double energySum = 0;
    double energyFull = 0;
    TTree *treeEnergySum = new TTree("energySum",Form("electron efficiency %f",electronEfficiency));
    treeEnergySum -> Branch("energySum",&energySum);
    treeEnergySum -> Branch("energyFull",&energyFull);

    int lastEventID = 0;
    ifstream dataFile(input);
    while (dataFile >> eventID >> volumeID >> x >> y >> z >> energy) {
        treePoint -> Fill();
        if (gRandom->Rndm()<=electronEfficiency) {
            if (z>z1 && z<z2) {
                energySum += energy;
            }
            energyFull += energy;
        }
        if (eventID!=lastEventID) {
            treeEnergySum -> Fill();
            energySum = 0.;
            energyFull = 0.;
            lastEventID = eventID;
        }
    }
    cout << treePoint -> GetEntries() << endl;

    file -> cd();
    treePoint -> Write();
    treeEnergySum -> Write();

    //////////////////////////////////////////////////////////

    auto histEZ = new TH2D("histEZ",Form("efficiency=%.2f;z;energy",electronEfficiency),100,0,100,100,0,0.5);
    auto histEnergySum = new TH1D("histEnergySum",Form("efficiency=%.2f;energy sum",electronEfficiency),200,0,6);

    auto cvs = new TCanvas("cvs1","",1300,600);
    cvs -> Divide(2,1);
    cvs -> cd(1); treePoint -> Draw("energy:z>>histEZ","","colz");
    cvs -> cd(2); treeEnergySum -> Draw("energySum>>histEnergySum");
    TString figure = input;
    figure.ReplaceAll("data/","figure/");
    figure.ReplaceAll(".txt",".png");
    cvs -> SaveAs("figures/summary_energy.png");

    cout << output << endl;
}
