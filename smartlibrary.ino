#include <WiFi.h>
#include <WebServer.h>

// =====================================================
// SMART LIBRARY - ESP32
// =====================================================

// Wi-Fi Access Point
const char* ssid = "Smart Library";
const char* password = "12345678";

WebServer server(80);

// -----------------------------------------------------
// LED GPIO PINS
// -----------------------------------------------------

const int shelfLEDs[6] = {
  13, // Shelf 1
  12, // Shelf 2
  14, // Shelf 3
  27, // Shelf 4
  26, // Shelf 5
  25 // Shelf 6
};

// -----------------------------------------------------
// BOOK DATABASE
// 20 books total
// 6 available books are mapped to shelves
// -----------------------------------------------------

struct Book {
  String title;
  String author;
  bool available;
  int shelf;
};

Book books[20] = {

  {"The Alchemist", "Paulo Coelho", true, 1},
  {"Wings of Fire", "A.P.J. Abdul Kalam", true, 2},
  {"Atomic Habits", "James Clear", true, 3},
  {"Rich Dad Poor Dad", "Robert Kiyosaki", true, 4},
  {"The Power of Now", "Eckhart Tolle", true, 5},
  {"Think and Grow Rich", "Napoleon Hill", true, 6},

  {"Ikigai", "Hector Garcia", false, 0},
  {"1984", "George Orwell", false, 0},
  {"The Hobbit", "J.R.R. Tolkien", false, 0},
  {"Harry Potter", "J.K. Rowling", false, 0},
  {"The Psychology of Money", "Morgan Housel", false, 0},
  {"Deep Work", "Cal Newport", false, 0},
  {"Atomic Thinking", "Various", false, 0},
  {"The 7 Habits", "Stephen Covey", false, 0},
  {"Steve Jobs", "Walter Isaacson", false, 0},
  {"Zero to One", "Peter Thiel", false, 0},
  {"The Intelligent Investor", "Benjamin Graham", false, 0},
  {"Sapiens", "Yuval Noah Harari", false, 0},
  {"The Lean Startup", "Eric Ries", false, 0},
  {"Digital Electronics", "Morris Mano", false, 0}
};

// -----------------------------------------------------
// TIMER VARIABLES
// -----------------------------------------------------

unsigned long ledStartTime = 0;
unsigned long lastActivityTime = 0;

const unsigned long LED_TIMEOUT = 10000; // 10 seconds
const unsigned long IDLE_TIMEOUT = 120000; // 2 minutes

int activeShelf = -1;

// -----------------------------------------------------
// TURN OFF ALL LEDs
// -----------------------------------------------------

void turnOffLEDs() {

  for (int i = 0; i < 6; i++) {
    digitalWrite(shelfLEDs[i], LOW);
  }

  activeShelf = -1;
}

// -----------------------------------------------------
// ACTIVATE SHELF LED
// -----------------------------------------------------

void locateBook(int shelf) {

  turnOffLEDs();

  if (shelf >= 1 && shelf <= 6) {

    activeShelf = shelf - 1;

    digitalWrite(shelfLEDs[activeShelf], HIGH);

    ledStartTime = millis();
    lastActivityTime = millis();

    Serial.print("Book located at Shelf ");
    Serial.println(shelf);
  }
}

// -----------------------------------------------------
// HOME PAGE
// -----------------------------------------------------

