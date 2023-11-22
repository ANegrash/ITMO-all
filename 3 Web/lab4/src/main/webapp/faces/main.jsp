<!DOCTYPE html>
<html>
<head>
    <title>Lab 4</title>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/2.2.0/jquery.min.js"></script>
    <script src="https://unpkg.com/vue"></script>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>

    <link rel="stylesheet" href="../styles/main.css"/>
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css"
          integrity="sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T" crossorigin="anonymous">
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.7/umd/popper.min.js"
            integrity="sha384-UO2eT0CpHqdSJQ6hJty5KVphtPhzWj9WO1clHTMGa3JDZwrnQq4sF86dIHNDz0W1"
            crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js"
            integrity="sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM"
            crossorigin="anonymous"></script>

    <script type="text/javascript" src="../scripts/main.js"></script>
</head>
<body>
<div id="header">
    <img src="../resourcesPicture/logo.jpg" width="10px" height="10px" alt="logo"/><br/>
    This labwork created by: Negrash Andrey and Rogachev Kirill. <br/>Variant 2622<br/>
    <div id="time"></div>
    <button onclick="exit()" id="toIndex">Go back</button>
</div>
<div id="content">
    <div id="leftSide">

        <div id="picture" height="310px">
            <svg id="image-coordinates" style="height:300px">
                <rect width="300" height="300" fill="rgb(255,255,255)" stroke-width="1" stroke="rgb(0,0,0)"></rect>

                <circle cx="150" cy="150" r="60" fill="rgb(0,255,255)" stroke-width="1" stroke="rgb(0,0,0)"></circle>
                <polyline points="150,150 150,300 300,300 300,0 0,0 0,150 150,150" fill="rgb(255,255,255)"
                          stroke-width="1" stroke="rgb(0,0,0)"></polyline>

                <rect x="150" y="150" width="120" height="60" fill="rgb(0,255,255)" stroke-width="1"
                      stroke="rgb(50,50,50)"></rect>

                <polyline points="150,30 90,150 150,150 150,90" fill="rgb(0,255,255)" stroke-width="1"
                          stroke="rgb(0,0,0)"></polyline>

                <line x1="150" y1="0" x2="150" y2="500" stroke-width="1" stroke="rgb(0,0,0)"></line>
                <line x1="0" y1="150" x2="300" y2="150" stroke-width="1" stroke="rgb(0,0,0)"></line>

                <line x1="145" y1="30" x2="155" y2="30" stroke-width="1" stroke="rgb(0,0,0)"></line>
                <line x1="145" y1="90" x2="155" y2="90" stroke-width="1" stroke="rgb(0,0,0)"></line>

                <line x1="30" y1="145" x2="30" y2="155" stroke-width="1" stroke="rgb(0,0,0)"></line>
                <line x1="90" y1="145" x2="90" y2="155" stroke-width="1" stroke="rgb(0,0,0)"></line>

                <line x1="210" y1="145" x2="210" y2="155" stroke-width="1" stroke="rgb(0,0,0)"></line>
                <line x1="270" y1="145" x2="270" y2="155" stroke-width="1" stroke="rgb(0,0,0)"></line>

                <line x1="145" y1="210" x2="155" y2="210" stroke-width="1" stroke="rgb(0,0,0)"></line>
                <line x1="145" y1="270" x2="155" y2="270" stroke-width="1" stroke="rgb(0,0,0)"></line>

                <polyline points="150,0 140,15 150,5 160,15 150,0" fill="rgb(249,249,249)" stroke-width="1"
                          stroke="rgb(0,0,0)"></polyline>
                <polyline points="300,150 285,140 295,150 285,160 300,150" fill="rgb(249,249,249)" stroke-width="1"
                          stroke="rgb(0,0,0)"></polyline>

            </svg>
        </div>

        <form id="form">

            <div id="xText">
                X:
                <input type="checkbox" name="coordX" value="-3" v-model="coord_x" id="x-3" checked>
                <label class="form-check-label" for="x-3">-3</label>
                <input type="checkbox" name="coordX" value="-2" v-model="coord_x" id="x-2">
                <label class="form-check-label" for="x-2">-2</label>
                <input type="checkbox" name="coordX" value="-1" v-model="coord_x" id="x-1">
                <label class="form-check-label" for="x-1">-1</label>
                <input type="checkbox" name="coordX" value="0" v-model="coord_x" id="x0">
                <label class="form-check-label" for="x0">0</label>
                <input type="checkbox" name="coordX" value="1" v-model="coord_x" id="x1">
                <label class="form-check-label" for="x1">1</label>
                <input type="checkbox" name="coordX" value="2" v-model="coord_x" id="x2">
                <label class="form-check-label" for="x2">2</label>
                <input type="checkbox" name="coordX" value="3" v-model="coord_x" id="x3">
                <label class="form-check-label" for="x3">3</label>
                <input type="checkbox" name="coordX" value="4" v-model="coord_x" id="x4">
                <label class="form-check-label" for="x4">4</label>
                <input type="checkbox" name="coordX" value="5" v-model="coord_x" id="x5">
                <label class="form-check-label" for="x5">5</label>
            </div>

            <div id="yButtons">
                Y[-5;5]:
                <input type="text" id="text_input_Y" v-model="coord_y" value="0"/>
            </div>

            <div id="rButtons">
                R:
                <input type="checkbox" class="rCheckbox" name="coordR" value="-3" v-model="coord_r" onclick="setR(-3)" id="r-3" checked>
                <label class="form-check-label" for="r-3">-3</label>
                <input type="checkbox" class="rCheckbox" name="coordR" value="-2" v-model="coord_r" onclick="setR(-2)" id="r-2">
                <label class="form-check-label" for="r-2">-2</label>
                <input type="checkbox" class="rCheckbox" name="coordR" value="-1" v-model="coord_r" onclick="setR(-1)" id="r-1">
                <label class="form-check-label" for="r-1">-1</label>
                <input type="checkbox" class="rCheckbox" name="coordR" value="0" v-model="coord_r" onclick="setR(0)" id="r0">
                <label class="form-check-label" for="r0">0</label>
                <input type="checkbox" class="rCheckbox" name="coordR" value="1" v-model="coord_r" onclick="setR(1)" id="r1">
                <label class="form-check-label" for="r1">1</label>
                <input type="checkbox" class="rCheckbox" name="coordR" value="2" v-model="coord_r" onclick="setR(2)" id="r2">
                <label class="form-check-label" for="r2">2</label>
                <input type="checkbox" class="rCheckbox" name="coordR" value="3" v-model="coord_r" onclick="setR(3)" id="r3">
                <label class="form-check-label" for="r3">3</label>
                <input type="checkbox" class="rCheckbox" name="coordR" value="4" v-model="coord_r" onclick="setR(4)" id="r4">
                <label class="form-check-label" for="r4">4</label>
                <input type="checkbox" class="rCheckbox" name="coordR" value="5" v-model="coord_r" onclick="setR(5)" id="r5">
                <label class="form-check-label" for="r5">5</label>
            </div>

            <div id="sender">
                <input type="submit" value="Send" v-on:click="sdc"/>
            </div>

        </form>
    </div>


    <div id="centerSide">
        <div>
            <input type="button" value="Clear" v-on:click="clear"/>
        </div>
    </div>


    <div id="rightSide">
        <div id="table" class="custom_scrollbar">
            <table class="table table-striped page-table-T" border="1">
                <thead class="header" id="headerTable">
                <tr>
                    <th class="x-class stickyTh">
                        <center>X</center>
                    </th>
                    <th class="y-class stickyTh">
                        <center>Y</center>
                    </th>
                    <th class="r-class stickyTh">
                        <center>R</center>
                    </th>
                    <th class="som-class stickyTh">
                        <center>Y/N</center>
                    </th>
                    <th class="stt-class stickyTh">
                        <center>Start time</center>
                    </th>
                    <th class="sct-class stickyTh">
                        <center>Script time</center>
                    </th>
                </tr>
                </thead>
                <tbody id="tableBody">

                </tbody>
            </table>
        </div>
    </div>
