# LabWork 1
## Author
Чигиренко Егор Дмитриевич, группа: 24.Б81-мм
## Contacts
st128240@student.spbu.ru
## Description
Labwork 1 - the BMP image processing tool with multi-threaded operations. There are 3 options:  
 1. Processing a pre-selected file "1.bmp": (make --> ./run)  
 2. Processing your own file (or one from "Images") using redactor: (make redactor --> ./start)  
 3. Processing 10 tests with custom "test.bmp": (make test --> ./test)  
## Redactor operations:
 1. Rotating clockwise by 90°  
 2. Rotating counterclockwise by 90°  
 3. Putting gaussan filter on image  
⠀  
Addition 1: after starting the programm:  
 1.Write down the full name of the file  
 2.Use one of three options above  
 3.Save image  
⠀  
Addition 2: you can repeat steps if you want
## Build
make  
make redactor  
make test
## Run
./run  
./start  
./test
## Clean
make clean  
make cleanall
