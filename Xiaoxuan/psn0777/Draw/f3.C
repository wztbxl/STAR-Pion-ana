static const double PI=TMath::Pi();
static const double twoPI=PI*2.0;
static const int kNPtBin=6;
static const int kNCut=26;

float PAR0[kNPtBin][kNPtBin][kNCut][3];
float PAR1[kNPtBin][kNPtBin][kNCut][3];
float PAR2[kNPtBin][kNPtBin][kNCut][3];
float ERR0[kNPtBin][kNPtBin][kNCut][3];
float ERR1[kNPtBin][kNPtBin][kNCut][3];
float ERR2[kNPtBin][kNPtBin][kNCut][3];
float CHI[kNPtBin][kNPtBin][kNCut][3];

TLatex* drawLatex(Double_t x, Double_t y, TString text, Int_t textFont, Double_t textSize, Int_t colorIndex){
  TLatex *latex = new TLatex(x,y,text);
  latex->SetNDC();
  latex->SetTextFont(textFont);
  latex->SetTextSize(textSize);
  latex->SetTextColor(colorIndex);
  latex->Draw("same");
  return latex;
}

TLatex* drawTof(Double_t x, Double_t y, TString text, Int_t textFont, Double_t textSize, Int_t colorIndex){
  TLatex *latex = new TLatex(x,y,text);
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
  

void readpar(int beam, int cut, int corr, int print=0){
    char name[200];
    sprintf(name,"./txt/beam%d_cut%d_corr%d.par",beam,cut,corr);
    if(print>0) printf("Reading %s\n",name);
    FILE* f=fopen(name,"r");
    for(int i=1;i<kNPtBin; i++){
        for(int j=1; j<i; j++){
            fscanf(f,"%f %f %f %f %f %f %f\n",
                   &(PAR0[i][j][cut][beam]),&(PAR1[i][j][cut][beam]),&(PAR2[i][j][cut][beam]),
                   &(ERR0[i][j][cut][beam]),&(ERR1[i][j][cut][beam]),&(ERR2[i][j][cut][beam]),&(CHI[i][j][cut][beam]));
            if(i>0 && j>0 && print==1)
                printf("%1d %d %1d %1d %10.6f %10.6f %10.6f %10.6f %10.6f %10.6f %10.6f %d\n",
                       beam,cut,i,j,
                       PAR0[i][j][cut][beam],PAR1[i][j][cut][beam],PAR2[i][j][cut][beam],
                       ERR0[i][j][cut][beam],ERR1[i][j][cut][beam],ERR2[i][j][cut][beam],CHI[i][j][cut][beam]);
                       }
		}
	fclose(f);
}


Double_t oneGaus(Double_t *x, Double_t *par){
    Double_t OP=1.0/sqrt(2.0*PI);
    Double_t x1 = x[0]+PI;
    while(x1<-PI) x1+=2.0*PI;
    while(x1>=PI) x1-=2.0*PI;
    Double_t f = par[0]/2.0/PI;
    f += par[1]*OP/par[2]*exp(-x1*x1/2.0/par[2]/par[2]);
    return f;
}

Double_t ratioerr(Double_t a, Double_t aerr,Double_t b,Double_t berr){
     Double_t e = a/b * sqrt(pow(aerr/a,2)+pow(berr/b,2));
     return e;
}

void f3()
{
	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);
	gStyle->SetOptDate(0);
	gStyle->SetPadGridX(0);
	gStyle->SetPadGridY(0);
	gStyle->SetEndErrorSize(10);
	gStyle->SetTitleFont(42,"XY");
gStyle->SetTextFont(42);
gStyle->SetLabelFont(42,"XY");
gStyle->SetLegendFont(42);
int BBC[4]= {7300.,18000,30000,43500};
//int BBCpAl[3]= {6000,12300,22800};
int BBCpAl[3]= {5245. ,11100.,22800.};
int shift = 0;
//Data
	memset(PAR0,0,sizeof(PAR0));
	memset(PAR1,0,sizeof(PAR1));
	memset(PAR2,0,sizeof(PAR2));
	memset(ERR0,0,sizeof(ERR0));
	memset(ERR0,0,sizeof(ERR0));
        memset(ERR1,0,sizeof(ERR1));
        memset(ERR2,0,sizeof(ERR2));

	readpar(0,2,1,1);//pp MiniBais
	readpar(3,4,1,1);//pAu 3000<BBCE<12000
	readpar(3,5,1,1);//pAu 12000<BBCE<24000
        readpar(3,15,1,1);//pAu 24000<BBCE<36000
	readpar(3,16,1,1);//pAu 36000<BBCE
	readpar(3,2,1,1);//pAu MiniBias
	readpar(1,4,1,1);//pAl 3000<BBCE<10000
	readpar(1,5,1,1);//pAl 10000<BBCE<15000
	readpar(1,15,1,1);//pAl 15000<BBCE
        //readpar(1,16,1,1);//pAl very large BBCE, not used

        //calculate ratio pAu/pp, and error
	double RAT1_4[kNPtBin][kNPtBin],RAT1_5[kNPtBin][kNPtBin],RAT1_16[kNPtBin][kNPtBin],RAT1_15[kNPtBin][kNPtBin];
	double ERROR1_4[kNPtBin][kNPtBin],ERROR1_5[kNPtBin][kNPtBin],ERROR1_16[kNPtBin][kNPtBin],ERROR1_15[kNPtBin][kNPtBin], ERROR1_2[kNPtBin][kNPtBin];

	//calculate ratio pAl/pp, and error
	double RATpAl1_4[kNPtBin][kNPtBin],RATpAl1_5[kNPtBin][kNPtBin],RATpAl1_16[kNPtBin][kNPtBin],RATpAl1_15[kNPtBin][kNPtBin];
	double ERRORpAl1_4[kNPtBin][kNPtBin],ERRORpAl1_5[kNPtBin][kNPtBin],ERRORpAl1_16[kNPtBin][kNPtBin],ERRORpAl1_15[kNPtBin][kNPtBin];

	//MiniBias
	double RAT1_2[kNPtBin][kNPtBin], ERROR1_2[kNPtBin][kNPtBin];

        for(int i=1;i<kNPtBin; i++){
		for(int j=1; j<i; j++){
			//ratio
			RAT1_4[i][j] = PAR1[i][j][4][3]/PAR1[i][j][2][0];
			RAT1_5[i][j]= PAR1[i][j][5][3]/PAR1[i][j][2][0];
			RAT1_15[i][j]= PAR1[i][j][15][3]/PAR1[i][j][2][0];
			RAT1_16[i][j] = PAR1[i][j][16][3]/PAR1[i][j][2][0];
			RATpAl1_4[i][j] = PAR1[i][j][4][1]/PAR1[i][j][2][0];
			RATpAl1_5[i][j]= PAR1[i][j][5][1]/PAR1[i][j][2][0];
			RATpAl1_15[i][j]= PAR1[i][j][15][1]/PAR1[i][j][2][0];
			RATpAl1_16[i][j] = PAR1[i][j][16][1]/PAR1[i][j][2][0];
			RAT1_2[i][j] = PAR1[i][j][2][3]/PAR1[i][j][2][0];

			//statistic error
			ERROR1_4[i][j] = RAT1_4[i][j]*sqrt(pow(ERR1[i][j][4][3],2)/pow(PAR1[i][j][4][3],2)+pow(ERR1[i][j][2][0],2)/pow(PAR1[i][j][2][0],2));
			ERROR1_5[i][j] = RAT1_5[i][j]*sqrt(pow(ERR1[i][j][5][3],2)/pow(PAR1[i][j][5][3],2)+pow(ERR1[i][j][2][0],2)/pow(PAR1[i][j][2][0],2));
			ERROR1_15[i][j] = RAT1_15[i][j]*sqrt(pow(ERR1[i][j][15][3],2)/pow(PAR1[i][j][15][3],2)+pow(ERR1[i][j][2][0],2)/pow(PAR1[i][j][2][0],2));
			ERROR1_16[i][j] = RAT1_16[i][j]*sqrt(pow(ERR1[i][j][16][3],2)/pow(PAR1[i][j][16][3],2)+pow(ERR1[i][j][2][0],2)/pow(PAR1[i][j][2][0],2));

			ERRORpAl1_4[i][j] = RATpAl1_4[i][j]*sqrt(pow(ERR1[i][j][4][1],2)/pow(PAR1[i][j][4][1],2)+pow(ERR1[i][j][2][0],2)/pow(PAR1[i][j][2][0],2));
			ERRORpAl1_5[i][j] = RATpAl1_5[i][j]*sqrt(pow(ERR1[i][j][5][1],2)/pow(PAR1[i][j][5][1],2)+pow(ERR1[i][j][2][0],2)/pow(PAR1[i][j][2][0],2));
			ERRORpAl1_15[i][j] = RATpAl1_15[i][j]*sqrt(pow(ERR1[i][j][15][1],2)/pow(PAR1[i][j][15][1],2)+pow(ERR1[i][j][2][0],2)/pow(PAR1[i][j][2][0],2));
			ERRORpAl1_16[i][j] = RATpAl1_16[i][j]*sqrt(pow(ERR1[i][j][16][1],2)/pow(PAR1[i][j][16][1],2)+pow(ERR1[i][j][2][0],2)/pow(PAR1[i][j][2][0],2));


			ERROR1_2[i][j] = RAT1_2[i][j]*sqrt(pow(ERR1[i][j][2][3],2)/pow(PAR1[i][j][2][3],2)+pow(ERR1[i][j][2][0],2)/pow(PAR1[i][j][2][0],2));
		}
	}
	//sys error divided by content
        double sys21 = 0.02*1.414, sys31 = 0.019*1.414, sys41 = 0.038*1.414, sys51 = 0.054*1.414;
        double sys32 = 0.06*1.414, sys42 = 0.107*1.414, sys52 = 0.127*1.414;
        double sys53 = 0.186*1.414;
	TGraphErrors* g21 = new TGraphErrors();
	g21->SetPoint(0, BBC[0]-shift,RAT1_4[2][1]);
	g21->SetPoint(1, BBC[1]-shift,RAT1_5[2][1]);
	g21->SetPoint(2, BBC[2]-shift,RAT1_15[2][1]);
	g21->SetPoint(3, BBC[3]-shift,RAT1_16[2][1]);
	//g21->SetPoint(4, BBC[4]-shift,RAT1_2[2][1]);
	//stat error
	g21->SetPointError(0, 0.0,ERROR1_4[2][1]);
	g21->SetPointError(1, 0.0,ERROR1_5[2][1]);
	g21->SetPointError(2, 0.0,ERROR1_15[2][1]);
	g21->SetPointError(3, 0.0,ERROR1_16[2][1]);
        g21->Draw();
	//g21->SetPointError(4, 0.0,ERROR1_2[2][1]);
        TGraphErrors* g21s = new TGraphErrors();
	g21s->SetPoint(0, BBC[0]-shift*1,RAT1_4[2][1]);
	g21s->SetPoint(1, BBC[1]-shift*1,RAT1_5[2][1]);
	g21s->SetPoint(2, BBC[2]-shift*1,RAT1_15[2][1]);
	g21s->SetPoint(3, BBC[3]-shift*1,RAT1_16[2][1]);
double lowsigma = sqrt(ERROR1_4[2][1]*ERROR1_4[2][1]+sys21*RAT1_4[2][1]*sys21*RAT1_4[2][1]);
double highsigma = sqrt(ERROR1_16[2][1]*ERROR1_16[2][1]+sys21*RAT1_16[2][1]*sys21*RAT1_16[2][1]);
cout<<"ERROR1_4[2][1] "<<ERROR1_4[2][1]<<endl;
cout<<"sys21*RAT1_4[2][1] "<<sys21*RAT1_4[2][1]<<endl;
cout<<"lowsigma "<<lowsigma<<endl;
double sig = sqrt(lowsigma*lowsigma+highsigma*highsigma);
cout<<"sig "<<sig<<endl;
cout<<(RAT1_4[2][1]-RAT1_16[2][1])/sig<<endl;

	//pAl
	TGraphErrors* g21pAl = new TGraphErrors();
	g21pAl->SetPoint(0, BBCpAl[0]-shift,RATpAl1_4[2][1]);
	g21pAl->SetPoint(1, BBCpAl[1]-shift,RATpAl1_5[2][1]);
	g21pAl->SetPoint(2, BBCpAl[2]-shift,RATpAl1_15[2][1]);
	//g21pAl->SetPoint(3, BBCpAl[3]-shift,RATpAl1_16[2][1]);
	g21pAl->SetPointError(0, 0.0,ERRORpAl1_4[2][1]);
	g21pAl->SetPointError(1, 0.0,ERRORpAl1_5[2][1]);
	g21pAl->SetPointError(2, 0.0,ERRORpAl1_15[2][1]);
	//g21pAl->SetPointError(3, 0.0,ERRORpAl1_16[2][1]);
	TGraphErrors* g21pAls = new TGraphErrors();
	g21pAls->SetPoint(0, BBCpAl[0]-shift*1,RATpAl1_4[2][1]);
	g21pAls->SetPoint(1, BBCpAl[1]-shift*1,RATpAl1_5[2][1]);
	g21pAls->SetPoint(2, BBCpAl[2]-shift*1,RATpAl1_15[2][1]);
	//g21pAls->SetPoint(3, BBCpAl[3]-shift*1,RATpAl1_16[2][1]);
	g21pAls->SetPointError(0, 0.0,sys21*RATpAl1_4[2][1]);
	g21pAls->SetPointError(1, 0.0,sys21*RATpAl1_5[2][1]);
	g21pAls->SetPointError(2, 0.0,sys21*RATpAl1_15[2][1]);
	//g21pAls->SetPointError(3, 0.0,sys21*RATpAl1_16[2][1]);
	cout<<"RATpAl1_4 "<<RATpAl1_4[2][1]<<endl;
	cout<<"RATpAl1_5 "<<RATpAl1_5[2][1]<<endl;
	cout<<"RATpAl1_15 "<<RATpAl1_15[2][1]<<endl;
	cout<<"ERRORpAl1_4 "<<ERRORpAl1_4[2][1]<<endl;
	cout<<"ERRORpAl1_5 "<<ERRORpAl1_5[2][1]<<endl;
	cout<<"ERRORpAl1_15 "<<ERRORpAl1_15[2][1]<<endl;
	cout<<"sys21*RATpAl1_4 "<<sys21*RATpAl1_4[2][1]<<endl;
	cout<<"sys21*RATpAl1_5 "<<sys21*RATpAl1_5[2][1]<<endl;
	cout<<"sys21*RATpAl1_15 "<<sys21*RATpAl1_15[2][1]<<endl;
double lowsigma1 = sqrt(ERRORpAl1_4[2][1]*ERRORpAl1_4[2][1]+sys21*RATpAl1_4[2][1]*sys21*RATpAl1_4[2][1]);
double highsigma1 = sqrt(ERRORpAl1_15[2][1]*ERRORpAl1_15[2][1]+sys21*RATpAl1_15[2][1]*sys21*RATpAl1_15[2][1]);
cout<<"ERRORpAl1_4[2][1] "<<ERRORpAl1_4[2][1]<<endl;
cout<<"sys21*RATpAl1_4[2][1] "<<sys21*RATpAl1_4[2][1]<<endl;
cout<<"lowsigma1 "<<lowsigma1<<endl;
double sig1 = sqrt(lowsigma1*lowsigma1+highsigma1*highsigma1);
cout<<"sig1 "<<sig1<<endl;
cout<<(RATpAl1_4[2][1]-RATpAl1_15[2][1])/sig1<<endl;	
	//add sys error
	g21s->SetPointError(0, 0.0,sys21*RAT1_4[2][1]);
	g21s->SetPointError(1, 0.0,sys21*RAT1_5[2][1]);
	g21s->SetPointError(2, 0.0,sys21*RAT1_15[2][1]);
	g21s->SetPointError(3, 0.0,sys21*RAT1_16[2][1]);
	//g21s->SetPointError(4, 0.0,sys21*RAT1_2[2][1]);

	TGraphErrors* g31 = new TGraphErrors();
	g31->SetPoint(0, BBC[0],RAT1_4[3][1]);
	g31->SetPoint(1, BBC[1],RAT1_5[3][1]);
	g31->SetPoint(2, BBC[2],RAT1_15[3][1]);
	g31->SetPoint(3, BBC[3],RAT1_16[3][1]);
	g31->SetPointError(0, 0.0,ERROR1_4[3][1]);
	g31->SetPointError(1, 0.0,ERROR1_5[3][1]);
	g31->SetPointError(2, 0.0,ERROR1_15[3][1]);
	g31->SetPointError(3, 0.0,ERROR1_16[3][1]);
        TGraphErrors* g31s = new TGraphErrors();
	g31s->SetPoint(0, BBC[0],RAT1_4[3][1]);
	g31s->SetPoint(1, BBC[1],RAT1_5[3][1]);
	g31s->SetPoint(2, BBC[2],RAT1_15[3][1]);
	g31s->SetPoint(3, BBC[3],RAT1_16[3][1]);
	g31s->SetPointError(0, 0.0,sys31*RAT1_4[3][1]);
	g31s->SetPointError(1, 0.0,sys31*RAT1_5[3][1]);
	g31s->SetPointError(2, 0.0,sys31*RAT1_15[3][1]);
	g31s->SetPointError(3, 0.0,sys31*RAT1_16[3][1]);

	TGraphErrors* g31pAl = new TGraphErrors();
	g31pAl->SetPoint(0, BBCpAl[0],RATpAl1_4[3][1]);
	g31pAl->SetPoint(1, BBCpAl[1],RATpAl1_5[3][1]);
	g31pAl->SetPoint(2, BBCpAl[2],RATpAl1_15[3][1]);
	g31pAl->SetPoint(3, BBCpAl[3],RATpAl1_16[3][1]);
	g31pAl->SetPointError(0, 0.0,ERRORpAl1_4[3][1]);
	g31pAl->SetPointError(1, 0.0,ERRORpAl1_5[3][1]);
	g31pAl->SetPointError(2, 0.0,ERRORpAl1_15[3][1]);
	g31pAl->SetPointError(3, 0.0,ERRORpAl1_16[3][1]);
        TGraphErrors* g31pAls = new TGraphErrors();
	g31pAls->SetPoint(0, BBCpAl[0],RATpAl1_4[3][1]);
	g31pAls->SetPoint(1, BBCpAl[1],RATpAl1_5[3][1]);
	g31pAls->SetPoint(2, BBCpAl[2],RATpAl1_15[3][1]);
	g31pAls->SetPoint(3, BBCpAl[3],RATpAl1_16[3][1]);
	g31pAls->SetPointError(0, 0.0,sys31*RATpAl1_4[3][1]);
	g31pAls->SetPointError(1, 0.0,sys31*RATpAl1_5[3][1]);
	g31pAls->SetPointError(2, 0.0,sys31*RATpAl1_15[3][1]);
	g31pAls->SetPointError(3, 0.0,sys31*RATpAl1_16[3][1]);

	TGraphErrors* g41 = new TGraphErrors();
	g41->SetPoint(0, BBC[0]+shift,RAT1_4[4][1]);
	g41->SetPoint(1, BBC[1]+shift,RAT1_5[4][1]);
	g41->SetPoint(2, BBC[2]+shift,RAT1_15[4][1]);
	g41->SetPoint(3, BBC[3]+shift,RAT1_16[4][1]);
	g41->SetPointError(0, 0.0,ERROR1_4[4][1]);
	g41->SetPointError(1, 0.0,ERROR1_5[4][1]);
	g41->SetPointError(2, 0.0,ERROR1_15[4][1]);
	g41->SetPointError(3, 0.0,ERROR1_16[4][1]);
        TGraphErrors* g41s = new TGraphErrors();
	g41s->SetPoint(0, BBC[0]+shift,RAT1_4[4][1]);
	g41s->SetPoint(1, BBC[1]+shift,RAT1_5[4][1]);
	g41s->SetPoint(2, BBC[2]+shift,RAT1_15[4][1]);
	g41s->SetPoint(3, BBC[3]+shift,RAT1_16[4][1]);
	g41s->SetPointError(0, 0.0,sys41*RAT1_4[4][1]);
	g41s->SetPointError(1, 0.0,sys41*RAT1_5[4][1]);
	g41s->SetPointError(2, 0.0,sys41*RAT1_15[4][1]);
	g41s->SetPointError(3, 0.0,sys41*RAT1_16[4][1]);

	TGraphErrors* g41pAl = new TGraphErrors();
	g41pAl->SetPoint(0, BBCpAl[0]+shift,RATpAl1_4[4][1]);
	g41pAl->SetPoint(1, BBCpAl[1]+shift,RATpAl1_5[4][1]);
	g41pAl->SetPoint(2, BBCpAl[2]+shift,RATpAl1_15[4][1]);
	g41pAl->SetPoint(3, BBCpAl[3]+shift,RATpAl1_16[4][1]);
	g41pAl->SetPointError(0, 0.0,ERRORpAl1_4[4][1]);
	g41pAl->SetPointError(1, 0.0,ERRORpAl1_5[4][1]);
	g41pAl->SetPointError(2, 0.0,ERRORpAl1_15[4][1]);
	g41pAl->SetPointError(3, 0.0,ERRORpAl1_16[4][1]);
        TGraphErrors* g41pAls = new TGraphErrors();
	g41pAls->SetPoint(0, BBCpAl[0]+shift,RATpAl1_4[4][1]);
	g41pAls->SetPoint(1, BBCpAl[1]+shift,RATpAl1_5[4][1]);
	g41pAls->SetPoint(2, BBCpAl[2]+shift,RATpAl1_15[4][1]);
	g41pAls->SetPoint(3, BBCpAl[3]+shift,RATpAl1_16[4][1]);
	g41pAls->SetPointError(0, 0.0,sys41*RATpAl1_4[4][1]);
	g41pAls->SetPointError(1, 0.0,sys41*RATpAl1_5[4][1]);
	g41pAls->SetPointError(2, 0.0,sys41*RATpAl1_15[4][1]);
	g41pAls->SetPointError(3, 0.0,sys41*RATpAl1_16[4][1]);

	TGraphErrors* g51 = new TGraphErrors();
	g51->SetPoint(0, BBC[0]+2*shift,RAT1_4[5][1]);
	g51->SetPoint(1, BBC[1]+2*shift,RAT1_5[5][1]);
	g51->SetPoint(2, BBC[2]+2*shift,RAT1_15[5][1]);
	g51->SetPoint(3, BBC[3]+2*shift,RAT1_16[5][1]);
	g51->SetPointError(0, 0.0,ERROR1_4[5][1]);
	g51->SetPointError(1, 0.0,ERROR1_5[5][1]);
	g51->SetPointError(2, 0.0,ERROR1_15[5][1]);
	g51->SetPointError(3, 0.0,ERROR1_16[5][1]);
	TGraphErrors* g51s = new TGraphErrors();
	g51s->SetPoint(0, BBC[0]+2*shift,RAT1_4[5][1]);
	g51s->SetPoint(1, BBC[1]+2*shift,RAT1_5[5][1]);
	g51s->SetPoint(2, BBC[2]+2*shift,RAT1_15[5][1]);
	g51s->SetPoint(3, BBC[3]+2*shift,RAT1_16[5][1]);
	g51s->SetPointError(0, 0.0,sys51*RAT1_4[5][1]);
	g51s->SetPointError(1, 0.0,sys51*RAT1_5[5][1]);
	g51s->SetPointError(2, 0.0,sys51*RAT1_15[5][1]);
	g51s->SetPointError(3, 0.0,sys51*RAT1_16[5][1]);

	TGraphErrors* g51pAl = new TGraphErrors();
	g51pAl->SetPoint(0, BBCpAl[0]+2*shift,RATpAl1_4[5][1]);
	g51pAl->SetPoint(1, BBCpAl[1]+2*shift,RATpAl1_5[5][1]);
	g51pAl->SetPoint(2, BBCpAl[2]+2*shift,RATpAl1_15[5][1]);
	g51pAl->SetPoint(3, BBCpAl[3]+2*shift,RATpAl1_16[5][1]);
	g51pAl->SetPointError(0, 0.0,ERRORpAl1_4[5][1]);
	g51pAl->SetPointError(1, 0.0,ERRORpAl1_5[5][1]);
	g51pAl->SetPointError(2, 0.0,ERRORpAl1_15[5][1]);
	g51pAl->SetPointError(3, 0.0,ERRORpAl1_16[5][1]);
	TGraphErrors* g51pAls = new TGraphErrors();
	g51pAls->SetPoint(0, BBCpAl[0]+2*shift,RATpAl1_4[5][1]);
	g51pAls->SetPoint(1, BBCpAl[1]+2*shift,RATpAl1_5[5][1]);
	g51pAls->SetPoint(2, BBCpAl[2]+2*shift,RATpAl1_15[5][1]);
	g51pAls->SetPoint(3, BBCpAl[3]+2*shift,RATpAl1_16[5][1]);
	g51pAls->SetPointError(0, 0.0,sys51*RATpAl1_4[5][1]);
	g51pAls->SetPointError(1, 0.0,sys51*RATpAl1_5[5][1]);
	g51pAls->SetPointError(2, 0.0,sys51*RATpAl1_15[5][1]);
	g51pAls->SetPointError(3, 0.0,sys51*RATpAl1_16[5][1]);

	TF1 *baseline = new TF1("baseline","1",-1000,52600);
	baseline->GetYaxis()->SetRangeUser(0.35,1.4);
	baseline->SetLineWidth(0);
	baseline->SetLineColor(0);
	baseline->GetYaxis()->SetNdivisions(505);
        baseline->GetXaxis()->SetNdivisions(505);

	auto c1 = new TCanvas("c1","pAu/pp and pAl/pp",400,400);
	c1->SetMargin(0.17,0.01,0.15,0.04);
	//draw pAu
	double size = 1.5;
	double width = 3;
	baseline->SetLineStyle(7);
	baseline->GetYaxis()->SetLabelSize(0.06);
	baseline->GetXaxis()->SetLabelSize(0.05);
	baseline->GetYaxis()->SetTitle("Relative area");
	baseline->GetYaxis()->SetTitleSize(0.06);
	baseline->GetYaxis()->CenterTitle();
	baseline->GetXaxis()->SetTitle("E.A. (#SigmaE_{BBC})");
	baseline->GetXaxis()->CenterTitle();
	baseline->GetXaxis()->SetTitleOffset(1.1);
	baseline->GetXaxis()->SetTitleSize(0.06);
	baseline->GetYaxis()->SetTitleOffset(1.35);
	
	baseline->Draw();
	Draw_BoxError(g21s,2000,kRed,1001);
	Draw_BoxError(g21pAls,2000,15,1001);
	g21->GetYaxis()->SetRangeUser(0,1.5);
	g21->SetMarkerStyle(29);
	g21->SetLineColor(2);
	g21->SetMarkerColor(2);
	g21->SetLineWidth(width);
	g21->SetMarkerSize(1.8);
	g21->Draw("samePZ");
	g21s->SetMarkerSize(size+1);
	g21s->SetLineColor(2);
	g21s->SetLineWidth(width);
	//g51s->Draw("same[]");
        double xx = 0.25;
        double yy = 0.1;
        //drawLatex(xx-0.07, yy+0.7,"1.4-2.0 GeV/c#otimes1.0-1.4 GeV/c",62,0.065,kBlack);
        TLegend *leg1_1 = new TLegend(0.56,0.57,0.99,0.63);
	leg1_1->SetNColumns(2);
	leg1_1->SetTextSize(0.05);
	//leg1_1->SetHeader("p_{T}^{trig}=1.5-2.0 GeV/c, p_{T}^{asso}=1.0-1.5 GeV/c");
        leg1_1->AddEntry(g21,"pAu/pp","P");
	leg1_1->AddEntry(g21pAl,"pAl/pp","P");
        leg1_1->SetFillStyle(0);
	leg1_1->SetLineColor(0);
	leg1_1->SetBorderSize ( 0 );
        leg1_1->Draw("same");

	g21pAl->GetYaxis()->SetRangeUser(0,2.0);
	g21pAl->SetMarkerColor(1);
	g21pAl->SetMarkerStyle(34);
	g21pAl->SetLineColor(1);
	g21pAl->SetLineWidth(width);
	g21pAl->SetMarkerSize(size);
	g21pAl->Draw("samePZ");
	g21pAls->SetMarkerSize(size);
	g21pAls->SetLineColor(1);
	g21pAls->SetLineWidth(width);
	 drawLatex(0.2,0.9,"STAR",22,0.06,1);
	drawLatex(0.40,0.90,"#sqrt{s_{NN}} = 200 GeV, NN #rightarrow #pi^{0}#pi^{0}X",42,0.05,kBlack);
	drawLatex(0.46,0.82,"2.6 < #eta < 4, #Delta#phi #in  [ #frac{#pi}{2} , #frac{3#pi}{2} ]",42,0.05,1);
	drawLatex(0.64,0.74, "p_{T}^{trig}=1.5-2 GeV/c",42,0.05,kBlack);
	drawLatex(0.61,0.66, " p_{T}^{asso}=1-1.5 GeV/c",42,0.05,kBlack);


 	c1->SaveAs("f3.pdf");	
}
