//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
Form1->Connection->GetTableNames(Tables->Items,false);
Tables->ItemIndex = 0;
TablesChange(Form2);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormDestroy(TObject *Sender)
{
        // Çàêðûòü ÁÄ
Form1->Database->Close();
Form1->Database->SQL->Clear();
}
//---------------------------------------------------------------------------
//                              ÐÀÁÎÒÀ Ñ ÒÀÁËÈÖÀÌÈ
//---------------------------------------------------------------------------
void __fastcall TForm2::TablesChange(TObject *Sender)
{
        // Ïåðåêëþ÷åíèå ìåæäó òàáëèöàìè
Form1->Database->Close();
DBMemo->DataField = "";
Form1->Database->SQL->Clear();
Form1->Database->SQL->Add("SELECT * FROM "+Tables->Items->Strings[Tables->ItemIndex]);
try {
        Form1->Database->Open();       // Database->ExecSQL();
        }
catch(...){
        Form1->Database->Close();
        ShowMessage("Îøèáêà ðàáîòû ïðîãðàììû!");
        return;
        }
        // Memo - ïîëå
if(Tables->Items->Strings[Tables->ItemIndex]=="messages") DBMemo->DataField = "message";
}
//---------------------------------------------------------------------------
//                        ÂÛÕÎÄ ÈÇ ÐÅÄÀÊÒÈÐÎÂÀÍÈß ÒÀÁËÈÖ
//---------------------------------------------------------------------------
void __fastcall TForm2::CloseButtonClick(TObject *Sender)
{
        // Êí. ÇÀÊÐÛÒÜ
DBMemo->DataField = "";
        // Ïåðåñîçäàòü ãëàâíîå ñîîáùåíèå ò.ê. îíî ìîæåò áûòü èçìåíåíî
Form1->CreateMMessage("");
Form1->ShowMMessage();
        // Çàêðûòî îêíî
Form2->Close();
}
//---------------------------------------------------------------------------

