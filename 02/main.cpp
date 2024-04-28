#include <iostream>
#include <map>
#include <regex>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

struct Game
{
  int id;
  vector<map<string, int>> records;
};

void print_game(Game game)
{
  cout << "Game id: " << game.id << endl;
  cout << "Records: " << endl;
  for (auto const &record : game.records)
  {
    for (auto const &pair : record)
    {
      cout << pair.first << ':' << pair.second << ',';
    }
    cout << endl;
  }
  cout << "---" << endl;
}

Game parse_game(string line)
{
  Game game;

  string token;
  stringstream ss(line);

  if (getline(ss, token, ':'))
  {
    smatch sm;
    regex_search(token, sm, regex("Game\\s(\\d+)"));
    game.id = stoi(sm[1]);
  }
  else
  {
    cerr << "Error parsing game id" << endl;
    exit(1);
  }

  vector<map<string, int>> records;

  while (getline(ss, token, ';'))
  {
    map<string, int> record;

    string token2;
    stringstream ss2(token);
    while (getline(ss2, token2, ','))
    {
      smatch sm;
      regex_search(token2, sm, regex("\\s*(\\d+)\\s(\\w+)\\s*"));
      record[sm[2]] = stoi(sm[1]);
    }

    records.push_back(record);
  }

  game.records = records;

  return game;
}

bool check_game_playable(map<string, int> bag, Game game)
{
  for (int i = 0; i < game.records.size(); i++)
  {
    for (auto const &kv : game.records[i])
    {
      int game_count = kv.second;
      int bag_count = bag[kv.first];

      if (game_count > bag_count)
      {
        return false;
      }
    }
  }
  return true;
}

int main()
{

  vector<Game> games;

  string line;
  ifstream file("input.txt");
  if (file.is_open())
  {
    while (getline(file, line))
    {
      Game game = parse_game(line);
      games.push_back(game);
    }
  }
  file.close();

  map<string, int> bag;
  bag["red"] = 12;
  bag["green"] = 13;
  bag["blue"] = 14;

  int acc = 0;

  for (auto const &game : games)
  {
    if (check_game_playable(bag, game))
    {
      acc += game.id;
    }
  }

  cout << "ANSWER: " << acc << endl;
  return 0;
}