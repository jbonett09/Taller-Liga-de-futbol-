#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<string> enteredTeamNames;
vector<int> enteredNumericMatchData;

struct MatchRecord {
    string matchDate;
    string homeTeamName;
    string awayTeamName;
    int homeTeamGoals;
    int awayTeamGoals;
};

struct LeagueTableTeamStats {
    string teamName;
    int matchesPlayed;
    int matchesWon;
    int matchesDrawn;
    int matchesLost;
    int goalsScored;
    int goalsConceded;
    int goalDifference;
    int totalPoints;
};

ofstream editfiles(string file) {
    ofstream outputFile(file.c_str());

    if (!outputFile.is_open()) {
        cout << "Error while opening file\n";
    }

    return outputFile;
}

ofstream appendToFile(string file) {
    ofstream outputFile(file.c_str(), ios::app);

    if (!outputFile.is_open()) {
        cout << "Error while opening file\n";
    }

    return outputFile;
}

ifstream read(string file) {
    ifstream inputFile(file.c_str());

    if (!inputFile.is_open()) {
        cout << "Error opening file\n";
    }

    return inputFile;
}

string removeSpacesFromStartAndEnd(string textToClean) {
    while (!textToClean.empty() &&
          (textToClean[0] == ' ' ||
           textToClean[0] == '\t' ||
           textToClean[0] == '\r' ||
           textToClean[0] == '\n')) {
        textToClean.erase(0, 1);
    }

    while (!textToClean.empty() &&
          (textToClean[textToClean.size() - 1] == ' ' ||
           textToClean[textToClean.size() - 1] == '\t' ||
           textToClean[textToClean.size() - 1] == '\r' ||
           textToClean[textToClean.size() - 1] == '\n')) {
        textToClean.erase(textToClean.size() - 1, 1);
    }

    return textToClean;
}

int convertTextToInteger(string textNumber) {
    stringstream numberConverter;
    int convertedNumber = 0;

    numberConverter << textNumber;
    numberConverter >> convertedNumber;

    return convertedNumber;
}

string convertIntegerToText(int numberToConvert) {
    stringstream textConverter;
    textConverter << numberToConvert;
    return textConverter.str();
}

string readElements(string element) {
    ifstream configFileContent = read("data/config.txt");
    string currentLineFromConfigFile;

    while (getline(configFileContent, currentLineFromConfigFile)) {
        currentLineFromConfigFile = removeSpacesFromStartAndEnd(currentLineFromConfigFile);

        if (currentLineFromConfigFile.empty()) {
            continue;
        }

        if (currentLineFromConfigFile[0] == '#') {
            continue;
        }

        int equalSignPosition = (int)currentLineFromConfigFile.find('=');

        if (equalSignPosition == (int)string::npos) {
            continue;
        }

        string currentKeyName =
            removeSpacesFromStartAndEnd(currentLineFromConfigFile.substr(0, equalSignPosition));

        string currentKeyValue =
            removeSpacesFromStartAndEnd(currentLineFromConfigFile.substr(equalSignPosition + 1));

        if (currentKeyName == element) {
            return currentKeyValue;
        }
    }

    return "";
}

vector<string> loadAllTeamNamesFromConfigFile() {
    vector<string> allTeamNames;
    ifstream configFileContent = read("data/config.txt");
    string currentLineFromConfigFile;

    while (getline(configFileContent, currentLineFromConfigFile)) {
        currentLineFromConfigFile = removeSpacesFromStartAndEnd(currentLineFromConfigFile);

        if (currentLineFromConfigFile.empty()) {
            continue;
        }

        if (currentLineFromConfigFile[0] == '#') {
            continue;
        }

        int equalSignPosition = (int)currentLineFromConfigFile.find('=');

        if (equalSignPosition == (int)string::npos) {
            continue;
        }

        string currentKeyName =
            removeSpacesFromStartAndEnd(currentLineFromConfigFile.substr(0, equalSignPosition));

        string currentKeyValue =
            removeSpacesFromStartAndEnd(currentLineFromConfigFile.substr(equalSignPosition + 1));

        if (currentKeyName == "Team" ||
            currentKeyName == "Team1" ||
            currentKeyName == "Team2" ||
            currentKeyName == "Team3" ||
            currentKeyName == "Team4" ||
            currentKeyName == "Team5" ||
            currentKeyName == "Team6" ||
            currentKeyName == "Team7" ||
            currentKeyName == "Team8") {
            allTeamNames.push_back(currentKeyValue);
        }
    }

    return allTeamNames;
}

