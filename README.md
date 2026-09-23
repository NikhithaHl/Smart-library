
📚 Smart Library

📌 Project Overview

In a traditional library, users may know the name of a book but still spend considerable time searching for it on physical shelves.

The Smart Library solves this problem by connecting a digital book-search interface with physical shelf LEDs.

When the user selects an available book and presses Locate Book, the ESP32 activates the LED corresponding to the shelf where the book is located.

This provides a simple and low-cost method for guiding users to the required book.

---

🎯 Objectives

- To develop an IoT-based smart library system.
- To reduce the time required to locate physical books.
- To provide a low-cost alternative to complex RFID-based systems.
- To use visual indicators for identifying book locations.
- To improve user convenience and library efficiency.
- To develop a simple, scalable and easy-to-maintain system.

---

⚙️ Hardware Requirements

- ESP32 Development Board
- LEDs × 6
- Resistors for LEDs
- Connecting wires
- Breadboard
- USB cable
- Smartphone/Laptop for accessing the web interface

---

💻 Software Requirements

- Arduino IDE
- ESP32 Board Package
- HTML/CSS/JavaScript
- Web browser

---

🔌 ESP32 Pin Configuration

Shelf| ESP32 GPIO| Output
Shelf 1| GPIO 13| LED 1
Shelf 2| GPIO 12| LED 2
Shelf 3| GPIO 14| LED 3
Shelf 4| GPIO 27| LED 4
Shelf 5| GPIO 26| LED 5
Shelf 6| GPIO 25| LED 6

---

🌐 Wi-Fi Configuration

The ESP32 operates as a Wi-Fi Access Point, so an external internet connection is not required.

Wi-Fi SSID:

Smart Library

Password:

12345678

ESP32 Web Server IP:

192.168.4.1

Connect your phone or laptop to the Smart Library Wi-Fi network and open "192.168.4.1" in a browser.

---

🔄 Working Principle

User
  ↓
Smart Library Web Interface
  ↓
Select Book
  ↓
HTTP Request
  ↓
ESP32 Web Server
  ↓
Identify Shelf
  ↓
Corresponding GPIO
  ↓
Shelf LED
  ↓
User Finds Book

---

📖 Book Database

The prototype contains a database of 20 books.

Six available books are mapped to six physical shelves:

Book| Shelf
The Alchemist| 1
Wings of Fire| 2
Atomic Habits| 3
Rich Dad Poor Dad| 4
The Power of Now| 5
Think and Grow Rich| 6

The remaining books are displayed as currently unavailable in the prototype database.

---

💡 LED Operation

When a user selects a book:

1. The browser sends a request to the ESP32.
2. ESP32 identifies the shelf number.
3. The corresponding GPIO is activated.
4. The shelf LED turns ON.
5. The LED automatically turns OFF after 10 seconds.

The system also includes an idle timeout of 2 minutes.

---

🖥️ Web Interface Features

- Smart Library home page
- Searchable book database
- Book title and author
- Availability status
- Locate Book button
- Physical shelf LED indication
- Offline operation through ESP32 Access Point

---

🚀 How to Run

Step 1 – Install Arduino IDE

Install Arduino IDE and configure the ESP32 board package.

Step 2 – Connect ESP32

Connect the ESP32 to your computer using a USB cable.

Step 3 – Upload Code

Open:

Smart_Library.ino

Select the appropriate ESP32 board and COM port, then upload the program.

Step 4 – Connect to Wi-Fi

From your smartphone or laptop, connect to:

Smart Library

Password:

12345678

Step 5 – Open Dashboard

Open a browser and enter:

192.168.4.1

Step 6 – Locate a Book

Search for a book and press:

Locate Book

The LED on the corresponding shelf will turn ON.

---

🌱 Sustainable Development Goals

This project is related to:

- SDG 4 – Quality Education
- SDG 9 – Industry, Innovation and Infrastructure
- SDG 8 – Decent Work and Economic Growth

---

🔮 Future Improvements

Possible future developments include:

- RFID-based book identification
- Larger book databases
- Mobile application
- Online database integration
- Automatic book availability updates
- Multiple library sections
- User login system
- Book issue and return tracking
- Cloud-based library management

---

👩‍💻 Project Domain

IoT | Embedded Systems | ESP32 | Web Technology | Library Automation
