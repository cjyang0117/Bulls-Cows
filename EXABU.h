//---------------------------------------------------------------------------

#ifndef EXABUH
#define EXABUH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Mask.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TLabel *LaOut1;
        TMaskEdit *Edi_A;
        TButton *But_In1;
        TGroupBox *GroupBox2;
        TLabel *LaOut2;
        TMaskEdit *Edi_In;
        TButton *But_In2;
        TMaskEdit *Edi_B;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *LaChange;
        void __fastcall But_In1Click(TObject *Sender);
        void __fastcall But_In2Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
