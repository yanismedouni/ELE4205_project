# USB Camera-Based Vision Project

This project, carried out as part of the **ELE4205 - Operating Systems and Hardware Interfaces** course, involves developing a system based on a USB camera connected to an Odroid-C2. It combines concepts of image processing, client/server communication via TCP/IP, and hardware integration. The whole project was made with a lab partner.

## Main Features

1. **Video Capture**: Record 5-second videos in different formats and resolutions.
2. **TCP Client/Server**: Transfer images from the Odroid-C2 to the workstation for display.
3. **Resolution Switching**: Allow dynamic selection from several resolutions.
4. **Hardware Integration**: Use a photosensitive resistor and a button to add features.
5. **QR Code Detection**: Analyze and annotate images containing QR codes.
6. **Morse Transmission**: Decode the content of QR codes and transmit them in Morse code.

---

## Deliverables

1. **Deliverable 1**: Video capture and saving as `.avi` file.
2. **Deliverable 2**: Image transmission via a TCP/IP connection.
3. **Deliverable 3**: Dynamic resolution management via an interactive menu.
4. **Deliverable 4**: Sensor readings (light and button) to modify server behavior.
5. **Deliverable 5**: QR code decoding and annotation on images.
6. **Deliverable 6**: Transmission and interpretation of QR data in Morse code.

---

## Compilation and Execution

### Prerequisites

- **OpenCV 3.1.0** installed on the Odroid-C2.
- **ZBAR** installed on the Odroid-C2.
- **Docker** to configure the environment.
- **CMake** for build management.

### Compilation Instructions

1. **Clone the project**:
   ```bash
   git clone <repository_url>
   cd gX-vlsi4YY-odroid
2. Configure with CMake:
   ```bash
   mkdir build && cd build
   cmake ..
   make
3. Run the program on the Odroid-C2:
   ```bash
   ./build/Project

4. Run the program on the workstation:
   ```bash
   ./build/Client






