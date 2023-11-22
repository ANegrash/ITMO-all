<?
    $login = $_POST['login'];
    $pass = $_POST['password']; 
    
    if (empty($login) or empty($pass)) {
        ?>
            <!DOCTYPE html>
            <html lang="ru">
                <head>
                    <meta charset="utf-8">
                    <meta name="viewport" content="width=device-width, initial-scale=1">
                    <meta name="description" content="">
                    <title>Панель администрации | Склад товаров</title>
                    
                    <!-- Bootstrap core CSS -->
                    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.0/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-wEmeIV1mKuiNpC+IOBjI7aAzPcEZeedi5yW5f2yOq55WWLwNGmvvx4Um1vskeMj0" crossorigin="anonymous">
                    <meta name="theme-color" content="#7952b3">
                    
                    <style>
                        .bd-placeholder-img {
                            font-size: 1.125rem;
                            text-anchor: middle;
                            -webkit-user-select: none;
                            -moz-user-select: none;
                            user-select: none;
                        }
                        
                        @media (min-width: 768px) {
                            .bd-placeholder-img-lg {
                                font-size: 3.5rem;
                            }
                        }
                        
                        html, body {
                            height: 100%;
                        }
                        
                        body {
                            display: flex;
                            align-items: center;
                            padding-top: 40px;
                            padding-bottom: 40px;
                            background-color: #f5f5f5;
                        }
                        
                        .form-signin {
                            width: 100%;
                            max-width: 330px;
                            padding: 15px;
                            margin: auto;
                        }
            
                        .form-signin .checkbox {
                            font-weight: 400;
                        }
                        
                        .form-signin .form-floating:focus-within {
                            z-index: 2;
                        }
                        
                        .form-signin input[type="login"] {
                            margin-bottom: -1px;
                            border-bottom-right-radius: 0;
                            border-bottom-left-radius: 0;
                        }
                        
                        .form-signin input[type="password"] {
                            margin-bottom: 10px;
                            border-top-left-radius: 0;
                            border-top-right-radius: 0;
                        }
                    </style>
                </head>
                <body class="text-center">
                    <main class="form-signin">
                        <form method="POST" action="">
                            <h1 class="h3 mb-3 fw-normal">Панель администрации</h1>
                            
                            <div class="form-floating">
                                <input type="text" class="form-control" name="login" id="floatingInput" placeholder="Ваш логин">
                                <label for="floatingInput">Логин</label>
                            </div>
                            <div class="form-floating">
                                <input type="password" class="form-control" name="password" id="floatingPassword" placeholder="Пароль">
                                <label for="floatingPassword">Пароль</label>
                            </div>
                            <button class="w-100 btn btn-lg btn-primary" type="submit">Войти</button>
                            <p class="mt-5 mb-3 text-muted">&copy; 2022<? echo date('Y') == "2022" ? "" : "-".date('Y'); ?></p>
                        </form>
                    </main>
                </body>
            </html>
        <?
    } else {
        if ($login == "admin" && $pass == "1234")
            $idUser = 1;
        
        if ($idUser > 0){
            ?>
                <!doctype html>
                <html lang="ru">
                    <head>
                        <meta charset="utf-8">
                        <meta name="viewport" content="width=device-width, initial-scale=1">
                        <meta name="description" content="">
                        <title>Панель администрации | Склад товаров</title>
                        <!-- Bootstrap core CSS -->
                        <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.0/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-wEmeIV1mKuiNpC+IOBjI7aAzPcEZeedi5yW5f2yOq55WWLwNGmvvx4Um1vskeMj0" crossorigin="anonymous">
                        <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.6.1/css/all.css" integrity="sha384-gfdkjb5BdAXd+lj+gudLWI+BXq4IuLW5IT+brZEZsLFm++aCMlF1V92rMkPaX4PP" crossorigin="anonymous">
                        <meta name="theme-color" content="#7952b3">
                        <style>
                            .bd-placeholder-img {
                                font-size: 1.125rem;
                                text-anchor: middle;
                                -webkit-user-select: none;
                                -moz-user-select: none;
                                user-select: none;
                            }

                            @media (min-width: 768px) {
                                .bd-placeholder-img-lg {
                                    font-size: 3.5rem;
                                }
                            }
                            
                            body {
                                font-size: .875rem;
                            }

                            .feather {
                                width: 16px;
                                height: 16px;
                                vertical-align: text-bottom;
                            }

                            .sidebar {
                                position: fixed;
                                top: 0;
                                /* rtl:raw:
                                right: 0;
                                */
                                bottom: 0;
                                /* rtl:remove */
                                left: 0;
                                z-index: 100; /* Behind the navbar */
                                padding: 48px 0 0; /* Height of navbar */
                                box-shadow: inset -1px 0 0 rgba(0, 0, 0, .1);
                            }
                            
                            @media (max-width: 767.98px) {
                                .sidebar {
                                    top: 5rem;
                                }
                            }
                            
                            .sidebar-sticky {
                                position: relative;
                                top: 0;
                                height: calc(100vh - 48px);
                                padding-top: .5rem;
                                overflow-x: hidden;
                                overflow-y: auto; /* Scrollable contents if viewport is shorter than content. */
                            }
                            
                            .sidebar .nav-link {
                                font-weight: 500;
                                color: #333;
                            }
                            
                            .sidebar .nav-link .feather {
                                margin-right: 4px;
                                color: #727272;
                            }
                            
                            .sidebar .nav-link.active {
                                color: #007bff;
                            }
                            
                            .sidebar .nav-link:hover .feather,
                            .sidebar .nav-link.active .feather {
                                color: inherit;
                            }
                            
                            .sidebar-heading {
                                font-size: .75rem;
                                text-transform: uppercase;
                            }
                            
                            .navbar-brand {
                                padding-top: .75rem;
                                padding-bottom: .75rem;
                                font-size: 1rem;
                                background-color: rgba(0, 0, 0, .25);
                                box-shadow: inset -1px 0 0 rgba(0, 0, 0, .25);
                            }
                            
                            .navbar .navbar-toggler {
                                top: .25rem;
                                right: 1rem;
                            }
                            
                            .navbar .form-control {
                                padding: .75rem 1rem;
                                border-width: 0;
                                border-radius: 0;
                            }
                            
                            .form-control-dark {
                                color: #fff;
                                background-color: rgba(255, 255, 255, .1);
                                border-color: rgba(255, 255, 255, .1);
                            }
                            
                            .form-control-dark:focus {
                                border-color: transparent;
                                box-shadow: 0 0 0 3px rgba(255, 255, 255, .25);
                            }
                        </style>
                        <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.js"></script>
                    </head>
                    <body style="overflow-x: hidden;">
                        <header class="navbar navbar-dark sticky-top bg-dark flex-md-nowrap p-0 shadow">
                            <a class="navbar-brand col-md-3 col-lg-2 me-0 px-3" href="#" target="_blank">Склад товаров</a>
                            <button class="navbar-toggler position-absolute d-md-none collapsed" type="button" data-bs-toggle="collapse" data-bs-target="#sidebarMenu" aria-controls="sidebarMenu" aria-expanded="false" aria-label="Toggle navigation">
                                <span class="navbar-toggler-icon"></span>
                            </button>
                            <input class="form-control form-control-dark" id="searchInput" type="text" placeholder="Поиск" aria-label="Search">
                            <a class="btn" id="searching" z-index="256" style="margin-left: -60px;"><i class="fas fa-search"></i></a>
                                
                        </header>

                        <div class="container-fluid">
                            <div class="row">
                                <nav id="sidebarMenu" class="col-md-3 col-lg-2 d-md-block bg-light sidebar collapse">
                                    <div class="position-sticky pt-1">
                                        <ul class="nav flex-column" id="ul_nav">
                                            <li class="nav-item">
                                                <a class="nav-link" href="#">
                                                    <div class="row">
                                                        <div class="col-12 d-flex align-items-center">
                                                            <div>
                                                                <b>Андрей</b><br>
                                                                <small>anegrash@nav-com.ru</small>
                                                            </div>
                                                        </div>
                                                    </div>
                                                </a>
                                            </li>
                                            <li class="nav-item">
                                                <a class="nav-link" href="" style="color:red;">
                                                    Выйти 
                                                </a>
                                            </li>
                                            <hr>
                                            <li class="nav-item">
                                                <a class="nav-link active" id="transactions" href="#transactions" data-bs-toggle="collapse" data-bs-target="#sidebarMenu" aria-controls="sidebarMenu" aria-expanded="false">
                                                    Транзакции 
                                                </a>
                                            </li>
                                            <li class="nav-item">
                                                <a class="nav-link" id="products" href="#products" data-bs-toggle="collapse" data-bs-target="#sidebarMenu" aria-controls="sidebarMenu" aria-expanded="false">
                                                    Товары 
                                                </a>
                                            </li>
                                            <li class="nav-item">
                                                <a class="nav-link" id="companies" href="#companies" data-bs-toggle="collapse" data-bs-target="#sidebarMenu" aria-controls="sidebarMenu" aria-expanded="false">
                                                    Компании
                                                </a>
                                            </li>
                                            <li class="nav-item">
                                                <a class="nav-link" id="transporters" href="#transporters" data-bs-toggle="collapse" data-bs-target="#sidebarMenu" aria-controls="sidebarMenu" aria-expanded="false">
                                                    Перевозчики
                                                </a>
                                            </li>
                                            
                                            <hr>
                                            <li class="nav-item">
                                                <a class="nav-link" id="documents" href="#documents" data-bs-toggle="collapse" data-bs-target="#sidebarMenu" aria-controls="sidebarMenu" aria-expanded="false">
                                                    Документы 
                                                </a>
                                            </li>
                                            
                                            <li class="nav-item">
                                                <a class="nav-link" id="workers" href="#workers" data-bs-toggle="collapse" data-bs-target="#sidebarMenu" aria-controls="sidebarMenu" aria-expanded="false">
                                                    Работники
                                                </a>
                                            </li>
                                                   
                                            <hr>
                                            <li class="nav-item">
                                                <a class="nav-link" id="log" href="#log" data-bs-toggle="collapse" data-bs-target="#sidebarMenu" aria-controls="sidebarMenu" aria-expanded="false">
                                                    Лог
                                                </a>
                                            </li>
                                            <li class="nav-item">
                                                <a class="nav-link" id="about" href="#about" data-bs-toggle="collapse" data-bs-target="#sidebarMenu" aria-controls="sidebarMenu" aria-expanded="false">
                                                    О системе
                                                </a>
                                            </li>
                                        </ul>
                                    </div>
                                </nav>
                                <script>
                                    var adminEmail = '<? echo $login; ?>';
                                    var adminPass = '<? echo $pass; ?>';
                                    $(document).ready(function(){
                                        $('#main-panel').empty();
                                        $('#main-panel').html("<div class=\"row d-flex justify-content-center align-items-center\" style=\"height:75vh;\"><div class=\"spinner-grow\" role=\"status\"><span class=\"visually-hidden\">Загрузка...</span></div></div>");
                                        $.ajax({
                                        	url: 'script.php',
                                        	method: 'post',
                                        	dataType: 'html',
                                        	data: {email: adminEmail, pass: adminPass, type: 'transactions'},
                                        	success: function(data){
                                                $('#main-panel').empty();
                                        		$('#main-panel').html(data);
                                        	},
                                        	error: function (jqXHR, exception) {
                                        		$('#main-panel').empty();
                                        		$('#main-panel').html("<h2><center>Произошла ошибка. Попробуйте позже</center></h2>");
                                        	}
                                        });
                                        
                                        $('#searching').click(function(){
                                            $('.nav-item').each(function() {
                                                $('.nav-link').removeClass('active');
                                            });
                                            var needle = $('#searchInput').val();
                                            $('#searchInput').val("");
                                            $('#main-panel').empty();
                                            $('#main-panel').html("<div class=\"row d-flex justify-content-center align-items-center\" style=\"height:75vh;\"><div class=\"spinner-grow\" role=\"status\"><span class=\"visually-hidden\">Загрузка...</span></div></div>");
                                            $.ajax({
                                            	url: 'script.php',
                                            	method: 'post',
                                            	dataType: 'html',
                                            	data: {email: adminEmail, pass: adminPass, type: 'searchAll', input: needle},
                                            	success: function(data){
                                                    $('#main-panel').empty();
                                            		$('#main-panel').html(data);
                                            	},
                                            	error: function (jqXHR, exception) {
                                            		$('#main-panel').empty();
                                            		$('#main-panel').html("<h2><center>Произошла ошибка. Попробуйте позже</center></h2>");
                                            	}
                                            });
                                        });
                                        //--Транзакции---
                                        $('#transactions').click(function(){
                                            $('.nav-item').each(function() {
                                                $('.nav-link').removeClass('active');
                                            });
                                            $('#transactions').addClass(' active');
                                            $('#main-panel').empty();
                                            $('#main-panel').html("<div class=\"row d-flex justify-content-center align-items-center\" style=\"height:75vh;\"><div class=\"spinner-grow\" role=\"status\"><span class=\"visually-hidden\">Загрузка...</span></div></div>");
                                            $.ajax({
                                            	url: 'script.php',
                                            	method: 'post',
                                            	dataType: 'html',
                                            	data: {email: adminEmail, pass: adminPass, type: 'transactions'},
                                            	success: function(data){
                                                    $('#main-panel').empty();
                                            		$('#main-panel').html(data);
                                            	},
                                            	error: function (jqXHR, exception) {
                                            		$('#main-panel').empty();
                                            		$('#main-panel').html("<h2><center>Произошла ошибка. Попробуйте позже</center></h2>");
                                            	}
                                            });
                                        });
                                        //--Компании---
                                        $('#companies').click(function(){
                                            $('.nav-item').each(function() {
                                                $('.nav-link').removeClass('active');
                                            });
                                            $('#companies').addClass(' active');
                                            $('#main-panel').empty();
                                            $('#main-panel').html("<div class=\"row d-flex justify-content-center align-items-center\" style=\"height:75vh;\"><div class=\"spinner-grow\" role=\"status\"><span class=\"visually-hidden\">Загрузка...</span></div></div>");
                                            $.ajax({
                                            	url: 'script.php',
                                            	method: 'post',
                                            	dataType: 'html',
                                            	data: {email: adminEmail, pass: adminPass, type: 'companies'},
                                            	success: function(data){
                                                    $('#main-panel').empty();
                                            		$('#main-panel').html(data);
                                            	},
                                            	error: function (jqXHR, exception) {
                                            		$('#main-panel').empty();
                                            		$('#main-panel').html("<h2><center>Произошла ошибка. Попробуйте позже</center></h2>");
                                            	}
                                            });
                                        });
                                        //--Товары---
                                        $('#products').click(function(){
                                            $('.nav-item').each(function() {
                                                $('.nav-link').removeClass('active');
                                            });
                                            $('#products').addClass(' active');
                                            $('#main-panel').empty();
                                            $('#main-panel').html("<div class=\"row d-flex justify-content-center align-items-center\" style=\"height:75vh;\"><div class=\"spinner-grow\" role=\"status\"><span class=\"visually-hidden\">Загрузка...</span></div></div>");
                                            $.ajax({
                                            	url: 'script.php',
                                            	method: 'post',
                                            	dataType: 'html',
                                            	data: {email: adminEmail, pass: adminPass, type: 'products'},
                                            	success: function(data){
                                                    $('#main-panel').empty();
                                            		$('#main-panel').html(data);
                                            	},
                                            	error: function (jqXHR, exception) {
                                            		$('#main-panel').empty();
                                            		$('#main-panel').html("<h2><center>Произошла ошибка. Попробуйте позже</center></h2>");
                                            	}
                                            });
                                        });
                                        //--Перевозчики---
                                        $('#transporters').click(function(){
                                            $('.nav-item').each(function() {
                                                $('.nav-link').removeClass('active');
                                            });
                                            $('#transporters').addClass(' active');
                                            $('#main-panel').empty();
                                            $('#main-panel').html("<div class=\"row d-flex justify-content-center align-items-center\" style=\"height:75vh;\"><div class=\"spinner-grow\" role=\"status\"><span class=\"visually-hidden\">Загрузка...</span></div></div>");
                                            $.ajax({
                                            	url: 'script.php',
                                            	method: 'post',
                                            	dataType: 'html',
                                            	data: {email: adminEmail, pass: adminPass, type: 'transporters'},
                                            	success: function(data){
                                                    $('#main-panel').empty();
                                            		$('#main-panel').html(data);
                                            	},
                                            	error: function (jqXHR, exception) {
                                            		$('#main-panel').empty();
                                            		$('#main-panel').html("<h2><center>Произошла ошибка. Попробуйте позже</center></h2>");
                                            	}
                                            });
                                        });
                                        //--Документы---
                                        $('#documents').click(function(){
                                            $('.nav-item').each(function() {
                                                $('.nav-link').removeClass('active');
                                            });
                                            $('#documents').addClass(' active');
                                            $('#main-panel').empty();
                                            $('#main-panel').html("<div class=\"row d-flex justify-content-center align-items-center\" style=\"height:75vh;\"><div class=\"spinner-grow\" role=\"status\"><span class=\"visually-hidden\">Загрузка...</span></div></div>");
                                            $.ajax({
                                            	url: 'script.php',
                                            	method: 'post',
                                            	dataType: 'html',
                                            	data: {email: adminEmail, pass: adminPass, type: 'documents'},
                                            	success: function(data){
                                                    $('#main-panel').empty();
                                            		$('#main-panel').html(data);
                                            	},
                                            	error: function (jqXHR, exception) {
                                            		$('#main-panel').empty();
                                            		$('#main-panel').html("<h2><center>Произошла ошибка. Попробуйте позже</center></h2>");
                                            	}
                                            });
                                        });
                                        //--Работники---
                                        $('#workers').click(function(){
                                            $('.nav-item').each(function() {
                                                $('.nav-link').removeClass('active');
                                            });
                                            $('#workers').addClass(' active');
                                            $('#main-panel').empty();
                                            $('#main-panel').html("<div class=\"row d-flex justify-content-center align-items-center\" style=\"height:75vh;\"><div class=\"spinner-grow\" role=\"status\"><span class=\"visually-hidden\">Загрузка...</span></div></div>");
                                            $.ajax({
                                            	url: 'script.php',
                                            	method: 'post',
                                            	dataType: 'html',
                                            	data: {email: adminEmail, pass: adminPass, type: 'workers'},
                                            	success: function(data){
                                                    $('#main-panel').empty();
                                            		$('#main-panel').html(data);
                                            	},
                                            	error: function (jqXHR, exception) {
                                            		$('#main-panel').empty();
                                            		$('#main-panel').html("<h2><center>Произошла ошибка. Попробуйте позже</center></h2>");
                                            	}
                                            });
                                        });
                                        //--Лог---
                                        $('#log').click(function(){
                                            $('.nav-item').each(function() {
                                                $('.nav-link').removeClass('active');
                                            });
                                            $('#log').addClass(' active');
                                            $('#main-panel').empty();
                                            $('#main-panel').html("<div class=\"row d-flex justify-content-center align-items-center\" style=\"height:75vh;\"><div class=\"spinner-grow\" role=\"status\"><span class=\"visually-hidden\">Загрузка...</span></div></div>");
                                            $.ajax({
                                            	url: 'script.php',
                                            	method: 'post',
                                            	dataType: 'html',
                                            	data: {email: adminEmail, pass: adminPass, type: 'log'},
                                            	success: function(data){
                                                    $('#main-panel').empty();
                                            		$('#main-panel').html(data);
                                            	},
                                            	error: function (jqXHR, exception) {
                                            		$('#main-panel').empty();
                                            		$('#main-panel').html("<h2><center>Произошла ошибка. Попробуйте позже</center></h2>");
                                            	}
                                            });
                                        });
                                        //--О системе---
                                        $('#about').click(function(){
                                            $('.nav-item').each(function() {
                                                $('.nav-link').removeClass('active');
                                            });
                                            $('#about').addClass(' active');
                                            $('#main-panel').empty();
                                            $('#main-panel').html("<div class=\"row d-flex justify-content-center align-items-center\" style=\"height:75vh;\"><div class=\"spinner-grow\" role=\"status\"><span class=\"visually-hidden\">Загрузка...</span></div></div>");
                                            $.ajax({
                                            	url: 'script.php',
                                            	method: 'post',
                                            	dataType: 'html',
                                            	data: {email: adminEmail, pass: adminPass, type: 'about'},
                                            	success: function(data){
                                                    $('#main-panel').empty();
                                            		$('#main-panel').html(data);
                                            	},
                                            	error: function (jqXHR, exception) {
                                            		$('#main-panel').empty();
                                            		$('#main-panel').html("<h2><center>Произошла ошибка. Попробуйте позже</center></h2>");
                                            	}
                                            });
                                        });
                                        
                                    });
                                </script>

                                <main class="col-md-9 ms-sm-auto col-lg-10 px-md-4" id="main-panel">
                                    
                                </main>
                            </div>
                        </div>
                        <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.0/dist/js/bootstrap.bundle.min.js" integrity="sha384-p34f1UUtsS3wqzfto5wAAmdvj+osOnFyQFpp4Ua3gs/ZVWx6oOypYoCJhGGScy+8" crossorigin="anonymous"></script>
                        <script src="https://cdn.jsdelivr.net/npm/feather-icons@4.28.0/dist/feather.min.js" integrity="sha384-uO3SXW5IuS1ZpFPKugNNWqTZRRglnUJK6UAZ/gxOX80nxEkN9NcGZTftn6RzhGWE" crossorigin="anonymous"></script>
                        <style>
                            .nav-item:hover{
                                background-color: rgb(0 0 0 /12%);
                            }
                            .forBack {
                                margin-top: -27px;
                            }
                        </style>
                    </body>
                </html>

            <?
        }else{
            ?>
                <!DOCTYPE html>
                <html lang="ru">
                    <head>
                        <meta charset="utf-8">
                        <meta name="viewport" content="width=device-width, initial-scale=1">
                        <meta name="description" content="">
                        <title>Панель администрации | Склад товаров</title>
                        
                        <!-- Bootstrap core CSS -->
                        <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.0/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-wEmeIV1mKuiNpC+IOBjI7aAzPcEZeedi5yW5f2yOq55WWLwNGmvvx4Um1vskeMj0" crossorigin="anonymous">
                        <meta name="theme-color" content="#7952b3">
                        
                        <style>
                            .bd-placeholder-img {
                                font-size: 1.125rem;
                                text-anchor: middle;
                                -webkit-user-select: none;
                                -moz-user-select: none;
                                user-select: none;
                            }
                            
                            @media (min-width: 768px) {
                                .bd-placeholder-img-lg {
                                    font-size: 3.5rem;
                                }
                            }
                            
                            html, body {
                                height: 100%;
                            }
                            
                            body {
                                display: flex;
                                align-items: center;
                                padding-top: 40px;
                                padding-bottom: 40px;
                                background-color: #f5f5f5;
                            }
                            
                            .form-signin {
                                width: 100%;
                                max-width: 330px;
                                padding: 15px;
                                margin: auto;
                            }
                
                            .form-signin .checkbox {
                                font-weight: 400;
                            }
                            
                            .form-signin .form-floating:focus-within {
                                z-index: 2;
                            }
                            
                            .form-signin input[type="login"] {
                                margin-bottom: -1px;
                                border-bottom-right-radius: 0;
                                border-bottom-left-radius: 0;
                            }
                            
                            .form-signin input[type="password"] {
                                margin-bottom: 10px;
                                border-top-left-radius: 0;
                                border-top-right-radius: 0;
                            }
                        </style>
                    </head>
                    <body class="text-center">
                        <main class="form-signin">
                            <div class="alert alert-warning alert-dismissible fade show" role="alert">
                                <center>Неверный login или пароль</center>
                            </div>
                            <form method="POST" action="">
                                <h1 class="h3 mb-3 fw-normal">Панель администрации</h1>
                                
                                <div class="form-floating">
                                    <input type="text" class="form-control" name="login" id="floatingInput" placeholder="Ваш логин">
                                    <label for="floatingInput">Логин</label>
                                </div>
                                <div class="form-floating">
                                    <input type="password" class="form-control" name="password" id="floatingPassword" placeholder="Пароль">
                                    <label for="floatingPassword">Пароль</label>
                                </div>
                                <button class="w-100 btn btn-lg btn-primary" type="submit">Войти</button>
                                <p class="mt-5 mb-3 text-muted">&copy; 2022<? echo date('Y') == "2022" ? "" : "-".date('Y'); ?></p>
                            </form>
                        </main>
                    </body>
                </html>
            <?
        }
    }
?>