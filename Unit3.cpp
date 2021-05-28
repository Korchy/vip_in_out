//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm3::FormDestroy(TObject *Sender)
{
        // ���� ���� ���� ������� - ������� ��
Form1->Database->Close();
Form1->Database->SQL->Clear();
}
//---------------------------------------------------------------------------
//                              �������� ������
//---------------------------------------------------------------------------
void __fastcall TForm3::FormButtonClick(TObject *Sender)
{
        // ������������ �����
if(Code->Text=="") {    // �� ������ ���
        Code->SetFocus();
        return;
        }
        // �������� �� �.�. ������
Form1->Database->Close();
Form1->Database->SQL->Clear();
Form1->Database->SQL->Add("SELECT personal.code,personal.name_i,personal.family_i,personal.parent_i,personal.work_time,personal.dinner_time,inout.in_date,inout.in_time,inout.out_date,inout.out_time FROM personal left outer join inout on personal.code=inout.code where (personal.code=:P_Code)and(inout.in_date>=:P_InDate)and(inout.in_date<=:P_InDate1)");
Form1->Database->Parameters->ParamByName("P_Code")->Value = Code->Text;
Form1->Database->Parameters->ParamByName("P_InDate")->Value = StartDate->Date;
Form1->Database->Parameters->ParamByName("P_InDate1")->Value = EndDate->Date;
try {
        Form1->Database->Open();       // Database->ExecSQL();
        }
catch(...){
        Form1->Database->Close();
        ShowMessage("������ ������ ���������!");
        return;
        }
//ShowMessage(IntToStr(Form1->Database->RecordCount));
        // ������� ����� � HTML
HtmlReport* Report = new HtmlReport();
//Report->Path = GetCurrentDir+"\\Reports\\";
Report->Path = Form1->Settings->FindByName("ReportsDir");
Report->Name = Code->Text+"_"+DateToStr(StartDate->Date)+"_"+DateToStr(EndDate->Date);
Report->New();
Report->Add("<h1><b><i>����� � ������������</i></b></h1>");
Report->Add("<HR>");
Report->Add("<h4><b><i>�������� ������ ��: "+DateToStr(StartDate->Date)+" - "+DateToStr(EndDate->Date)+"</i></b></h4>");
Report->Add("<HR>");
Form1->Database->First();
AnsiString IspCode = "";
Report->Add("<pre>\n");
while(!Form1->Database->Eof) {
        IspCode = Form1->Database->FieldByName("code")->AsString;
        double Total = 0.0;
        Report->Add("<b><i>"+Form1->Database->FieldByName("family_i")->AsString+" "+Form1->Database->FieldByName("name_i")->AsString+" "+Form1->Database->FieldByName("parent_i")->AsString+"</i></b><p>");
        while(Form1->Database->FieldByName("code")->AsString==IspCode&&!Form1->Database->Eof) {
                AnsiString TmpText = "";
                TmpText += "������: "+Form1->Database->FieldByName("in_date")->AsString+" "+TimeToStr(Form1->Database->FieldByName("in_time")->AsDateTime);
                TmpText += "\t";
                TmpText += "����: "+Form1->Database->FieldByName("out_date")->AsString+" "+TimeToStr(Form1->Database->FieldByName("out_time")->AsDateTime);
                TmpText += "\t";
                TmpText += "���������� �� ����: "+TimeToStr(Form1->Database->FieldByName("out_time")->AsDateTime - Form1->Database->FieldByName("in_time")->AsDateTime);
                TmpText += "\t";
                TmpText += "������� �����: "+TimeToStr(Form1->Database->FieldByName("work_time")->AsDateTime + Form1->Database->FieldByName("dinner_time")->AsDateTime);
                TmpText += "\t";
                TmpText += "���� �� ����:";
                TDateTime a = Form1->Database->FieldByName("work_time")->AsDateTime + Form1->Database->FieldByName("dinner_time")->AsDateTime - (Form1->Database->FieldByName("out_time")->AsDateTime - Form1->Database->FieldByName("in_time")->AsDateTime);
                if(StrToFloat(FloatToStr(a))>0.0) {
                        TmpText += " -";
                        Total -= (double)a;
                        }
                else {
                        TmpText += " +";
                        Total += (double)a;
                        }
                TmpText += TimeToStr(a);

                Report->Add(TmpText);
                Form1->Database->Next();
                IspCode = Form1->Database->FieldByName("code")->AsString;
                }
        Report->Add("<hr align=left dotted width=50%>");
        ShowMessage(FloatToStr(Total));
        if((double)Total>0.0) Report->Add("�����: ����������� "+IntToStr(abs((int)Total))+" �. "+TimeToStr(Total));
        else Report->Add("�����:  ����������� "+IntToStr(abs((int)Total))+" �. "+TimeToStr(Total));
        }
Report->Add("<\pre>\n");
Report->Save();
Report->Show();
delete Report;
Form1->Database->Close();
}
//---------------------------------------------------------------------------
