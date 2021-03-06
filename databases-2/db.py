import cx_Oracle, unicodedata

create_tables = """drop table perioxes
create table perioxes (id integer not null, name varchar2(100) not null, lat number not null, lon number not null, clusterid number null)
drop table kentra
create table kentra (id integer generated by default on null as identity, lat number not null, lon number not null)
drop table apostaseis
create table apostaseis (pid integer, kid integer, distance number)
drop table apostaseis
create table apostaseis (pid integer, kid integer, distance number)
drop table results
create table results (vima_id integer, perioxi_id integer, perioxi_name varchar2(100), p_lat number, p_lon number, cluster_id integer, kentro_id integer, k_lat number, k_lon number, distance number)"""

insert_locations = """insert into perioxes values (1,'samos',37.7245805,26.6778265,0)
insert into perioxes values (2,'china',34.41202,86.0325116,0)
insert into perioxes values (3,'cyprus',35.1636339,32.3039272,0)
insert into perioxes values (4,'israel',31.3867049,32.8377084,0)
insert into perioxes values (5,'germany',51.0898808,5.9672522,0)
insert into perioxes values (6,'uk',46.3224896,-5.3810526,0)
insert into perioxes values (7,'usa',36.208349,-113.7368394,0)
insert into perioxes values (8,'philippines',11.5561608,113.5719421,0)
insert into perioxes values (9,'hawai',20.4456008,-159.749638,0)
insert into perioxes values (10,'japan',31.6783217,120.2783573,0)"""

def query(string,cursor):
    for i in string.split("\n"):
        print(i)
        try:
            cursor.execute(i)
            print("OK")
        except Exception as ex :
            print("ERROR")
            print(ex)

def calculate(locations,k):
    con = cx_Oracle.connect('c##11186','1234',
            cx_Oracle.makedsn('195.251.162.129',1521,'db2'))
    cur = con.cursor()

    query(create_tables,cur)

    cur.prepare("insert into perioxes values (:id,:name,:lat,:lon,:clusterid)")
    for row in locations:
        row['name'] = unicodedata.normalize('NFKD',row['name']).encode('ascii','ignore').decode()
        cur.execute(None,row)

    cur.callproc('project',(k,))
    cur.execute('select * from results')
    res = cur.fetchall()
    
    cur.close()
    con.close()

    return res
