#include <iostream>
using namespace std;

class IntArray2D {
public:
	IntArray2D( int size0, int size1 ) :
			mArray( 0 ),
			mSize0( size0 ),
			mSize1( size1 ){
		cout << "constructor" << endl;
		mArray = new int( size0 * size1 );
		for( int i=0; i<size0*size1; i++ ){
			mArray[i] = 0;
		}
	}
	
	~IntArray2D(){
		cout << "destructor" << endl;
		delete[] mArray;
		mArray = 0;
	}
	
	int& operator()( int index0, int index1 ){
// 		cout << "get array" << endl;
		return mArray[ index1 * mSize0 + index0 ];
	}
	
	/*
	const int& operator()( int index0, int index1 ) const {
		cout << "set array" << endl;
		return mArray[ index1 * mSize0 + index0 ];
	}
	*/
	
	void disp() {
		for( int y=0; y<mSize1; y++ ){
			for( int x=0; x<mSize0; x++ ) {
				cout << mArray[y*mSize0+x];
			}
			cout << endl;
		}
	}

private:
	int* mArray;
	const int mSize0;
	const int mSize1;
};

int main(){
	int width=5;
	int height=6;
	
	IntArray2D array( width, height );
	array( 3, 0 ) = 5;
	array( 2, 2 ) = 3;
	array.disp();
	
	return 0;
}
	
