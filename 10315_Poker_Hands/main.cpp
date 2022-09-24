#include <iostream>
#include <vector>
#include <map>
#include <bits/stdc++.h>

using namespace std;

const vector<char> cards = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
#define WHITE_WINS cout << "White wins.\n";
#define BLACK_WINS cout << "Black wins.\n";
#define TIE cout << "Tie.\n";

vector<string> split(string, char);
int find_card(char card);
void tiebreaker_high_card(vector<string> v_black, vector<string> v_white);

bool is_straight_flush(vector<string> cards)
{
  for (int i = 0; i < cards.size() - 1; i++)
  {
    if (cards[i][1] != cards[i + 1][1])
      return false;
  }

  for (int i = 0; i < cards.size() - 1; i++)
  {
    if (find_card(cards[i][0]) != find_card(cards[i + 1][0]) - 1)
      return false;
  }

  return true;
}

char is_four_of_a_kind(vector<string> cards)
{
  int x = 0;

  for (int i = 0; i < cards.size() - 1; i++)
  {
    if (cards[i][0] == cards[i + 1][0])
    {
      x++;

      if (x == 3)
        return cards[i][0];
    }
    else
    {
      x = 0;
    }
  }

  return '_';
}

char is_full_house(vector<string> cards)
{
  map<char, int> card_counts = map<char, int>();

  for (int i = 0; i < cards.size(); i++)
  {
    char number = cards[i][0];
    if (card_counts.find(number) == card_counts.end())
    {
      card_counts[number] = 1;
    }
    else
      card_counts[number]++;
  }

  if (card_counts.size() != 2)
    return '_';

  map<char, int>::iterator iter;

  for (iter = card_counts.begin(); iter != card_counts.end(); iter++)
  {
    if ((*iter).second == 3)
      return (*iter).first;
  }

  return '_';
}

bool is_flush(vector<string> cards)
{
  for (int i = 0; i < cards.size() - 1; i++)
  {
    if (cards[i][1] != cards[i + 1][1])
      return false;
  }

  return true;
}

bool is_straight(vector<string> cards)
{
  for (int i = 0; i < cards.size() - 1; i++)
  {
    if (cards[i][0] != cards[i + 1][0] - 1)
      return false;
  }

  return true;
}

char is_three_of_kind(vector<string> cards)
{
  int x = 0;

  for (int i = 0; i < cards.size() - 1; i++)
  {
    if (cards[i][0] == cards[i + 1][0])
    {
      x++;

      if (x == 2)
        return cards[i][0];
    }
    else
    {
      x = 0;
    }
  }

  return '_';
}

vector<string> is_two_pair(vector<string> cards)
{
  int x = 0;
  vector<string> res = vector<string>();

  for (int i = 0; i < cards.size() - 1; i++)
  {
    if (cards[i][0] == cards[i + 1][0])
    {
      x++;

      res.push_back(cards[i]);
      res.push_back(cards[i + 1]);
    }
    else
    {
      x = 0;
    }
  }

  return res;
}

vector<string> is_pair(vector<string> cards)
{
  vector<string> res = vector<string>();

  for (int i = 0; i < cards.size() - 1; i++)
  {
    if (cards[i][0] == cards[i + 1][0])
    {
      res.push_back(cards[i]);
      res.push_back(cards[i + 1]);
    }
  }

  return res;
}

char get_high_card(vector<string> cards, ushort pos = 1)
{
  return cards[cards.size() - pos][0];
}

bool is_same_hand(vector<string> white, vector<string> black)
{
  for (int i = 0; i < white.size(); i++)
  {
    if (white[i][0] != black[i][0])
      return false;
  }

  return true;
}

bool get_winner(bool white, bool black)
{
  if (!white && !black)
    return false;

  if (white && !black)
  {
    WHITE_WINS;
  }
  else if (black && !white)
  {
    BLACK_WINS;
  }

  return true;
}

bool get_winner(vector<string> v_white, vector<string> v_black, bool (*func)(vector<string>), void (*tiebreaker)(vector<string>, vector<string>))
{
  bool white = func(v_white);
  bool black = func(v_black);

  if (white && black)
  {
    tiebreaker(v_white, v_black);
    return true;
  }

  return get_winner(white, black);
}

bool get_winner(vector<string> v_white, vector<string> v_black, char (*func)(vector<string>))
{
  char white = func(v_white);
  char black = func(v_black);

  if (white == '_' && black == '_')
    return false;

  int white_index = find_card(white);
  int black_index = find_card(black);

  if (white_index > black_index)
  {
    WHITE_WINS;
  }
  else if (black_index > white_index)
  {
    BLACK_WINS;
  }
  else
  {
    TIE;
  }

  return true;
}

