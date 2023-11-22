let rGlNum = 1;
let code = 0;
let tableOfShots = new Array();

// window.alert = function () {
// };

function updateClock() {
    let now = new Date();
    let time = now.getHours() + ':' + now.getMinutes() + ':' + now.getSeconds();
    let variant = "Variant 2622";
    // a cleaner way than string concatenation
    let date = [now.getDate(),
        now.getMonth() + 1,
        now.getFullYear()].join('.');
    document.getElementById('time').innerHTML = [variant, time, date].join(' | ');
    setTimeout(updateClock, 1000);
}

function setR(newR) {
    rGlNum = newR;
    printPaint();
}

const clickAnswer = function (event) {

    var box = document.getElementById("image-coordinates").getBoundingClientRect();

    var body = document.body;
    var docEl = document.documentElement;

    // (2)
    var scrollTop = window.pageYOffset || docEl.scrollTop || body.scrollTop;
    var scrollLeft = window.pageXOffset || docEl.scrollLeft || body.scrollLeft;

    // (3)
    var clientTop = docEl.clientTop || body.clientTop || 0;
    var clientLeft = docEl.clientLeft || body.clientLeft || 0;

    // (4)
    var top = box.top + scrollTop - clientTop;
    var left = box.left + scrollLeft - clientLeft;

    var xCord = ((event.clientX - left) / box.width) * 300;
    var yCord = ((event.clientY - top) / box.height) * 300;

    xCord = xCord - 150;
    yCord = yCord - 150;

    var r = parseFloat(rGlNum);

    var x = (xCord / 120) * r;
    var y = -(yCord / 120) * r;

    x = parseFloat(x.toString().slice(0, 5));
    y = parseFloat(y.toString().slice(0, 5));
    r = parseFloat(r.toString().slice(0, 5));

    send(x, y, r);
};

function send(x, y, r) {
    let numOflinesInTable = document.getElementById("tableBody").getElementsByTagName("tr").length;
    let numOfCirclesInPaint = document.getElementById("image-coordinates").getElementsByTagName("circle").length - 1;

    if (numOflinesInTable != code || numOfCirclesInPaint != code) {
        code = 0;
    } else {
        code = numOflinesInTable;
    }
    console.log("X: " + x + " Y: " + y + " R: " + r);
    $.ajax({
        url: '/Lab4/faces/checkShot',
        headers: {
            "rows": code
        },
        method: 'POST',
        dataType: 'text',
        data: {coord_x: x, coord_y: y, coord_r: r},
        success: function (data, textStatus, request) {
            console.log(data);
            console.log(request.getResponseHeader('rows'));

            saveToApp(data);
            writeTable();
            printPaint();
        }
    });
}

function saveToApp(data) {
    if (code !== 0 && code !== -1) {
        tableOfShots.push(data.slice(0, data.length - 1).split(" "));
    } else {
        let ar = data.slice(0, data.length - 1).split("\n");
        tableOfShots = new Array();
        for (let i = 0; i < ar.length; i++) {
            tableOfShots.push(ar[i].split(" "));
        }
    }
    console.log(tableOfShots);
}

function writeTable() {
    let inHTML = "";
    for (let i = 0; i < tableOfShots.length; i++) {
        inHTML += "<tr>";
        for (let j = 0; j < 6; j++) {
            inHTML += "<td>" + tableOfShots[i][j] + "</td>";
        }
        inHTML += "</tr>";
    }
    document.getElementById("tableBody").innerHTML = inHTML;
}

