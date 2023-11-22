<!DOCTYPE html>
<html>
    <head>
        <title>Лабораторная работа №1 //Неграш Андрей</title>
		<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
		<link rel="stylesheet" type="text/css" href="style2.css">
    </head>
    <body>
        <?php
        //запоминаем время начала работы скрипта
        $start = microtime(true);
        //получаем дату и время по москве
        date_default_timezone_set('Europe/Moscow');
        $now= date("d.m.y H:i");
        //получаем параметры из index.php
        $coordX=$_POST['coordX'];
        $coordYSee=$_POST['coordY'];
        $paramR=$_POST['paramR'];
        //меняем в Y запятую на точку
        $coordNY=explode(",",$coordYSee);
        $coordY=$coordNY[0].".".$coordNY[1];
	//готовимся к вычислению попадания в область
        $halfR=$paramR/2;
        $chetvert=0;
	//узнаём четверть, в которой располагается точка
        if($coordX>0 && $coordY>0) $chetvert=2;//правая верхняя
        if($coordX<0 && $coordY>0) $chetvert=1;//левая верхняя
        if($coordX>0 && $coordY<0) $chetvert=3;//правая нижняя
        if($coordX<0 && $coordY<0) $chetvert=4;//левая нижняя
        if ($chetvert==1){//в этой четверти совсем нет области, так что всё просто
           $message= "Точка не входит в область";
        }

        if ($chetvert==2){//вспоминаем уравнение наклонной прямой y=kx+b, где b=-1, и если ниже, то входит, если выше, то нет
            $yfunk=-$coordX+$halfR;
            if($yfunk>=$coordY){
                $message= "Точка входит в область";
            }else{
                $message= "Точка не входит в область";
            }
        }

        if ($chetvert==3){//поскольку прямоугольник, то X<=R и Y<=R/2. Если да, то в области. нет - нет
            if($coordY<=$halfR && $coordX<=$paramR){
                $message= "Точка входит в область";
            }else{
                $message= "Точка не входит в область";
            }
        }

        if ($chetvert==4){//окружность с центром в точке (0;0). Находим расстояние от нашей точки до центра окружности, и если оно больше R/2, то точка не в области.
            $distance=$coordX*$coordX+$coordY*$coordY;
            $distance=sqrt($distance);
            if ($distance>$halfR){
                $message= "Точка не входит в область";
            }else{
                $message= "Точка входит в область";
            }
        }
        if ($chetvert==0){//если точка лежит на координатной оси (X=0 или Y=0)
            if($coordX==0){//если лежит на оси y...
                if($coordY<=$halfR && $coordY>=-$halfR) {//то координата Y должна быть в диапазоне [R/2; -R/2]
                    $message="Точка входит в область";
                }else{
                    $message="Точка не входит в область";
                }
            }else{//если лежит на оси x...
                if($coordX<=$paramR && $coordX>=-$halfR) {//то координата X должна быть в диапазоне [R; -R/2]
                    $message="Точка входит в область";
                }else{
                    $message="Точка не входит в область";
                }
            }
        }
	//получаем время окончания работы скрипта
        $finish = microtime(true);
	//высчитываем время работы (разницу) и округляем
        $timeWork=$finish-$start;
        $timeWork=round($timeWork,7);
	//заполняем переменную сессии для отображения всей таблицы
        $ses=$_SESSION['counter'];
        $ses++;
        $_SESSION['str_'.$ses]="    <tr>
        <td> $now</td>
        <td> $timeWork с</td>
        <td>$coordX </td>
        <td> $coordYSee </td>
        <td> $paramR </td>
        <td> $message </td>
    </tr>";

?>
<!--Выводим сообщение о результате-->
<h3><center><?php echo $message; ?></center></h3>
<br>
<center>
<table>
    <tr>
        <td>Дата и время запроса</td>
        <td>Время выполнения</td>
        <td>Координата X</td>
        <td>Координата Y</td>
        <td>Параметр R</td>
        <td>Результат</td>
    </tr>
    <?php
	//таблица истории введённых значений. Работает на костылях и некрасиво, но работает
    for($m=1;$m<=$ses;$m++){
        echo $_SESSION['str_'.$m];
    }
    ?>

</table>
</center>
    </body>
</html>