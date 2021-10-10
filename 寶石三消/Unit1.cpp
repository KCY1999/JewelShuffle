//---------------------------------------------------------------------------
#include <vcl.h>
#include <time.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include<stdio.h>
#define len 4
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int rnd[len][len],pnum[len][len],com[len][len];
TImage *img[len][len];
AnsiString str,strr;
int val=0,count=0; //判斷點擊次數 //寶石量數 //能否消除  rm=0
int x,y,z,a,b,rd,tm;
int tmp=0,tmp2=0,tmpp=0,tmpp2=0,ck=30;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FortimemCreate(TObject *Sender) //Rnd
{
	time_t t;
	srand((unsigned)time(&t));
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	Timer1->Enabled=true;
	Button1->Enabled=false;
	Button2->Enabled=true;
	for(int i=0;i<len;i++)
	{
		str="";
		for(int j=0;j<len;j++)
		{
			rnd[i][j] = (rand()%(6-1+1))+1;
			str += AnsiString(rnd[i][j]);
			if(img[i][j]!=NULL)
			{
				ShowMessage("error");
				return;
			}
			img[i][j]=new TImage(this);
			img[i][j]->Top=100+((i)*50);
			img[i][j]->Left=100+(j*50);
			img[i][j]->Tag=(i*len)+(j+1);
			img[i][j]->OnClick=swap;
			img[i][j]->Parent=this;
			img[i][j]->Picture->LoadFromFile(AnsiString(rnd[i][j])+".png");
		}
		   Form2->Memo1->Lines->Add(str);//顯示確認
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
	for(int i=0;i<len*len;i++)
	{
		img[i/len][i%len]=NULL;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::swap(TObject *Sender)
{
  TImage *img1;
  img1=(TImage *)Sender;
  AnsiString stt = AnsiString(img1->Tag); //TAG
  val++;
  Timer2->Enabled=true;
	if(val==1)  //判斷點擊
	{
		tmp = StrToInt(stt);
		x = tmp-1, z = tmp+1, a = tmp-len, b = tmp+len; //位置
		tmp2 = rnd[x/len][x%len];     //Tag對應之檔名
		Edit1->Text = tmp;
		Edit3->Text = tmp2;
	}
	else if(val==2)
	{
		tmpp = StrToInt(stt);
		y = tmpp-1;
		tmpp2 = rnd[y/len][y%len];
		val=3;
		Edit2->Text = tmpp;
		Edit4->Text = tmpp2;
		if(tmpp==x||tmpp==z||tmpp==a||tmpp==b)
		{
			img[x/len][x%len]->Picture->LoadFromFile(AnsiString(tmpp2)+".png");
			img[y/len][y%len]->Picture->LoadFromFile(AnsiString(tmp2)+".png");
			rnd[x/len][x%len] = tmpp2;
			rnd[y/len][y%len] = tmp2;
			line();
		}
		else
		{
			ShowMessage("取消");
			val = 0;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
	for(int i=0;i<len*len;i++)
	{
		if(img[i/len][i%len]!=NULL)
		{
			delete img[i/len][i%len];
			img[i/len][i%len]=NULL;
		}
	}
}
//---------------------------------------------------------------------------
void TForm1::line()
{
	int cb=0;
	for(int i=0;i<len;i++)
	{
		for(int j=0;j<len;j++)
		{
			if(j+2<len&&rnd[i][j]==rnd[i][j+1]&&rnd[i][j]==rnd[i][j+2])
			{
				pnum[i][j]=1;
				pnum[i][j+1]=1;
				pnum[i][j+2]=1;
				cb=1;
			}
			if(i+2<len&&rnd[i][j]==rnd[i+1][j]&&rnd[i][j]==rnd[i+2][j])
			{
				pnum[i][j]=1;
				pnum[i+1][j]=1;
				pnum[i+2][j]=1;
				cb=1;
			}
		}
	}
	for(int i=0;i<len;i++)
	{
		for(int j=0;j<len;j++)
		{
			if(pnum[i][j]==1)
			{
				img[i][j]->Picture->LoadFromFile("0.png");
				pnum[i][j]=1;
				rnd[i][j]=0;
			}
		}
	}
    for(int i=len-1;i>=0;i--)
	{
		for(int j=0;j<len;j++)
		{
			int up=1,down=0;
			if(rnd[i][j]==0)
			{
				while(i-up>=0&&down==0)
				{
					if(rnd[i-up][j]!=0)
					{
						down=1;
					}
					if(rnd[i-up][j]==0)
					{
						up+=1;
					}
				}
				if(down==1)
				{
                    rnd[i][j] = rnd[i-up][j];
					img[i][j]->Picture->LoadFromFile(IntToStr(rnd[i-up][j])+".png");
					rnd[i-up][j]=0;
					pnum[i][j]=0;
					img[i-up][j]->Picture->LoadFromFile("0.png");
					Timer2->Enabled=true;
				}
			}
		}
	}
	for(int i=0;i<len;i++)
	{
		for(int j=0;j<len;j++)
		{
			if(i<len&&rnd[i][j]==0)
			{
				int rd;
				rd=(rand()%(6-1+1))+1;
				img[i][j]->Picture->LoadFromFile(IntToStr(rd)+".png");
				rnd[i][j]=rd;
				pnum[i][j]=0;
			}
		}
	}
	if(cb==0&&val==3)
	{
	dis();
		img[x/len][x%len]->Picture->LoadFromFile(AnsiString(tmp2)+".png");
		img[y/len][y%len]->Picture->LoadFromFile(AnsiString(tmpp2)+".png");
		rnd[x/len][x%len] = tmp2;
		rnd[y/len][y%len] = tmpp2;
		val=0;
	}
	else if(val==3)
	{
		val=0;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
	line();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Debug1Click(TObject *Sender)
{
	Form2->Top=Form1->Top;
	Form2->Left=Form1->Left+Form1->Width+10;
	Form2->Show();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
	for(int i=0;i<len;i++)
	{
		strr="";
		for(int j=0;j<len;j++)
		{
			strr += AnsiString(rnd[i][j]);  //rnd
			strr += " ";
		}
		Form2->Memo2->Lines->Add(strr);  //顯示確認
	}
	Form2->Memo2->Lines->Add(" ");
	Timer2->Enabled=false;
}
//---------------------------------------------------------------------------
void TForm1::dis()
{
	int rm=1;
	for(int i=0;i<len;i++)
	{
		for(int j=0;j<len;j++)
		{
			com[i][j]=rnd[i][j];
		}
	}
	for(int k=0;k<len*len;k++)
	{
		if((k%len)+1<len)
		{
			tm=com[(k%len)][(k/len)];
			com[(k%len)][(k/len)]=com[(k%len)+1][(k/len)];
			com[(k%len)+1][(k/len)]=tm;
		}
		for(int i=0;i<len;i++)
		{
			for(int j=0;j<len;j++)
			{

				if(j+2<len&&com[i][j]==com[i][j+1]&&com[i][j]==com[i][j+2])
				{
					rm=0;
				}
				if(i+2<len&&com[i][j]==com[i+1][j]&&com[i][j]==com[i+2][j])
				{
					rm=0;
				}
			}
		}
		if((k%len)+1<len)
		{
			tm=com[(k%len)][(k/len)];
			com[(k%len)][(k/len)]=com[(k%len)+1][(k/len)];
			com[(k%len)+1][(k/len)]=tm;
		}
		if((k%len)-1>=0)
		{
			tm=com[(k%len)][(k/len)];
			com[(k%len)][(k/len)]=com[(k%len)-1][(k/len)];
			com[(k%len)-1][(k/len)]=tm;
		}
		for(int i=0;i<len;i++)
		{
			for(int j=0;j<len;j++)
			{
				if(j+2<len&&com[i][j]==com[i][j+1]&&com[i][j]==com[i][j+2])
				{
					rm=0;
				}
				if(i+2<len&&com[i][j]==com[i+1][j]&&com[i][j]==com[i+2][j])
				{
					rm=0;
				}
			}
		}
		if((k%len)-1>=0)
		{
			tm=com[(k%len)][(k/len)];
			com[(k%len)][(k/len)]=com[(k%len)-1][(k/len)];
			com[(k%len)-1][(k/len)]=tm;
		}
		if((k/len)+1<len)
		{
			tm=com[(k%len)][(k/len)];
			com[(k%len)][(k/len)]=com[(k%len)][(k/len)+1];
			com[(k%len)][(k/len)+1]=tm;
		}
		for(int i=0;i<len;i++)
		{
			for(int j=0;j<len;j++)
			{
				if(j+1<len)
				{
					tm=com[i][j];
					com[i][j]=com[i][j+1];
					com[i][j+1]=tm;
				}
				if(j+2<len&&com[i][j]==com[i][j+1]&&com[i][j]==com[i][j+2])
				{
					rm=0;
				}
				if(i+2<len&&com[i][j]==com[i+1][j]&&com[i][j]==com[i+2][j])
				{
					rm=0;
				}
			}
		}
		if((k/len)+1<len)
		{
			tm=com[(k%len)][(k/len)];
			com[(k%len)][(k/len)]=com[(k%len)][(k/len)+1];
			com[(k%len)][(k/len)+1]=tm;
		}
		for(int i=0;i<len;i++)
		{
			for(int j=0;j<len;j++)
			{
				if(j-1>=0)
				{
					tm=com[i][j];
					com[i][j]=com[i][j-1];
					com[i][j-1]=tm;
				}
				if(j+2<len&&com[i][j]==com[i][j+1]&&com[i][j]==com[i][j+2])
				{
					rm=0;
				}
				if(i+2<len&&com[i][j]==com[i+1][j]&&com[i][j]==com[i+2][j])
				{
					rm=0;
				}
			}
		}
		if((k/len)+1<len)
		{
			tm=com[(k%len)][(k/len)];
			com[(k%len)][(k/len)]=com[(k%len)][(k/len)+1];
			com[(k%len)][(k/len)+1]=tm;
		}
	}
	if(rm==1)
	{
		Timer1->Enabled=false;
		ShowMessage("結束");
		rm=0;
	}
}
//--------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	ShowMessage("歸還記憶體成功");
	Button2->Enabled=false;
	Button1->Enabled=true;
	str="",strr="";
	val=0,count=0,x=0,y=0,z=0,a=0,b=0,rd=0;
	tmp=0,tmp2=0,tmpp=0,tmpp2=0;
	Edit1->Text = tmp;Edit2->Text = tmp2;Edit3->Text = tmpp;Edit4->Text = tmpp2;
	Form2->Memo1->Lines->Clear();
	Form2->Memo2->Lines->Clear();
	for(int i=0;i<len;i++)
	{
		for(int j=0;j<len;j++)
		{
			if(img[i][j]==NULL)
			{
				ShowMessage("error");
				return;
			}
			delete img[i][j];
			img[i][j]=NULL;
			pnum[i][j]=0;
		}
	}
}
//---------------------------------------------------------------------------

