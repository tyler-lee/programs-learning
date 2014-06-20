#ifndef __WORD
#define __WORD

#include <iostream>

using namespace std;

typedef unsigned char byte;

class word {
public:
	word(byte b1, byte b2, byte b3, byte b4) {
		w[0] = b1;
		w[1] = b2;
		w[2] = b3;
		w[3] = b4;
	}

	word(unsigned int wd) {
		w[0] = (wd & 0xff);
		w[1] = ((wd >> 8) & 0xff);
		w[2] = ((wd >> 16) & 0xff);
		w[3] = ((wd >> 24) & 0xff);
	}

	friend ostream& operator<< (ostream& out, const word& wd) {
		//big-endian 先输出大端
	//	out << wd.w[3] << wd.w[2] << wd.w[1] << wd.w[0];
	//	/*
		out << static_cast<int>(wd.w[3])
			<< static_cast<int>(wd.w[2])
			<< static_cast<int>(wd.w[1])
			<< static_cast<int>(wd.w[0]);
		//*/
		return out;
	}

	word& operator& (word& rw) {
		for(int i=0; i<4; i++) {
			w[i] = w[i] & rw[i];
		}

		return *this;
	}

	word& operator= (word& rw) {
		for(int i=0; i<4; i++) {
			w[i] = rw[i];
		}

		return *this;
	}

	byte& operator[] (std::size_t index) {
		return w[index];
	}


private:
	byte w[4];
	word() {
		for(int i=0; i<4; i++) {
			w[i] = 0x00;
		}
	}

};
#endif

int main() {
	byte hex = 0x37;
	byte boy = 0x01;

	word wd = word(hex,hex,hex,hex);
	word wdb = word(boy,boy,boy,boy);

	cout << wd << endl;
	cout << wdb << endl;
	cout << (wd & wdb) << endl;

	 int max = -12;
	 int min = 12;

	word wdint = word(max);

	cout << wdint << endl;

	/*
	cout << (max & 0xff)
		 << ((max >> 8) & 0xff)
		 << ((max >> 16) & 0xff)
		 << ((max >> 24) & 0xff)
		 << endl;


	cout << "hex= " << static_cast<int>(hex) << endl
		 << "high= " << static_cast<int>(high) << endl
		 << "low= " << static_cast<int>(low) << endl;

	word w = {'a','b','c','d'};
	cout << "word= " << w.b1 << w.b2 << w.b3 << w.b4 << endl;
	//*/
}
