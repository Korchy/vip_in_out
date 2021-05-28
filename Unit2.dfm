object Form2: TForm2
  Left = 247
  Top = 166
  Width = 531
  Height = 363
  BorderIcons = [biSystemMenu, biMaximize]
  Caption = #1056#1045#1044#1040#1050#1058#1048#1056#1054#1042#1040#1053#1048#1045' '#1041#1040#1047#1067' '#1044#1040#1053#1053#1067#1061
  Color = clBtnFace
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Arial'
  Font.Style = []
  OldCreateOrder = False
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 14
  object DBGrid: TDBGrid
    Left = 0
    Top = 40
    Width = 523
    Height = 276
    Align = alClient
    DataSource = Form1.Data
    TabOrder = 0
    TitleFont.Charset = RUSSIAN_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Arial'
    TitleFont.Style = []
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 523
    Height = 40
    Align = alTop
    TabOrder = 1
    object CloseButton: TButton
      Left = 320
      Top = 8
      Width = 193
      Height = 25
      Caption = #1047#1072#1082#1088#1099#1090#1100
      TabOrder = 0
      OnClick = CloseButtonClick
    end
    object Tables: TComboBox
      Left = 8
      Top = 8
      Width = 145
      Height = 22
      Style = csDropDownList
      ItemHeight = 14
      TabOrder = 1
      OnChange = TablesChange
    end
  end
  object DBMemo: TDBMemo
    Left = 0
    Top = 316
    Width = 523
    Height = 20
    Align = alBottom
    DataSource = Form1.Data
    TabOrder = 2
  end
end
