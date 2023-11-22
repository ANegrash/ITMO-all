<?
    date_default_timezone_set('Europe/Moscow'); 
    $lastDateUpdate = "2022-11-25 09:00";
    $email = $_POST['email'];
    $pass = $_POST['pass'];
    $type = $_POST['type'];
    
    $hostname = "web08-cp";
    $username = "i1583376"; 
    $password = "NEUT6mf9bp"; 
    $dbName = "i1583376_warehouse"; 
    
    $link = mysqli_connect($hostname,$username,$password,$dbName);
    
    if ($email == "admin" && $pass == "1234")
        $idUser = 10;
    
    if ($idUser > 0) {
        switch ($type) {
            case "transactions": echo viewTransactions($link, $idUser); break;
            case "transactionInfo": echo viewTransactionInfo($link); break;
            case "createInTransaction": echo createInTransaction($link); break;
            case "createOutTransaction": echo createOutTransaction($link); break;
            case "products": echo viewProducts($link); break;
            case "addProduct": echo addProduct($link); break;
            case "companies": echo viewCompanies($link); break;
            case "addCompany": echo addCompany($link); break;
            case "transporters": echo viewTransporters($link); break;
            case "addTransporter": echo addTransporter($link); break;
            case "documents": echo viewDocuments($link); break;
            case "addDocument": echo addDocument($link); break;
            case "workers": echo viewWorkers($link); break;
            case "addWorker": echo addWorker($link); break;
            case "log": echo viewLog($link); break;
            case "about": echo about($lastDateUpdate); break;
            case "searchAll": echo searchGlobal($link); break;
            case "getEmptyShelf": echo getEmptyShelf($link); break;
        }
    }
    
    function viewTransactions($link, $id){
        
        if (isset($_POST['activity'])){
            $activity = $_POST['activity'];
            if ($activity == 'saveTransaction'){
                $new_id = mysqli_fetch_array(mysqli_query($link, "
                    SELECT max(`id_order`) + 1 as new_id FROM `orders`
                "))['new_id'];
                $products = explode(";", $_POST['products']);
                $temp = array();
                foreach ($products as $product){
                    if ($product !== "" and !in_array($product, $temp)){
                        mysqli_query($link, "
                            INSERT INTO `orders`(`id_order`, `id_product`) VALUES ('".$new_id."', '".$product."')
                        ");
                        array_push($temp, $product);
                    }
                }
                if (mysqli_query($link, "
                    INSERT INTO `transactions`(`type`, `id_order`, `id_worker_accept`, `id_company`, `id_transporter`) VALUES ('".$_POST['typeIO']."', '".$new_id."', '".$id."', '".$_POST['company']."', '".$_POST['transporter']."')
                ")){
                    addToLog($link, 'INSERT', 'transactions');
                    header("Refresh:0");
                } else {
                    ?>
                        <center><h5>Произошла ошибка. Попробуйте позже</h5></center>
                    <?
                    return;
                }
            }
        }
        
        $count_in = mysqli_fetch_array(mysqli_query($link, "
            SELECT COUNT(*) as count_in FROM `transactions` WHERE `type`='IN'
        "))['count_in'];
        $count_out = mysqli_fetch_array(mysqli_query($link, "
            SELECT COUNT(*) as count_out FROM `transactions` WHERE `type`='OUT'
        "))['count_out'];
        ?>
            <script>
                function getTransactionInfo(id){
                    $('#main-panel').empty();
                    $('#main-panel').html("<div class=\"row d-flex justify-content-center align-items-center\" style=\"height:75vh;\"><div class=\"spinner-grow\" role=\"status\"><span class=\"visually-hidden\">Загрузка...</span></div></div>");
                    $.ajax({
                    	url: 'script.php',
                    	method: 'post',
                    	dataType: 'html',
                    	data: {email: adminEmail, pass: adminPass, type: 'transactionInfo', id: id},
                    	success: function(data){
                            $('#main-panel').empty();
                    		$('#main-panel').html(data);
                    	},
                    	error: function (jqXHR, exception) {
                    		$('#main-panel').empty();
                    		$('#main-panel').html("<h2><center>Произошла ошибка. Попробуйте позже</center></h2>");
                    	}
                    });
                }
                
                $('#createInTransaction').click(function(){
                    $('#main-panel').empty();
                    $('#main-panel').html("<div class=\"row d-flex justify-content-center align-items-center\" style=\"height:75vh;\"><div class=\"spinner-grow\" role=\"status\"><span class=\"visually-hidden\">Загрузка...</span></div></div>");
                    $.ajax({
                    	url: 'script.php',
                    	method: 'post',
                    	dataType: 'html',
                    	data: {email: adminEmail, pass: adminPass, type: 'createInTransaction'},
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
                
                $('#createOutTransaction').click(function(){
                    $('#main-panel').empty();
                    $('#main-panel').html("<div class=\"row d-flex justify-content-center align-items-center\" style=\"height:75vh;\"><div class=\"spinner-grow\" role=\"status\"><span class=\"visually-hidden\">Загрузка...</span></div></div>");
                    $.ajax({
                    	url: 'script.php',
                    	method: 'post',
                    	dataType: 'html',
                    	data: {email: adminEmail, pass: adminPass, type: 'createOutTransaction'},
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
            </script>
            <br>
            <div style="display: flex; justify-content: space-evenly;">
                <div class="card" style="width:270px;">
                    <h5 class="card-header">Входящие транзакции</h5>
                    <div class="card-body">
                        <p class="card-text">
                            <center>
                                За всё время:
                                <h2><? echo $count_in; ?></h2>
                            </center>
                        </p>
                        <a href="#createInTransaction" id="createInTransaction" class="btn btn-primary">Создать новую</a>
                    </div>
                </div>
                <div class="card" style="width:270px;">
                    <h5 class="card-header">Исходящие транзакции</h5>
                    <div class="card-body">
                        <p class="card-text">
                            <center>
                                За всё время:
                                <h2><? echo $count_out; ?></h2>
                            </center>
                        </p>
                        <a href="#createOutTransaction" id="createOutTransaction" class="btn btn-primary">Создать новую</a>
                    </div>
                </div>
            </div>
            <br>
            <h5><center>Все транзакции</center></h5>
            <hr>
            <div class="table-responsive">
                <table class="table table-striped table-hover table-sm align-middle" width="90%">
                    <thead>
                        <tr>
                            <th scope="col">id</th>
                            <th scope="col">Дата создания</th>
                            <th scope="col">Тип</th>
                            <th scope="col">Товаров</th>
                            <th scope="col">Создал</th>
                            <th scope="col">Предназначена</th>
                            <th scope="col">Перевозчик</th>
                        </tr>
                    </thead>
                    <tbody>
                        <?
                            $j = 0;
                            $res2 = mysqli_query($link, "
                                SELECT 
                                    t.id_transaction, 
                                    t.type, 
                                    t.datetime, 
                                    (SELECT COUNT(*) FROM orders as o WHERE o.id_order = t.id_order) as count_products, 
                                    w.name, 
                                    c.name as company_name,
                                    tr.transporter_name
                                FROM 
                                    transactions as t, 
                                    workers as w, 
                                    companies as c,
                                    transporters as tr
                                WHERE 
                                    t.id_worker_accept = w.id_worker 
                                    AND t.id_company = c.id_recipient 
                                    AND t.id_transporter = tr.id_transporter
                                ORDER BY t.datetime DESC
                            ");
                            while ($row = mysqli_fetch_array($res2)){
                                $id_transaction = $row['id_transaction'];
                                $type = ($row['type'] == 'IN' ? "входящая" : "исходящая");
                                $date = goodDate($row['datetime']);
                                $count_products = $row['count_products'];
                                $name = $row['name'];
                                $company_name = $row['company_name'];
                                $transporter = $row['transporter_name'];
                                
                                $j++;
                                ?>
                                    <tr onclick="getTransactionInfo(<? echo $id_transaction; ?>);">
                                        <td><? echo $id_transaction; ?></td>
                                        <td><? echo $date; ?></td>
                                        <td><? echo $type; ?></td>
                                        <td><? echo $count_products; ?></td>
                                        <td><? echo $name; ?></td>
                                        <td><? echo $company_name; ?></td>
                                        <td><? echo $transporter; ?></td>
                                    </tr>
                                <?
                            }
                            if($j == 0){
                                ?>
                                    <tr><td colspan="7"><center>Ни одной транзакции!</center></td></tr>
                                <?
                            }
                        ?>
                    </tbody>
                </table>
            </div>
        <?
    }
    
    function viewTransactionInfo($link){
        $id = $_POST['id'];
        $res2 = mysqli_query($link, "
            SELECT 
            	t.type,
                t.datetime,
                t.id_order,
                tr.transporter_name,
                tr.auto_number,
                c.name as company,
                c.agent,
                w.name,
                w.role
            FROM 
            	transactions as t,
            	transporters as tr,
                companies as c,
                workers as w
            WHERE
            	t.id_transporter = tr.id_transporter
                AND t.id_company = c.id_recipient
                AND t.id_worker_accept = w.id_worker
                AND t.id_transaction = '".$id."'
        ");
        $row = mysqli_fetch_array($res2);
        $type = $row['type'];
        $datetime = $row['datetime'];
        $id_order = $row['id_order'];
        $transporter_name = $row['transporter_name'];
        $auto_number = $row['auto_number'];
        $company = $row['company'];
        $agent = $row['agent'];
        $name = $row['name'];
        $role = $row['role'];
        
        $headr = "";
        $com = "";
        if ($type == 'IN'){
            $headr = "Входящая";
            $com = "отправитель";
        } else {
            $headr = "Исходящая";
            $com = "получатель";
        }
        ?>
            <a id="toTransactions" href="#transactions">
                <i class="fas fa-arrow-circle-left fa-2x" style="color:#6c757d;"></i>
            </a> 
            <script>
                $('#toTransactions').click(function(){
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
            </script>
            <br>
            <h5><center><? echo $headr; ?> транзакция №<? echo $id; ?></center></h5>
            <hr>
            <b>Дата создания: </b><? echo goodDate($datetime); ?><br>
            <b>Продукты:</b><br>
            <div style="display:flex; justyfy-content: space-evenly;">
                <?
                    $res = mysqli_query($link, "SELECT p.product_name, p.article_number, p.price FROM orders as o, products as p WHERE o.id_product = p.id_product AND o.id_order = '".$id."'");
                    while($row = mysqli_fetch_array($res)){
                        $prod_name = $row['product_name'];
                        $article_number = $row['article_number'];
                        $price = $row['price'];
                        ?>
                        <div class="card" style="max-width: 16rem;margin:5px;">
                            <div class="card-body">
                                <p class="card-text">
                                    <b><? echo $prod_name; ?></b>
                                    <hr>Артикул: <? echo $article_number; ?><br>
                                    Цена: <? echo $price; ?>₽<br>
                                </p>
                            </div>
                        </div>
                        <?
                    }
                ?>
            </div>
            <br>
            
            <center><h6>Перевозчик</h6></center>
            <hr>
            
            <b>ФИО водителя: </b><? echo $transporter_name; ?><br>
            <b>Номер автомобиля: </b><? echo $auto_number; ?><br>
            
            <center><h6>Компания-<? echo $com; ?></h6></center>
            <hr>
            
            <b>Наименование: </b><? echo $company; ?><br>
            <b>Контактное лицо: </b><? echo $agent; ?><br>
            
            <center><h6>Ответственный</h6></center>
            <hr>
            
            <b>ФИО работника: </b><? echo $name; ?><br>
            <b>Должность: </b><? echo $role; ?><br>
        <?
    }
    
    function createInTransaction($link){
        ?>
            <a id="toTransactions" href="#transactions">
                <i class="fas fa-arrow-circle-left fa-2x" style="color:#6c757d;"></i>
            </a> 
            <script>
                $('#toTransactions').click(function(){
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
                
                $('#addToOrder').click(function(){
                    var productId = $('#select-prod').val();
                    var productName = $('#select-prod option:selected').data('name');
                    var productArticle = $('#select-prod option:selected').data('article');
                    $('#product-container').append('<div class="card" style="max-width: 16rem;margin:5px;"><div class="card-body"><p class="card-text"><b>'+productName+'</b><hr>Артикул: '+productArticle+'<br></p></div></div>');
                    var list = '' + $('#products').val();
                    list = '' + list + productId + ';';
                    $('#products').val(list);
                });
                
                $('#saveTransaction').click(function(){
                    var products = $('#products').val();
                    var company =  $('#select-company').val();
                    var transporter = $('#select-transporter').val();
                    $('#main-panel').empty();
                    $('#main-panel').html("<div class=\"row d-flex justify-content-center align-items-center\" style=\"height:75vh;\"><div class=\"spinner-grow\" role=\"status\"><span class=\"visually-hidden\">Загрузка...</span></div></div>");
                    $.ajax({
                    	url: 'script.php',
                    	method: 'post',
                    	dataType: 'html',
                    	data: {email: adminEmail, pass: adminPass, type: 'transactions', activity: 'saveTransaction', products: products, company: company, transporter: transporter, typeIO: 'IN'},
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
            </script>
            <h5><center>Создание входящей транзакции</center></h5>
            <div class="row">
                <div class="col-1"></div>
                <div class="col-10">
                    <b>Компания-отправитель:</b>
                    <select class="form-select" id="select-company">
                        <?
                            $res2 = mysqli_query($link, "
                                SELECT `id_recipient`, `name`, `agent` FROM `companies` ORDER BY `name`
                            ");
                            ?>
                                <option selected>Выберите отправителя</option>
                            <?
                            while ($row = mysqli_fetch_array($res2)){
                                $id_recipient = $row['id_recipient'];
                                $name = $row['name'];
                                $agent = $row['agent'];
                                ?>
                                    <option value="<? echo $id_recipient; ?>"><? echo $name; ?> (<? echo $agent; ?>)</option>
                                <?
                            }
                        ?>
                    </select>
                </div>
                <div class="col-1"></div>
            </div>
            <br>
            <div class="row">
                <div class="col-1"></div>
                <div class="col-10">
                    <b>Перевозчик:</b>
                    <select class="form-select" id="select-transporter">
                        <?
                            $res2 = mysqli_query($link, "
                                SELECT `id_transporter`, `transporter_name`, `auto_number` FROM `transporters` ORDER BY `transporter_name`
                            ");
                            ?>
                                <option selected>Выберите перевозчика</option>
                            <?
                            while ($row = mysqli_fetch_array($res2)){
                                $id_transporter = $row['id_transporter'];
                                $name = $row['transporter_name'];
                                $auto_number = $row['auto_number'];
                                ?>
                                    <option value="<? echo $id_transporter; ?>"><? echo $name; ?> (<? echo $auto_number; ?>)</option>
                                <?
                            }
                        ?>
                    </select>
                </div>
                <div class="col-1"></div>
            </div>
            <br>
            <div class="row">
                <div class="col-1"></div>
                <div class="col-10">
                    <b>Товары:</b>
                    <small>Для добавления товаров в транзакцию их сначала нужно добавить во вкладке "Товары"</small>
                    <input type="hidden" name="products" value="">
                    <div style="display: flex; justify-content: start;" id="product-container">
                        <div class="card" id="product-add" data-bs-toggle="modal" data-bs-target="#exampleModal" style="width: 100px; background-color: green; color: white; cursor: pointer;">
                            <div class="card-body">
                                <h1><center>+</center></h1>
                            </div>
                        </div>
                    </div>
                </div>
                <div class="col-1"></div>
            </div>
            <br>
            <div class="row">
                <div class="col-1"></div>
                <div class="col-10">
                    <a type="button" class="btn btn-success" id="saveTransaction">Создать транзакцию</a>
                </div>
                <div class="col-1"></div>
            </div>
            <br>
            
            <div class="modal fade" id="exampleModal" tabindex="-1" aria-labelledby="exampleModalLabel" aria-hidden="true">
              <div class="modal-dialog modal-dialog-centered">
                <div class="modal-content">
                  <div class="modal-header">
                    <h5 class="modal-title" id="exampleModalLabel">Добавление товара</h5>
                    <button type="button" class="btn-close" data-bs-dismiss="modal" aria-label="Close"></button>
                  </div>
                  <div class="modal-body">
                    <form>
                      <div class="mb-3">
                        <select class="form-select" id="select-prod">
                            <?
                                $res2 = mysqli_query($link, "
                                    SELECT p.id_product, p.product_name, p.article_number FROM products as p 
                                ");
                                ?>
                                    <option selected>Выберите товар</option>
                                <?
                                while ($row = mysqli_fetch_array($res2)){
                                    $id_product = $row['id_product'];
                                    $name = $row['product_name'];
                                    $article = $row['article_number'];
                                    ?>
                                        <option value="<? echo $id_product; ?>" data-name="<? echo $name; ?>" data-article="<? echo $article; ?>"><? echo $name; ?> (<? echo $article; ?>)</option>
                                    <?
                                }
                            ?>
                        </select>
                      </div>
                    </form>
                  </div>
                  <div class="modal-footer">
                    <button type="button" class="btn btn-secondary" data-bs-dismiss="modal">Отменить</button>
                    <button type="button" class="btn btn-primary" data-bs-dismiss="modal" id="addToOrder">Добавить товар</button>
                  </div>
                </div>
              </div>
            </div>
        <?
    }
    
    function createOutTransaction($link){
        ?>
            <a id="toTransactions" href="#transactions">
                <i class="fas fa-arrow-circle-left fa-2x" style="color:#6c757d;"></i>
            </a> 
            <script>
                $('#toTransactions').click(function(){
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
                
                $('#addToOrder').click(function(){
                    var productId = $('#select-prod').val();
                    var productName = $('#select-prod option:selected').data('name');
                    var productArticle = $('#select-prod option:selected').data('article');
                    $('#product-container').append('<div class="card" style="max-width: 16rem;margin:5px;"><div class="card-body"><p class="card-text"><b>'+productName+'</b><hr>Артикул: '+productArticle+'<br></p></div></div>');
                    var list = '' + $('#products').val();
                    list = '' + list + productId + ';';
                    $('#products').val(list);
                });
                
                $('#saveTransaction').click(function(){
                    var products = $('#products').val();
                    var company =  $('#select-company').val();
                    var transporter = $('#select-transporter').val();
                    $('#main-panel').empty();
                    $('#main-panel').html("<div class=\"row d-flex justify-content-center align-items-center\" style=\"height:75vh;\"><div class=\"spinner-grow\" role=\"status\"><span class=\"visually-hidden\">Загрузка...</span></div></div>");
                    $.ajax({
                    	url: 'script.php',
                    	method: 'post',
                    	dataType: 'html',
                    	data: {email: adminEmail, pass: adminPass, type: 'transactions', activity: 'saveTransaction', products: products, company: company, transporter: transporter, typeIO: 'OUT'},
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
            </script>
            <h5><center>Создание исходящей транзакции</center></h5>
            <div class="row">
                <div class="col-1"></div>
                <div class="col-10">
                    <b>Компания-получатель:</b>
                    <select class="form-select" id="select-company">
                        <?
                            $res2 = mysqli_query($link, "
                                SELECT `id_recipient`, `name`, `agent` FROM `companies` ORDER BY `name`
                            ");
                            ?>
                                <option selected>Выберите получателя</option>
                            <?
                            while ($row = mysqli_fetch_array($res2)){
                                $id_recipient = $row['id_recipient'];
                                $name = $row['name'];
                                $agent = $row['agent'];
                                ?>
                                    <option value="<? echo $id_recipient; ?>"><? echo $name; ?> (<? echo $agent; ?>)</option>
                                <?
                            }
                        ?>
                    </select>
                </div>
                <div class="col-1"></div>
            </div>
            <br>
            <div class="row">
                <div class="col-1"></div>
                <div class="col-10">
                    <b>Перевозчик:</b>
                    <select class="form-select" id="select-transporter">
                        <?
                            $res2 = mysqli_query($link, "
                                SELECT `id_transporter`, `transporter_name`, `auto_number` FROM `transporters` ORDER BY `transporter_name`
                            ");
                            ?>
                                <option selected>Выберите перевозчика</option>
                            <?
                            while ($row = mysqli_fetch_array($res2)){
                                $id_transporter = $row['id_transporter'];
                                $name = $row['transporter_name'];
                                $auto_number = $row['auto_number'];
                                ?>
                                    <option value="<? echo $id_transporter; ?>"><? echo $name; ?> (<? echo $auto_number; ?>)</option>
                                <?
                            }
                        ?>
                    </select>
                </div>
                <div class="col-1"></div>
            </div>
            <br>
            <div class="row">
                <div class="col-1"></div>
                <div class="col-10">
                    <b>Товары:</b>
                    <input type="hidden" name="products" value="">
                    <div style="display: flex; justify-content: start;" id="product-container">
                        <div class="card" id="product-add" data-bs-toggle="modal" data-bs-target="#exampleModal" style="width: 100px; background-color: green; color: white; cursor: pointer;">
                            <div class="card-body">
                                <h1><center>+</center></h1>
                            </div>
                        </div>
                    </div>
                </div>
                <div class="col-1"></div>
            </div>
            <br>
            <div class="row">
                <div class="col-1"></div>
                <div class="col-10">
                    <a type="button" class="btn btn-success" id="saveTransaction">Создать транзакцию</a>
                </div>
                <div class="col-1"></div>
            </div>
            <br>
            
            <div class="modal fade" id="exampleModal" tabindex="-1" aria-labelledby="exampleModalLabel" aria-hidden="true">
              <div class="modal-dialog modal-dialog-centered">
                <div class="modal-content">
                  <div class="modal-header">
                    <h5 class="modal-title" id="exampleModalLabel">Добавление товара</h5>
                    <button type="button" class="btn-close" data-bs-dismiss="modal" aria-label="Close"></button>
                  </div>
                  <div class="modal-body">
                    <form>
                      <div class="mb-3">
                        <select class="form-select" id="select-prod">
                            <?
                                $res2 = mysqli_query($link, "
                                    SELECT p.id_product, p.product_name, p.article_number FROM products as p 
                                ");
                                ?>
                                    <option selected>Выберите товар</option>
                                <?
                                while ($row = mysqli_fetch_array($res2)){
                                    $id_product = $row['id_product'];
                                    $name = $row['product_name'];
                                    $article = $row['article_number'];
                                    ?>
                                        <option value="<? echo $id_product; ?>" data-name="<? echo $name; ?>" data-article="<? echo $article; ?>"><? echo $name; ?> (<? echo $article; ?>)</option>
                                    <?
                                }
                            ?>
                        </select>
                      </div>
                    </form>
                  </div>
                  <div class="modal-footer">
                    <button type="button" class="btn btn-secondary" data-bs-dismiss="modal">Отменить</button>
                    <button type="button" class="btn btn-primary" data-bs-dismiss="modal" id="addToOrder">Добавить товар</button>
                  </div>
                </div>
              </div>
            </div>
        <?
    }
    
    function getEmptyShelf($link){
        $size = $_POST['size'];
        $res2 = mysqli_query($link, "
            SELECT 
                ws.id_storage, ws.sector, ws.row, ws.shelf 
            FROM warehouse_storage as ws 
            WHERE ws.size='".$size."' 
                AND ws.id_storage NOT IN (SELECT wp.id_storage FROM warehouse_positions as wp WHERE wp.date_add < NOW() AND YEAR(wp.date_remove) < 2000) 
            ORDER BY ws.sector, ws.row, ws.shelf
        ");
        ?>
            <option selected>Выберите место хранения</option>
        <?
        while ($row = mysqli_fetch_array($res2)){
            $id_storage = $row['id_storage'];
            $sector = $row['sector'];
            $row1 = $row['row'];
            $shelf = $row['shelf'];
            ?>
                <option value="<? echo $id_storage; ?>">Сектор <? echo $sector; ?>, ряд <? echo $row1; ?>, полка <? echo $shelf; ?></option>
            <?
        }
    }
    
    function viewProducts($link){
        if (isset($_POST['activity'])){
            $activity = $_POST['activity'];
            if ($activity == 'addProduct'){
                if (mysqli_query($link, "
                    INSERT INTO `products`(`product_name`, `article_number`, `price`, `quantity`, `comment`) VALUES ('".$_POST['name']."', '".$_POST['article']."', '".$_POST['price']."', '".$_POST['quantity']."', '".$_POST['comment']."')
                ") and mysqli_query($link, "
                    INSERT INTO `warehouse_positions`(`id_product`, `size`, `id_storage`, `date_add`) VALUES (LAST_INSERT_ID(), '".$_POST['size']."', '".$_POST['position']."', NOW())
                ")){
                    addToLog($link, 'INSERT', 'products');
                    addToLog($link, 'INSERT', 'warehouse_positions');
                } else {
                    ?>
                        <center><h5>Произошла ошибка. Попробуйте позже</h5></center>
                    <?
                    return;
                }
            }
        }
        ?>
            <script>
                $('#addProduct').click(function(){
                    $('#main-panel').empty();
                    $('#main-panel').html("<div class=\"row d-flex justify-content-center align-items-center\" style=\"height:75vh;\"><div class=\"spinner-grow\" role=\"status\"><span class=\"visually-hidden\">Загрузка...</span></div></div>");
                    $.ajax({
                    	url: 'script.php',
                    	method: 'post',
                    	dataType: 'html',
                    	data: {email: adminEmail, pass: adminPass, type: 'addProduct'},
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
                
                function getProductInfo(id){
                    console.log("Здесь должна быть функция просмотра товара со статистикой");
                }
            </script>
            <h5><center>Товары на складе</center></h5>
            <div class="row">
                <button class="btn btn-success" id="addProduct">Добавить новый товар</button>
            </div>
            <div class="table-responsive">
                <table class="table table-striped table-hover table-sm align-middle" width="90%">
                    <thead>
                        <tr>
                            <th scope="col">Наименование</th>
                            <th scope="col">Артикул</th>
                            <th scope="col">Цена</th>
                            <th scope="col">Количество</th>
                            <th scope="col">Комментарий</th>
                        </tr>
                    </thead>
                    <tbody>
                        <?
                            $j = 0;
                            $res2 = mysqli_query($link, "
                                SELECT 
                                    `id_product`, `product_name`, `article_number`, `price`, `quantity`, `comment` 
                                FROM `products`
                                ORDER BY
                                    `product_name` DESC LIMIT 50
                            ");
                            while ($row = mysqli_fetch_array($res2)){
                                $id_product = $row['id_product'];
                                $product_name = $row['product_name'];
                                $article_number = $row['article_number'];
                                $price = $row['price'];
                                $quantity = $row['quantity'];
                                $comment = $row['comment'];
                                
                                $j++;
                                ?>
                                    <tr onclick="getProductInfo(<? echo $id_product; ?>);">
                                        <td><? echo $product_name; ?></td>
                                        <td><? echo $article_number; ?></td>
                                        <td><? echo $price; ?></td>
                                        <td><? echo $quantity; ?></td>
                                        <td><? echo $comment; ?></td>
                                    </tr>
                                <?
                            }
                            if($j == 0){
                                ?>
                                    <tr><td colspan="5"><center>Ни одного товара на складе!</center></td></tr>
                                <?
                            }
                        ?>
                    </tbody>
                </table>
            </div>
        <?
    }
    
    function addProduct($link){
        ?>
            <a id="toProducts" href="#products">
                <i class="fas fa-arrow-circle-left fa-2x" style="color:#6c757d;"></i>
            </a> 
            <script>
                $('#toProducts').click(function(){
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
                
                $('input[name="size"]').click(function(){
                    var size = $(this).val();
                    $.ajax({
                    	url: 'script.php',
                    	method: 'post',
                    	dataType: 'html',
                    	data: {email: adminEmail, pass: adminPass, type: 'getEmptyShelf', size: size},
                    	success: function(data){
                            $('#select-place').empty();
                    		$('#select-place').html(data);
                    	},
                    	error: function (jqXHR, exception) {
                    		$('#main-panel').empty();
                    		$('#main-panel').html("<h2><center>Произошла ошибка. Попробуйте позже</center></h2>");
                    	}
                    });
                });
                
                $('#saveProduct').click(function(){
                    var name = $('input[name=name]').val();
                    var article = $('input[name=article]').val();
                    var price = $('input[name=price]').val();
                    var quantity = $('input[name=quantity]').val();
                    var size =  $('input[name="size"]:checked').val();
                    var position =  $('#select-place').val();
                    var comment = $('textarea[name=comment]').val();
                    $('#main-panel').empty();
                    $('#main-panel').html("<div class=\"row d-flex justify-content-center align-items-center\" style=\"height:75vh;\"><div class=\"spinner-grow\" role=\"status\"><span class=\"visually-hidden\">Загрузка...</span></div></div>");
                    $.ajax({
                    	url: 'script.php',
                    	method: 'post',
                    	dataType: 'html',
                    	data: {email: adminEmail, pass: adminPass, type: 'products', activity: 'addProduct', name: name, article: article, price: price, quantity: quantity, size: size, position: position, comment: comment},
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
            </script>
            <h5 style="margin-top:-27px;"><center>Добавить товар</center></h5>
            <br>
            <div class="row">
                <div class="col-1"></div>
                <div class="col-10">
                    <b>Название товара:</b>
                    <input type="text" name="name" class="form-control is-valid" placeholder="Samsung Galaxy A52" required>
                </div>
                <div class="col-1"></div>
            </div>
            <br>
            <div class="row">
                <div class="col-1"></div>
                <div class="col-10">
                    <b>Артикул:</b>
                    <input type="text" name="article" class="form-control is-valid" placeholder="8806090987618" required>
                </div>
                <div class="col-1"></div>
            </div>
            <br>
            <div class="row">
                <div class="col-1"></div>
                <div class="col-10">
                    <b>Цена:</b>
                    <input type="number" name="price" class="form-control is-valid" value="10" min="0" step="1" required>
                </div>
                <div class="col-1"></div>
            </div>
            <br>
            <div class="row">
                <div class="col-1"></div>
                <div class="col-10">
                    <b>Количество:</b>
                    <input type="number" name="quantity" class="form-control is-valid" value="1" min="1" step="1" required>
                </div>
                <div class="col-1"></div>
            </div>
            <br>
            <div class="row">
                <div class="col-1"></div>
                <div class="col-10">
                    <b>Размер:</b>
                    <br>
                    <input class="form-check-input" type="radio" name="size" id="sizeS" value="S">
                    <label class="form-check-label" for="sizeS">S</label>
                    <br>
                    <input class="form-check-input" type="radio" name="size" id="sizeM" value="M">
                    <label class="form-check-label" for="sizeM">M</label>
                    <br>
                    <input class="form-check-input" type="radio" name="size" id="sizeL" value="L">
                    <label class="form-check-label" for="sizeL">L</label>
                    <br>
                    <input class="form-check-input" type="radio" name="size" id="sizeXL" value="XL">
                    <label class="form-check-label" for="sizeXL">XL</label>
                </div>
                <div class="col-1"></div>
            </div>
            <br>
            <div class="row">
                <div class="col-1"></div>
                <div class="col-10">
                    <b>Место хранения на складе:</b>
                    <select class="form-select" id="select-place">
                    </select>
                </div>
                <div class="col-1"></div>
            </div>
            <br>
            <div class="row">
                <div class="col-1"></div>
                <div class="col-10">
                    <b>Комментарий:</b>
                    <textarea type="text" name="comment" class="form-control"></textarea>
                </div>
                <div class="col-1"></div>
            </div>
            <br>
            <div class="row">
                <div class="col-1"></div>
                <div class="col-10">
                    <a type="button" class="btn btn-success" id="saveProduct">Добавить</a>
                </div>
                <div class="col-1"></div>
            </div>
            <br>
        <?
    }
    
    function viewCompanies($link){
        if (isset($_POST['activity'])){
            $activity = $_POST['activity'];
            if ($activity == 'addCompany'){
                if (mysqli_query($link, "
                    INSERT INTO `companies`(`name`, `agent`) VALUES ('".$_POST['company']."', '".$_POST['fio']."')
                ")){
                    addToLog($link, 'INSERT', 'companies');
                } else {
                    ?>
                        <center><h5>Произошла ошибка. Попробуйте позже</h5></center>
                    <?
                    return;
                }
            }
        }
        ?>
            <script>
                $('#addCompany').click(function(){
                    $('#main-panel').empty();
                    $('#main-panel').html("<div class=\"row d-flex justify-content-center align-items-center\" style=\"height:75vh;\"><div class=\"spinner-grow\" role=\"status\"><span class=\"visually-hidden\">Загрузка...</span></div></div>");
                    $.ajax({
                    	url: 'script.php',
                    	method: 'post',
                    	dataType: 'html',
                    	data: {email: adminEmail, pass: adminPass, type: 'addCompany'},
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
            </script>
            <h5><center>Компании</center></h5>
            <div class="row">
                <button class="btn btn-success" id="addCompany">Добавить новую компанию</button>
            </div>
            <div class="row d-flex justify-content-center">
                <?
                    $result20 = mysqli_query($link, "SELECT `id_recipient`, `name`, `agent` FROM `companies` ORDER BY `name`");
                    while ($row6 = mysqli_fetch_array($result20)){
                        $idCompany = $row6['id_recipient'];
                        $name = $row6['name'];
                        $agent = $row6['agent'];
                        ?>
                            <div class="card" style="max-width: 16rem;margin:5px;">
                                <div class="card-body">
                                    <p class="card-text">
                                        <b><? echo $name; ?></b><hr>
                                        Контактное лицо: <? echo $agent; ?><br>
                                    </p>
                                </div>
                            </div>
                        <?
                    }
                ?>
            </div>
        <?
    }
    
    function addCompany($link){
        ?>
            <a id="toCompanies" href="#companies">
                <i class="fas fa-arrow-circle-left fa-2x" style="color:#6c757d;"></i>
            </a> 
            <script>
                $('#toCompanies').click(function(){
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
                
                $('#saveCompany').click(function(){
                    var company = $('input[name=company]').val();
                    var fio = $('input[name=fio]').val();
                    $('#main-panel').empty();
                    $('#main-panel').html("<div class=\"row d-flex justify-content-center align-items-center\" style=\"height:75vh;\"><div class=\"spinner-grow\" role=\"status\"><span class=\"visually-hidden\">Загрузка...</span></div></div>");
                    $.ajax({
                    	url: 'script.php',
                    	method: 'post',
                    	dataType: 'html',
                    	data: {email: adminEmail, pass: adminPass, type: 'companies', activity: 'addCompany', company: company, fio: fio},
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
            </script>
            <h5 style="margin-top:-27px;"><center>Добавить компанию</center></h5>
            <br>
            <div class="row">
                <div class="col-1"></div>
                <div class="col-10">
                    <b>Название компании:</b>
                    <input type="text" name="company" class="form-control is-valid" placeholder="ООО СДЭК" required>
                </div>
                <div class="col-1"></div>
            </div>
            <br>
            <div class="row">
                <div class="col-1"></div>
                <div class="col-10">
                    <b>ФИО агента:</b>
                    <input type="text" name="fio" class="form-control is-valid" placeholder="Иванов Иван Иванович" required>
                </div>
                <div class="col-1"></div>
            </div>
            <br>
            <div class="row">
                <div class="col-1"></div>
                <div class="col-10">
                    <a type="button" class="btn btn-success" id="saveCompany">Сохранить</a>
                </div>
                <div class="col-1"></div>
            </div>
            <br>
        <?
    }
    
    function viewTransporters($link){
        if (isset($_POST['activity'])){
            $activity = $_POST['activity'];
            if ($activity == 'addTransporter'){
                if (mysqli_query($link, "
                    INSERT INTO `transporters`(`transporter_name`, `auto_number`) VALUES ('".$_POST['name']."', '".$_POST['autoNumber']."')
                ")){
                    addToLog($link, 'INSERT', 'transporters');
                } else {
                    ?>
                        <center><h5>Произошла ошибка. Попробуйте позже</h5></center>
                    <?
                    return;
                }
            }
        }
        ?>
            <script>
                $('#addTransporter').click(function(){
                    $('#main-panel').empty();
                    $('#main-panel').html("<div class=\"row d-flex justify-content-center align-items-center\" style=\"height:75vh;\"><div class=\"spinner-grow\" role=\"status\"><span class=\"visually-hidden\">Загрузка...</span></div></div>");
                    $.ajax({
                    	url: 'script.php',
                    	method: 'post',
                    	dataType: 'html',
                    	data: {email: adminEmail, pass: adminPass, type: 'addTransporter'},
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
            </script>
            <h5><center>Перевозчики</center></h5>
            <div class="row">
                <button class="btn btn-success" id="addTransporter">Добавить нового перевозчика</button>
            </div>
            <div class="row d-flex justify-content-center">
                <?
                    $result20 = mysqli_query($link, "SELECT `id_transporter`, `transporter_name`, `auto_number` FROM `transporters` ORDER BY `transporter_name`");
                    while ($row6 = mysqli_fetch_array($result20)){
                        $idTransporter = $row6['id_transporter'];
                        $name = $row6['transporter_name'];
                        $auto = $row6['auto_number'];
                        ?>
                            <div class="card" style="max-width: 16rem;margin:5px;">
                                <div class="card-body">
                                    <p class="card-text">
                                        <b><? echo $name; ?></b><hr>
                                        Номер: <? echo $auto; ?><br>
                                    </p>
                                </div>
                            </div>
                        <?
                    }
                ?>
            </div>
        <?
    }
    
    function addTransporter($link){
        ?>
            <a id="toTransporters" href="#transporters">
                <i class="fas fa-arrow-circle-left fa-2x" style="color:#6c757d;"></i>
            </a> 
            <script>
                $('#toTransporters').click(function(){
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
                
                $('#saveTransporter').click(function(){
                    var name = $('input[name=name]').val();
                    var autoNumber = $('input[name=autoNumber]').val();
                    $('#main-panel').empty();
                    $('#main-panel').html("<div class=\"row d-flex justify-content-center align-items-center\" style=\"height:75vh;\"><div class=\"spinner-grow\" role=\"status\"><span class=\"visually-hidden\">Загрузка...</span></div></div>");
                    $.ajax({
                    	url: 'script.php',
                    	method: 'post',
                    	dataType: 'html',
                    	data: {email: adminEmail, pass: adminPass, type: 'transporters', activity: 'addTransporter', name: name, autoNumber: autoNumber},
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
            </script>
            <h5 style="margin-top:-27px;"><center>Добавить перевозчика</center></h5>
            <br>
            <div class="row">
                <div class="col-1"></div>
                <div class="col-10">
                    <b>ФИО перевозчика:</b>
                    <input type="text" name="name" class="form-control is-valid" placeholder="Иванов Иван Иванович" required>
                </div>
                <div class="col-1"></div>
            </div>
            <br>
            <div class="row">
                <div class="col-1"></div>
                <div class="col-10">
                    <b>Номер автомобиля:</b>
                    <input type="text" name="autoNumber" class="form-control is-valid" placeholder="а000аа 111" required>
                </div>
                <div class="col-1"></div>
            </div>
            <br>
            <div class="row">
                <div class="col-1"></div>
                <div class="col-10">
                    <a type="button" class="btn btn-success" id="saveTransporter">Сохранить</a>
                </div>
                <div class="col-1"></div>
            </div>
            <br>
        <?
    }
    
    function viewDocuments($link){
        if (isset($_POST['activity'])){
            $activity = $_POST['activity'];
            if ($activity == 'addDocument'){
                if (mysqli_query($link, "
                    INSERT INTO `documents`(`number`, `date`, `file_path`, `is_file_loaded`, `comment`) VALUES ('".$_POST['number']."', NOW(), '".$_POST['path']."', '".$_POST['isFileLoaded']."', '".$_POST['comment']."')
                ")){
                    addToLog($link, 'INSERT', 'documents');
                } else {
                    ?>
                        <center><h5>Произошла ошибка. Попробуйте позже</h5></center>
                    <?
                    return;
                }
            }
        }
        ?>
            <script>
                $('#addDocument').click(function(){
                    $('#main-panel').empty();
                    $('#main-panel').html("<div class=\"row d-flex justify-content-center align-items-center\" style=\"height:75vh;\"><div class=\"spinner-grow\" role=\"status\"><span class=\"visually-hidden\">Загрузка...</span></div></div>");
                    $.ajax({
                    	url: 'script.php',
                    	method: 'post',
                    	dataType: 'html',
                    	data: {email: adminEmail, pass: adminPass, type: 'addDocument'},
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
            </script>
            <h5><center>Документы</center></h5>
            <div class="row">
                <button class="btn btn-success" id="addDocument">Добавить новый документ</button>
            </div>
            <div class="row d-flex justify-content-center">
                <?
                    $result20 = mysqli_query($link, "SELECT `id_document`, `number`, `date`, `file_path`, `is_file_loaded`, `comment` FROM `documents` ORDER BY `date`");
                    while ($row6 = mysqli_fetch_array($result20)){
                        $idDocument = $row6['id_document'];
                        $number = $row6['number'];
                        $date = $row6['date'];
                        $filePath = $row6['file_path'];
                        $isFileLoaded = $row6['is_file_loaded'];
                        $comment = $row6['comment'];
                        ?>
                            <div class="card" style="max-width: 16rem;margin:5px;">
                                <div class="card-body">
                                    <p class="card-text">
                                        <b>Документ №<? echo $number; ?></b><hr>
                                        Добавлено: <? echo goodDate($date); ?><br>
                                        <i><? echo $comment; ?></i>
                                        <hr>
                                        <?
                                            if ($isFileLoaded){
                                                ?>
                                                    <a href="<? echo $filePath; ?>" target="_blank" class="btn btn-primary">Просмотреть</a>
                                                <?
                                            } else {
                                                ?>
                                                    Файл не загружен в систему
                                                <?
                                            }
                                        ?>
                                    </p>
                                </div>
                            </div>
                        <?
                    }
                ?>
            </div>
        <?
    }
    
    function addDocument($link){
        ?>
            <a id="toDocuments" href="#documents">
                <i class="fas fa-arrow-circle-left fa-2x" style="color:#6c757d;"></i>
            </a> 
            <script>
                $('#toDocuments').click(function(){
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
                $('#filePath').hide();
                $('#isLoadedFile').click(function(){
                	if ($(this).is(':checked')){
                		$('#filePath').show(100);
                	} else {
                		$('#filePath').hide(100);
                	}
                });
                
                $('#saveDocument').click(function(){
                    var number = $('input[name=number]').val();
                    if ($('#isLoadedFile').is(':checked')){
                        var isFileLoaded = 1;
                    } else {
                        var isFileLoaded = 0;
                    }
                    var path = $('input[name=path]').val();
                    var comment = $('textarea').val();
                    if (isFileLoaded){
                        path = "https://nav-com.ru/itmo/docs/" + path
                    }
                    $('#main-panel').empty();
                    $('#main-panel').html("<div class=\"row d-flex justify-content-center align-items-center\" style=\"height:75vh;\"><div class=\"spinner-grow\" role=\"status\"><span class=\"visually-hidden\">Загрузка...</span></div></div>");
                    $.ajax({
                    	url: 'script.php',
                    	method: 'post',
                    	dataType: 'html',
                    	data: {email: adminEmail, pass: adminPass, type: 'documents', activity: 'addDocument', number: number, isFileLoaded: isFileLoaded, path: path, comment: comment},
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
            </script>
            <h5 style="margin-top:-27px;"><center>Добавить документ</center></h5>
            <br>
            <div class="row">
                <div class="col-1"></div>
                <div class="col-10">
                    <b>Номер:</b>
                    <input type="text" name="number" class="form-control is-valid" placeholder="Пример: П-369/2022" required>
                </div>
                <div class="col-1"></div>
            </div>
            <br>
            <div class="row">
                <div class="col-1"></div>
                <div class="col-10">
                    <div class="form-check form-switch">
                        <input class="form-check-input" type="checkbox" id="isLoadedFile">
                        <label class="form-check-label" for="isLoadedFile">Файл в системе</label>
                    </div>
                </div>
                <div class="col-1"></div>
            </div>
            <br>
            <div class="row" id="filePath">
                <div class="col-1"></div>
                <div class="col-10">
                    <b>Путь к файлу:</b>
                    <div class="input-group mb-3">
                        <span class="input-group-text" id="basic-addon3">https://nav-com.ru/itmo/docs/</span>
                        <input type="text" name="path" class="form-control is-valid" aria-describedby="basic-addon3" placeholder="file_name.pdf">
                    </div>
                    <br>
                </div>
                <div class="col-1"></div>
            </div>
            <div class="row">
                <div class="col-1"></div>
                <div class="col-10">
                    <b>Комментарий:</b>
                    <textarea type="text" name="comment" class="form-control"></textarea>
                </div>
                <div class="col-1"></div>
            </div>
            <br>
            <div class="row">
                <div class="col-1"></div>
                <div class="col-10">
                    <a type="button" class="btn btn-success" id="saveDocument">Сохранить</a>
                </div>
                <div class="col-1"></div>
            </div>
            <br>
        <?
    }
    
    function viewWorkers($link){
        if (isset($_POST['activity'])){
            $activity = $_POST['activity'];
            if ($activity == 'addWorker'){
                if (mysqli_query($link, "
                    INSERT INTO `workers`(`name`, `role`) VALUES ('".$_POST['fio']."', '".$_POST['position']."')
                ")){
                    addToLog($link, 'INSERT', 'workers');
                } else {
                    ?>
                        <center><h5>Произошла ошибка. Попробуйте позже</h5></center>
                    <?
                    return;
                }
            }
        }
        ?>
            <script>
                $('#addWorker').click(function(){
                    $('#main-panel').empty();
                    $('#main-panel').html("<div class=\"row d-flex justify-content-center align-items-center\" style=\"height:75vh;\"><div class=\"spinner-grow\" role=\"status\"><span class=\"visually-hidden\">Загрузка...</span></div></div>");
                    $.ajax({
                    	url: 'script.php',
                    	method: 'post',
                    	dataType: 'html',
                    	data: {email: adminEmail, pass: adminPass, type: 'addWorker'},
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
            </script>
            <h5><center>Работники склада</center></h5>
            <div class="row">
                <button class="btn btn-success" id="addWorker">Добавить нового работника</button>
            </div>
            <div class="row d-flex justify-content-center">
                <?
                    $result20 = mysqli_query($link, "SELECT * FROM `workers` ORDER BY `role`");
                    while ($row6 = mysqli_fetch_array($result20)){
                        $idWorker = $row6['id_worker'];
                        $name = $row6['name'];
                        $role = $row6['role'];
                        ?>
                            <div class="card" style="max-width: 16rem;margin:5px;">
                                <div class="card-body">
                                    <p class="card-text">
                                        <b><? echo $name; ?></b><hr>
                                        <i><? echo $role; ?></i>
                                    </p>
                                </div>
                            </div>
                        <?
                    }
                ?>
            </div>
        <?
    }
    
    function addWorker($link){
        ?>
            <a id="toWorkers" href="#workers">
                <i class="fas fa-arrow-circle-left fa-2x" style="color:#6c757d;"></i>
            </a> 
            <script>
                $('#toWorkers').click(function(){
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
                
                $('#saveWorker').click(function(){
                    var fio = $('input[name=name]').val();
                    var position = $('input[name=position]').val();
                    $('#main-panel').empty();
                    $('#main-panel').html("<div class=\"row d-flex justify-content-center align-items-center\" style=\"height:75vh;\"><div class=\"spinner-grow\" role=\"status\"><span class=\"visually-hidden\">Загрузка...</span></div></div>");
                    $.ajax({
                    	url: 'script.php',
                    	method: 'post',
                    	dataType: 'html',
                    	data: {email: adminEmail, pass: adminPass, type: 'workers', activity: 'addWorker', fio: fio, position: position},
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
            </script>
            <h5 style="margin-top:-27px;"><center>Добавить работника</center></h5>
            <br>
            <div class="row">
                <div class="col-1"></div>
                <div class="col-10">
                    <b>ФИО:</b>
                    <input type="text" name="name" class="form-control is-valid" placeholder="Иванов Иван Иванович" required>
                </div>
                <div class="col-1"></div>
            </div>
            <br>
            <div class="row">
                <div class="col-1"></div>
                <div class="col-10">
                    <b>Должность:</b>
                    <input type="text" name="position" class="form-control is-valid" placeholder="Главный бухгалтер" required>
                </div>
                <div class="col-1"></div>
            </div>
            <br>
            <div class="row">
                <div class="col-1"></div>
                <div class="col-10">
                    <a type="button" class="btn btn-success" id="saveWorker">Сохранить</a>
                </div>
                <div class="col-1"></div>
            </div>
            <br>
        <?
    }
    
    function viewLog($link){
        $resultArray = array();
        $result = mysqli_query($link, "SELECT * FROM `db_log` ORDER BY `datetime` DESC LIMIT 25"); 
        while ($res = mysqli_fetch_array($result)){
            $tempArray = array(
                "id" => $res['id_recording'],
                "type" => $res['type'],
                "date" => goodDate($res['datetime']),
                "comment" => $res['description']
            );
            array_push($resultArray, $tempArray);
        }
        ?>
            <h5><center>Лог записей базы данных</center></h5>
            <table class="table table-hover">
                <thead>
                    <tr>
                        <th scope="col">#</th>
                        <th scope="col">Тип</th>
                        <th scope="col">Дата</th>
                        <th scope="col">Описание</th>
                    </tr>
                </thead>
                <tbody>
                    <?
                        $counter = 1;
                        foreach ($resultArray as $item){
                            ?>
                                <tr>
                                    <th scope="row"><? echo $counter; ?></th>
                                    <td><b><? echo $item['type']; ?></b></td>
                                    <td><? echo $item['date']; ?></td>
                                    <td><? echo $item['comment']; ?></td>
                                </tr>
                            <?
                            $counter++;
                        }
                    ?>
                </tbody>
            </table>
        <?
    }

    function about($date){
        ?>
            <div class="wrapper">
                <div class="layer">
                    <h3>
                        <center>Админ-панель <br>склада товаров</center>
                    </h3>
                    <h6><center>версия 1.0</center></h6>
                    <center><b>Обновлено</b> <? echo goodDate($date); ?></center><br>
                    <center><a href="mailto:anegrash@nav-com.ru" target="_blank">Сообщить об ошибке</a></center>
                    <hr>
                    <center>Сделано с любовью ❤️ на 3 курсе ИТМО</center>
                    <center><a type="button" class="btn btn-white" href="https://nav-com.ru/" target="_blank">
                        <img src="https://nav-com.ru/img/logo_full.png" width="70vw">
                    </a></center>
                </div>
            </div>
            
            <style>
                html, body, .row {
                    height: 100%;
                }
                .container-fluid {
                    height: 90%;
                    margin-top: 1.5%;
                }
                .wrapper {
                    display: flex;
                    height: 100%;
                    align-items: center;
                    padding-top: 40px;
                    padding-bottom: 40px;
                }
                
                .layer {
                    width: 100%;
                    max-width: 330px;
                    padding: 15px;
                    margin: auto;
                    border: 1px solid gray;
                    border-radius: 5px;
                    background-color: #f5f5f5;
                }
            </style>
        <?
    }
    
    function searchGlobal($link){
        $input = $_POST['input'];
        $resultArray = array();
        $result = mysqli_query($link, "
            SELECT
                c.id_recipient as id,
                c.name as name,
                'COMPANY' as type
            FROM companies as c
            WHERE c.name LIKE '%".$input."%'
            UNION SELECT
                d.id_document as id,
                CONCAT_WS(' ', 'Документ №', d.number) as name,
                'DOCUMENT' as type
            FROM documents as d
            WHERE d.number LIKE '%".$input."%'
            UNION SELECT
                p.id_product as id,
                p.product_name as name,
                'PRODUCT' as type
            FROM products as p
            WHERE
                p.product_name LIKE '%".$input."%' OR
                p.article_number LIKE '%".$input."%'
            UNION SELECT
                t.id_transporter as id,
                t.transporter_name as name,
                'TRANSPORTER' as type
            FROM transporters as t
            WHERE
                t.transporter_name LIKE '%".$input."%' OR
                t.auto_number LIKE '%".$input."%'
            UNION SELECT
                w.id_worker as id,
                w.name as name,
                'WORKER' as type
            FROM workers as w
            WHERE w.name LIKE '%".$input."%'
        "); 
        while ($res = mysqli_fetch_array($result)){
            $tempArray = array(
                "id" => $res['id'],
                "name" => $res['name'],
                "type" => $res['type'],
            );
            array_push($resultArray, $tempArray);
        }
        ?>
            <h5><center>Результаты поиска по системе</center></h5>
            <p>> <? echo $input; ?></p>
            <table class="table table-hover">
                <thead>
                    <tr>
                        <th scope="col">id</th>
                        <th scope="col">Название/Имя</th>
                        <th scope="col">Раздел</th>
                    </tr>
                </thead>
                <tbody>
                    <?
                        foreach ($resultArray as $item){
                            ?>
                                <tr>
                                    <th scope="row"><? echo $item['id']; ?></th>
                                    <td><b><? echo $item['name']; ?></b></td>
                                    <td><? echo getSection($item['type']); ?></td>
                                </tr>
                            <?
                        }
                    ?>
                </tbody>
            </table>
        <?
    }
    
    function getSection($section){
        switch ($section){
            case "COMPANY": return "Компании";
            case "DOCUMENT": return "Документы";
            case "PRODUCT": return "Товары";
            case "TRANSPORTER": return "Перевозчики";
            case "WORKER": return "Работники";
        }
    }
    
    function goodDate($date){
        $exp= explode(' ',$date);
        $dateG=$exp[0];
        $timeG=$exp[1];
        
        $dateG= explode('-',$dateG);
        $dayG="".$dateG[2];
        $monthG="".$dateG[1];
        $yearG="".$dateG[0];
        
        $timeG= explode(':',$timeG);
        $hourG="".$timeG[0];
        $minuteG="".$timeG[1];
        
        $dateThis = mktime(0, 0, 0, $monthG, $dayG, $yearG);
        $tomorrow  = mktime(0, 0, 0, date("m"), date("d")+1, date("Y"));
        $afterTomorrow  = mktime(0, 0, 0, date("m"), date("d")+2, date("Y"));
        
        if($yearG == date('Y') and $monthG == date('m') and $dayG == date('d')){
            return "сегодня в ".$hourG.":".$minuteG;
        }
        
        if($dateThis == $tomorrow){
            return "завтра в ".$hourG.":".$minuteG;
        }
        
        if($dateThis == $afterTomorrow){
            return "послезавтра в ".$hourG.":".$minuteG;
        }
        
        switch($monthG){
            case 1: $monthText="января"; break;
            case 2: $monthText="февраля"; break;
            case 3: $monthText="марта"; break;
            case 4: $monthText="апреля"; break;
            case 5: $monthText="мая"; break;
            case 6: $monthText="июня"; break;
            case 7: $monthText="июля"; break;
            case 8: $monthText="августа"; break;
            case 9: $monthText="сентября"; break;
            case 10: $monthText="октября"; break;
            case 11: $monthText="ноября"; break;
            case 12: $monthText="декабря"; break;
            
        }
    
        $weekDay = date("N", mktime(0, 0, 0, $monthG, $dayG, $yearG));
        switch($weekDay){
            case 1: $dayText="понедельник"; break;
            case 2: $dayText="вторник"; break;
            case 3: $dayText="среда"; break;
            case 4: $dayText="четверг"; break;
            case 5: $dayText="пятница"; break;
            case 6: $dayText="суббота"; break;
            case 7: $dayText="воскресенье"; break;
            
        }
        
        return (int)$dayG." ".$monthText.($yearG != date('Y') ? " ".$yearG." года" : "").", ".$dayText.", ".$hourG.":".$minuteG;
    }
    
    function addToLog($link, $type, $table){
        $message = "";
        if ($type == "INSERT"){
            $message = "Новая запись добавлена в таблицу `".$table."`";
        } else if ($type == "UPDATE"){
            $message = "Обновление записи в таблице `".$table."`";
        } else if ($type == "DELETE"){
            $message = "Запись удалена в таблице `".$table."`";
        } else {
            $type = "UPDATE";
        }
        mysqli_query($link, "INSERT INTO `db_log`(`datetime`, `type`, `description`) VALUES (NOW(), '".$type."', '".$message."')"); 
    }
?>