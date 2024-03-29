#include <Arduino.h>

// # # # System control page # # #

const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en" dir="ltr">
  <head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>PILLBOX CONTROLLER</title>

    <!-- Bootstrap CSS -->
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/css/bootstrap.min.css">

    <style media="screen">

    body {
        margin:0;
        padding:0;
        background-color: #ECEEEF;
    }

    .cards {
      background-color: black;
      aspect-ratio : 1 / 1;
      border-radius: 10px;
    }

    .borders {
      padding: 20px;
      border-color: red;
    }

    .navbar{
      margin-left: 10px;
      margin-top: 10px;
      border-top-left-radius: 10px;
      border-bottom-left-radius: 10px
    }

    .btn {
      margin-left: 10px;;
      outline-color: #7895B2;
      transition: transform 0.3s ease;
    }

    .form-control {
      border-color: #80B2C9;
      margin-bottom: 5px;
    }

    .form-control::placeholder {
      color: #BCBEBF;
    }

    .btn:hover {
      transform: scale(1.1);
    }

    .btn:active {
      transform: scale(0.9);
    }

    .header {
      background-color: #92A9BD;
      box-shadow: rgba(0, 0, 0, 0.4) 0px 2px 4px, rgba(0, 0, 0, 0.3) 0px 7px 13px -3px, rgba(0, 0, 0, 0.2) 0px -3px 0px inset;
    }

    .notific {
      align-items: center;
    }

    .card {
      border-color: white;
      box-shadow: rgba(0, 0, 0, 0.15) 0px 3px 3px 0px;
    }

    .alerts {
      margin: 5px;
    }

    .customRow {
      margin-left: 10px;
    }

    .custom-close {
      position: absolute;
      top: 0;
      right: 0;
      padding: 0.5rem;
      background-color: transparent;
      border: none;
      outline: none;
      cursor: pointer;
    }

    .alert {
      /* Add animation styles */
      animation-name: popup;
      animation-duration: 0.3s;
      animation-timing-function: ease-in-out;
      animation-fill-mode: both;
    }

    .boxCards {
      background-color: white;
      border-radius: 10px;
      margin: 10px;
    }

    @keyframes popup {
      0% {
        opacity: 0;
        transform: scale(0.8);
      }
      50% {
        opacity: 1;
        transform: scale(1.1);
      }
      100% {
        opacity: 1;
        transform: scale(1);
      }
    }


    /* dark mode*/


    </style>

  </head>
  <body>
    <!-- HTML Content -->

    <div class="row">
      <div class="col-sm-12">
        <nav class="navbar header">
          <form class="form-inline">
            <button type="button" class="btn"  onclick="redirectToStatistics()" >Statistics</button>
            <button type="button" class="btn">Info</button>
            <button type="button" class="btn" onclick="logout()">Logout</button>
          </form>
        </nav>
      </div>
    </div>

    <div class="row">
      <div class="col-sm-9 customRow">

        <div class="row">
          <div class="col-sm-5 boxCards ">
            <div class="row borders d-flex justify-content-center" align="center">
              <div class="col-sm-5 boxCards">
                <h6>Box Controlles</h6>
              </div>
            </div>
          </div>

          <div class="col-sm-5 boxCards">
            <div class="row borders d-flex justify-content-center" align="center">
              <div class="col-sm-5 boxCards ">
                <h6>Tower Controlles</h6>
              </div>
            </div>
          </div>
        </div>

        <div class="row">
          <div class="col-sm-5 boxCards">

            <div class="row borders d-flex justify-content-center" align="center">

              <div class="col-sm-5">
                <div class="card uppercard" >
                  <div class="card-body">
                    <h5 class="card-title">Drop Pill</h5>
                    <h6 class="card-subtitle mb-2 text-muted">box</h6>
                    <p class="card-text">Drops one single pill.</p>
                    <button type="button" class="btn btn-dark" onclick="sendSingleDropRequest()">Drop</button>
                  </div>
                </div>
              </div>

              <div class="col-sm-1">
              </div>

              <div class="col-sm-5">
                <div class="card">
                  <div class="card-body">
                    <h5 class="card-title">Drop Pill</h5>
                    <h6 class="card-subtitle mb-2 text-muted">box</h6>
                    <p class="card-text">Drops the specified pill amount.</p>
                    <form>
                      <input class="form-control" id="specifiedDrop" placeholder="amount">
                    </form>
                    <button type="button" class="btn btn-dark" onclick="sendSpecifiedPillDrop()">Drop</button>
                  </div>
                </div>
              </div>

            </div>

            <div class="row borders d-flex justify-content-center" align="center">

              <div class="col-sm-5">
                <div class="card">
                  <div class="card-body">
                    <h5 class="card-title">Pill amount</h5>
                    <h6 class="card-subtitle mb-2 text-muted">box</h6>
                    <p class="card-text">Set a new specified pill amount.</p>
                    <form>
                      <input class="form-control" id="inputFieldPillBox" placeholder="amount">
                    </form>
                    <button type="button" class="btn btn-dark"  onclick="sendPillInputRequest()">Set</button>
                  </div>
                </div>
              </div>

              <div class="col-sm-1">
              </div>

              <div class="col-sm-5">
                <div class="card">
                  <div class="card-body">
                    <h5 class="card-title">Timer</h5>
                    <h6 class="card-subtitle mb-2 text-muted">box</h6>
                    <p class="card-text">Set a timer.</p>
                    <input class="form-control" type="number" id="hours" placeholder="hours : 00" name="hours" min="0" max="23" required>
                    <input class="form-control" type="number" id="minutes" placeholder="minutes : 00" name="minutes" min="0" max="59" required>
                    <input class="form-control" type="number" id="seconds" placeholder="hours : 00" name="seconds" min="0" max="59" required>
                    <input class="form-control" type="number" id="boxAmount" placeholder="amount" name="boxAmount" min="1" required>
                    <button type="button" class="btn btn-dark" onclick="sendTimer()">Set</button>
                  </div>
                </div>
              </div>

            </div>

            <div class="row borders d-flex justify-content-center" align="center">

              <div class="col-sm-5">
                <div class="card">
                  <div class="card-body">
                    <h5 class="card-title">Reset Timer</h5>
                    <h6 class="card-subtitle mb-2 text-muted">box</h6>
                    <p class="card-text">Resets all timer.</p>
                    <button type="button" class="btn btn-dark"  onclick="sendResetTimer()">Reset</button>
                  </div>
                </div>
              </div>

              <div class="col-sm-1">
              </div>

              <div class="col-sm-5">
                <div class="card">
                  <div class="card-body">
                    <h5 class="card-title">Delete Timer</h5>
                    <h6 class="card-subtitle mb-2 text-muted">box</h6>
                    <p class="card-text">Deletes all timer.</p>
                    <button type="button" class="btn btn-dark" onclick="sendDeleteTimer()">Delete</button>
                  </div>
                </div>
              </div>

            </div>

          </div>

          <div class="col-sm-5 boxCards">

            <div class="row borders d-flex justify-content-center" align="center">

              <div class="col-sm-5">
                <div class="card">
                  <div class="card-body">
                    <h5 class="card-title">Drop Pill</h5>
                    <h6 class="card-subtitle mb-2 text-muted">tower</h6>
                    <p class="card-text">Drop one single pill.</p>
                    <button type="button" class="btn btn-dark" onclick="sendSingleDropRequestServer()">Drop</button>
                  </div>
                </div>
              </div>

              <div class="col-sm-1">
              </div>

              <div class="col-sm-5">
                <div class="card">
                  <div class="card-body">
                    <h5 class="card-title">Drop Pill</h5>
                    <h6 class="card-subtitle mb-2 text-muted">tower</h6>
                    <p class="card-text">Drops the specified pill amount.</p>
                    <form>
                      <input class="form-control" id="specifiedDropServer" placeholder="amount">
                    </form>
                    <button type="button" class="btn btn-dark" onclick="sendSpecifiedPillDropServer()">Drop</button>
                  </div>
                </div>
              </div>
            </div>

            <div class="row borders d-flex justify-content-center" align="center">

              <div class="col-sm-5">
                <div class="card">
                  <div class="card-body">
                    <h5 class="card-title">Pill amount</h5>
                    <h6 class="card-subtitle mb-2 text-muted">tower</h6>
                    <p class="card-text">Set a new specified pill amount.</p>
                    <form>
                      <input class="form-control" id="inputFieldPillTower" placeholder="amount">
                    </form>
                    <button type="button" class="btn btn-dark" onclick="sendPillInputRequestServer()">Set</button>
                  </div>
                </div>
              </div>

              <div class="col-sm-1">
              </div>

              <div class="col-sm-5">
                <div class="card">
                  <div class="card-body">
                    <h5 class="card-title">Timer</h5>
                    <h6 class="card-subtitle mb-2 text-muted">tower</h6>
                    <p class="card-text">Set a timer.</p>
                    <input class="form-control" type="number" id="serverHours" placeholder="hours : 00" name="serverHours" min="0" max="23" required>
                    <input class="form-control" type="number" id="serverMinutes" placeholder="minutes : 00" name="serverMinutes" min="0" max="59" required>
                    <input class="form-control" type="number" id="serverSeconds" placeholder="hours : 00" name="serverSeconds" min="0" max="59" required>
                    <input class="form-control" type="number" id="serverAmount" placeholder="amount" name="serverAmount" min="1" required>
                    <button type="button" class="btn btn-dark" onclick="sendServerTimer()">Set</button>
                  </div>
                </div>
              </div>

            </div>

            <div class="row borders d-flex justify-content-center" align="center">

              <div class="col-sm-5">
                <div class="card">
                  <div class="card-body">
                    <h5 class="card-title">Reset Timer</h5>
                    <h6 class="card-subtitle mb-2 text-muted">tower</h6>
                    <p class="card-text">Resets all timer.</p>
                    <button type="button" class="btn btn-dark"  onclick="sendResetTimerServer()">Reset</button>
                  </div>
                </div>
              </div>

              <div class="col-sm-1">
              </div>

              <div class="col-sm-5">
                <div class="card">
                  <div class="card-body">
                    <h5 class="card-title">Delete Timer</h5>
                    <h6 class="card-subtitle mb-2 text-muted">tower</h6>
                    <p class="card-text">Deletes all timer.</p>
                    <button type="button" class="btn btn-dark" onclick="sendDeleteTimerServer()">Delete</button>
                  </div>
                </div>
              </div>

            </div>

          </div>
      </div>
    </div>

    <div class="col-sm-2" id = "notifications">

    </div>

    </div>


    <!-- JavaScript -->

    <script type="text/javascript">

      function sendResetTimer() {

        var x = document.createElement("div");
        x.className = "alert alert-danger alerts";
        x.setAttribute("role", "alert");

        var closeButton = document.createElement("button");
        closeButton.className = "custom-close";
        closeButton.innerHTML = "&times;";
        closeButton.addEventListener("click", function() {
          x.remove();
        });

        var heading = document.createElement("h5");
        heading.textContent = "Reset Timer";

        var text = document.createTextNode("box");

        x.appendChild(closeButton);
        x.appendChild(heading);
        x.appendChild(text);

        setTimeout(function() {
          x.remove();
        }, 3000);

        document.getElementById("notifications").appendChild(x);

        var xhttp = new XMLHttpRequest();
        xhttp.open("GET", "/resetTimer", true);
        xhttp.send();
      }

      <!-- ######################################################################################## -->


      function sendResetTimerServer() {

        var x = document.createElement("div");
        x.className = "alert alert-danger alerts";
        x.setAttribute("role", "alert");

        var closeButton = document.createElement("button");
        closeButton.className = "custom-close";
        closeButton.innerHTML = "&times;";
        closeButton.addEventListener("click", function() {
          x.remove();
        });

        var heading = document.createElement("h5");
        heading.textContent = "Reset Timer";

        var text = document.createTextNode("tower");

        x.appendChild(closeButton);
        x.appendChild(heading);
        x.appendChild(text);

        setTimeout(function() {
          x.remove();
        }, 3000);

        document.getElementById("notifications").appendChild(x);

        var xhttp = new XMLHttpRequest();
        xhttp.open("GET", "/resetTimerServer", true);
        xhttp.send();
      }

      <!-- ######################################################################################## -->


      function sendDeleteTimer() {

        var x = document.createElement("div");
        x.className = "alert alert-danger alerts";
        x.setAttribute("role", "alert");

        var closeButton = document.createElement("button");
        closeButton.className = "custom-close";
        closeButton.innerHTML = "&times;";
        closeButton.addEventListener("click", function() {
          x.remove();
        });

        var heading = document.createElement("h5");
        heading.textContent = "Delete Timer";

        var text = document.createTextNode("box");

        x.appendChild(closeButton);
        x.appendChild(heading);
        x.appendChild(text);

        setTimeout(function() {
          x.remove();
        }, 3000);

        document.getElementById("notifications").appendChild(x);

        var xhttp = new XMLHttpRequest();
        xhttp.open("GET", "/deleteTimer", true);
        xhttp.send();
      }

      <!-- ######################################################################################## -->


      function sendDeleteTimerServer() {

        var x = document.createElement("div");
        x.className = "alert alert-danger alerts";
        x.setAttribute("role", "alert");

        var closeButton = document.createElement("button");
        closeButton.className = "custom-close";
        closeButton.innerHTML = "&times;";
        closeButton.addEventListener("click", function() {
          x.remove();
        });

        var heading = document.createElement("h5");
        heading.textContent = "Delete Timer";

        var text = document.createTextNode("tower");

        x.appendChild(closeButton);
        x.appendChild(heading);
        x.appendChild(text);

        setTimeout(function() {
          x.remove();
        }, 3000);

        document.getElementById("notifications").appendChild(x);

        var xhttp = new XMLHttpRequest();
        xhttp.open("GET", "/deleteTimerServer", true);
        xhttp.send();
      }

      <!-- ######################################################################################## -->


      function sendPillInputRequest() {
        var pillAmountBox = document.getElementById("inputFieldPillBox").value;
        if (isNaN(pillAmountBox)) {
          alert("Invalid input. Please enter a number.");
          return;
        }

        var x = document.createElement("div");
        x.className = "alert alert-primary alerts";
        x.setAttribute("role", "alert");

        var closeButton = document.createElement("button");
        closeButton.className = "custom-close";
        closeButton.innerHTML = "&times;";
        closeButton.addEventListener("click", function() {
          x.remove();
        });

        var heading = document.createElement("h5");
        heading.textContent = "Set pills";

        var text = document.createTextNode("box | new pill count: " + pillAmountBox);

        x.appendChild(closeButton);
        x.appendChild(heading);
        x.appendChild(text);

        setTimeout(function() {
          x.remove();
        }, 3000);

        document.getElementById("notifications").appendChild(x);

        var xhttp = new XMLHttpRequest();
        xhttp.open("GET", "/inputPillAmountBox?input=" + pillAmountBox, true);
        xhttp.send();
      }

      <!-- ######################################################################################## -->


      function sendPillInputRequestServer() {
        var pillAmountServer = document.getElementById("inputFieldPillTower").value;
        if (isNaN(pillAmountServer)) {
          alert("Invalid input. Please enter a number.");
          return;
        }

        var x = document.createElement("div");
        x.className = "alert alert-primary alerts";
        x.setAttribute("role", "alert");

        var closeButton = document.createElement("button");
        closeButton.className = "custom-close";
        closeButton.innerHTML = "&times;";
        closeButton.addEventListener("click", function() {
          x.remove();
        });

        var heading = document.createElement("h5");
        heading.textContent = "Set pills";

        var text = document.createTextNode("tower | new pill count: " + pillAmountServer);

        x.appendChild(closeButton);
        x.appendChild(heading);
        x.appendChild(text);

        setTimeout(function() {
          x.remove();
        }, 3000);

        document.getElementById("notifications").appendChild(x);

        var xhttp = new XMLHttpRequest();
        xhttp.open("GET", "/inputPillAmountServer?input=" + pillAmountServer, true);
        xhttp.send();
      }

      <!-- ######################################################################################## -->


        function sendSingleDropRequest() {
          var xhttp = new XMLHttpRequest();

          var x = document.createElement("div");
          x.className = "alert alert-success alerts";
          x.setAttribute("role", "alert");

          var closeButton = document.createElement("button");
          closeButton.className = "custom-close";
          closeButton.innerHTML = "&times;";
          closeButton.addEventListener("click", function() {
            x.remove();
          });

          var heading = document.createElement("h5");
          heading.textContent = "Requested single pill drop";

          var text = document.createTextNode("box");

          x.appendChild(closeButton);
          x.appendChild(heading);
          x.appendChild(text);

          setTimeout(function() {
            x.remove();
          }, 3000);

          document.getElementById("notifications").appendChild(x);

          xhttp.open("GET", "/singelPillDrop", true);
          xhttp.send();
        }

        <!-- ######################################################################################## -->

        function sendSingleDropRequestServer() {
          var xhttp = new XMLHttpRequest();

          var x = document.createElement("div");
          x.className = "alert alert-success alerts";
          x.setAttribute("role", "alert");

          var closeButton = document.createElement("button");
          closeButton.className = "custom-close";
          closeButton.innerHTML = "&times;";
          closeButton.addEventListener("click", function() {
            x.remove();
          });

          var heading = document.createElement("h5");
          heading.textContent = "Requested single pill drop";

          var text = document.createTextNode("tower");

          x.appendChild(closeButton);
          x.appendChild(heading);
          x.appendChild(text);

          setTimeout(function() {
            x.remove();
          }, 3000);

          document.getElementById("notifications").appendChild(x);

          var xhttp = new XMLHttpRequest();
          xhttp.open("GET", "/singelPillDropServer", true);
          xhttp.send();
        }

        <!-- ######################################################################################## -->


        function sendSpecifiedPillDrop() {
          var specifiedAmount = document.getElementById("specifiedDrop").value;

          if (validateAmount(specifiedAmount)) {

            var xhttp = new XMLHttpRequest();

            var x = document.createElement("div");
            x.className = "alert alert-success alerts";
            x.setAttribute("role", "alert");

            var closeButton = document.createElement("button");
            closeButton.className = "custom-close";
            closeButton.innerHTML = "&times;";
            closeButton.addEventListener("click", function() {
              x.remove();
            });

            var heading = document.createElement("h5");
            heading.textContent = "Requested specified pill drop";

            var text = document.createTextNode("box" + " | to drop: " + specifiedAmount);

            x.appendChild(closeButton);
            x.appendChild(heading);
            x.appendChild(text);

            setTimeout(function() {
              x.remove();
            }, 3000);

            document.getElementById("notifications").appendChild(x);

            xhttp.open("GET", "/sendSpecifiedPillDrop?specifiedAmount=" + specifiedAmount, true);
            xhttp.send();

          }
        }

        <!-- ######################################################################################## -->


        function sendSpecifiedPillDropServer() {
          var specifiedAmount = document.getElementById("specifiedDropServer").value;

          if (validateAmount(specifiedAmount)) {

            var xhttp = new XMLHttpRequest();

            var x = document.createElement("div");
            x.className = "alert alert-success alerts";
            x.setAttribute("role", "alert");

            var closeButton = document.createElement("button");
            closeButton.className = "custom-close";
            closeButton.innerHTML = "&times;";
            closeButton.addEventListener("click", function() {
              x.remove();
            });

            var heading = document.createElement("h5");
            heading.textContent = "Requested specified pill drop";

            var text = document.createTextNode("tower" + " | to drop: " + specifiedAmount);

            x.appendChild(closeButton);
            x.appendChild(heading);
            x.appendChild(text);

            setTimeout(function() {
              x.remove();
            }, 3000);

            document.getElementById("notifications").appendChild(x);

            xhttp.open("GET", "/sendSpecifiedPillDropServer?specifiedAmount=" + specifiedAmount, true);
            xhttp.send();

          }
        }

        <!-- ######################################################################################## -->

        function sendTimer() {
          var hours = document.getElementById("hours").value;
          var minutes = document.getElementById("minutes").value;
          var seconds = document.getElementById("seconds").value;
          var boxAmount = document.getElementById("boxAmount").value;

          if (validateTime(hours, minutes, seconds) && validateAmount(boxAmount)) {
            var x = document.createElement("div");
            x.className = "alert alert-primary alerts";
            x.setAttribute("role", "alert");

            var closeButton = document.createElement("button");
            closeButton.className = "custom-close";
            closeButton.innerHTML = "&times;";
            closeButton.addEventListener("click", function() {
              x.remove();
            });

            var heading = document.createElement("h5");
            heading.textContent = "Box timer added:";

            var text = document.createTextNode(hours + ":" + minutes + ":" + seconds + " | Pills: " + boxAmount);

            x.appendChild(closeButton);
            x.appendChild(heading);
            x.appendChild(text);

            setTimeout(function() {
              x.remove();
            }, 3000);

            document.getElementById("notifications").appendChild(x);
          } else {
            alert("Invalid time entered. Check the time / format (00:00:00). Check if amount is greater than zero.");
          }

          var xhttp = new XMLHttpRequest();
          xhttp.open("GET", "/setTimer?hours=" + hours + "&minutes=" + minutes + "&seconds=" + seconds + "&boxAmount=" + boxAmount, true);
          xhttp.send();
        }

        <!-- ######################################################################################## -->

        function sendServerTimer() {
          var serverHours = document.getElementById("serverHours").value;
          var serverMinutes = document.getElementById("serverMinutes").value;
          var serverSeconds = document.getElementById("serverSeconds").value;
          var serverAmount = document.getElementById("serverAmount").value;

          if (validateTime(serverHours, serverMinutes, serverSeconds) && validateAmount(serverAmount)) {
            var x = document.createElement("div");
            x.className = "alert alert-primary alerts";
            x.setAttribute("role", "alert");

            var closeButton = document.createElement("button");
            closeButton.className = "custom-close";
            closeButton.innerHTML = "&times;";
            closeButton.addEventListener("click", function() {
              x.remove();
            }, 300);

            var heading = document.createElement("h5");
            heading.textContent = "Tower timer added:";

            var text = document.createTextNode(serverHours + ":" + serverMinutes + ":" + serverSeconds + " | Pills: " + serverAmount);

            x.appendChild(closeButton);
            x.appendChild(heading);
            x.appendChild(text);

            setTimeout(function() {
              x.remove();
            }, 3000);

            document.getElementById("notifications").appendChild(x);

          } else {
            alert("Invalid time entered. Check the time / format (00:00:00). Check if amount is greater than zero.");
          }

          var xhttp = new XMLHttpRequest();
          xhttp.open("GET", "/setServerTimer?hours=" + serverHours + "&minutes=" + serverMinutes + "&seconds=" + serverSeconds + "&serverAmount=" + serverAmount, true);
          xhttp.send();
        }

        <!-- ######################################################################################## -->


        function redirectToStatistics() {
          window.location.href = "/statistics";
        }

        <!-- ######################################################################################## -->


        function validateTime(hours, minutes, seconds) {
          if (
            hours !== "" && minutes !== "" && seconds !== "" &&
            hours >= 0 && hours <= 23 && minutes >= 0 && minutes <= 59 && seconds >= 0 && seconds <= 59
          ) {
            const timeRegex = /^([0-1][0-9]|2[0-3]):[0-5][0-9]:[0-5][0-9]$/;
            return timeRegex.test(hours + ":" + minutes + ":" + seconds);
          }
          return false;
        }

        <!-- ######################################################################################## -->

        function validateAmount(amount) {
          return amount > 0;
        }

        <!-- ######################################################################################## -->

        function logout() {
          window.location.href = "/login";
        }
    </script>

    <!-- Bootstrap JavaScript -->
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/js/bootstrap.min.js"></script>
  </body>
