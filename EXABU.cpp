//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "EXABU.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
int AllAns[4536][4],PosAns[4536][4],  //���y�s��i�൪�ת���}�C
    Ans_Com,Ans_Com1[4],              //�q���X���D��
    Ans_Ply,                          //���a�X���D��
    n,                                //n=random(4536)
    GTimes_Player=0,GTimes_Com=1,     //���a�C�����ƻP�q���C������
    y1[4],y,                          //����Ans_Ply
    guess_com,guess_com1[4],          //�q���q�����׻P��s�񵪮ת��}�C
    a,b,                              //��J�q���q��ab
    ChangeAll=4536,                   //�i�઺���� ���ܪ��`�d��
    Edi_In1=0,
    repeat[1000],repeat1,             //�ˬd�O�_��J���Ƶ���
    change=0;                         //�}�C���y�s��ƪ��P�_���� AllAns���Ʀ� PosAns�_�Ʀ�
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
    if(y1[i]==guess_com1[i]) na++;             //���a�X���D�ػP�q���q�o����XA�XB
    for(int j=0;j<4;j++){
      if(i!=j&&y1[i]==guess_com1[j]) nb++;
    }
  }

  a=Edi_A->Text.ToInt();
  b=Edi_B->Text.ToInt();
  if(a!=na||b!=nb){
    ShowMessage("�A�T�w���׬O"+IntToStr(a)+"A"+IntToStr(b)+"B��= =?");
    return;
  }
  LaOut1->Caption=LaOut1->Caption+IntToStr(a)+"A"+IntToStr(b)+"B"+"\n";

  int t=0;
  if(change%2==0){
    change++;
    for(int n=0;n<ChangeAll;n++){                //�������׻P�q���q�o�����
      int na1=0,nb1=0;                           //�N�i�൪�צs�J�}�C
      for(int i=0;i<4;i++){                      //�Ϲq���q���A�q�@�ӵ���
       if(AllAns[n][i]==guess_com1[i]) na1++;    //�i�઺���ײĤ@���s�bPosAns
        for(int j=0;j<4;j++){                    //�U���sAllAns ���y
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
  if(Edi_In1!=Ans_Com){                                //�Y�t�@��C���٨S����
    GroupBox1->Enabled=false;                          //�q���N�ۤvenabled����
    GroupBox2->Enabled=true;                           //���}�t�@�䴫�q
    LaChange->Parent=GroupBox2;
  }

  if(a==4&&Edi_In1==Ans_Com){
    int c=GTimes_Com-GTimes_Player;
    switch(c){
      case 0:                                           //���H��4A
        ShowMessage("����!?���M�������!!");            //�H��ӶV�h���y�V�n
        break;
      case 1:
        ShowMessage("�ܼF�`�@~Ĺ�F�C!");
        break;
      case 2:
        ShowMessage("�u���\�O�H��~!!YEE�Ŵ�!!");
        break;
      case 3:
        ShowMessage("�Ѫ��ӱj�F!~���ߧAĹ�F~");
        break;
      default:
        ShowMessage("�A�O�@���٬O�bDebug�A���i��Ĺ�o��h�� = =?");
        break;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::But_In2Click(TObject *Sender)
{
  int x1[4],x3,na=0,nb=0,pre_guess[100];
  x3=Edi_In->Text.ToInt();
  for(int i=3;i>-1;i--){                //�N�H�q��J���Ʀr����
    x1[i]=x3%10;
    x3=x3/10;
  }

  if(Edi_In->Text=="    "||x1[0]==x1[1]||x1[0]==x1[2]||x1[0]==x1[3]||x1[1]==x1[2]||x1[1]==x1[3]||x1[2]==x1[3]){
    ShowMessage("�п�J�ŦX���|��Ʀr!");
    return;
  }

  repeat[repeat1]=Edi_In->Text.ToInt();  repeat1++;
  for(int i=0;i<repeat1-1;i++){
    if(repeat[i]==Edi_In->Text.ToInt()){
      ShowMessage("�o�ӼƦr���e��J�L�F�@!");
      return;
    }
  }

  if(a!=4){
    GroupBox2->Enabled=false;             //�٨S��Ӯ�
    GroupBox1->Enabled=true;              //�q�������ۤvBOX ���}�t�@��
    LaChange->Parent=GroupBox1;
  }
  if(Edi_In1!=Ans_Com) GTimes_Player++;
  for(int i=0;i<4;i++){
    if(x1[i]==Ans_Com1[i]) na++;             //�P�_���a�q�����׬O�XA�XB����ܨ�C������
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
        ShowMessage("����!?���M�������!!");
        break;
      case 1:
        ShowMessage("�ܼF�`�@~�t�I�NĹ�q���F");        //�����Ӯɸ��X���y
        break;                                         //���a��V�h���y�V�t
      case 2:
        ShowMessage("�i���ڮt�⦸�Ӥw!!");
        break;
      case 3:
        ShowMessage("�[�o�[�o~��F�T����!!");
        break;
      case 4:
        ShowMessage("�u�i��~�U���A�[�o");
        break;
      case 5:
      case 6:
        ShowMessage("�b�[�@��l��~");
        break;
      case 7:
        ShowMessage("���I�t�Z��~");
        break;
      case 8:
      case 9:
        ShowMessage("�[�o�[�o��");
        break;
      case 10:
      case 11:
        ShowMessage("�t���I�h��!");
        break;
      case 12:
      case 13:
        ShowMessage("�A�b��ı��!?");
        break;
      case 14:
      default:
        ShowMessage("�z�z��!");
        break;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
  randomize();
  GroupBox2->Enabled=false;
  GroupBox1->Enabled=true;       //�@�}�l�ѹq�����q ���aBOX���_��
  LaChange->Parent=GroupBox1;

  int All=0;
  for(int i=1;i<10;i++){
    for(int j=0;j<10;j++){
      if(i==j) continue;
      for(int m=0;m<10;m++){
        if(i==m||j==m) continue;           //�]���Ҧ��ŦX�����ƪ��|��Ʀr
        for(int n=0;n<10;n++){             //�æs��}�C��
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
  Ans_Com=1000*AllAns[n][0]+100*AllAns[n][1]+10*AllAns[n][2]+AllAns[n][3];      //�q���H�� �ç�|�ӼƦr����
  Ans_Com1[0]=AllAns[n][0]; Ans_Com1[1]=AllAns[n][1]; Ans_Com1[2]=AllAns[n][2]; Ans_Com1[3]=AllAns[n][3];
  //Form1->Caption=IntToStr(Ans_Com);       //���ܵ���

  int t=0;
  do{
    if(t>0){
      ShowMessage("�Фſ�J���ŦX���|��ƩζW�L�|��Ʀr");
    }
    Ans_Ply=StrToInt(InputBox("�ХX�D","�п�J�����ƪ��|���","1023"));     //���a�X�D
    y=Ans_Ply;                                                              //��J���Ʀr���i���Ƥ��i�W�L�|��
    for(int i=3;i>-1;i--){                                                  //�Y�W�L�N�����X�j��
      y1[i]=y%10;                                                           //����X�ŦX���D��
      y=y/10;
    }
    t++;
  }while(y1[0]==y1[1]||y1[0]==y1[2]||y1[0]==y1[3]||y1[1]==y1[2]||y1[1]==y1[3]||y1[2]==y1[3]||Ans_Ply>9877||Ans_Ply<1023); 

  n=random(4536);
  guess_com=1000*AllAns[n][0]+100*AllAns[n][1]+10*AllAns[n][2]+AllAns[n][3];   //�q���H���q�@���� �ç�q���q���|��Ʀr����
  guess_com1[0]=AllAns[n][0]; guess_com1[1]=AllAns[n][1]; guess_com1[2]=AllAns[n][2]; guess_com1[3]=AllAns[n][3];
  LaOut1->Caption=LaOut1->Caption+GTimes_Com+".\t"+IntToStr(guess_com)+"\t";
}
//---------------------------------------------------------------------------
