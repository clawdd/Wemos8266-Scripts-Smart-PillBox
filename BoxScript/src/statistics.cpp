#include <Arduino.h>
#include <statistics.h>
#include <vector>
#include <parse_utils.h>
#include <time_utils.h>

String getStatus(int pills) {

    if (pills > 0) {
        return "NOT EMPTY";
    }
    return "EMPTY";
}

String getAllTimer(std::vector<String>& timeVector, std::vector<int>& amountToDrop) {

    String div = "";

    for (size_t i = 0; i < timeVector.size(); i++)
    {
        
        div += "<div class=\"card card-block mx-2\" style=\"min-width: 300px;\">";
        div += "<div class=\"card-body text-left\">";
        div += "<h5>Timer at: " + timeVector[i] + "</h5>";
        div += "<h6 class=\"card-subtitle mb-2 text-body-secondary\">box</h6>";
        div += "<p>pills to drop: " + (String) amountToDrop[i] + "</p>";
        div += "</div>";
        div += "</div>";

    }
    return div;
}

String getAllTimerTower(std::vector<String>& timeVector, std::vector<int>& amountToDrop) {

    String div = "";

    for (size_t i = 0; i < timeVector.size(); i++)
    {
        
        div += "<div class=\"card card-block mx-2\" style=\"min-width: 300px;\">";
        div += "<div class=\"card-body text-left\">";
        div += "<h5>Timer at: " + timeVector[i] + "</h5>";
        div += "<h6 class=\"card-subtitle mb-2 text-body-secondary\">tower</h6>";
        div += "<p>pills to drop: " + (String) amountToDrop[i] + "</p>";
        div += "</div>";
        div += "</div>";

    }
    return div;
}

