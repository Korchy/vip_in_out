object Form3: TForm3
  Left = 240
  Top = 151
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Form3'
  ClientHeight = 159
  ClientWidth = 343
  Color = clBtnFace
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Arial'
  Font.Style = []
  OldCreateOrder = False
  Scaled = False
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 14
  object Label1: TLabel
    Left = 8
    Top = 13
    Width = 61
    Height = 13
    Caption = #1053#1072#1095#1080#1085#1072#1103' '#1089':'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Arial'
    Font.Style = [fsBold, fsItalic]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 8
    Top = 61
    Width = 71
    Height = 13
    Caption = #1047#1072#1082#1072#1085#1095#1080#1074#1072#1103':'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Arial'
    Font.Style = [fsBold, fsItalic]
    ParentFont = False
  end
  object Code: TLabeledEdit
    Left = 208
    Top = 60
    Width = 121
    Height = 22
    EditLabel.Width = 78
    EditLabel.Height = 13
    EditLabel.Caption = #1042#1074#1077#1076#1080#1090#1077' '#1082#1086#1076':'
    EditLabel.Font.Charset = RUSSIAN_CHARSET
    EditLabel.Font.Color = clWindowText
    EditLabel.Font.Height = -11
    EditLabel.Font.Name = 'Arial'
    EditLabel.Font.Style = [fsBold, fsItalic]
    EditLabel.ParentFont = False
    LabelPosition = lpAbove
    LabelSpacing = 3
    MaxLength = 3
    TabOrder = 0
  end
  object StartDate: TDateTimePicker
    Left = 8
    Top = 28
    Width = 186
    Height = 22
    CalAlignment = dtaLeft
    Date = 38953.6480586227
    Time = 38953.6480586227
    DateFormat = dfShort
    DateMode = dmComboBox
    Kind = dtkDate
    ParseInput = False
    TabOrder = 1
  end
  object EndDate: TDateTimePicker
    Left = 8
    Top = 76
    Width = 186
    Height = 22
    CalAlignment = dtaLeft
    Date = 38953.6495451736
    Time = 38953.6495451736
    DateFormat = dfShort
    DateMode = dmComboBox
    Kind = dtkDate
    ParseInput = False
    TabOrder = 2
  end
  object FormButton: TButton
    Left = 8
    Top = 110
    Width = 321
    Height = 25
    Caption = #1089#1092#1086#1088#1084#1080#1088#1086#1074#1072#1090#1100' '#1086#1090#1095#1077#1090
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 3
    OnClick = FormButtonClick
  end
end