</div>
<style>
    @media (min-width: 1245px) {
        #header{
            width: 100%;
        }
        #leftSide {
            width: 49%;
        }
        #rightSide{
            width: 49%;
        }
    }
    @media (min-width: 791px) and (max-width: 1245px) {
        #header{
            width: 49%;
        }
        #leftSide {
            width: 49%;
        }
        #rightSide{
            width: 100%;
        }
    }
    @media (max-width: 791px) {
        #header{
            width: 100%;
        }
        #leftSide {
            width: 100%;
        }
        #rightSide{
            width: 100%;
        }
    }
</style>
<script>
    new Vue({
        el: '#form',
        data: {
            coord_r: [],
            coord_x: [],
            coord_y: ""
        },
        methods: {
            sdc: function (event) {
                send(parseFloat(this.coord_x[0]), parseFloat(this.coord_y), parseFloat(this.coord_r[0]));
            }
        }
    });
    new Vue({
        el: '#centerSide',

        methods: {
            clear: function (event) {
                clear();
            }
        }
    });
    var inputs = document.getElementsByName("coordX");
    for (var i = 0; i < inputs.length; i++) inputs[i].onchange = checkboxHandler;
    var inputs2 = document.getElementsByName("coordR");
    for (var i2 = 0; i2 < inputs2.length; i2++) inputs2[i2].onchange = checkboxHandler2;

    function checkboxHandler(e) {
        for (var i = 0; i < inputs.length; i++)
            if (inputs[i].checked && inputs[i] !== this) inputs[i].checked = false;
    }

    function checkboxHandler2(e) {
        for (var i2 = 0; i2 < inputs2.length; i2++)
            if (inputs2[i2].checked && inputs2[i2] !== this) inputs2[i2].checked = false;
    }
</script>
</body>
</html>