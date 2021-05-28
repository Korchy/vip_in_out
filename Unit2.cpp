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
        // ������� ��
Form1->Database->Close();
Form1->Database->SQL->Clear();
}
//---------------------------------------------------------------------------
//                              ������ � ���������
//---------------------------------------------------------------------------
void __fastcall TForm2::TablesChange(TObject *Sender)
{
        // ������������ ����� ���������
Form1->Database->Close();
DBMemo->DataField = "";
Form1->Database->SQL->Clear();
Form1->Database->SQL->Add("SELECT * FROM "+Tables->Items->Strings[Tables->ItemIndex]);
try {
        Form1->Database->Open();       // Database->ExecSQL();
        }
catch(...){
        Form1->Database->Close();
        ShowMessage("������ ������ ���������!");
        return;
        }
        // Memo - ����
if(Tables->Items->Strings[Tables->ItemIndex]=="messages") DBMemo->DataField = "message";
}
//---------------------------------------------------------------------------
//                        ����� �� �������������� ������
//---------------------------------------------------------------------------
void __fastcall TForm2::CloseButtonClick(TObject *Sender)
{
        // ��. �������
DBMemo->DataField = "";
        // ����������� ������� ��������� �.�. ��� ����� ���� ��������
Form1->CreateMMessage("");
Form1->ShowMMessage();
        // ������� ����
Form2->Close();
}
//---------------------------------------------------------------------------

