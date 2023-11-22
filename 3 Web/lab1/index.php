<!DOCTYPE html>
<html>
	<head>
		<title>Лабораторная работа №1 //Неграш Андрей</title>
		<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
		<link rel="stylesheet" type="text/css" href="style.css">
	</head>
	<body>
		<div class="header">
			<h3><center>Неграш Андрей Владимирович</center></h3>
			<p>
			    <center>
			        <b>группа:</b> P3230
			    </center>
			    <center>
			        <b>вариант:</b> 2619
			    </center>
		    	</p>
			<hr>
		</div>
		<?php
			session_start();
			if (!isset($_SESSION['counter'])) $_SESSION['counter']=0;
            		$_SESSION['counter']++;
        	?>
		<form action="index.php" method="post">
    			<div class="form-row">
    		    		<div id="coord">
    		        		Параметр R:
					<p><input type="radio" name="paramR" value="1" checked>1</p>
					<p><input type="radio" name="paramR" value="1.5">1,5</p>
					<p><input type="radio" name="paramR" value="2">2</p>
					<p><input type="radio" name="paramR" value="2.5">2,5</p>
					<p><input type="radio" name="paramR" value="3">3</p>
    		        	</div>
    		    		<div id="coord">
    		        		Координата X:
                    			<p><input type="checkbox" name="coordX" value="-3" checked>-3</p>
                    			<p><input type="checkbox" name="coordX" value="-2" >-2</p>
                    			<p><input type="checkbox" name="coordX" value="-1" >-1</p>
                    			<p><input type="checkbox" name="coordX" value="0" >0</p>
                    			<p><input type="checkbox" name="coordX" value="1" >1</p>
                    			<p><input type="checkbox" name="coordX" value="2" >2</p>
                    			<p><input type="checkbox" name="coordX" value="3" >3</p>
                    			<p><input type="checkbox" name="coordX" value="4" >4</p>
                    			<p><input type="checkbox" name="coordX" value="5" >5</p>
    		    		</div>
    		    		<div id="coord">
    		        		Координата Y:
    		        		<input type="text" class="number" name="coordY" required>
    		    		</div>
    		    		<input type="submit" class="button">
    			</div>
		</form>

		<div class="form-row">
		    <center>
		        <img src="myTask.png">
		    </center>
		</div>
		<?php
			include 'script.php'; //определение попадания точки в область происходит здесь. ВАЖНО! в файле .html эта строка не будет работать
		?>
		<script>
			//здесь мы не даём пользователю ввести в поле для Y ввести не те данные
			function onlyDigits() {
      				this.value = this.value.replace(/[^\d\,\-]/g, "");//разрешаем ввод только цифр 0-9, запятой и минуса

          			if(this.value.lastIndexOf("-")> 0) {//если пользователь вводит тире (минус) не самым первым символом...
            				this.value = this.value.substr(0, this.value.lastIndexOf("-"));//то удаляем этот минус
          			}

        			if(this.value[0]== "-") {//если первый символ это минус (число отрицательно)...
            				if(this.value[1]== "4" || this.value[1]== "5" || this.value[1]== "6" || this.value[1]== "7" || this.value[1]== "8" || this.value[1]== "9"){
                				this.value = this.value.substr(0, 1);//то запрещаем вводить цифры 4,5,6,7,8,9
            				}
					if(this.value[1]== "3" && this.value[2]!=""){
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
			//присваиваем данный скрипт нашему полю ввода
    			document.querySelector(".number").onkeyup = onlyDigits


		//следующие строчки я скопипастил со stackoverflow и они не дают выбирать больше одного checkbox-а. Работает - не трогай
            	var inputs = document.getElementsByName("coordX");
            	for(var i = 0; i < inputs.length; i++) inputs[i].onchange = checkboxHandler;

            	function checkboxHandler(e) {
                	for(var i = 0; i < inputs.length; i++)
                    		if(inputs[i].checked && inputs[i] !== this) inputs[i].checked = false;
            	}
		</script>
	</body>
</html>