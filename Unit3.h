//---------------------------------------------------------------------------
#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------
#include "Unit1.h"      // Для связи с Form1
#include "D:\Programms\Cpp\include\HTMLReport\HtmlReport.h"    // Для объекта HTMLReport
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE-managed Components
        TLabeledEdit *Code;
        TDateTimePicker *StartDate;
        TLabel *Label1;
        TDateTimePicker *EndDate;
        TLabel *Label2;
        TButton *FormButton;
        void __fastcall FormButtonClick(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm3(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
