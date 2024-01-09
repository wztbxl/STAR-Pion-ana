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

void readpar(int beam, int cut, int corr, int print=0){
    char name[200];
    sprintf(name,"../txt/beam%d_cut%d_corr%d.par",beam,cut,corr);
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

void sumBkg()
{
	gStyle->SetOptTitle(0);
	gStyle->SetPadGridX(0);
	gStyle->SetPadGridY(0);
	gStyle->SetEndErrorSize(8);

	memset(PAR0,0,sizeof(PAR0));
	memset(PAR1,0,sizeof(PAR1));
	memset(PAR2,0,sizeof(PAR2));
	memset(ERR0,0,sizeof(ERR0));
	memset(ERR0,0,sizeof(ERR0));
        memset(ERR1,0,sizeof(ERR1));
        memset(ERR2,0,sizeof(ERR2));

	readpar(0,2,1,1);//pp
	readpar(3,4,1,1);//pAu1 3000<BBCE<12000
	readpar(3,5,1,1);//pAu1 12000<BBCE<24000
        readpar(3,15,1,1);//pAu1 24000<BBCE<36000
	readpar(3,16,1,1);//pAu1 36000<BBCE

        //calculate ratio pAu/pp, and error
	double RAT0_4[kNPtBin][kNPtBin],RAT0_5[kNPtBin][kNPtBin],RAT0_16[kNPtBin][kNPtBin],RAT0_15[kNPtBin][kNPtBin];
	double RAT2_4[kNPtBin][kNPtBin],RAT2_5[kNPtBin][kNPtBin],RAT2_16[kNPtBin][kNPtBin],RAT2_15[kNPtBin][kNPtBin];
	double ERROR0_4[kNPtBin][kNPtBin],ERROR0_5[kNPtBin][kNPtBin],ERROR0_16[kNPtBin][kNPtBin],ERROR0_15[kNPtBin][kNPtBin];
	
        for(int i=1;i<kNPtBin; i++){
		for(int j=1; j<i; j++){
			//ratio
			RAT0_4[i][j] = PAR0[i][j][4][3]/PAR0[i][j][2][0];
			RAT0_5[i][j]= PAR0[i][j][5][3]/PAR0[i][j][2][0];
			RAT0_15[i][j]= PAR0[i][j][15][3]/PAR0[i][j][2][0];
			RAT0_16[i][j] = PAR0[i][j][16][3]/PAR0[i][j][2][0];

			//statistic error
			ERROR0_4[i][j] = RAT0_4[i][j]*sqrt(pow(ERR0[i][j][4][3],2)/pow(PAR0[i][j][4][3],2)+pow(ERR0[i][j][2][0],2)/pow(PAR0[i][j][2][0],2));
			ERROR0_5[i][j] = RAT0_5[i][j]*sqrt(pow(ERR0[i][j][5][3],2)/pow(PAR0[i][j][5][3],2)+pow(ERR0[i][j][2][0],2)/pow(PAR0[i][j][2][0],2));
			ERROR0_15[i][j] = RAT0_15[i][j]*sqrt(pow(ERR0[i][j][15][3],2)/pow(PAR0[i][j][15][3],2)+pow(ERR0[i][j][2][0],2)/pow(PAR0[i][j][2][0],2));
			ERROR0_16[i][j] = RAT0_16[i][j]*sqrt(pow(ERR0[i][j][16][3],2)/pow(PAR0[i][j][16][3],2)+pow(ERR0[i][j][2][0],2)/pow(PAR0[i][j][2][0],2));


		}
	}
	//sys error divided by content
	double sys21 = 0.019*1.414, sys31 = 0.019*1.414, sys41 = 0.031*1.414, sys51 = 0.042*1.414;
	double sys32 = 0.063*1.414, sys42 = 0.087*1.414, sys52 = 0.116*1.414;
	double sys43 = 0.163*1.414,sys53 = 0.245*1.414;
        //int BBC[4]= {3000,12000,24000,36000};
        int BBC[4]={7300,18000,30000,43500};
	int shift = 850;
	TGraphErrors* g21 = new TGraphErrors();
	g21->SetPoint(0, BBC[0]-3*shift,RAT0_4[2][1]);
	g21->SetPoint(1, BBC[1]-3*shift,RAT0_5[2][1]);
	g21->SetPoint(2, BBC[2]-3*shift,RAT0_15[2][1]);
	g21->SetPoint(3, BBC[3]-3*shift,RAT0_16[2][1]);
	//stat error
	g21->SetPointError(0, 0.0,ERROR0_4[2][1]);
	g21->SetPointError(1, 0.0,ERROR0_5[2][1]);
	g21->SetPointError(2, 0.0,ERROR0_15[2][1]);
	g21->SetPointError(3, 0.0,ERROR0_16[2][1]);
        TGraphErrors* g21s = new TGraphErrors();
	g21s->SetPoint(0, BBC[0]-shift*3,RAT0_4[2][1]);
	g21s->SetPoint(1, BBC[1]-shift*3,RAT0_5[2][1]);
	g21s->SetPoint(2, BBC[2]-shift*3,RAT0_15[2][1]);
	g21s->SetPoint(3, BBC[3]-shift*3,RAT0_16[2][1]);
	//add total error = sqrt(stat error*stat error + sys error*sys error)
	/*
	g21s->SetPointError(0, 0.0,sqrt(ERROR0_4[2][1]*ERROR0_4[2][1]+sys21*sys21*RAT0_4[2][1]*RAT0_4[2][1]));
	g21s->SetPointError(1, 0.0,sqrt(ERROR0_5[2][1]*ERROR0_5[2][1]+sys21*sys21*RAT0_5[2][1]*RAT0_5[2][1]));
	g21s->SetPointError(2, 0.0,sqrt(ERROR0_15[2][1]*ERROR0_15[2][1]+sys21*sys21*RAT0_15[2][1]*RAT0_15[2][1]));
	g21s->SetPointError(3, 0.0,sqrt(ERROR0_16[2][1]*ERROR0_16[2][1]+sys21*sys21*RAT0_16[2][1]*RAT0_16[2][1]));
*/
	//add sys error
g21s->SetPointError(0, 0.0,sys21*RAT0_4[2][1]);
	g21s->SetPointError(1, 0.0,sys21*RAT0_5[2][1]);
	g21s->SetPointError(2, 0.0,sys21*RAT0_15[2][1]);
	g21s->SetPointError(3, 0.0,sys21*RAT0_16[2][1]);
TGraphErrors* g31 = new TGraphErrors();
	g31->SetPoint(0, BBC[0]-shift,RAT0_4[3][1]);
	g31->SetPoint(1, BBC[1]-shift,RAT0_5[3][1]);
	g31->SetPoint(2, BBC[2]-shift,RAT0_15[3][1]);
	g31->SetPoint(3, BBC[3]-shift,RAT0_16[3][1]);
	g31->SetPointError(0, 0.0,ERROR0_4[3][1]);
	g31->SetPointError(1, 0.0,ERROR0_5[3][1]);
	g31->SetPointError(2, 0.0,ERROR0_15[3][1]);
	g31->SetPointError(3, 0.0,ERROR0_16[3][1]);
        TGraphErrors* g31s = new TGraphErrors();
	g31s->SetPoint(0, BBC[0]-shift,RAT0_4[3][1]);
	g31s->SetPoint(1, BBC[1]-shift,RAT0_5[3][1]);
	g31s->SetPoint(2, BBC[2]-shift,RAT0_15[3][1]);
	g31s->SetPoint(3, BBC[3]-shift,RAT0_16[3][1]);
/*
	g31s->SetPointError(0, 0.0,sqrt(ERROR0_4[3][1]*ERROR0_4[3][1]+sys31*sys31*RAT0_4[3][1]*RAT0_4[3][1]));
	g31s->SetPointError(1, 0.0,sqrt(ERROR0_5[3][1]*ERROR0_5[3][1]+sys31*sys31*RAT0_5[3][1]*RAT0_5[3][1]));
	g31s->SetPointError(2, 0.0,sqrt(ERROR0_15[3][1]*ERROR0_15[3][1]+sys31*sys31*RAT0_15[3][1]*RAT0_15[3][1]));
	g31s->SetPointError(3, 0.0,sqrt(ERROR0_16[3][1]*ERROR0_16[3][1]+sys31*sys31*RAT0_16[3][1]*RAT0_16[3][1]));
*/
g31s->SetPointError(0, 0.0,sys31*RAT0_4[3][1]);
	g31s->SetPointError(1, 0.0,sys31*RAT0_5[3][1]);
	g31s->SetPointError(2, 0.0,sys31*RAT0_15[3][1]);
	g31s->SetPointError(3, 0.0,sys31*RAT0_16[3][1]);
TGraphErrors* g41 = new TGraphErrors();
	g41->SetPoint(0, BBC[0]+shift,RAT0_4[4][1]);
	g41->SetPoint(1, BBC[1]+shift,RAT0_5[4][1]);
	g41->SetPoint(2, BBC[2]+shift,RAT0_15[4][1]);
	g41->SetPoint(3, BBC[3]+shift,RAT0_16[4][1]);
	g41->SetPointError(0, 0.0,ERROR0_4[4][1]);
	g41->SetPointError(1, 0.0,ERROR0_5[4][1]);
	g41->SetPointError(2, 0.0,ERROR0_15[4][1]);
	g41->SetPointError(3, 0.0,ERROR0_16[4][1]);
        TGraphErrors* g41s = new TGraphErrors();
	g41s->SetPoint(0, BBC[0]+shift,RAT0_4[4][1]);
	g41s->SetPoint(1, BBC[1]+shift,RAT0_5[4][1]);
	g41s->SetPoint(2, BBC[2]+shift,RAT0_15[4][1]);
	g41s->SetPoint(3, BBC[3]+shift,RAT0_16[4][1]);
/*
	g41s->SetPointError(0, 0.0,sqrt(ERROR0_4[4][1]*ERROR0_4[4][1]+sys41*sys41*RAT0_4[4][1]*RAT0_4[4][1]));
	g41s->SetPointError(1, 0.0,sqrt(ERROR0_5[4][1]*ERROR0_5[4][1]+sys41*sys41*RAT0_5[4][1]*RAT0_5[4][1]));
	g41s->SetPointError(2, 0.0,sqrt(ERROR0_15[4][1]*ERROR0_15[4][1]+sys41*sys41*RAT0_15[4][1]*RAT0_15[4][1]));
	g41s->SetPointError(3, 0.0,sqrt(ERROR0_16[4][1]*ERROR0_16[4][1]+sys41*sys41*RAT0_16[4][1]*RAT0_16[4][1]));
*/
	g41s->SetPointError(0, 0.0,sys41*RAT0_4[4][1]);
	g41s->SetPointError(1, 0.0,sys41*RAT0_5[4][1]);
	g41s->SetPointError(2, 0.0,sys41*RAT0_15[4][1]);
	g41s->SetPointError(3, 0.0,sys41*RAT0_16[4][1]);

TGraphErrors* g51 = new TGraphErrors();
	g51->SetPoint(0, BBC[0]+3*shift,RAT0_4[5][1]);
	g51->SetPoint(1, BBC[1]+3*shift,RAT0_5[5][1]);
	g51->SetPoint(2, BBC[2]+3*shift,RAT0_15[5][1]);
	g51->SetPoint(3, BBC[3]+3*shift,RAT0_16[5][1]);
	g51->SetPointError(0, 0.0,ERROR0_4[5][1]);
	g51->SetPointError(1, 0.0,ERROR0_5[5][1]);
	g51->SetPointError(2, 0.0,ERROR0_15[5][1]);
	g51->SetPointError(3, 0.0,ERROR0_16[5][1]);
	TGraphErrors* g51s = new TGraphErrors();
	g51s->SetPoint(0, BBC[0]+3*shift,RAT0_4[5][1]);
	g51s->SetPoint(1, BBC[1]+3*shift,RAT0_5[5][1]);
	g51s->SetPoint(2, BBC[2]+3*shift,RAT0_15[5][1]);
	g51s->SetPoint(3, BBC[3]+3*shift,RAT0_16[5][1]);
/*
	g51s->SetPointError(0, 0.0,sqrt(ERROR0_4[5][1]*ERROR0_4[5][1]+sys51*sys51*RAT0_4[5][1]*RAT0_4[5][1]));
	g51s->SetPointError(1, 0.0,sqrt(ERROR0_5[5][1]*ERROR0_5[5][1]+sys51*sys51*RAT0_5[5][1]*RAT0_5[5][1]));
	g51s->SetPointError(2, 0.0,sqrt(ERROR0_15[5][1]*ERROR0_15[5][1]+sys51*sys51*RAT0_15[5][1]*RAT0_15[5][1]));
	g51s->SetPointError(3, 0.0,sqrt(ERROR0_16[5][1]*ERROR0_16[5][1]+sys51*sys51*RAT0_16[5][1]*RAT0_16[5][1]));
*/
	g51s->SetPointError(0, 0.0,sys51*RAT0_4[5][1]);
	g51s->SetPointError(1, 0.0,sys51*RAT0_5[5][1]);
	g51s->SetPointError(2, 0.0,sys51*RAT0_15[5][1]);
	g51s->SetPointError(3, 0.0,sys51*RAT0_16[5][1]);

TGraphErrors* g32 = new TGraphErrors();
	g32->SetPoint(0, BBC[0]-2*shift,RAT0_4[3][2]);
	g32->SetPoint(1, BBC[1]-2*shift,RAT0_5[3][2]);
	g32->SetPoint(2, BBC[2]-2*shift,RAT0_15[3][2]);
	g32->SetPoint(3, BBC[3]-2*shift,RAT0_16[3][2]);
	g32->SetPointError(0, 0.0,ERROR0_4[3][2]);
	g32->SetPointError(1, 0.0,ERROR0_5[3][2]);
	g32->SetPointError(2, 0.0,ERROR0_15[3][2]);
	g32->SetPointError(3, 0.0,ERROR0_16[3][2]);
TGraphErrors* g32s = new TGraphErrors();
	g32s->SetPoint(0, BBC[0]-2*shift,RAT0_4[3][2]);
	g32s->SetPoint(1, BBC[1]-2*shift,RAT0_5[3][2]);
	g32s->SetPoint(2, BBC[2]-2*shift,RAT0_15[3][2]);
	g32s->SetPoint(3, BBC[3]-2*shift,RAT0_16[3][2]);
/*
	g32s->SetPointError(0, 0.0,sqrt(ERROR0_4[3][2]*ERROR0_4[3][2]+sys32*sys32*RAT0_4[3][2]*RAT0_4[3][2]));
	g32s->SetPointError(1, 0.0,sqrt(ERROR0_5[3][2]*ERROR0_5[3][2]+sys32*sys32*RAT0_5[3][2]*RAT0_5[3][2]));
	g32s->SetPointError(2, 0.0,sqrt(ERROR0_15[3][2]*ERROR0_15[3][2]+sys32*sys32*RAT0_15[3][2]*RAT0_15[3][2]));
	g32s->SetPointError(3, 0.0,sqrt(ERROR0_16[3][2]*ERROR0_16[3][2]+sys32*sys32*RAT0_16[3][2]*RAT0_16[3][2]));
*/
	g32s->SetPointError(0, 0.0,sys32*RAT0_4[3][2]);
	g32s->SetPointError(1, 0.0,sys32*RAT0_5[3][2]);
	g32s->SetPointError(2, 0.0,sys32*RAT0_15[3][2]);
	g32s->SetPointError(3, 0.0,sys32*RAT0_16[3][2]);
	
TGraphErrors* g42 = new TGraphErrors();
	g42->SetPoint(0, BBC[0],RAT0_4[4][2]);
	g42->SetPoint(1, BBC[1],RAT0_5[4][2]);
	g42->SetPoint(2, BBC[2],RAT0_15[4][2]);
	g42->SetPoint(3, BBC[3],RAT0_16[4][2]);
	g42->SetPointError(0, 0.0,ERROR0_4[4][2]);
	g42->SetPointError(1, 0.0,ERROR0_5[4][2]);
	g42->SetPointError(2, 0.0,ERROR0_15[4][2]);
	g42->SetPointError(3, 0.0,ERROR0_16[4][2]);
 TGraphErrors* g42s = new TGraphErrors();
	g42s->SetPoint(0, BBC[0],RAT0_4[4][2]);
	g42s->SetPoint(1, BBC[1],RAT0_5[4][2]);
	g42s->SetPoint(2, BBC[2],RAT0_15[4][2]);
	g42s->SetPoint(3, BBC[3],RAT0_16[4][2]);
/*
	g42s->SetPointError(0, 0.0,sqrt(ERROR0_4[4][2]*ERROR0_4[4][2]+sys42*sys42*RAT0_4[4][2]*RAT0_4[4][2]));
	g42s->SetPointError(1, 0.0,sqrt(ERROR0_5[4][2]*ERROR0_5[4][2]+sys42*sys42*RAT0_5[4][2]*RAT0_5[4][2]));
	g42s->SetPointError(2, 0.0,sqrt(ERROR0_15[4][2]*ERROR0_15[4][2]+sys42*sys42*RAT0_15[4][2]*RAT0_15[4][2]));
	g42s->SetPointError(3, 0.0,sqrt(ERROR0_16[4][2]*ERROR0_16[4][2]+sys42*sys42*RAT0_16[4][2]*RAT0_16[4][2]));
*/
	g42s->SetPointError(0, 0.0,sys42*RAT0_4[4][2]);
	g42s->SetPointError(1, 0.0,sys42*RAT0_5[4][2]);
	g42s->SetPointError(2, 0.0,sys42*RAT0_15[4][2]);
	g42s->SetPointError(3, 0.0,sys42*RAT0_16[4][2]);
	
TGraphErrors* g52 = new TGraphErrors();
	g52->SetPoint(0, BBC[0]+2*shift,RAT0_4[5][2]);
	g52->SetPoint(1, BBC[1]+2*shift,RAT0_5[5][2]);
	g52->SetPoint(2, BBC[2]+2*shift,RAT0_15[5][2]);
	g52->SetPoint(3, BBC[3]+2*shift,RAT0_16[5][2]);
	g52->SetPointError(0, 0.0,ERROR0_4[5][2]);
	g52->SetPointError(1, 0.0,ERROR0_5[5][2]);
	g52->SetPointError(2, 0.0,ERROR0_15[5][2]);
	g52->SetPointError(3, 0.0,ERROR0_16[5][2]);
TGraphErrors* g52s = new TGraphErrors();
	g52s->SetPoint(0, BBC[0]+2*shift,RAT0_4[5][2]);
	g52s->SetPoint(1, BBC[1]+2*shift,RAT0_5[5][2]);
	g52s->SetPoint(2, BBC[2]+2*shift,RAT0_15[5][2]);
	g52s->SetPoint(3, BBC[3]+2*shift,RAT0_16[5][2]);
/*
		g52s->SetPointError(0, 0.0,sqrt(ERROR0_4[5][2]*ERROR0_4[5][2]+sys52*sys52*RAT0_4[5][2]*RAT0_4[5][2]));
	g52s->SetPointError(1, 0.0,sqrt(ERROR0_5[5][2]*ERROR0_5[5][2]+sys52*sys52*RAT0_5[5][2]*RAT0_5[5][2]));
	g52s->SetPointError(2, 0.0,sqrt(ERROR0_15[5][2]*ERROR0_15[5][2]+sys52*sys52*RAT0_15[5][2]*RAT0_15[5][2]));
	g52s->SetPointError(3, 0.0,sqrt(ERROR0_16[5][2]*ERROR0_16[5][2]+sys52*sys52*RAT0_16[5][2]*RAT0_16[5][2]));
*/
	g52s->SetPointError(0, 0.0,sys52*RAT0_4[5][2]);
	g52s->SetPointError(1, 0.0,sys52*RAT0_5[5][2]);
	g52s->SetPointError(2, 0.0,sys52*RAT0_15[5][2]);
	g52s->SetPointError(3, 0.0,sys52*RAT0_16[5][2]);
	

TGraphErrors* g43 = new TGraphErrors();
	g43->SetPoint(0, BBC[0]-shift,RAT0_4[4][3]);
	g43->SetPoint(1, BBC[1]-shift,RAT0_5[4][3]);
	g43->SetPoint(2, BBC[2]-shift,RAT0_15[4][3]);
	g43->SetPoint(3, BBC[3]-shift,RAT0_16[4][3]);
	g43->SetPointError(0, 0.0,ERROR0_4[4][3]);
	g43->SetPointError(1, 0.0,ERROR0_5[4][3]);
	g43->SetPointError(2, 0.0,ERROR0_15[4][3]);
	g43->SetPointError(3, 0.0,ERROR0_16[4][3]);
TGraphErrors* g43s = new TGraphErrors();
	g43s->SetPoint(0, BBC[0]-shift,RAT0_4[4][3]);
	g43s->SetPoint(1, BBC[1]-shift,RAT0_5[4][3]);
	g43s->SetPoint(2, BBC[2]-shift,RAT0_15[4][3]);
	g43s->SetPoint(3, BBC[3]-shift,RAT0_16[4][3]);
	g43s->SetPointError(0, 0.0,sys43*RAT0_4[4][3]);
	g43s->SetPointError(1, 0.0,sys43*RAT0_5[4][3]);
	g43s->SetPointError(2, 0.0,sys43*RAT0_15[4][3]);
	g43s->SetPointError(3, 0.0,sys43*RAT0_16[4][3]);
TGraphErrors* g53 = new TGraphErrors();
	g53->SetPoint(0, BBC[0]+shift,RAT0_4[5][3]);
	g53->SetPoint(1, BBC[1]+shift,RAT0_5[5][3]);
	g53->SetPoint(2, BBC[2]+shift,RAT0_15[5][3]);
	g53->SetPoint(3, BBC[3]+shift,RAT0_16[5][3]);
	g53->SetPointError(0, 0.0,ERROR0_4[5][3]);
	g53->SetPointError(1, 0.0,ERROR0_5[5][3]);
	g53->SetPointError(2, 0.0,ERROR0_15[5][3]);
	g53->SetPointError(3, 0.0,ERROR0_16[5][3]);
TGraphErrors* g53s = new TGraphErrors();
	g53s->SetPoint(0, BBC[0]+shift,RAT0_4[5][3]);
	g53s->SetPoint(1, BBC[1]+shift,RAT0_5[5][3]);
	g53s->SetPoint(2, BBC[2]+shift,RAT0_15[5][3]);
	g53s->SetPoint(3, BBC[3]+shift,RAT0_16[5][3]);
/*
			g53s->SetPointError(0, 0.0,sqrt(ERROR0_4[5][3]*ERROR0_4[5][3]+sys53*sys53*RAT0_4[5][3]*RAT0_4[5][3]));
	g53s->SetPointError(1, 0.0,sqrt(ERROR0_5[5][3]*ERROR0_5[5][3]+sys53*sys53*RAT0_5[5][3]*RAT0_5[5][3]));
	g53s->SetPointError(2, 0.0,sqrt(ERROR0_15[5][3]*ERROR0_15[5][3]+sys53*sys53*RAT0_15[5][3]*RAT0_15[5][3]));
	g53s->SetPointError(3, 0.0,sqrt(ERROR0_16[5][3]*ERROR0_16[5][3]+sys53*sys53*RAT0_16[5][3]*RAT0_16[5][3]));
*/
	g53s->SetPointError(0, 0.0,sys53*RAT0_4[5][3]);
	g53s->SetPointError(1, 0.0,sys53*RAT0_5[5][3]);
	g53s->SetPointError(2, 0.0,sys53*RAT0_15[5][3]);
	g53s->SetPointError(3, 0.0,sys53*RAT0_16[5][3]);
	

TGraphErrors* g54 = new TGraphErrors();
	g54->SetPoint(0, BBC[0],RAT0_4[5][4]);
	g54->SetPoint(1, BBC[1],RAT0_5[5][4]);
	g54->SetPoint(2, BBC[2],RAT0_15[5][4]);
	g54->SetPoint(3, BBC[3],RAT0_16[5][4]);
	g54->SetPointError(0, 0.0,ERROR0_4[5][4]);
	g54->SetPointError(1, 0.0,ERROR0_5[5][4]);
	g54->SetPointError(2, 0.0,ERROR0_15[5][4]);
	g54->SetPointError(3, 0.0,ERROR0_16[5][4]);

	TF1 *baseline = new TF1("baseline","1",1000,52000);
	baseline->GetYaxis()->SetRangeUser(-0.1,2.5);
	baseline->SetLineWidth(1.5);
	        baseline->GetYaxis()->SetNdivisions(505);
        baseline->GetXaxis()->SetNdivisions(505);

	auto c1 = new TCanvas("c1","Paway_pAu/Paway_pp",200,10,600,800);
        TPad *pad_1 = new TPad("pad_1", "pad_1", 0.00,0.67,1.0,1.00);
	pad_1->SetMargin(0.11, 0.01, 0.00, 1.00);
	TPad *pad_2 = new TPad("pad_2", "pad_2", 0.00,0.38,1.0,0.67);
    	pad_2->SetMargin(0.11, 0.01, 0.00, 0.005);
	TPad *pad_3 = new TPad("pad_3", "pad_3", 0.00,0.05,1.0,0.38);
    	pad_3->SetMargin(0.11, 0.01, 1.00, 0.00);
	TPad *pad_4 = new TPad("pad_4", "pad_4", 0.00,0.0,1.0,0.05);

	c1->cd();
	pad_1->Draw();
	pad_2->Draw();
    	pad_3->Draw();
    	pad_4->Draw();

	pad_1->cd();
	double size = 1.7;
	double width = 2.8;
	baseline->SetLineStyle(7);
	baseline->GetYaxis()->SetLabelSize(0.08);
	baseline->Draw();
	g21->GetYaxis()->SetRangeUser(0,2.0);
	g21->SetMarkerColor(kMagenta-6);
	g21->SetMarkerStyle(30);
	g21->SetLineColor(kMagenta-6);
	g21->SetLineWidth(width);
	g21->SetMarkerSize(size);
	g21->Draw("sameP");
	g21s->SetMarkerSize(size);
	g21s->SetLineColor(kMagenta-6);
	g21s->SetLineWidth(width);
	g21s->Draw("same[]");
	g31->SetMarkerColor(kBlue-6);
	g31->SetMarkerStyle(8);
	g31->SetLineColor(kBlue-6);
	g31->SetLineWidth(width);
	g31->SetMarkerSize(size);
	g31->Draw("sameP");
	g31s->SetLineColor(kBlue-6);
	g31s->SetLineWidth(width);
	g31s->Draw("same[]");
	g41s->SetLineColor(kCyan+2);
	g41s->SetLineWidth(width);
	g41s->Draw("same[]");
	g41->SetMarkerColor(kCyan+2);
	g41->SetMarkerStyle(25);
	g41->SetLineColor(kCyan+2);
	g41->SetLineWidth(width);
	g41->SetMarkerSize(size);
	g41->Draw("sameP");
	g51->SetMarkerColor(kGreen+3);
	g51->SetMarkerStyle(22);
	g51->SetLineColor(kGreen+3);
	g51->SetLineWidth(width);
	g51->SetMarkerSize(size);
	g51->Draw("sameP");
	g51s->SetLineColor(kGreen+3);
	g51s->SetLineWidth(width);
	g51s->Draw("same[]");
        double xx = 0.25;
        double yy = 0.09;
	drawLatex(0.15, 0.8,"#sqrt{s_{NN}} = 200 GeV, 2.6 < #eta < 4.0",62,0.088,kBlack);
	drawLatex(0.25-0.07, 0.58,"p^{trig}_{T}",62,0.085,kBlack);
        drawLatex(0.65, yy,"p^{asso}_{T} = 1.0-1.5 GeV/c",62,0.085,kBlack);
	drawLatex(0.88,0.8,"STAR",62,0.09,1);
        TLegend *leg1_1 = new TLegend(0.25,0.56,0.85,0.78);
        leg1_1->SetNColumns(2);
        leg1_1->AddEntry(g21,"1.5-2.0 GeV/c","P");
        leg1_1->AddEntry(g31,"2.0-2.5 GeV/c","P");
        TLegend *leg1_2 = new TLegend(0.25,0.43,0.85,0.65);
        leg1_2->SetNColumns(2);
        leg1_2->AddEntry(g41,"2.5-3.0 GeV/c","P");
        leg1_2->AddEntry(g51,"3.0-5.0 GeV/c","P");
        leg1_1->SetFillStyle(0);
        leg1_1->SetLineColor(0);
        leg1_2->SetFillStyle(0);
        leg1_2->SetLineColor(0);
        leg1_2->SetBorderSize(0);
        leg1_1->Draw("same");
        leg1_2->Draw("same");	

	pad_2->cd();
	g32->GetYaxis()->SetRangeUser(-0.1,1.8);
	g32->GetYaxis()->SetLabelSize(0.08);
	g32->GetYaxis()->SetTitle("Pedestal: pAu/pp");
	g32->GetYaxis()->SetTitleSize(0.1);
	g32->GetYaxis()->SetTitleOffset(0.5);
	g32->GetYaxis()->SetNdivisions(505);
	//baseline->GetYaxis()->SetTitle("#frac{Paway pAu1}{Paway pp}");
	g32->SetMarkerColor(kBlue-6);
	g32->SetMarkerStyle(8);
	g32->SetLineColor(kBlue-6);
	g32->SetLineWidth(width);
	g32->SetMarkerSize(size);
        TF1 *baseline2 = new TF1("baseline2","1",1000,52000);
	baseline2->SetLineWidth(1.5);
        baseline2->GetYaxis()->SetRangeUser(-0.1,1.8);
	baseline2->GetYaxis()->SetTitle("Relative pedestal");
	baseline2->GetYaxis()->CenterTitle();
	baseline2->GetYaxis()->SetTitleSize(0.12);
	baseline2->GetYaxis()->SetTitleOffset(0.46);
	baseline2->GetYaxis()->SetLabelSize(0.09);
	baseline2->SetLineStyle(7);
                baseline2->GetYaxis()->SetNdivisions(505);
        baseline2->GetXaxis()->SetNdivisions(505);
	baseline2->Draw();
	g32->Draw("sameP");
	g32s->SetLineColor(kBlue-6);
	g32s->SetLineWidth(width);
	g32s->Draw("same[]");
	baseline->Draw("same");
	g42->SetMarkerColor(kCyan+2);
	g42->SetMarkerStyle(25);
	g42->SetLineColor(kCyan+2);
	g42->SetLineWidth(width);
	g42->SetMarkerSize(size);
	g42->Draw("sameP");
	g42s->SetLineColor(kCyan+2);
	g42s->SetLineWidth(width);
	g42s->Draw("same[]");
	g52->SetMarkerColor(kGreen+3);
	g52->SetMarkerStyle(22);
	g52->SetLineColor(kGreen+3);
	g52->SetLineWidth(width);
	g52->SetMarkerSize(size);
	g52->Draw("sameP");
	g52s->SetLineColor(kGreen+3);
	g52s->SetLineWidth(width);
	g52s->Draw("same[]");
	drawLatex(0.67, yy,"p^{asso}_{T} = 1.5-2.0 GeV/c",62,0.09,kBlack);
        TLegend *leg2 = new TLegend(0.1,0.7,0.48,0.9);
        leg2->AddEntry(g32,"pT1 = 2.0-2.5 GeV/c","P");
        leg2->AddEntry(g42,"pT1 = 2.5-3.0 GeV/c","P");
        leg2->AddEntry(g52,"pT1 = 3.0-5.0 GeV/c","P");
        //leg2->Draw("same");

	pad_3->cd();
	TF1 *baseline3 = new TF1("baseline3","1",1000,52000);
	baseline3->GetYaxis()->SetRangeUser(0.1,1.9);
	baseline3->SetLineWidth(1.5);
	//g53->GetYaxis()->SetRangeUser(0,1.1);
	baseline3->GetXaxis()->SetLabelSize(0.08);
	baseline3->GetYaxis()->SetLabelOffset(0.01);
	baseline3->GetYaxis()->SetNdivisions(505);
	baseline3->GetXaxis()->SetNdivisions(505);
	baseline3->SetLineStyle(7);
	baseline3->GetYaxis()->SetLabelSize(0.08);
	baseline3->Draw();
	g53->SetMarkerColor(kGreen+3);
	g53->SetMarkerStyle(22);
	g53->SetLineColor(kGreen+3);
	g53->SetLineWidth(width);
	g53->SetMarkerSize(size);
	g53->Draw("sameP");
	g53s->SetLineColor(kGreen+3);
	g53s->SetLineWidth(width);
	g53s->Draw("same[]");
	g43->SetMarkerColor(kCyan+2);
	g43->SetMarkerStyle(25);
	g43->SetLineColor(kCyan+2);
	g43->SetLineWidth(width);
	g43->SetMarkerSize(size);
	g43->Draw("sameP");
	g43s->SetLineColor(kCyan+2);
	g43s->SetLineWidth(width);
	g43s->Draw("same[]");
	
        drawLatex(0.67, yy+0.1,"p^{asso}_{T2} = 2.0-2.5 GeV/c",62,0.08,kBlack);
        TLegend *leg3 = new TLegend(0.1,0.7,0.48,0.9);
        leg3->AddEntry(g53,"pT1 = 3.0-5.0 GeV/c","P");
/*
        TArrow *line = new TArrow(1000,0.1,45000,0.1,0.01);
        line->SetAngle(60);
        TLine *line1 = new TLine(7300,0.08,7300,0.12);
        TLine *line2 = new TLine(18000,0.08,18000,0.12);
        TLine *line3 = new TLine(30000,0.08,30000,0.12);
        TLine *line4 = new TLine(43500,0.08,43500,0.12);
        drawTof(46100, 0.07,"TofM",102,0.08,kBlack);

        line->SetLineColor(13);
        line1->SetLineColor(13);
        line2->SetLineColor(13);
        line3->SetLineColor(13);
        line4->SetLineColor(13);
        drawTof(5700, 0.13,"18.4%",62,0.06,13);
        drawTof(16500, 0.13,"24.2%",62,0.06,13);
        drawTof(28500, 0.13,"30.7%",62,0.06,13);
        drawTof(42000, 0.13,"42.8%",62,0.06,13);
        line->SetLineWidth(2);
        line1->SetLineWidth(3);
        line2->SetLineWidth(3);
        line3->SetLineWidth(3);
        line4->SetLineWidth(3);
        line->Draw();
        line1->Draw("same");
        line2->Draw("same");
        line3->Draw("same");
        line4->Draw("same");
        //leg3->Draw("same");
        pad_4->cd();
	drawLatex(0.45, 0.4,"Event Activity",62,0.7,kBlack);
c1->SaveAs("plot/HighpAu_MBpp_Bkg_Ratio.pdf");
*/
/*
TArrow *line = new TArrow(1000,0.1,45000,0.1,0.01);
        line->SetAngle(60);
        TLine *line1 = new TLine(12000,0.08,12000,0.12);
        TLine *line2 = new TLine(24000,0.08,24000,0.12);
        TLine *line3 = new TLine(36000,0.08,36000,0.12);
        drawTof(46000, 0.07,"N_{#pi^{0}}",102,0.08,kBlack);

        line->SetLineColor(13);
        line1->SetLineColor(13);
        line2->SetLineColor(13);
        line3->SetLineColor(13);
        drawTof(11000, 0.13,"31.6%",62,0.06,13);
        drawTof(23000, 0.13,"63.5%",62,0.06,13);
        drawTof(35000, 0.13,"85.3%",62,0.06,13);
        line->SetLineWidth(2);
        line1->SetLineWidth(3);
        line2->SetLineWidth(3);
        line3->SetLineWidth(3);
        line->Draw();
        line1->Draw("same");
        line2->Draw("same");
        line3->Draw("same");

        //leg3->Draw("same");
              pad_4->cd();
                        drawLatex(0.45, 0.4,"Event Activity",62,0.7,kBlack);

	c1->cd(4);
	baseline->Draw();
	g54->GetYaxis()->SetRangeUser(0,1.1);
	g54->SetMarkerColor(4);
	g54->SetMarkerStyle(21);
	g54->SetLineColor(4);
	g54->Draw("sameP");
*/
        pad_4->cd();
        drawLatex(0.43, 0.4,"E.A. (#SigmaE_{BBC})",62,0.7,kBlack);
c1->SaveAs("Pedestal_pppAu.pdf");
}
