#include "lexicon.h"
#include <iostream>
#include <vector>
using namespace std;

bool isOnBoard(const string& str, vector<string>& map);
bool isWord(const string& str);
bool isFound(const string& str);
bool isShort(const string& str);
bool DFS(const string& str, int index, int x, int y, vector<string>& map, vector<vector<bool>>& visited);
void DFS2(int x, int y, vector<string>& map, vector<vector<bool>>& visited, string& prefix, set<string>& result);
int  Player1Score = 0;
int  Player2Score = 0;
int  getScore(const string& str);
void showPlayerScore(int id);
void showAllPossibleWords(vector<string>& map);
Lexicon dictionary("EnglishWords.txt");
Lexicon foundWords1;
Lexicon foundWords2;

bool DFS(const string& str, int index, int x, int y, vector<string>& map, vector<vector<bool>>& visited){
   if(index == str.length()) return true;

   int N = map.size();

   if(x < 0 || x >= N || y < 0 || y >= N) return false;

   if(visited[x][y] || map[x][y] != (char)toupper(str[index])) return false;

   visited[x][y] = true;

   for(int i = x - 1; i <= x + 1; i++){
      for(int j = y - 1; j <= y + 1; j++){
        if(!((x == i) && (y == j)) && DFS(str, index + 1, i, j, map, visited)) return true;
      }
   }

   visited[x][y] = false;
   return false;
}

void DFS2(int x, int y, vector<string>& map, vector<vector<bool>>& visited, string& prefix, set<string>& result){
  int N = map.size();
  if(x < 0 || x >= N || y < 0 || y >= N) return;
  if(visited[x][y]) return;
  prefix += map[x][y];

  if(!dictionary.containsPrefix(prefix)){
    prefix.pop_back();
    return;
  }

  visited[x][y] = true;

  if(dictionary.contains(prefix) && isWord(prefix) && !isShort(prefix) && result.find(prefix) == result.end()){
    result.insert(prefix);
  }
  
  for(int i = x - 1; i <= x + 1; i++){
    for(int j = y - 1; j <= y + 1; j++){
      if(!((x == i) && (y == j))){
         DFS2(i, j, map, visited, prefix, result);
      }
    }
  }

  visited[x][y] = false;
  prefix.pop_back();
}

void showAllPossibleWords(vector<string>& map){
  int N = map.size();
  set<string> result;

  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      string prefix = "";
      vector<vector<bool>> visited(N, vector<bool>(N, false));
      if(dictionary.containsPrefix(prefix)){
        DFS2(i, j, map, visited, prefix, result);
      }
    }
  }
  
  cout << "All possible words:";
  for(const string& word: result){
    cout << " " << word;
  }
  cout << endl;

}

bool isOnBoard(const string& str, vector<string>& map){
  int N = map.size();
  int len = str.length();

  if(len > N * N) return false;

  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      if(map[i][j] == (char)toupper(str[0])){
        vector<vector<bool>> visited(N, vector<bool>(N, false));
        if(DFS(str, 0, i, j, map, visited)) return true;
      }
    }
  }

  return false;
} 


int getScore(const string& str){
  if(str.length() < 4) return 0;
  int len = str.length();
  return len - 3;
}

void showPlayerScore(int id){
  if(id == 1){
    cout << "Player 1 Score: " << Player1Score << endl;
  } else if (id == 2){
    cout << "Player 2 Score: " << Player2Score << endl;
  }
}

bool isShort(const string& str){
  return str.length() < 4;
}

bool isWord(const string& str){
  return dictionary.contains(str);
}

bool isFound(const string& str, int id){
  switch(id){
    case 1:
      if (foundWords1.contains(str)) return true;
      else{
        foundWords1.add(str);
        return false;
      }
      break;
    case 2:
      if (foundWords2.contains(str)) return true;
      else{
        foundWords2.add(str);
        return false;
      }
      break;
    default:
      return false;
  }
}

int main() {
  // TODO
  int N;
  cin >> N;

  vector<string> map;
  for(int i = 0; i < N; i++){
    string s;
    cin >> s;
    map.push_back(s);
  }

  while(true){
    showPlayerScore(1);
    string str;
    cin >> str;
    if (str == "???") break;
    
    if(isShort(str)){
      cout << str << " is too short." << endl;
      continue;
    }

    if(!isWord(str)){
      cout << str << " is not a word." << endl;
      continue;
    }
  
    if (!isOnBoard(str, map)){
      cout << str << " is not on board." << endl;
      continue;
    }

    if(isFound(str, 1)){
      cout << str << " is already found." << endl;
      continue;
    }


    cout << "Correct." << endl;
    Player1Score += getScore(str);
    
  }

  while(true){
    showPlayerScore(2);
    string str;
    cin >> str;
    if (str == "???") break;

    if(isShort(str)){
      cout << str << " is too short." << endl;
      continue;
    }

    if(!isWord(str)){
      cout << str << " is not a word." << endl;
      continue;
    }
  
    if (!isOnBoard(str, map)){
      cout << str << " is not on board." << endl;
      continue;
    }

    if(isFound(str, 2)){
      cout << str << " is already found." << endl;
      continue;
    }

    cout << "Correct." << endl;
    Player2Score += getScore(str);

  }

  showPlayerScore(1);
  showPlayerScore(2);
  if(Player1Score > Player2Score){
      cout << "Player 1 wins!" << endl;
  } else if (Player1Score < Player2Score){
      cout << "Player 2 wins!" << endl;
  } else {
      cout << "It's a tie!" << endl;
  }
  showAllPossibleWords(map);

  return 0;
}
