void analysis(TString input = "data/sim_alpha1.root")
{
    auto file = new TFile(input,"read");
    auto tree = (TTree*) file -> Get("energySum");

    auto histEnergySum = new TH1D("histEnergySum","energy sum",200,0,6);
    tree -> Project("histEnergySum","energySum");

    auto histEnergyFull = new TH1D("histEnergyFull","energy sum",200,1,7);
    tree -> Project("histEnergyFull","energyFull");

    auto cvs = new TCanvas("cvs1","",1300,600);
    cvs -> Divide(2,1);
    cvs -> cd(1);
    histEnergySum -> Draw();
    auto fit = new TF1("fit","gaus(0)",0,6);
    histEnergySum -> Fit(fit);

    cvs -> cd(2);
    histEnergyFull -> Draw();
}
