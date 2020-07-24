//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "EXABU.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
int AllAns[4536][4],PosAns[4536][4],  //輪流存放可能答案的兩陣列
    Ans_Com,Ans_Com1[4],              //電腦出的題目
    Ans_Ply,                          //玩家出的題目
    n,                                //n=random(4536)
    GTimes_Player=0,GTimes_Com=1,     //玩家遊戲次數與電腦遊戲次數
    y1[4],y,                          //分解Ans_Ply
    guess_com,guess_com1[4],          //電腦猜的答案與其存放答案的陣列
    a,b,                              //輸入電腦猜的ab
    ChangeAll=4536,                   //可能的答案 改變的總範圍
    Edi_In1=0,
    repeat[1000],repeat1,             //檢查是否輸入重複答案
    change=0;                         //陣列輪流存資料的判斷條件 AllAns偶數次 PosAns奇數次
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::But_In1Click(TObject *Sender)
{
  int na=0,nb=0;
  for(int i=0;i<4;i++){
    if(y1[i]==guess_com1[i]) na++;             //玩家出的題目與電腦猜得比較幾A幾B
    for(int j=0;j<4;j++){
      if(i!=j&&y1[i]==guess_com1[j]) nb++;
    }
  }

  a=Edi_A->Text.ToInt();
  b=Edi_B->Text.ToInt();
  if(a!=na||b!=nb){
    ShowMessage("你確定答案是"+IntToStr(a)+"A"+IntToStr(b)+"B嗎= =?");
    return;
  }
  LaOut1->Caption=LaOut1->Caption+IntToStr(a)+"A"+IntToStr(b)+"B"+"\n";

  int t=0;
  if(change%2==0){
    change++;
    for(int n=0;n<ChangeAll;n++){                //全部答案與電腦猜得做比較
      int na1=0,nb1=0;                           //將可能答案存入陣列
      for(int i=0;i<4;i++){                      //使電腦從中再猜一個答案
       if(AllAns[n][i]==guess_com1[i]) na1++;    //可能的答案第一次存在PosAns
        for(int j=0;j<4;j++){                    //下次存AllAns 輪流
          if(i!=j&&AllAns[n][i]==guess_com1[j]) nb1++;
        }
      }
      if(na1==a&&nb1==b){
        for(int l=0;l<4;l++){
          PosAns[t][l]=AllAns[n][l];
        }
        t++;
      }
    }
  }else{
    change++;
    for(int n=0;n<ChangeAll;n++){
      int na1=0,nb1=0;
      for(int i=0;i<4;i++){
        if(PosAns[n][i]==guess_com1[i]) na1++;
        for(int j=0;j<4;j++){
          if(i!=j&&PosAns[n][i]==guess_com1[j]) nb1++;
        }
      }
      if(na1==a&&nb1==b){
        for(int l=0;l<4;l++){
          AllAns[t][l]=PosAns[n][l];
        }
        t++;
      }
    }
  }

  ChangeAll=t;
  int c=random(ChangeAll);
  if(change%2==0){
    guess_com=1000*AllAns[c][0]+100*AllAns[c][1]+10*AllAns[c][2]+AllAns[c][3];
    guess_com1[0]=AllAns[c][0]; guess_com1[1]=AllAns[c][1]; guess_com1[2]=AllAns[c][2]; guess_com1[3]=AllAns[c][3];
  }else{
    guess_com=1000*PosAns[c][0]+100*PosAns[c][1]+10*PosAns[c][2]+PosAns[c][3];
    guess_com1[0]=PosAns[c][0]; guess_com1[1]=PosAns[c][1]; guess_com1[2]=PosAns[c][2]; guess_com1[3]=PosAns[c][3];
  }
  if(na!=4){
    GTimes_Com++;
    LaOut1->Caption=LaOut1->Caption+GTimes_Com+".\t"+IntToStr(guess_com)+"\t";
  }

  if(GTimes_Player!=0) Edi_In1=Edi_In->Text.ToInt();
  if(Edi_In1!=Ans_Com){                                //若另一方遊戲還沒結束
    GroupBox1->Enabled=false;                          //猜完將自己enabled關掉
    GroupBox2->Enabled=true;                           //打開另一邊換猜
    LaChange->Parent=GroupBox2;
  }

  if(a==4&&Edi_In1==Ans_Com){
    int c=GTimes_Com-GTimes_Player;
    switch(c){
      case 0:                                           //當兩人都4A
        ShowMessage("什麼!?竟然平分秋色!!");            //人獲勝越多評語越好
        break;
      case 1:
        ShowMessage("很厲害哦~贏了耶!");
        break;
      case 2:
        ShowMessage("真不愧是人腦~!!YEE級棒!!");
        break;
      case 3:
        ShowMessage("天阿太強了!~恭喜你贏了~");
        break;
      default:
        ShowMessage("你是作弊還是在Debug，怎麼可能贏這麼多次 = =?");
        break;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::But_In2Click(TObject *Sender)
{
  int x1[4],x3,na=0,nb=0,pre_guess[100];
  x3=Edi_In->Text.ToInt();
  for(int i=3;i>-1;i--){                //將人猜輸入的數字分解
    x1[i]=x3%10;
    x3=x3/10;
  }

  if(Edi_In->Text=="    "||x1[0]==x1[1]||x1[0]==x1[2]||x1[0]==x1[3]||x1[1]==x1[2]||x1[1]==x1[3]||x1[2]==x1[3]){
    ShowMessage("請輸入符合的四位數字!");
    return;
  }

  repeat[repeat1]=Edi_In->Text.ToInt();  repeat1++;
  for(int i=0;i<repeat1-1;i++){
    if(repeat[i]==Edi_In->Text.ToInt()){
      ShowMessage("這個數字之前輸入過了哦!");
      return;
    }
  }

  if(a!=4){
    GroupBox2->Enabled=false;             //還沒獲勝時
    GroupBox1->Enabled=true;              //猜完關掉自己BOX 打開另一邊
    LaChange->Parent=GroupBox1;
  }
  if(Edi_In1!=Ans_Com) GTimes_Player++;
  for(int i=0;i<4;i++){
    if(x1[i]==Ans_Com1[i]) na++;             //判斷玩家猜的答案是幾A幾B並顯示到遊戲紀錄
    for(int j=0;j<4;j++){
      if(i!=j&&x1[i]==Ans_Com1[j]) nb++;
    }
  }
  LaOut2->Caption=LaOut2->Caption+IntToStr(GTimes_Player)+".\t"+Edi_In->Text+"\t"+IntToStr(na)+"A"+IntToStr(nb)+"B"+"\n";

  if(GTimes_Player!=0) Edi_In1=Edi_In->Text.ToInt();
  if(a==4&&Edi_In1==Ans_Com){
    int c=GTimes_Player-GTimes_Com;
    switch(c){
      case 0:
        ShowMessage("什麼!?竟然平分秋色!!");
        break;
      case 1:
        ShowMessage("很厲害哦~差點就贏電腦了");        //兩方獲勝時跳出評語
        break;                                         //玩家輸越多評語越差
      case 2:
        ShowMessage("可惜啊差兩次而已!!");
        break;
      case 3:
        ShowMessage("加油加油~輸了三次捏!!");
        break;
      case 4:
        ShowMessage("真可惜~下次再加油");
        break;
      case 5:
      case 6:
        ShowMessage("在加一把勁阿~");
        break;
      case 7:
        ShowMessage("有點差距欸~");
        break;
      case 8:
      case 9:
        ShowMessage("加油加油啦");
        break;
      case 10:
      case 11:
        ShowMessage("差有點多喔!");
        break;
      case 12:
      case 13:
        ShowMessage("你在睡覺嘛!?");
        break;
      case 14:
      default:
        ShowMessage("弱爆啦!");
        break;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
  randomize();
  GroupBox2->Enabled=false;
  GroupBox1->Enabled=true;       //一開始由電腦先猜 玩家BOX關起來
  LaChange->Parent=GroupBox1;

  int All=0;
  for(int i=1;i<10;i++){
    for(int j=0;j<10;j++){
      if(i==j) continue;
      for(int m=0;m<10;m++){
        if(i==m||j==m) continue;           //跑完所有符合不重複的四位數字
        for(int n=0;n<10;n++){             //並存到陣列中
          if(i==n||j==n||m==n) continue;
          AllAns[All][3]=n;
          AllAns[All][2]=m;
          AllAns[All][1]=j;
          AllAns[All][0]=i;
          All++;
        }
      }
    }
  }
  n=random(4536);
  Ans_Com=1000*AllAns[n][0]+100*AllAns[n][1]+10*AllAns[n][2]+AllAns[n][3];      //電腦隨機 並把四個數字分解
  Ans_Com1[0]=AllAns[n][0]; Ans_Com1[1]=AllAns[n][1]; Ans_Com1[2]=AllAns[n][2]; Ans_Com1[3]=AllAns[n][3];
  //Form1->Caption=IntToStr(Ans_Com);       //提示答案

  int t=0;
  do{
    if(t>0){
      ShowMessage("請勿輸入不符合的四位數或超過四位數字");
    }
    Ans_Ply=StrToInt(InputBox("請出題","請輸入不重複的四位數","1023"));     //玩家出題
    y=Ans_Ply;                                                              //輸入的數字不可重複不可超過四位
    for(int i=3;i>-1;i--){                                                  //若超過將跳不出迴圈
      y1[i]=y%10;                                                           //直到出符合的題目
      y=y/10;
    }
    t++;
  }while(y1[0]==y1[1]||y1[0]==y1[2]||y1[0]==y1[3]||y1[1]==y1[2]||y1[1]==y1[3]||y1[2]==y1[3]||Ans_Ply>9877||Ans_Ply<1023); 

  n=random(4536);
  guess_com=1000*AllAns[n][0]+100*AllAns[n][1]+10*AllAns[n][2]+AllAns[n][3];   //電腦隨機猜一答案 並把電腦猜的四位數字分解
  guess_com1[0]=AllAns[n][0]; guess_com1[1]=AllAns[n][1]; guess_com1[2]=AllAns[n][2]; guess_com1[3]=AllAns[n][3];
  LaOut1->Caption=LaOut1->Caption+GTimes_Com+".\t"+IntToStr(guess_com)+"\t";
}
//---------------------------------------------------------------------------
