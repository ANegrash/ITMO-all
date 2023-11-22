<%--
  Created by IntelliJ IDEA.
  User: admin
  Date: 26.10.2020
  Time: 15:36
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD html 4.01//EN"
"http://www.w3.org/TR/html4/strict.dtd">
<HTML lang="en">
<head>
    <meta charset="UTF-8">
    <title>
        Lab 2
    </title>
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css"
          integrity="sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T" crossorigin="anonymous">
    <link rel="icon" type="image/png" href="Resources/icon.png">
    <script src="clientScript/Script.js"></script>
    <link href="styles/styleStart.css" rel="stylesheet">
    <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js"
            integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo"
            crossorigin="anonymous"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.7/umd/popper.min.js"
            integrity="sha384-UO2eT0CpHqdSJQ6hJty5KVphtPhzWj9WO1clHTMGa3JDZwrnQq4sF86dIHNDz0W1"
            crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js"
            integrity="sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM"
            crossorigin="anonymous"></script>
</head>
<body>

<header>
    <div class="pos-f-t">
        <div class="collapse show" id="navbarToggleExternalContent">
            <div class="bg-dark p-4">
                <h5 class="text-white h4">Rogachev Kirill Olegovich - P3230<br>Negrash Andrey Vladimirovich - P3230</h5>
                <span class="text-muted">Variant 2635</span>
            </div>
        </div>
        <nav class="navbar navbar-dark bg-dark d-flex justify-content-center">
            <button class="navbar-toggler" type="button" data-toggle="collapse"
                    data-target="#navbarToggleExternalContent" aria-controls="navbarToggleExternalContent"
                    aria-expanded="true" aria-label="Toggle navigation">
                <span class="navbar-toggler-icon"></span>
            </button>
        </nav>
    </div>
</header>

<div style="padding:5%">
    <form method="post" onsubmit="checkText(this);" action="/Lab2/control">
        <table id="page-table-F">
            <tr>
                <td colspan="14">
                    <div>
                        <svg id="image-coordinates">
                            <rect width="300" height="300" fill="rgb(255,255,255)" stroke-width="1"
                                  stroke="rgb(0,0,0)"/>

                            <circle cx="150" cy="150" r="120" fill="rgb(0,255,255)" stroke-width="1"
                                    stroke="rgb(0,0,0)"/>
                            <polyline points="150,150 150,300 300,300 300,0 0,0 0,150 150,150" fill="rgb(255,255,255)"
                                      stroke-width="1"
                                      stroke="rgb(0,0,0)"/>

                            <rect x="30" y="90" width="120" height="60" fill="rgb(0,255,255)" stroke-width="1"
                                  stroke="rgb(50,50,50)"/>

                            <polyline points="150,90 270,150 150,150 150,90" fill="rgb(0,255,255)" stroke-width="1"
                                      stroke="rgb(0,0,0)"/>

                            <line x1="150" y1="0" x2="150" y2="500" stroke-width="1" stroke="rgb(0,0,0)"/>
                            <line x1="0" y1="150" x2="300" y2="150" stroke-width="1" stroke="rgb(0,0,0)"/>

                            <line x1="145" y1="30" x2="155" y2="30" stroke-width="1" stroke="rgb(0,0,0)"/>
                            <line x1="145" y1="90" x2="155" y2="90" stroke-width="1" stroke="rgb(0,0,0)"/>

                            <line x1="30" y1="145" x2="30" y2="155" stroke-width="1" stroke="rgb(0,0,0)"/>
                            <line x1="90" y1="145" x2="90" y2="155" stroke-width="1" stroke="rgb(0,0,0)"/>

                            <line x1="210" y1="145" x2="210" y2="155" stroke-width="1" stroke="rgb(0,0,0)"/>
                            <line x1="270" y1="145" x2="270" y2="155" stroke-width="1" stroke="rgb(0,0,0)"/>

                            <line x1="145" y1="210" x2="155" y2="210" stroke-width="1" stroke="rgb(0,0,0)"/>
                            <line x1="145" y1="270" x2="155" y2="270" stroke-width="1" stroke="rgb(0,0,0)"/>

                            <polyline points="150,0 140,15 150,5 160,15 150,0" fill="rgb(249,249,249)" stroke-width="1"
                                      stroke="rgb(0,0,0)"/>
                            <polyline points="300,150 285,140 295,150 285,160 300,150" fill="rgb(249,249,249)"
                                      stroke-width="1" stroke="rgb(0,0,0)"/>




                        </svg>
                    </div>

                </td>
            </tr>

            <tr id="buttonRow">
                <td colspan="5" width="auto"><p width="90px">Change X</p></td>

            </tr>

            <tr>
                <td colspan="7">Change Y [-5;3]</td>
                <td class="chooseable" colspan="7"><input class="form-control" id="text_input_Y" type="text"
                                                          name="answerY" value="0">
                </td>
            </tr>

            <tr>
                <td colspan="7">Change R [2;5]</td>
                <td class="chooseable" colspan="7"><input class="form-control" id="text_input_R" type="text"
                                                          name="answerR" value="2">
                </td>
            </tr>

            <tr>
                <td colspan="14">
                    <input id="submitButton" class="btn btn-block btn-dark" type="submit" value="Send">
                    <input id="vX" type="hidden" name="answerX" value="0">
                </td>
            </tr>
        </table>
    </form>
</div>
<div class="footer d-flex justify-content-end">
    <a class="btn btn-dark rounded-pill" href="https://github.com/selbstbeherrschung/web-lab-1"><img
            src="https://nav-com.ru/img/git.png" width="50px" alt="GitHub"></a>
</div>

</body>

