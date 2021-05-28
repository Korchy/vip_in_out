//---------------------------------------------------------------------------
#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include "D:\Programms\Cpp\include\Options\Options.h"    // ��� ������� "���������"
#include "registry.hpp" // ��� ������ � ��������
#include <jpeg.hpp>     // ����� ����� TImage ������� � *.jpg �������
#include "Math.hpp"     // ��� ������������� �������������� �������
#include "Unit2.h"      // ��� ����� � Form2
#include "Unit3.h"      // ��� ����� � Form3
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TImage *P_Fon;
        TADOQuery *Database;
        TDataSource *Data;
        TTimer *Timer;
        TADOConnection *Connection;
        TLabel *ClockMessage;
        TLabeledEdit *Code;
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall TimerTimer(TObject *Sender);
        void __fastcall CodeKeyPress(TObject *Sender, char &Key);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);

        // ����������
        int c_CMessageShowTime; // ����� ������ CMessage (���)
        int c_CodeShowTime;     // ����� ������ Code (���)

        Options* Settings;      // ��������� ���������

        enum {rCenter,rLeftTop,rLeftBottom,rRightTop,rRightBottom} MessagePlace;        // �����, ��� ������ ���������� ���������

        int CodeShowTime;       // ����� ������ ���� ����� ���� Code

        TList* CMessage;        // ������� ��������� (������� �� ���-����) - ������ ��������� �� Label �� ������� �������� �����
        int CMessageShowTime;   // ����� ������ CMessage (� ���.)
        TList* MMessage;        // ������� ��������� (����� ������ � ������� ���) - ������ ��������� �� Label �� ������� �������� �����

        int P_FonB_ShowTime;    // ����� ������ ������� � ������������� � ���� ��������

        // �������
        void FirstSetup();      // ��������, ���� �� � ������� ODBC Alias ��� ������� � ���� ������, ���� ��� - ������� ���

        bool ComeInOut(AnsiString Code);        // ��������� �������-�����

        bool CreateCMessage(AnsiString Text);   // ������� ��������� CMessage
        bool ShowCMessage();    // �������� CMessage
        bool HideCMessage();    // ������ CMessage
        bool DeleteCMessage();  // ������� CMessage
        bool CreateMMessage(AnsiString Text);   // ������� ��������� MMessage
        bool ShowMMessage();    // �������� MMessage
        bool HideMMessage();    // ������ MMessage
        bool DeleteMMessage();  // ������� MMessage
        bool ShowP_Fon_b();     // �������� P_Fon_b
        bool HideP_Fon_b();     // ������ P_Fon_b (��������� ������� ���)


};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
