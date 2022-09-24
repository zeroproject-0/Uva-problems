#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
  //! Remove these lines to send
  freopen("input.in", "r", stdin);
  freopen("output.out", "w", stdout);
  // ----------------------------

  int cases;

  scanf("%d\n", &cases);

  for (int i = 0; i < cases; i++)
  {
    int wallsCount;
    scanf("%d\n", &wallsCount);

    int walls[50];

    for (int i = 0; i < wallsCount; i++)
      scanf("%d", &walls[i]);

    int currentWall = walls[0], high = 0, low = 0;

    for (int i = 1; i < wallsCount; i++)
    {
      if (currentWall < walls[i])
        high++;
      else if (currentWall > walls[i])
        low++;
      currentWall = walls[i];
    }

    cout << "Case " << (i + 1) << ": " << high << " " << low << endl;
  }

  //! Remove these lines to send
  fclose(stdin);
  fclose(stdout);
  // ----------------------------

  return 0;
}
