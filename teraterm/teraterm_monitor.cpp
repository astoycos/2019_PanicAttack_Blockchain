#include <iostream>
#include <string>
#include <fstream>
// #include <sstream>


int main()
{
    //Monitor teraterm.log
    std::ifstream ifs("teraterm.log");
    if (ifs.is_open())
    {
        std::string line;
        //Set a counter to make a fresh text file with a new name every sample
        int counter = 0;
        while (true)
        {
            //Get line if possible
            bool header_removed = false;

            if (std::getline(ifs,line)) {
                //Make filename to store line of data
                char fileName[100];
                sprintf(fileName, "data%d.txt", counter);
                std::string fN = fileName;

                //Increment counter afterwards
                counter++;

                std::ofstream ofs(fileName, ios::app);

                //Ignore empty lines and header
                if (line != "\n" && line != "" && line != "***** Booting Zephyr OS zephyr-v1.14.0-117-g83de530d5a36 *****") {
                    ofs << line << "\n";
                }
                //If theres a header or empty line, may want to look at any trailing lines that have the data
                while (std::getline(ifs, line)) {
                    if (line != "\n" && line != "") {
                    ofs << line << "\n";
                    }
                }
            }
            // Break when EOF
            if (!ifs.eof()) {
                break;
            } 
            ifs.clear();
            sleep(1);
        }
    }
    return 0;
}