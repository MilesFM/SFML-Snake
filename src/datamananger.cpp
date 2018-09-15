#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "datamanager.h"

static std::string dataFileName = "data.txt";
static std::ifstream dataFileIn;
static std::ofstream dataFileOut;

void CreateDataFile()
{
    dataFileIn.open(dataFileName);
    if (!dataFileIn.good()) // If the file does not exist
    {
        dataFileOut.open(dataFileName);
        dataFileOut << "0";
    }
    dataFileIn.close();
    dataFileOut.close();
}

std::string GetHighScore()
{
    dataFileIn.open(dataFileName);
    std::string line;
    std::getline(dataFileIn, line); // Gets the first line

    dataFileIn.close();
    return line; // Return first line
}

void SetHighScore(int highScore)
{
    dataFileOut.open(dataFileName, std::ios::trunc);
    dataFileOut << std::to_string(highScore);
    dataFileOut.close();
}

// Not very secure but oh well
std::string GetRecordScore() // Stored on website
{
    sf::Http::Request request("/games/getrecordlength.php", sf::Http::Request::Post);
    sf::Http http("http://milesfm.000webhostapp.com/");
    sf::Http::Response response = http.sendRequest(request);

    if (response.getStatus() == sf::Http::Response::Ok)
    {
        return response.getBody();
    }
    else
    {
        return "Webserver offline";
    }
}

void SetRecordScore(int highScore) // Stored on website
{
    sf::Http::Request request("/games/setrecordlength.php", sf::Http::Request::Post);

    // Encode the parameters in the request body
    std::ostringstream stream;
    stream << "newrecordlength=" << std::to_string(highScore);
    request.setBody(stream.str());

    sf::Http http("http://milesfm.000webhostapp.com/");
    http.sendRequest(request);
}

/*

NOT WORKING
WILL FIX LATER

std::string CopyFile(std::string fileToCopyFrom, std::string fileToCopyTo)
{
    std::ifstream copyFrom(fileToCopyFrom);
    std::ofstream copyTo(fileToCopyTo);

    if (!copyFrom || !copyTo)
    {
        exit(1);
    }

    std::string strTemp;
    while(copyFrom >> strTemp)
        copyTo << strTemp;

    return fileToCopyTo;
}

void CreateDataFile()
{
    dataFileIn.open(dataFileName);
    if (!dataFileIn.good()) // If the file does not exist
    {
        dataFileOut.open(dataFileName);
        dataFileOut << "highscore:" << std::endl;
        dataFileOut << "0";
    }
    dataFileIn.close();
    dataFileOut.close();
}

std::string GetHighScore()
{
    dataFileIn.open(dataFileName);
    std::string line;
    while (std::getline(dataFileIn, line))
    {
        if (line == "highscore:")
        {
            std::getline(dataFileIn, line); // Reads next line which is the score
            break;
        }
    }
    std::cout << line << std::endl;

    dataFileIn.close();
    return line; // Return first line
}

void SetHighScore(int highScore)
{
    std::string tempFileName = CopyFile(dataFileName, "tempFile.txt");
    dataFileIn.open(tempFileName, std::ios::trunc);
    dataFileOut.open(dataFileName, std::ios::trunc);

    // Choses the line to get the high score
    std::string strTemp;
    while(dataFileIn >> strTemp)
    {
        if (strTemp == "highscore:")
        {
            dataFileIn >> strTemp; // Goes to next line
            strTemp = std::to_string(highScore);
        }
        strTemp += "\n";
        dataFileOut << strTemp;
    }
    dataFileIn.close();
    dataFileOut.close();
}
*/
