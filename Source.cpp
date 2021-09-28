#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <regex>
using namespace std;

// Information and stats of individual player
struct statistics {
	string name;
	string birthday;
	string league;
	string season;
	string position;
	string current_club;
	string nationality;
	string age;
	string minutes_played;
	string goals_overall;
	string assists_overall;
	string penalty_goals;
	string yellow_cards_overall;
	string red_cards_overall;
};

// Array to store all players
statistics players[573];

void parse_data_file();
void fill_individual_players_statistics(statistics &player, int, string);
void search_player_by_name(string);
void display_results(statistics& player);
void divider(char);

int main() {
	string name;
	parse_data_file();

	cout << "This program outputs bio and performance statistics" \
		"of players of England Premier League 2018-2019." << endl;
	cout << "Database contains of 573 players." << endl << endl;
	cout << "Enter name: ";
	
	cin >> name;

	while (name!="q") {
		search_player_by_name(name);
		cout << "Enter name to proceed: ";
		cin >> name;
	}

	return 0;
}

void parse_data_file() {
	//Parses CSV data file and extracts information for each player.
	//Stores information in `statistics` struct and plases it in the global array of players.

	int count = 0;
	string column_value;
	
	fstream infile;
	string line;
	infile.open("england-premier-league-players-2018-to-2019-stats.csv");

	if (infile.is_open()) {
		getline(infile, line); //Skip column headers

		while (!infile.eof() && (count < 573)) {
			//On each iteration of while loop it parses one line in CSV file
			//that corresponds to some players infomation and stats.

			//For-loop extracts values that are delimited by comma.
			for (int i = 0; i < 13; i++) {
				getline(infile, column_value, ',');
				fill_individual_players_statistics(players[count], i, column_value);
			}
			//Parses the last column of the line that ends with `\n` character.
			getline(infile, column_value);
			fill_individual_players_statistics(players[count], 13, column_value);
			count++;
		}
		infile.close();
	}
	else {
		//File can not be opened. In this scenario it exits the process.
		cout << "Error reading the data..." << endl;
		exit(1);
	}
	
}

void fill_individual_players_statistics(statistics &player, 
	int column_number, string column_value){
	//This function actually determines the `type` of information extracted from data file.
	//Depending on the column number in the original CSV file it assigns extracted string
	//to the corresponding member of the player struct.
	switch (column_number) {
	case 0:
		player.name = column_value;
		break;
	case 1:
		player.age = column_value;
		break;
	case 2:
		player.birthday = column_value;
		break;
	case 3:
		player.league = column_value;
		break;
	case 4:
		player.season = column_value;
		break;
	case 5:
		player.position = column_value;
		break;
	case 6:
		player.current_club = column_value;
		break;
	case 7:
		player.minutes_played = column_value;
		break;
	case 8:
		player.nationality = column_value;
		break;
	case 9:
		player.goals_overall = column_value;
		break;
	case 10:
		player.assists_overall = column_value;
		break;
	case 11:
		player.penalty_goals = column_value;
		break;
	case 12:
		player.yellow_cards_overall = column_value;
		break;
	case 13:
		player.red_cards_overall = column_value;
		break;
	}
}

void search_player_by_name(string name) {
	//Performs regular expression matching and tryes to locate the player 
	//that user queries for.

	int output = 0;
	smatch matches;
	regex reg_expr(name, regex_constants::syntax_option_type::icase);
	for (int i = 0; i < 573; i++) {
		if (regex_search(players[i].name, matches, reg_expr)) {
			display_results(players[i]);
			output++;
		}
	}

	if (output<1) {
		cout << "Players data not found..." << endl;
	}
}

void display_results(statistics &player) {
	
	//Players info and statistics.

	divider('*');

	cout << left << fixed;
	cout << player.name << endl << endl;
	cout << "*Info*" << endl;
	cout << setw(11) << "Birthday " << setw(7) <<"Age" << setw(15) << "Nationality" << 
		setw(15) << "Position" << setw(15) << "Club" << endl; //15
	cout << setw(11) << player.birthday << setw(7) << player.age << setw(15) << player.nationality 
		<< setw(15) << player.position << setw(15) << player.current_club << endl << endl;

	cout << "*Stats*" << endl;

	cout << setw(16) << "Minutes played" << setw(8) << "Goals" << setw(8) << "Assists"
		<< setw(16) << "Penalty goals" << setw(8) << "R-cards" << setw(8) << "Y-cards" << endl;
	cout << setw(16) << player.minutes_played << setw(8) << player.goals_overall <<
		setw(8) << player.assists_overall << setw(16) << player.penalty_goals <<
		setw(8) << player.red_cards_overall << setw(8) << player.yellow_cards_overall << endl << endl;

	divider('*');
	
}

void divider(char d) {

	//Prints horizontal separator line.

	for (int i = 0; i < 100; i++) {
		cout << d;
	}
	cout << endl;
}