void handleHome() {

  String html = R"rawliteral(

<!DOCTYPE html>
<html>

<head>

<meta name="viewport" content="width=device-width, initial-scale=1">

<title>Smart Library</title>

<style>

body {
  font-family: Arial;
  background: #f2f4f7;
  margin: 0;
  padding: 20px;
}

.container {
  max-width: 900px;
  margin: auto;
}

h1 {
  text-align: center;
  color: #222;
}

.subtitle {
  text-align: center;
  color: #666;
}

.search {
  width: 100%;
  padding: 14px;
  margin: 20px 0;
  box-sizing: border-box;
  border: 1px solid #ccc;
  border-radius: 8px;
  font-size: 16px;
}

.book {
  background: white;
  padding: 18px;
  margin: 12px 0;
  border-radius: 10px;
  box-shadow: 0 2px 6px rgba(0,0,0,0.1);
}

.title {
  font-size: 19px;
  font-weight: bold;
}

.author {
  color: #666;
  margin-top: 5px;
}

.available {
  color: green;
  font-weight: bold;
}

.unavailable {
  color: red;
  font-weight: bold;
}

button {
  padding: 10px 18px;
  border: none;
  border-radius: 6px;
  background: #1976d2;
  color: white;
  cursor: pointer;
  margin-top: 10px;
}

button:hover {
  background: #125ca1;
}

</style>

</head>

<body>

<div class="container">

<h1>📚 Smart Library</h1>

<p class="subtitle">
Find your book quickly
</p>

<input
  type="text"
  id="search"
  class="search"
  placeholder="Search book or author..."
  onkeyup="searchBooks()"
>

<div id="books">

)rawliteral";

  // Generate book cards
  for (int i = 0; i < 20; i++) {

    html += "<div class='book'>";

    html += "<div class='title'>";
    html += books[i].title;
    html += "</div>";

    html += "<div class='author'>";
    html += "Author: ";
    html += books[i].author;
    html += "</div>";

    if (books[i].available) {

      html += "<p class='available'>Available</p>";

      html += "<button onclick='locateBook(";
      html += String(books[i].shelf);
      html += ")'>Locate Book</button>";

    } else {

      html += "<p class='unavailable'>Currently Unavailable</p>";

    }

    html += "</div>";
  }

  html += R"rawliteral(

</div>

</div>

<script>

function locateBook(shelf) {

  fetch('/locate?shelf=' + shelf)
  .then(response => response.text())
  .then(data => {

    alert(data);

  });

}

function searchBooks() {

  let input =
    document.getElementById("search")
    .value
    .toLowerCase();

  let books =
    document.getElementsByClassName("book");

  for (let i = 0; i < books.length; i++) {

    let text =
      books[i].innerText.toLowerCase();

    if (text.includes(input)) {
      books[i].style.display = "block";
    }
    else {
      books[i].style.display = "none";
    }

  }

}

</script>

</body>

</html>

)rawliteral";

  server.send(200, "text/html", html);

  lastActivityTime = millis();
}

// -----------------------------------------------------
// LOCATE BOOK
// -----------------------------------------------------

void handleLocate() {

  if (!server.hasArg("shelf")) {

    server.send(
      400,
      "text/plain",
      "Shelf number missing"
    );

    return;
  }

  int shelf =
    server.arg("shelf").toInt();

  if (shelf >= 1 && shelf <= 6) {

    locateBook(shelf);

    String message =
      "Book found! Check Shelf " +
      String(shelf);

    server.send(
      200,
      "text/plain",
      message
    );

  } else {

    server.send(
      400,
      "text/plain",
      "Invalid shelf"
    );
  }
}

// -----------------------------------------------------
// SETUP
// -----------------------------------------------------

void setup() {

  Serial.begin(115200);

  // Configure LEDs
  for (int i = 0; i < 6; i++) {

    pinMode(
      shelfLEDs[i],
      OUTPUT
    );

    digitalWrite(
      shelfLEDs[i],
      LOW
    );
  }

  // Start ESP32 Access Point
  WiFi.mode(WIFI_AP);

  WiFi.softAP(
    ssid,
    password
  );

  IPAddress IP =
    WiFi.softAPIP();

  Serial.println();
  Serial.println("==============================");
  Serial.println(" SMART LIBRARY");
  Serial.println("==============================");

  Serial.print("Wi-Fi Name: ");
  Serial.println(ssid);

  Serial.print("IP Address: ");
  Serial.println(IP);

  Serial.println("==============================");

  // Web server routes
  serve.on(
    "/",
    handleHome
  );

  server.on(
    "/locate",
    handleLocate
  );

  server.begin();

  lastActivityTime = millis();

  Serial.println(
    "Web server started!"
  );
}

// -----------------------------------------------------
// LOOP
// -----------------------------------------------------

void loop() {

  server.handleClient();

  // Turn off LED after 10 seconds
  if (
    activeShelf != -1 &&
    millis() - ledStartTime >= LED_TIMEOUT
  ) {

    digitalWrite(
      shelfLEDs[activeShelf],
      LOW
    );

    activeShelf = -1;

    Serial.println(
      "Shelf LED automatically turned OFF."
    );
  }

  // Reset after 2 minutes of inactivity
  if (
    millis() - lastActivityTime >= IDLE_TIMEOUT
  ) {

    turnOffLEDs();

    lastActivityTime = millis();

    Serial.println(
      "System returned to idle state."
    );
  }
}
