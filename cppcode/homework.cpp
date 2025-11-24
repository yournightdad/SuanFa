procedure insertsort(n:integer);
  var i,j:integer;
  begin
    for i:=2 to n do
    begin
      a[0]:=a[i];
      j:=i-1;
      while a[j]>a[0] do  
      begin
        a[j+1]:=a[j];
        j:=j-1;
      end;
      a[j+1]:=a[0];
    end;
  end;
