object Form1: TForm1
  Left = 192
  Top = 107
  AutoScroll = False
  Caption = 
    'Header maker for FEGUI  (criador de cabe'#231'alho para a biblioteca ' +
    'dinamica FEGUI)              by   Mario Freire'
  ClientHeight = 715
  ClientWidth = 1145
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 545
    Top = 41
    Height = 196
  end
  object Splitter2: TSplitter
    Left = 0
    Top = 237
    Width = 1145
    Height = 3
    Cursor = crVSplit
    Align = alBottom
  end
  object ClassBrowser1: TClassBrowser
    Left = 0
    Top = 41
    Width = 545
    Height = 196
    Align = alLeft
    Indent = 19
    TabOrder = 0
    ShowFilter = sfAll
    Parser = CppParser1
    ItemImages.Globals = 0
    ItemImages.Classes = 0
    ItemImages.VariablePrivate = 0
    ItemImages.VariableProtected = 0
    ItemImages.VariablePublic = 0
    ItemImages.VariablePublished = 0
    ItemImages.MethodPrivate = 0
    ItemImages.MethodProtected = 0
    ItemImages.MethodPublic = 0
    ItemImages.MethodPublished = 0
    ItemImages.InheritedMethodProtected = 0
    ItemImages.InheritedMethodPublic = 0
    ItemImages.InheritedVariableProtected = 0
    ItemImages.InheritedVariablePublic = 0
    UseColors = True
    ShowInheritedMembers = False
  end
  object SynEdit1: TSynEdit
    Left = 548
    Top = 41
    Width = 597
    Height = 196
    Align = alClient
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    TabOrder = 1
    Gutter.Font.Charset = DEFAULT_CHARSET
    Gutter.Font.Color = clWindowText
    Gutter.Font.Height = -11
    Gutter.Font.Name = 'Courier New'
    Gutter.Font.Style = []
    Highlighter = Cpp
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 696
    Width = 1145
    Height = 19
    Panels = <>
  end
  object SynEdit2: TSynEdit
    Left = 0
    Top = 240
    Width = 1145
    Height = 456
    Align = alBottom
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    TabOrder = 3
    Gutter.Font.Charset = DEFAULT_CHARSET
    Gutter.Font.Color = clWindowText
    Gutter.Font.Height = -11
    Gutter.Font.Name = 'Courier New'
    Gutter.Font.Style = []
    Highlighter = Cpp
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 1145
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 4
    object Button1: TButton
      Left = 8
      Top = 8
      Width = 113
      Height = 25
      Caption = 'Salvar como...'
      Default = True
      TabOrder = 0
      OnClick = Button1Click
    end
  end
  object Panel2: TPanel
    Left = 40
    Top = 296
    Width = 8
    Height = 8
    TabOrder = 5
    Visible = False
    object source_begin: TMemo
      Left = 1
      Top = 1
      Width = 6
      Height = 144
      Align = alTop
      Lines.Strings = (
        '// Fast Engine Graphical User Interface (F.E.G.U.I)'
        '// This feature is a part of FastEngine'
        '// by Mario Freire'
        '// Copyright (C) 2013 DSP Interactive. All rights reserved.'
        '// Development Systems and Programs'
        
          '// See more information in the website: http://www.dspinteractiv' +
          'e.com'
        
          '//--------------------------------------------------------------' +
          '-------------'
        ''
        '#ifndef feguiH'
        '#define feguiH'
        
          '//--------------------------------------------------------------' +
          '-------------'
        ''
        '#include <stdio.h>'
        '#include <dlltype.h>'
        ''
        'namespace fegui'
        '{'
        'class TObject'
        '{'
        #9'public:'
        #9#9'// class constructor'
        #9#9'TObject();'
        #9#9'// class destructor'
        #9#9'~TObject();'
        '};'
        '};'
        ''
        'typedef void (* TFEGUI_NotifyEvent)(int windowid,int sender);'
        'typedef void (* TFEGUI_RenderEvent)(int windowid,int sender);'
        'typedef void (* TFEGUI_TimerEvent)(int windowid, int sender);'
        
          'typedef void (* TFEGUI_MenuEvent)(int windowid, int sender, int ' +
          'menuid);'
        ''
        '#define FEGUI_STDCALL'
        '#define FEGUI_CALLBACK FEGUI_STDCALL'
        ''
        
          'typedef FILE* (FEGUI_CALLBACK *FEGUI_FILE_OPENCALLBACK) (const c' +
          'har* filename, const char* mode);'
        
          'typedef int (FEGUI_CALLBACK *FEGUI_FILE_CLOSECALLBACK) (FILE* st' +
          'ream);'
        
          'typedef long (FEGUI_CALLBACK *FEGUI_FILE_TELLCALLBACK) (FILE* st' +
          'ream);'
        
          'typedef int (FEGUI_CALLBACK *FEGUI_FILE_SEEKCALLBACK) (FILE* str' +
          'eam, long offset, int whence);'
        
          'typedef size_t (FEGUI_CALLBACK *FEGUI_FILE_READCALLBACK) (void* ' +
          'ptr, size_t size, size_t n, FILE* stream);'
        
          'typedef size_t (FEGUI_CALLBACK *FEGUI_FILE_WRITECALLBACK) (const' +
          ' void* ptr, size_t size, size_t n, FILE* stream);'
        ''
        ''
        '#pragma pack(push, 1)'
        ''
        '#ifdef __cplusplus'
        'extern "C" {'
        '#endif'
        ''
        
          'void fegui_settransparentboxonrender(int handlewindow,int handle' +
          'control,TFEGUI_RenderEvent onrender);'
        
          'void fegui_setviewportonrender(int handlewindow,int handlecontro' +
          'l,TFEGUI_RenderEvent onrender);'
        
          'void fegui_setviewportonclick(int handlewindow,int handlecontrol' +
          ',TFEGUI_NotifyEvent onclick);'
        
          'void fegui_setbuttononclick(int handlewindow,int handlecontrol,T' +
          'FEGUI_NotifyEvent onclick);'
        
          'void fegui_setspeedbuttononclick(int handlewindow,int handlecont' +
          'rol,TFEGUI_NotifyEvent onclick);'
        
          'void fegui_setglyphbuttononclick(int handlewindow,int handlecont' +
          'rol,TFEGUI_NotifyEvent onclick);'
        
          'void fegui_settimerontimer(int handlewindow,int handlecontrol,TF' +
          'EGUI_TimerEvent ontimer);'
        
          'void fegui_setmenuitemonclick(int handlewindow,int handlecontrol' +
          ',int handlemenuitem,TFEGUI_MenuEvent onclick);'
        
          'void fegui_setmenusubitemonclick(int handlewindow,int handlecont' +
          'rol,int handlemenuitem,int handlemenusubitem,TFEGUI_MenuEvent on' +
          'click);'
        
          'void fegui_setfilesystem(FEGUI_FILE_OPENCALLBACK fileopen,FEGUI_' +
          'FILE_CLOSECALLBACK fileclose,FEGUI_FILE_READCALLBACK fileread,FE' +
          'GUI_FILE_WRITECALLBACK filewrite,FEGUI_FILE_TELLCALLBACK filetel' +
          'l,FEGUI_FILE_SEEKCALLBACK fileseek);'
        ''
        '#ifdef __cplusplus'
        '}'
        '#endif'
        ''
        '#pragma pack(pop)'
        ''
        ''
        ''
        '#define FEGUI_MOUSECURSOR_XCURSOR               0x0000'
        '#define FEGUI_MOUSECURSOR_ARROW                 0x0001'
        '#define FEGUI_MOUSECURSOR_APPSTART              0x0002'
        '#define FEGUI_MOUSECURSOR_IBEAM                 0x0003'
        '#define FEGUI_MOUSECURSOR_CROSSHAIR             0x0004'
        '#define FEGUI_MOUSECURSOR_POINTER               0x0005'
        '#define FEGUI_MOUSECURSOR_HELP                  0x0006'
        '#define FEGUI_MOUSECURSOR_WAIT                  0x0007'
        '#define FEGUI_MOUSECURSOR_DRAG                  0x0008'
        '#define FEGUI_MOUSECURSOR_MULTIDRAG             0x0009'
        '#define FEGUI_MOUSECURSOR_HSPLIT                0x0010'
        '#define FEGUI_MOUSECURSOR_VSPLIT                0x0011'
        '#define FEGUI_MOUSECURSOR_MOVE                  0x0012'
        '#define FEGUI_MOUSECURSOR_SIZEWZ                0x0013'
        '#define FEGUI_MOUSECURSOR_SIZEXZ                0x0014'
        '#define FEGUI_MOUSECURSOR_SIZEX                 0x0015'
        '#define FEGUI_MOUSECURSOR_SIZEY                 0x0016'
        '#define FEGUI_MOUSECURSOR_NO                    0x0017'
        '#define FEGUI_MOUSECURSOR_NODROP                0x0018'
        '#define FEGUI_MOUSECURSOR_UPARROW               0x0019'
        '#define FEGUI_MOUSECURSOR_PENCIL                0x0020'
        '#define FEGUI_MOUSECURSOR_ERASER                0x0021'
        '#define FEGUI_MOUSECURSOR_FLOODFILL             0x0022'
        '#define FEGUI_MOUSECURSOR_PICKERDROP            0x0023'
        '#define FEGUI_MOUSECURSOR_STYLUSPEN             0x0024'
        '#define FEGUI_MOUSECURSOR_OK                    0x0025'
        '#define FEGUI_MOUSECURSOR_XCANCEL               0x0026'
        '#define FEGUI_MOUSECURSOR_HANDMOVE              0x0027'
        '#define FEGUI_MOUSECURSOR_DOWNARROW             0x0028'
        '#define FEGUI_MOUSECURSOR_LEFTARROW             0x0029'
        '#define FEGUI_MOUSECURSOR_RIGHTARROW            0x0030'
        '#define FEGUI_MOUSECURSOR_WZARROW               0x0031'
        '#define FEGUI_MOUSECURSOR_XZARROW               0x0032'
        '#define FEGUI_MOUSECURSOR_YZARROW               0x0033'
        '#define FEGUI_MOUSECURSOR_XYARROW               0x0034'
        '#define FEGUI_MOUSECURSOR_SOUND                 0x0035'
        '#define FEGUI_MOUSECURSOR_ARROWPLUS             0x0036'
        '#define FEGUI_MOUSECURSOR_ARROWMINUS            0x0037'
        '#define FEGUI_MOUSECURSOR_CAROUSELWAIT          0x0038'
        '#define FEGUI_MOUSECURSOR_RADIALWAIT            0x0039'
        '#define FEGUI_MOUSECURSOR_NONE                  0x0040'
        ''
        '')
      TabOrder = 0
      Visible = False
      WordWrap = False
    end
    object source_end: TMemo
      Left = 1
      Top = 145
      Width = 6
      Height = 143
      Align = alClient
      Lines.Strings = (
        ''
        
          '//--------------------------------------------------------------' +
          '-------------'
        '#endif'
        '')
      TabOrder = 1
      Visible = False
      WordWrap = False
    end
  end
  object CppTokenizer1: TCppTokenizer
    LogTokens = False
    Left = 192
    Top = 64
  end
  object CppParser1: TCppParser
    Enabled = True
    Tokenizer = CppTokenizer1
    ParseLocalHeaders = False
    ParseGlobalHeaders = False
    LogStatements = False
    Left = 224
    Top = 64
  end
  object Cpp: TSynCppSyn
    DefaultFilter = 'C++ files (*.cpp,*.h,*.hpp)|*.cpp;*.h;*.hpp'
    AsmAttri.Foreground = clBlue
    CommentAttri.Foreground = clHighlight
    DirecAttri.Foreground = clGreen
    IdentifierAttri.Foreground = clBlack
    InvalidAttri.Foreground = clBlack
    KeyAttri.Foreground = clBlack
    NumberAttri.Foreground = clTeal
    StringAttri.Foreground = clRed
    SymbolAttri.Foreground = clBlack
    Left = 256
    Top = 64
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = 'h'
    FileName = 'fegui.h'
    Filter = 
      'Header files|*.h|C++ Header files|*.hpp|C files|*.c|C++ files|*.' +
      'cpp|All files (*.*)|*.*'
    Left = 288
    Top = 64
  end
end
