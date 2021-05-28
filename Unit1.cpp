//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
        // При создании формы
        // Постоянные
c_CMessageShowTime = 15;
c_CodeShowTime = 10;
        // Загрузить настройки
Settings = new Options();
Settings->File = "in_out.cfg";
if(Settings->Load()==true) {
        Form1->Top = StrToInt(Settings->FindByName("FormTop"));
        Form1->Left = StrToInt(Settings->FindByName("FormLeft"));
        Form1->Width = StrToInt(Settings->FindByName("FormWidth"));
        Form1->Height = StrToInt(Settings->FindByName("FormHeight"));
        switch (StrToInt(Settings->FindByName("FormStyle"))) {
                case 0: Form1->WindowState = wsNormal;
                        break;
                case 1: Form1->WindowState = wsMaximized;
                        break;
                case 2: Form1->WindowState = wsMinimized;
                        break;
                }
        }
        // Проверить, есть-ли Alias для доступа к базе данных
FirstSetup();
        // Загрузить оформление
HideP_Fon_b();
        // Установить дату-время
AnsiString TmpDT = "";
DateTimeToString(TmpDT,"dddd  hh:nn  d mmmm yyy",Now());
ClockMessage->Caption = TmpDT;
        // Место для сообщений
CMessage = new TList();
MMessage = new TList();
CreateMMessage("");
ShowMMessage();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormDestroy(TObject *Sender)
{
        // При закрытии формы
        // Удалить окна сообщений, если они есть
if(CMessage!=NULL) {
        DeleteCMessage();
        delete CMessage;
        }
if(MMessage!=NULL) {
        DeleteMMessage();
        delete MMessage;
        }
        // Сохранить настройки
if(Form1->WindowState==wsNormal) {
        Settings->SetByName("FormStyle","0");
        Settings->SetByName("FormTop",IntToStr(Form1->Top));
        Settings->SetByName("FormLeft",IntToStr(Form1->Left));
        Settings->SetByName("FormWidth",IntToStr(Form1->Width));
        Settings->SetByName("FormHeight",IntToStr(Form1->Height));
        }
if(Form1->WindowState==wsMaximized) Settings->SetByName("FormStyle","1");
if(Form1->WindowState==wsMinimized) Settings->SetByName("FormStyle","2");
Settings->Save();
        // Удалить объект с настройками
delete Settings;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormResize(TObject *Sender)
{
        // При изменении размеров формы
        // Окно ввода кода
Code->Font->Size = Floor(Form1->Width/50);
Code->Width = Form1->Width/5;
Code->Left = Form1->Width/2-Code->Width/2;
Code->Top = Form1->Height/2-Code->Height/2;
        // Окна вывода сообщений
        // Центральное собщение CMessage
if(CMessage!=NULL&&CMessage->Count!=0) {
        // Top
        int TmpHeight = 0;
        for(int i=0; i<CMessage->Count; i++) {
                TmpHeight += ((TLabel*)CMessage->Items[i])->Height;
                }
        // Определим Top для каждой Label в CMessage
        ((TLabel*)CMessage->Items[0])->Top = (Form1->Height-TmpHeight)/2;      // Первая Label - отцентрировать по высоте окна, остальные - по ней
        for(int i=1; i<CMessage->Count; i++) {
                ((TLabel*)CMessage->Items[i])->Top = ((TLabel*)CMessage->Items[i-1])->Top+((TLabel*)CMessage->Items[i-1])->Height;
                }
        }
        // Главное собщение MMessage
if(MMessage!=NULL&&MMessage->Count!=0) {
        // Top
        int TmpHeight = 0;
        for(int i=0; i<MMessage->Count; i++) {
                TmpHeight += ((TLabel*)MMessage->Items[i])->Height;
                }
        // Определим Top для каждой Label в CMessage
        ((TLabel*)MMessage->Items[0])->Top = (Form1->Height-TmpHeight)/2;      // Первая Label - отцентрировать по высоте окна, остальные - по ней
        for(int i=1; i<MMessage->Count; i++) {
                ((TLabel*)MMessage->Items[i])->Top = ((TLabel*)MMessage->Items[i-1])->Top+((TLabel*)MMessage->Items[i-1])->Height;
                }
        }
        // Окно показа даты и времени
ClockMessage->Font->Size = Floor(Form1->Width/60);
}
//---------------------------------------------------------------------------
//                             ФУНКЦИИ НАСТРОЙКИ
//---------------------------------------------------------------------------
void TForm1::FirstSetup()
{
        // Проверяет, есть ли в системе ODBC Alias для доступа к базе данных,
        // если нет - создает его. Должно срабатывать только при
        // первом запуске программы
        // Получить системный каталог и каталог WINDOWS
char SystemDirTmp[MAX_PATH];
GetSystemDirectory(SystemDirTmp,MAX_PATH);
AnsiString SystemDir = AnsiString(SystemDirTmp);
char WindowsDirTmp[MAX_PATH];
GetWindowsDirectory(WindowsDirTmp,MAX_PATH);
AnsiString WindowsDir = AnsiString(WindowsDirTmp);
        // Если в ODBC отсутствует Alias "IN_OUT" - создать его
TRegistry* AliasReg = new TRegistry();
AliasReg->RootKey =  HKEY_CURRENT_USER;
TStringList* AliasIni = new TStringList();
AliasIni->LoadFromFile(WindowsDir+"\\odbc.ini");
if(AliasIni->IndexOf("[IN_OUT]")==-1) {
        int Poz = AliasIni->IndexOf("[ODBC 32 bit Data Sources]")+1;
        AliasIni->Insert(Poz,"IN_OUT=Microsoft Access Driver (*.mdb) (32 разряда)");
        AliasIni->Add("[IN_OUT]");
        AliasIni->Add("Driver32="+SystemDir+"\\odbcjt32.dll");
        AliasIni->Add("");
        AliasIni->SaveToFile(WindowsDir+"\\odbc.ini");

        AliasReg->OpenKey("\\SOFTWARE\\ODBC\\ODBC.INI\\IN_OUT",true);
        AliasReg->WriteString("DBQ",Settings->FindByName("Database"));
        AliasReg->WriteString("Driver",SystemDir+"\\odbcjt32.dll");
        AliasReg->WriteInteger("DriverId",0x00000019);
        AliasReg->WriteString("FIL","Ms Access;");
        AliasReg->WriteInteger("SafeTransactions",0x00000000);
        AliasReg->WriteString("UID","");
        AliasReg->OpenKey("\\SOFTWARE\\ODBC\\ODBC.INI\\IN_OUT\\Engines\\Jet",true);
        AliasReg->WriteString("ImplicitCommitSync","");
        AliasReg->WriteInteger("MaxBufferSize",0x00000800);
        AliasReg->WriteInteger("PageTimeout",0x00000005);
        AliasReg->WriteInteger("Threads",0x00000003);
        AliasReg->WriteString("UserCommitSync","Yes");
        AliasReg->OpenKey("\\SOFTWARE\\ODBC\\ODBC.INI\\ODBC Data Sources",true);
        AliasReg->WriteString("IN_OUT","Microsoft Access Driver (*.mdb)");
        }
        // Если изменилось месторасположение таблицы с базой данных  внастройках - обновить в реестре
AliasReg->OpenKey("\\SOFTWARE\\ODBC\\ODBC.INI\\IN_OUT",true);
if(AliasReg->ReadString("DBQ")!=Settings->FindByName("Database")) {
        AliasReg->WriteString("DBQ",Settings->FindByName("Database"));
        }
delete AliasReg;
delete AliasIni;
}
//---------------------------------------------------------------------------
//                        НАЖАТИЕ КНОПОК НА ФОРМЕ
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        // При нажатии клавиши
        // Enter
if(Key==VK_RETURN) {
        HideCMessage();
        HideMMessage();
        HideP_Fon_b();
        if(Code->Visible==false) {
                Code->Visible = true;
                Code->SetFocus();
                CodeShowTime = c_CodeShowTime;
                }
        }
        // Ctrl + Alt + F9
if(Key==VK_F9&&Shift.Contains(ssCtrl)&&Shift.Contains(ssAlt)) {
        // Выход
        Close();
        }
        // Ctrl + Alt + F5
if(Key==VK_F5&&Shift.Contains(ssCtrl)&&Shift.Contains(ssAlt)) {
        // Вызов формы редактирования в таблицах
        Application->CreateForm(__classid(TForm2),&Form2);
        Form2->Visible = true;
        }
        // Ctrl + Alt + F6
if(Key==VK_F6&&Shift.Contains(ssCtrl)&&Shift.Contains(ssAlt)) {
        // Вызов формы для распечатки отчетов
        Application->CreateForm(__classid(TForm3),&Form3);
        Form3->Visible = true;
        }
}
//---------------------------------------------------------------------------
//                              ПРИХОД-УХОД
//---------------------------------------------------------------------------
void __fastcall TForm1::CodeKeyPress(TObject *Sender, char &Key)
{
        // Ввод кода
CodeShowTime = c_CodeShowTime;
        // Нажатие Enter в окне регистрации
if(Key==VK_RETURN&&(Code->Text)!="") {
        ComeInOut(Code->Text);
        Code->Visible = false;
        Code->Text = "";
        }
if(Key!=VK_BACK) {
        // Чтобы вводились только заглавные латинские буквы
        Set <char, 'a','z'> LChar;
        LChar <<'a'<<'b'<<'c'<<'d'<<'e'<<'f'<<'g'<<'h'<<'i'<<'j'<<'k'<<'l'<<'m'<<'n'<<'o'<<'p'<<'q'<<'r'<<'s'<<'t'<<'u'<<'v'<<'w'<<'x'<<'y'<<'z';
        if(LChar.Contains(Key)) {
                Key = _toupper(Key);
                }
        Set <char, 'A','Z'> UChar;
        UChar <<'A'<<'B'<<'C'<<'D'<<'E'<<'F'<<'G'<<'H'<<'I'<<'J'<<'K'<<'L'<<'M'<<'N'<<'O'<<'P'<<'Q'<<'R'<<'S'<<'T'<<'U'<<'V'<<'W'<<'X'<<'Y'<<'Z';
        if(!UChar.Contains(Key)) {
                Key = 0;
                }
        }
}
//---------------------------------------------------------------------------
bool TForm1::ComeInOut(AnsiString Code)
{
        // Обработка прихода - ухода
bool ComeIn = false;    // true - приход, false - уход
AnsiString Io = "";     // Имя и отчество отмечающегося
        // Проверяем правильность кода
Database->Close();
Database->SQL->Clear();
Database->SQL->Add("SELECT *,Day(birthday) as Day,Month(birthday) as Month FROM personal WHERE code=:P_Code");
Database->Parameters->ParamByName("P_Code")->Value = Code;
try {
        Database->Open();       // Database->ExecSQL();
        }
catch(...){
        Database->Close();
        ShowMessage("Ошибка работы программы!");
        return false;
        }
if(Database->RecordCount!=1) {
        // Неправильно введен код
//        ShowMessage("Пользователя с таким паролем нет!");
        CreateCMessage("НЕПРАВИЛЬНО ВВЕДЕН КОД!");
        ShowCMessage();
        Database->Close();
        return false;
        }
        // Если введен правильный код
Io = Database->FieldByName("name_i")->AsString + " " + Database->FieldByName("parent_i")->AsString;    // Запомним Имя-Отчество
        // Если сегодня его день рождения - сменить оформление
unsigned short ADay,AMonth,AYear;
TDateTime ADate = Date();
ADate.DecodeDate(&AYear,&AMonth,&ADay);
if(Database->FieldByName("Day")->AsInteger==ADay&&Database->FieldByName("Month")->AsInteger==AMonth) {
        ShowP_Fon_b();
        }
Database->Close();
        // Проверяем что это, приход или уход
Database->SQL->Clear();
Database->SQL->Add("SELECT * FROM inout WHERE (code=:P_Code)AND(in_date=:P_Date)AND(out_date=:P_EmptyDate)");
Database->Parameters->ParamByName("P_Code")->Value = Code;
Database->Parameters->ParamByName("P_Date")->Value = Date();
Database->Parameters->ParamByName("P_EmptyDate")->Value = StrToDate("30.12.1899");  // Пустая дата
try {
        Database->Open();       // Database->ExecSQL();
        }
catch(...){
        Database->Close();
        ShowMessage("Ошибка работы программы!");
        return false;
        }
if(Database->RecordCount>=1) ComeIn = false;            // Уход
else ComeIn = true;     // Приход
        // Обработать Приход-Уход
Database->Close();
Database->SQL->Clear();
if(ComeIn==true) {
        // Зафиксировать приход
        Database->SQL->Add("insert into inout (code,in_date) values (:P_Code,:P_Date)");
        Database->Parameters->ParamByName("P_Code")->Value = Code;
        Database->Parameters->ParamByName("P_Date")->Value = Date();

        }
else {
        // Зафиксировать уход
        AnsiString P_Time = TimeToStr(Time());  // Через параметры почему-то не берет время
        Database->SQL->Add("update inout set out_date=:P_Date1,out_time='"+P_Time+"' where (code=:P_Code)AND(in_date=:P_Date)AND(out_date=:P_EmptyDate)");
        Database->Parameters->ParamByName("P_EmptyDate")->Value = StrToDateTime("30.12.1899");  // Пустая дата
        Database->Parameters->ParamByName("P_Code")->Value = Code;
        Database->Parameters->ParamByName("P_Date")->Value = Date();
        Database->Parameters->ParamByName("P_Date1")->Value = Date();
        }
try {
        Database->ExecSQL();    // Database->Open();
        }
catch(...){
        Database->Close();
        ShowMessage("Ошибка работы программы!");
        return false;
        }
Database->Close();
        // Вывести сообщение о фиксации времени прихода-ухода
if(ComeIn==true) CreateCMessage("Здравствуйте, "+Io+",\nвремя Вашего прихода зафиксировано");       // Приход
else CreateCMessage("До свидания, "+Io+",\nвремя Вашего ухода зафиксировано");   // Уход
ShowCMessage();
return true;
}
//---------------------------------------------------------------------------
//                           ФУНКЦИИ ПОКАЗА СООБЩЕНИЙ
//---------------------------------------------------------------------------
bool TForm1::CreateCMessage(AnsiString Text)
{
        // Создать сообщение CMessage. Все сообщение состоит из Text
DeleteCMessage();       // Удалить то, что было
        // Разбить текст на набор Label в каждой из которых будет по одной строке текста
Text+="\n";     // Чтобы последняя строчка тоже входила
int i=Text.Pos("\n");
while(i>=1) {
        TLabel* TmpLabel = new TLabel(Form1);
        TmpLabel->Parent = Form1;
        TmpLabel->Caption = Text.SubString(1,i-1);      // Сначала вводим текст чтобы правильно делался autosize
        TmpLabel->AutoSize = false;
        TmpLabel->WordWrap = true;
        TmpLabel->Transparent = true;
        TmpLabel->Font->Size = Floor(Form1->Width/60);
        TmpLabel->Font->Style = TFontStyles()<< fsBold;
        TmpLabel->Font->Color = clYellow;
//        TmpLabel->Color = clGreen;
        TmpLabel->Visible = false;
        TmpLabel->Width = Form1->Width/2;
        TmpLabel->Left = (Form1->Width-Form1->Width/2)/2;
        TmpLabel->Height = Form1->Height;
        TmpLabel->AutoSize = true;      // Пересчитать размеры
        TmpLabel->Anchors = TAnchors() << akLeft << akRight;
//        TmpLabel->Refresh();
//        TmpLabel->Repaint();
//        ShowMessage("*"+TmpLabel->Caption+"*");
        CMessage->Add(TmpLabel);
        Text.Delete(1,i);
        i=Text.Pos("\n");
        }
        // По сумме всех Label получим Top для каждой из них
        // Общая высота
int TmpHeight = 0;
for(int i=0; i<CMessage->Count; i++) {
        TmpHeight += ((TLabel*)CMessage->Items[i])->Height;
        }
        // Определим Top
((TLabel*)CMessage->Items[0])->Top = (Form1->Height-TmpHeight)/2;      // Первая Label - отцентрировать по высоте окна, остальные - по ней
for(int i=1; i<CMessage->Count; i++) {
        ((TLabel*)CMessage->Items[i])->Top = ((TLabel*)CMessage->Items[i-1])->Top+((TLabel*)CMessage->Items[i-1])->Height;
        }
return true;
}
//---------------------------------------------------------------------------
bool TForm1::ShowCMessage()
{
        // Показать CMessage
for(int i=0; i<CMessage->Count; i++) {
        ((TLabel*)CMessage->Items[i])->Visible = true;
        }
CMessageShowTime = c_CMessageShowTime;
return true;
}
//---------------------------------------------------------------------------
bool TForm1::HideCMessage()
{
        // Скрыть CMessage
for(int i=0; i<CMessage->Count; i++) {
        ((TLabel*)CMessage->Items[i])->Visible = false;
        }
return true;
}
//---------------------------------------------------------------------------
bool TForm1::DeleteCMessage()
{
        // Удалить CMessage
for(int i=0; i<CMessage->Count; i++) {
        delete ((TLabel*)CMessage->Items[i]);
        }
CMessage->Clear();
return true;
}
//---------------------------------------------------------------------------
bool TForm1::CreateMMessage(AnsiString Text)
{
        // Создать сообщение MMessage. Сообщение состоит из овновного
        // сообщения из б.д. на сегодня + день рождения + Text
        // Удалить то, что было
DeleteMMessage();
        // Получить из б.д. данные
        // Сообщения
Database->Close();
Database->SQL->Clear();
Database->SQL->Add("SELECT message FROM messages WHERE (start_date<=:P_Start)and(end_date>=:P_End)");
Database->Parameters->ParamByName("P_Start")->Value = Date();
Database->Parameters->ParamByName("P_End")->Value = Date();
try {
        Database->Open();       // Database->ExecSQL();
        }
catch(...){
        Database->Close();
        ShowMessage("Ошибка работы программы!");
        return false;
        }
Database->First();
while(!Database->Eof) {
        Text = Database->FieldByName("message")->AsString+"\n\n"+Text;
        Database->Next();
        }
Database->Close();
        // День рождения
Database->SQL->Clear();
Database->SQL->Add("SELECT family_i,name_i,parent_i FROM personal where (Day(birthday)=:P_Day)and(Month(birthday)=:P_Month)");
unsigned short ADay,AMonth,AYear;
TDateTime ADate = Date();
ADate.DecodeDate(&AYear,&AMonth,&ADay);
Database->Parameters->ParamByName("P_Day")->Value = ADay;
Database->Parameters->ParamByName("P_Month")->Value = AMonth;
try {
        Database->Open();       // Database->ExecSQL();
        }
catch(...){
        Database->Close();
        ShowMessage("Ошибка работы программы!");
        return false;
        }
Database->First();
while(!Database->Eof) {
        Text = Database->FieldByName("name_i")->AsString+" "+Database->FieldByName("parent_i")->AsString+" "+Database->FieldByName("family_i")->AsString+",С ДНЕМ РОЖДЕНИЯ!\n\n"+Text;
        Database->Next();
        }
Database->Close();
        // Разбить текст на набор Label в каждой из которых будет по одной строке текста
Text+="\n";     // Чтобы последняя строчка тоже входила
int i=Text.Pos("\n");
while(i>=1) {
        TLabel* TmpLabel = new TLabel(Form1);
        TmpLabel->Parent = Form1;
        TmpLabel->Caption = Text.SubString(1,i-1);      // Сначала вводим текст чтобы правильно делался autosize
        TmpLabel->AutoSize = false;
        TmpLabel->WordWrap = true;
        TmpLabel->Transparent = true;
        TmpLabel->Font->Size = Floor(Form1->Width/60);
        TmpLabel->Font->Style = TFontStyles()<< fsBold;
        TmpLabel->Font->Color = clYellow;
        TmpLabel->Visible = false;
        TmpLabel->Width = Form1->Width/2;
        TmpLabel->Left = Form1->Width/4;
        TmpLabel->Height = Form1->Height;
        TmpLabel->AutoSize = true;      // Пересчитать размеры
        TmpLabel->Anchors = TAnchors() << akLeft << akRight;
        MMessage->Add(TmpLabel);
        Text.Delete(1,i);
        i=Text.Pos("\n");
        }
        // По сумме всех Label получим Top для каждой из них
        // Общая высота
int TmpHeight = 0;
for(int i=0; i<MMessage->Count; i++) {
        TmpHeight += ((TLabel*)MMessage->Items[i])->Height;
        }
        // Определим Top
((TLabel*)MMessage->Items[0])->Top = (Form1->Height-TmpHeight)/2;      // Первая Label - отцентрировать по высоте окна, остальные - по ней
for(int i=1; i<MMessage->Count; i++) {
        ((TLabel*)MMessage->Items[i])->Top = ((TLabel*)MMessage->Items[i-1])->Top+((TLabel*)MMessage->Items[i-1])->Height;
        }
return true;
}
//---------------------------------------------------------------------------
bool TForm1::ShowMMessage()
{
        // Показать MMessage
for(int i=0; i<MMessage->Count; i++) {
        ((TLabel*)MMessage->Items[i])->Visible = true;
        }
return true;
}
//---------------------------------------------------------------------------
bool TForm1::HideMMessage()
{
        // Скрыть MMessage
for(int i=0; i<MMessage->Count; i++) {
        ((TLabel*)MMessage->Items[i])->Visible = false;
        }
return true;
}
//---------------------------------------------------------------------------
bool TForm1::DeleteMMessage()
{
        // Удалить CMessage
for(int i=0; i<MMessage->Count; i++) {
        delete ((TLabel*)MMessage->Items[i]);
        }
MMessage->Clear();
return true;
}
//---------------------------------------------------------------------------
//                           ФУНКЦИИ ПОКАЗА ФОНА
//---------------------------------------------------------------------------
bool TForm1::ShowP_Fon_b()
{
        // Показать P_Fon_b
P_Fon->Picture->LoadFromFile(Settings->FindByName("P_Fon_b"));
P_FonB_ShowTime = c_CMessageShowTime;
return true;
}
//---------------------------------------------------------------------------
bool TForm1::HideP_Fon_b()
{
        // Скрыть P_Fon_b
P_Fon->Picture->LoadFromFile(Settings->FindByName("P_Fon"));
P_FonB_ShowTime = 0;
return true;
}
//---------------------------------------------------------------------------
//                           ФУНКЦИИ ТАЙМЕРА
//---------------------------------------------------------------------------
void __fastcall TForm1::TimerTimer(TObject *Sender)
{
        // Работа таймера
        // Установить дату-время
AnsiString TmpDT = "";
DateTimeToString(TmpDT,"dddd  hh:nn  d mmmm yyy",Now());
ClockMessage->Caption = TmpDT;
        // Если есть показ Code - проверить и если нужно - скрыть
if(CodeShowTime>0) {
        CodeShowTime--;
        if(CodeShowTime<=0) {
                Code->Visible = false;
                Code->Text = "";
//                if(Form2->Visible==false) Form1->SetFocus();    // Иначе закрывает Form2 если оно открыто
                }
        }
        // Если есть показ CMessage - проверить и если нужно - скрыть
if(CMessageShowTime>0) {
        CMessageShowTime--;
        if(CMessageShowTime<=0) {
                HideCMessage(); // Скрыть CMessage
                ShowMMessage(); // Показать MMessage
                }
        }
        // Если есть показ рисунка для дня рождения - если нужно скрыть
if(P_FonB_ShowTime>0) {
        P_FonB_ShowTime--;
        if(P_FonB_ShowTime<=0) {
                HideP_Fon_b();
                }
        }
}
//---------------------------------------------------------------------------

