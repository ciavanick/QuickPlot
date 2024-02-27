void quickplot(Double_t thresholddown, Double_t thresholdup, TString path)
{
    // Creating the graph
    TGraph *g1 = new TGraph(path, "%lg %lg", "\t");

    // Extracting the path
    Int_t dot = path.First('.');
    Int_t len = path.Length();
    path.Remove(dot, len - dot);

    // Cosmetic
    g1->SetTitle(path + ";time (s);Voltage (V)");
    g1->SetMarkerStyle(8);
    g1->SetMarkerColor(kBlack);
    g1->SetMarkerSize(.4);
    g1->SetLineStyle(1);
    g1->SetLineWidth(1.);

    // Extracting the last point
    Int_t N = g1->GetN();
    Double_t lastpoint = N - 1.;
    Double_t x, y;
    g1->GetPoint(lastpoint, x, y);

    // Extracting the first point
    Double_t firstpoint = 0.;
    Double_t x_0, y_0;
    g1->GetPoint(firstpoint, x_0, y_0);

    // Upper threshold
    TLine *lineup = new TLine(x_0, thresholdup, x, thresholdup);
    lineup->SetLineColor(kRed + 2);
    lineup->SetLineStyle(2);

    // Lower threshold
    TLine *linedown = new TLine(x_0, thresholddown, x, thresholddown);
    linedown->SetLineColor(kBlue + 2);
    linedown->SetLineStyle(2);

    // Legend
    TLegend *leg1 = new TLegend(0.75, 0.85, 0.95, .95);
    leg1->AddEntry(g1, "Experimental Data");
    leg1->AddEntry(lineup, "V_{HIGH}", "l");
    leg1->AddEntry(linedown, "V_{LOW}", "l");

    // Plotting and saving
    TCanvas *c1 = new TCanvas("c1", "c1");
    g1->Draw();
    lineup->Draw("SAME");
    linedown->Draw("SAME");
    leg1->Draw("SAME");
    c1->Print("Result/" + path + ".png");
    c1->Print("Result/" + path + ".pdf");

    TFile *f = new TFile("Result/" + path + ".root", "recreate");
    g1->Write();
    f->Close();
}
void quickplot(Double_t x_min, Double_t x_max, Double_t thresholddown, Double_t thresholdup, TString path)
{
    // Setting gStyle legend
    gStyle->SetOptFit(0010);
    gStyle->SetStatX(0.9);
    gStyle->SetStatY(0.95);
    gStyle->SetStatW(0.15);
    gStyle->SetStatH(0.05);

    // Creating the graph
    TGraph *g1 = new TGraph(path, "%lg %lg", "\t");

    // Extracting the path
    Int_t dot = path.First('.');
    Int_t len = path.Length();
    path.Remove(dot, len - dot);

    // Cosmetic
    g1->SetTitle(path + ";time (s);Voltage (V)");
    g1->SetMarkerStyle(8);
    g1->SetMarkerColor(kBlack);
    g1->SetMarkerSize(.4);
    g1->SetLineStyle(1);
    g1->SetLineWidth(1.);

    // Fit function
    TF1 *f_exp1 = new TF1("f_exp1", "[0]*e^(-(x-[1])/[2])+[3]", x_min, x_max);
    f_exp1->SetTitle("Voltage vs time; time (s); Voltage (V)");
    f_exp1->SetParNames("A (V)", "t_{0} (s)", "T (s)", "V_{0} (V)");
    f_exp1->SetParameters(0.5, x_min, 10, 2.5);
    f_exp1->FixParameter(1, x_min);

    // Fit
    g1->Fit("f_exp1", "S", "", x_min, x_max);

    // Extracting the last point
    Int_t N = g1->GetN();
    Double_t lastpoint = N - 1.;
    Double_t x, y;
    g1->GetPoint(lastpoint, x, y);

    // Extracting the first point
    Double_t firstpoint = 0.;
    Double_t x_0, y_0;
    g1->GetPoint(firstpoint, x_0, y_0);

    // Upper threshold
    TLine *lineup = new TLine(x_0, thresholdup, x, thresholdup);
    lineup->SetLineColor(kRed + 2);
    lineup->SetLineStyle(2);

    // Lower threshold
    TLine *linedown = new TLine(x_0, thresholddown, x, thresholddown);
    linedown->SetLineColor(kBlue + 2);
    linedown->SetLineStyle(2);

    // Legend
    TLegend *leg1 = new TLegend(0.63, 0.65, 0.9, .78);
    leg1->AddEntry(g1, "Experimental Data");
    leg1->AddEntry(f_exp1, "Fit V = Ae^{-t/T}+V_{0}");
    leg1->AddEntry(lineup, "V_{HIGH}", "l");
    leg1->AddEntry(linedown, "V_{LOW}", "l");

    // Plotting and saving
    TCanvas *c1 = new TCanvas("c1", "c1");
    g1->Draw();
    lineup->Draw("SAME");
    linedown->Draw("SAME");
    leg1->Draw("SAME");
    c1->Print("Result/" + path + ".png");
    c1->Print("Result/" + path + ".pdf");

    TFile *f = new TFile("Result/" + path + ".root", "recreate");
    g1->Write();
    f->Close();
}