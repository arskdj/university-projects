#!/bin/bash
export LC_ALL=C.UTF-8
export LANG=C.UTF-8
export LD_LIBRARY_PATH=/usr/lib/oracle/12.2/client64/lib:/usr/lib/oracle/12.2/client64/lib:/opt/oracle/instantclient_12_2:$LD_LIBRARY_PATH
export FLASK_APP=flask_app.py 
flask run --host=0.0.0.0