bool configFileHasAllRequiredData() {
    string leagueNameFromConfig = readElements("League");
    string winPointsFromConfig = readElements("Win");
    string drawPointsFromConfig = readElements("Draw");
    string lossPointsFromConfig = readElements("Loss");
    vector<string> allTeamNames = loadAllTeamNamesFromConfigFile();

    if (leagueNameFromConfig.empty()) {
        return false;
    }

    if (winPointsFromConfig.empty()) {
        return false;
    }

    if (drawPointsFromConfig.empty()) {
        return false;
    }

    if (lossPointsFromConfig.empty()) {
        return false;
    }

    if (allTeamNames.empty()) {
        return false;
    }

    return true;
}

bool enteredTeamExistsInLeague(string teamNameToValidate) {
    vector<string> allTeamNames = loadAllTeamNamesFromConfigFile();

    for (int currentTeamIndex = 0; currentTeamIndex < (int)allTeamNames.size(); currentTeamIndex++) {
        if (allTeamNames[currentTeamIndex] == teamNameToValidate) {
            return true;
        }
    }

    return false;
}

void showAllAvailableTeamNames() {
    vector<string> allTeamNames = loadAllTeamNamesFromConfigFile();

    cout << "\nAvailable teams:\n";

    for (int currentTeamIndex = 0; currentTeamIndex < (int)allTeamNames.size(); currentTeamIndex++) {
        cout << "- " << allTeamNames[currentTeamIndex] << "\n";
    }

    cout << "\n";
}

void clearAllEnteredMatchData() {
    enteredTeamNames.clear();
    enteredNumericMatchData.clear();
}

string buildCompleteMatchDateText() {
    string dayText;
    string monthText;
    string yearText;

    if (enteredNumericMatchData[0] < 10) {
        dayText = "0" + convertIntegerToText(enteredNumericMatchData[0]);
    } else {
        dayText = convertIntegerToText(enteredNumericMatchData[0]);
    }

    if (enteredNumericMatchData[1] < 10) {
        monthText = "0" + convertIntegerToText(enteredNumericMatchData[1]);
    } else {
        monthText = convertIntegerToText(enteredNumericMatchData[1]);
    }

    yearText = convertIntegerToText(enteredNumericMatchData[2]);

    return yearText + "-" + monthText + "-" + dayText;
}

void enterDetails() {
    clearAllEnteredMatchData();

    string enteredTextValue;
    int enteredNumberValue;

    cout << "Please enter day of the match: ";
    cin >> enteredNumberValue;
    enteredNumericMatchData.push_back(enteredNumberValue);

    cout << "Please enter month of the match: ";
    cin >> enteredNumberValue;
    enteredNumericMatchData.push_back(enteredNumberValue);

    cout << "Please enter year of the match: ";
    cin >> enteredNumberValue;
    enteredNumericMatchData.push_back(enteredNumberValue);

    showAllAvailableTeamNames();

    cout << "Enter home team: ";
    cin >> enteredTextValue;
    enteredTeamNames.push_back(enteredTextValue);

    cout << "Enter away team: ";
    cin >> enteredTextValue;
    enteredTeamNames.push_back(enteredTextValue);

    cout << "Enter home goals: ";
    cin >> enteredNumberValue;
    enteredNumericMatchData.push_back(enteredNumberValue);

    cout << "Enter away goals: ";
    cin >> enteredNumberValue;
    enteredNumericMatchData.push_back(enteredNumberValue);
}

