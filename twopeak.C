double fAlphaEnergy1 = 5.486;// MeV (85.2 %)
double fAlphaEnergy2 = 5.443;// MeV (12.8 %)
double fAEBR = 6.65625; ///< alpha energy branching ratio = 85.2 / 12.8 = 6.65625;
double FxTwoAlpha(Double_t *xy, Double_t *par);
void Convert2APParameters(double* par, double &mean1, double &sigma1, double &amplitude1, double &mean2, double &sigma2, double &amplitude2);

void twopeak(TString input = "data/sim_alpha1.root", TString input2 = "data/sim_alpha2.root")
{
    TChain *tree = new TChain("energySum");
    tree -> Add(input);
    //tree -> Add(input2);

    auto histEnergySum = new TH1D("histEnergySum","energy sum",200,4,6);
    auto histEnergySum2 = new TH1D("histEnergySum2","energy sum",200,4,6);
    tree -> Project("histEnergySum","energyFull");
    tree -> Project("histEnergySum2","energyFull");

    auto cvs = new TCanvas("cvs1","",1300,600);
    cvs -> Divide(2,1);

    cvs -> cd(1);
    histEnergySum -> Draw();
    auto fit = new TF1("fit","gaus(0)",0,6);
    fit -> SetNpx(1000);
    histEnergySum -> Fit(fit);

    cvs -> cd(2);
    histEnergySum2 -> Draw();
    auto fit2 = new TF1("fit2",FxTwoAlpha,0,6,4);
    fit2 -> SetNpx(1000);
    fit2 -> SetParameters(0,0.018,5.5,10000);
    histEnergySum2 -> Fit(fit2);

    auto fit_peak1 = new TF1("fit_peak1","gaus(0)",0,6);
    auto fit_peak2 = new TF1("fit_peak2","gaus(0)",0,6);
    fit_peak1 -> SetLineColor(kBlue);
    fit_peak2 -> SetLineColor(kGreen+1);
    auto parameters = fit2 -> GetParameters();
    double amplitude1, mean1, sigma1;
    double amplitude2, mean2, sigma2;
    Convert2APParameters(parameters, mean1, sigma1, amplitude1, mean2, sigma2, amplitude2);
    fit_peak1 -> SetParameters(amplitude1, mean1, sigma1);
    fit_peak2 -> SetParameters(amplitude2, mean2, sigma2);
    fit_peak1 -> Draw("samel");
    fit_peak2 -> Draw("samel");

    cout << "resolution: " << parameters[1] << endl;
}

double FxTwoAlpha(Double_t *xy, Double_t *par)
{
    double x = xy[0];

    double ADCOffset = par[0];
    double energyResolution = par[1];

    double mean1 = par[2]; // ADC mean of 5.486 MeV peak
    double meanP1 = mean1 - ADCOffset; // pure ADC without ADC-offset
    double sigma1 = energyResolution * meanP1;
    double amplitude1 = par[3];

    double ADCEnergyRatio = meanP1 / fAlphaEnergy1;

    double mean2 = fAlphaEnergy2 * ADCEnergyRatio + ADCOffset;
    double meanP2 = mean2 - ADCOffset; // pure ADC without ADC-offset
    double sigma2 = energyResolution * meanP2;
    double amplitude2 = amplitude1 * sigma1 / fAEBR / sigma2;

    double value1 = amplitude1*exp(-0.5*((x-mean1)*(x-mean1)/sigma1/sigma1));
    double value2 = amplitude2*exp(-0.5*((x-mean2)*(x-mean2)/sigma2/sigma2));
    double value  = value1 + value2;

    return value;
}

void Convert2APParameters(double* par, double &mean1, double &sigma1, double &amplitude1, double &mean2, double &sigma2, double &amplitude2)
{
    double ADCOffset = par[0];
    double energyResolution = par[1];

    mean1 = par[2]; // ADC mean of 5.486 MeV peak
    double meanP1 = mean1 - ADCOffset; // pure ADC without ADC-offset
    sigma1 = energyResolution * meanP1;
    amplitude1 = par[3];

    double ADCEnergyRatio = meanP1 / fAlphaEnergy1;

    mean2 = fAlphaEnergy2 * ADCEnergyRatio + ADCOffset;
    double meanP2 = mean2 - ADCOffset; // pure ADC without ADC-offset
    sigma2 = energyResolution * meanP2;
    amplitude2 = amplitude1 * sigma1 / 6.65625 / sigma2; // 85.2 / 12.8 = 6.65625;
}
