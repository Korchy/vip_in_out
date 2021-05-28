object Form1: TForm1
  Left = 295
  Top = 201
  Width = 500
  Height = 400
  Cursor = crArrow
  Caption = 'RECEIPTION'
  Color = clBtnFace
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Arial'
  Font.Style = []
  OldCreateOrder = False
  OnDestroy = FormDestroy
  OnKeyDown = FormKeyDown
  OnResize = FormResize
  DesignSize = (
    492
    373)
  PixelsPerInch = 96
  TextHeight = 14
  object P_Fon: TImage
    Left = 0
    Top = 0
    Width = 492
    Height = 373
    Align = alClient
    Stretch = True
  end
  object ClockMessage: TLabel
    Left = 392
    Top = 8
    Width = 93
    Height = 14
    Alignment = taRightJustify
    Anchors = [akLeft, akTop, akRight]
    Caption = '00:00    00.00.0000'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clYellow
    Font.Height = -11
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
    Transparent = True
  end
  object Code: TLabeledEdit
    Left = 200
    Top = 184
    Width = 100
    Height = 24
    Color = clBlack
    EditLabel.Width = 78
    EditLabel.Height = 13
    EditLabel.Caption = #1042#1074#1077#1076#1080#1090#1077' '#1082#1086#1076':'
    EditLabel.Color = clBtnFace
    EditLabel.Font.Charset = RUSSIAN_CHARSET
    EditLabel.Font.Color = clYellow
    EditLabel.Font.Height = -11
    EditLabel.Font.Name = 'Arial'
    EditLabel.Font.Style = [fsBold, fsItalic]
    EditLabel.ParentColor = False
    EditLabel.ParentFont = False
    EditLabel.Transparent = True
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clYellow
    Font.Height = -13
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    LabelPosition = lpAbove
    LabelSpacing = 3
    MaxLength = 3
    ParentFont = False
    TabOrder = 0
    Visible = False
    OnKeyPress = CodeKeyPress
  end
  object Database: TADOQuery
    Connection = Connection
    CursorLocation = clUseServer
    CursorType = ctStatic
    Parameters = <>
    Left = 408
    Top = 120
  end
  object Data: TDataSource
    DataSet = Database
    Left = 376
    Top = 120
  end
  object Timer: TTimer
    OnTimer = TimerTimer
    Left = 376
    Top = 176
  end
  object Connection: TADOConnection
    Connected = True
    ConnectionString = 
      'Provider=MSDASQL.1;Persist Security Info=False;Data Source=IN_OU' +
      'T'
    LoginPrompt = False
    Left = 440
    Top = 120
  end
end