bool detailsValidation() {
    if (enteredNumericMatchData.size() != 5 || enteredTeamNames.size() != 2) {
        cout << "Error: missing match data\n";
        return false;
    }

    if (enteredNumericMatchData[0] <= 0 || enteredNumericMatchData[0] > 31) {
        cout << "Error: invalid day\n";
        return false;
    }

    if (enteredNumericMatchData[1] <= 0 || enteredNumericMatchData[1] > 12) {
        cout << "Error: invalid month\n";
        return false;
    }

    if (enteredNumericMatchData[2] <= 0) {
        cout << "Error: invalid year\n";
        return false;
    }

    if (enteredNumericMatchData[3] < 0 || enteredNumericMatchData[4] < 0) {
        cout << "Error: goals can not be negative\n";
        return false;
    }

    if (!enteredTeamExistsInLeague(enteredTeamNames[0])) {
        cout << "Error: home team does not exist\n";
        return false;
    }

    if (!enteredTeamExistsInLeague(enteredTeamNames[1])) {
        cout << "Error: away team does not exist\n";
        return false;
    }

    if (enteredTeamNames[0] == enteredTeamNames[1]) {
        cout << "Error: you entered the same team\n";
        return false;
    }

    return true;
}

void pasteDetailsInGames() {
    ofstream gamesFile = appendToFile("data/partidos.txt");

    gamesFile << buildCompleteMatchDateText() << "|"
              << enteredTeamNames[0] << "|"
              << enteredTeamNames[1] << "|"
              << enteredNumericMatchData[3] << "|"
              << enteredNumericMatchData[4] << "\n";
}

int getLastMatchdayNumberFromDatesFile(vector<string> allLinesFromDatesFile) {
    int lastMatchdayNumberFound = 0;

    for (int currentLineIndex = 0; currentLineIndex < (int)allLinesFromDatesFile.size(); currentLineIndex++) {
        if (allLinesFromDatesFile[currentLineIndex].find("MATCHDAY=") == 0) {
            string matchdayNumberAsText = allLinesFromDatesFile[currentLineIndex].substr(9);
            lastMatchdayNumberFound = convertTextToInteger(matchdayNumberAsText);
        }
    }

    return lastMatchdayNumberFound;
}

void pasteDetailsInDates() {
    string currentMatchDateText = buildCompleteMatchDateText();
    string currentMatchLineForDatesFile =
        enteredTeamNames[0] + "|" +
        enteredTeamNames[1] + "|" +
        convertIntegerToText(enteredNumericMatchData[3]) + "|" +
        convertIntegerToText(enteredNumericMatchData[4]);

    vector<string> allLinesFromDatesFile;
    ifstream datesFileContent = read("data/fechas.txt");
    string currentLineFromDatesFile;

    while (getline(datesFileContent, currentLineFromDatesFile)) {
        allLinesFromDatesFile.push_back(currentLineFromDatesFile);
    }

    if (allLinesFromDatesFile.empty()) {
        ofstream datesFile = appendToFile("data/fechas.txt");
        datesFile << "MATCHDAY=1\n";
        datesFile << "DATE=" << currentMatchDateText << "\n";
        datesFile << currentMatchLineForDatesFile << "\n";
        datesFile << "END_MATCHDAY\n";
        return;
    }

    string lastDateFoundInDatesFile = "";
    int lastEndMatchdayLineIndex = -1;

    for (int currentLineIndex = 0; currentLineIndex < (int)allLinesFromDatesFile.size(); currentLineIndex++) {
        if (allLinesFromDatesFile[currentLineIndex].find("DATE=") == 0) {
            lastDateFoundInDatesFile = allLinesFromDatesFile[currentLineIndex].substr(5);
        }

        if (allLinesFromDatesFile[currentLineIndex] == "END_MATCHDAY") {
            lastEndMatchdayLineIndex = currentLineIndex;
        }
    }

    if (lastDateFoundInDatesFile == currentMatchDateText && lastEndMatchdayLineIndex != -1) {
        allLinesFromDatesFile.insert(
            allLinesFromDatesFile.begin() + lastEndMatchdayLineIndex,
            currentMatchLineForDatesFile
        );

        ofstream datesFile = editfiles("data/fechas.txt");

        for (int currentLineIndex = 0; currentLineIndex < (int)allLinesFromDatesFile.size(); currentLineIndex++) {
            datesFile << allLinesFromDatesFile[currentLineIndex] << "\n";
        }
    } else {
        int nextMatchdayNumber =
            getLastMatchdayNumberFromDatesFile(allLinesFromDatesFile) + 1;

        ofstream datesFile = appendToFile("data/fechas.txt");
        datesFile << "MATCHDAY=" << nextMatchdayNumber << "\n";
        datesFile << "DATE=" << currentMatchDateText << "\n";
        datesFile << currentMatchLineForDatesFile << "\n";
        datesFile << "END_MATCHDAY\n";
    }
}

