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
statistics players[572];

void display_menu();
void selection_handler(int);
void parse_data_file();
void fill_individual_players_statistics(statistics &player, int, string);
void search_player_by_name(string);
void display_results(statistics& player);
void edit_players_data(string);
void display_changes_to_make(statistics& player);
void list_all();
void divider(char);
void save_changes();
void update_data_file();
int changes_handler(char, statistics& player);


int main() {
	char selection;

	parse_data_file();

	cout << "This program outputs bio and performance statistics" \
		"of players of England Premier League 2018-2019." << endl;
	cout << "Database contains 572 players." << endl << endl;
	
	display_menu();
	
	cin >> selection;

	while (selection!='q') {
		selection_handler(selection);
		display_menu();
		cin >> selection;
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

		while (!infile.eof() && (count < 572)) {
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
	for (int i = 0; i < 572; i++) {
		if (regex_search(players[i].name, matches, reg_expr)) {
			display_results(players[i]);
			output++;
		}
	}

	if (output<1) {
		cout << "Players data not found..." << endl << endl;
	}
}

void search_by_team(string team) {
	//Performs regular expression matching and tryes to locate the player 
	//that user queries for.

	int output = 0;
	smatch matches;
	regex reg_expr(team, regex_constants::syntax_option_type::icase);
	for (int i = 0; i < 573; i++) {
		if (regex_search(players[i].current_club, matches, reg_expr)) {
			display_results(players[i]);
			output++;
		}
	}

	if (output < 1) {
		cout << "Team's data not found..." << endl;
	}
}

void display_results(statistics &player) {
	
	//Players info and statistics.

	divider('_');

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
		setw(8) << player.red_cards_overall << setw(8) << player.yellow_cards_overall << endl;

	divider('_');
	
}

void divider(char d) {

	//Prints horizontal separator line.

	for (int i = 0; i < 100; i++) {
		cout << d;
	}
	cout << endl << endl;
}

void display_menu() {
	cout << "1 to see all player's statistics." << endl;
	cout << "2 to search by player's name." << endl;
	cout << "3 to search by team's name." << endl;
	cout << "4 to edit the data for specific player." << endl;
	cout << "q to quit." << endl;
}

void selection_handler(int selection) {
	string team;
	string name;
	switch (selection) {
	case '1':
		list_all();
		break;
	case '2':
		cin.ignore();
		cout << "Enter name to proceed: ";
		getline(cin, name);
		search_player_by_name(name);
		break;
	case '3':
		cin.ignore();
		cout << "Enter team to proceed: ";
		getline(cin, team);
		search_by_team(team);
		break;
	case '4':
		cin.ignore();
		cout << "Enter name to proceed: ";
		getline(cin, name);
		edit_players_data(name);
		save_changes();
		break;
	default:
		cout << "invalid entry..." << endl << endl;
		break;
	}
}

void list_all() {
	for (int i = 0; i < 572; i++) {
		display_results(players[i]);
	}
}

void edit_players_data(string name) {
	//Performs regular expression matching and tries to locate the player 
	//that user queries for.
	char response;
	int players_found = 0;
	int counter = 0;
	char selection;
	smatch matches;
	regex reg_expr(name, regex_constants::syntax_option_type::icase);
	for (int i = 0; i < 573; i++) {
		if (regex_search(players[i].name, matches, reg_expr)) {
			cout << "Would you like to edit data of " << players[i].name << " y/n?" << endl;
			cin >> response;
			if (tolower(response) == 'y') {
				players_found++;
				display_changes_to_make(players[i]);
				cin >> selection;

				while (changes_handler(selection, players[i])!=1) {
					cin >> selection;
				}

				break;
			}
			else {
				continue;
			}
			
		}

	}
	if (players_found < 1) {
		cout << "Players data not found..." << endl << endl;
	}

}

void display_changes_to_make(statistics &player) {
	display_results(player);
	cout << "What would you like to change for " << player.name << "?" << endl << endl;
	cout << "1 to change current club" << endl;
	cout << "2 to change the field position" << endl;
	cout << "q to main menu" << endl;
 }

int changes_handler(char selection, statistics& player) {
	if (selection == '1') {
		cout << "The current club is " << player.current_club << endl;
		cout << "Enter new value: ";
		cin.ignore();
		getline(cin, player.current_club);
		display_results(player);
		return 1;
	}
	else if (selection == '2') {
		cout << "The current field position is " << player.position << endl;
		cout << "Enter new value: ";
		cin.ignore();
		getline(cin, player.position);
		display_results(player);
		return 1;
	}
	else if (selection == 'q') {
		cout << endl;
		return 1;
	}
	else {
		cout << "invalid entry..." << endl;
		return 0;
	}
}

void save_changes() {
	char selection;
	cout << "Changes made are virtual and do not change data file." <<
		"Would you like to make corresponding changes to the data file? y/n";
	cin >> selection;
	if (tolower(selection) == 'y') {
		update_data_file();
	}

}

void update_data_file() {

	ofstream outfile;
	string theader = "name, age, birthday, league, season, position, current_club," \
		"minutes_played_overall, nationality, goals_overall, assists_overall," \
		"penalty_goals, yellow_cards_overall, red_cards_overall";

	outfile.open("england-premier-league-players-2018-to-2019-stats.csv", ios::trunc);
	
	if (outfile.is_open()) {
		outfile << theader << endl;
		for (int i = 0; i < 572; i++) {
			statistics player = players[i];
			outfile << player.name << ',';
			outfile << player.age << ',';
			outfile << player.birthday << ',';
			outfile << player.league << ',';
			outfile << player.season << ',';
			outfile << player.position << ',';
			outfile << player.current_club << ',';
			outfile << player.minutes_played << ',';
			outfile << player.nationality << ',';
			outfile << player.goals_overall << ',';
			outfile << player.assists_overall << ',';
			outfile << player.penalty_goals << ',';
			outfile << player.yellow_cards_overall << ',';
			outfile << player.red_cards_overall << endl;
		}
	}
	else {
		if (outfile.is_open()) outfile.close();
		cout << "An error has occured..." << endl;
	}
	outfile.close();
}