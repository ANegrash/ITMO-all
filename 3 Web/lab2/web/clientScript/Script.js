var checkSetX = false;


function checkTextY() {
    var strY = text_input_Y.value;
    if (isNaN(strY)) {
        alert(strY + " is wrong. You should write number!");
        return false;
    } else {
        var y = parseFloat(strY);
        if (y >= -3 && y <= 3) {
            text_input_Y.value = y;
            return true;
        } else {
            alert(str + " isn't in range[-3:3]!");
            return false;
        }
    }
}

function checkTextR() {
    var strR = text_input_R.value;
    if (isNaN(strR)) {
        alert(strR + " is wrong. You should write number!");
        return false;
    } else {
        var r = parseFloat(strR);
        if (r >= 2 && r <= 5) {
            text_input_R.value = r;
            return true;
        } else {
            alert(str + " isn't in range[2:5]!");
            return false;
        }
    }
}

function checkText() { //Проверка введённого в поле и реакция

    if (checkTextY() && checkTextR()) {
        if (checkSetX) {
            return true;
        } else {
            setX(0);
            return true;
        }
    }
    return false;
}

function setX(int) {    //Установка значения X получаемого от кнопок. Скрипт запускается при нажатии на кнопку
    document.getElementById("vX").setAttribute("value", int);
    var xNames = document.getElementsByName("xChoose");
    for (let i = 0; i < xNames.length; i++) {
        xNames[i].setAttribute("class", "btn btn-secondary");
    }
    xNames[int + 3].setAttribute("class", "btn btn-success");
    checkSetX = true;
}

const clickAnswer = function (event) {
    //Валидация текста
    if (!checkTextR()) {
        alert("Enter R");
        return;
    }

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

    var r = parseFloat(text_input_R.value);

    var x = (xCord / 120) * r;
    var y = -(yCord / 120) * r;

    const form = document.createElement('form');
    form.method = 'post';
    form.action = "/Lab2/control";

    const params = {
        answerX: x,
        answerY: y,
        answerR: r
    };

    for (const key in params) {
        if (params.hasOwnProperty(key)) {
            const hiddenField = document.createElement('input');
            hiddenField.type = 'hidden';
            hiddenField.name = key;
            hiddenField.value = params[key];

            form.appendChild(hiddenField);
        }
    }

    document.body.appendChild(form);
    form.submit();

};

//здесь мы не даём пользователю ввести в поле для Y ввести не те данные
function validateY() {
    this.value = this.value.replace(/[^\d.\-]/g, ""); //разрешаем ввод только цифр 0-9, запятой и минуса

    if(this.value.lastIndexOf("-")> 0) { //если пользователь вводит тире (минус) не самым первым символом...
        this.value = this.value.substr(0, this.value.lastIndexOf("-"));//то удаляем этот минус
    }

    if(this.value[0]== "-") {//если первый символ это минус (число отрицательно)...
        if(this.value[1]== "6" || this.value[1]== "7" || this.value[1]== "8" || this.value[1]== "9"){
            this.value = this.value.substr(0, 1);//то запрещаем вводить цифры 6,7,8,9
        }
        if(this.value[1]== "5" && this.value[2]!=""){
            this.value = this.value.substr(0, 2);//то запрещаем вводить число больше 0
        }

        if(this.value.length>2 && this.value[2]!=".") this.value=this.value[0]+this.value[1]+"."+this.value[2]; //если третий символ введён и он не запятая, то вставляем запятую между вторым и третим символом

        if(this.value.length>8) this.value = this.value.substr(0, 8); //если количество символов равно 8 (5 знаков после запятой), не даём вводить больше
    }else{ //если число положительно (первым введён не минус, а цифра)...
        if(this.value[0]== "." || this.value[0]== "4" || this.value[0]== "5" || this.value[0]== "6" || this.value[0]== "7" || this.value[0]== "8" || this.value[0]== "9"){
            this.value = this.value.substr(0, 0); //то эта цифра должна быть от 0 до 3
        }
        if(this.value[0]== "3" && this.value[1]!= ""){
            this.value = this.value.substr(0, 1); //то эта цифра должна быть от 0 до 3
        }

        if(this.value.length>1 && this.value[1]!=".") this.value=this.value[0]+"."+this.value[1]; //если второй символ введён и он не запятая, то вставляем запятую между первым и вторым символом
        if(this.value.length>7) this.value = this.value.substr(0, 7); //если количество символов равно 7 (5 знаков после запятой), не даём вводить больше
    }

    if(this.value.match(/\./g).length > 1) { //не даём ввести больше одной запятой
        this.value = this.value.substr(0, 0);
    }

    if(this.value.match(/\-/g).length > 1) { //не даём ввести больше одного минуса
        this.value = this.value.substr(0, 0);
    }
}



//здесь мы не даём пользователю ввести в поле для R ввести не те данные
function validateR() {
    this.value = this.value.replace(/[^\d/.]/g, ""); //разрешаем ввод только цифр 0-9 и запятой

    if(this.value[0]!== "-") { //если число положительно (первым введён не минус, а цифра)...
        if(this.value[0]== "." || this.value[0]== "0" || this.value[0]== "1" || this.value[0]== "6" || this.value[0]== "7" || this.value[0]== "8" || this.value[0]== "9"){
            this.value = this.value.substr(0, 0); //то эта цифра должна быть от 2 до 5
        }
        if(this.value[0]=== "5" && this.value[1]!== ""){
            this.value = this.value.substr(0, 1);
        }

        if(this.value.length>1 && this.value[1]!==".") this.value=this.value[0]+"."+this.value[1]; //если второй символ введён и он не запятая, то вставляем запятую между первым и вторым символом
        if(this.value.length>7) this.value = this.value.substr(0, 7); //если количество символов равно 7 (5 знаков после запятой), не даём вводить больше
    }

    if(this.value.match(/\./g).length > 1) { //не даём ввести больше одной запятой
        this.value = this.value.substr(0, 0);
    }

    if(this.value.match(/\-/g).length > 0) { //не даём ввести минус
        this.value = this.value.substr(0, 0);
    }
}


//Добавление скрипта для валидации перед отправкой
document.addEventListener('DOMContentLoaded', function () {

    //присваиваем данный скрипт нашему полю ввода координаты Y
    document.querySelector("#text_input_Y").onkeyup = validateY
//присваиваем данный скрипт нашему полю ввода координаты R
    document.querySelector("#text_input_R").onkeyup = validateR

    document.getElementById('image-coordinates').addEventListener('click', clickAnswer);
});