vector<MatchRecord> loadAllMatchesFromGamesFile() {
    vector<MatchRecord> allRegisteredMatches;
    ifstream gamesFileContent = read("data/partidos.txt");
    string currentLineFromGamesFile;

    while (getline(gamesFileContent, currentLineFromGamesFile)) {
        currentLineFromGamesFile = removeSpacesFromStartAndEnd(currentLineFromGamesFile);

        if (currentLineFromGamesFile.empty()) {
            continue;
        }

        stringstream currentLineParts(currentLineFromGamesFile);
        string currentMatchDateText;
        string currentHomeTeamName;
        string currentAwayTeamName;
        string currentHomeGoalsText;
        string currentAwayGoalsText;

        getline(currentLineParts, currentMatchDateText, '|');
        getline(currentLineParts, currentHomeTeamName, '|');
        getline(currentLineParts, currentAwayTeamName, '|');
        getline(currentLineParts, currentHomeGoalsText, '|');
        getline(currentLineParts, currentAwayGoalsText, '|');

        MatchRecord currentMatchRecord;
        currentMatchRecord.matchDate = removeSpacesFromStartAndEnd(currentMatchDateText);
        currentMatchRecord.homeTeamName = removeSpacesFromStartAndEnd(currentHomeTeamName);
        currentMatchRecord.awayTeamName = removeSpacesFromStartAndEnd(currentAwayTeamName);
        currentMatchRecord.homeTeamGoals = convertTextToInteger(removeSpacesFromStartAndEnd(currentHomeGoalsText));
        currentMatchRecord.awayTeamGoals = convertTextToInteger(removeSpacesFromStartAndEnd(currentAwayGoalsText));

        allRegisteredMatches.push_back(currentMatchRecord);
    }

    return allRegisteredMatches;
}

LeagueTableTeamStats createEmptyLeagueTableTeamStats(string teamName) {
    LeagueTableTeamStats emptyTeamStats;
    emptyTeamStats.teamName = teamName;
    emptyTeamStats.matchesPlayed = 0;
    emptyTeamStats.matchesWon = 0;
    emptyTeamStats.matchesDrawn = 0;
    emptyTeamStats.matchesLost = 0;
    emptyTeamStats.goalsScored = 0;
    emptyTeamStats.goalsConceded = 0;
    emptyTeamStats.goalDifference = 0;
    emptyTeamStats.totalPoints = 0;
    return emptyTeamStats;
}

LeagueTableTeamStats* findTeamStatsInsideTable(vector<LeagueTableTeamStats>& leagueTable, string teamNameToFind) {
    for (int currentTeamIndex = 0; currentTeamIndex < (int)leagueTable.size(); currentTeamIndex++) {
        if (leagueTable[currentTeamIndex].teamName == teamNameToFind) {
            return &leagueTable[currentTeamIndex];
        }
    }

    return nullptr;
}

void updateTeamStats(
    LeagueTableTeamStats* teamStatsToUpdate,
    int goalsScoredByThatTeam,
    int goalsConcededByThatTeam,
    int pointsForWin,
    int pointsForDraw,
    int pointsForLoss
) {
    teamStatsToUpdate->matchesPlayed = teamStatsToUpdate->matchesPlayed + 1;
    teamStatsToUpdate->goalsScored = teamStatsToUpdate->goalsScored + goalsScoredByThatTeam;
    teamStatsToUpdate->goalsConceded = teamStatsToUpdate->goalsConceded + goalsConcededByThatTeam;
    teamStatsToUpdate->goalDifference =
        teamStatsToUpdate->goalsScored - teamStatsToUpdate->goalsConceded;

    if (goalsScoredByThatTeam > goalsConcededByThatTeam) {
        teamStatsToUpdate->matchesWon = teamStatsToUpdate->matchesWon + 1;
        teamStatsToUpdate->totalPoints = teamStatsToUpdate->totalPoints + pointsForWin;
    } else if (goalsScoredByThatTeam == goalsConcededByThatTeam) {
        teamStatsToUpdate->matchesDrawn = teamStatsToUpdate->matchesDrawn + 1;
        teamStatsToUpdate->totalPoints = teamStatsToUpdate->totalPoints + pointsForDraw;
    } else {
        teamStatsToUpdate->matchesLost = teamStatsToUpdate->matchesLost + 1;
        teamStatsToUpdate->totalPoints = teamStatsToUpdate->totalPoints + pointsForLoss;
    }
}

