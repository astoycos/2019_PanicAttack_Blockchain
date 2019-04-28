#include <iostream>
#include <string>
#include <fstream>

int main()
{
    std::ifstream ifs("teraterm.log");
    if (ifs.is_open())
    {
        std::string line;
        while (true)
        {
            if (std::getline(ifs,line)) {
                remove( "data.txt" );
                std::ofstream ofs("data.txt", ios::app);
                if (line != "\n" && line != "") {

                    std::cout << line << "\n";
                    ofs << line << "\n";
                }
                while (std::getline(ifs, line)) {
                    if (line != "\n" && line != "") {

                    std::cout << line << "\n";
                    ofs << line << "\n";
                    }
                }
            }
            
            if (!ifs.eof()) {
                break;
            } // Ensure end of read was EOF.
            ifs.clear();
            sleep(5);
            //remove( "data.txt" );
            // You may want a sleep in here to avoid
            // being a CPU hog.
        }
    }

    return 0;
}