    #include <Arduino.h>
    #include <statistics.h>

    String timeEventsDisplayer(const std::vector<String>& timeVector, std::vector<int>& pillsToDrop) {

        String col = "";

        for (size_t i = 0; i < timeVector.size(); i++)
        {
            col += "<div>";
            col += "<p>Timer: " + timeVector[i] + " | Pills: " + pillsToDrop[i] + "</p>";
            col += "</div>";
        }
        
        return col;
    }

    String getStatisticsPage(int pillCount, int pillCountServer, int pillsDropped, const std::vector<String>& timeVector,
                             std::vector<int>& pillsToDrop, const std::vector<String>& timeVectorServer, 
                             std::vector<int>& pillsToDropServer) {

        String statistics_page = "<html>";
        String timeEvents = timeEventsDisplayer(timeVector, pillsToDrop);

        String timeEventsServer = timeEventsDisplayer(timeVectorServer, pillsToDropServer);

        statistics_page += "<head>";
        statistics_page += "<title>Pill Dispenser Statistics</title>";
        statistics_page += "</head>";
        statistics_page += "<body>";
        statistics_page += "<h1>Pill Dispenser Statistics</h1>";

        statistics_page += "<div class=\"pill-count\">";
        statistics_page += "<h2>Current Pill Count Box:</h2>";
        statistics_page += "<p id=\"pillCount\">" + String(pillCount) + "</p>";
        statistics_page += "</div>";

        statistics_page += "<div class=\"pill-count\">";
        statistics_page += "<h2>Current Pill Count Tower:</h2>";
        statistics_page += "<p id=\"pillCount\">" + String(pillCountServer) + "</p>";
        statistics_page += "</div>";

        statistics_page += "<div class=\"pills-dropped\">";
        statistics_page += "<h2>Pills droped today:</h2>";
        statistics_page += "<p id=\"pillCount\">" + String(pillsDropped) + "</p>";
        statistics_page += "</div>";

        statistics_page += "<div class=\"Timer\">";
        statistics_page += "<h2>Your timer:</h2>";
        statistics_page += timeEvents;
        statistics_page += "</div>";

        statistics_page += "<div class=\"TimerServer\">";
        statistics_page += "<h2>Your timer:</h2>";
        statistics_page += timeEventsServer;
        statistics_page += "</div>";

        statistics_page += "<button onclick=\"goToRootPage()\">Go to Root</button>"; // Added button element
        statistics_page += "<script type=\"text/javascript\">";
        statistics_page += "function getCurrentPillCount() {";
        statistics_page += "var xhttp = new XMLHttpRequest();";
        statistics_page += "xhttp.onreadystatechange = function() {";
        statistics_page += "if (xhttp.readyState === 4 && xhttp.status === 200) {";
        statistics_page += "var pillCount = JSON.parse(xhttp.responseText).count;";
        statistics_page += "document.getElementById(\"pillCount\").textContent = pillCount;";
        statistics_page += "}";
        statistics_page += "};";
        statistics_page += "xhttp.open(\"GET\", \"/getPillCount\", true);";
        statistics_page += "xhttp.send();";
        statistics_page += "}";
        statistics_page += "function goToRootPage() {";
        statistics_page += "window.location.href = \"/\";"; // Redirect to root page
        statistics_page += "}";
        statistics_page += "getCurrentPillCount();";
        statistics_page += "</script>";
        statistics_page += "</body>";
        statistics_page += "</html>";

        return statistics_page;
    }