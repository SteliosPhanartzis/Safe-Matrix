#include <iostream>
#include <cstdlib>
#include<cassert> 
using namespace std;

template <class T>
//SM
class SM{
private:
	private:
		int colLow, colHigh, rowLow, rowHigh;
		T **pM;
public:
 	// default constructor
 	// allows for writing things like SA a;
	SM(){
		colLow = 0;
		colHigh = -1;
		rowLow = 0;
		colHigh = -1;
		pM=NULL;
	}

 	// single parameter constructor lets us
 	// create a square matrix
	SM(int side){
		colLow=0; colHigh=side;
		rowLow=0; rowHigh=side;		
		pM= new T*[rowHigh-rowLow+1];
		for(int i = 0; i < (rowHigh-rowLow+1); i++){
			pM[i] = new T[colHigh-colLow+1];
		}
 	}

	//Overloaded constructors
	//2 parameters
	SM(int r, int c){
		colLow=0; colHigh=c;
		rowLow=0; rowHigh=r;
		pM= new T*[rowHigh-rowLow+1];
		for(int i = 0; i < (rowHigh-rowLow+1); i++){
			pM[i] = new T[colHigh-colLow+1];
		}
	}

	
	//4 parameters
	SM(int cL, int cH, int rL, int rH){
		if((cH-cL+1)<=0 || (rH-rL+1)<=0){
			cout<< "constructor error in bounds definition"<<endl;
			exit(1);
		}
		colLow=cL; colHigh=cH;
		rowLow=rL; rowHigh=rH;
		pM= new T*[rH-rL+1];
		for(int i = 0; i < (rowHigh-rowLow+1); i++){
			pM[i] = new T[colHigh-colLow+1];
		}
	}
 	
	// copy constructor for pass by value and
	// initialization
	SM(const SM & s){
		int sizeRow=s.rowHigh-s.rowLow+1;
		int sizeCol=s.colHigh-s.colLow+1;
		rowLow = s.rowLow; rowHigh = s.rowHigh;
		colLow = s.colLow; colHigh = s.colHigh;
		pM= new T*[sizeRow];
		for(int i=0; i<sizeRow; i++)
			pM[i]= new T[sizeCol];
		for(int i=0; i<sizeRow; i++)
			for(int j=0; j<sizeCol; j++)
				pM[i][j] = s.pM[i][j];
	}
 	
	// destructor
 	~SM(){
 		for(int i=0; i<rowHigh-rowLow;i++)
 			delete [] pM[i];
 		delete [] pM;
 	}
 	
 

	// overloaded assignment lets us assign
	// one SA to another
	SM & operator=(const SM & s){
		if(this==&s)
			return *this;
		for(int i=0; i<rowHigh-rowLow;i++)
 			delete [] pM[i];
 		delete [] pM;
 		
 		colLow=s.colLow; colHigh=s.colHigh;
		rowLow=s.rowLow; rowHigh=s.rowHigh;
		int sizeRow=s.rowHigh-s.rowLow+1;
		int sizeCol=s.colHigh-s.colLow+1;
 		
		pM=new T*[sizeRow];
		for(int i=0; i<sizeRow; i++)
			pM[i]= new T[sizeCol];
		for(int i=0; i<sizeRow; i++)
			for(int j=0; j<sizeCol; j++)
				pM[i][j] = s.pM[i][j];
		return *this;
	}
	
	class dim {
    private:
        T* p;
        int low, high;
    public:
        dim(T* in, int l, int h){
            low= l; high= h;
            p= in;
        }
        
        T& operator[](int i) {
            if(i<low || i>high){
                cout<<"index "<<i<<" out of range"<<endl;
                exit(1);
            }
            return p[i-low];
        }
    };
    
	//overloaded [] lets us write
 	//SA x(10,20); x[15]= 100;
 	dim operator[](int i){
	 	if(i<rowLow || i>rowHigh){
			cout<< "index "<<i<<" out of range"<<endl;
		 	exit(1);
		}
        dim param(pM[i-rowLow],colLow, colHigh);
		return param;
	}
	// overloads << so we can directly print SAs
	template <class K>
	friend ostream& operator<<(ostream& os, const SM<K> s);
	
	//Matrix multiplication
	SM operator*(const SM & s){
		if((colHigh-colLow) != (s.rowHigh-s.rowLow)){
			cout<<"The columns of the first matrix must match the rows of the second.\n";
			exit(1);
		}
		int sizeRow=s.rowHigh-s.rowLow;
		int sizeCol=s.colHigh-s.colLow;
		SM product((colHigh-colLow),(s.rowHigh-s.rowLow));
		for(int i = product.colLow; i < sizeCol; i++){
			for(int j = product.rowLow; j < sizeRow; j++){
				product[i][j]=0;
				for(int k = product.colLow; k < sizeCol; k++){
					product[i][j] += pM[i][k] * s.pM[k][j];
				}
			}
		}
		return product;
	}
	
	//Get Methods
	int getRLow(){
		return rowLow;
	}
	int getRHigh(){
		return rowHigh+1;
	}
	int getCLow(){
		return colLow;
	}
	int getCHigh(){
		return colHigh+1;
	}
};

template <class T>
ostream& operator<<(ostream& os, const SM<T> s){
	int sizeRow=s.rowHigh-s.rowLow+1;
	int sizeCol=s.colHigh-s.colLow+1;
	if(s.rowLow == 0)
		sizeRow-=1;
	if(s.colLow == 0)
		sizeCol-=1;
	for(int i=0; i<sizeRow; i++){
		for(int j=0; j<sizeCol; j++)
			cout<<s.pM[i][j]<< " ";
		cout << endl;
	}
	return os;
}; 



////Test Main
//int main(){
//	SM<int> testM(3);
//	SM<int> testM1(3);
//	for(int i = testM.getRLow(); i < testM.getRHigh(); i++){
//		for(int j = testM.getCLow(); j < testM.getCHigh(); j++){
//			testM[i][j] = i;
//			testM1[i][j] = j;
//		}
//	}
//	cout<<testM * testM1;
//	return 0;
//}
