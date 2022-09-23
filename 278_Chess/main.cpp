#include <iostream>
#include <string>
#include <math.h>

using namespace std;

int main(int argc, char *argv[])
{
  //! Remove this lines to sumbit
  freopen("input.in", "r", stdin);
  freopen("output.out", "w", stdout);
  // ----------------------------

  int cases;

  scanf("%d\n", &cases);

  for (int i = 0; i < cases; i++)
  {
    char piece;
    int rows, columns;
    scanf("%c %d %d\n", &piece, &rows, &columns);

    switch (piece)
    {
    case 'r':
    case 'Q':
      cout << min(rows, columns) << endl;
      break;
    case 'k':
      cout << ceil((rows * columns) / (float)2) << endl;
      break;
    case 'K':
      cout << (ceil(rows / (float)2) * ceil(columns / (float)2)) << endl;
      break;
    default:
      break;
    }
  }

  //! Remove this lines to sumbit
  fclose(stdin);
  fclose(stdout);
  // ----------------------------

  return 0;
}
