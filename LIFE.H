/* ND4 */
#define FIELD_W 250
#define FIELD_H 200

typedef unsigned char byte;

void fope( void );

void PutPixel( int x, int y, int r, int g, int b );

void LifeInit( void );
void LifeStep( void );
void LifeKeyboard( byte Key );
