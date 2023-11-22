var list_of_X = new Array();
var list_of_Y = new Array();
var x;
var y;
var R = '-1';

//Graph
var plot_canvas = document.getElementById("plot");
var plot_context = plot_canvas.getContext("2d");
plot_context.beginPath();
plot_context.arc(150, 150, 50, Math.PI, 3*Math.PI/2);
plot_context.lineTo(150, 150);
plot_context.closePath();
plot_context.rect(150, 100, 100, 50);
plot_context.fillStyle = '#3BA4C7';
plot_context.fill();
plot_context.beginPath();
plot_context.moveTo(150, 150);
plot_context.lineTo(150, 200);
plot_context.lineTo(200, 150);
plot_context.lineTo(150, 150);
plot_context.closePath();
plot_context.fillStyle = '#3BA4C7';
plot_context.fill();
plot_context.beginPath();

//Ox
plot_context.moveTo(30, 150);
plot_context.lineTo(270, 150);
plot_context.lineTo(260, 140);
plot_context.moveTo(270, 150);
plot_context.lineTo(260, 160);

//Oy
plot_context.moveTo(150, 30);
plot_context.lineTo(140, 40);
plot_context.moveTo(150, 30);
plot_context.lineTo(160, 40);
plot_context.moveTo(150, 30);
plot_context.lineTo(150, 270);
plot_context.moveTo(30, 150);
plot_context.closePath();
plot_context.stroke();

//Buttons
document.getElementById("r1").addEventListener("click", changeR1, false);
document.getElementById("r2").addEventListener("click", changeR2, false);
document.getElementById("r3").addEventListener("click", changeR3, false);
document.getElementById("r4").addEventListener("click", changeR4, false);
document.getElementById("r5").addEventListener("click", changeR5, false);
plot_canvas.addEventListener("click", drawPoint, false);

function drawPoint(e) {
    if(R == '-1') {
        alert("Выберите какое-нибудь значение R");
    } else {
        var cell = getCursorPosition(e);
        list_of_X.push(x);
        list_of_Y.push(y);
        drawDefinedPoint(x, y);
        document.getElementById("canvaForm:canvaX").value = x;
        document.getElementById("canvaForm:canvaY").value = y;
        canvaReady();
    }
}

function drawDefinedPoint(xx, yy) {
    plot_context.beginPath();
    plot_context.rect(xx, yy, 5, 5);
    xx -= 150;
    yy -= 150;
    yy *= -1;
    xx = xx/100*5;
    yy = yy/100*5;
    plot_context.fillStyle = 'gray';
    if (checkArea(xx, yy, R) == 1) plot_context.fillStyle = 'white';
    plot_context.fill();
    plot_context.closePath();
    x = xx;
    y = yy;
}

function checkArea(x, y, r){
    if((x >= 0 && y >= 0) && (x <= r) && (y <= (r/2))){
        return 1;
    } else if(x >= 0 && y <= 0 && y >= (x-(r/2))){
        return 1;
    } else if (x <= 0 && y >= 0 && (r/2) >= Math.sqrt(y*y+x*x)){
        return 1;
    } else {
        return 0;
    }
}

function getCursorPosition(e) {
    if (e.pageX != undefined && e.pageY != undefined) {
        x = e.pageX;
        y = e.pageY;
    } else {
        x = e.clientX + document.body.scrollLeft +
            document.documentElement.scrollLeft;
        y = e.clientY + document.body.scrollTop +
            document.documentElement.scrollTop;
    }
    x -= plot_canvas.offsetLeft ;
    y -= plot_canvas.offsetTop ;
}

function changeR1(e) {
    R = 1;
    document.getElementById("disr").value = R;
    drawCanva(1);
    list_of_X.forEach(function(item, i, arr) {
        drawDefinedPoint(item, list_of_Y[i]);
    });
    document.getElementById("mesR").style.display = "none";
    document.getElementById("infoR").innerHTML = "You set R = 1";
}
function changeR2(e) {
    R = 2;
    document.getElementById("disr").value = R;
    drawCanva(2);
    list_of_X.forEach(function(item, i, arr) {
        drawDefinedPoint(item, list_of_Y[i]);
    });
    document.getElementById("mesR").style.display = "none";
    document.getElementById("infoR").innerHTML = "You set R = 2";
}
function changeR3(e) {
    R = 3;
    document.getElementById("disr").value = R;
    drawCanva(3);
    list_of_X.forEach(function(item, i, arr) {
        drawDefinedPoint(item, list_of_Y[i]);
    });
    document.getElementById("mesR").style.display = "none";
    document.getElementById("infoR").innerHTML = "You set R = 3";
}
function changeR4(e) {
    R = 4;
    document.getElementById("disr").value = R;
    drawCanva(4);
    list_of_X.forEach(function(item, i, arr) {
        drawDefinedPoint(item, list_of_Y[i]);
    });
    document.getElementById("mesR").style.display = "none";
    document.getElementById("infoR").innerHTML = "You set R = 4";
}
function changeR5(e) {
    R = 5;
    document.getElementById("disr").value = R;
    drawCanva(5);
    list_of_X.forEach(function(item, i, arr) {
        drawDefinedPoint(item, list_of_Y[i]);
    });
    document.getElementById("mesR").style.display = "none";
    document.getElementById("infoR").innerHTML = "You set R = 5";
}

function drawCanva(mult) {
    plot_canvas.width+=0;
    plot_context.beginPath();
    plot_context.arc(150, 150, 10*mult, Math.PI, 3*Math.PI/2);
    plot_context.lineTo(150, 150);
    plot_context.closePath();
    plot_context.rect(150, 100+10*(5-mult), 20*mult, 10*mult);
    plot_context.fillStyle = '#3BA4C7';
    plot_context.fill();
    plot_context.beginPath();
    plot_context.moveTo(150, 150);
    plot_context.lineTo(150, 200-10*(5-mult));
    plot_context.lineTo(200-10*(5-mult), 150);
    plot_context.lineTo(150, 150);
    plot_context.closePath();
    plot_context.fillStyle = '#3BA4C7';
    plot_context.fill();
    plot_context.beginPath();

    //Ox
    plot_context.moveTo(30, 150);
    plot_context.lineTo(270, 150);
    plot_context.lineTo(260, 140);
    plot_context.moveTo(270, 150);
    plot_context.lineTo(260, 160);

    //Oy
    plot_context.moveTo(150, 30);
    plot_context.lineTo(140, 40);
    plot_context.moveTo(150, 30);
    plot_context.lineTo(160, 40);
    plot_context.moveTo(150, 30);
    plot_context.lineTo(150, 270);
    plot_context.moveTo(30, 150);
    plot_context.closePath();
    plot_context.stroke();
    changeR();
}