function printPaint() {
    let inHTML = "<rect width=\"300\" height=\"300\" fill=\"rgb(255,255,255)\" stroke-width=\"1\" stroke=\"rgb(0,0,0)\"></rect>\n" +
        "\n" +
        "                <circle cx=\"150\" cy=\"150\" r=\"60\" fill=\"rgb(0,255,255)\" stroke-width=\"1\" stroke=\"rgb(0,0,0)\"></circle>\n" +
        "                <polyline points=\"150,150 150,300 300,300 300,0 0,0 0,150 150,150\" fill=\"rgb(255,255,255)\"\n" +
        "                          stroke-width=\"1\" stroke=\"rgb(0,0,0)\"></polyline>\n" +
        "\n" +
        "                <rect x=\"150\" y=\"150\" width=\"120\" height=\"60\" fill=\"rgb(0,255,255)\" stroke-width=\"1\"\n" +
        "                      stroke=\"rgb(50,50,50)\"></rect>\n" +
        "\n" +
        "                <polyline points=\"150,30 90,150 150,150 150,90\" fill=\"rgb(0,255,255)\" stroke-width=\"1\"\n" +
        "                          stroke=\"rgb(0,0,0)\"></polyline>\n" +
        "\n" +
        "                <line x1=\"150\" y1=\"0\" x2=\"150\" y2=\"500\" stroke-width=\"1\" stroke=\"rgb(0,0,0)\"></line>\n" +
        "                <line x1=\"0\" y1=\"150\" x2=\"300\" y2=\"150\" stroke-width=\"1\" stroke=\"rgb(0,0,0)\"></line>\n" +
        "\n" +
        "                <line x1=\"145\" y1=\"30\" x2=\"155\" y2=\"30\" stroke-width=\"1\" stroke=\"rgb(0,0,0)\"></line>\n" +
        "                <line x1=\"145\" y1=\"90\" x2=\"155\" y2=\"90\" stroke-width=\"1\" stroke=\"rgb(0,0,0)\"></line>\n" +
        "\n" +
        "                <line x1=\"30\" y1=\"145\" x2=\"30\" y2=\"155\" stroke-width=\"1\" stroke=\"rgb(0,0,0)\"></line>\n" +
        "                <line x1=\"90\" y1=\"145\" x2=\"90\" y2=\"155\" stroke-width=\"1\" stroke=\"rgb(0,0,0)\"></line>\n" +
        "\n" +
        "                <line x1=\"210\" y1=\"145\" x2=\"210\" y2=\"155\" stroke-width=\"1\" stroke=\"rgb(0,0,0)\"></line>\n" +
        "                <line x1=\"270\" y1=\"145\" x2=\"270\" y2=\"155\" stroke-width=\"1\" stroke=\"rgb(0,0,0)\"></line>\n" +
        "\n" +
        "                <line x1=\"145\" y1=\"210\" x2=\"155\" y2=\"210\" stroke-width=\"1\" stroke=\"rgb(0,0,0)\"></line>\n" +
        "                <line x1=\"145\" y1=\"270\" x2=\"155\" y2=\"270\" stroke-width=\"1\" stroke=\"rgb(0,0,0)\"></line>\n" +
        "\n" +
        "                <polyline points=\"150,0 140,15 150,5 160,15 150,0\" fill=\"rgb(249,249,249)\" stroke-width=\"1\"\n" +
        "                          stroke=\"rgb(0,0,0)\"></polyline>\n" +
        "                <polyline points=\"300,150 285,140 295,150 285,160 300,150\" fill=\"rgb(249,249,249)\" stroke-width=\"1\"\n" +
        "                          stroke=\"rgb(0,0,0)\"></polyline>";

    for (let i = 0; i < tableOfShots.length; i++) {
        inHTML += "<circle cx=\"" +
            (150 + 120 * (parseFloat(tableOfShots[i][0]) / rGlNum)) +
            "\" cy=\"" +
            (150 - 120 * (parseFloat(tableOfShots[i][1]) / rGlNum)) +
            "\" r=\"5\" ";
        if ("true".localeCompare(tableOfShots[i][3])) {
            inHTML += "fill=\"rgb(255,0,0)\" ";
        } else {
            inHTML += "fill=\"rgb(0,255,0)\" ";
        }
        inHTML += "stroke-width=\"1\"\n stroke=\"rgb(0,0,0)\"/>";
    }
    document.getElementById("image-coordinates").innerHTML = inHTML;
}

function exit() {
    $.ajax({
        url: '/Lab4/faces/exit',
        method: 'POST',
        dataType: 'text',
        success: function (data) {
            tableOfShots = new Array();
            location.href = '../';
        }
    });
}
function onlyDigits() {
    this.value = this.value.replace(/[^\d\,\-]/g, "");//разрешаем ввод только цифр 0-9, запятой и минуса

    if(this.value.lastIndexOf("-")> 0) {//если пользователь вводит тире (минус) не самым первым символом...
        this.value = this.value.substr(0, this.value.lastIndexOf("-"));//то удаляем этот минус
    }

    if(this.value[0]== "-") {//если первый символ это минус (число отрицательно)...
        if(this.value[1]== "6" || this.value[1]== "7" || this.value[1]== "8" || this.value[1]== "9"){
            this.value = this.value.substr(0, 1);//то запрещаем вводить цифры 4,5,6,7,8,9
        }
        if(this.value[1]== "5" && this.value[2]!=""){
            this.value = this.value.substr(0, 2);//то запрещаем вводить число больше 0
        }

        if(this.value.length>2 && this.value[2]!=",") this.value=this.value[0]+this.value[1]+","+this.value[2];//если третий символ введён и он не запятая, то вставляем запятую между вторым и третим символом
        if(this.value.length>8) this.value = this.value.substr(0, 8);//если количество символов равно 8 (5 знаков после запятой), не даём вводить больше
    }else{//если число положительно (первым введён не минус, а цифра)...
        if(this.value[0]== "," || this.value[0]== "6" || this.value[0]== "7" || this.value[0]== "8" || this.value[0]== "9"){
            this.value = this.value.substr(0, 0);//то эта цифра должна быть от 0 до 5
        }
        if(this.value[0]== "5" && this.value[1]!= ""){
            this.value = this.value.substr(0, 1);//то эта цифра должна быть от 0 до 5
        }

        if(this.value.length>1 && this.value[1]!=",") this.value=this.value[0]+","+this.value[1];//если второй символ введён и он не запятая, то вставляем запятую между первым и вторым символом
        if(this.value.length>7) this.value = this.value.substr(0, 7);//если количество символов равно 7 (5 знаков после запятой), не даём вводить больше
    }

    if(this.value.match(/\,/g).length > 1) {//не даём ввести больше одной запятой
        this.value = this.value.substr(0, 0);
    }

    if(this.value.match(/\-/g).length > 1) {//не даём ввести больше одного минуса
        this.value = this.value.substr(0, 0);
    }
}

function clear(){
    console.log("Start clearing")
    $.ajax({
        url: '/Lab4/faces/checkShot',
        headers: {
            "rows": -2
        },
        method: 'POST',
        dataType: 'text',
        success: function (data, textStatus, request) {
            tableOfShots = new Array();
            code = 0;
            writeTable();
            printPaint();
            console.log("clearing success")
        }
    });
}

document.addEventListener('DOMContentLoaded', function () {
    document.getElementById('image-coordinates').addEventListener('click', clickAnswer);
    document.querySelector("#text_input_Y").onkeyup = onlyDigits
    updateClock();
    $.ajax({
        url: '/Lab4/faces/checkShot',
        headers: {
            "rows": -1
        },
        method: 'POST',
        dataType: 'text',
        success: function (data, textStatus, request) {
            if (request.getResponseHeader('rows') > 0) {
                saveToApp(data);
                writeTable();
                printPaint();
            }
        }
    });

});