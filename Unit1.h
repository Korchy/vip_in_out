//---------------------------------------------------------------------------
#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include "D:\Programms\Cpp\include\Options\Options.h"    // Для объекта "Настройки"
#include "registry.hpp" // Для работы с реестром
#include <jpeg.hpp>     // Нужен чтобы TImage работал с *.jpg файлами
#include "Math.hpp"     // Для использования математических функций
#include "Unit2.h"      // Для связи с Form2
#include "Unit3.h"      // Для связи с Form3
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

        // Переменные
        int c_CMessageShowTime; // Время показа CMessage (сек)
        int c_CodeShowTime;     // Время показа Code (сек)

        Options* Settings;      // Настройки программы

        enum {rCenter,rLeftTop,rLeftBottom,rRightTop,rRightBottom} MessagePlace;        // Место, где должно выводиться сообщение

        int CodeShowTime;       // Время показа окна ввода кода Code

        TList* CMessage;        // Текущее сообщение (реакция на что-либо) - Список состоящий из Label из которых сотавлен текст
        int CMessageShowTime;   // Время показа CMessage (в сек.)
        TList* MMessage;        // Главное сообщение (видно всегда в течение дня) - Список состоящий из Label из которых сотавлен текст

        int P_FonB_ShowTime;    // Время показа рисунка с поздравлением с днем рождения

        // Функции
        void FirstSetup();      // Проверка, есть ли в системе ODBC Alias для доступа к базе данных, если нет - создает его

        bool ComeInOut(AnsiString Code);        // Обработка прихода-ухода

        bool CreateCMessage(AnsiString Text);   // Создать сообщение CMessage
        bool ShowCMessage();    // Показать CMessage
        bool HideCMessage();    // Скрыть CMessage
        bool DeleteCMessage();  // Удалить CMessage
        bool CreateMMessage(AnsiString Text);   // Создать сообщение MMessage
        bool ShowMMessage();    // Показать MMessage
        bool HideMMessage();    // Скрыть MMessage
        bool DeleteMMessage();  // Удалить MMessage
        bool ShowP_Fon_b();     // Показать P_Fon_b
        bool HideP_Fon_b();     // Скрыть P_Fon_b (загрузить обычный фон)


};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