</html>
)=====";

//# # # login page # # #

const char LOGIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">

<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>LOGIN</title>
  <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/css/bootstrap.min.css" rel="stylesheet">

  <style media="screen">
    body {
        margin:0;
        padding:0;
        background-color: #ECEEEF;
    }

    .card {
      border-color: white;
      box-shadow: rgba(0, 0, 0, 0.09) 0px 3px 12px;
    }

    .uppercard {
      box-shadow: rgba(0, 0, 0, 0.09) 0px 3px 12px;
    }

    .card-body {
      text-align: center;
    }

    .form-group {
      margin: 5px;
    }

    .btn {
      margin-left: 10px;;
      outline-color: #7895B2;
      transition: transform 0.3s ease;
    }

    .form-control {
      border-color: #80B2C9;
      margin-bottom: 5px;
    }

    .form-control::placeholder {
      color: #BCBEBF;
    }

    .btn:hover {
      transform: scale(1.1);
    }

    .btn:active {
      transform: scale(0.9);
    }

    .custom {
      margin: 5px;
    }
  </style>
</head>

<body data-bs-theme="light">

  <div class="container d-flex align-items-center justify-content-center min-vh-100">
    <div class="row d-flex flex-column">
      <div class="col-md-6 custom">
        <div class="card" style="width: 18rem;">
          <div class="card-body">
            <h5 class="card-title">Authenticate</h5>
            <form class="form-group" action="/login" method="POST">
              <input class="form-control" type="text" id="username" name="username" placeholder="username">
              <input class="form-control" type="password" id="password" name="password" placeholder="password">
              <input class="btn btn-dark" type="submit" value="Login">
            </form>
          </div>
        </div>
      </div>
      <div class="col-md-6 custom">
        <div class="card customCard" style="width: 18rem;">
          <div class="card-body">
            <h5 class="card-title">or continue without as</h5>
            <h6 class="card-subtitle mb-2 text-muted">user / patient</h6>
              <form action="/statistics">
                <input class="btn btn-dark btn-block" type="submit" value="View plan">
              </form>
        </div>
      </div>
    </div>
  </div>

  <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/js/bootstrap.bundle.min.js"></script>
  <script>

  </script>
</body>
</html>
)=====";
