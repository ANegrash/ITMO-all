<%@ page import="Resources.SessionShotsBean" %>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8"/>
    <title>Result</title> <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css" integrity="sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T" crossorigin="anonymous">
    <link rel="icon" type="image/png" href="resources/icon.png">
    <link href="styles/styleResult.css" rel="stylesheet">
    <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.7/umd/popper.min.js" integrity="sha384-UO2eT0CpHqdSJQ6hJty5KVphtPhzWj9WO1clHTMGa3JDZwrnQq4sF86dIHNDz0W1" crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js" integrity="sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM" crossorigin="anonymous"></script>
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
            <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarToggleExternalContent" aria-controls="navbarToggleExternalContent" aria-expanded="true" aria-label="Toggle navigation">
                <span class="navbar-toggler-icon"></span>
            </button>
        </nav>
    </div>
</header>

<div id="content-panel">
    ${Content}
</div>

<div id="table-panel" style="padding: 5%">
    <div id="result" class="custom_scrollbar">
        <table class="page-table-T" border="1">
            <thead class="header" id="headerTable">
            <tr>
                <th id="x-id" class="stickyTh"><center>X</center></th>
                <th class="y-class stickyTh"><center>Y</center></th>
                <th class="r-class stickyTh"><center>R</center></th>
                <th class="som-class stickyTh"><center>Y/N</center></th>
                <th class="stt-class stickyTh"><center>Start time</center></th>
                <th class="sct-class stickyTh"><center>Script time</center></th>
            </tr>
            </thead>
            <tbody>
            <%
                SessionShotsBean shots = (SessionShotsBean) request.getSession().getAttribute("shots");
                if(shots != null){
                    out.print(shots.writeAll());
                }
            %>

            </tbody>

        </table>

    </div>
    <center>
    <div class="page-table-T">
        <a href="/Lab2" class="btn btn-block btn-dark" id="footer-form">Form</a>
    </div>
    </center>
</div>

<div class="footer d-flex justify-content-end">
    <a class="btn btn-dark rounded-pill" href="https://github.com/selbstbeherrschung/web-lab-1"><img src="https://nav-com.ru/img/git.png" width="50px" alt="GitHub"></a>
</div>

</body>
</html>