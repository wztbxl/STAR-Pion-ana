TLatex* drawLatex(Double_t x, Double_t y, TString text, Int_t textFont, Double_t textSize, Int_t colorIndex){
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
  for ( int i = 1; i < gr->GetN(); i++ )
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


void f4(){

gStyle->SetOptTitle(0);
gStyle->SetPadGridX(0);
gStyle->SetPadGridY(0);
gStyle->SetEndErrorSize(8);
gStyle->SetOptDate(0);
TGaxis::SetMaxDigits(3);
gStyle->SetFrameLineWidth(1.5);
gStyle->SetOptFit(11111111);
gStyle->SetTitleFont(42,"XY");
gStyle->SetTextFont(42);
gStyle->SetLabelFont(42,"XY");

//x measn pT bins, A of proton, Al and Au
double x[3] = {1,3,pow(197,1./3.)};
double shift = 0.5;
double xhigh [3] = {1-shift,3-shift,pow(197,1./3.)-shift};
//y is the yileds in pp, pAl, pAu; low mean low pT bin, high means high pT bin
double ylow[3] = {0.00451,0.00384,0.00257};
double ylowe[3] = {0.00015,0.00028,0.00008};
double yhigh[3] = {0.00023,0.00029,0.00018};
double yhighe[3] = {0.00002,0.00009,0.00002};
//sys error
double ylowse[3] = {0.00451*0.02,0.00384*0.02,0.00257*0.02};
double yhighse[3] = {0.00023*0.186,0.00029*0.186,0.00018*0.186};

//we need to use the yields ratio: pp/pp, pAl/pp, pAu/pp
//ratio
double lowratio[3] = {1., 0.00384./0.00451, 0.00257/0.00451};
double highratio[3] = {1., 0.00029./0.00023, 0.00018/0.00023};
//ratio's stat error, there is no stat error for pp/pp
double lowratioe[3] = {0.0, sqrt(pow(0.00015/0.00451,2) + pow(0.00028/0.00384,2)), sqrt(pow(0.00015/0.00451,2) + pow(0.00008/0.00257,2))};
double highratioe[3] = {sqrt(pow((0.00002/0.00023),2)*2), sqrt(pow((0.00002/0.00023),2) + pow((0.00009/0.00029),2)), sqrt(pow((0.00002/0.00023),2) + pow((0.00002/0.00018),2))};
//ratio's sys error, there is no sys error for pp/pp
double lowratiose[3] = {0.00, 0.00384./0.00451*1.414*0.02, 0.00257/0.00451*1.414*0.02};
double highratiose[3] = {1*0.186*1.414, 0.00029./0.00023*0.186*1.414, 0.00018/0.00023*0.186*1.414};
//combin stat and sys error
double ylowCombe[3] = {0,0,0};
double yhighCombe[3] = {0,0,0};
for(int i = 0; i<3;i++)// for pAu/pp and pAl/pp
{
	ylowCombe[i] = sqrt(pow(lowratioe[i],2) + pow(lowratiose[i],2));
	yhighCombe[i] = sqrt(pow(highratioe[i],2) + pow(highratiose[i],2));
}


TGraphErrors *highPt = new TGraphErrors(3,x,highratio,0,highratioe);
TGraphErrors *lowPt = new TGraphErrors(3,x,lowratio,0,lowratioe);
TGraphErrors *highPts = new TGraphErrors(3,x,highratio,0,highratiose);
TGraphErrors *lowPts = new TGraphErrors(3,x,lowratio,0,lowratiose);

TGraphErrors *highPtComb = new TGraphErrors(3,x,highratio,0,yhighCombe);
TGraphErrors *lowPtComb = new TGraphErrors(3,x,lowratio,0,ylowCombe);

TCanvas *c = new TCanvas("c","c",400,400);
c->SetMargin(0.14,0.01,0.15,0.04);
TH2D *frame = new TH2D("frame",";A^{1/3};Relative area",3,0.2,6.5,1,0.2,1.5);
frame->GetXaxis()->SetLabelSize(0.0);
frame->GetYaxis()->SetLabelSize(0.06);
frame->GetYaxis()->SetTitleSize(0.06);
frame->GetXaxis()->SetTitleSize(0.07);
frame->GetXaxis()->SetTitleOffset(0.95);
frame->GetYaxis()->SetTitleOffset(1.2);
frame->GetXaxis()->SetNdivisions(405);
frame->GetYaxis()->SetNdivisions(405);
frame->SetStats(0);
frame->GetYaxis()->CenterTitle();
frame->GetXaxis()->CenterTitle();
frame->Draw();

TF1 *f1 = new TF1("f1", "[0]*(x-1)+1",0.6,6.4); 
TF1 *f2 = new TF1("f2", "pol1",0.6,6.4);
lowPtComb->Fit("f1","ER");
f1->SetLineWidth(3);
f1->SetLineStyle(5);
f1->Draw("same");

double p1 = f1->GetParameter(0);
double sigma = f1->GetParError(0);
cout<<f1->GetChisquare()<<" "<<f1->GetNDF()<<endl;
double chi = f1->GetChisquare()/(f1->GetNDF());

highPt->SetMarkerSize(2);
highPt->SetMarkerStyle(24);
highPt->SetLineWidth(2);
highPts->SetFillStyle(3001);
highPts->SetFillColor(1);
highPts->SetLineWidth(2);

lowPt->SetMarkerSize(2.5);
lowPt->SetMarkerStyle(29);
lowPt->SetMarkerColor(2);
lowPt->SetLineColor(2);
lowPt->SetLineWidth(3);
lowPts->SetMarkerColor(2);
lowPts->SetLineColor(2);
lowPts->SetLineWidth(2);


//highPt->SetPointError(0,0,0);
//Draw_BoxError(highPts, 0.25,15,1001);
//highPt->Draw("PZsame");
Draw_BoxError(lowPts, 0.25,kRed,1001);
lowPt->Draw("PZsame");

TLegend *leg = new TLegend(0.42,0.66,0.94,0.83);
//leg->AddEntry(lowPt,"p_{T}^{trig}=1.5-2 GeV, p_{T}^{asso}=1-1.5 GeV","p");
//leg->AddEntry(highPt,"p_{T}^{trig}=3.0-5 GeV, p_{T}^{asso}=2-2.5 GeV","p");
leg->AddEntry(lowPt,"p_{T}^{trig}=1.5-2 GeV/c, p_{T}^{asso}=1-1.5 GeV/c","p");
leg->AddEntry(highPt,"p_{T}^{trig}=3-5, p_{T}^{asso}=2-2.5 GeV/c","P");
leg->SetBorderSize(0);
leg->SetTextSize(0.05);
leg->SetFillColorAlpha( kWhite, 0);
//leg->Draw("same");

drawLatex(0.38,1.4,"STAR",22,0.06,1);
drawLatex(2.1,1.4,"#sqrt{s_{NN}} = 200 GeV, NN #rightarrow #pi^{0}#pi^{0}X",42,0.05,1);
drawLatex(2.56,1.27,"2.6 < #eta < 4, #Delta#phi #in  [ #frac{#pi}{2} , #frac{3#pi}{2} ]",42,0.05,1);
drawLatex(3.88,1.14,"p_{T}^{trig}=1.5-2 GeV/c",42,0.05,1);
drawLatex(3.72,1.01,"p_{T}^{asso}=1-1.5 GeV/c",42,0.05,1);
drawLatex(4.08,0.89,Form("P= %1.2f #pm %1.2f",p1,sigma),42,0.05,1);
//drawLatex(4.14,0.85,Form("#chi^{2}/NDF = %1.2f",chi),62,0.05,1);
drawLatex(0.87,0.28,"p",42,0.07,1);
drawLatex(2.75,0.28,"Al",42,0.07,1);
drawLatex(5.52,0.28,"Au",42,0.07,1);
drawLatex(0.92,0.12,"1",42,0.06,1);
drawLatex(2.92,0.12,"3",42,0.06,1);
drawLatex(4.92,0.12,"5",42,0.06,1);
c->SaveAs("f4.pdf");
}
