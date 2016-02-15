

#include <VGAX.h>
#include <math.h>

VGAX vga ;

byte z1[ ] = {
	0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
	0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 ,
	0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
	0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 
} ;

byte z2[ ] = {
	0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
	0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
	0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
	0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 
} ;	

byte bcol = 0 , fcol = 1 ;
byte v0 = 0 , v1 = 1 , v2 = 1 , v3 = 1 , v4 = 0 , v5 = 1 , v6 = 1 , v7 = 0 ;

void setup( ) {


	randomSeed( analogRead( 5 ) ) ;

	vga.begin( ) ;

}

void drawLine( byte yline ) {

	byte i , j , k , l  , c ;


	for( i = 0 ; i < 120 ; i++ ) {

		k =  7 - ( i & 7 ) ;

		l = z1[ ( i >> 3 ) + 8 ] ;

		if( ( ( l >> k ) & 1 ) == 0 ) {

			vga.putpixel( i , yline , bcol ) ;

		} else {

			vga.putpixel( i , yline , fcol ) ;

		}

	}

}

void updateLine( ) {

	static byte i , j , k , x , y , z  , v , counter ;

	static byte l , c , r ;

	for( i = 1 ; i < 255 ; i++ ) {

		l = i - 1 ;
		c = i ;
		r = i + 1 ;

		x = l ;
		z =  7 - ( x & 7 ) ;
		l = ( ( z1[ x >> 3 ] >> z ) & 1 ) ;


		////////

		x = c ;
		z =  7 - ( x & 7 );
		c = ( ( z1[ x >> 3 ] >> z ) & 1 ) ;


		////////
		
		x = r ;
		z =  7 - ( x & 7 );
		r = ( ( z1[ x >> 3 ] >> z ) & 1 ) ;

//current pattern	111	110	101	100	011	010	001	000
//new state for center cell	0	1	1	0	1	1	1	0


		if( ( l == 0 ) && ( c == 0 ) && ( r == 0 ) ) v = v0 ;
		if( ( l == 0 ) && ( c == 0 ) && ( r == 1 ) ) v = v1 ;
		if( ( l == 0 ) && ( c == 1 ) && ( r == 0 ) ) v = v2 ;
		if( ( l == 0 ) && ( c == 1 ) && ( r == 1 ) ) v = v3 ;
		if( ( l == 1 ) && ( c == 0 ) && ( r == 0 ) ) v = v4 ;
		if( ( l == 1 ) && ( c == 0 ) && ( r == 1 ) ) v = v5 ;
		if( ( l == 1 ) && ( c == 1 ) && ( r == 0 ) ) v = v6 ;
		if( ( l == 1 ) && ( c == 1 ) && ( r == 1 ) ) v = v7 ;


		y = i >> 3 ;
		z = 7 - ( i & 7 ) ;
		//z =  7 - ( i - ( y * 8 ) );

		if( v == 0 ) {

			z2[ y ] = z2[ y ] & ~( 1 << z ) ;

			continue ;

		}


		if( v == 1 ) {
			z2[ y ] = z2[ y ] | ( v << z ) ;
			continue ;
		}



	}


	for( i = 0 ; i < 32 ; i++ ) {

		z1[ i ] = z2[ i ] ;

	}



}

void newLine( ) {

	static byte i ;

	for( i = 0 ; i < 32 ; i++ ) {

		z1[ i ] = random( 0 , 256 ) ;

	}		

	v0 = random( 0 , 2 ) ;
	v1 = random( 0 , 2 ) ;
	v2 = random( 0 , 2 ) ;
	v3 = random( 0 , 2 ) ;
	v4 = random( 0 , 2 ) ;
	v5 = random( 0 , 2 ) ;
	v6 = random( 0 , 2 ) ;
	v7 = random( 0 , 2 ) ;


}

void loop( ) {

	static byte i ;

	for( i = 0 ; i < 60 ; i++ ) {

		drawLine( i ) ;
		updateLine( ) ;

	}

	bcol = random( 0 , 4 ) ;
	fcol = random( 0 , 4 - 1 ) ;

	if( fcol >= bcol ) fcol++ ;
	//bcol=0;fcol=1;
	newLine( ) ;


	vga.delay( 15000 ) ;

}