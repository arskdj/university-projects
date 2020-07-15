set serveroutput on;

create or replace procedure project(n in int) as
begin
declare
  cursor cur_perioxes is select * from perioxes;
  cursor cur_kentra is select * from kentra;

  row_perioxes cur_perioxes%rowtype;
  row_kentra cur_kentra%rowtype;

  vima integer:=0;
  
--ipologismos apostasis
function distance (lat1 in number, 
    lat2 in number, lon1 in number, lon2 in number)
return number as
begin
    return sqrt(power(lat1-lat2,2) + power(lon1-lon2,2));
end;

procedure init_apostaseis is
begin
  --execute immediate 'delete from apostaseis where 1=1';
  open cur_perioxes;
  loop
    fetch cur_perioxes into row_perioxes;
    exit when cur_perioxes%notfound;
    open cur_kentra;
    loop
      fetch cur_kentra into row_kentra;
      exit when cur_kentra%notfound;
      insert into apostaseis values (row_perioxes.id,row_kentra.id, 540);
    end loop;
    close cur_kentra;
  end loop;
  close cur_perioxes;
end;

procedure print_clusters is
begin
      dbms_output.put_line('clusters for each location');
          open cur_perioxes;
            loop
                fetch cur_perioxes into row_perioxes;
                exit when cur_perioxes%notfound;
                dbms_output.put(' ' || row_perioxes.clusterid);
            end loop;
          close cur_perioxes;
          dbms_output.put_line(' ');
end;

procedure print_info is
begin
declare
cursor cur_info is
  select perioxes.id,perioxes.name,perioxes.lat,perioxes.lon,perioxes.clusterid,
  apostaseis.kid, kentra.lat as klat, kentra.lon as klon,apostaseis.distance 
  from perioxes 
  join apostaseis
    on apostaseis.pid = perioxes.id
  join kentra
    on apostaseis.kid = kentra.id;
row_info cur_info%rowtype;

begin
  --dbms_output.put_line('id,name,lat,lon,clusterid,kid,lat,lon,distance');
  vima := vima +1;
  open cur_info;
  loop
    fetch cur_info into row_info;
    exit when cur_info%notfound;
    --dbms_output.put_line(row_info.id||','||row_info.name||','||row_info.lat||','||
    --row_info.lon||','||row_info.clusterid||','||row_info.kid||','||row_info.klat||','||
    --row_info.klon||','||row_info.distance);
    
    insert into results values(vima,row_info.id,row_info.name,row_info.lat,
    row_info.lon, row_info.clusterid, row_info.kid, row_info.klat,
    row_info.klon, row_info.distance);
  end loop;
  close cur_info;
end;
end;

--1. select random k kentra ston pinaka kentra
procedure step1 (k in integer)
is
begin
declare 
cursor cur_random is select * from perioxes order by dbms_random.value ;
i integer;
  begin
    --dbms_output.put_line('STEP1');
    i := 1;
    open cur_random;
    --delete from kentra where 1=1; --empty table
    loop
        exit when i=k+1;
        fetch cur_random into row_perioxes;
        insert into kentra values(i, row_perioxes.lat, row_perioxes.lon);
        i := i + 1;
    end loop;
    close cur_random;
    init_apostaseis();
    --print_clusters();

  end;
end;

--2. ana8esi omadas olon ton rows tu table
function step2
return number
is
begin
    declare
      min_distance number :=0;
      min_cluster number := 0;
      dis number :=0;
      changes number :=0;
      cursor cur_kentra is select * from kentra;
    begin
    --dbms_output.put_line('STEP2');
        open cur_perioxes;
        loop
            fetch cur_perioxes into row_perioxes; --gia ka8e poli
            exit when cur_perioxes%notfound;
            open cur_kentra;
            loop --ipologismos apostaseon olon ton perioxon apo ola ta kentra
                fetch cur_kentra into row_kentra; -- gia ka8e kentro
                exit when cur_kentra%notfound;
                
                dis := distance(row_perioxes.lat,row_kentra.lat,row_perioxes.lon,row_kentra.lon);
                 update apostaseis
                      set apostaseis.distance = dis
                    where apostaseis.pid = row_perioxes.id
                      and apostaseis.kid = row_kentra.id;
                  
                   
            end loop;
            close cur_kentra;
            
            --evresi minimum apostasis gia perioxi
            select min(distance) into min_distance
              from apostaseis
              where pid = row_perioxes.id;
              
            --epilogi kentro id me tin mikroteri apostasi
            select kid into min_cluster
            from apostaseis
            where distance = min_distance and pid=row_perioxes.id;
            
            --ana8esi cluster id
            if row_perioxes.clusterid != min_cluster then
              update perioxes
              set clusterid = min_cluster
              where id = row_perioxes.id;

              changes := changes + 1;
            end if;
        end loop;
        close cur_perioxes;
        
        --print_clusters();
        --dbms_output.put_line('changes: ' || changes);
        print_info();
        return changes;
    end;    
end;

-- 3. ipologismos meson oron gia lat,lon gia cluster = c
procedure calc_aver(c in number) is
begin
    declare
      cursor cur_cluster is 
        select * from perioxes
        where perioxes.CLUSTERID=c;
      sum_lat number := 0;
      sum_lon number := 0;
      kentro number  := 0;
      i integer :=0;
    begin
        open cur_cluster;
        
        loop
            fetch cur_cluster into row_perioxes;
            exit when cur_cluster%notfound;
            sum_lon := sum_lon + row_perioxes.lon;
            sum_lat := sum_lat + row_perioxes.lat;
            i:=i+1;
        end loop;
        close cur_cluster;

        select lat into kentro from kentra where id = c;
        sum_lat := sum_lat+kentro;
        select lon into kentro from kentra where id = c;
        sum_lon := sum_lon + kentro;
        
        i:=i+1;
        sum_lat := sum_lat/i;
        sum_lon := sum_lon/i;
        
        update kentra
        set lat = sum_lat, 
        lon = sum_lon
        where ID=c;
    end;
end;

-- ipologismos aver gia olus tus clusters
procedure step3 (k in integer) is
begin
    declare
    c number := 1;
    begin
    --dbms_output.put_line('STEP3');
        loop
            exit when c>k;
            calc_aver(c);
            c:=c+1;
        end loop;
    end;
end;



procedure step4(k in integer) is
begin
    declare
    cursor cur_perioxes is select * from perioxes;
    i number :=0;
    changes number := -1;
    begin
    --dbms_output.put_line('STEP4');
        loop
            changes := step2();
            exit when i>10 or changes = 0 ;
            step3(k);
            i:=i+1;
        end loop;
    end;
end;

procedure kmeans (k in integer) is
begin
declare
  changes number;
begin
    step1(k);
    --print_info();
    changes := step2();
    step3(k);
    step4(k);
end;
end;

--MAIN--
begin
    kmeans(n);
end;
end;