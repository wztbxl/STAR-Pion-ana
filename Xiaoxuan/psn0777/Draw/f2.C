drawLatex(Double_t x, Double_t y, TString text, Int_t textFont, Double_t textSize, Int_t colorIndex){
  TLatex *latex = new TLatex(x,y,text);
 // latex->SetNDC();
  latex->SetTextFont(textFont);
  latex->SetTextSize(textSize);
  latex->SetTextColor(colorIndex);
  latex->Draw("same");
  return latex;
}

int Draw_BoxError( TGraphErrors* gr, double Box_width, int FillColor, int FillStyle)
{
  if ( !gr ) cout << "Wrong Graph!!!" << endl;
  for ( int i = 0; i < gr->GetN(); i++ )
  {
    double x1, y1, x2, y2;
    double x,y;
    double Error_y;
    gr->GetPoint(i,x,y);
    Error_y = gr->GetErrorY(i);
    x1 = x - Box_width;
    x2 = x + Box_width;
    y1 = y - Error_y;
    y2 = y + Error_y;

    TBox* box = new TBox(x1,y1,x2,y2);
    box->SetFillColorAlpha(FillColor,0.4);
    box->SetFillStyle(FillStyle);
    box->SetLineColor(FillColor);
    box->DrawClone("F");
  }

  return 1;
}


