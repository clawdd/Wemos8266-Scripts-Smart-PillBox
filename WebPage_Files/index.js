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


    function redirectToStatistics() {
      window.location.href = "/statistics";
    }


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

    function validateAmount(amount) {
      return amount > 0;
    }

    function logout() {
      window.location.href = "/login";
    }