import serial
import pyvjoy

arduino = serial.Serial('COM4', 115200)

# Initialize vJoy device
j = pyvjoy.VJoyDevice(1)  # Initialize virtual joystick (ID 1)

while True:
    try:
        # Read a line from the Arduino
        line = arduino.readline().strip()  # Raw bytes from Arduino
        decoded_line = line.decode('utf-8', 'ignore')  # Decode as UTF-8, ignore invalid bytes
        
        # Print the raw line for debugging (optional)
        print(f"Raw Line: {decoded_line}")
        
        # Expect the format "first_value second_value"
        parts = decoded_line.split()
        if len(parts) != 2:
            print("Error: Incorrect data format!")
            continue
        
        x = float(parts[0])
        y = float(parts[1])
        
        # Normalize the values for vJoy axes (range 0 to 32768)
        joy_y = int((y + 1000) * 32768 / 2000)  # Scale -1000 to 1000 → 0 to 32768
        joy_x = int(32768 - ((x + 1000) * 32768 / 2000))
        
        # Set the vJoy axes and update the device
        j.data.wAxisX = joy_x
        j.data.wAxisY = joy_y
        j.update()  # Push the updates to the virtual joystick
        
        # Print the mapped values for debugging
        print(f"Mapped X: {joy_x}, Y: {joy_y}")
    
    except ValueError:
        print("Error: Could not parse data, check Arduino output!")
    except Exception as e:
        print(f"Unexpected error: {e}")
