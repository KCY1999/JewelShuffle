object Form1: TForm1
  Left = 165
  Top = 0
  Caption = 'Game'
  ClientHeight = 603
  ClientWidth = 681
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnCreate = FortimemCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Button1: TButton
    Left = 80
    Top = 32
    Width = 75
    Height = 25
    Caption = #38283#22987#36938#25138
    TabOrder = 0
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 284
    Top = 35
    Width = 75
    Height = 25
    Caption = #32080#26463
    TabOrder = 1
    OnClick = Button2Click
  end
  object Edit1: TEdit
    Left = 365
    Top = 34
    Width = 52
    Height = 21
    TabOrder = 2
    Text = 'Edit1'
  end
  object Edit2: TEdit
    Left = 432
    Top = 34
    Width = 49
    Height = 21
    TabOrder = 3
    Text = 'Edit2'
  end
  object Edit3: TEdit
    Left = 365
    Top = 8
    Width = 52
    Height = 21
    TabOrder = 4
    Text = 'Edit3'
  end
  object Edit4: TEdit
    Left = 432
    Top = 8
    Width = 49
    Height = 21
    TabOrder = 5
    Text = 'Edit4'
  end
  object Timer1: TTimer
    Enabled = False
    OnTimer = Timer1Timer
    Left = 552
    Top = 24
  end
  object MainMenu1: TMainMenu
    Left = 512
    Top = 24
    object Debug1: TMenuItem
      Caption = 'Debug'
      OnClick = Debug1Click
    end
  end
  object Timer2: TTimer
    Interval = 500
    OnTimer = Timer2Timer
    Left = 600
    Top = 24
  end
end
