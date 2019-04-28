#include <iostream>
#include <string>
#include <fstream>


int main()
{
    //Monitor teraterm.log
    std::ifstream ifs("teraterm.log");
    if (ifs.is_open())
    {
        std::string line;
        while (true)
        {
            //Get line if possible
            bool header_removed = false;
            if (std::getline(ifs,line)) {
                //Remove old data file and make a new one
                remove( "data.txt" );
                std::ofstream ofs("data.txt", ios::app);
                // if (line == "***** Booting Zephyr OS zephyr-v1.14.0-117-g83de530d5a36 *****") {
                    // std::cout << "header\n";
                // }
                if (line != "\n" && line != "" && line != "***** Booting Zephyr OS zephyr-v1.14.0-117-g83de530d5a36 *****") {
                    std::cout << line << "\n";
                    ofs << line << "\n";
                }
                //Repeat for the rest of the lines
                while (std::getline(ifs, line)) {
                    if (line != "\n" && line != "") {
                    std::cout << line << "\n";
                    ofs << line << "\n";
                    }
                }
                //System to go function (if needed)
                //std::system("go run ../GO_blockchain/main.go");
                std::cout << "Done\n"; 
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