#ifndef HD_H_
#define HD_H_

char * getTemporaryBuffer(unsigned int& bytes)
{
	// 
	for (;;) {

		while (!(char * tmp_buffer = operator new
					(bytes * sizeof(char), nothrow))) {
			bytes /= 2;
			if (bytes == 0)
					return nullptr;
		}
		
	}
	// can never be here.
}

void returnTemporaryBuffer(char * buf)
{ delete buf;}



#endif 
