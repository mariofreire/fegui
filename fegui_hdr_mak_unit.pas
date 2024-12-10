unit fegui_hdr_mak_unit;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ColorPickerButton, devTabs, ComCtrls, DropFileListView,
  BetterProgressBar, devFileMonitor, CppTokenizer, CppParser, ClassBrowser,
  ExtCtrls, SynEditHighlighter, SynHighlighterCpp, SynEdit, StdCtrls;

type
  TForm1 = class(TForm)
    ClassBrowser1: TClassBrowser;
    CppTokenizer1: TCppTokenizer;
    CppParser1: TCppParser;
    SynEdit1: TSynEdit;
    Splitter1: TSplitter;
    StatusBar1: TStatusBar;
    SynEdit2: TSynEdit;
    Splitter2: TSplitter;
    Panel1: TPanel;
    Button1: TButton;
    source_begin: TMemo;
    source_end: TMemo;
    Panel2: TPanel;
    Cpp: TSynCppSyn;
    SaveDialog1: TSaveDialog;
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure Button1Click(Sender: TObject);
  private
    { Private declarations }
  public
    FileName: string;
    stream: tmemorystream;
    slist:tstrings;
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

uses StrUtils;

{$R *.dfm}

procedure TForm1.FormCreate(Sender: TObject);
var
i: integer;
item:string;
function_item:string;
begin
          FileName := 'ext_unit.cpp';
          SaveDialog1.InitialDir := ExtractFilePath(ParamStr(0));
          slist := TStringList.Create;
          slist.Clear;
          stream := TMemoryStream.Create;
          stream.Clear;
          stream.Position:=0;
          CppParser1.AddFileToScan(FileName);
          CppParser1.ParseList;
          ClassBrowser1.CurrentFile:=FileName;
          ClassBrowser1.SaveToStream(stream);
          SynEdit1.Lines.LoadFromStream(stream);
          item:= '';
          function_item:= '';
          for i:=0 to SynEdit1.Lines.Count do
          begin
            item := SynEdit1.Lines.Strings[i];
            item := AnsiLeftStr(item,AnsiPos(')',item)) + ';';
            function_item:= '';
            if (AnsiContainsText(item,'  FEGUIFUNCTION')) then
            begin
              function_item := (StringReplace(item,'  FEGUIFUNCTION','DLLIMPORT',[rfReplaceAll]));
              slist.Add(StringReplace(function_item,'fegui_T','TFEGUI_',[rfReplaceAll]));
            end;
          end;
          SynEdit1.Lines.Clear;
          SynEdit1.Lines.AddStrings(slist);

          SynEdit2.Lines.AddStrings(source_begin.Lines);
          SynEdit2.Lines.AddStrings(SynEdit1.Lines);
          SynEdit2.Lines.AddStrings(source_end.Lines);

end;

procedure TForm1.FormDestroy(Sender: TObject);
begin
          stream.Free;
          slist.Free;
end;

procedure TForm1.Button1Click(Sender: TObject);
begin
  if SaveDialog1.Execute then
  begin
    SynEdit2.Lines.SaveToFile(SaveDialog1.FileName);
  end;
end;

end.