void f2(){

gStyle->SetOptTitle(0);
gStyle->SetPadGridX(0);
gStyle->SetPadGridY(0);
gStyle->SetEndErrorSize(8);
gStyle->SetOptDate(0);
TGaxis::SetMaxDigits(3);
gStyle->SetFrameLineWidth(1.5);
gStyle->SetOptFit(11111111);
gStyle->SetTextFont(42);
gStyle->SetLabelFont(42,"XY");
gStyle->SetLegendFont(42);
//double x[3] = {1,2,3};
double shift = 0.06;
double xlow[3] = {1.2-shift,1.7-shift,2.2-shift};
double xhigh[3] = {1.2,1.7,2.2};
double theory_x[3] = {1.2,1.7,2.2};

//area 
//low: pAl/pp
// high: pAu/pp
double Areaylow[3] = {0.824637,0.710071,0.733423};
double Areaylowe[3] = {0.0452007,0.0790675,0.155164};
double Areaylowse[3] = {0.0443094,0.107432,0.159707};

double Areayhigh[3] = {0.665278,0.713075,0.850371};
double Areayhighe[3] = {0.0217878,0.0406512,0.0926425};
double Areayhighse[3] = {0.0357467,0.107887,0.185173};

double ylowCombe[3] = {0,0,0};
double yhighCombe[3] = {0,0,0};

for(int i = 0; i<3;i++)
{
        ylowCombe[i] = sqrt(pow(Areaylow[i],2) + pow(Areaylowse[i],2));
        yhighCombe[i] = sqrt(pow(Areayhigh[i],2) + pow(Areayhighse[i],2));
}

//theory for b=0 pAu
double theory_y[3] = {0.441027,0.697957,0.711995};
double theory_ye[3] = {0.0367393,0.0559593,0.134389};

TGraphErrors *Areahigh = new TGraphErrors(3,xhigh,Areayhigh,0,Areayhighe);
TGraphErrors *Arealow = new TGraphErrors(3,xlow,Areaylow,0,Areaylowe);
TGraphErrors *Areahighs = new TGraphErrors(3,xhigh,Areayhigh,0,Areayhighse);
TGraphErrors *Arealows = new TGraphErrors(3,xlow,Areaylow,0,Areaylowse);
TGraphErrors *highEAComb = new TGraphErrors(3,xhigh,Areayhigh,0,yhighCombe);
TGraphErrors *lowEAComb = new TGraphErrors(3,xlow,Areaylow,0,ylowCombe);
TGraphErrors *theory = new TGraphErrors(3,theory_x,theory_y,0,theory_ye);

TCanvas *c = new TCanvas("c","c",430,900);
TPad *pad_1 = new TPad("pad_1", "pad_1", 0.00,0.69,1.0,1.00);
TPad *pad_2 = new TPad("pad_2", "pad_2", 0.0,0.38,1.0,0.69);
TPad *pad_3 = new TPad("pad_3", "pad_3", 0.0,0,1.0,0.38);
pad_1->SetMargin(0.16,0.005,0.00,0.005);
pad_2->SetMargin(0.16,0.005,0.00,0.000);
pad_3->SetMargin(0.16,0.005,0.19,0.000);
pad_1->Draw();
pad_2->Draw();
pad_3->Draw();

pad_1->cd();
TH2D *frame = new TH2D("frame",";p^{asso}_{T} [GeV/c];Relative area",3,0.9,2.45,1,0.35,1.44);
frame->GetYaxis()->SetTitleFont(42);
c->cd(1);
frame->GetXaxis()->SetLabelSize(0.04);
frame->GetYaxis()->SetLabelSize(0.08);
frame->GetYaxis()->SetTitleSize(0.08);
frame->GetXaxis()->SetTitleSize(0.04);
frame->GetXaxis()->SetTitleOffset(1.3);
frame->GetYaxis()->SetTitleOffset(0.71);
frame->GetXaxis()->SetNdivisions(405);
frame->GetYaxis()->SetNdivisions(405);
frame->SetStats(0);
frame->GetYaxis()->CenterTitle();
frame->GetXaxis()->CenterTitle();
frame->Draw();

Areahigh->SetMarkerSize(2.4);
Areahigh->SetMarkerStyle(29);
Areahigh->SetLineWidth(2);
Areahigh->SetLineColor(2);
Areahigh->SetMarkerColor(2);
Areahighs->SetFillStyle(3001);
Areahighs->SetFillColor(1);
Areahighs->SetLineWidth(2);

Arealow->SetMarkerSize(1.9);
Arealow->SetMarkerStyle(34);
Arealow->SetLineWidth(2);
Arealows->SetLineWidth(2);

theory->SetLineWidth(2.0);
theory->SetMarkerStyle(24);
theory->SetMarkerSize(1.5);
theory->SetMarkerColor(46);
theory->SetLineColor(46);
theory->SetFillColorAlpha(46,0.3);
theory->SetFillStyle(1001);

theory->Draw("le3");
Draw_BoxError(Areahighs,0.025,kRed-4,1001);
Draw_BoxError(Arealows,0.025,14,1001);
Arealow->Draw("PZsame");
Areahigh->Draw("PZsame");

//drawLatex(1.68,1.52,"STAR Preliminary",22,0.06,1);
double yy = 1.16+0.18;
drawLatex(0.98,yy-0.02,"#sqrt{s_{NN}} = 200 GeV",42,0.07,1);
drawLatex(0.99,yy-0.16,"NN #rightarrow #pi^{0}#pi^{0}X",42,0.07,1);
//drawLatex(0.95,yy-0.23,"2.6 < #eta < 4, #Delta#phi #in  [ #frac{#pi}{2} , #frac{3#pi}{2} ]",42,0.09,1);
//drawLatex(0.95,yy-0.31,"p_{T}^{trig} = 2.5-3 GeV/c",42,0.09,1);
drawLatex(2.22,yy+0.02,"STAR",22,0.07,1);
drawLatex(2.33,0.39,"(a)",42,0.07,1);
//sigma
// low: pAl/pp
// high: pAu/pp
double ylow[3] = {1.04823,1.08069,1.08376};
double ylowe[3] = {0.0462659, 0.0940302, 0.163922};
double ylowse[3] = {0.000592881, 0.0565394, 0.168567};

double yhigh[3] = {1.0195,0.994461,0.962517 };
double yhighe[3] = {0.026911,0.0491966,0.0940773};
double yhighse[3] = {0.00576629,0.0520282,0.14971};

double ylowCombe[3] = {0,0,0};
double yhighCombe[3] = {0,0,0};
for(int i = 0; i<3;i++)
{
	ylowCombe[i] = sqrt(pow(ylow[i],2) + pow(ylowse[i],2));
	yhighCombe[i] = sqrt(pow(yhigh[i],2) + pow(yhighse[i],2));
}


TGraphErrors *highEA = new TGraphErrors(3,xhigh,yhigh,0,yhighe);
TGraphErrors *lowEA = new TGraphErrors(3,xlow,ylow,0,ylowe);
TGraphErrors *highEAs = new TGraphErrors(3,xhigh,yhigh,0,yhighse);
TGraphErrors *lowEAs = new TGraphErrors(3,xlow,ylow,0,ylowse);
TGraphErrors *highEAComb = new TGraphErrors(3,xhigh,yhigh,0,yhighCombe);
TGraphErrors *lowEAComb = new TGraphErrors(3,xlow,ylow,0,ylowCombe);

TH2D *framea = new TH2D("framea",";p^{asso}_{T} [GeV/c];Relative width",3,0.9,2.45,1,0.55,1.84);
framea->GetYaxis()->SetTitleFont(42);
pad_2->cd();
c->cd(2);
framea->GetXaxis()->SetLabelSize(0.03);
framea->GetYaxis()->SetLabelSize(0.08);
framea->GetYaxis()->SetTitleSize(0.08);
framea->GetXaxis()->SetTitleSize(0.04);
framea->GetXaxis()->SetTitleOffset(1.3);
framea->GetYaxis()->SetTitleOffset(0.69);
framea->GetXaxis()->SetNdivisions(405);
framea->GetYaxis()->SetNdivisions(405);
framea->SetStats(0);
framea->GetYaxis()->CenterTitle();
framea->GetXaxis()->CenterTitle();
framea->Draw();

highEA->SetMarkerSize(2.4);
highEA->SetMarkerStyle(29);
highEA->SetLineWidth(2);
highEA->SetLineColor(2);
highEA->SetMarkerColor(2);
highEAs->SetFillStyle(3001);
highEAs->SetFillColor(1);
highEAs->SetLineWidth(2);

lowEA->SetMarkerSize(1.9);
lowEA->SetMarkerStyle(34);
lowEA->SetLineWidth(2);
lowEAs->SetLineWidth(2);

Draw_BoxError(highEAs,0.025,kRed-4,1001);
Draw_BoxError(lowEAs,0.025,14,1001);
lowEA->Draw("PZsame");
highEA->Draw("PZsame");

TLegend *sleg = new TLegend(0.20,0.7,0.85,0.96);
sleg->SetNColumns(2);
sleg->SetHeader("MinBias data, p_{T}^{trig} = 2.5-3 GeV/c");
sleg->AddEntry(lowEA,"pAl/pp","p");
sleg->AddEntry(highEA,"pAu/pp","P");
sleg->SetBorderSize(0);
sleg->SetFillStyle(0);
sleg->SetTextSize(0.07);
sleg->SetFillColorAlpha( kWhite, 0);
sleg->Draw("same");

drawLatex(2.33,0.61,"(b)",42,0.07,1);

//pedestal
//low pAl/pp
//high pAu/pp
double slow[3] = {0.875103,0.944363,1.0646};
cout<<"pAl low pT width how far from 1 :"<<(1-0.875103)/sqrt(pow(0.0160909,2)+pow(0.0383593,2))<<endl;
double slowe[3] = {0.0160909,0.0391258,0.0701045};
double slowse[3] = {0.0383593,0.116174,0.245372};

double shigh[3] = {0.835441,0.997642,1.09375 };
cout<<"pAu low pT width how far from 1 :"<<(1-0.835441)/sqrt(pow(0.00857672,2)+pow(0.0366207,2))<<endl;
double shighe[3] = {0.00857672,0.022433,0.0430363};
double shighse[3] = {0.0366207,0.122728,0.25209};

TGraphErrors *highEA = new TGraphErrors(3,xhigh,yhigh,0,yhighe);
TGraphErrors *lowEA = new TGraphErrors(3,xlow,ylow,0,ylowe);
TGraphErrors *highEAs = new TGraphErrors(3,xhigh,yhigh,0,yhighse);
TGraphErrors *lowEAs = new TGraphErrors(3,xlow,ylow,0,ylowse);

TGraphErrors *shighEA = new TGraphErrors(3,xhigh,shigh,0,shighe);
TGraphErrors *slowEA = new TGraphErrors(3,xlow,slow,0,slowe);
TGraphErrors *shighEAs = new TGraphErrors(3,xhigh,shigh,0,shighse);
TGraphErrors *slowEAs = new TGraphErrors(3,xlow,slow,0,slowse);
TH2D *sframe = new TH2D("sframe",";p^{asso}_{T} [GeV/c];Relative pedestal",3,0.9,2.45,1,0.4,1.96);
sframe->GetXaxis()->SetTitleFont(42);
sframe->GetYaxis()->SetTitleFont(42);
pad_3->cd();
sframe->GetXaxis()->SetLabelSize(0.06);
sframe->GetYaxis()->SetLabelSize(0.06);
sframe->GetYaxis()->SetTitleSize(0.065);
sframe->GetXaxis()->SetTitleSize(0.06);
sframe->GetXaxis()->SetTitleOffset(1.1);
sframe->GetYaxis()->SetTitleOffset(0.83);
sframe->GetXaxis()->SetNdivisions(405);
sframe->GetYaxis()->SetNdivisions(405);
sframe->SetStats(0);
sframe->GetYaxis()->CenterTitle();
sframe->GetXaxis()->CenterTitle();
//sframe->Draw("y+");
sframe->Draw();

shighEA->SetMarkerSize(2.4);
shighEA->SetMarkerStyle(29);
shighEA->SetLineWidth(2);
shighEA->SetLineColor(2);
shighEA->SetMarkerColor(2);
shighEAs->SetFillStyle(3001);
shighEAs->SetFillColor(1);
shighEAs->SetLineWidth(2);

slowEA->SetMarkerSize(1.9);
slowEA->SetMarkerStyle(34);
slowEA->SetLineWidth(2);
slowEAs->SetLineWidth(2);

Draw_BoxError(shighEAs,0.025,kRed-4,1001);
Draw_BoxError(slowEAs,0.025,14,1001);
slowEA->Draw("PZsame");
shighEA->Draw("PZsame");

/*
ofstream fout("HepData/f2_theory_highEA.yaml");
fout<<"independent_variables:"<<endl;
fout<<"- header: {name:p^asso_T}"<<endl;
fout<<"  values: "<<endl;
for(int i = 0; i<theory->GetN();i++){
fout<<" - value: "<<theory->GetX()[i]<<endl;
}
fout<<"dependent_variables:"<<endl;
fout<<"- header: {name: Relative area}"<<endl;
fout<<"  values:"<<endl;
for(int i = 0; i<theory->GetN();i++){
fout<<"  - value: "<<theory->GetY()[i]<<endl;
fout<<"    errors:"<<endl;
fout<<"    - {staterror: "<<theory->GetErrorY(i)<<", label: stat}"<<endl;
}
*/

drawLatex(0.95,1.75,"2.6 < #eta < 4, #Delta#phi #in  [ #frac{#pi}{2} , #frac{3#pi}{2} ]",42,0.055,1);
TLegend *ssleg = new TLegend(0.17,0.76,0.67,0.86);
ssleg->AddEntry(theory,"pAu/pp: rcBK,","l");
ssleg->SetBorderSize(0);
ssleg->SetFillStyle(0);
ssleg->SetTextSize(0.055);
ssleg->SetFillColorAlpha( kWhite, 0);
ssleg->Draw("same");
drawLatex(1.63,1.54,"b",52,0.055,1);
drawLatex(1.68,1.54,"=0",42,0.055,1);
drawLatex(2.33,0.48,"(c)",42,0.058,1);

c->SaveAs("f2.pdf");
}
