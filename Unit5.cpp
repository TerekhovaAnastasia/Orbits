//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm5 *Form5;
//---------------------------------------------------------------------------
__fastcall TForm5::TForm5(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
float pi = M_PI;
int points = 800;
float coo_orbita[800][2];
void orbit_maden_by_Bonacci(float e, float T,float theta[points]){
	for (int i = 0; i < points; i++){
		float difference = 0.1;
		float av_move = 2*pi/T;//среднее движение
		float M = i*av_move;//средн€€ аномали€ в момент i
		float last_one = M;
	while (difference > 1e-15){
		float new_one = e*sin(last_one)+M; //”равнение  еплера
		difference = new_one - last_one;
		last_one = new_one;
	}
	float t= 2*atan(pow(((1+e)/(1-e)),0.5)*tan(last_one/2.0));
	theta[i] = t;
	}

	float haxis = pow(pow(T,2),1./3.);  //полуось
	for (int i = 0; i < points; i++){
		coo_orbita[i][0] =(haxis*(1-pow(e,2))/(1+e*cos(theta[i])))*cos(theta[i]);
		coo_orbita[i][1] = (haxis*(1-pow(e,2))/(1+e*cos(theta[i])))*sin(theta[i]);
	}
}

void __fastcall TForm5::Button1Click(TObject *Sender)
{
	HD_189733_A_b->Clear();
	STAR->Clear();
	TRAPPIST_1->Clear();
	TOI_700d->Clear();
	STAR->AddXY(0,0);
	float e,T;
	float theta[points];
	   if (CheckBox1->Checked) {
			T = 2.22;
			e = 0.0039;
			orbit_maden_by_Bonacci(e,T,theta);
			for (int i = 0; i < points; i++) {
				float x = coo_orbita[i][0];
				float y = coo_orbita[i][1];
				HD_189733_A_b->AddXY(x,y);
			}
	   }
	   if (CheckBox2->Checked) {
			float T0[7]={1.51,2.42,4.05,6.10,9.21,12.35,18.77};
			float e0[7] = {0.019,0.014,0.003,0.007,0.011,0.003,0.086};
			for (int i = 0; i < 7; i++) {
				orbit_maden_by_Bonacci(e0[i],T0[i],theta);
				for (int j = 0; j < points; j++) {
					float x = coo_orbita[j][0];
					float y = coo_orbita[j][1];
					TRAPPIST_1->AddXY(x,y);
				}
			}


	   }
	   if (CheckBox3->Checked) {
			T = 37.43;
			e = 0.032;
			orbit_maden_by_Bonacci(e,T,theta);
			for (int i = 0; i < points; i++) {
				float x = coo_orbita[i][0];
				float y = coo_orbita[i][1];
				TOI_700d->AddXY(x,y);
			}
		}
}

