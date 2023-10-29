/**
 * @file /example1/main.cpp
 * @author Philippe Lucidarme
 * @date December 2019
 * @brief File containing example of serial port communication
 *
 * This example send the ASCII table through the serial device
 *
 * @see https://lucidar.me
 */


// Serial library
#include "serialib.h"
#include <unistd.h>
#include <stdio.h>
#include <random>


#if defined (_WIN32) || defined(_WIN64)
    //for serial ports above "COM9", we must use this extended syntax of "\\.\COMx".
    //also works for COM0 to COM9.
    //https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilea?redirectedfrom=MSDN#communications-resources
    #define SERIAL_PORT "\\\\.\\COM1"
#endif
#if defined (__linux__) || defined(__APPLE__)
    #define SERIAL_PORT "/dev/ttyACM0"
#endif

#if defined (_WIN32) || defined(_WIN64)
    //for serial ports above "COM9", we must use this extended syntax of "\\.\COMx".
    //also works for COM0 to COM9.
    //https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilea?redirectedfrom=MSDN#communications-resources
    #define SERIAL_PORT "\\\\.\\COM1"
#endif
#if defined (__linux__) || defined(__APPLE__)
    #define SERIAL_PORT "/dev/ttyACM0"
#endif

/*!
 * \brief main  Example of read and write string
  */
int main( /*int argc, char *argv[]*/)
{
    // Serial object
    serialib serial;

    // Connection to serial port
    char errorOpening = serial.openDevice(SERIAL_PORT, 115200);


    // If connection fails, return the error code otherwise, display a success message
    if (errorOpening!=1) return errorOpening;
    printf ("Successful connection to %s\n",SERIAL_PORT);

    char buffer[15];
    while(1){
        // Create the string
        // char buffer[15] = "1";

        // // Write the string on the serial device
        // serial.writeString(buffer);
        // printf ("String sent: %s\n", buffer);
        // sleep(1);

        // char buffer1[15] = "2";

        // // Write the string on the serial device
        // serial.writeString(buffer1);
        // printf ("String sent: %s\n", buffer1);
        // sleep(1);

        for (int i = 1; i <= 4; i++) {
            snprintf(buffer, sizeof(buffer), "%d", i);
            serial.writeString(buffer);
            // Write the string on the serial device
            // Thay đổi serial.writeString(buffer) thành hàm gửi dữ liệu điều khiển Serial của bạn
            printf("String sent: %s\n", buffer);
            sleep(1);
        }
    }
    

    // Close the serial device
    serial.closeDevice();

    return 0 ;
}