bool t_get_winner(vector<string> v_white, vector<string> v_black, vector<string> (*func)(vector<string>))
{
  vector<string> white = func(v_white);
  vector<string> black = func(v_black);

  if (white.empty() && black.empty())
    return false;

  if (white.size() < 2 && black.size() < 2)
    return false;

  if (white.size() > black.size())
  {
    WHITE_WINS;
    return true;
  }
  else if (white.size() < black.size())
  {
    BLACK_WINS;
    return true;
  }

  int white_index_1 = find_card(white[0][0]);
  int white_index_2 = (white.size() > 2) ? find_card(white[2][0]) : find_card(white[1][0]);
  int white_maior = (white_index_1 > white_index_2) ? white_index_1 : white_index_2;
  int white_minor = (white_index_1 < white_index_2) ? white_index_1 : white_index_2;

  int black_index_1 = find_card(black[0][0]);
  int black_index_2 = (black.size() > 2) ? find_card(black[2][0]) : find_card(black[1][0]);
  int black_maior = (black_index_1 > black_index_2) ? black_index_1 : black_index_2;
  int black_minor = (black_index_1 < black_index_2) ? black_index_1 : black_index_2;

  if (white_maior == black_maior && white_minor == black_minor)
  {
    for (int i = 0; i < black.size(); i++)
    {
      v_black.erase(find(v_black.begin(), v_black.end(), black[i]));
    }

    for (int i = 0; i < black.size(); i++)
    {
      v_white.erase(find(v_white.begin(), v_white.end(), white[i]));
    }

    tiebreaker_high_card(v_white, v_black);

    return true;
  }

  if (white_maior == black_maior)
  {
    if (white_minor > black_minor)
    {
      WHITE_WINS;
    }
    else
    {
      BLACK_WINS;
    }
  }
  else if (white_maior > black_maior)
  {
    WHITE_WINS;
  }
  else
  {
    BLACK_WINS;
  }

  return true;
}

void tiebreaker_high_card(vector<string> v_white, vector<string> v_black)
{
  for (int i = v_black.size() - 1; i >= 0; i--)
  {
    int black_index = find_card(v_black[i][0]);
    int white_index = find_card(v_white[i][0]);

    if (black_index == white_index)
    {
      if (i == 0)
      {
        TIE;
      }
      continue;
    }

    if (black_index > white_index)
    {
      BLACK_WINS;
    }
    else
    {
      WHITE_WINS;
    }
    break;
  }
}

int main(void)
{
  //! Remove these lines to send
  freopen("input.in", "r", stdin);
  freopen("output.out", "w", stdout);
  //----------------------------------

  string s;

  while (getline(cin, s))
  {
    string black_hand = s.substr(0, 14);
    string white_hand = s.substr(15);
    vector<string> v_black_hand = split(black_hand, ' ');
    vector<string> v_white_hand = split(white_hand, ' ');

    sort(v_white_hand.begin(), v_white_hand.end(), [](string a, string b)
         { return find(cards.begin(), cards.end(), a[0]) < find(cards.begin(), cards.end(), b[0]); });

    sort(v_black_hand.begin(), v_black_hand.end(), [](string a, string b)
         { return find(cards.begin(), cards.end(), a[0]) < find(cards.begin(), cards.end(), b[0]); });

    bool white, black;

    if (get_winner(v_white_hand, v_black_hand, is_straight_flush, tiebreaker_high_card))
    {
    }
    else if (is_same_hand(v_white_hand, v_black_hand))
    {
      TIE;
    }
    else if (get_winner(v_white_hand, v_black_hand, is_four_of_a_kind))
    {
    }
    else if (get_winner(v_white_hand, v_black_hand, is_full_house))
    {
    }
    else if (get_winner(v_white_hand, v_black_hand, is_flush, tiebreaker_high_card))
    {
    }
    else if (get_winner(v_white_hand, v_black_hand, is_straight, tiebreaker_high_card))
    {
    }
    else if (get_winner(v_white_hand, v_black_hand, is_three_of_kind))
    {
    }
    else if (t_get_winner(v_white_hand, v_black_hand, is_two_pair))
    {
    }
    else if (t_get_winner(v_white_hand, v_black_hand, is_pair))
    {
    }
    else
    {
      tiebreaker_high_card(v_white_hand, v_black_hand);
    }

    v_black_hand.clear();
    v_white_hand.clear();
  }

  //! Remove these lines to send
  fclose(stdin);
  fclose(stdout);
  // ----------------------------

  return 0;
}

vector<string> split(string s, char delim)
{
  vector<string> result;

  string temp = "";
  for (auto x : s)
  {
    if (x == delim)
    {
      result.push_back(temp);
      temp = "";
    }
    else
    {
      temp += x;
    }
  }

  result.push_back(temp);

  return result;
}

int find_card(char card)
{
  int idx = find(cards.begin(), cards.end(), card) - cards.begin();
  return idx > 12 ? -1 : idx;
}