cd resources
7z.exe x ..\NCUI-Library\NCUI-Library.7z.001 -o..\..\NCUI-Library\
cd ..
python config.py Debug
python config.py Release