bool compareTeamsByTotalPoints(LeagueTableTeamStats firstTeamStats, LeagueTableTeamStats secondTeamStats) {
    return firstTeamStats.totalPoints > secondTeamStats.totalPoints;
}

vector<LeagueTableTeamStats> buildLeagueTableFromAllMatches() {
    vector<LeagueTableTeamStats> leagueTable;
    vector<string> allTeamNames = loadAllTeamNamesFromConfigFile();
    vector<MatchRecord> allRegisteredMatches = loadAllMatchesFromGamesFile();

    int pointsForWin = convertTextToInteger(readElements("Win"));
    int pointsForDraw = convertTextToInteger(readElements("Draw"));
    int pointsForLoss = convertTextToInteger(readElements("Loss"));

    for (int currentTeamIndex = 0; currentTeamIndex < (int)allTeamNames.size(); currentTeamIndex++) {
        leagueTable.push_back(createEmptyLeagueTableTeamStats(allTeamNames[currentTeamIndex]));
    }

    for (int currentMatchIndex = 0; currentMatchIndex < (int)allRegisteredMatches.size(); currentMatchIndex++) {
        LeagueTableTeamStats* homeTeamStatsPointer =
            findTeamStatsInsideTable(leagueTable, allRegisteredMatches[currentMatchIndex].homeTeamName);

        LeagueTableTeamStats* awayTeamStatsPointer =
            findTeamStatsInsideTable(leagueTable, allRegisteredMatches[currentMatchIndex].awayTeamName);

        if (homeTeamStatsPointer != nullptr) {
            updateTeamStats(
                homeTeamStatsPointer,
                allRegisteredMatches[currentMatchIndex].homeTeamGoals,
                allRegisteredMatches[currentMatchIndex].awayTeamGoals,
                pointsForWin,
                pointsForDraw,
                pointsForLoss
            );
        }

        if (awayTeamStatsPointer != nullptr) {
            updateTeamStats(
                awayTeamStatsPointer,
                allRegisteredMatches[currentMatchIndex].awayTeamGoals,
                allRegisteredMatches[currentMatchIndex].homeTeamGoals,
                pointsForWin,
                pointsForDraw,
                pointsForLoss
            );
        }
    }

    sort(leagueTable.begin(), leagueTable.end(), compareTeamsByTotalPoints);
    return leagueTable;
}

void saveLeagueTableInTableFile(vector<LeagueTableTeamStats> leagueTable) {
    ofstream tableFile = editfiles("data/tabla.txt");

    tableFile << "# Team PJ PG PE PP GF GC DG PTS\n";

    for (int currentTeamIndex = 0; currentTeamIndex < (int)leagueTable.size(); currentTeamIndex++) {
        tableFile << currentTeamIndex + 1 << " "
                  << leagueTable[currentTeamIndex].teamName << " "
                  << leagueTable[currentTeamIndex].matchesPlayed << " "
                  << leagueTable[currentTeamIndex].matchesWon << " "
                  << leagueTable[currentTeamIndex].matchesDrawn << " "
                  << leagueTable[currentTeamIndex].matchesLost << " "
                  << leagueTable[currentTeamIndex].goalsScored << " "
                  << leagueTable[currentTeamIndex].goalsConceded << " "
                  << leagueTable[currentTeamIndex].goalDifference << " "
                  << leagueTable[currentTeamIndex].totalPoints << "\n";
    }
}

