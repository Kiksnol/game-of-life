/* ND4 */
#include <stdio.h>
#include <stdlib.h>

#include "LIFE.h"

static byte *F1, *F2;
byte Font[2048];

void fope( void )
{
  FILE *F;    
  F = fopen("font3.fnt", "rb");
  if (F != NULL)
  {
    fread(Font, 1, 2048, F);
    fclose(F);
  }
}

void DrawChar( int X0, int Y0, char Ch, int R, int G, int B )
{
  int x, y;

  for (y = 0; y < 8; y++)
    for (x = 0; x < 8; x++)
      if ((Font[Ch * 8 + y] & (0x80 >> x)) != 0)
        PutPixel(X0 + x, Y0 + y, R, G, B);
}

void DrawChars( int X0, int Y0, char *Str, int R, int G, int B )
{
  int i;

  for (i = 0; Str[i] != 0; i++)
    DrawChar(X0, Y0, Str[i], R, G, B), X0 += 8;
}

static int GetCell( byte *F, int x, int y )
{
  x = (x + FIELD_W) % FIELD_W;
  y = (y + FIELD_H) % FIELD_H;
  return F[y * FIELD_W + x];
}                            

static void SetCell( byte *F, int x, int y, int value )
{
  x = (x + FIELD_W) % FIELD_W;
  y = (y + FIELD_H) % FIELD_H;
  F[y * FIELD_W + x] = value;
}

void LSS( void )
{
  int x, y, i;

  for (i = 0; i < 10; i++)
  {
    x = rand() % FIELD_W;
    y = rand() % FIELD_H;
    SetCell(F1, x, y, 1);
    SetCell(F1, x + 1, y, 1);
    SetCell(F1, x + 2, y, 1);
    SetCell(F1, x + 2, y + 1, 1);
    SetCell(F1, x + 1, y + 2, 1);
  }
}

void Pulsar( void )
{
  int x, y, k, j, i;

  char *Pulsar[] =
  {
    "    *     *    ",
    "    *     *    ",
    "    **   **    ",
    "               ",
    "***  ** **  ***",
    "  * * * * * *  ",
    "    **   **    ",
    "               ",
    "    **   **    ",
    "  * * * * * *  ",
    "***  ** **  ***",
    "               ",
    "    **   **    ",
    "    *     *    ",
    "    *     *    "
    };
    for (k = 0; k < 3; k++)
    {
      x = rand() % FIELD_W;
      y = rand() % FIELD_H;
      for (i = 0; i < 15; i++)
        for (j = 0; j < 15; j++)
          if (Pulsar[i][j] == '*')
            SetCell(F1, x + j, y + i, 1);
    }
}

void Beacon( void )
{
  int x, y, k, j, i;

  char *Beacon[] =
    {
      "**  ",
      "*   ",
      "   *",
      "  **"
    };
    for (k = 0; k < 20; k++)
    {
      x = rand() % FIELD_W;
      y = rand() % FIELD_H;
      for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
          if (Beacon[i][j] == '*')
            SetCell(F1, x + j, y + i, 1);
    }
}

static int GetNeighbours( byte *F, int x, int y )
{
  int x1, y1, n = 0;

  for (y1 = y - 1; y1 <= y + 1; y1++)
    for (x1 = x - 1; x1 <= x + 1; x1++)
      if ((x1 != x || y1 != y) && GetCell(F, x1, y1))
        n++;

  return n;
}

static void NewGen( byte *F1, byte *F2 )
{
  int x, y, value, n;

  for (y = 0; y < FIELD_H; y++)
    for (x = 0; x < FIELD_W; x++)
    {
      n = GetNeighbours(F1, x, y);

      if(GetCell(F1, x, y))
        if (n < 2 || n > 3)
          value = 0;
        else
          value = 1;
      else
        if (n == 3)
          value = 1;
        else
          value = 0;

      SetCell(F2, x, y, value);
    }
}

void heart( void )
{

  DrawChars(10, 10, "\3", 255, 0, 0);
}

static void DrawField( byte *F )
{
  int x, y;

  NewGen(F1, F2);

  for (y = 0; y < FIELD_H; y++)
    for (x = 0; x < FIELD_W; x++)
      if (GetCell(F, x, y))
        PutPixel(x, y, 255, 229, 180);
      else
        PutPixel(x, y, x * y * rand() % 80, 0, x * y * rand() % 120);
}

void Clear( void )
{
  F1 = malloc(FIELD_W * FIELD_H);
}

void GliderGun( void )                        
{
  int x, y, k, j, i;

  char *Gun[] = 
  {
    "                        *           ",
    "                      * *           ",
    "            **      **            **",
    "           *   *    **            **",
    "**        *     *   **              ",
    "**        *   * **    * *           ",
    "          *     *       *           ",
    "           *   *                    ",
    "            **                      "
  };
  for (k = 0; k < 3; k++)
    {
      x = rand() % FIELD_W;
      y = rand() % FIELD_H;
      for (i = 0; i < 9; i++)
        for (j = 0; j < 36; j++)
          if (Gun[i][j] == '*')
            SetCell(F1, x + j, y + i, 1);
    }

}

void LifeKeyboard( byte Key )
{
  if (Key == '1')
    Beacon();
  else if (Key == '2')
    LSS();   
  else if (Key == '3')
    Pulsar();
  else if (Key == '4')
    GliderGun();      
  else if (Key == 'c')
    Clear();
  else if (Key == ' ')
    LifeInit();
}

void LifeInit( void )
{
  int x, y;

  F1 = malloc(FIELD_W * FIELD_H);
  F2 = malloc(FIELD_W * FIELD_H);

  for (y = 0; y < FIELD_H; y++)
    for (x = 0; x < FIELD_W; x++)
      SetCell(F1, x, y, rand() % 2);
}

void LifeStep( void )
{
  byte *tmp;

  DrawField(F1);
  NewGen(F1, F2);

  tmp = F1;
  F1 = F2;
  F2 = tmp;
}