<!--
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
-->
<!DOCTYPE html>
<html>
<head>
    <title>Registration</title>
    <script src="https://unpkg.com/vue"></script>
    <link rel="stylesheet" href="styles/registration.css"/>
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css"
          integrity="sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T" crossorigin="anonymous">
    <script src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.0/jquery.min.js"/>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.7/umd/popper.min.js"
            integrity="sha384-UO2eT0CpHqdSJQ6hJty5KVphtPhzWj9WO1clHTMGa3JDZwrnQq4sF86dIHNDz0W1"
            crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js"
            integrity="sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM"
            crossorigin="anonymous"></script>

</head>

<body>
<div id="app">
    <center>
        {{ message }}
        <br>
        <button onclick="location.href = '../Lab4/';" class="btn btn-primary">Go login</button>
    </center>

</div>
<div class="form-row">
    <div class="col-4"></div>
    <div class="col-4" id="form">
        <br>
        <div class="form-row">
            <div class="ots"></div>
            <div class="pole">
                <h3>
                    <center>Lab 4</center>
                </h3>
            </div>
            <div class="ots"></div>
        </div>
        <br>

        <div class="form-row">
            <div class="ots"></div>
            <div class="pole">
                <h6>Email:</h6>
                <input v-model="login" id="email-text" placeholder="me@example.com" type="email" class="form-control is-valid"
                       style="min-width:200px" required>
            </div>
            <div class="ots"></div>
        </div>
        <br>

        <div class="form-row">
            <div class="ots"></div>
            <div class="pole">
                <h6>Password:</h6>
                <input v-model="pass" id="password-text" placeholder="Your pass" class="form-control is-valid" type="password"
                       style="min-width:200px" required>
            </div>
            <div class="ots"></div>
        </div>
        <br>

        <div class="form-row">
            <div class="ots"></div>
            <div class="pole">
                <input v-model="passR" id="password-r-text" placeholder="Repeat your pass" class="form-control is-valid" type="password"
                       style="min-width:200px" required>
            </div>
            <div class="ots"></div>
        </div>
        <br>

        <div class="form-row d-flex align-items-center">
            <div class="col-3">
                <div class="ots"></div>
                <div class="pole" id="login">
                    <button type="submit" class="btn btn-primary" v-on:click="greet">Log in</button>
                </div>
                <div class="ots"></div>
            </div>
            <div class="col-1"></div>
            <div class="col-5">
                <h6>Status: </h6>
                <h6 id="register-status"></h6>
                <div class="ots"></div>
            </div>
            <div class="col-3"></div>


        </div>
        <br>
    </div>
    <div class="col-4"></div>
</div>

<script src="scripts/index.js"></script>
<script>
    new Vue({
        el: '#form',
        data: {
            login: "",
            pass: "",
            passR: ""
        },
        methods: {
            greet: function (event) {
                if (this.pass === this.passR) {
                    document.getElementById("password-text").classList.replace("is-invalid", "is-valid");
                    document.getElementById("password-r-text").classList.replace("is-invalid", "is-valid");
                    console.log("Right password repeating");
                    sendDataRegistration(this.login, this.pass);
                } else {
                    document.getElementById("password-text").classList.replace("is-valid", "is-invalid");
                    document.getElementById("password-r-text").classList.replace("is-valid", "is-invalid");
                    document.getElementById("register-status").innerText = "Wrong password repeating";
                    console.log("Wrong password repeating");
                }

            }
        }

    })
    new Vue({
        el: '#app',
        data: {
            message: 'Rogachev&Negrash presents'
        }
    })

</script>
</body>
</html>