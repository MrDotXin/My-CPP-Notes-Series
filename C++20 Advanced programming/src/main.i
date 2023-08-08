# 1 "main.cpp"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "main.cpp"
# 1 "hd.h" 1



char * getTemporaryBuffer(unsigned int& bytes)
{

 for (;;) {

  while ((char * tmp_buffer = operator new
     (bytes * sizeof(char), nothrow))) {
   bytes /= 2;
   if (bytes == 0)
     return nullptr;
  }

 }

}

void returnTemporaryBuffer(char * buf)
{ delete buf;}
# 2 "main.cpp" 2

int main()
{

 return 0;
}