void showLeagueTableOnScreen() {
    vector<LeagueTableTeamStats> leagueTable = buildLeagueTableFromAllMatches();

    cout << "# Team PJ PG PE PP GF GC DG PTS\n";

    for (int currentTeamIndex = 0; currentTeamIndex < (int)leagueTable.size(); currentTeamIndex++) {
        cout << currentTeamIndex + 1 << " "
             << leagueTable[currentTeamIndex].teamName << " "
             << leagueTable[currentTeamIndex].matchesPlayed << " "
             << leagueTable[currentTeamIndex].matchesWon << " "
             << leagueTable[currentTeamIndex].matchesDrawn << " "
             << leagueTable[currentTeamIndex].matchesLost << " "
             << leagueTable[currentTeamIndex].goalsScored << " "
             << leagueTable[currentTeamIndex].goalsConceded << " "
             << leagueTable[currentTeamIndex].goalDifference << " "
             << leagueTable[currentTeamIndex].totalPoints << "\n";
    }

    cout << "Do you want to save the table in data/tabla.txt? (1 yes / 0 no): ";
    int userChoiceToSaveTable;
    cin >> userChoiceToSaveTable;

    if (userChoiceToSaveTable == 1) {
        saveLeagueTableInTableFile(leagueTable);
        cout << "Table saved in data/tabla.txt\n";
    }
}

void showAllMatchesStoredInGamesFile() {
    vector<MatchRecord> allRegisteredMatches = loadAllMatchesFromGamesFile();

    if (allRegisteredMatches.empty()) {
        cout << "No matches registered yet\n";
        return;
    }

    for (int currentMatchIndex = 0; currentMatchIndex < (int)allRegisteredMatches.size(); currentMatchIndex++) {
        cout << allRegisteredMatches[currentMatchIndex].matchDate << " | "
             << allRegisteredMatches[currentMatchIndex].homeTeamName << " "
             << allRegisteredMatches[currentMatchIndex].homeTeamGoals << " - "
             << allRegisteredMatches[currentMatchIndex].awayTeamGoals << " "
             << allRegisteredMatches[currentMatchIndex].awayTeamName << "\n";
    }
}

void showAllMatchdaysFromDatesFile() {
    ifstream datesFileContent = read("data/fechas.txt");
    string currentLineFromDatesFile;
    bool datesFileHasAnyLine = false;

    while (getline(datesFileContent, currentLineFromDatesFile)) {
        datesFileHasAnyLine = true;
        cout << currentLineFromDatesFile << "\n";
    }

    if (!datesFileHasAnyLine) {
        cout << "No matchdays registered yet\n";
    }
}

string showMainMenuAndReturnUserOption() {
    cout << "\n";
    cout << readElements("League") << "\n";
    cout << "1. View table\n";
    cout << "2. Register match\n";
    cout << "3. View matchday history\n";
    cout << "4. View all matches\n";
    cout << "5. Exit\n";
    cout << "Choose one option: ";

    string userMenuOption;
    cin >> userMenuOption;
    return userMenuOption;
}

void registerOneMatchUsingCurrentFunctions() {
    enterDetails();

    if (detailsValidation()) {
        pasteDetailsInGames();
        pasteDetailsInDates();
        cout << "Match saved correctly\n";
    } else {
        cout << "Match not saved\n";
    }
}

void run() {
    if (!configFileHasAllRequiredData()) {
        cout << "Error: config.txt is missing required data\n";
        return;
    }

    string currentUserMenuOption = "";

    while (currentUserMenuOption != "5") {
        currentUserMenuOption = showMainMenuAndReturnUserOption();

        if (currentUserMenuOption == "1") {
            showLeagueTableOnScreen();
        } else if (currentUserMenuOption == "2") {
            registerOneMatchUsingCurrentFunctions();
        } else if (currentUserMenuOption == "3") {
            showAllMatchdaysFromDatesFile();
        } else if (currentUserMenuOption == "4") {
            showAllMatchesStoredInGamesFile();
        } else if (currentUserMenuOption == "5") {
            cout << "Program finished\n";
        } else {
            cout << "Invalid option\n";
        }
    }
}
