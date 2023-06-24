source ./activate
cd vm
make clean
make
cd build
pintos -v -k -T 60 -m 20   --fs-disk=10 -p tests/userprog/read-boundary:read-boundary -p ../../tests/userprog/sample.txt:sample.txt --swap-disk=4 -- -q   -f run read-boundary < /dev/null 2> tests/userprog/read-boundary.errors > tests/userprog/read-boundary.output
perl -I../.. ../../tests/userprog/read-boundary.ck tests/userprog/read-boundary tests/userprog/read-boundary.result