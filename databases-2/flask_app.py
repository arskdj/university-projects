from flask import Flask, request, render_template, json
import db
from pprint import pprint
from collections import OrderedDict

app = Flask(__name__)
@app.route("/")
def hello():
    return render_template('maps.html')

@app.route("/results", methods=['POST'])
def results():
    k = int(request.form['k'])
    locations = request.form['markers_array']
    locations = json.loads(locations)
    results = db.calculate(locations,k)
    pprint(results)

    table = OrderedDict()
    total_steps = results[len(results)-1][0]
    for i in range(1,total_steps+1):
        step = [x for x in results if  x[0] == i]

        table[i] = OrderedDict()
        for row in step:
            table[i][row[1]] = OrderedDict()

        for row in step:
            table[i][row[1]]['name'] = row[2]
            table[i][row[1]]['lat'] = row[3]
            table[i][row[1]]['lon'] = row[4]
            table[i][row[1]]['cluster'] = row[5]
            table[i][row[1]][row[7:9]] = row[9]
    pprint(table)
    return render_template('results.html',results=table)