String getStatisticsPage(int currentPills, int pillPer, int currentPillsTower, int pillPerTower, int totalDropped, int totalDroppedTower,
                         std::vector<String>& timeVector, std::vector<int>& checkTimers, std::vector<int>& amountToDrop,
                         std::vector<String>& timeVectorTower, std::vector<int>& checkTimersTower, std::vector<int>& amountToDropTower, String currentTimer) {
                        
    String currentPillsString = (String) currentPills;
    String pillPerString = (String) pillPer;
    String currentPillsTowerString = (String) currentPillsTower;
    String pillPerTowerString = (String) pillPerTower;
    String totalDroppedString = (String) totalDropped;
    String totalDroppedTowerString = (String) totalDroppedTower;

    int pillsDropped = pillPer - currentPills;
    int pillsDroppedTower = pillPerTower - currentPillsTower;

    String pillsDroppedString = (String) pillsDropped;
    String pillsDroppedTowerString = (String) pillsDroppedTower;

    String statistics_page;

    String boxStatus = getStatus(currentPills);
    String towerStatus = getStatus(currentPillsTower);

    String timerDivString = getAllTimer(timeVector, amountToDrop);
    String timerDivStringTower = getAllTimerTower(timeVectorTower, amountToDropTower);

    statistics_page += "<!DOCTYPE html>";
    statistics_page += "<html lang=\"en\" dir=\"ltr\">";
    statistics_page += "<head>";
    statistics_page += "<meta charset=\"utf-8\">";
    statistics_page += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
    statistics_page += "<title>STATISTICS</title>";
    statistics_page += "<script src=\"https://cdn.jsdelivr.net/npm/chart.js@3.5.0\"></script>";
    statistics_page += "<link href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/css/bootstrap.min.css\" rel=\"stylesheet\">";
    statistics_page += "<style media=\"screen\">";
    statistics_page += "body {";
    statistics_page += "margin:0;";
    statistics_page += "padding:0;";
    statistics_page += "background-color: #ECEEEF;";
    statistics_page += "}";
    statistics_page += ".navbar{";
    statistics_page += "margin-left: 10px;";
    statistics_page += "margin-top: 10px;";
    statistics_page += "border-top-left-radius: 10px;";
    statistics_page += "border-bottom-left-radius: 10px;";
    statistics_page += "}";
    statistics_page += ".header {";
    statistics_page += "background-color: #92A9BD;";
    statistics_page += "box-shadow: rgba(0, 0, 0, 0.4) 0px 2px 4px, rgba(0, 0, 0, 0.3) 0px 7px 13px -3px, rgba(0, 0, 0, 0.2) 0px -3px 0px inset;";
    statistics_page += "}";
    statistics_page += ".boxCards {";
    statistics_page += "background-color: white;";
    statistics_page += "border-radius: 10px;";
    statistics_page += "margin: 10px;";
    statistics_page += "}";
    statistics_page += ".card {";
    statistics_page += "border-color: white;";
    statistics_page += "box-shadow: rgba(0, 0, 0, 0.15) 0px 3px 3px 0px;";
    statistics_page += "margin: 10px;";
    statistics_page += "}";
    statistics_page += "</style>";
    statistics_page += "</head>";

    statistics_page += "<body>";

    statistics_page += "<div class=\"row\">";
    statistics_page += "<div class=\"col-sm-12\">";
    statistics_page += "<nav class=\"navbar header\">";
    statistics_page += "<form class=\"form-inline\">";
    statistics_page += "<button type=\"button\" class=\"btn\" onclick=\"redirectToControls()\">Controlles</button>";
    statistics_page += "<button type=\"button\" class=\"btn\">Info</button>";
    statistics_page += "<button type=\"button\" class=\"btn\" onclick=\"logout()\">Logout</button>";
    statistics_page += "</form>";
    statistics_page += "</nav>";
    statistics_page += "</div>";
    statistics_page += "</div>";
    statistics_page += "<div class=\"container text-center\">";
    statistics_page += "<div class=\"row align-items-start\">";
    statistics_page += "<div class=\"col border boxCards\">";
    statistics_page += "<h6>Box Information</h6>";
    statistics_page += "</div>";
    statistics_page += "<div class=\"col border boxCards\">";
    statistics_page += "<h6>Tower Information</h6>";
    statistics_page += "</div>";
    statistics_page += "</div>";
    statistics_page += "</div>";
    statistics_page += "<div class=\"container text-center\">";
    statistics_page += "<div class=\"row align-items-start\">";
    statistics_page += "<div class=\"col border boxCards\">";
    statistics_page += "<div class=\"card\">";
    statistics_page += "<div class=\"card-body text-left\">";
    statistics_page += "<h5 class=\"card-title\">Pills: <span style=\"color: gray;\">" + currentPillsString + "</span>/<span style=\"color: gray;\">" + pillPerString + "</span></h5>";
    statistics_page += "</div>";
    statistics_page += "</div>";
    statistics_page += "<div class=\"card\">";
    statistics_page += "<div class=\"card-body text-left\">";
    statistics_page += "<h5 class=\"card-title\">Total Dropped: <span style=\"color: gray;\"> " + totalDroppedString + " </span></h5>";
    statistics_page += "</div>";
    statistics_page += "</div>";
    statistics_page += "<div class=\"card\">";
    statistics_page += "<div class=\"card-body text-left\">";
    statistics_page += "<h5 class=\"card-title\">Pill status: <span style=\"color: gray;\">" + boxStatus + "</span></h5>";
    statistics_page += "</div>";
    statistics_page += "</div>";
    statistics_page += "<div class=\"container text-center\">";
    statistics_page += "<div class=\"row align-items-start\">";
    statistics_page += "<div class=\"col border boxCards\">";
    statistics_page += "<canvas id=\"pieChart\"></canvas>";
    statistics_page += "</div>";
    statistics_page += "</div>";
    statistics_page += "</div>";
    statistics_page += "<div class=\"card\">";
    statistics_page += "<div class=\"card-body text-left\">";
    statistics_page += "<h5 class=\"card-title\">Next timer: <span style=\"color: gray;\"> " + getSmallestNextTimer(timeVector, checkTimers, currentTimer)  + "</span></h5>";
    statistics_page += "</div>";
    statistics_page += "</div>";
    statistics_page += "</div>";
    statistics_page += "<div class=\"col border boxCards\">";
    statistics_page += "<div class=\"card\">";
    statistics_page += "<div class=\"card-body text-left\">";
    statistics_page += "<h5 class=\"card-title\">Pills: <span style=\"color: gray;\">" + currentPillsTowerString + "</span>/<span style=\"color: gray;\">" + pillPerTowerString + "</span></h5>";
    statistics_page += "</div>";
    statistics_page += "</div>";
    statistics_page += "<div class=\"card\">";
    statistics_page += "<div class=\"card-body text-left\">";
    statistics_page += "<h5 class=\"card-title\">Total Dropped: <span style=\"color: gray;\">" + totalDroppedTowerString + "</span></h5>";
    statistics_page += "</div>";
    statistics_page += "</div>";
    statistics_page += "<div class=\"card\">";
    statistics_page += "<div class=\"card-body text-left\">";
    statistics_page += "<h5 class=\"card-title\">Pill status: <span style=\"color: gray;\">" + towerStatus + "</span></h5>";
    statistics_page += "</div>";
    statistics_page += "</div>";
    statistics_page += "<div class=\"container text-center\">";
    statistics_page += "<div class=\"row align-items-start\">";
    statistics_page += "<div class=\"col border boxCards\">";
    statistics_page += "<canvas id=\"pieChart2\"></canvas>";
    statistics_page += "</div>";
    statistics_page += "</div>";
    statistics_page += "</div>";
    statistics_page += "<div class=\"card\">";
    statistics_page += "<div class=\"card-body text-left\">";
    statistics_page += "<h5 class=\"card-title\">Next timer: <span style=\"color: gray;\">" + getSmallestNextTimer(timeVectorTower, checkTimersTower, currentTimer) + "</span></h5>";
    statistics_page += "</div>";
    statistics_page += "</div>";
    statistics_page += "</div>";
    statistics_page += "</div>";
    statistics_page += "</div>";
    statistics_page += "<div class=\"d-flex flex-row flex-nowrap overflow-auto box boxCards\">";
    statistics_page += timerDivString;
    statistics_page += "</div>";
    statistics_page += "<div class=\"d-flex flex-row flex-nowrap overflow-auto box boxCards\">";
    statistics_page += timerDivStringTower;
    statistics_page += "</div>";

    statistics_page += "<script>";
    statistics_page += "const data1 = {";
    statistics_page += "labels: ['Dropped Pills', 'Remaining Pills'],";
    statistics_page += "datasets: [{";
    statistics_page += "data: [" + pillsDroppedString + ",  " + currentPillsString +"],";
    statistics_page += "backgroundColor: ['#FF6384', '#92A9BD'],";
    statistics_page += "}]";
    statistics_page += "};";
    statistics_page += "const pieChartCanvas = document.getElementById('pieChart');";
    statistics_page += "new Chart(pieChartCanvas, {";
    statistics_page += "type: 'pie',";
    statistics_page += "data: data1,";
    statistics_page += "options: {";
    statistics_page += "responsive: true,";
    statistics_page += "maintainAspectRatio: false,";
    statistics_page += "}";
    statistics_page += "});";
    statistics_page += "const data2 = {";
    statistics_page += "labels: ['Dropped Pills', 'Remaining Pills'],";
    statistics_page += "datasets: [{";
    statistics_page += "data: [" + pillsDroppedTowerString + ",  " + currentPillsTowerString +"],";
    statistics_page += "backgroundColor: ['#FF6384', '#92A9BD'],";
    statistics_page += "}]";
    statistics_page += "};";
    statistics_page += "const pieChart2Canvas = document.getElementById('pieChart2');";
    statistics_page += "new Chart(pieChart2Canvas, {";
    statistics_page += "type: 'pie',";
    statistics_page += "data: data2,";
    statistics_page += "options: {";
    statistics_page += "responsive: true,";
    statistics_page += "maintainAspectRatio: false,";
    statistics_page += "}";
    statistics_page += "});";

    statistics_page += "function redirectToControls() {";
    statistics_page += "window.location.href = \"/\"";
    statistics_page += "}";

    statistics_page += "function logout() {";
    statistics_page += "window.location.href = \"login\"";
    statistics_page += "}";

    statistics_page += "</script>";

    statistics_page += "<script src=\"https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/js/bootstrap.bundle.min.js\"></script>";
    statistics_page += "</body>";
    statistics_page += "</html>";

    return statistics_page;
}
