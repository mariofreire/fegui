program fegui_hdr_maker;

uses
  Forms,
  fegui_hdr_mak_unit in 'fegui_hdr_mak_unit.pas' {Form1};

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
